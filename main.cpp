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

float x = 0.0f, y = 100.0f, z = -500.0f;

vector<SolidPolygon3D> polys;
ViewWindow view(0, 0, XMAX, YMAX, DegToRad(75));
Transform3D camera(x, y, z);
PolygonRenderer* polygonRenderer ;


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

void plot_pixel(int px, int py, int color) {
        MB.set_pixel(px,py,color);
}

void render()
    {
        polygonRenderer->startFrame();

        for (int i=0; i!=polys.size(); ++i)
        {
            polygonRenderer->draw(&polys[i]);
        }

    }



void setup() {
    MB.begin();
    createPolygons();
    polygonRenderer = new SolidPolygonRenderer(camera, view); //remember to delete
}

void loop() {
    /*MB.draw_line(0,0,83,47,HATCH);
    MB.draw_line(0,0,0,47,HATCH);
    MB.draw_line(0,0,83,0,HATCH);
    MB.draw_line(0,1,83,1,HATCH);
    MB.draw_line(0,2,83,2,HATCH);
    MB.draw_line(0,47,83,47,HATCH);*/
    MB.draw_rect(random(0,83),random(0,47),random(5,60),random(5,40),random(0,2),random(0,6));
    /*MB.draw_rect(0,0,XMAX,YMAX,1,1);
    MB.draw_rect(10,0,6,20,-1,HATCH2);
    MB.draw_rect(20,1,6,16,-1,HATCH);
    MB.draw_rect(30,2,6,18,-1,HATCH2);
    MB.draw_rect(40,3,6,29,-1,HATCH3);
    MB.draw_rect(50,4,6,30,-1,HATCH2);
    MB.draw_rect(60,5,6,41,-1,HATCH2);*/
    //MB.draw_rect(10,0,6,20,-1,HATCH2);
    //render();
    //polygonRenderer->resetCounters();

}


// END OF ARDUINO CODE

int main()
{
    EMU.start();
    setup();
    mb14 test,test2,test3;
    int result=0;
    test = int2mb(2);
    test2 = int2mb(2);
    test3 = mbMul(test,test2);
    result = mb2int(test3);
    test3 = mbDiv(test,test2);
    result = mb2int(test3);



while (emuWindow.isOpen())
    {
	loop();
	EMU.refresh(&MB.buffer[0]);
    }
	return 0;
}

