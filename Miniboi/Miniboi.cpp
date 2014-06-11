#include "Miniboi.h"

char Miniboi::begin() {

	return 1;
} // end of begin

void Miniboi::sp(uint8_t x, uint8_t y, char c) {
    if (c==WHITE) {buffer[(y >> 3) * 84 + x] |= (0x80 >> (y & 7)); return;}
    if (c==HATCH) {
        if ((x+y) & 1) {
                // odd pixels on
                buffer[(y >> 3) * 84 + x] |= (0x80 >> (y & 7));
                } else {
                // even pixels off
                buffer[(y >> 3) * 84 + x] &= ~(0x80 >> (y & 7));
                }
        return;
        }
	buffer[(y >> 3) * 84 + x] &= ~(0x80 >> (y & 7));
}

void Miniboi::set_pixel(uint8_t x, uint8_t y, char c) {
	if (x >= 84 || y >= 48)
		return;
	if (c==WHITE) {buffer[(y >> 3) * 84 + x] |= (0x80 >> (y & 7)); return;}
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

void Miniboi::draw_row(uint8_t y, uint16_t x0, uint16_t x1, uint8_t c) {
	uint8_t hbit;

    if (x0 > x1) {
			hbit = x0;
			x0 = x1;
			x1 = hbit;
		} // swap the xs correct way round

	if (x0 == x1)
		sp(x0,y,c);
	else {

	hbit = 0x80 >> (y&7); //find the bit to be set in that byte
                          // remainder = number & ( divisor - 1 )

    x0 = (y>>3)*84 + x0 ;         // x0 now points to first buffer byte
    x1 = (y>>3)*84 + x1 ;         // x1 now points to last buffer byte

    // Drawing loops

    if (c == WHITE) {
			while (x0 < x1)
				buffer[x0++] |= hbit;
		}
		else if (c == BLACK) {
			while (x0 < x1)
				buffer[x0++] &= ~hbit;
		}
		else if (c == INVERT) {
			while (x0 < x1)
				buffer[x0++] ^= hbit;
		}
		else if (c == HATCH) {
			while (x0 < x1)
				if ((y+x0)&1) {
                    // odd bits set
                    buffer[x0++] |= hbit;
				} else {
                    // even bits turn off
                    buffer[x0++] &= ~hbit;
				}
		}
	}
} // end of draw_row

void Miniboi::draw_column(uint8_t x, uint16_t y0, uint16_t y1, uint8_t c) {

	unsigned char topbits, bottombits, hatchbit,topmask,bottommask;

    if (y0 > y1) {
			topbits = y0;
			y0 = y1;
			y1 = topbits;
		} // swap the ys correct way round

    if (y0 == y1)
		sp(x,y0,c); // draw pixel if length = 1

    if (c == HATCH) {
        if (x&1) {
            // odd columns
            topmask = 0xFF >> (y0&7); // mask for top byte
            topbits = 0xAA >> (y0&7); // hatch for top byte
            bottommask = 0xFF << (7-(y1&7)); // mask for bottom byte
            bottombits = 0xAA << (7-(y1&7)); // mask for bottom byte
            hatchbit = 0xAA;
        } else {
            // even columns
            topmask = 0xFF >> (y0&7); // mask for top byte
            topbits = 0x55 >> (y0&7); // hatch for top byte
            bottommask = 0xFF << (7-(y1&7)); // mask for bottom byte
            bottombits = 0x55 << (7-(y1&7)); // mask for bottom byte
            hatchbit = 0x55;
        }
    } else {
        topbits = 0xff >> (y0&7); // mask for top byte
        bottombits = ~(0xff >> (y1&7)); // mask for bottom byte
    }
    y0 = (y0>>3)*84 + x; // y0 now points to topmost byte
    y1 = (y1>>3)*84 + x; // y1 now points to last bottom byte

    // Drawing loop

    if (c == WHITE) {
            buffer[y0] |= topbits; // topmost byte
			while ( y0 < y1) {
                y0 += 84;           // increment, if several bytes
				buffer[y0] = 0xFF; // its a whole byte
			}
			buffer[y0] |= bottombits; // last byte
		}
		else if (c == BLACK) {
            buffer[y0] &= ~topbits; // topmost byte
            while ( y0 < y1) {
                y0 += 84;           // increment, if several bytes
				buffer[y0] = 0x00; // its a whole byte
			}
			buffer[y0] &= ~bottombits; // last byte
		}
		else if (c == INVERT) {
            buffer[y0] ^= topbits; // topmost byte
            while ( y0 < y1) {
                y0 += 84;           // increment, if several bytes
				buffer[y0] ^= 0xFF; // its a whole byte
			}
			buffer[y0] ^= bottombits; // last byte
		}
        else if (c == HATCH) {
            buffer[y0] &= ~topmask; // switch off affected bytes
            buffer[y0] |= topbits; // topmost byte
            while ( y0 < y1) {
                y0 += 84;           // increment, if several bytes
				buffer[y0] = hatchbit; // its a whole byte
			}
			buffer[y0] &= bottommask; // switch off affected bytes
			buffer[y0] |= bottombits; // last byte
		}
}
