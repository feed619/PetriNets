#ifndef _START_CALC_
#define _START_CALC_

#include "../pakage/init.hpp"
#include "../pakage/interface/Interface.cpp"
#include "../pakage/button/Button.cpp"

#include "../Petri/Petri.cpp"

class Source
{
private:
    Interface interface;
    sf::RenderWindow *window;
    sf::Vector2f mou_poz;

    int width = 1300;
    int height = 800;
    int fps = 60;
    int pick_element = -1;
    int circle_pos = -1;
    int square_pos = -1;

    int arrow_element = 0;

    float dX = 0;
    float dY = 0;

    std::list<Petri *> vector_circles;
    std::list<Petri *> vector_squares;
    std::vector<Button *> vector_buttons;

    Petri *Main_petri;
    Petri *Main_square;
    Arrow *Main_arrow;
    Button *Pick;

    sf::Font font;

    std::string string_Text = "0";

    bool active = false;
    bool CLICK = false;
    bool include = false;
    int ARROW_BUTTON = 0;

    void update(sf::Event &event);
    void draw(sf::Event &event);

    void updateMousePosition();

    void Create_Buttons();
    void DrawButton();
    void DrawPetri();
    void FunctionOfButton(const int &index);
    void MouseAnimateButtons(const sf::Vector2f &mouse_position);
    void Petri_active();
    void Move(Petri *pet, const int variable);
    void Arrow_move(Arrow *arr);
    void Petri_network();

public:
    Source();
    ~Source();

    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    sf::Vector2f getMousePosition() { return this->mou_poz; }
    void start();
};

#endif