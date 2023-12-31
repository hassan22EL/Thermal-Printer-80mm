
#include <stdint.h>
#include <font.h>
#include <stddef.h>



 static const uint8_t  gu8Font_8x16[95*16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char space 
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0xFE, 0xE7, 0x7E, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char !
    0x00, 0x00, 0x13, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x13, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char "
    0x00, 0x04, 0x10, 0x7C, 0xF0, 0x07, 0x1E, 0x04, 0x10, 0x7C, 0xF0, 0x07, 0x1E, 0x04, 0x10, 0x00, // Code for char #
    0x38, 0x1C, 0x44, 0x24, 0x82, 0x20, 0xFF, 0xFF, 0x82, 0x20, 0x14, 0x11, 0x18, 0x0E, 0x00, 0x00, // Code for char $
    0x3C, 0xC0, 0x42, 0x38, 0x42, 0x06, 0xBC, 0x3D, 0x60, 0x42, 0x1C, 0x42, 0x03, 0x3C, 0x00, 0x00, // Code for char %
    0x00, 0x1C, 0x3C, 0x23, 0xC2, 0x20, 0x22, 0x27, 0x9C, 0x18, 0x80, 0x17, 0x80, 0x20, 0x00, 0x00, // Code for char &
    0x13, 0x00, 0x13, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char '
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x0C, 0x30, 0x02, 0x40, 0x01, 0x80, 0x00, 0x00, // Code for char (
    0x01, 0x80, 0x02, 0x40, 0x0C, 0x30, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char )
    0x60, 0x03, 0x40, 0x01, 0x90, 0x04, 0xF8, 0x0F, 0x90, 0x04, 0x40, 0x01, 0x60, 0x03, 0x00, 0x00, // Code for char *
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xF8, 0x0F, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, // Code for char +
    0x00, 0x98, 0x00, 0x98, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char ,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, // Code for char -
    0x00, 0x30, 0x00, 0x78, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char .
    0x00, 0xC0, 0x00, 0x30, 0x00, 0x0C, 0x80, 0x03, 0x70, 0x00, 0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, // Code for char /
    0x00, 0x00, 0xF0, 0x0F, 0x0C, 0x30, 0x02, 0x40, 0x02, 0x40, 0x0C, 0x30, 0xF0, 0x0F, 0x00, 0x00, // Code for char 0
    0x00, 0x00, 0x04, 0x20, 0x04, 0x20, 0xFE, 0x3F, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, // Code for char 1
    0x00, 0x00, 0x18, 0x30, 0x14, 0x2C, 0x02, 0x22, 0x82, 0x21, 0x44, 0x20, 0x38, 0x38, 0x00, 0x00, // Code for char 2
    0x18, 0x0C, 0x04, 0x10, 0x82, 0x20, 0x82, 0x20, 0x82, 0x20, 0x44, 0x11, 0x38, 0x0E, 0x00, 0x00, // Code for char 3
    0x80, 0x03, 0x60, 0x02, 0x18, 0x22, 0x04, 0x22, 0xFE, 0x3F, 0x00, 0x22, 0x00, 0x02, 0x00, 0x00, // Code for char 4
    0xFE, 0x0C, 0x42, 0x14, 0x22, 0x20, 0x22, 0x20, 0x22, 0x20, 0x42, 0x10, 0x80, 0x0F, 0x00, 0x00, // Code for char 5
    0xF0, 0x0F, 0x8C, 0x10, 0x42, 0x20, 0x42, 0x20, 0x42, 0x20, 0x8A, 0x10, 0x0C, 0x0F, 0x00, 0x00, // Code for char 6
    0x0E, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x78, 0x82, 0x07, 0x72, 0x00, 0x0E, 0x00, 0x00, 0x00, // Code for char 7
    0x38, 0x0E, 0x44, 0x11, 0x82, 0x20, 0x82, 0x20, 0x82, 0x20, 0x44, 0x11, 0x38, 0x0E, 0x00, 0x00, // Code for char 8
    0x78, 0x08, 0x84, 0x10, 0x02, 0x21, 0x02, 0x21, 0x02, 0x21, 0x84, 0x10, 0xF8, 0x0F, 0x00, 0x00, // Code for char 9
    0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x60, 0x30, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char :
    0x00, 0x00, 0x00, 0x00, 0x60, 0x98, 0x60, 0xF8, 0x60, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char ;
    0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x60, 0x06, 0x18, 0x18, 0x06, 0x60, 0x01, 0x80, 0x00, 0x00, // Code for char <
    0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x00, 0x00, // Code for char =
    0x01, 0x80, 0x06, 0x60, 0x18, 0x18, 0x60, 0x06, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char >
    0x18, 0x00, 0x14, 0x00, 0x02, 0x40, 0x02, 0xE6, 0x02, 0x41, 0xC4, 0x00, 0x38, 0x00, 0x00, 0x00, // Code for char ?
    0xF8, 0x0F, 0x04, 0x10, 0xE2, 0x23, 0x12, 0x24, 0x12, 0x24, 0x22, 0x22, 0xFC, 0x17, 0x00, 0x00, // Code for char @
    0x00, 0x3C, 0xE0, 0x23, 0x1C, 0x02, 0x02, 0x02, 0x1C, 0x02, 0xE0, 0x23, 0x00, 0x3C, 0x00, 0x00, // Code for char A
    0x02, 0x20, 0xFE, 0x3F, 0x82, 0x20, 0x82, 0x20, 0x82, 0x20, 0x44, 0x21, 0x38, 0x1E, 0x00, 0x00, // Code for char B
    0xF0, 0x07, 0x0C, 0x18, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x04, 0x20, 0x0E, 0x1C, 0x00, 0x00, // Code for char C
    0x02, 0x20, 0xFE, 0x3F, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x0C, 0x18, 0xF0, 0x07, 0x00, 0x00, // Code for char D
    0x02, 0x20, 0xFE, 0x3F, 0x82, 0x20, 0x82, 0x20, 0xE2, 0x23, 0x02, 0x20, 0x0E, 0x3C, 0x00, 0x00, // Code for char E
    0x02, 0x20, 0xFE, 0x3F, 0x82, 0x20, 0x82, 0x20, 0xE2, 0x03, 0x02, 0x00, 0x0E, 0x00, 0x00, 0x00, // Code for char F
    0xE0, 0x07, 0x18, 0x18, 0x04, 0x10, 0x02, 0x20, 0x82, 0x20, 0x84, 0x10, 0x8E, 0x3F, 0x80, 0x00, // Code for char G
    0x02, 0x20, 0xFE, 0x3F, 0x42, 0x20, 0x40, 0x00, 0x40, 0x00, 0x42, 0x20, 0xFE, 0x3F, 0x02, 0x20, // Code for char H
    0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0xFE, 0x3F, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x00, 0x00, // Code for char I
    0x00, 0x0E, 0x00, 0x10, 0x00, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x10, 0xFE, 0x0F, 0x02, 0x00, // Code for char J
    0x02, 0x20, 0xFE, 0x3F, 0x42, 0x20, 0xC0, 0x00, 0x30, 0x03, 0x0E, 0x0C, 0x02, 0x30, 0x00, 0x20, // Code for char K
    0x02, 0x20, 0xFE, 0x3F, 0x02, 0x20, 0x02, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3C, 0x00, 0x00, // Code for char L
    0xFE, 0x3F, 0x04, 0x20, 0x38, 0x00, 0xC0, 0x01, 0x38, 0x00, 0x04, 0x20, 0xFE, 0x3F, 0x00, 0x00, // Code for char M
    0xFE, 0x3F, 0x04, 0x20, 0x38, 0x00, 0xC0, 0x01, 0x00, 0x0E, 0x02, 0x10, 0xFE, 0x3F, 0x02, 0x00, // Code for char N
    0xF8, 0x0F, 0x04, 0x10, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x04, 0x10, 0xF8, 0x0F, 0x00, 0x00, // Code for char O
    0x02, 0x20, 0xFE, 0x3F, 0x02, 0x21, 0x02, 0x21, 0x02, 0x01, 0x84, 0x00, 0x78, 0x00, 0x00, 0x00, // Code for char P
    0xF0, 0x07, 0x0C, 0x18, 0x02, 0x24, 0x02, 0x24, 0x02, 0x64, 0x0C, 0x98, 0xF0, 0x87, 0x00, 0x00, // Code for char Q
    0x02, 0x20, 0xFE, 0x3F, 0x82, 0x20, 0x82, 0x00, 0x82, 0x01, 0x44, 0x0E, 0x38, 0x30, 0x00, 0x20, // Code for char R
    0x38, 0x3E, 0x44, 0x10, 0x42, 0x20, 0x82, 0x20, 0x84, 0x20, 0x0E, 0x11, 0x00, 0x0E, 0x00, 0x00, // Code for char S
    0x0E, 0x00, 0x02, 0x20, 0x02, 0x20, 0xFE, 0x3F, 0x02, 0x20, 0x02, 0x20, 0x0E, 0x00, 0x00, 0x00, // Code for char T
    0x02, 0x00, 0xFE, 0x1F, 0x02, 0x20, 0x00, 0x20, 0x00, 0x20, 0x02, 0x20, 0xFE, 0x1F, 0x02, 0x00, // Code for char U
    0x3E, 0x00, 0xC2, 0x03, 0x00, 0x0C, 0x00, 0x30, 0x00, 0x0C, 0xC2, 0x03, 0x3E, 0x00, 0x00, 0x00, // Code for char V
    0xFE, 0x07, 0x02, 0x38, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x07, 0x02, 0x38, 0xFE, 0x07, 0x00, 0x00, // Code for char W
    0x02, 0x30, 0x0E, 0x2C, 0xB2, 0x03, 0x40, 0x00, 0xB2, 0x03, 0x0E, 0x2C, 0x02, 0x30, 0x00, 0x00, // Code for char X
    0x06, 0x00, 0x3A, 0x20, 0xC0, 0x20, 0x00, 0x3F, 0xC0, 0x20, 0x3A, 0x20, 0x06, 0x00, 0x00, 0x00, // Code for char Y
    0x0E, 0x30, 0x02, 0x2C, 0x02, 0x23, 0xE2, 0x20, 0x1A, 0x20, 0x06, 0x20, 0x02, 0x3C, 0x00, 0x00, // Code for char Z
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, // Code for char [
    0x06, 0x00, 0x18, 0x00, 0x60, 0x00, 0x80, 0x01, 0x00, 0x06, 0x00, 0x18, 0x00, 0x60, 0x00, 0x00, // Code for char BackSlash
    0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char ]
    0x08, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, // Code for char ^
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, // Code for char _
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char `
    0x00, 0x1C, 0x40, 0x22, 0x20, 0x21, 0x20, 0x21, 0x20, 0x21, 0x20, 0x11, 0xC0, 0x3F, 0x00, 0x20, // Code for char a
    0x02, 0x00, 0xFE, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40, 0x10, 0x80, 0x0F, 0x00, 0x00, // Code for char b
    0x80, 0x0F, 0x40, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40, 0x20, 0xE0, 0x18, 0x00, 0x00, // Code for char c
    0x80, 0x0F, 0x40, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xFE, 0x3F, 0x02, 0x20, 0x00, 0x00, // Code for char d
    0x80, 0x0F, 0x40, 0x11, 0x20, 0x21, 0x20, 0x21, 0x20, 0x21, 0x40, 0x21, 0x80, 0x19, 0x00, 0x00, // Code for char e
    0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0xFC, 0x3F, 0x22, 0x20, 0x22, 0x20, 0x22, 0x00, 0x04, 0x00, // Code for char f
    0x00, 0x70, 0xC0, 0x8D, 0x20, 0x8A, 0x20, 0x8A, 0x20, 0x8A, 0xC0, 0x91, 0x20, 0x60, 0x20, 0x00, // Code for char g
    0x02, 0x20, 0xFE, 0x3F, 0x40, 0x20, 0x20, 0x00, 0x20, 0x00, 0x20, 0x20, 0xC0, 0x3F, 0x00, 0x20, // Code for char h
    0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 0x20, 0xE3, 0x3F, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, // Code for char i
    0x00, 0x30, 0x00, 0x40, 0x20, 0x80, 0x20, 0x80, 0x20, 0x80, 0x23, 0x40, 0xE3, 0x3F, 0x00, 0x00, // Code for char j
    0x02, 0x20, 0xFE, 0x3F, 0x00, 0x22, 0x00, 0x01, 0x80, 0x01, 0x40, 0x06, 0x20, 0x38, 0x00, 0x20, // Code for char k
    0x00, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0xFE, 0x3F, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, // Code for char l
    0xC0, 0x3F, 0x20, 0x20, 0x20, 0x00, 0xC0, 0x3F, 0x20, 0x20, 0x20, 0x00, 0xC0, 0x3F, 0x00, 0x20, // Code for char m
    0x20, 0x20, 0xE0, 0x3F, 0x40, 0x20, 0x20, 0x00, 0x20, 0x00, 0x20, 0x20, 0xC0, 0x3F, 0x00, 0x20, // Code for char n
    0x80, 0x0F, 0x40, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40, 0x10, 0x80, 0x0F, 0x00, 0x00, // Code for char o
    0x20, 0x80, 0xE0, 0xFF, 0x20, 0x90, 0x20, 0x90, 0x20, 0x10, 0x40, 0x08, 0x80, 0x07, 0x00, 0x00, // Code for char p
    0x80, 0x07, 0x40, 0x08, 0x20, 0x10, 0x20, 0x90, 0x20, 0x90, 0xE0, 0xFF, 0x20, 0x80, 0x00, 0x00, // Code for char q
    0x20, 0x20, 0x20, 0x20, 0xE0, 0x3F, 0x40, 0x20, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x00, 0x00, 0x00, // Code for char r
    0x00, 0x38, 0xC0, 0x11, 0x20, 0x22, 0x20, 0x22, 0x20, 0x22, 0x40, 0x22, 0xE0, 0x1C, 0x00, 0x00, // Code for char s
    0x20, 0x00, 0x20, 0x00, 0xFC, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x18, 0x00, 0x00, // Code for char t
    0x20, 0x00, 0xE0, 0x1F, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x20, 0x10, 0xE0, 0x1F, 0x00, 0x20, // Code for char u
    0xE0, 0x00, 0x20, 0x07, 0x00, 0x18, 0x00, 0x20, 0x00, 0x18, 0x20, 0x07, 0xE0, 0x00, 0x00, 0x00, // Code for char v
    0xE0, 0x07, 0x00, 0x38, 0x00, 0x06, 0xE0, 0x01, 0x00, 0x06, 0x00, 0x38, 0xE0, 0x07, 0x00, 0x00, // Code for char w
    0x20, 0x20, 0x60, 0x30, 0xA0, 0x2D, 0x00, 0x02, 0xA0, 0x2D, 0x60, 0x30, 0x20, 0x20, 0x00, 0x00, // Code for char x
    0x20, 0x60, 0x60, 0x80, 0xA0, 0x41, 0x00, 0x32, 0x00, 0x0C, 0x20, 0x03, 0xE0, 0x00, 0x20, 0x00, // Code for char y
    0x00, 0x20, 0x60, 0x30, 0x20, 0x28, 0x20, 0x26, 0xA0, 0x21, 0x60, 0x20, 0x20, 0x38, 0x00, 0x00, // Code for char z
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x01, 0x3E, 0x7E, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, // Code for char {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char |
    0x01, 0x80, 0x01, 0x80, 0x3E, 0x7E, 0x40, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char }
    0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, // Code for char ~
};

 const st_standFont_t gst8x16Font = {(uint8_t *) gu8Font_8x16, 8, 16, 16};