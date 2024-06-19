#include "Source.hpp"
#include <iostream>
Source::Source()
{
    window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Network Petri", sf::Style::None);

    window->setFramerateLimit(this->fps);
    window->setVerticalSyncEnabled(true);

    this->Main_petri = nullptr;
    this->Main_square = nullptr;
    this->Main_arrow = nullptr;

    Source::Create_Buttons();
    this->vector_buttons[2]->BTN_WAIT = false;
    this->vector_buttons[3]->BTN_WAIT = false;
    this->vector_buttons[4]->BTN_WAIT = false;
    this->vector_buttons[5]->BTN_WAIT = false;

    srand(time(NULL));
}
////////////////////////////////////////////////////////////////
Source::~Source()
{
    delete this->window;
    for (Petri *circle : this->vector_circles)
    {
        if (circle->InboxArrows.size() > 0)
        {
            for (Arrow *a : circle->InboxArrows)
            {
                delete a;
            }
        }
        if (circle->ExitArrows.size() > 0)
        {
            for (Arrow *a : circle->ExitArrows)
            {
                delete a;
            }
        }
        delete circle->text;
        delete circle;
    }
    for (Petri *square : this->vector_squares)
    {
        if (square->InboxArrows.size() > 0)
        {
            for (Arrow *a : square->InboxArrows)
            {
                delete a;
            }
        }
        if (square->ExitArrows.size() > 0)
        {
            for (Arrow *a : square->ExitArrows)
            {
                delete a;
            }
        }
        delete square;
    }
    for (Button *button : this->vector_buttons)
    {
        delete button;
    }
    delete this->Pick;
}
////////////////////////////////////////////////////////////////
void Source::Create_Buttons()
{
    this->vector_buttons.push_back(new Button(sf::Vector2f(-1, -1), "image/button_1.png", "image/shadow.png", "image/shadow.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(51, -1), "image/button_2.png", "image/shadow_2.png", "image/shadow_2.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(101, -1), "image/button_3.png", "image/shadow_2.png", "image/shadow_2.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(151, -1), "image/button_4.png", "image/shadow.png", "image/shadow.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(201, -1), "image/button_5.png", "image/shadow.png", "image/shadow.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(1246, 767), "image/button_6.png", "image/shadow.png", "image/shadow.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(1195, 767), "image/button_7.png", "image/shadow.png", "image/shadow.png"));
    this->vector_buttons.push_back(new Button(sf::Vector2f(1249, -2), "image/button_8.png", "image/shadow.png", "image/shadow.png"));
    this->Pick = new Button(sf::Vector2f(550, 550), "image/pick_1.png", "image/pick_2.png", "image/pick_2.png");
}
////////////////////////////////////////////////////////////////
void Source::update(sf::Event &event)
{
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->window->close();
    }
    Source::updateMousePosition();
    Source::Petri_active();
    for (Petri *circle : this->vector_circles)
    {
        if (circle->BTN_ACTIVE)
        {
            Source::Move(circle, 1);
            this->Pick->setVector_poz(circle->getVector_poz());
            circle->text->setPosition(sf::Vector2f(circle->getVector_poz().x + 43, circle->getVector_poz().y + 38));
            if (circle->quantity_in_arrows > 0)
            {
                for (Arrow *arrow : circle->InboxArrows)
                {
                    arrow->vec_poz = sf::Vector2f(circle->getVector_poz().x + 52, circle->getVector_poz().y + 52);
                    this->dX = arrow->vec_poz_square.x - this->mou_poz.x - 10;
                    this->dY = arrow->vec_poz_square.y - this->mou_poz.y - 10;
                    float ro = (atan2(this->dY, this->dX)) * 180 / 3.14159265;
                    arrow->setVector_poz(sf::Vector2f(arrow->vec_poz.x + 52 * cos(ro * 3.14159265 / 180 * (-1)), arrow->vec_poz.y + 52 * sin(ro * 3.141492 / 180 * (1))));
                    arrow->setRotation(ro);
                    float scale = sqrt(pow((arrow->vec_poz.x - arrow->vec_poz_square.x), 2) + pow((arrow->vec_poz.y - arrow->vec_poz_square.y), 2));
                    arrow->setScale(sf::Vector2f(scale / 300, scale / 300));
                    // arrow->vec_poz_circle = sf::Vector2f(circle->getVector_poz().x + 52, circle->getVector_poz().y + 52);
                }
            }
            if (circle->quantity_out_arrows > 0)
            {
                for (Arrow *ar : circle->ExitArrows)
                {
                    this->dX = this->mou_poz.x - ar->getVector_poz().x - 10;
                    this->dY = this->mou_poz.y - ar->getVector_poz().y - 10;
                    float ro = (atan2(this->dY, this->dX)) * 180 / 3.14159265;
                    ar->setRotation(ro);
                    ar->setVector_poz(sf::Vector2f(ar->vec_poz.x + 30 * cos(ro * 3.14159265 / 180 * (-1)), ar->vec_poz.y + 60 * sin(ro * 3.141492 / 180 * (1))));
                    ar->vec_poz_circle = sf::Vector2f(circle->getVector_poz().x + 52, circle->getVector_poz().y + 52);
                    // ar->vec_poz_circle = sf::Vector2f(circle->getVector_poz().x, circle->getVector_poz().y);

                    float scale = sqrt(pow((ar->vec_poz.x - circle->getVector_poz().x), 2) + pow((ar->vec_poz.y - circle->getVector_poz().y), 2));
                    ar->setScale(sf::Vector2f(scale / 300, scale / 300));
                }
            }
        }
        if (!this->active)
        {
            if (!circle->getSprite().getGlobalBounds().contains(sf::Vector2f(this->mou_poz.x, this->mou_poz.y)) and (sf::Mouse::isButtonPressed(sf::Mouse::Left) and (this->mou_poz.y > 31) and (this->mou_poz.y < 769)))
            {
                this->CLICK = false;
                this->pick_element = -1;
                this->vector_buttons[2]->BTN_WAIT = false;
                this->vector_buttons[3]->BTN_WAIT = false;
                this->vector_buttons[4]->BTN_WAIT = false;
            }
        }
    }
    for (Petri *square : this->vector_squares)
    {
        if (square->BTN_ACTIVE)
        {
            Source::Move(square, 2);
            this->Pick->setSh_Vector_poz(square->getVector_poz().x - 22, square->getVector_poz().y);
            if (square->quantity_in_arrows > 0)
            {
                for (Arrow *arrow : square->InboxArrows)
                {
                    arrow->setVector_poz(sf::Vector2f(square->getVector_poz().x + 15, square->getVector_poz().y + 50));
                    arrow->vec_poz = sf::Vector2f(square->getVector_poz().x + 15, square->getVector_poz().y + 50);
                    this->dX = arrow->vec_poz_circle.x - this->mou_poz.x - 10;
                    this->dY = arrow->vec_poz_circle.y - this->mou_poz.y - 10;
                    float ro = (atan2(this->dY, this->dX)) * 180 / 3.14159265;
                    arrow->setRotation(ro);
                    arrow->setVector_poz(sf::Vector2f(arrow->vec_poz.x + 30 * cos(ro * 3.14159265 / 180 * (-1)), arrow->vec_poz.y + 60 * sin(ro * 3.141492 / 180 * (1))));
                    arrow->vec_poz_square = sf::Vector2f(square->getVector_poz().x + 15, square->getVector_poz().y + 50);
                    // arrow->vec_poz_square = sf::Vector2f(square->getVector_poz().x, square->getVector_poz().y);

                    float scale = sqrt(pow((arrow->vec_poz.x - arrow->vec_poz_circle.x), 2) + pow((arrow->vec_poz.y - arrow->vec_poz_circle.y), 2));
                    arrow->setScale(sf::Vector2f(scale / 300, scale / 300));
                }
            }
            if (square->quantity_out_arrows > 0)
            {
                for (Arrow *ar : square->ExitArrows)
                {
                    this->dX = this->mou_poz.x - ar->getVector_poz().x - 10;
                    this->dY = this->mou_poz.y - ar->getVector_poz().y - 10;
                    float ro = (atan2(this->dY, this->dX)) * 180 / 3.14159265;
                    ar->setRotation(ro);
                    ar->setVector_poz(sf::Vector2f(ar->vec_poz.x + 52 * cos(ro * 3.14159265 / 180 * (-1)), ar->vec_poz.y + 52 * sin(ro * 3.141492 / 180 * (1))));
                    // ar->vec_poz_square = sf::Vector2f(square->getVector_poz().x, square->getVector_poz().y);
                    ar->vec_poz_square = sf::Vector2f(square->getVector_poz().x + 15, square->getVector_poz().y + 50);

                    // float scale = sqrt(pow((ar->vec_poz.x - square->getVector_poz().x), 2) + pow((ar->vec_poz.y - square->getVector_poz().y), 2));
                    float scale = sqrt(pow((ar->vec_poz.x - ar->vec_poz_square.x), 2) + pow((ar->vec_poz.y - ar->vec_poz_square.y) - 25, 2));

                    ar->setScale(sf::Vector2f(scale / 300, scale / 300));
                }
            }
        }
    }
    if (this->Main_arrow)
    {
        if (Main_arrow->BTN_ACTIVE)
            Source::Arrow_move(Main_arrow);
    }
}
////////////////////////////////////////////////////////////////
void Source::draw(sf::Event &event)
{
    Source::updateMousePosition();
    this->window->clear();

    this->window->draw(interface.getSprite());

    Source::DrawButton();
    Source::MouseAnimateButtons(sf::Vector2f(this->mou_poz.x, this->mou_poz.y));
    Source::DrawPetri();

    if (this->Main_petri and CLICK and this->vector_circles.size() > 0)
    {
        if (this->pick_element == 1)
        {
            this->window->draw(this->Pick->getSprite());
        }
    }
    if (this->Main_square and CLICK and this->vector_squares.size() > 0)
    {
        if (this->pick_element == 2)
        {
            this->window->draw(this->Pick->getShadowSprite());
        }
    }
    this->window->display();
}
////////////////////////////////////////////////////////////////
void Source::updateMousePosition()
{
    this->mou_poz.x = sf::Mouse::getPosition().x - this->window->getPosition().x;
    this->mou_poz.y = sf::Mouse::getPosition().y - this->window->getPosition().y;
}
////////////////////////////////////////////////////////////////
void Source::DrawButton()
{
    for (Button *button : this->vector_buttons)
    {
        window->draw(button->getSprite());
    }
    if (this->vector_buttons[0]->Enabled == false)
        window->draw(this->vector_buttons[0]->getShadowSprite());
}
////////////////////////////////////////////////////////////////
void Source::DrawPetri()
{
    if (this->Main_petri)
    {
        for (Petri *circle : this->vector_circles)
        {
            if (this->Main_petri == circle)
                continue;
            if (circle->Enabled)
            {
                this->window->draw(circle->getSprite());
                // if (!this->vector_buttons[5]->BTN_WAIT)
                this->window->draw(*circle->text);
                if (circle->InboxArrows.size() > 0)
                {
                    for (Arrow *arrow : circle->InboxArrows)
                    {
                        this->window->draw(arrow->getSprite());
                    }
                }
            }
        }
        if (Main_petri->Enabled)
        {
            this->window->draw(this->Main_petri->getSprite());
            // if (!this->vector_buttons[5]->BTN_WAIT)
            this->window->draw(*this->Main_petri->text);
            if (Main_petri->InboxArrows.size() > 0)
            {
                for (Arrow *arrow : Main_petri->InboxArrows)
                {
                    this->window->draw(arrow->getSprite());
                }
            }
        }
    }
    else if (!this->vector_circles.empty())
    {
        for (Petri *circle : this->vector_circles)
        {
            this->window->draw(circle->getSprite());
            // if (!this->vector_buttons[5]->BTN_WAIT)
            this->window->draw(*circle->text);
        }
    }

    for (Petri *square : this->vector_squares)
    {
        this->window->draw(square->getSprite());
        if (square->InboxArrows.size() > 0)
        {
            for (Arrow *arrow : square->InboxArrows)
            {
                this->window->draw(arrow->getSprite());
            }
        }
    }
}
////////////////////////////////////////////////////////////////
void Source::MouseAnimateButtons(const sf::Vector2f &mouse_position)
{
    for (int i = 0; i < this->vector_buttons.size(); ++i)
    {
        if (vector_buttons[i]->getSprite().getGlobalBounds().contains(mouse_position) and vector_buttons[i]->BTN_WAIT and !this->active)
        {
            this->window->draw(this->vector_buttons[i]->getShadowSprite());
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and !vector_buttons[i]->BTN_ACTIVE and vector_buttons[i]->BTN_WAIT)
            {
                window->draw(vector_buttons[i]->getShadowSprite());

                Source::FunctionOfButton(i);
                vector_buttons[i]->BTN_ACTIVE = true;
            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                vector_buttons[i]->BTN_ACTIVE = false;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                window->draw(vector_buttons[i]->getShadowSprite());
            }
        }
    }
}
////////////////////////////////////////////////////////////////
void Source::FunctionOfButton(const int &index)
{
    switch (index)
    {
    case 0:
    {
        if (this->vector_circles.size() == 0)
        {
            this->vector_circles.push_back(new Petri(sf::Vector2f(40, 54), "image/circle.png", 1));
            this->Main_petri = this->vector_circles.front();
        }
        else
        {
            this->vector_circles.push_back(new Petri(sf::Vector2f(40, 54), "image/circle.png", 1));
        }
        break;
    }
    case 1:
    {
        this->vector_squares.push_back(new Petri(sf::Vector2f(80, 54), "image/square.png", 0));
        break;
    }
    case 2:
    {
        if (this->CLICK)
        {
            if (this->pick_element == 1)
            {
                Main_petri->InboxArrows.push_back(new Arrow(sf::Vector2f(Main_petri->getVector_poz().x + 52, Main_petri->getVector_poz().y + 52), "image/arrow.png"));
                Main_petri->quantity_in_arrows += 1;
                Main_arrow = Main_petri->InboxArrows.back();
                Main_arrow->BTN_ACTIVE = true;
                Main_arrow->vec_poz_circle = Main_petri->getVector_poz();
                this->arrow_element = 2;
            }
            if (this->pick_element == 2)
            {
                Main_square->InboxArrows.push_back(new Arrow(sf::Vector2f(Main_square->getVector_poz().x + 15, Main_square->getVector_poz().y + 50), "image/arrow.png"));
                Main_square->quantity_in_arrows += 1;
                Main_arrow = Main_square->InboxArrows.back();
                Main_arrow->BTN_ACTIVE = true;
                Main_arrow->vec_poz_square = Main_square->getVector_poz();
                this->arrow_element = 1;
            }
        }
        break;
    }
    case 3:
    {
        if (this->CLICK)
        {
            this->Main_petri->QUAN += 1;
            this->Main_petri->text->setString(std::to_string(this->Main_petri->QUAN));
        }
        break;
    }
    case 4:
    {

        if (this->CLICK)
        {
            if (this->pick_element == 1)
            {
                if (this->Main_arrow and this->Main_arrow->BTN_ACTIVE)
                {

                    delete this->Main_petri->InboxArrows.back();
                    this->Main_petri->InboxArrows.pop_back();
                    this->Main_arrow->BTN_ACTIVE = false;
                    this->arrow_element = 0;
                    Main_petri->quantity_in_arrows -= 1;
                    if (Main_petri->quantity_in_arrows > 0)
                        Main_arrow = Main_petri->InboxArrows.back();
                    else
                        Main_arrow = nullptr;
                }
                else
                {
                    if (this->vector_squares.size() > 0)
                    {

                        for (Petri *square : this->vector_squares)
                        {
                            for (std::list<Petri *>::iterator iter_circle = square->In_Circles.begin(); iter_circle != square->In_Circles.end(); ++iter_circle)
                            {
                                if (this->Main_petri == *iter_circle)
                                {
                                    square->In_Circles.erase(iter_circle);
                                }
                            }
                            for (std::list<Petri *>::iterator iter_circle = square->out_Circles.begin(); iter_circle != square->out_Circles.end(); ++iter_circle)
                            {
                                if (this->Main_petri == *iter_circle)
                                {
                                    square->out_Circles.erase(iter_circle);
                                }
                            }
                        }
                    }
                    int i = 0;
                    for (std::list<Petri *>::iterator iter = this->vector_circles.begin(); iter != this->vector_circles.end(); ++iter)
                    {
                        if (*iter == this->Main_petri)
                        {
                            this->vector_circles.erase(iter);
                            if (Main_petri->quantity_in_arrows > 0)
                            {
                                for (std::list<Arrow *>::iterator iter_arrow_circle = Main_petri->InboxArrows.begin(); iter_arrow_circle != Main_petri->InboxArrows.end(); ++iter_arrow_circle)
                                {
                                    for (Petri *square : this->vector_squares)
                                    {
                                        for (std::list<Arrow *>::iterator iter_arrow_square = square->ExitArrows.begin(); iter_arrow_square != square->ExitArrows.end(); ++iter_arrow_square)
                                        {
                                            if (*iter_arrow_circle == *iter_arrow_square)
                                            {
                                                square->ExitArrows.erase(iter_arrow_square);
                                                Main_petri->quantity_in_arrows -= 1;
                                            }
                                        }
                                    }
                                    delete *iter_arrow_circle;
                                }
                            }
                            if (Main_petri->quantity_out_arrows > 0)
                            {
                                for (std::list<Arrow *>::iterator iter_arrow_circle = Main_petri->ExitArrows.begin(); iter_arrow_circle != Main_petri->ExitArrows.end(); ++iter_arrow_circle)
                                {
                                    for (Petri *square : this->vector_squares)
                                    {
                                        for (std::list<Arrow *>::iterator iter_arrow_square = square->InboxArrows.begin(); iter_arrow_square != square->InboxArrows.end(); ++iter_arrow_square)
                                        {
                                            if (*iter_arrow_circle == *iter_arrow_square)
                                            {
                                                square->InboxArrows.erase(iter_arrow_square);
                                                Main_petri->quantity_out_arrows -= 1;
                                            }
                                        }
                                    }
                                    delete *iter_arrow_circle;
                                }
                            }
                            // delete this->Main_petri;
                            if (this->vector_circles.size() == 0)
                            {
                                this->Main_petri = nullptr;
                            }
                            else
                            {
                                this->Main_petri = this->vector_circles.back();
                            }
                            this->CLICK = false;
                            this->vector_buttons[2]->BTN_WAIT = false;
                            this->vector_buttons[3]->BTN_WAIT = false;
                            this->vector_buttons[4]->BTN_WAIT = false;
                            break;
                        }
                        ++i;
                    }
                }
            }
            else if (this->pick_element == 2)
            {
                if (this->Main_arrow and this->Main_arrow->BTN_ACTIVE)
                {

                    delete this->Main_square->InboxArrows.back();
                    this->Main_square->InboxArrows.pop_back();
                    this->Main_square->BTN_ACTIVE = false;
                    this->arrow_element = 0;
                    Main_square->quantity_in_arrows -= 1;
                    if (Main_square->quantity_in_arrows > 0)
                        Main_arrow = Main_square->InboxArrows.back();
                    else
                        Main_arrow = nullptr;
                }
                else
                {
                    int j = 0;
                    for (Petri *circle : this->vector_circles)
                    {
                        for (std::list<Petri *>::iterator iter_square = circle->In_Squares.begin(); iter_square != circle->In_Squares.end(); ++iter_square)
                        {
                            if (this->Main_square == *iter_square)
                            {
                                circle->In_Circles.erase(iter_square);
                            }
                        }
                    }
                    for (std::list<Petri *>::iterator iter = this->vector_squares.begin(); iter != this->vector_squares.end(); ++iter)
                    {
                        if (j == this->square_pos)
                        {
                            this->vector_squares.erase(iter);

                            if (Main_square->InboxArrows.size() > 0)
                            {
                                for (std::list<Arrow *>::iterator iter_arrow_square = Main_square->InboxArrows.begin(); iter_arrow_square != Main_square->InboxArrows.end(); ++iter_arrow_square)
                                {
                                    for (Petri *circle : this->vector_circles)
                                    {
                                        for (std::list<Arrow *>::iterator iter_arrow_circle = circle->ExitArrows.begin(); iter_arrow_circle != circle->ExitArrows.end(); ++iter_arrow_circle)
                                        {
                                            if (*iter_arrow_circle == *iter_arrow_square)
                                            {
                                                circle->ExitArrows.erase(iter_arrow_circle);
                                                Main_square->quantity_in_arrows -= 1;
                                            }
                                        }
                                    }
                                    delete *iter_arrow_square;
                                }
                            }
                            if (Main_square->ExitArrows.size() > 0)
                            {
                                for (std::list<Arrow *>::iterator iter_arrow_square = Main_square->ExitArrows.begin(); iter_arrow_square != Main_square->ExitArrows.end(); ++iter_arrow_square)
                                {
                                    for (Petri *circle : this->vector_circles)
                                    {
                                        for (std::list<Arrow *>::iterator iter_arrow_circle = circle->InboxArrows.begin(); iter_arrow_circle != circle->InboxArrows.end(); ++iter_arrow_circle)
                                        {
                                            if (*iter_arrow_circle == *iter_arrow_square)
                                            {
                                                circle->InboxArrows.erase(iter_arrow_circle);
                                                Main_square->quantity_out_arrows -= 1;
                                            }
                                        }
                                    }
                                    delete *iter_arrow_square;
                                }
                            }

                            delete this->Main_square;
                            if (this->vector_squares.size() == 0)
                            {
                                this->Main_square = nullptr;
                            }
                            else
                            {
                                this->Main_square = this->vector_squares.back();
                            }
                            this->CLICK = false;
                            this->vector_buttons[2]->BTN_WAIT = false;
                            this->vector_buttons[4]->BTN_WAIT = false;
                            break;
                        }
                        ++j;
                    }
                }
            }
        }
        break;
    }
    case 5:
    {
        if (this->vector_buttons[5]->BTN_WAIT)
        {
            this->vector_buttons[5]->BTN_WAIT = false;
        }
        break;
    }
    case 6:
    {
        // this->vector_buttons[5]->BTN_WAIT = true;

        Source::Petri_network();

        // this->vector_buttons[5]->BTN_WAIT = true;
        // // this->window->clear();
        // // Source::DrawButton();
        // // Source::DrawPetri();

        // while (this->vector_buttons[5]->BTN_WAIT)
        // {
        //     this->window->clear();
        //     this->window->draw(interface.getSprite());
        //     Source::DrawButton();
        //     Source::DrawPetri();
        //     Source::updateMousePosition();

        //     if (vector_buttons[5]->getSprite().getGlobalBounds().contains(sf::Vector2f(this->mou_poz.x, this->mou_poz.y)) and vector_buttons[5]->BTN_WAIT and !this->active)
        //     {
        //         this->window->draw(this->vector_buttons[5]->getShadowSprite());
        //         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        //         {
        //             this->vector_buttons[5]->BTN_WAIT = false;
        //         }
        //     }
        //     Source::Petri_network();
        //     // sleep(1);
        //     this->window->display();
        // }
        break;
    }
    case 7:
    {
        this->window->close();
        break;
    }
    case 8:
    {
        this->window->close();
        break;
    }
    }
}
////////////////////////////////////////////////////////////////
void Source::Petri_active()
{
    int x = 0;
    for (Petri *circle : this->vector_circles)
    {
        if (circle->getSprite().getGlobalBounds().contains(sf::Vector2f(this->mou_poz.x, this->mou_poz.y)) and this->Pressclick == false)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and this->active == false)
            {
                if (circle->BTN_ACTIVE == false)
                {

                    if (arrow_element == 0)
                    {
                        circle->BTN_ACTIVE = true;
                        this->active = true;
                        this->Main_petri = circle;
                        this->CLICK = true;
                    }
                    if (Main_petri and Main_square)
                    {
                        this->vector_buttons[2]->BTN_WAIT = true;
                    }
                    this->vector_buttons[3]->BTN_WAIT = true;
                    this->vector_buttons[4]->BTN_WAIT = true;
                    this->pick_element = 1;
                    this->circle_pos = x;
                    if (this->Main_arrow and this->arrow_element == 1)
                    {
                        if (this->Main_arrow->BTN_ACTIVE)
                        {
                            this->Main_arrow->BTN_ACTIVE = false;
                            circle->ExitArrows.push_back(Main_arrow);
                            circle->quantity_out_arrows += 1;
                            this->Main_square->In_Circles.push_back(circle);

                            Main_arrow->vec_poz_circle = circle->getVector_poz();
                            this->arrow_element = 0;
                        }
                    }
                }
                else
                    circle->BTN_ACTIVE = false;
            }

            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                circle->BTN_ACTIVE = false;
                this->active = false;
            }
        }

        else
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->Pressclick = true;
            }
            else
                this->Pressclick = false;
        }
        ++x;
    }
    int y = 0;
    for (Petri *square : this->vector_squares)
    {
        if (square->getSprite().getGlobalBounds().contains(sf::Vector2f(this->mou_poz.x, this->mou_poz.y)))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and this->active == false)
            {
                if (square->BTN_ACTIVE == false)
                {
                    if (arrow_element == 0)
                    {
                        square->BTN_ACTIVE = true;
                        this->active = true;
                        this->Main_square = square;
                        this->CLICK = true;
                    }
                    if (Main_petri and Main_square)
                        this->vector_buttons[2]->BTN_WAIT = true;
                    this->vector_buttons[3]->BTN_WAIT = false;
                    this->vector_buttons[4]->BTN_WAIT = true;
                    this->pick_element = 2;
                    this->square_pos = y;

                    if (this->Main_arrow and this->arrow_element == 2)
                    {
                        if (this->Main_arrow->BTN_ACTIVE)
                        {
                            this->Main_arrow->BTN_ACTIVE = false;
                            Main_arrow->vec_poz_square = square->getVector_poz();
                            square->ExitArrows.push_back(Main_arrow);
                            square->quantity_out_arrows += 1;
                            this->Main_petri->In_Squares.push_back(square);
                            square->out_Circles.push_back(Main_petri);
                            this->arrow_element = 0;
                        }
                    }
                }
                else
                    square->BTN_ACTIVE = false;
            }

            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                square->BTN_ACTIVE = false;
                this->active = false;
            }
        }
        else
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->Pressclick = true;
            }
            else
                this->Pressclick = false;
        }
        ++y;
    }
}
////////////////////////////////////////////////////////////////
void Source::Move(Petri *pet, const int variable)
{
    if (variable == 1)
    {
        if (this->mou_poz.x > 1240)
        {
            if (this->mou_poz.y > 740)
                pet->setVector_poz(sf::Vector2f(1200, 700));
            else if (this->mou_poz.y < 50)
                pet->setVector_poz(sf::Vector2f(1200, 0));
            else
                pet->setVector_poz(sf::Vector2f(1200, this->mou_poz.y - 40));
        }
        else if (this->mou_poz.x < 50)
        {
            if (this->mou_poz.y < 50)
                pet->setVector_poz(sf::Vector2f(0, 0));
            else if (this->mou_poz.y > 740)
                pet->setVector_poz(sf::Vector2f(0, 700));

            else
                pet->setVector_poz(sf::Vector2f(0, this->mou_poz.y - 40));
        }
        else if (this->mou_poz.y > 740)
        {
            pet->setVector_poz(sf::Vector2f(this->mou_poz.x - 40, 700));
        }
        else if (this->mou_poz.y < 50)
        {
            pet->setVector_poz(sf::Vector2f(this->mou_poz.x - 40, 0));
        }
        else
            pet->setVector_poz(sf::Vector2f(this->mou_poz.x - 45, this->mou_poz.y - 45));
    }
    else if (variable == 2)
    {
        if (this->mou_poz.x > 1300 - 15)
        {
            if (this->mou_poz.y > 740)
                pet->setVector_poz(sf::Vector2f(1300 - 30, 700));
            else if (this->mou_poz.y < 50)
                pet->setVector_poz(sf::Vector2f(1300 - 30, 0));
            else
                pet->setVector_poz(sf::Vector2f(1300 - 30, this->mou_poz.y - 40));
        }
        else if (this->mou_poz.x < 15)
        {
            if (this->mou_poz.y < 15)
                pet->setVector_poz(sf::Vector2f(0, 0));
            else if (this->mou_poz.y > 740)
                pet->setVector_poz(sf::Vector2f(0, 700));

            else
                pet->setVector_poz(sf::Vector2f(0, this->mou_poz.y - 40));
        }
        else if (this->mou_poz.y > 740)
        {
            pet->setVector_poz(sf::Vector2f(this->mou_poz.x - 15, 700));
        }
        else if (this->mou_poz.y < 40)
        {
            pet->setVector_poz(sf::Vector2f(this->mou_poz.x - 15, 0));
        }
        else
            pet->setVector_poz(sf::Vector2f(this->mou_poz.x - 15, this->mou_poz.y - 40));
    }
}
////////////////////////////////////////////////////////////////
void Source::Arrow_move(Arrow *arr)
{
    this->dX = this->mou_poz.x - arr->getVector_poz().x - 10;
    this->dY = this->mou_poz.y - arr->getVector_poz().y - 10;
    float ro = (atan2(this->dY, this->dX)) * 180 / 3.14159265;
    arr->setRotation(ro);
    float cos_angle = cos(ro * 3.14159265 / 180 * (-1));
    float sin_angle = sin(ro * 3.141492 / 180);
    if (this->arrow_element == 2)
    {
        arr->setVector_poz(sf::Vector2f(arr->vec_poz.x + 52 * cos_angle, arr->vec_poz.y + 52 * sin_angle));
    }
    else if (this->arrow_element == 1)
    {
        arr->setVector_poz(sf::Vector2f(arr->vec_poz.x + 30 * cos_angle, arr->vec_poz.y + 50 * sin_angle));
        // arr->setVector_poz(sf::Vector2f(arr->vec_poz.x+ 160* cos(atan((160*tan(ro * 3.14159265 / 180 * (-1))/30))), arr->vec_poz.y + 30* sin(atan((160*tan(ro * 3.14159265 / 180 * (-1))/30)))));
    }
    float scale = sqrt(pow((arr->vec_poz.x - this->mou_poz.x), 2) + pow((arr->vec_poz.y - this->mou_poz.y), 2));
    arr->setScale(sf::Vector2f(scale / 300, 1));
    // this->Main_petri->text->setString(std::to_string(scale));
}
////////////////////////////////////////////////////////////////
void Source::Petri_network()
{
    int i = 0;
    std::vector<Petri *> Active_squares;

    for (Petri *square : this->vector_squares)

    {
        bool yes = true;
        for (Petri *circle_out_square : square->out_Circles)
        {
            if (circle_out_square->QUAN == 0)
            {
                yes = false;
            }
        }
        if (yes)
        {
            Active_squares.push_back(square);
        }
    }
    int random_square = (1 + rand() % (Active_squares.size()) - 1);
    Petri *square;
    for (Petri *square_ : Active_squares)
    {
        if (i == random_square)
        {
            square = square_;
            break;
        }
        ++i;
    }

    for (Petri *circle : square->out_Circles)
    {
        circle->QUAN -= 1;
        circle->text->setString(std::to_string(circle->QUAN));
    }
    for (Petri *circle : square->In_Circles)
    {
        circle->QUAN += 1;
        circle->text->setString(std::to_string(circle->QUAN));
    }
}
////////////////////////////////////////////////////////////////
void Source::start()
{
    while (this->window->isOpen())
    {
        sf::Event event;
        update(event);
        draw(event);
    }
}
////////////////////////////////////////////////////////////////