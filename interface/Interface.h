#ifndef _INTER_
#define _INTER_


#include "../pakage/init.hpp"

class Interface
{
private:
    sf::Image image_frame;
    sf::Texture texture_frame;
    sf::Sprite sprite_frame;

    sf::Image image_frame_shadow;
    sf::Texture texture_frame_shadow;
    sf::Sprite sprite_frame_shadow;
    
public:
    Interface();
    sf::Sprite getSprite();
};

#endif

