#ifndef _BUTTON_
#define _BUTTON_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <string>
#include <stack>
#include <map>

class Button
{
private:
	;
	// position of the button
	sf::Vector2f vec_poz;
	// size of the button
	sf::Vector2u vector_size_button;

	// sf atributes
	sf::Image image_shell;
	sf::Texture texture_shell;
	sf::Sprite sprite_shell;

	sf::Image image_shadow;
	sf::Texture texture_shadow;
	sf::Sprite sprite_shadow;

	sf::Image image_click;
	sf::Texture texture_click;
	sf::Sprite sprite_click;

public:
	sf::Text *text;
	sf::Text *text_name;

	// bool value
	bool Enabled = true;
	bool TextPut = false;
	bool BTN_ACTIVE = false;
	bool BTN_WAIT = true;
	bool BTN_Anim = true;
	// Constructor and destructor
	Button(sf::Vector2f vector_poz, const std::string &image, const std::string &shadow, const std::string &click);
	~Button() = default;

	// getters
	sf::Image getImage() { return this->image_shell; }
	sf::Texture getTexture() { return this->texture_shell; }
	sf::Sprite getSprite() { return this->sprite_shell; }

	sf::Image getShadowImage() { return this->image_shadow; }
	sf::Texture getShadowTexture() { return this->texture_shadow; }
	sf::Sprite getShadowSprite() { return this->sprite_shadow; }

	sf::Sprite getClickSprite() { return this->sprite_click; }

	sf::Vector2f getVector_poz() { return this->vec_poz; }
	sf::Vector2u getSize() { return this->vector_size_button; }

	sf::Sprite getSpriteShadow() { return this->sprite_shadow; }

	// setters
	void setTexture(const std::string &texture);
	void setTexture(const sf::Image &image) { this->texture_shell.loadFromImage(image); }
	void setVector_poz(sf::Vector2f f) { this->sprite_shell.setPosition(f); }
	void setVector_poz(float fo) { this->sprite_shell.setPosition(sf::Vector2f(fo, fo)); }
};

#endif