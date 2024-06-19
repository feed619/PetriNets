#include "Interface.h"

Interface::Interface()
{
    this->image_frame.loadFromFile("image/FrameNew.png");
    this->texture_frame.loadFromImage(this->image_frame);
    this->sprite_frame.setTexture(this->texture_frame);

    this->sprite_frame.setPosition(0, 0);

    this->image_frame_shadow.loadFromFile("image/shadow.png");
    this->texture_frame_shadow.loadFromImage(this->image_frame_shadow);
    this->sprite_frame_shadow.setTexture(this->texture_frame_shadow);
}

sf::Sprite Interface::getSprite()
{
    return this->sprite_frame;
}
