#pragma once

#include "SFML\Graphics.hpp"

namespace Sonar
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

		sf::Vector2i GetMousePosition(sf::RenderWindow &window);

		bool GetKeyPressed(sf::Keyboard::Key key);
		bool GetKeyDown(sf::Event e, sf::Keyboard::Key key);
	};
}