#include "ShellButtons.h"

ShellButtons::ShellButtons()
{
    this->sizeMatrix = 6;
    vector_poz = new sf::Vector2f(44, 44);
    vector_new_poz = new sf::Vector2f(224, 95);
    this->font.loadFromFile("fileButton/font/qwe.ttf");

    CreateVectorButtons();
    CreateVectorFreeButtons();
    this->vector_buttons[2]->BTN_Anim = false;
    this->vector_buttons[4]->BTN_WAIT = false;
    this->vector_buttons[8]->BTN_WAIT = false;

    this->TextAnswer = new sf::Text("", this->font);
    this->TextAnswer->setCharacterSize(30);
    this->TextAnswer->setStyle(sf::Text::Italic);
    this->TextAnswer->setPosition(sf::Vector2f(60, 615));
}
////////////////////////////////////////////////////////////////
void ShellButtons::CreateVectorButtons()
{

    this->vector_buttons.push_back(new Button(sf::Vector2f(1651, 54), "image/frontButton/quantity.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png"));

    this->vector_buttons.push_back(new Button(sf::Vector2f(1702, 135), "image/frontPM/minus.png", "image/frontPM/shadow/shadow15.png", "image/frontPM/click/click15.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(1759, 135), "image/frontPm/plus.png", "image/frontPM/shadow/shadow15.png", "image/frontPM/click/click15.png"));

    this->vector_buttons.push_back(new Button(sf::Vector2f(1651, 223), "image/frontButton/file.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(1651, 400), "image/frontButton/history.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(1651, 879), "image/frontButton/answer.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png"));

    this->vector_buttons.push_back(new Button(sf::Vector2f(1863, 0), "image/frontPM/exitnew.png", "image/frontPM/shadow/shadowExitWindow.png", "image/frontPM/shadow/shadowExitWindow.png"));

    this->vector_buttons.push_back(new Button(sf::Vector2f(1700, 300), "image/frontButton/off.png", "image/frontPM/shadow/shadowExitWindow.png", "image/frontPM/shadow/shadowExitWindow.png"));

    this->vector_buttons.push_back(new Button(sf::Vector2f(1700, 300), "image/frontButton/on.png", "image/frontPM/shadow/shadowExitWindow.png", "image/frontPM/shadow/shadowExitWindow.png"));
}
void ShellButtons::CreateVectorFreeButtons()
{
    for (int i = 0; i < this->MAX_MATRIX_SIZE; ++i)
    {
        this->vector_free_buttons.push_back(std::vector<Button *>());
        this->vector_poz->x = 44;
        for (int j = 0; j < this->MAX_MATRIX_SIZE + 1; ++j)
        {
            this->vector_free_buttons[i].push_back(new Button(*this->vector_poz, "image/emptyButton/spriteButton.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png"));
            std::string str;
            if (j == this->MAX_MATRIX_SIZE)
                str = "C" + std::to_string(j + 1) + "=";

            else
            {
                str = "X" + std::to_string(j + 1) + "=";
            }
            this->vector_free_buttons[i][j]->text = new sf::Text(this->string_Text, this->font);
            this->vector_free_buttons[i][j]->text_name = new sf::Text(str, this->font);

            this->vector_free_buttons[i][j]->text->setCharacterSize(45);
            this->vector_free_buttons[i][j]->text_name->setCharacterSize(30);

            this->vector_free_buttons[i][j]->text->setStyle(sf::Text::Italic);
            this->vector_free_buttons[i][j]->text_name->setStyle(sf::Text::Italic);

            this->vector_free_buttons[i][j]->text->setColor(sf::Color(90, 90, 90));
            this->vector_free_buttons[i][j]->text_name->setColor(sf::Color(137, 137, 137));

            this->vector_free_buttons[i][j]->text->setPosition(this->vector_poz->x + 10 + 48, this->vector_poz->y + 3);
            this->vector_free_buttons[i][j]->text_name->setPosition(this->vector_poz->x + 10, this->vector_poz->y + 15);
            this->vector_poz->x += this->vector_new_poz->x;
        }
        this->vector_poz->y += this->vector_new_poz->y;
    }
}
////////////////////////////////////////////////////////////////
void ShellButtons::DrawButton(sf::RenderWindow &window)
{
    this->mou_poz.x = sf::Mouse::getPosition().x - window.getPosition().x;
    this->mou_poz.y = sf::Mouse::getPosition().y - window.getPosition().y;

    for (Button *button : this->vector_buttons)
    {
        if (button->BTN_WAIT)
            window.draw(button->getSprite());
    }

    for (int i = 0; i < this->sizeMatrix; ++i)
    {
        for (int j = 0; j < this->sizeMatrix + 1; ++j)
        {
            if (this->vector_free_buttons[i][j]->BTN_WAIT)
                window.draw(this->vector_free_buttons[i][j]->getSprite());
            if (this->vector_free_buttons[i][j]->TextPut == true)
                window.draw(this->vector_free_buttons[i][j]->getSpriteShadow());
        }
    }
}
void ShellButtons::DrawText(sf::RenderWindow &window)
{
    for (int i = 0; i < this->sizeMatrix; ++i)
    {
        for (int j = 0; j < this->sizeMatrix + 1; ++j)
        {

            window.draw(*this->vector_free_buttons[i][j]->text);
            window.draw(*this->vector_free_buttons[i][j]->text_name);
        }
    }
    window.draw(*this->TextAnswer);
}
////////////////////////////////////////////////////////////////
void ShellButtons::TextPut(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::BackSpace)
        {
            if (this->string_Text.length() > 0)
            {
                this->string_Text.pop_back();
                this->vector_free_buttons[this->y][this->x]->text->setString(this->string_Text);
            }
        }
    }
    else if (event.type == sf::Event::TextEntered and !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) and this->string_Text.length() < 5)
    {

        this->string_Text += event.text.unicode;
        this->vector_free_buttons[this->y][this->x]->text->setString(this->string_Text);
    }
}
////////////////////////////////////////////////////////////////
void ShellButtons::MouseAnimateButtons(const sf::Vector2f &mouse_position, sf::RenderWindow &window)
{
    if (!this->TextBool)
    {
        for (int i = 1; i < this->vector_buttons.size(); ++i)
        {
            if (vector_buttons[i]->getSprite().getGlobalBounds().contains(mouse_position) and vector_buttons[i]->BTN_WAIT and vector_buttons[i]->BTN_Anim)
            {
                if (i < 7)
                    window.draw(vector_buttons[i]->getShadowSprite());
                ShellButtons::PositionMouse(window, vector_buttons[i], i);
            }
        }
    }
}
void ShellButtons::MouseAnimateFreeButtons(const sf::Vector2f &mouse_position, sf::RenderWindow &window)
{
    if (!this->TextBool)
    {
        for (int i = 0; i < this->sizeMatrix; ++i)
        {
            for (int j = 0; j < this->sizeMatrix + 1; ++j)
            {
                if (this->vector_free_buttons[i][j]->getSprite().getGlobalBounds().contains(mouse_position))
                {
                    window.draw(this->vector_free_buttons[i][j]->getShadowSprite());
                    PositionMouseFree(window, this->vector_free_buttons[i][j], j, i);
                }
            }
        }
    }
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) and !(this->vector_free_buttons[this->y][this->x]->getSprite().getGlobalBounds().contains(this->mou_poz))))
    {
        this->vector_free_buttons[this->y][this->x]->TextPut = false;
        if (this->string_Text.length() == 0)
            this->vector_free_buttons[this->y][this->x]->text->setString("0");
        this->TextBool = false;
        this->vector_free_buttons[this->y][this->x]->TextPut = false;
    }
}
void ShellButtons::MouseAnimate(const sf::Vector2f &mouse_position, sf::RenderWindow &window)
{
    ShellButtons::MouseAnimateButtons(mouse_position, window);
    ShellButtons::MouseAnimateFreeButtons(mouse_position, window);
}
////////////////////////////////////////////////////////////////
void ShellButtons::PositionMouse(sf::RenderWindow &window, Button *button, int &pos_but_in_vector)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and !button->BTN_ACTIVE and button->BTN_WAIT)
    {
        if (pos_but_in_vector < 7)
            window.draw(button->getSpriteShadow());
        ShellButtons::FunctionOfButton(pos_but_in_vector, window);
        button->BTN_ACTIVE = true;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        button->BTN_ACTIVE = false;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (pos_but_in_vector < 7)
            window.draw(button->getSpriteShadow());
    }
}
void ShellButtons::PositionMouseFree(sf::RenderWindow &window, Button *button, int a, int b)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->vector_free_buttons[this->y][this->x]->TextPut = false;
        window.draw(button->getSpriteShadow());
        FreeMethodButtons(window, a, b);
        button->BTN_ACTIVE = true;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        window.draw(button->getSpriteShadow());
    }
}
////////////////////////////////////////////////////////////////
void ShellButtons::FunctionOfButton(const int &index, sf::RenderWindow &window)
{
    switch (index)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        this->Methods.MinusMethod(this->sizeMatrix);
        if (this->sizeMatrix == 1)
        {
            this->vector_buttons[1]->BTN_Anim = false;
            this->vector_buttons[2]->BTN_Anim = true;
        }
        else
        {
            this->vector_buttons[1]->BTN_Anim = true;
            this->vector_buttons[2]->BTN_Anim = true;
        }
        for (int i = 0; i < this->sizeMatrix; ++i)
        {
            this->vector_free_buttons[i][this->sizeMatrix]->text_name->setString("C" + std::to_string(i + 1) + "=");
        }
        break;
    }
    case 2:
    {
        this->Methods.PlusMethod(this->sizeMatrix);
        if (this->sizeMatrix == 6)
        {
            this->vector_buttons[2]->BTN_Anim = false;
            this->vector_buttons[1]->BTN_Anim = true;
        }
        else
        {
            this->vector_buttons[1]->BTN_Anim = true;
            this->vector_buttons[2]->BTN_Anim = true;
        }
        for (int i = 0; i < this->sizeMatrix; ++i)
        {
            this->vector_free_buttons[i][this->sizeMatrix - 1]->text_name->setString("X" + std::to_string(this->sizeMatrix) + "=");
        }
        break;
    }
    case 3:
    {
        this->Methods.FileMethod(this->path_of_file);
        if (this->path_of_file.length() > 0)
            this->vector_buttons[8]->BTN_WAIT = true;
        break;
    }
    case 4:
    {
        break;
    }
    case 5:
    {
        if (this->vector_buttons[8]->BTN_WAIT == true)
        {
            if (this->path_of_file.length() > 0)
                this->Answer = this->Methods.FileSlae(this->path_of_file);
            else
            {
                this->Answer = this->Methods.FileSlae(this->path_main);
            }
        }
        else
        {
            try
            {
                std::vector<std::vector<double>> Matrix_of_numbers;
                for (int i = 0; i < this->sizeMatrix; i++)
                {
                    Matrix_of_numbers.push_back(std::vector<double>());

                    for (int j = 0; j < this->sizeMatrix + 1; j++)
                    {
                        std::string asd = this->vector_free_buttons[i][j]->text->getString();
                        auto a = std::stod(asd);
                        Matrix_of_numbers[i].push_back(a);
                    }
                }
                this->Answer = this->Methods.ManuallySlae(Matrix_of_numbers, this->sizeMatrix, this->sizeMatrix + 1);
            }
            catch (...)
            {
                this->Answer.clear();
                this->Answer.push_back("Error with numbers");
            }
        }

        std::string ans;
        for (auto str : this->Answer)
        {
            if (ans.length() > 0)
                ans = ans + "\n" + str;
            else
            {
                ans += str;
            }
        }
        // if (ans.length() < 10)
        this->TextAnswer->setString(ans);
        // else
        // {
        //     this->TextAnswer->setString("Look at the answer in the file 'answer.txt'");
        //     std::ofstream out; // поток для записи
        //     out.open("File\\answer.txt");
        //     if (out.is_open())
        //     {
        //         out << ans;
        //         out.close();
        //     }
        // }
        break;
    }
    case 6:
    {
        this->Methods.ExitMethod(window);
        break;
    }
    case 7:
    {
        if (this->vector_buttons[8]->BTN_WAIT == false)
            this->vector_buttons[8]->BTN_WAIT = true;
        else if (this->vector_buttons[8]->BTN_WAIT == true)
            this->vector_buttons[8]->BTN_WAIT = false;
        break;
    }
    case 8:
    {
        break;
    }
    }
}
void ShellButtons::FreeMethodButtons(sf::RenderWindow &window, int x, int y)
{
    if (this->vector_free_buttons[y][x]->text->getString() == "0")
        this->vector_free_buttons[y][x]->text->setString("");
    this->x = x;
    this->y = y;
    this->vector_free_buttons[this->y][this->x]->TextPut = true;
    this->string_Text = this->vector_free_buttons[y][x]->text->getString();
    this->TextBool = true;
}
////////////////////////////////////////////////////////////////
ShellButtons::~ShellButtons()
{
    delete this->vector_poz;
    delete this->vector_new_poz;
    delete this->TextAnswer;

    for (Button *button : this->vector_buttons)
    {
        delete button;
    }

    for (std::vector<Button *> vector : this->vector_free_buttons)
    {
        for (Button *button : vector)
        {
            delete button->text;
            delete button;
        }
    }
}
