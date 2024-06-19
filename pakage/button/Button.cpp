#include "Button.hpp"

Button::Button(sf::Vector2f vector_poz,const std::string &image, const std::string &shadow, const std::string &click)
{

    this->vec_poz = vector_poz;

    this->image_shell.loadFromFile(image);
    this->image_shadow.loadFromFile(shadow);
    this->image_click.loadFromFile(click);

    this->vector_size_button = image_shell.getSize();

    this->texture_shell.loadFromImage(this->image_shell);
    this->texture_shadow.loadFromImage(this->image_shadow);
    this->texture_click.loadFromImage(this->image_click);

    this->sprite_shell.setTexture(this->texture_shell);
    this->sprite_shadow.setTexture(this->texture_shadow);
    this->sprite_click.setTexture(this->texture_click);

    this->sprite_shell.setPosition(vector_poz);
    this->sprite_shadow.setPosition(vector_poz);
    this->sprite_click.setPosition(vector_poz);

    
}

void Button::setTexture(const std::string &texture)
{    
    sf::Image im;
    im.loadFromFile(texture);
    this->texture_shell.loadFromImage(im);
    this->sprite_shell.setTexture(this->texture_shell);
}
