#ifndef _CCRC32_H
#define _CCRC32_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// http://www.networkdls.com/Software.Asp?Review=22
//
// This software / source code is released under the GNU lesser General Public License.
// If you make any changes that you believe improve this free product, please let us
// know so that we may implement them into our version. We give credit where credit is due!
//
//  Last Updated:  	  1/8/2009
//  License: 	   GNU LGPL v3
//  OS Version: 	  Independent
//
// Revisions
// 1/8/2009: Revised code to make type casting compliant with a wider range of compilers.
// 1/8/2009: Added class constructor so that the initialize() function would not need to be called.
//
// Changes:
//  Moved function names, from having capital letter, to having small letter at first.
//  Added std::string fileCRC function.
//
// Usage:
//
//  std::string filename = "HelloWorld.txt";
//  unsigned long hash;
//  CCRC32 crcHash;
//  if( crcHash.fileCRC( filename , hash ) )
//  {
//      // hashing success!
//  } else
//  {
//      // failed
//  }
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

class CCRC32
{
    public:
        CCRC32(void);
        ~CCRC32(void);

        void initialize(void);

        bool fileCRC(const std::string& filename , unsigned long& outCRC );
        bool fileCRC(const char *sFileName, unsigned long *ulOutCRC);
        bool fileCRC(const char *sFileName, unsigned long *ulOutCRC, unsigned long ulBufferSize);

        unsigned long fullCRC(const unsigned char *sData, unsigned long ulDataLength);
        void fullCRC(const unsigned char *sData, unsigned long ulLength, unsigned long *ulOutCRC);

        void partialCRC(unsigned long *ulCRC, const unsigned char *sData, unsigned long ulDataLength);

    private:
        unsigned long reflect(unsigned long ulReflect, const char cChar);
        unsigned long ulTable[256]; // CRC lookup table array.
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
