/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --no-compress --use-color-info --font mine-sweeper.ttf --symbols 0123456789*`  --format lvgl -o minesweeper_font.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef MINESWEEPER_FONT
#define MINESWEEPER_FONT 1
#endif

#if MINESWEEPER_FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002A "*" */
    0x0, 0x18, 0x0, 0x0, 0x30, 0x0, 0x0, 0x60,
    0x0, 0x0, 0xc0, 0x1, 0x9f, 0xf3, 0x3, 0xff,
    0xfe, 0x1, 0xff, 0xf0, 0xf, 0xf, 0xf8, 0x1e,
    0x1f, 0xf0, 0x3c, 0x3f, 0xe0, 0x78, 0x7f, 0xc7,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xfe,
    0x7, 0xff, 0xfc, 0xf, 0xff, 0xf8, 0x7, 0xff,
    0xc0, 0x3, 0xfe, 0x0, 0x67, 0xfc, 0xc0, 0xcf,
    0xf9, 0x80, 0x1, 0x80, 0x0, 0x3, 0x0, 0x0,
    0x6, 0x0, 0x0,

    /* U+0030 "0" */
    0x7f, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0x1f, 0xf8, 0x7, 0xfe, 0x1, 0xff, 0x80, 0x7f,
    0xe0, 0x1f, 0xf8, 0x7, 0xfe, 0x1, 0xff, 0x80,
    0x7f, 0xe0, 0x1f, 0xf8, 0x7, 0xfe, 0x1, 0xff,
    0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
    0xe0,

    /* U+0031 "1" */
    0x7, 0x80, 0x7c, 0x7, 0xe0, 0x7f, 0x7, 0xf8,
    0x7f, 0xc3, 0xfe, 0x1f, 0xf0, 0xf, 0x80, 0x7c,
    0x3, 0xe0, 0x1f, 0x0, 0xf8, 0x7, 0xc0, 0x3e,
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+0032 "2" */
    0x7f, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0x1f, 0xf8, 0x7, 0xc0, 0x1, 0xf0, 0x0, 0xfc,
    0x0, 0xff, 0x0, 0xff, 0x80, 0xff, 0x80, 0x7f,
    0x80, 0x7f, 0xc0, 0x7f, 0xc0, 0x3f, 0xc0, 0xf,
    0xe0, 0x3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf0,

    /* U+0033 "3" */
    0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xfc, 0x0,
    0x1f, 0x0, 0x7, 0xc0, 0x1, 0xf0, 0x0, 0x7c,
    0xf, 0xfe, 0x3, 0xff, 0x0, 0xff, 0xe0, 0x0,
    0x7c, 0x0, 0x1f, 0x0, 0x7, 0xc0, 0x1, 0xf0,
    0x0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xe0,

    /* U+0034 "4" */
    0x1f, 0x9f, 0x7, 0xc7, 0xc3, 0xf1, 0xf0, 0xf8,
    0x7c, 0x7e, 0x1f, 0x1f, 0x7, 0xcf, 0xc1, 0xf3,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1,
    0xf0, 0x0, 0x7c, 0x0, 0x1f, 0x0, 0x7, 0xc0,
    0x1, 0xf0, 0x0, 0x7c, 0x0, 0x1f, 0x0, 0x7,
    0xc0,

    /* U+0035 "5" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0x0, 0xf8, 0x0, 0x3e, 0x0, 0xf, 0x80, 0x3,
    0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0,
    0x7c, 0x0, 0x1f, 0x0, 0x7, 0xc0, 0x1, 0xf0,
    0x0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xe0,

    /* U+0036 "6" */
    0x7f, 0xff, 0x3f, 0xff, 0xcf, 0xff, 0xf3, 0xe0,
    0x0, 0xf8, 0x0, 0x3e, 0x0, 0xf, 0x80, 0x3,
    0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
    0x7f, 0xe0, 0x1f, 0xf8, 0x7, 0xfe, 0x1, 0xff,
    0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
    0xe0,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0,
    0x1f, 0x0, 0x7, 0xc0, 0x1, 0xf0, 0x0, 0x7c,
    0x0, 0x1f, 0x0, 0xf, 0x80, 0x3, 0xe0, 0x1,
    0xf0, 0x0, 0x7c, 0x0, 0x3e, 0x0, 0xf, 0x80,
    0x7, 0xe0, 0x1, 0xf0, 0x0, 0xfc, 0x0, 0x3e,
    0x0,

    /* U+0038 "8" */
    0x7f, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0x1f, 0xf8, 0x7, 0xfe, 0x1, 0xff, 0x80, 0x7d,
    0xff, 0xfe, 0x3f, 0xff, 0x1f, 0xff, 0xef, 0x80,
    0x7f, 0xe0, 0x1f, 0xf8, 0x7, 0xfe, 0x1, 0xff,
    0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
    0xe0,

    /* U+0039 "9" */
    0x7f, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0x1f, 0xf8, 0x7, 0xfe, 0x1, 0xff, 0x80, 0x7f,
    0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xf0, 0x0,
    0x7c, 0x0, 0x1f, 0x0, 0x7, 0xc0, 0x1, 0xf0,
    0x0, 0x7c, 0xff, 0xff, 0x3f, 0xff, 0xcf, 0xff,
    0xe0,

    /* U+0060 "`" */
    0x7, 0x80, 0x1e, 0x3, 0xf8, 0xf, 0xe0, 0xff,
    0x83, 0xfe, 0x3, 0xf8, 0x1, 0xe0, 0x7, 0x80,
    0x6, 0x0, 0x18, 0x0, 0x60, 0x1, 0x80, 0x3f,
    0x80, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 144, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 403, .box_w = 23, .box_h = 23, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 68, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 230, .box_w = 13, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 317, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 259, .box_w = 14, .box_h = 18, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xa, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x40
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 65, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 13, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t minesweeper_font = {
#else
lv_font_t minesweeper_font = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 23,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if MINESWEEPER_FONT*/

