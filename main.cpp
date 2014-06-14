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

//float x = 0.0f, y = 100.0f, z = -500.0f;
float x = 0.0f, y = 100.0f, z = 500.0f;


vector<SolidPolygon3D> polys;
ViewWindow view(0, 0, XMAX, YMAX, DegToRad(75));
Transform3D camera(x, y, z);
Transform3D away(0, 0, 0.0f);
Transform3D turntable();
PolygonRenderer* polygonRenderer ;
point2D quad[4];


void createPolygons() {

        SolidPolygon3D poly;

        //cube, front face
        poly = SolidPolygon3D(
            Vector3D(-200, -200, 200),
            Vector3D(200, -200, 200),
            Vector3D(200, 200, 200),
            Vector3D(-200, 200, 200));
        poly.setFillColor(HATCH);
        polys.push_back(poly);
        // back face
        poly = SolidPolygon3D(
            Vector3D(-200, 200, -200),
            Vector3D(200, 200, -200),
            Vector3D(200, -200, -200),
            Vector3D(-200, -200, -200));
        poly.setFillColor(1);
        polys.push_back(poly);
        // bottom face
        poly = SolidPolygon3D(
            Vector3D(-200, -200, -200),
            Vector3D(200, -200, -200),
            Vector3D(200, -200, 200),
            Vector3D(-200, -200, 200));
        poly.setFillColor(1);
        polys.push_back(poly);
        // top face
        poly = SolidPolygon3D(
            Vector3D(-200, 200, -200),
            Vector3D(-200, 200, 200),
            Vector3D(200, 200, 200),
            Vector3D(200, 200, -200));
        poly.setFillColor(1);
        polys.push_back(poly);
        // right face
        poly = SolidPolygon3D(
            Vector3D(200, 200, 200),
            Vector3D(200, -200, 200),
            Vector3D(200, -200, -200),
            Vector3D(200, 200, -200));
        poly.setFillColor(1);
        polys.push_back(poly);
}


void render() {
for (int i=0; i!=polys.size(); ++i)
{
polygonRenderer->draw(&polys[i]);
//polys[i].add(away);
polys[i].addRotation(away);
}
}


void setup() {
    MB.begin();
    createPolygons();
    polygonRenderer = new SolidPolygonRenderer(camera, view); //remember to delete
    away.rotateAngle(0.00f,0.01f,0.01f);
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
  if (EMU.pollUp())
  {
    polygonRenderer->getCamera().getLocation().x -= distanceChange * polygonRenderer->getCamera().getSinAngleY();
    polygonRenderer->getCamera().getLocation().z -= distanceChange * polygonRenderer->getCamera().getCosAngleY();
  }
  if (EMU.pollDown())
  {
    polygonRenderer->getCamera().getLocation().x += distanceChange * polygonRenderer->getCamera().getSinAngleY();
    polygonRenderer->getCamera().getLocation().z += distanceChange * polygonRenderer->getCamera().getCosAngleY();
  }
  if (EMU.pollLeft())
  {
    if (EMU.pollC()) {
    polygonRenderer->getCamera().getLocation().x -= distanceChange;
    } else {
    polygonRenderer->getCamera().rotateAngleY(angleChange);
    }
  }
  if (EMU.pollRight())
  {
    if (EMU.pollC()) {
    polygonRenderer->getCamera().getLocation().x += distanceChange;
    } else {
    polygonRenderer->getCamera().rotateAngleY(-angleChange);
    }
  }

    //MB.delay(1);
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

