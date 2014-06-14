#ifndef MINIBOI_H
#define MINIBOI_H

#include <stdint.h>
#include <stdlib.h>
#include "Miniboi_math.h" // needed for polygon filling

//#define MINIBOI_TRIG // if fixed point trigonometric needed

#define WHITE   1
#define BLACK   0
#define HATCH   2
#define HATCH2  3
#define HATCH3  4
#define INVERT  5

#define HATCH1EVEN  0xAA
#define HATCH1ODD   0x55
#define HATCH2EVEN  0x88
#define HATCH2ODD   0x22
#define HATCH3EVEN  0xDD
#define HATCH3ODD   0x77

#define XMAX    83
#define YMAX    47

typedef struct
{
    mb14 x, y;
} point2D;

#define clear_screen()	fill(0)

class Miniboi {
public:
    uint8_t buffer[504]; // Teh screen buffer
    uint8_t edgeTable1[84]; // edge tables for polygon filling
    uint8_t edgeTable2[84]; // ToDo: make optional if not needed
	char begin();
	void fill(uint8_t);
	unsigned long millis();
	void delay(unsigned int);
	void set_pixel(uint8_t,uint8_t,char);
	void draw_line(uint8_t,uint8_t, uint8_t, uint8_t, char);
    void draw_column(uint8_t, uint16_t, uint16_t, uint8_t);
    void draw_row(uint8_t, uint16_t, uint16_t, uint8_t);
    void draw_rect(uint8_t,uint8_t,uint8_t,uint8_t,char,char);
    void draw_poly(uint8_t, point2D*, char, char);

private:
    void sp(uint8_t,uint8_t,char);
    int  round2Scanline(mb14);
    void walkEdge(uint8_t *, point2D *, point2D *);
};

extern Miniboi MB; // to make life a bit easier in testing

#endif
