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

#define FRAME_RATE 41

#define PIN_SCE   A1
#define PIN_RESET A0
#define PIN_DC    A2
#define PIN_SDIN  11
#define PIN_SCLK  13
#define PIN_BACKLIGHT 5

#define BTN_UP_PIN      9
#define BTN_RIGHT_PIN   7
#define BTN_DOWN_PIN    6
#define BTN_LEFT_PIN    8
#define BTN_A_PIN       4
#define BTN_B_PIN       2
#define BTN_C_PIN       A3

#define PORT_SCLK PORTB
#define SCLK_BIT 5
#define PORT_SDIN PORTB
#define SDIN_BIT 3

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48
#define LCD_CMD   0

#define FOV  30
#define NEAR_PLANE (0.5/tan(PI*FOV/180))
#define CLIP_PLANE 0.01f
#define CAMERA_SCALE 50
#define WALL_HEIGHT 0.8f
#define OBJECT_SIZE 0.8f

void drawWall(float, float, float, float);
void drawMonster(float, float);

volatile boolean frameReady = false;
byte buffer[LCD_X*LCD_Y/8];
float wbuffer[LCD_X];
int numColumns;

#define MAP_SIZE 16
const char theMap[MAP_SIZE*MAP_SIZE+1] =
{
  "################"
  "#.#............#"
  "#.#..#.........#"
  "#.#..#.........#"
  "#....#....#....#"
  "##.#.#.........#"
  "######.........#"
  "#..............#"
  "##########..####"
  "#........#.....#"
  "#.....#..#..#..#"
  "#.....#.....#..#"
  "#.....##########"
  "#..............#"
  "#.#.#.#.#......#"
  "################"
};

#define SWAP(A, B) B, A,

// raw data for the monster sprite
const byte sprite[] =
{
  SWAP(B00000000, B00000000)
  SWAP(B11111111, B11111000)
  SWAP(B01000000, B00001100)
  SWAP(B00101000, B00000110)
  SWAP(B01001100, B00000010)
  SWAP(B10000110, B01110011)
  SWAP(B01000010, B10001001)
  SWAP(B00100010, B10101001)
  SWAP(B01000010, B10001001)
  SWAP(B10000110, B01110011)
  SWAP(B01001100, B00000010)
  SWAP(B00101000, B00000110)
  SWAP(B01000000, B00001100)
  SWAP(B11111111, B11111000)
  SWAP(B00000000, B00000000)
  SWAP(B00000000, B00000000)
};

// the mask for the monster sprite indicating which pixels should be drawn
const byte mask[] =
{
  SWAP(B00000000, B00000000)
  SWAP(B11111111, B11111000)
  SWAP(B01111111, B11111100)
  SWAP(B00111111, B11111110)
  SWAP(B01111111, B11111110)
  SWAP(B11111111, B11111111)
  SWAP(B01111111, B11111111)
  SWAP(B00111111, B11111111)
  SWAP(B01111111, B11111111)
  SWAP(B11111111, B11111111)
  SWAP(B01111111, B11111110)
  SWAP(B00111111, B11111110)
  SWAP(B01111111, B11111100)
  SWAP(B11111111, B11111000)
  SWAP(B00000000, B00000000)
  SWAP(B00000000, B00000000)
};

float xpos = 1.5f;
float zpos = 1.5f;
int xcell = 1;
int zcell = 1;
float dir = 0.0f;
float cos_dir;
float sin_dir;

#define MOVEMENT 0.1f
#define TURN 0.1f

void loop2(void) {
  boolean strafe = EMU.pollB(); //should poll A button
  float movement = MOVEMENT;
  float turn = TURN;
  if (EMU.pollB())
  {
    movement *= 2.0f;
    turn *= 2.0f;
  }

  if (EMU.pollDown())
  {
    xpos -= movement * sin_dir;
    zpos -= movement * cos_dir;
  }

  if (EMU.pollUp())
  {
    xpos += movement * sin_dir;
    zpos += movement * cos_dir;
  }

  if (EMU.pollLeft())
  {
    if (strafe)
    {
      xpos -= movement * cos_dir;
      zpos += movement * sin_dir;
    }
    else
      dir -= turn;
  }

  if (EMU.pollRight())
  {
    if (strafe)
    {
      xpos += movement * cos_dir;
      zpos -= movement * sin_dir;
    }
    else
      dir += turn;
  }

  xpos = fmax(xpos, 0);
  zpos = fmax(zpos, 0);
  xpos = fmin(xpos, MAP_SIZE);
  zpos = fmin(zpos, MAP_SIZE);
}

boolean isValid(int cellX, int cellZ)
{
  if (cellX < 0)
    return false;
  if (cellX >= MAP_SIZE)
    return false;
  if (cellZ < 0)
    return false;
  if (cellZ >= MAP_SIZE)
    return false;
  return true;
}

boolean isBlocked(int cellX, int cellZ)
{
  return theMap[cellZ * MAP_SIZE + cellX] == '#';
}

void initWBuffer()
{
  for (int i=0; i<LCD_X; i++)
    wbuffer[i] = 0.0f;
  numColumns = 0;
}


void drawFloorAndCeiling()
{
  memset(buffer, 0xff, 3*84);
  for (int y=3, ofs=3*84; y<6; y++) // y=3 originally, ofs = 3*84
    for (int x=0; x<84; x+=2) // x<84 originally
    {
      buffer[ofs++] = 0x55;
      buffer[ofs++] = 0xaa;
    }
}




void drawCell(int cellX, int cellZ)
{
  if (!isValid(cellX, cellZ))
    return;
  if (!isBlocked(cellX, cellZ))
    return;
  if (zpos < cellZ)
  {
    if (xpos > cellX)
    {
      // north west quadrant
      if ((zpos < cellZ) && !isBlocked(cellX, cellZ-1))
        drawWall(cellX, cellZ, cellX+1, cellZ);  // south wall
      if ((xpos > cellX+1) && (!isBlocked(cellX+1, cellZ)))
        drawWall(cellX+1, cellZ, cellX+1, cellZ+1);  // east wall
    }
    else
    {
      // north east quadrant
      if ((zpos < cellZ) && !isBlocked(cellX, cellZ-1))
        drawWall(cellX, cellZ, cellX+1, cellZ);  // south wall
      if ((xpos< cellX) && !isBlocked(cellX-1, cellZ))
        drawWall(cellX, cellZ+1, cellX, cellZ);  // west wall
    }
  }
  else
  {
    if (xpos > cellX)
    {
      // south west quadrant
      if ((zpos > cellZ+1) && !isBlocked(cellX, cellZ+1))
        drawWall(cellX+1, cellZ+1, cellX, cellZ+1);  // north wall
      if ((xpos > cellX+1) && !isBlocked(cellX+1, cellZ))
        drawWall(cellX+1, cellZ, cellX+1, cellZ+1);  // east wall
    }
    else
    {
      // south east quadrant
      if ((zpos > cellZ+1) && !isBlocked(cellX, cellZ+1))
        drawWall(cellX+1, cellZ+1, cellX, cellZ+1);  // north wall
      if ((xpos< cellX) && !isBlocked(cellX-1, cellZ))
        drawWall(cellX, cellZ+1, cellX, cellZ);  // west wall
    }
  }
}

void drawLayer(int layer)
{
  drawCell(xcell, zcell-layer);
  drawCell(xcell, zcell+layer);
  drawCell(xcell-layer, zcell);
  drawCell(xcell+layer, zcell);
  for (int i=1; i<layer; i++)
  {
    drawCell(xcell-i, zcell+layer);
    drawCell(xcell+i, zcell-layer);
    drawCell(xcell-layer, zcell-i);
    drawCell(xcell+layer, zcell+i);
  }
  for (int i=1; (i<layer) && (numColumns<LCD_X); i++)
  {
    drawCell(xcell+i, zcell+layer);
    drawCell(xcell-i, zcell-layer);
    drawCell(xcell-layer, zcell+i);
    drawCell(xcell+layer, zcell-i);
  }
  drawCell(xcell-layer, zcell+layer);
  drawCell(xcell+layer, zcell+layer);
  drawCell(xcell-layer, zcell-layer);
  drawCell(xcell+layer, zcell-layer);
}

void drawFrame()
{
  cos_dir = cos(dir);
  sin_dir = sin(dir);
  xcell = floor(xpos);
  zcell = floor(zpos);
  initWBuffer();
  drawFloorAndCeiling();
  for (int layer=1; (layer<MAP_SIZE) && (numColumns<LCD_X); layer++)
    drawLayer(layer);
  drawMonster(3.5f, 1.5f);
}





inline void setPixel(int x, int y)
{
  //buffer[(y >> 3) * 84 + x] |= (0x80 >> (y & 7));
  buffer[(y >> 3) * 84 + x] |= (0x80 >> (y & 7));
}

inline void clearPixel(int x, int y)
{
  //buffer[(y >> 3) * 84 + x] &= ~(0x80 >> (y & 7));
  buffer[(y >> 3) * 84 + x] &= ~(0x80 >> (y & 7));
}

// draws one side of a cell
void drawWall(float _x1, float _z1, float _x2, float _z2)
{
  // find position of wall edges relative to eye
  float x1 = cos_dir * (_x1-xpos) - sin_dir * (_z1-zpos);
  float z1 = sin_dir * (_x1-xpos) + cos_dir * (_z1-zpos);
  float x2 = cos_dir * (_x2-xpos) - sin_dir * (_z2-zpos);
  float z2 = sin_dir * (_x2-xpos) + cos_dir * (_z2-zpos);

  // clip to the front pane
  if ((z1<CLIP_PLANE) && (z2<CLIP_PLANE))
    return;
  if (z1 < CLIP_PLANE)
  {
    x1 += (CLIP_PLANE-z1) * (x2-x1) / (z2-z1);
    z1 = CLIP_PLANE;
  }
  else if (z2 < CLIP_PLANE)
  {
    x2 += (CLIP_PLANE-z2) * (x1-x2) / (z1-z2);
    z2 = CLIP_PLANE;
  }

  // apply perspective projection
  float vx1 = x1 * NEAR_PLANE * CAMERA_SCALE / z1;
  float vx2 = x2 * NEAR_PLANE * CAMERA_SCALE / z2;

  // transform the end points into screen space
  int sx1 = (int)ceil((LCD_X / 2) + vx1);
  int sx2 = (int)ceil((LCD_X / 2) + vx2) - 1;

  // clamp to the visible portion of the screen
  int firstx = max(sx1, 0);
  int lastx = min(sx2, LCD_X-1);
  if (lastx < firstx)
    return;

  // loop across each column
  float w1 = 1.0f / z1;
  float w2 = 1.0f / z2;
  float delta_w = (w2 - w1) / (sx2-sx1);
  float w = w1 + (firstx - sx1) * delta_w;
  for (int x=firstx; x<=lastx; x++, w+=delta_w)
  {
    if (w > wbuffer[x])
    {
      wbuffer[x] = w;
      numColumns++;

      // calculate top and bottom
      float vy = (WALL_HEIGHT / 2.0) * NEAR_PLANE * CAMERA_SCALE * w;
      int sy1 = (int)ceil(LCD_Y / 2 - vy);
      int sy2 = (int)ceil(LCD_Y / 2 + vy) - 1;

      // clamp to the visible portion of the screen
      int firsty = max(sy1, 0);
      int lasty = min(sy2, LCD_Y-1);

      // draw this column
      if ((x==sx1) || (x==sx2))
        for (int y=firsty; y<=lasty; y++)
          setPixel(x, y);
        else
          for (int y=firsty; y<=lasty; y++)
            clearPixel(x, y);
      if (sy1 >= 0)
        setPixel(x, sy1);
      if (sy2 < LCD_Y)
        setPixel(x, sy2);
    }
  }
}

// I have done a little bit of optimization here, namely the use of 4:12 fixed-point arithmetic.
void drawMonster(float _x, float _z)
{
  // find position relative to eye
  float x = cos_dir * (_x-xpos) - sin_dir * (_z-zpos);
  float z = sin_dir * (_x-xpos) + cos_dir * (_z-zpos);

  // make sure it's in front of us
  if (z < CLIP_PLANE)
    return;
  float w = 1.0f / z;

  // project the mid-point onto the screen
  float midx = x * NEAR_PLANE * CAMERA_SCALE * w;
  float screen_size = 0.5f * OBJECT_SIZE * CAMERA_SCALE * w;
  int sx1 = (int)ceil(LCD_X / 2 + midx - screen_size);
  int sx2 = (int)ceil(LCD_X / 2 + midx + screen_size) - 1;
  int sy1 = (int)ceil(LCD_Y / 2 - screen_size);
  int sy2 = (int)ceil(LCD_Y / 2 + screen_size) - 1;

  int firstx = max(sx1, 0);
  int lastx = min(sx2, LCD_X-1);
  if (firstx > lastx)
    return;
  int firsty = max(sy1, 0);
  int lasty = min(sy2, LCD_Y-1);

  unsigned deltax = 0x10000 / (sx2-sx1+1);
  unsigned deltay = 0x10000 / (sy2-sy1+1);
  unsigned first_srcy = 0x10000 * (firsty-sy1) / (sy2-sy1+1);
  unsigned srcx = 0x10000 * (firstx-sx1) / (sx2-sx1+1);
  for (int sx=firstx; sx<=lastx; sx++, srcx+=deltax)
    if (w >= wbuffer[sx])
    {
      unsigned line = ((unsigned *)&sprite)[srcx>>12];
      unsigned line_mask = ((unsigned *)&mask)[srcx>>12];
      unsigned srcy = first_srcy;
      for (int sy=firsty; sy<=lasty; sy++, srcy+=deltay)
      {
        unsigned bit_mask = 1<<(srcy>>12);
        if (line_mask & bit_mask)
        {
          if (line & bit_mask)
            setPixel(sx, sy);
          else
            clearPixel(sx, sy);
        }
      }
    }
}

Miniboi MB;


void setup() {
    MB.begin();
}

void loop() {
    loop2();
    drawFrame();
    setPixel(0,0);
    setPixel(1,0);

}


// END OF ARDUINO CODE

int main()
{
    //memset(testscr,0xAA,504);
    EMU.start();
    setup();

while (emuWindow.isOpen())
    {
	loop();
	EMU.refresh(&buffer[0]);
    }
	return 0;
}

