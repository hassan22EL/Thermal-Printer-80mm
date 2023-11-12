#include "font_iso_8859_7_12x24.c"
#include "font_iso_8859_7_9x17.c"
#include "font_iso_8859_7_8x16.c"
#define MAX_FONT_SUPPORTS  3

static const st_standFont_t * const gstStandFonts[MAX_FONT_SUPPORTS] = {&gst12x24Font, (st_standFont_t*) NULL, &gst8x16Font};

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current font data
 ---------------------------------------------------------------------------------------------------
 * @param : font Index
 * 
 * @return: Pointer to font
 */
 st_standFont_t * getCurrentstandFont(uint8_t value) {
    return ( st_standFont_t *)gstStandFonts[value];
}