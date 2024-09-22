#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int vasprintf(char **buf, const char *fmt, va_list ap)
{
#ifdef _WIN32
  int chars;
  char *b;

  if (!buf)
  {
    return -1;
  }
  chars = _vscprintf(fmt, ap);
#else  /* !defined(_WIN32) */
  static char _T_emptybuffer = '\0';
  va_list ap2;

  /* CAW: RAWR! We have to hope to god here that vsnprintf doesn't overwrite
   * our buffer like on some 64bit sun systems... but hey, it's time to move on
   */
  va_copy(ap2, ap);
  chars = vsnprintf(&_T_emptybuffer, 0, fmt, ap2);
  va_end(ap2);
#endif /* defined(_WIN32) */
  if (chars < 0 || (size_t)chars + 1 > SIZE_MAX / sizeof(char))
  {
    return -1;
  }

  b = (char *)malloc(sizeof(char) * ((size_t)chars + 1));
  if (!b)
  {
    return -1;
  }

  if ((chars = vsprintf(b, fmt, ap)) < 0)
  {
    free(b);
  }
  else
  {
    *buf = b;
  }

  return chars;
}

int asprintf(char **strp, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  int r = vasprintf(strp, fmt, ap);
  va_end(ap);
  return r;
}