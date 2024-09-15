/*	$OpenBSD: explicit_bzero.c,v 1.4 2015/08/31 02:53:57 guenther Exp $ */
/*
 * Public domain.
 * Written by Matthew Dempsky.
 */

#include <string.h>

#ifndef _MSC_VER

__attribute__((weak)) void
__explicit_bzero_hook(void *buf, size_t len)
{
}

void
explicit_bzero(void *buf, size_t len)
{
	memset(buf, 0, len);
	__explicit_bzero_hook(buf, len);
}

#else

#define _WINSOCKAPI_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void
explicit_bzero(void *buf, size_t len)
{
	SecureZeroMemory (buf, len);
}

#endif