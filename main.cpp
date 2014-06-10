#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include "Miniboi.h"
#include "Miniboi_emu.h"

Miniboi_emu EMU;

using namespace sf;

// START OF ARDUINO CODE

Miniboi MB;
uint8_t testscr[48*84/8]; //is 504


void setup() {
    MB.begin();
}

void loop() {

}


// END OF ARDUINO CODE

int main()
{
    memset(testscr,0xAA,504);
    EMU.start();
    setup();

while (emuWindow.isOpen())
    {
	loop();
	EMU.refresh(&testscr[0]);
    }
	return 0;
}

