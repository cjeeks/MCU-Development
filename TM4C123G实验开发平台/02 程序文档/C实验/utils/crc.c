//*****************************************************************************
//
// crc.c - CRC functions.
//
// Copyright (c) 2010-2011 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 8034 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup crc_api
//! @{
//
//*****************************************************************************

#include "utils/crc.h"

//*****************************************************************************
//
// The CRC table for the polynomial C(x) = x^8 + x^2 + x + 1 (CRC-8-CCITT).
//
//*****************************************************************************
static const unsigned char g_pucCrc8CCITT[256] =
{
    0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
    0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
    0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
    0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
    0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
    0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
    0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
    0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
    0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
    0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
    0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
    0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
    0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
    0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
    0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
    0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
    0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
    0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
    0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
    0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
    0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
    0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
    0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
    0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
    0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
    0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
    0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
    0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
    0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
    0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
    0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
    0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};

//*****************************************************************************
//
// The CRC-16 table for the polynomial C(x) = x^16 + x^15 + x^2 + 1 (standard
// CRC-16, also known as CRC-16-IBM and CRC-16-ANSI).
//
//*****************************************************************************
static const unsigned short g_pusCrc16[256] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

//*****************************************************************************
//
// This macro executes one iteration of the CRC-8-CCITT.
//
//*****************************************************************************
#define CRC8_ITER(crc, data)    g_pucCrc8CCITT[(unsigned char)((crc) ^ (data))]

//*****************************************************************************
//
// This macro executes one iteration of the CRC-16.
//
//*****************************************************************************
#define CRC16_ITER(crc, data)   (((crc) >> 8) ^                               \
                                 g_pusCrc16[(unsigned char)((crc) ^ (data))])

//*****************************************************************************
//
//! Calculates the CRC-8-CCITT of an array of bytes.
//!
//! \param ucCrc is the starting CRC-8-CCITT value.
//! \param pucData is a pointer to the data buffer.
//! \param ulCount is the number of bytes in the data buffer.
//!
//! This function is used to calculate the CRC-8-CCITT of the input buffer.
//! The CRC-8-CCITT is computed in a running fashion, meaning that the entire
//! data block that is to have its CRC-8-CCITT computed does not need to be
//! supplied all at once.  If the input buffer contains the entire block of
//! data, then \b ucCrc should be set to 0.  If, however, the entire block of
//! data is not available, then \b ucCrc should be set to 0 for the first
//! portion of the data, and then the returned value should be passed back in
//! as \b ucCrc for the next portion of the data.
//!
//! For example, to compute the CRC-8-CCITT of a block that has been split into
//! three pieces, use the following:
//!
//! \verbatim
//!     ucCrc = Crc8CCITT(0, pucData1, ulLen1);
//!     ucCrc = Crc8CCITT(ucCrc, pucData2, ulLen2);
//!     ucCrc = Crc8CCITT(ucCrc, pucData3, ulLen3);
//! \endverbatim
//!
//! Computing a CRC-8-CCITT in a running fashion is useful in cases where the
//! data is arriving via a serial link (for example) and is therefore not all
//! available at one time.
//!
//! \return The CRC-8-CCITT of the input data.
//
//*****************************************************************************
unsigned char
Crc8CCITT(unsigned char ucCrc, const unsigned char *pucData,
          unsigned long ulCount)
{
    unsigned long ulTemp;

    //
    // If the data buffer is not short-aligned, then perform a single step of
    // the CRC to make it short-aligned.
    //
    if((unsigned long)pucData & 1)
    {
        //
        // Perform the CRC on this input byte.
        //
        ucCrc = CRC8_ITER(ucCrc, *pucData);

        //
        // Skip this input byte.
        //
        pucData++;
        ulCount--;
    }

    //
    // If the data buffer is not word-aligned and there are at least two bytes
    // of data left, then perform two steps of the CRC to make it word-aligned.
    //
    if(((unsigned long)pucData & 2) && (ulCount > 1))
    {
        //
        // Read the next short.
        //
        ulTemp = *(unsigned short *)pucData;

        //
        // Perform the CRC on these two bytes.
        //
        ucCrc = CRC8_ITER(ucCrc, ulTemp);
        ucCrc = CRC8_ITER(ucCrc, ulTemp >> 8);

        //
        // Skip these input bytes.
        //
        pucData += 2;
        ulCount -= 2;
    }

    //
    // While there is at least a word remaining in the data buffer, perform
    // four steps of the CRC to consume a word.
    //
    while(ulCount > 3)
    {
        //
        // Read the next word.
        //
        ulTemp = *(unsigned long *)pucData;

        //
        // Perform the CRC on these four bytes.
        //
        ucCrc = CRC8_ITER(ucCrc, ulTemp);
        ucCrc = CRC8_ITER(ucCrc, ulTemp >> 8);
        ucCrc = CRC8_ITER(ucCrc, ulTemp >> 16);
        ucCrc = CRC8_ITER(ucCrc, ulTemp >> 24);

        //
        // Skip these input bytes.
        //
        pucData += 4;
        ulCount -= 4;
    }

    //
    // If there is a short left in the input buffer, then perform two steps of
    // the CRC.
    //
    if(ulCount > 1)
    {
        //
        // Read the short.
        //
        ulTemp = *(unsigned short *)pucData;

        //
        // Perform the CRC on these two bytes.
        //
        ucCrc = CRC8_ITER(ucCrc, ulTemp);
        ucCrc = CRC8_ITER(ucCrc, ulTemp >> 8);

        //
        // Skip these input bytes.
        //
        pucData += 2;
        ulCount -= 2;
    }

    //
    // If there is a final byte remaining in the input buffer, then perform a
    // single step of the CRC.
    //
    if(ulCount != 0)
    {
        ucCrc = CRC8_ITER(ucCrc, *pucData);
    }

    //
    // Return the resulting CRC-8-CCITT value.
    //
    return(ucCrc);
}

//*****************************************************************************
//
//! Calculates the CRC-16 of an array of bytes.
//!
//! \param usCrc is the starting CRC-16 value.
//! \param pucData is a pointer to the data buffer.
//! \param ulCount is the number of bytes in the data buffer.
//!
//! This function is used to calculate the CRC-16 of the input buffer.  The
//! CRC-16 is computed in a running fashion, meaning that the entire data block
//! that is to have its CRC-16 computed does not need to be supplied all at
//! once.  If the input buffer contains the entire block of data, then \b usCrc
//! should be set to 0.  If, however, the entire block of data is not
//! available, then \b usCrc should be set to 0 for the first portion of the
//! data, and then the returned value should be passed back in as \b usCrc for
//! the next portion of the data.
//!
//! For example, to compute the CRC-16 of a block that has been split into
//! three pieces, use the following:
//!
//! \verbatim
//!     usCrc = Crc16(0, pucData1, ulLen1);
//!     usCrc = Crc16(usCrc, pucData2, ulLen2);
//!     usCrc = Crc16(usCrc, pucData3, ulLen3);
//! \endverbatim
//!
//! Computing a CRC-16 in a running fashion is useful in cases where the data
//! is arriving via a serial link (for example) and is therefore not all
//! available at one time.
//!
//! \return The CRC-16 of the input data.
//
//*****************************************************************************
unsigned short
Crc16(unsigned short usCrc, const unsigned char *pucData,
      unsigned long ulCount)
{
    unsigned long ulTemp;

    //
    // If the data buffer is not short-aligned, then perform a single step of
    // the CRC to make it short-aligned.
    //
    if((unsigned long)pucData & 1)
    {
        //
        // Perform the CRC on this input byte.
        //
        usCrc = CRC16_ITER(usCrc, *pucData);

        //
        // Skip this input byte.
        //
        pucData++;
        ulCount--;
    }

    //
    // If the data buffer is not word-aligned and there are at least two bytes
    // of data left, then perform two steps of the CRC to make it word-aligned.
    //
    if(((unsigned long)pucData & 2) && (ulCount > 1))
    {
        //
        // Read the next short.
        //
        ulTemp = *(unsigned short *)pucData;

        //
        // Perform the CRC on these two bytes.
        //
        usCrc = CRC16_ITER(usCrc, ulTemp);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 8);

        //
        // Skip these input bytes.
        //
        pucData += 2;
        ulCount -= 2;
    }

    //
    // While there is at least a word remaining in the data buffer, perform
    // four steps of the CRC to consume a word.
    //
    while(ulCount > 3)
    {
        //
        // Read the next word.
        //
        ulTemp = *(unsigned long *)pucData;

        //
        // Perform the CRC on these four bytes.
        //
        usCrc = CRC16_ITER(usCrc, ulTemp);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 8);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 16);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 24);

        //
        // Skip these input bytes.
        //
        pucData += 4;
        ulCount -= 4;
    }

    //
    // If there is a short left in the input buffer, then perform two steps of
    // the CRC.
    //
    if(ulCount > 1)
    {
        //
        // Read the short.
        //
        ulTemp = *(unsigned short *)pucData;

        //
        // Perform the CRC on these two bytes.
        //
        usCrc = CRC16_ITER(usCrc, ulTemp);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 8);

        //
        // Skip these input bytes.
        //
        pucData += 2;
        ulCount -= 2;
    }

    //
    // If there is a final byte remaining in the input buffer, then perform a
    // single step of the CRC.
    //
    if(ulCount != 0)
    {
        usCrc = CRC16_ITER(usCrc, *pucData);
    }

    //
    // Return the resulting CRC-16 value.
    //
    return(usCrc);
}

//*****************************************************************************
//
//! Calculates the CRC-16 of an array of words.
//!
//! \param ulWordLen is the length of the array in words (the number of bytes
//! divided by 4).
//! \param pulData is a pointer to the data buffer.
//!
//! This function is a wrapper around the running CRC-16 function, providing
//! the CRC-16 for a single block of data.
//!
//! \return The CRC-16 of the input data.
//
//*****************************************************************************
unsigned short
Crc16Array(unsigned long ulWordLen, const unsigned long *pulData)
{
    //
    // Calculate and return the CRC-16 of this array of words.
    //
    return(Crc16(0, (const unsigned char *)pulData, ulWordLen * 4));
}

//*****************************************************************************
//
//! Calculates three CRC-16s of an array of words.
//!
//! \param ulWordLen is the length of the array in words (the number of bytes
//! divided by 4).
//! \param pulData is a pointer to the data buffer.
//! \param pusCrc3 is a pointer to an array in which to place the three CRC-16
//! values.
//!
//! This function is used to calculate three CRC-16s of the input buffer; the
//! first uses every byte from the array, the second uses only the even-index
//! bytes from the array (in other words, bytes 0, 2, 4, etc.), and the third
//! uses only the odd-index bytes from the array (in other words, bytes 1, 3,
//! 5, etc.).
//!
//! \return None
//
//*****************************************************************************
void
Crc16Array3(unsigned long ulWordLen, const unsigned long *pulData,
            unsigned short *pusCrc3)
{
    unsigned short usCrc, usCrcOdd, usCrcEven;
    unsigned long ulTemp;

    //
    // Initialize the CRC values to zero.
    //
    usCrc = 0;
    usCrcOdd = 0;
    usCrcEven = 0;

    //
    // Loop while there are more words in the data buffer.
    //
    while(ulWordLen--)
    {
        //
        // Read the next word.
        //
        ulTemp = *pulData++;

        //
        // Perform the first CRC on all four data bytes.
        //
        usCrc = CRC16_ITER(usCrc, ulTemp);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 8);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 16);
        usCrc = CRC16_ITER(usCrc, ulTemp >> 24);

        //
        // Perform the second CRC on only the even-index data bytes.
        //
        usCrcEven = CRC16_ITER(usCrcEven, ulTemp);
        usCrcEven = CRC16_ITER(usCrcEven, ulTemp >> 16);

        //
        // Perform the third CRC on only the odd-index data bytes.
        //
        usCrcOdd = CRC16_ITER(usCrcOdd, ulTemp >> 8);
        usCrcOdd = CRC16_ITER(usCrcOdd, ulTemp >> 24);
    }

    //
    // Return the resulting CRC-16 values.
    //
    pusCrc3[0] = usCrc;
    pusCrc3[1] = usCrcEven;
    pusCrc3[2] = usCrcOdd;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
