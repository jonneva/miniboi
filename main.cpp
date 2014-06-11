#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <algorithm> // needed for min max
#include "Miniboi.h"
#include "Miniboi_emu.h"

Miniboi_emu EMU;

using namespace sf;
using namespace std;

// START OF ARDUINO CODE

Miniboi MB;


void setup() {
    MB.begin();
}

void loop() {
    MB.draw_line(0,0,83,47,1);
    MB.draw_line(0,0,0,47,1);
    MB.draw_line(0,0,83,0,1);
    MB.draw_line(0,2,83,2,1);
}


// END OF ARDUINO CODE

int main()
{
    EMU.start();
    setup();

while (emuWindow.isOpen())
    {
	loop();
	EMU.refresh(&MB.buffer[0]);
    }
	return 0;
}

