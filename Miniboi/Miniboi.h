#ifndef MINIBOI_H
#define MINIBOI_H

#include <stdint.h>
#include <stdlib.h>

#define WHITE   1
#define BLACK   0
#define HATCH   2
#define HATCH2  3
#define INVERT  4

#define XMAX    83
#define YMAX    47



class Miniboi {
public:
    uint8_t buffer[504];
	char begin();
	void end();
	void set_pixel(uint8_t,uint8_t,char);
	void draw_line(uint8_t,uint8_t, uint8_t, uint8_t, char);
    void draw_column(uint8_t, uint16_t, uint16_t, uint8_t);
    void draw_row(uint8_t, uint16_t, uint16_t, uint8_t);
    void draw_rect(uint8_t,uint8_t,uint8_t,uint8_t,char,char);

private:
    void sp(uint8_t,uint8_t,char);
};

#endif
