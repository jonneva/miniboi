#ifndef PRIMITIVES_H
#define PRIMITIVES_H


extern const int width;
extern const int height;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#define MAKE_RGB32(r, g, b) ((((BYTE)(b)|((WORD)((BYTE)(g))<< 8 ))|(((DWORD)(BYTE)(r))<< 16 )))
#define PITCH 4 // PixelToaster works with a 32-bit buffer

namespace Miniboi3D
{
    #define sgn(x) ((x<0)?-1:((x>0)?1:0))       // macro to return the sign of a number
    typedef unsigned int TRUECOLOR;             // 32-bit color as argb

    inline void cls();
    inline void line_horiz(int x1, int x2, int y, unsigned int color);
    inline void plot_pixel(int x,int y, TRUECOLOR color);
    void line_fast(int x1, int y1, int x2, int y2, TRUECOLOR color);

    inline void cls()
    {
        //memset((void*)&pixels[0], 0, pixels.size() << 2);
        //memset((void*)&pixels[0], 0, sizeof pixels);
    }


    // Draw a horizontal line
    inline void line_horiz(int x1, int x2, int y, unsigned int color)
    {
        for (int x=x1; x<=x2; ++x)
        {
            //plot_pixel(x, y, color);
        }
    }


}

#endif  //PRIMITIVES_H
