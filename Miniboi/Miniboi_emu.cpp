#include <SFML/Graphics.hpp>
#include "Miniboi_emu.h"

using namespace std;
using namespace sf;

sf::Texture emuTexture;
sf::Sprite emuSprite;
sf::RectangleShape emuPixel0, emuPixel1;
RenderWindow emuWindow{{EMUW, EMUH}, "Miniboi Emulator"};
sf::View emuScreen(sf::FloatRect(0, 0, 84, 48));
sf::Event emuEvent;


int Miniboi_emu::pollEsc() {
emuWindow.pollEvent(emuEvent);
    if(emuEvent.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
       emuWindow.close();
       return -1;
    }
return 0;
}

int Miniboi_emu::pollFire()
{
emuWindow.pollEvent(emuEvent);
    if(Keyboard::isKeyPressed(Keyboard::Key::Space)) return 1;
    return 0;
}

int Miniboi_emu::pollLeft()
{
emuWindow.pollEvent(emuEvent);
    if(Keyboard::isKeyPressed(Keyboard::Key::Left)) return 1;
    return 0;
}

int Miniboi_emu::pollRight()
{
emuWindow.pollEvent(emuEvent);
    if(Keyboard::isKeyPressed(Keyboard::Key::Right)) return 1;
    return 0;
}

int Miniboi_emu::pollUp()
{
emuWindow.pollEvent(emuEvent);
    if(Keyboard::isKeyPressed(Keyboard::Key::Up)) return 1;
    return 0;
}

int Miniboi_emu::pollDown()
{
emuWindow.pollEvent(emuEvent);
    if(Keyboard::isKeyPressed(Keyboard::Key::Down)) return 1;
    return 0;
}

void Miniboi_emu::start()
{
    emuWindow.setFramerateLimit(60);
    emuPixel0.setSize(sf::Vector2f(1,1));
    emuPixel0.setFillColor(sf::Color::Blue);
    emuPixel1.setSize(sf::Vector2f(1,1));
    emuPixel1.setFillColor(sf::Color::Black);
    emuScreen.zoom(EMUZ);
    emuScreen.setViewport(sf::FloatRect(0, 0, 1, 1));
    emuWindow.clear(Color::White);
    emuWindow.setView(emuScreen);
}

void Miniboi_emu::refresh(uint8_t * screen){
    emuWindow.setView(emuScreen);
    emuWindow.clear(Color::White);
    /*for (int y=0; y < 48; y++) {
        for (int x=0; x < 84; x ++) {
            if (screen[x/8+y*84] & (0x80 >>(x&7)))
                {
                    emuPixel1.setPosition(x,y);
                    emuWindow.draw(emuPixel1);
                } else {
                    emuPixel0.setPosition(x,y);
                    emuWindow.draw(emuPixel0);
                }
            }
        }*/
    int x=0, y=0;
    for (uint16_t byteptr=0; byteptr < 504; byteptr++) {
        for (uint8_t bitptr=0; bitptr < 8; bitptr ++) {
            if (screen[byteptr] & (0x80 >> (bitptr&7)))
                {
                    emuPixel1.setPosition(x,y);
                    emuWindow.draw(emuPixel1);
                } else {
                    emuPixel0.setPosition(x,y);
                    emuWindow.draw(emuPixel0);
                }
            x++;
            if (x==84) { x = 0; y++;}
            }
    }

    emuWindow.display();
    pollEsc();
}
