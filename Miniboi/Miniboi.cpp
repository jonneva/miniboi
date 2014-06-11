#include "Miniboi.h"

char Miniboi::begin() {

	return 1;
} // end of begin

void Miniboi::sp(uint8_t x, uint8_t y, char c) {
    if (c) {buffer[(y >> 3) * 84 + x] |= (0x80 >> (y & 7)); return;}
	buffer[(y >> 3) * 84 + x] &= ~(0x80 >> (y & 7));
}

void Miniboi::set_pixel(uint8_t x, uint8_t y, char c) {
	if (x >= 84 || y >= 48)
		return;
	if (c) {buffer[(y >> 3) * 84 + x] |= (0x80 >> (y & 7)); return;}
	buffer[(y >> 3) * 84 + x] &= ~(0x80 >> (y & 7));
}// end of set_pixel

void Miniboi::draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char c) {

	if (x0 > 84 || y0 > 48 || x1 > 84 || y1 > 48)
		return;
	if (x0 == x1)
		draw_column(x0,y0,y1,c);
	else if (y0 == y1)
		draw_row(y0,x0,x1,c);
	else {
		int e;
		signed int dx,dy,j, temp;
		signed char s1,s2, xchange;
		signed int x,y;

		x = x0;
		y = y0;

		//take absolute value
		if (x1 < x0) {
			dx = x0 - x1;
			s1 = -1;
		}
		else if (x1 == x0) {
			dx = 0;
			s1 = 0;
		}
		else {
			dx = x1 - x0;
			s1 = 1;
		}

		if (y1 < y0) {
			dy = y0 - y1;
			s2 = -1;
		}
		else if (y1 == y0) {
			dy = 0;
			s2 = 0;
		}
		else {
			dy = y1 - y0;
			s2 = 1;
		}

		xchange = 0;

		if (dy>dx) {
			temp = dx;
			dx = dy;
			dy = temp;
			xchange = 1;
		}

		e = ((int)dy<<1) - dx;

		for (j=0; j<=dx; j++) {
			sp(x,y,c);

			if (e>=0) {
				if (xchange==1) x = x + s1;
				else y = y + s2;
				e = e - ((int)dx<<1);
			}
			if (xchange==1)
				y = y + s2;
			else
				x = x + s1;
			e = e + ((int)dy<<1);
		}
	}
}

void Miniboi::draw_row(uint8_t line, uint16_t x0, uint16_t x1, uint8_t c) {
	uint8_t lbit, rbit;

	if (x0 == x1)
		set_pixel(x0,line,c);
	else {
		if (x0 > x1) {
			lbit = x0;
			x0 = x1;
			x1 = lbit;
		}
		lbit = 0xff >> (x0&7);
		x0 = x0/8 + 84*line;
		rbit = ~(0xff >> (x1&7));
		x1 = x1/8 + 84*line;
		if (x0 == x1) {
			lbit = lbit & rbit;
			rbit = 0;
		}
		if (c == WHITE) {
			buffer[x0++] |= lbit;
			while (x0 < x1)
				buffer[x0++] = 0xff;
			buffer[x0] |= rbit;
		}
		else if (c == BLACK) {
			buffer[x0++] &= ~lbit;
			while (x0 < x1)
				buffer[x0++] = 0;
			buffer[x0] &= ~rbit;
		}
		else if (c == INVERT) {
			buffer[x0++] ^= lbit;
			while (x0 < x1)
				buffer[x0++] ^= 0xff;
			buffer[x0] ^= rbit;
		}
	}
} // end of draw_row

void Miniboi::draw_column(uint8_t row, uint16_t y0, uint16_t y1, uint8_t c) {

	unsigned char bit;
	int byte;

	if (y0 == y1)
		set_pixel(row,y0,c);
	else {
		if (y1 < y0) {
			bit = y0;
			y0 = y1;
			y1 = bit;
		}
		bit = 0x80 >> (row&7);
		byte = row/8 + y0*48;
		if (c == WHITE) {
			while ( y0 <= y1) {
				buffer[byte] |= bit;
				byte += 84;
				y0++;
			}
		}
		else if (c == BLACK) {
			while ( y0 <= y1) {
				buffer[byte] &= ~bit;
				byte += 84;
				y0++;
			}
		}
		else if (c == INVERT) {
			while ( y0 <= y1) {
				buffer[byte] ^= bit;
				byte += 84;
				y0++;
			}
		}
	}
}
