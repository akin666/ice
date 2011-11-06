/*
 * common.h
 *
 *  Created on: 12.6.2011
 *      Author: akin
 */

#ifndef ICE_COMMON_H_
#define ICE_COMMON_H_

#define DELTA 0.0001f
#define PI 3.141593f
#define PI2 6.283185f
#define DEG2RAD 0.017453292519943
 // PI/360.0f =
#define PI_OVER_360 0.0087266462599716478846184538424431

namespace ice
{
    typedef unsigned int uint;
    typedef float vec;

    typedef unsigned int UNICODE;
    typedef unsigned int UTF32;
    typedef unsigned short UNICODE16;
    typedef unsigned short UTF16;
    typedef unsigned char UTF8;
    typedef unsigned int Time;
    typedef unsigned int BufferIndex;
    typedef unsigned int MicroSeconds;
    typedef unsigned int Seconds;
}

#endif /* ICE_COMMON_H_ */
