#include "StartCalculator.hpp"

StartCalculator::StartCalculator()
{
    window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Calculator", sf::Style::Fullscreen);
    sf::Image icon;
    window->setFramerateLimit(this->fps);
}
////////////////////////////////////////////////////////////////
StartCalculator::~StartCalculator()
{
    delete this->window;
}
////////////////////////////////////////////////////////////////
void StartCalculator::update(sf::Event &event)
{
    while (this->window->pollEvent(event))
    {
        if (shell.TextBool)
            shell.TextPut(*this->window, event);
    }
}
////////////////////////////////////////////////////////////////
void StartCalculator::draw(sf::Event &event)
{
    this->window->clear();

    this->window->draw(interface.getSprite());
    this->shell.DrawButton(*this->window);

    this->updateMousePosition();
    this->shell.MouseAnimate(this->mou_poz, *this->window);

    this->shell.DrawText(*this->window);

    this->window->display();
}
////////////////////////////////////////////////////////////////
void StartCalculator::updateMousePosition()
{
    this->mou_poz.x = sf::Mouse::getPosition().x - this->window->getPosition().x;
    this->mou_poz.y = sf::Mouse::getPosition().y - this->window->getPosition().y;
}
////////////////////////////////////////////////////////////////
void StartCalculator::start()
{
    while (this->window->isOpen())
    {
        sf::Event event;
        update(event);
        draw(event);
    }
}
////////////////////////////////////////////////////////////////