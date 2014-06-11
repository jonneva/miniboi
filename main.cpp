#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "Miniboi.h"
#include "Miniboi_emu.h"
#include "Miniboi3D.h"

Miniboi_emu EMU;

using namespace sf;
using namespace std;
using namespace Miniboi3D;

// START OF ARDUINO CODE

Miniboi MB;
vector<SolidPolygon3D> polys;


    // Create a house (convex polyhedra)
    // All faces must use anti-clockwise winding order
void createPolygons() {
        SolidPolygon3D poly;

        // walls
        poly = SolidPolygon3D(
            Vector3D(-200, 0, -1000),
            Vector3D(200, 0, -1000),
            Vector3D(200, 250, -1000),
            Vector3D(-200, 250, -1000));
        poly.setColor(1);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(-200, 0, -1400),
            Vector3D(-200, 250, -1400),
            Vector3D(200, 250, -1400),
            Vector3D(200, 0, -1400));
        poly.setColor(1);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(-200, 0, -1400),
            Vector3D(-200, 0, -1000),
            Vector3D(-200, 250, -1000),
            Vector3D(-200, 250, -1400));
        poly.setColor(1);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(200, 0, -1000),
            Vector3D(200, 0, -1400),
            Vector3D(200, 250, -1400),
            Vector3D(200, 250, -1000));
        poly.setColor(1);
        polys.push_back(poly);

        // door and windows
        poly = SolidPolygon3D(
            Vector3D(0, 0, -1000),
            Vector3D(75, 0, -1000),
            Vector3D(75, 125, -1000),
            Vector3D(0, 125, -1000));
        poly.setColor(1);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(-150, 150, -1000),
            Vector3D(-100, 150, -1000),
            Vector3D(-100, 200, -1000),
            Vector3D(-150, 200, -1000));
        poly.setColor(1);
        polys.push_back(poly);

        // roof
        poly = SolidPolygon3D(
            Vector3D(-200, 250, -1000),
            Vector3D(200, 250, -1000),
            Vector3D(75, 400, -1200),
            Vector3D(-75, 400, -1200));
        poly.setColor(1);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(-200, 250, -1400),
            Vector3D(-200, 250, -1000),
            Vector3D(-75, 400, -1200));
        poly.setColor(1);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(200, 250, -1400),
            Vector3D(-200, 250, -1400),
            Vector3D(-75, 400, -1200),
            Vector3D(75, 400, -1200));
        poly.setColor(1);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(200, 250, -1000),
            Vector3D(200, 250, -1400),
            Vector3D(75, 400, -1200));
        poly.setColor(1);
        polys.push_back(poly);
    }

void setup() {
    MB.begin();
}

void loop() {
    /*MB.draw_line(0,0,83,47,HATCH);
    MB.draw_line(0,0,0,47,HATCH);
    MB.draw_line(0,0,83,0,HATCH);
    MB.draw_line(0,1,83,1,HATCH);
    MB.draw_line(0,2,83,2,HATCH);
    MB.draw_line(0,47,83,47,HATCH);*/
    MB.draw_rect(random(0,83),random(0,47),random(0,83),random(0,47),random(0,3),random(0,3));
    /*MB.draw_rect(10,0,5,6,HATCH,1);
    MB.draw_rect(20,0,5,7,HATCH,1);
    MB.draw_rect(30,0,5,8,HATCH,HATCH);
    MB.draw_rect(40,0,5,9,HATCH,HATCH);
    MB.draw_rect(50,0,5,10,HATCH,HATCH);
    MB.draw_rect(60,0,5,11,HATCH,HATCH);*/
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

