#ifndef _uufont_h_
#define _uufont_h_
#include <stdint.h>
#include <stdlib.h>

typedef struct uuglyph_s{
  const uint8_t width;         /// < Bitmap dimensions in pixels
  const uint8_t height;        /// < Bitmap dimensions in pixels
  const uint8_t advancex;      /// < Distance to advance cursor (x axis)
  const int8_t  offsetx;       /// < X dist from cursor pos to UL corner
  const int8_t  offsety;       /// < Y dist from cursor pos to UL corner
  const uint8_t bitmap[0];     /// < bitmap_array, can be zero
} uuglyph_t;

typedef struct uufontblock_s{
  const uint16_t first_code;      /// < (first charcode)
  const uint16_t glyph_size;      /// < glyph size
  const uint32_t *glyph;          /// < GlyphOffsetTable
} uufontblock_t;

typedef struct uufont_s{
  const uufontblock_t *blocks;   /// < ordered uufontblock_t's
  const int16_t block_size;      /// < block size
  const uint8_t advancey;        /// < Newline distance (y axis)
  const uint8_t *glyph_stream;   ///
} uufont_t;

const uuglyph_t *get_glyph(const uufont_t *font, const uint16_t code);
#endif // _uufont_h_
