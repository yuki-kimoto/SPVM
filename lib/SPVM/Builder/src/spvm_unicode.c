#include "spvm_unicode.h"

/*
SPVM_UNICODE is originally copied from utf8proc

utf8proc license

https://github.com/JuliaStrings/utf8proc

Copyright © 2014-2018 by Steven G. Johnson, Jiahao Chen, Tony Kelman, Jonas Fonseca, and other contributors listed in the git history.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

int32_t SPVM_UNICODE_convert_unicode_to_utf8(int32_t uc, uint8_t* dst) {
  if (uc < 0x00) {
    return 0;
  } else if (uc < 0x80) {
    dst[0] = (uint8_t)uc;
    return 1;
  } else if (uc < 0x800) {
    dst[0] = (uint8_t)(0xC0 + (uc >> 6));
    dst[1] = (uint8_t)(0x80 + (uc & 0x3F));
    return 2;
  // Note: we allow encoding 0xd800-0xdfff here, so as not to change
  // the API, however, these are actually invalid in UTF-8
  } else if (uc < 0x10000) {
    dst[0] = (uint8_t)(0xE0 + (uc >> 12));
    dst[1] = (uint8_t)(0x80 + ((uc >> 6) & 0x3F));
    dst[2] = (uint8_t)(0x80 + (uc & 0x3F));
    return 3;
  } else if (uc < 0x110000) {
    dst[0] = (uint8_t)(0xF0 + (uc >> 18));
    dst[1] = (uint8_t)(0x80 + ((uc >> 12) & 0x3F));
    dst[2] = (uint8_t)(0x80 + ((uc >> 6) & 0x3F));
    dst[3] = (uint8_t)(0x80 + (uc & 0x3F));
    return 4;
  }
  else {
    return 0;
  }
}

int32_t SPVM_UNICODE_codepoint_valid(int32_t uc) {
  return (((uint32_t)uc)-0xd800 > 0x07ff) && ((uint32_t)uc < 0x110000);
}

int32_t SPVM_UNICODE_iterate(const uint8_t *str, int32_t strlen, int32_t *dst) {
  uint32_t uc;
  const uint8_t *end;

  *dst = -1;
  if (!strlen) return 0;
  end = str + ((strlen < 0) ? 4 : strlen);
  uc = *str++;
  if (uc < 0x80) {
    *dst = uc;
    return 1;
  }
  // Must be between 0xc2 and 0xf4 inclusive to be valid
  if ((uc - 0xc2) > (0xf4-0xc2)) return SPVM_UNICODE_ERROR_INVALIDUTF8;
  if (uc < 0xe0) {         // 2-byte sequence
     // Must have valid continuation character
     if (str >= end || !SPVM_UNICODE_UTF8_COUNT(*str)) return SPVM_UNICODE_ERROR_INVALIDUTF8;
     *dst = ((uc & 0x1f)<<6) | (*str & 0x3f);
     return 2;
  }
  if (uc < 0xf0) {        // 3-byte sequence
     if ((str + 1 >= end) || !SPVM_UNICODE_UTF8_COUNT(*str) || !SPVM_UNICODE_UTF8_COUNT(str[1]))
        return SPVM_UNICODE_ERROR_INVALIDUTF8;
     // Check for surrogate chars
     if (uc == 0xed && *str > 0x9f)
         return SPVM_UNICODE_ERROR_INVALIDUTF8;
     uc = ((uc & 0xf)<<12) | ((*str & 0x3f)<<6) | (str[1] & 0x3f);
     if (uc < 0x800)
         return SPVM_UNICODE_ERROR_INVALIDUTF8;
     *dst = uc;
     return 3;
  }
  // 4-byte sequence
  // Must have 3 valid continuation characters
  if ((str + 2 >= end) || !SPVM_UNICODE_UTF8_COUNT(*str) || !SPVM_UNICODE_UTF8_COUNT(str[1]) || !SPVM_UNICODE_UTF8_COUNT(str[2]))
     return SPVM_UNICODE_ERROR_INVALIDUTF8;
  // Make sure in correct range (0x10000 - 0x10ffff)
  if (uc == 0xf0) {
    if (*str < 0x90) return SPVM_UNICODE_ERROR_INVALIDUTF8;
  } else if (uc == 0xf4) {
    if (*str > 0x8f) return SPVM_UNICODE_ERROR_INVALIDUTF8;
  }
  *dst = ((uc & 7)<<18) | ((*str & 0x3f)<<12) | ((str[1] & 0x3f)<<6) | (str[2] & 0x3f);
  return 4;
}

// Convert UTF-32 to UTF-8
int32_t convert_utf32_to_utf8_char(int32_t utf32ch, char* utf8ch) {
  
  if (utf32ch < 0 || utf32ch > 0x10FFFF) {
    return 0;
  }
  
  int32_t length;
  if (utf32ch < 128) {
    utf8ch[0] = (char)utf32ch;
    utf8ch[1] = 0;
    utf8ch[2] = 0;
    utf8ch[3] = 0;
    length = 1;
  } else if (utf32ch < 2048) {
    utf8ch[0] = 0xC0 | (char)(utf32ch >> 6);
    utf8ch[1] = 0x80 | ((char)utf32ch & 0x3F);
    utf8ch[2] = 0;
    utf8ch[3] = 0;
    length = 2;
  } else if (utf32ch < 65536) {
    utf8ch[0] = 0xE0 | (char)(utf32ch >> 12);
    utf8ch[1] = 0x80 | ((char)(utf32ch >> 6) & 0x3F);
    utf8ch[2] = 0x80 | ((char)utf32ch & 0x3F);
    utf8ch[3] = 0;
    length = 3;
  } else {
    utf8ch[0] = 0xF0 | (char)(utf32ch >> 18);
    utf8ch[1] = 0x80 | ((char)(utf32ch >> 12) & 0x3F);
    utf8ch[2] = 0x80 | ((char)(utf32ch >> 6) & 0x3F);
    utf8ch[3] = 0x80 | ((char)utf32ch & 0x3F);
    length = 4;
  }

  return length;
}


int32_t convert_utf32_to_utf16_char(int32_t utf32ch, int16_t* utf16ch) {
  if (utf32ch < 0 || utf32ch > 0x10FFFF) {
    return 0;
  }
  
  int32_t length;
  if (utf32ch < 0x10000) {
    utf16ch[0] = (int16_t)(utf32ch);
    utf16ch[1] = 0;
    length = 1;
  } else {
    utf16ch[0] = (int16_t)((utf32ch - 0x10000) / 0x400 + 0xD800);
    utf16ch[1] = (int16_t)((utf32ch - 0x10000) % 0x400 + 0xDC00);
    length = 2;
  }

  return length;
}

/*
int GetU8ByteCount(char ch) {
    if (0 <= uint8_t(ch) && uint8_t(ch) < 0x80) {
        return 1;
    }
    if (0xC2 <= uint8_t(ch) && uint8_t(ch) < 0xE0) {
        return 2;
    }
    if (0xE0 <= uint8_t(ch) && uint8_t(ch) < 0xF0) {
        return 3;
    }
    if (0xF0 <= uint8_t(ch) && uint8_t(ch) < 0xF8) {
        return 4;
    }
    return 0;
}

bool IsU8LaterByte(char ch) {
    return 0x80 <= uint8_t(ch) && uint8_t(ch) < 0xC0;
}

bool ConvChU8ToU32(char* u8Ch, char32_t& utf32ch) {
  int numBytes = GetU8ByteCount(u8Ch[0]);
  if (numBytes == 0) {
      return false;
  }
  switch (numBytes) {
    case 1:
      utf32ch = char32_t(uint8_t(u8Ch[0]));
      break;
    case 2:
      if (!IsU8LaterByte(u8Ch[1])) {
          return false;
      }
      if ((uint8_t(u8Ch[0]) & 0x1E) == 0) {
          return false;
      }

      utf32ch = char32_t(u8Ch[0] & 0x1F) << 6;
      utf32ch |= char32_t(u8Ch[1] & 0x3F);
      break;
    case 3:
      if (!IsU8LaterByte(u8Ch[1]) || !IsU8LaterByte(u8Ch[2])) {
          return false;
      }
      if ((uint8_t(u8Ch[0]) & 0x0F) == 0 &&
          (uint8_t(u8Ch[1]) & 0x20) == 0) {
          return false;
      }

      utf32ch = char32_t(u8Ch[0] & 0x0F) << 12;
      utf32ch |= char32_t(u8Ch[1] & 0x3F) << 6;
      utf32ch |= char32_t(u8Ch[2] & 0x3F);
      break;
    case 4:
      if (!IsU8LaterByte(u8Ch[1]) || !IsU8LaterByte(u8Ch[2]) ||
          !IsU8LaterByte(u8Ch[3])) {
          return false;
      }
      if ((uint8_t(u8Ch[0]) & 0x07) == 0 &&
          (uint8_t(u8Ch[1]) & 0x30) == 0) {
          return false;
      }

      utf32ch = char32_t(u8Ch[0] & 0x07) << 18;
      utf32ch |= char32_t(u8Ch[1] & 0x3F) << 12;
      utf32ch |= char32_t(u8Ch[2] & 0x3F) << 6;
      utf32ch |= char32_t(u8Ch[3] & 0x3F);
      break;
    default:
      return false;
  }

  return true;
}
*/
