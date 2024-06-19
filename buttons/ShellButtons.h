#ifndef _SHELL_BUTT_
#define _SHELL_BUTT_

#include "../pakage/init.hpp"
#include "Button.cpp"
#include "MethodButtons.cpp"
#include <limits>

class ShellButtons
{
public:
    sf::Font font;
    sf::Text *TextAnswer;

    std::string string_Text = "0";
    std::string path_of_file = "";
    std::string path_main = "File\\file.txt";

    const short int MAX_MATRIX_SIZE = 6;
    int sizeMatrix;
    int x = 0;
    int y = 0;
    int post_x = 0;
    int post_y = 0;

    bool TextBool = false;

    sf::Vector2f *vector_poz;
    sf::Vector2f *vector_new_poz;
    sf::Vector2f mou_poz;

    std::vector<std::string> Answer;
    std::vector<Button *> vector_buttons;
    std::vector<std::vector<Button *>> vector_free_buttons;

    /// buttons click methods
    MethodButtons Methods;

    // create buttons
    void CreateVector();
    void CreateVectorButtons();
    void CreateVectorFreeButtons();

    // Animation methods
    void MouseAnimateButtons(const sf::Vector2f &mouse_position, sf::RenderWindow &window);
    void MouseAnimateFreeButtons(const sf::Vector2f &mouse_position, sf::RenderWindow &window);

    // PositionMouse
    void PositionMouse(sf::RenderWindow &window, Button *button, int &pos_but_in_vector);
    void PositionMouseFree(sf::RenderWindow &window, Button *button, int x, int y);

    // click methods of free buttons
    void FreeMethodButtons(sf::RenderWindow &window, int x, int y);

    // vector position of mouse
    sf::Vector2i mouse_position;

    // constructor and destructor
    ShellButtons();
    ~ShellButtons();

    // draw all buttons
    void DrawButton(sf::RenderWindow &window); // Animation methods
    void MouseAnimate(const sf::Vector2f &mouse_position, sf::RenderWindow &window);

    // click methods of buttons
    void FunctionOfButton(const int &index, sf::RenderWindow &window);

    // resize size of matrix
    void ReSize(sf::RenderWindow &window);

    // Draw Text
    void DrawText(sf::RenderWindow &window);

    // getter
    Button &getButton(const int &index) { return *vector_buttons[index]; }
    void TextPut(sf::RenderWindow &window, sf::Event &event);
};

#endif