//*****************************************************************************
//
// charmap.c - Routines converting between different text codebases.
//
// Copyright (c) 2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 8034 of the Stellaris Graphics Library.
//
//*****************************************************************************

#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "grlib/grlib.h"

//*****************************************************************************
//
//! \addtogroup primitives_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Counts the number of zeros at the start of a word.  This macro uses
// compiler-specific constructs to perform an inline insertion of the "clz"
// instruction, which counts the leading zeros directly.
//
//*****************************************************************************
#if defined(ewarm)
#include <intrinsics.h>
#define NumLeadingZeros(x)      __CLZ(x)
#endif
#if defined(codered) || defined(gcc) || defined(sourcerygxx)
#define NumLeadingZeros(x) __extension__                        \
        ({                                                      \
            register unsigned long __ret, __inp = x;            \
            __asm__("clz %0, %1" : "=r" (__ret) : "r" (__inp)); \
            __ret;                                              \
        })
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
#define NumLeadingZeros(x)      __clz(x)
#endif
#if defined(ccs)
//
// The CCS/TI compiler _norm intrinsic function will generate an inline CLZ
// instruction.
//
#define NumLeadingZeros(x)      _norm(x)
#endif

//*****************************************************************************
//
// An array containing Unicode mappings for ISO8859-2 codes from 0xA1 and above.
//
//*****************************************************************************
const unsigned short g_pusISO8859_2_Unicode[] =
{
    0x0104, 0x02D8, 0x0141, 0x00A4, 0x013D, 0x015A, 0x00A7, 0x00A8,
    0x0160, 0x015E, 0x0164, 0x0179, 0x00AD, 0x017D, 0x017B, 0x00B0,
    0x0105, 0x02DB, 0x0142, 0x00B4, 0x013E, 0x015B, 0x02C7, 0x00B8,
    0x0161, 0x015F, 0x0165, 0x017A, 0x02DD, 0x017E, 0x017C, 0x0154,
    0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0139, 0x0106, 0x00C7, 0x010C,
    0x00C9, 0x0118, 0x00CB, 0x011A, 0x00CD, 0x00CE, 0x010E, 0x0110,
    0x0143, 0x0147, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x00D7, 0x0158,
    0x016E, 0x00DA, 0x0170, 0x00DC, 0x00DD, 0x0162, 0x00DF, 0x0155,
    0x00E1, 0x00E2, 0x0103, 0x00E4, 0x013A, 0x0107, 0x00E7, 0x010D,
    0x00E9, 0x0119, 0x00EB, 0x011B, 0x00ED, 0x00EE, 0x010F, 0x0111,
    0x0144, 0x0148, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x00F7, 0x0159,
    0x016F, 0x00FA, 0x0171, 0x00FC, 0x00FD, 0x0163, 0x02D9
};

//*****************************************************************************
//
// An array containing Unicode mappings for ISO8859-3 codes from 0xA1 and above.
//
//*****************************************************************************
const unsigned short g_pusISO8859_3_Unicode[] =
{
    0x0126, 0x02D8, 0x00A3, 0x00A4, 0x0000, 0x0124, 0x00A7, 0x00A8,
    0x0130, 0x015E, 0x011E, 0x0134, 0x00AD, 0x0000, 0x017B, 0x00B0,
    0x0127, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x0125, 0x00B7, 0x00B8,
    0x0131, 0x015F, 0x011F, 0x0135, 0x00BD, 0x0000, 0x017C, 0x00C0,
    0x00C1, 0x00C2, 0x0000, 0x00C4, 0x010A, 0x0108, 0x00C7, 0x00C8,
    0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 0x0000,
    0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x0120, 0x00D6, 0x00D7, 0x011C,
    0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x016C, 0x015C, 0x00DF, 0x00E0,
    0x00E1, 0x00E2, 0x0000, 0x00E4, 0x010B, 0x0109, 0x00E7, 0x00E8,
    0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 0x0000,
    0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x0121, 0x00F6, 0x00F7, 0x011D,
    0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x016D, 0x015D, 0x02D9
};

//*****************************************************************************
//
// An array containing Unicode mappings for ISO8859-4 codes from 0xA1 and above.
//
//*****************************************************************************
const unsigned short g_pusISO8859_4_Unicode[] =
{
    0x0104, 0x0138, 0x0156, 0x00A4, 0x0128, 0x013B, 0x00A7, 0x00A8,
    0x0160, 0x0112, 0x0122, 0x0166, 0x00AD, 0x017D, 0x00AF, 0x00B0,
    0x0105, 0x02DB, 0x0157, 0x00B4, 0x0129, 0x013C, 0x02C7, 0x00B8,
    0x0161, 0x0113, 0x0123, 0x0167, 0x014A, 0x017E, 0x014B, 0x0100,
    0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x012E, 0x010C,
    0x00C9, 0x0118, 0x00CB, 0x0116, 0x00CD, 0x00CE, 0x012A, 0x0110,
    0x0145, 0x014C, 0x0136, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8,
    0x0172, 0x00DA, 0x00DB, 0x00DC, 0x0168, 0x016A, 0x00DF, 0x0101,
    0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x012F, 0x010D,
    0x00E9, 0x0119, 0x00EB, 0x0117, 0x00ED, 0x00EE, 0x012B, 0x0111,
    0x0146, 0x014D, 0x0137, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8,
    0x0173, 0x00FA, 0x00FB, 0x00FC, 0x0169, 0x016B, 0x02D9
};

//*****************************************************************************
//
//! Maps an ISO8859-1 encoded character to its Unicode equivalent.
//!
//! \param pcSrcChar is a pointer to a string containing ISO8859-1 encoded
//!        text.
//! \param ulCount is the number of bytes in the buffer pointed to by
//!        pcSrcChar.
//! \param pulSkip points to storage that will be written with the number of
//!        bytes to skip in pcSrcChar to get to the next character in the
//!        buffer.
//!
//! This function may be passed to GrCodepageMapTableSet() in a tCodePointMap
//! structure to map source text in ISO8859-1 format into 32 bit Unicode
//! typically used by wide character fonts.  This conversion is trivial since
//! the bottom 256 characters in Unicode are the ISO8859-1 characters and since
//! ISO8859-1 is not a variable length encoding (every character is exactly 1
//! byte).
//!
//! See http://unicode.org/Public/MAPPINGS/ISO8859/8859-1.TXT for more
//! information.
//!
//! \return Returns the Unicode character code for the first character in the
//! pcSrcChar string passed.
//
//*****************************************************************************
unsigned long
GrMapISO8859_1_Unicode(const char *pcSrcChar,
                       unsigned long ulCount,
                       unsigned long *pulSkip)
{
    //
    // Parameter sanity check.
    //
    ASSERT(pulSkip);
    ASSERT(pcSrcChar);

    //
    // There is a 1:1 mapping of characters in ISO8859-1 to Unicode.
    //
    *pulSkip = 1;
    return((unsigned long)((unsigned char)*pcSrcChar));
}

//*****************************************************************************
//
//! Maps an ISO8859-2 encoded character to its Unicode equivalent.
//!
//! \param pcSrcChar is a pointer to a string containing ISO8859-2 encoded
//!        text.
//! \param ulCount is the number of bytes in the buffer pointed to by
//!        pcSrcChar.
//! \param pulSkip points to storage that will be written with the number of
//!        bytes to skip in pcSrcChar to get to the next character in the
//!        buffer.
//!
//! This function may be passed to GrCodepageMapTableSet() in a tCodePointMap
//! structure to map source text in ISO8859-2 format into 32 bit Unicode
//! typically used by wide character fonts.  This conversion is straightforward
//! since character codes 0xA0 and below map directly to the same code in
//! Unicode and those from 0xA1 to 0xFF are converted using a global data
//! table.
//!
//! See http://unicode.org/Public/MAPPINGS/ISO8859/8859-2.TXT for more
//! information.
//!
//! \return Returns the Unicode character code for the first character in the
//! pcSrcChar string passed.
//
//*****************************************************************************
unsigned long
GrMapISO8859_2_Unicode(const char *pcSrcChar,
                       unsigned long ulCount,
                       unsigned long *pulSkip)
{
    //
    // Parameter sanity check.
    //
    ASSERT(pulSkip);
    ASSERT(pcSrcChar);

    //
    // ISO8859 mappings are all 8 bits so we skip a single byte for each
    // character.
    //
    *pulSkip = 1;

    //
    // Is this character one of those which maps directly to Unicode?
    //
    if((unsigned char)*pcSrcChar <= 0xA0)
    {
        return((unsigned long)(unsigned char)*pcSrcChar);
    }
    else
    {
        return((unsigned long)g_pusISO8859_2_Unicode[
                              (unsigned char)*pcSrcChar - 0xA1]);
    }
}

//*****************************************************************************
//
//! Maps an ISO8859-3 encoded character to its Unicode equivalent.
//!
//! \param pcSrcChar is a pointer to a string containing ISO8859-3 encoded
//!        text.
//! \param ulCount is the number of bytes in the buffer pointed to by
//!        pcSrcChar.
//! \param pulSkip points to storage that will be written with the number of
//!        bytes to skip in pcSrcChar to get to the next character in the
//!        buffer.
//!
//! This function may be passed to GrCodepageMapTableSet() in a tCodePointMap
//! structure to map source text in ISO8859-3 format into 32 bit Unicode
//! typically used by wide character fonts.  This conversion is straightforward
//! since character codes 0xA0 and below map directly to the same code in
//! Unicode and those from 0xA1 to 0xFF are converted using a global data table.
//!
//! See http://unicode.org/Public/MAPPINGS/ISO8859/8859-3.TXT for more
//! information.
//!
//! \return Returns the Unicode character code for the first character in the
//! pcSrcChar string passed.
//
//*****************************************************************************
unsigned long
GrMapISO8859_3_Unicode(const char *pcSrcChar,
                       unsigned long ulCount,
                       unsigned long *pulSkip)
{
    //
    // Parameter sanity check.
    //
    ASSERT(pulSkip);
    ASSERT(pcSrcChar);

    //
    // ISO8859 mappings are all 8 bits so we skip a single byte for each
    // character.
    //
    *pulSkip = 1;

    //
    // Is this character one of those which maps directly to Unicode?
    //
    if((unsigned char)*pcSrcChar <= 0xA0)
    {
        return((unsigned long)(unsigned char)*pcSrcChar);
    }
    else
    {
        return((unsigned long)g_pusISO8859_3_Unicode[
               (unsigned char)*pcSrcChar - 0xA1]);
    }
}

//*****************************************************************************
//
//! Maps an ISO8859-4 encoded character to its Unicode equivalent.
//!
//! \param pcSrcChar is a pointer to a string containing ISO8859-4 encoded
//!        text.
//! \param ulCount is the number of bytes in the buffer pointed to by
//!        pcSrcChar.
//! \param pulSkip points to storage that will be written with the number of
//!        bytes to skip in pcSrcChar to get to the next character in the
//!        buffer.
//!
//! This function may be passed to GrCodepageMapTableSet() in a tCodePointMap
//! structure to map source text in ISO8859-4 format into 32 bit Unicode
//! typically used by wide character fonts.  This conversion is straightforward
//! since character codes 0xA0 and below map directly to the same code in
//! Unicode and those from 0xA1 to 0xFF are converted using a global data table.
//!
//! See http://unicode.org/Public/MAPPINGS/ISO8859/8859-4.TXT for more
//! information.
//!
//! \return Returns the Unicode character code for the first character in the
//! pcSrcChar string passed.
//
//*****************************************************************************
unsigned long
GrMapISO8859_4_Unicode(const char *pcSrcChar,
                       unsigned long ulCount,
                       unsigned long *pulSkip)
{
    //
    // Parameter sanity check.
    //
    ASSERT(pulSkip);
    ASSERT(pcSrcChar);

    //
    // ISO8859 mappings are all 8 bits so we skip a single byte for each
    // character.
    //
    *pulSkip = 1;

    //
    // Is this character one of those which maps directly to Unicode?
    //
    if((unsigned char)*pcSrcChar <= 0xA0)
    {
        return((unsigned long)(unsigned char)*pcSrcChar);
    }
    else
    {
        return((unsigned long)g_pusISO8859_4_Unicode[
               (unsigned char)*pcSrcChar - 0xA1]);
    }
}

//*****************************************************************************
//
//! Maps an ISO8859-5 encoded character to its Unicode equivalent.
//!
//! \param pcSrcChar is a pointer to a string containing ISO8859-5 encoded
//!        text.
//! \param ulCount is the number of bytes in the buffer pointed to by
//!        pcSrcChar.
//! \param pulSkip points to storage that will be written with the number of
//!        bytes to skip in pcSrcChar to get to the next character in the
//!        buffer.
//!
//! This function may be passed to GrCodepageMapTableSet() in a tCodePointMap
//! structure to map source text in ISO8859-5 format into 32 bit Unicode
//! typically used by wide character fonts.  This conversion is straightforward
//! since character codes 0xA0 and below map directly to the same code in
//! Unicode and those from 0xA1 to 0xFF map to the Unicode by adding 0x360 to
//! the ISO8859-5 code.
//!
//! See http://unicode.org/Public/MAPPINGS/ISO8859/8859-5.TXT for more
//! information.
//!
//! \return Returns the Unicode character code for the first character in the
//! pcSrcChar string passed.
//
//*****************************************************************************
unsigned long
GrMapISO8859_5_Unicode(const char *pcSrcChar,
                       unsigned long ulCount,
                       unsigned long *pulSkip)
{
    //
    // Parameter sanity check.
    //
    ASSERT(pulSkip);
    ASSERT(pcSrcChar);

    //
    // ISO8859 mappings are all 8 bits so we skip a single byte for each
    // character.
    //
    *pulSkip = 1;

    //
    // Is this character one of those which maps directly to Unicode?
    //
    if((unsigned char)*pcSrcChar <= 0xA0)
    {
        return((unsigned long)(unsigned char)*pcSrcChar);
    }
    else
    {
        return((unsigned long)((unsigned char)*pcSrcChar) + 0x360);
    }
}

//*****************************************************************************
//
//! Maps a UTF-8 encoded character to its Unicode equivalent.
//!
//! \param pcSrcChar is a pointer to a string containing UTF-8 encoded text.
//! \param ulCount is the number of bytes in the buffer pointed to by
//!        pcSrcChar.
//! \param pulSkip points to storage that will be written with the number of
//!        bytes to skip in pcSrcChar to get to the next character in the
//!        buffer.
//!
//! This function may be passed to GrCodepageMapTableSet() in a tCodePointMap
//! structure to map source text in UTF-8 format into 32 bit Unicode typically
//! used by wide character fonts.  This conversion will read bytes from the
//! buffer and decode the first full UTF-8 character found, returning the
//! Unicode code for that character and the number of bytes to advance
//! pcSrcChar by to point to the end of the decoded character.  If no valid
//! UTF-8 character is found, 0 is returned.
//!
//! See http://en.wikipedia.org/wiki/UTF-8 for more information.
//!
//! \return Returns the Unicode character code for the first character in the
//! pcSrcChar string passed.
//
//*****************************************************************************
unsigned long
GrMapUTF8_Unicode(const char *pcSrcChar, unsigned long ulCount,
                  unsigned long *pulSkip)
{
    unsigned long ulUnicode, ulToRead, ulIndex;

    //
    // Parameter sanity check.
    //
    ASSERT(pulSkip);
    ASSERT(pcSrcChar);

    //
    // Clear our our character code storage.
    //
    ulUnicode = 0;
    ulIndex = 0;

    //
    // While we have bytes left to examine in the buffer and the current byte
    // is a continuation code...
    //
    while(ulCount && ((unsigned char)pcSrcChar[ulIndex] & 0xC0) == 0x80)
    {
          //
           // Skip the byte.
           //
           ulIndex++;
           ulCount--;
    }

    //
    // We are now either at the end of the string or the start of a new
    // character unit.  Did we get to the end of the string?
    //
    if(!ulCount)
    {
        //
        // Yes - return 0.
        //
        return(0);
    }

    //
    // Is this a single byte encoded character of the form 0xxxxxxx?
    //
    if(!((unsigned char)(pcSrcChar[ulIndex]) & 0x80))
    {
        //
        // Yes - the Unicode equivalent is just the bottom 7 bits of the
        // UTF-8 byte.
        //
        ulUnicode = (unsigned char)(pcSrcChar[ulIndex++]) & 0x7F;
        ulToRead = 0;
    }
    else
    {
        //
        // This is a multi-byte encoded character. Determine how many bytes
        // it uses.
        //
        ulToRead = NumLeadingZeros(
                ~((unsigned long)pcSrcChar[ulIndex] << 24)) - 1;


        //
        // There can be a maximum of 5 more bytes to read.  If we found more
        // than this, then this is an illegal code.
        //
        if(ulToRead > 5)
        {
            ulUnicode = 0;
            ulToRead = 0;
            ulIndex++;
        }
        else
        {
            //
            // Extract the first bits of the Unicode value from this byte.
            //
            ulUnicode = (unsigned char)pcSrcChar[ulIndex++] &
                        ((1 << (6 - ulToRead)) - 1);

            //
            // Read the remaining bytes encoding this character.
            //
            while(ulCount && ulToRead)
            {
                //
                // Is this a continuation byte with form 10xxxxxx?
                //
                if(((unsigned char)pcSrcChar[ulIndex] & 0xC0) != 0x80)
                {
                    //
                    // No - this is an invalid character to return 0 and tell
                    // the caller to skip past it.
                    //
                    *pulSkip = ulIndex;
                    return(0);
                }
                else
                {
                    //
                    // Extract the bottom 6 bits from the continuation
                    // character and mask them into the Unicode code.
                    //
                    ulUnicode = ((ulUnicode << 6) |
                                 ((unsigned char)pcSrcChar[ulIndex++] & 0x3F));
                    ulToRead--;
                    ulCount--;
                }
            }

            //
            // If we get here and we didn't read the expected number of bytes,
            // this is an invalid character.
            //
            if(ulToRead)
            {
                //
                // We ran out of data before reading all the required
                // continuation bytes so tell the caller to skip the data and
                // return 0 to indicate an error.
                //
                *pulSkip = ulIndex;
                return(0);
            }
        }
    }

    //
    // Tell the caller how many bytes to skip to get to the next character in
    // the string.
    //
    *pulSkip = ulIndex;

    //
    // Return the Unicode character code.
    //
    return(ulUnicode);
}


//*****************************************************************************
//
//! Maps an 32 bit Unicode encoded character to itself.
//!
//! \param pcSrcChar is a pointer to a string containing 32 bit Unicode text.
//! \param ulCount is the number of bytes in the buffer pointed to by
//!        pcSrcChar.
//! \param pulSkip points to storage that will be written with the number of
//!        bytes to skip in pcSrcChar to get to the next character in the
//!        buffer.
//!
//! This function may be passed to GrCodepageMapTableSet() in a tCodePointMap
//! structure to map source text in Unicode (UTF32) format into 32 bit
//! Unicode typically used by wide character fonts.  This identity conversion is
//! trivial - we merely read 4 bytes at a time and return the 32 bit value they
//! contain. It is assumed that the text is encoded in little endian format.
//!
//! \return Returns the Unicode character code for the first character in the
//! pcSrcChar string passed.
//
//*****************************************************************************
unsigned long
GrMapUnicode_Unicode(const char *pcSrcChar,
                     unsigned long ulCount,
                     unsigned long *pulSkip)
{
    //
    // Parameter sanity check.
    //
    ASSERT(pulSkip);
    ASSERT(pcSrcChar);

    //
    // Do we have enough bytes to pull out a single 32 bit character code?
    //
    if(ulCount < 4)
    {
        //
        // Return 0 to indicate an error since we don't have enough data to
        // extract a single character code.
        //
        return(0);
    }
    else
    {
        //
        // We have at least 4 bytes so tell the caller to skip 4 bytes to get
        // the following character and return the Unicode codepoint represented
        // by the first 4 bytes in the buffer.
        //
        *pulSkip = 4;
        return(pcSrcChar[0] | (pcSrcChar[1] << 8) | (pcSrcChar[2] << 16) |
               (pcSrcChar[3] << 24));
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
