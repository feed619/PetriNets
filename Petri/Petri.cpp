#include "Petri.hpp"

Petri::Petri(sf::Vector2f vector_poz, const std::string &image, int variable)
{
    this->vec_poz = vector_poz;
    this->image.loadFromFile(image);
    this->vector_size_button = this->image.getSize();
    this->texture.loadFromImage(this->image);
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(vector_poz);
    this->variable = variable;
    if (this->variable == 1)
    {
        this->font.loadFromFile("Petri/font/qwe.ttf");
        this->text = new sf::Text(this->string_Text, this->font);
        this->text->setCharacterSize(25);
        this->text->setStyle(sf::Text::Italic);
        this->text->setFillColor(sf::Color::Black);
        this->text->setPosition(sf::Vector2f(40+43, 54+38));
    }
}
Petri::~Petri()
{
    if (this->variable == 1)
    {
        delete this->text;
    }
}
void Petri::setTexture(const std::string &texture)
{
    sf::Image im;
    im.loadFromFile(texture);
    this->texture.loadFromImage(im);
    this->sprite.setTexture(this->texture);
}
