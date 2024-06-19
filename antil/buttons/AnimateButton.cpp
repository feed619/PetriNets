#include "AnimateButton.hpp"

void AnimateButton::MouseAnimateButtons(const sf::Vector2f &mouse_position,
                                        sf::RenderWindow &window,
                                        std::vector<Button *> &vector_buttons)
{
    for (int i = 1; i < vector_buttons.size(); ++i)
    {
        if (vector_buttons[i]->getSprite().getGlobalBounds().contains(mouse_position))
        {
            window.draw(vector_buttons[i]->getShadowSprite());
        }
    }
}

void AnimateButton::MouseAnimateFreeButtons(const sf::Vector2f &mouse_position, sf::RenderWindow &window,
                                            std::vector<std::vector<Button *>> &vector_free_buttons, int sizeMatrix)
{
    for (int i = 0; i < sizeMatrix; ++i)
    {
        for (int j = 0; j < sizeMatrix + 1; ++j)
        {
            if (vector_free_buttons[i][j]->getSprite().getGlobalBounds().contains(mouse_position))
            {
                window.draw(vector_free_buttons[i][j]->getShadowSprite());
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    window.draw(vector_free_buttons[i][j]->getClickSprite());
                }
            }
        }
    }
}

void AnimateButton::MouseButtonLeftClick(sf::RenderWindow &window, Button &button, int &i)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and !button.BTN_ACTIVE)
    {
        window.draw(button.getSpriteShadow());
        button.BTN_ACTIVE = true;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        button.BTN_ACTIVE = false;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        window.draw(button.getSpriteShadow());
    }
}
