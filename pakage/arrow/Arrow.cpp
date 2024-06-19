#include "Arrow.hpp"

Arrow::Arrow(sf::Vector2f vector_poz,const std::string &image)
{
    this->vec_poz = vector_poz;
    this->image_shell.loadFromFile(image);
    this->vector_size_button = image_shell.getSize();
    this->texture_shell.loadFromImage(this->image_shell);
    this->sprite_shell.setTexture(this->texture_shell);
    this->sprite_shell.setPosition(vector_poz);
}

void Arrow::setTexture(const std::string &texture)
{    
    sf::Image im;
    im.loadFromFile(texture);
    this->texture_shell.loadFromImage(im);
    this->sprite_shell.setTexture(this->texture_shell);
}