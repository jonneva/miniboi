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
point2D quad[4];


void createPolygons() {
        SolidPolygon3D poly;

        // walls
        poly = SolidPolygon3D(
            Vector3D(-200, 0, -1000),
            Vector3D(200, 0, -1000),
            Vector3D(200, 250, -1000),
            Vector3D(-200, 250, -1000));
        poly.setColor(HATCH);
        polys.push_back(poly);
                polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(-200, 0, -1400),
            Vector3D(-200, 250, -1400),
            Vector3D(200, 250, -1400),
            Vector3D(200, 0, -1400));
        poly.setColor(2);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(-200, 0, -1400),
            Vector3D(-200, 0, -1000),
            Vector3D(-200, 250, -1000),
            Vector3D(-200, 250, -1400));
        poly.setColor(2);
        polys.push_back(poly);
        poly = SolidPolygon3D(
            Vector3D(200, 0, -1000),
            Vector3D(200, 0, -1400),
            Vector3D(200, 250, -1400),
            Vector3D(200, 250, -1000));
        poly.setColor(2);
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


void render() {
for (int i=0; i!=polys.size(); ++i) polygonRenderer->draw(&polys[i]);
}


void setup() {
    MB.begin();
    createPolygons();
    polygonRenderer = new SolidPolygonRenderer(camera, view); //remember to delete

}

void loop() {
    float distanceChange = 50.0 * 1; //was 500
    float angleChange = 0.1 * 1;
    MB.fill(0);
    //MB.draw_poly(3,&quad[0],random(1,2),random(0,6));
    //MB.draw_poly(3,&quad[0],0,0);
    //polygonRenderer->draw(&polys[0]);
    render();

  if (EMU.pollA())
  {
    polygonRenderer->getCamera().getLocation().y -= distanceChange;
  }
  if (EMU.pollB())
  {
    polygonRenderer->getCamera().getLocation().y += distanceChange;
  }
  if (EMU.pollDown())
  {
    polygonRenderer->getCamera().getLocation().x -= distanceChange * polygonRenderer->getCamera().getSinAngleY();
    polygonRenderer->getCamera().getLocation().z -= distanceChange * polygonRenderer->getCamera().getCosAngleY();
  }
  if (EMU.pollUp())
  {
    polygonRenderer->getCamera().getLocation().x += distanceChange * polygonRenderer->getCamera().getSinAngleY();
    polygonRenderer->getCamera().getLocation().z += distanceChange * polygonRenderer->getCamera().getCosAngleY();
  }
  if (EMU.pollLeft())
  {
    polygonRenderer->getCamera().rotateAngleY(angleChange);
  }
  if (EMU.pollRight())
  {
    polygonRenderer->getCamera().rotateAngleY(-angleChange);
  }

    MB.delay(100);
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

