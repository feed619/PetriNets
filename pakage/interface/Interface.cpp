#include "Interface.h"

Interface::Interface()
{
    this->image_frame.loadFromFile("image/White.png");

    this->texture_frame.loadFromImage(this->image_frame);
    this->sprite_frame.setTexture(this->texture_frame);

    this->sprite_frame.setPosition(0, 0);
}

sf::Sprite Interface::getSprite()
{
    return this->sprite_frame;
}
