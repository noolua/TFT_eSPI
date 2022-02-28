#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#endif
#include <string.h>

#include "uufont.h"

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

const uuglyph_t *get_glyph(const uufont_t *font, const uint16_t code) {
  int16_t min = 0, max = font->block_size - 1, mid = 0;
  uufontblock_t bk = {0, 0, NULL};
  while(min <= max) {
    mid = (max + min) / 2;
    memcpy_P(&bk, &(((uufontblock_t *)pgm_read_pointer(&font->blocks))[mid]), sizeof(uufontblock_t));
    if(code < bk.first_code) {
      max = mid - 1;
    } else if(code >= bk.first_code + bk.glyph_size) {
      min = mid + 1;
    } else {
      /*
        // DIRECT
        return (const uuglyph_t *)&font->glyph_stream[bk.glyph[code - bk.first_code]];

        // STEP BY STEP
        uint32_t *addr = &(((uint32_t *)pgm_read_pointer(&bk.glyph))[code - bk.first_code]);
        uint32_t offset = pgm_read_dword(addr);
        return (const uuglyph_t *)&(((uint8_t *)pgm_read_pointer(&font->glyph_stream))[offset]);
      */
      return (const uuglyph_t *)&(((uint8_t *)pgm_read_pointer(&font->glyph_stream))[pgm_read_dword(&(((uint32_t *)pgm_read_pointer(&bk.glyph))[code - bk.first_code]))]);
    }
  }
  // RETURN FIRST GLYPH
  return (const uuglyph_t *)font->glyph_stream;
}
