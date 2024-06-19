#ifndef _START_CALC_
#define _START_CALC_

#include "../pakage/init.hpp"
#include "../buttons/ShellButtons.cpp"
#include "../interface/Interface.cpp"
#include <cmath>

class StartCalculator
{
private:
    sf::RenderWindow *window;
    ShellButtons shell;
    Interface interface;
    sf::Vector2f mou_poz;

    int width = 1911;
    int height = 1008;
    int fps = 60;

    void update(sf::Event &event);
    void draw(sf::Event& event);

    void updateMousePosition();

public:
    StartCalculator();
    ~StartCalculator();

    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    sf::Vector2f getMousePosition() { return this->mou_poz; }

    void start();
};

#endif