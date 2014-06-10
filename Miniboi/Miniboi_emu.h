#ifndef MINIBOI_EMU_H
#define MINIBOI_EMU_H

#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <stdlib.h>
#include "binary.h"

#define EMUW    400
#define EMUH    300
#define EMUZ    1.f

// ARDUINO COMPATIBILITY
typedef unsigned char byte;
typedef unsigned char prog_char;
typedef bool boolean;
#define PI 3.14159265

using namespace sf;

extern RenderWindow emuWindow;

class Miniboi_emu {
public:
    void start();
    void refresh(uint8_t *);
    void refresh_old(uint8_t *);
    int pollA();
    int pollB();
    int pollC();
    int pollLeft();
    int pollRight();
    int pollUp();
    int pollDown();

private:
    int pollEsc();

};

#endif
