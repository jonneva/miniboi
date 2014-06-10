#ifndef MINIBOI_EMU_H
#define MINIBOI_EMU_H

#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <stdlib.h>

#define EMUW    400
#define EMUH    300
#define EMUZ    2.f

using namespace sf;

extern RenderWindow emuWindow;

class Miniboi_emu {
public:
    void start();
    void refresh(uint8_t *);
    int pollFire();
    int pollLeft();
    int pollRight();
    int pollUp();
    int pollDown();

private:
    int pollEsc();

};

#endif
