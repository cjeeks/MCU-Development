/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_JPEG.c
Purpose     : Implementation of GUI_JPEG... functions
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI_Private.h"
#include "jpeglib.h"
#include "jerror.h"
#include "jmemsys.h"


/*********************************************************************
*
*       Local defines & data types
*
**********************************************************************
*/
#define INPUT_BUF_SIZE  4096	/* choose an efficiently fread'able size */

/* Expanded data source object for stdio input */

typedef struct {
  struct jpeg_source_mgr pub;	/* public fields */
  const U8* pFileData;
  I32   FileSize;
  I32   Off;
  boolean start_of_file;	/* have we gotten any data yet? */
} SOURCE_MANAGER;

static const U8 _abEnd[2] = {
    0xFF, JPEG_EOI
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*
 * Initialize source --- called by jpeg_read_header
 * before any data is actually read.
 */

static void _InitSource (j_decompress_ptr cinfo) {
  SOURCE_MANAGER* pSrc = (SOURCE_MANAGER*) cinfo->src;

  /* We reset the empty-input-file flag for each image,
   * but we don't clear the input buffer.
   * This is correct behavior for reading a series of images from one source.
   */
  pSrc->start_of_file = TRUE;
}

/*
 * Fill the input buffer --- called whenever buffer is emptied.
 *
 * In typical applications, this should read fresh data into the buffer
 * (ignoring the current state of next_input_byte & bytes_in_buffer),
 * reset the pointer & count to the start of the buffer, and return TRUE
 * indicating that the buffer has been reloaded.  It is not necessary to
 * fill the buffer entirely, only to obtain at least one more byte.
 *
 * There is no such thing as an EOF return.  If the end of the file has been
 * reached, the routine has a choice of ERREXIT() or inserting fake data into
 * the buffer.  In most cases, generating a warning message and inserting a
 * fake EOI marker is the best course of action --- this will allow the
 * decompressor to output however much of the image is there.  However,
 * the resulting error message is misleading if the real problem is an empty
 * input file, so we handle that case specially.
 *
 * In applications that need to be able to suspend compression due to input
 * not being available yet, a FALSE return indicates that no more data can be
 * obtained right now, but more may be forthcoming later.  In this situation,
 * the decompressor will return to its caller (with an indication of the
 * number of scanlines it has read, if any).  The application should resume
 * decompression after it has loaded more data into the input buffer.  Note
 * that there are substantial restrictions on the use of suspension --- see
 * the documentation.
 *
 * When suspending, the decompressor will back up to a convenient restart point
 * (typically the start of the current MCU). next_input_byte & bytes_in_buffer
 * indicate where the restart point will be if the current call returns FALSE.
 * Data beyond this point must be rescanned after resumption, so move it to
 * the front of the buffer rather than discarding it.
 */

static boolean _FillInputBuffer(j_decompress_ptr cinfo) {
  SOURCE_MANAGER* pSrc = (SOURCE_MANAGER*) cinfo->src;
  size_t nbytes;
  int RemBytes = pSrc->FileSize - pSrc->Off;
  if (RemBytes > 0) {
    nbytes = (RemBytes > INPUT_BUF_SIZE) ? INPUT_BUF_SIZE : RemBytes;
    pSrc->pub.next_input_byte = pSrc->pFileData + pSrc->Off;
    pSrc->Off += nbytes;
  } else {
    if (pSrc->start_of_file)	/* Treat empty input file as fatal error */
      ERREXIT(cinfo, JERR_INPUT_EMPTY);
    WARNMS(cinfo, JWRN_JPEG_EOF);
    /* Insert a fake EOI marker */
    nbytes = 2;
    pSrc->pub.next_input_byte = _abEnd;
  }

  pSrc->pub.bytes_in_buffer = nbytes;
  pSrc->start_of_file = FALSE;
  return TRUE;
}

/*
 * Skip data --- used to skip over a potentially large amount of
 * uninteresting data (such as an APPn marker).
 *
 * Writers of suspendable-input applications must note that skip_input_data
 * is not granted the right to give a suspension return.  If the skip extends
 * beyond the data currently in the buffer, the buffer can be marked empty so
 * that the next read will cause a fill_input_buffer call that can suspend.
 * Arranging for additional bytes to be discarded before reloading the input
 * buffer is the application writer's problem.
 */

static void _SkipInputData (j_decompress_ptr cinfo, long num_bytes) {
  SOURCE_MANAGER* pSrc = (SOURCE_MANAGER*) cinfo->src;
  /* Just a dumb implementation for now.  Could use fseek() except
   * it doesn't work on pipes.  Not clear that being smart is worth
   * any trouble anyway --- large skips are infrequent.
   */
  if (num_bytes > 0) {
    while (num_bytes > (long) pSrc->pub.bytes_in_buffer) {
      num_bytes -= (long) pSrc->pub.bytes_in_buffer;
      (void) _FillInputBuffer(cinfo);
      /* note we assume that fill_input_buffer will never return FALSE,
       * so suspension need not be handled.
       */
    }
    pSrc->pub.next_input_byte += (size_t) num_bytes;
    pSrc->pub.bytes_in_buffer -= (size_t) num_bytes;
  }
}
/*
 * An additional method that can be provided by data source modules is the
 * resync_to_restart method for error recovery in the presence of RST markers.
 * For the moment, this source module just uses the default resync method
 * provided by the JPEG library.  That method assumes that no backtracking
 * is possible.
 */


/*
 * Terminate source --- called by jpeg_finish_decompress
 * after all data has been read.  Often a no-op.
 *
 * NB: *not* called by jpeg_abort or jpeg_destroy; surrounding
 * application must deal with any cleanup that should happen even
 * for error exit.
 */

static void _TermSource(j_decompress_ptr cinfo) {
  /* no work necessary here */
  GUI_USE_PARA(cinfo);
}


static void _InitSrc(j_decompress_ptr cinfo, const U8* pFileData, I32 FileSize) {
  SOURCE_MANAGER* pSrc;
  /* The source object and input buffer are made permanent so that a series
   * of JPEG images can be read from the same file by calling jpeg_stdio_src
   * only before the first one.  (If we discarded the buffer at the end of
   * one image, we'd likely lose the start of the next one.)
   * This makes it unsafe to use this manager and a different source
   * manager serially with the same JPEG object.  Caveat programmer.
   */
  if (cinfo->src == NULL) {	/* first time for this JPEG object? */
    cinfo->src = (jpeg_source_mgr *) (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT, sizeof(SOURCE_MANAGER));
  }
  pSrc = (SOURCE_MANAGER*) cinfo->src;
  pSrc->pub.init_source       = _InitSource;
  pSrc->pub.fill_input_buffer = _FillInputBuffer;
  pSrc->pub.skip_input_data   = _SkipInputData;
  pSrc->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
  pSrc->pub.term_source       = _TermSource;
  pSrc->pub.bytes_in_buffer   = 0;    /* forces fill_input_buffer on first read */
  pSrc->pub.next_input_byte   = NULL; /* until buffer loaded */
  /*
   *  Init private part of Source manager
   */
  pSrc->FileSize  = FileSize;
  pSrc->pFileData = pFileData;
  pSrc->Off       = 0;
}


/*********************************************************************
*
*       Memory allocation
*
**********************************************************************
*/

int AllocCnt;   /* for debugging only */
int TotalSize;
/*
 * Memory allocation and freeing are controlled by the regular library
 * routines malloc() and free().
 */

GLOBAL(void *) jpeg_get_small (j_common_ptr cinfo, size_t sizeofobject) {
  GUI_USE_PARA(cinfo);
  AllocCnt++;
  TotalSize += sizeofobject;
  return (void *) malloc(sizeofobject);
}

GLOBAL(void) jpeg_free_small (j_common_ptr cinfo, void * object, size_t sizeofobject) {
  GUI_USE_PARA(cinfo);
  GUI_USE_PARA(sizeofobject);
  if (--AllocCnt) {
    TotalSize = 0;
  }
  free(object);
}

/*
 * This routine computes the total memory space available for allocation.
 * Here we always say, "we got all you want bud!"
 */

GLOBAL(long) jpeg_mem_available (j_common_ptr cinfo, long min_bytes_needed, long max_bytes_needed, long already_allocated) {
  GUI_USE_PARA(cinfo);
  GUI_USE_PARA(min_bytes_needed);
  GUI_USE_PARA(already_allocated);
  return max_bytes_needed;
}


/*
 * These routines take care of any system-dependent initialization and
 * cleanup required.  Here, there isn't any.
 * just set max_memory_to_use to 0
 */

GLOBAL(long) jpeg_mem_init (j_common_ptr cinfo) { 
  GUI_USE_PARA(cinfo);
  return 0;
}

GLOBAL(void) jpeg_mem_term (j_common_ptr cinfo) {
  GUI_USE_PARA(cinfo);
}















/*********************************************************************
*
*       _Init
*/
static void _Init(struct jpeg_error_mgr* pjerr, struct jpeg_decompress_struct *pcinfo, const void * pFileData, int DataSize) {
  /* 1. Allocate and initialize a JPEG decompression object. */
  pcinfo->err = jpeg_std_error(pjerr);
	jpeg_create_decompress(pcinfo);
  /* 2. Init the source manager so the library can retrieve data via methods */
  _InitSrc(pcinfo, (const U8*)pFileData, DataSize);
  /* 3. Call jpeg_read_header() to obtain image info. */
	jpeg_read_header(pcinfo, TRUE);
}

/*********************************************************************
*
*       _WritePixelsRGB
*/
static void _WritePixelsRGB(const U8*p, int x0, int y0, int xSize) {
  U8 r,g,b;
  while (xSize) {
    r = *p++;
    g = *p++;
    b = *p++;
    LCD_SetColor(r | (g << 8) | (U32)((U32)b << 16));
    LCD_DrawPixel(x0++, y0);
    xSize--;
  }
}

/*********************************************************************
*
*       _WritePixelsGray
*/
static void _WritePixelsGray(const U8*p, int x0, int y0, int xSize) {
  U8 u;
  while (xSize) {
    u = *p++;
    LCD_SetColor(u * (U32)0x10101);
    LCD_DrawPixel(x0++, y0);
    xSize--;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_JPEG_GetInfo
*/
int GUI_JPEG_GetInfo(const void * pFileData, int DataSize, GUI_JPEG_INFO* pInfo) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
  _Init(&jerr, &cinfo, pFileData, DataSize);
  /*
   * Release the JPEG decompression object.
   */
  jpeg_destroy_decompress(&cinfo);
  if (pInfo) {
    pInfo->XSize = cinfo.image_width;
    pInfo->YSize = cinfo.image_height;
  }
  return 0;
}


/*********************************************************************
*
*       GUI_JPEG_Draw
*/
int GUI_JPEG_Draw(const void * pFileData, int DataSize, int x0, int y0) {
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  int Ret = 0;
  GUI_HMEM hBuffer = 0;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
  GUI_LOCK();
  _Init(&jerr, &cinfo, pFileData, DataSize);
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    r.x1 = (r.x0 = x0) + cinfo.image_width - 1;
    r.y1 = (r.y0 = y0) + cinfo.image_height - 1;
    WM_ITERATE_START(&r) {
  #endif
    if (hBuffer) {
      _Init(&jerr, &cinfo, pFileData, DataSize);
    }
    /* 4. Set up parameters for decompression (optional ...) */
    /* 5. jpeg_start_decompress(...); Should normally return quickly */
	  jpeg_start_decompress(&cinfo);
    /* 6. while (scan lines remain to be read) */
	  /*     jpeg_read_scanlines(...); */
    if (!hBuffer) {
      hBuffer = GUI_ALLOC_AllocNoInit(cinfo.image_width * 3);
    }
    while (cinfo.output_scanline < cinfo.output_height) {
      U8* p;
      p = (U8*)GUI_ALLOC_h2p(hBuffer);
      jpeg_read_scanlines(&cinfo, &p, 1);
      if (cinfo.jpeg_color_space == JCS_GRAYSCALE) {
        _WritePixelsGray(p, x0, y0 + cinfo.output_scanline, cinfo.image_width);
      } else {
        _WritePixelsRGB(p, x0, y0 + cinfo.output_scanline, cinfo.image_width);
      }
    }
    /* 7. jpeg_finish_decompress(...); */
    /*    Complete the decompression cycle.  This causes working memory associated */
    /*    with the JPEG object to be released. */
	  jpeg_finish_decompress(&cinfo);
    /* 8. Release the JPEG decompression object. */
    jpeg_destroy_decompress(&cinfo);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_ALLOC_Free(hBuffer);
  GUI_UNLOCK();
  return Ret;
}

/*************************** End of file ****************************/


