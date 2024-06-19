#ifndef _ANIMATE_BTN_
#define _ANIMATE_BTN_

#include "../pakage/init.hpp"

class AnimateButton
{
public:
	AnimateButton() = default;
	~AnimateButton() = default;
	// mouse position animation main buttons
	void MouseAnimateButtons(const sf::Vector2f &mouse_position, sf::RenderWindow &window,
							 std::vector<Button *> &vector_buttons);
	// mouse position animation free buttons
	void MouseAnimateFreeButtons(const sf::Vector2f &mouse_position, sf::RenderWindow &window,
								 std::vector<std::vector<Button *>> &vector_free_buttons, int sizeMatrix);
	// Clic animation of nuttons
	void MouseButtonLeftClick(sf::RenderWindow &window, Button &button, int &i);
};

#endif