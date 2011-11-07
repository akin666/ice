/*
 *  Created on: Mar 9, 2011
 *      Author: akin
 */

#ifndef ICE_OS_H_
#define ICE_OS_H_

// oses
#if defined(__unix__)
#define OS_UNIX
#endif

#if defined(__posix__)
#define OS_POSIX
#endif

// Real oses
#if defined(_WIN32) or defined(WIN32)
#define OS_WINDOWS
#endif

#if defined(linux) and defined(__ELF__)
#define OS_LINUX
#endif

#if defined(__QNX__)
#define OS_QNX
#endif

#if defined(__ANDROID__)
#define OS_ANDROID
#endif

// Shit oses
#if defined(__APPLE__) or defined(_APPLE_)
#define OS_MAC
#endif

// Real shit oses
#if defined(__IPHONE__)
#define OS_IPHONE
#endif

#endif /* ICE_OS_H_ */

