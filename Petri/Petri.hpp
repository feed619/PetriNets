#pragma once
#include "../pakage/init.hpp"
#include "../pakage/arrow/Arrow.cpp"

class Petri
{
private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;

	bool HEAD = false;
	bool END = false;
	int variable = 0;
	bool active = false;

public:
	int QUAN = 0;
	int quantity_in_arrows = 0;
	int quantity_out_arrows = 0;

	// position of the button
	sf::Vector2f vec_poz;
	// size of the button
	sf::Vector2u vector_size_button;

	bool Enabled = true;
	bool TextPut = false;
	bool BTN_ACTIVE = false;
	bool BTN_WAIT = true;
	bool Petri_work = true;
	bool Active_square = false;

	std::list<Arrow *> InboxArrows;
	std::list<Arrow *> ExitArrows;

	std::list<Petri *> In_Squares;
	std::list<Petri *> In_Circles;
	std::list<Petri *> out_Circles;




	sf::Text *text;
	std::string string_Text = "0";

	Petri(sf::Vector2f vector_poz, const std::string &image, int variable);
	~Petri();

	// getters
	sf::Image getImage() { return this->image; }
	sf::Texture getTexture() { return this->texture; }
	sf::Sprite getSprite() { return this->sprite; }

	sf::Vector2f getVector_poz() { return this->sprite.getPosition(); }
	sf::Vector2u getSize() { return this->vector_size_button; }

	// setters
	void setTexture(const std::string &texture);
	void setTexture(const sf::Image &image) { this->texture.loadFromImage(image); }
	void setVector_poz(sf::Vector2f f) { this->sprite.setPosition(f); }
	void setVector_poz(float fo) { this->sprite.setPosition(sf::Vector2f(fo, fo)); }
};