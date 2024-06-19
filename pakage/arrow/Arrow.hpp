
#ifndef _Arrow_
#define _Arrow_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <string>
#include <stack>
#include <map>

class Arrow
{
private:
	;
	// position of the button

	//size of the button
	sf::Vector2u vector_size_button;

	// sf atributes
	sf::Image image_shell;
	sf::Texture texture_shell;
	sf::Sprite sprite_shell;


public:
	sf::Vector2f vec_poz;
	// sf::Vector2f* vec_poz_square;
	// sf::Vector2f* vec_poz_circle;
	sf::Vector2f vec_poz_square;
	sf::Vector2f vec_poz_circle;


	sf::Text* text;
	//bool value
	bool Enabled = true;
	bool TextPut = false;
	bool BTN_ACTIVE = false;
	bool BTN_WAIT = true;

	float dX = 0;
	float dY = 0;
	// Constructor and destructor
	Arrow(sf::Vector2f vector_poz, const std::string &image);
	~Arrow() = default;

	// getters 
	sf::Image getImage() { return this->image_shell; }
	sf::Texture getTexture() { return this->texture_shell; }
	sf::Sprite getSprite() { return this->sprite_shell; }

	sf::Vector2f getVector_poz() { return this->vec_poz; }
	// sf::Vector2f getVector_poz_square() { return this->vec_poz_square; }
	sf::Vector2u getSize() { return this->vector_size_button; }
	
	//setters
	void setTexture(const std::string &texture);
	void setTexture(const sf::Image &image) { this->texture_shell.loadFromImage(image); }
	void setVector_poz(sf::Vector2f f) { this->sprite_shell.setPosition(f); }
	void setVector_poz(float fo) { this->sprite_shell.setPosition(sf::Vector2f(fo, fo)); }
	void setRotation( float fo) { this->sprite_shell.setRotation(fo); }
	void setScale (sf::Vector2f vec) { this->sprite_shell.setScale(vec); }

};

#endif