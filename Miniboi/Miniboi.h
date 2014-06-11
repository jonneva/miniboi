#ifndef MINIBOI_H
#define MINIBOI_H

#include <stdint.h>
#include <stdlib.h>

#define WHITE   1
#define BLACK   0
#define INVERT  2
#define HATCH   3


class Miniboi {
public:
    uint8_t buffer[504];
	char begin();
	void end();
	void set_pixel(uint8_t,uint8_t,char);
	void draw_line(uint8_t,uint8_t, uint8_t, uint8_t, char);
    void draw_column(uint8_t, uint16_t, uint16_t, uint8_t);
    void draw_row(uint8_t, uint16_t, uint16_t, uint8_t);

private:
    void sp(uint8_t,uint8_t,char);
};

#endif
