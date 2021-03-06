#include "sky.h"

unsigned char porsche_tiny[]= {
10,6,
0x1E,0x00,
0x21,0x00,
0x7F,0x80,
0x40,0x80,
0x73,0x80,
0x40,0x80
};

unsigned char porsche_tiny_alpha[]= {
10,6,
0x3F,0x00,
0x7F,0x80,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0
};

unsigned char porsche_small[]= {
15,11,
0x00,0x00,
0x0F,0xE0,
0x10,0x10,
0x7F,0xFC,
0x20,0x08,
0x7F,0xFC,
0x40,0x04,
0x77,0xDC,
0x68,0x2C,
0x48,0x24,
0x00,0x00
};

unsigned char porsche_small_alpha[]= {
15,11,
0x0F,0xE0,
0x1F,0xF0,
0x7F,0xFC,
0xFF,0xFE,
0xFF,0xFE,
0xFF,0xFE,
0xFF,0xFE,
0xFF,0xFE,
0xFF,0xFE,
0xFF,0xFE,
0xE0,0x0E
};

unsigned char porsche_med[] = {
21,14,
0x00,0x00,0x00, // was 0x00,0x00,0x00,
0x07,0xFF,0x80,
0x0C,0x00,0xC0,
0x7F,0xFF,0xF8,
0x70,0x00,0x38,
0x3B,0xFF,0x70,
0x7F,0xFF,0xF8,
0x40,0x00,0x08,
0x73,0xFF,0x38,
0x7F,0xFF,0xF8,
0x7A,0x01,0x78,
0x72,0x01,0x38,
0x40,0x00,0x08,
0x50,0x00,0x28
};

unsigned char porsche_med_alpha[] = {
21,14,
0x07,0xFF,0x80, // was 0x07,0xFF,0x80,
0x0F,0xFF,0xC0,
0x7F,0xFF,0xF8,
0xFF,0xFF,0xFC,
0xFF,0xFF,0xFC,
0x7F,0xFF,0xF8,
0xFF,0xFF,0xFC,
0xFF,0xFF,0xFC,
0xFF,0xFF,0xFC,
0xFF,0xFF,0xFC,
0xFF,0xFF,0xFC,
0xFF,0xFF,0xFC,
0xFF,0xFF,0xFC,
0xF8,0x00,0x7C
};


unsigned char test[] = {
10,10,
0x00,0x00,
0x00,0x00,
0x00,0x00,
0x00,0x00,
0x00,0x00,
0x00,0x00,
0x00,0x00,
0x00,0x00,
0x00,0x00,
0x00,0x00
};

unsigned char test_alpha[] = {
10,10,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0,
0xFF,0xC0
};

unsigned char palm_tiny[] = {
8,8,
0x00,
0x00,
0x00,
0x30,
0x70,
0x20,
0x20,
0x20
};

unsigned char palm_tiny_alpha[] = {
8,8,
0x00,
0x00,
0x00,
0x78,
0x78,
0x78,
0x70,
0x70
};

unsigned char palm_small[] = {
8,11,
0x00,
0x14,
0x3E,
0x58,
0x3C,
0x56,
0x10,
0x10,
0x10,
0x10,
0x18
};

unsigned char palm_small_alpha[] = {
8,11,
0x14,
0x3E,
0x7F,
0xFE,
0x7E,
0xFF,
0x7F,
0x38,
0x38,
0x38,
0x3C
};

unsigned char palm[] = {
10,16,
0x00,0x00,
0x13,0x80,
0x34,0x00,
0x7F,0x00,
0x1C,0x80,
0x3A,0x00,
0x5D,0x00,
0x52,0x00,
0x11,0x00,
0x10,0x00,
0x30,0x00,
0x30,0x00,
0x30,0x00,
0x10,0x00,
0x18,0x00,
0x18,0x00
};

unsigned char palm_alpha[] = {
10,16,
0x1f,0x00, // was 0x1F,0x00,
0x3C,0x00,
0x7F,0x40,
0xFF,0x80,
0xFF,0xC0,
0x7F,0xC0,
0xFF,0x80,
0xFF,0x00,
0x7B,0x80,
0x39,0x80,
0x78,0x00,
0x78,0x00,
0x78,0x00,
0x38,0x00,
0x3C,0x00,
0x3C,0x00,
};

unsigned char palm_big[] = {
15,24,
0x00,0x00,
0x00,0x38,
0x1C,0x7C,
0x3E,0xC0,
0x77,0xE0,
0x4F,0x70,
0x07,0x88,
0x1D,0x48,
0x3A,0x60,
0x67,0xB0,
0x66,0xC0,
0x2C,0x60,
0x0C,0x30,
0x0C,0x00,
0x0C,0x00,
0x1C,0x00,
0x1C,0x00,
0x1C,0x00,
0x1C,0x00,
0x0C,0x00,
0x0C,0x00,
0x0E,0x00,
0x0F,0x00,
0x07,0x00
};

unsigned char palm_big_alpha[] = {
15,24,
0x00,0x38,
0x1C,0x7C,
0x3E,0xFE,
0x7F,0xFE,
0xFF,0xF0,
0xFF,0xF8,
0x7F,0xFC,
0x3F,0xFC,
0x7F,0xF8,
0xFF,0xF8,
0xFF,0xF0,
0xFE,0xF0,
0x7E,0x78,
0x1E,0x30,
0x1E,0x00,
0x3E,0x00,
0x3E,0x00,
0x3E,0x00,
0x3E,0x00,
0x1E,0x00,
0x1E,0x00,
0x1F,0x00,
0x1F,0x80,
0x0F,0x80
};



unsigned char sky[] = {
104,15,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0xE0,0x3E,0x00,0x00,0x00,0x00,0x60,0x00,
0x00,0x00,0x00,0x00,0x1F,0xFC,0x77,0x00,0x00,0x00,0x00,0xF9,0x80,
0x00,0x00,0x00,0x00,0x37,0xFF,0xFF,0x80,0x00,0x00,0x01,0xFF,0xE0,
0x00,0x03,0x00,0x04,0x2B,0xFF,0xD7,0xE0,0x00,0x00,0x0A,0xBF,0xF0,
0x00,0xCF,0xE0,0x1F,0x77,0xFF,0xFF,0xFC,0x00,0x00,0x1F,0xFF,0xE8,
0x01,0xF7,0xE8,0x00,0x00,0x00,0x00,0x00,0x00,0xC1,0xEE,0xFF,0xF4,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF7,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x0F,0x81,0xFF,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0xFF,0xE7,0xFF,0xFD,0xC1,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
