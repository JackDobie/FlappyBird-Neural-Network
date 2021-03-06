#pragma once

#include "InputManager.hpp"

namespace Sonar
{
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect playButtonRect((int)object.getPosition().x, (int)object.getPosition().y, (int)object.getGlobalBounds().width, (int)object.getGlobalBounds().height);

			if (playButtonRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}

		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}

	bool InputManager::GetKeyPressed(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}
	bool InputManager::GetKeyDown(sf::Event e, sf::Keyboard::Key key)
	{
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == key)
			{
				return true;
			}
		}
		return false;
	}
}