#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Sonar
{
	class HUD
	{
	public:
		HUD(GameDataRef data);
		~HUD();

		void Draw();
		void UpdateScore(int score);
		void UpdateBirdCount(int count);
		void UpdateGen(int gen);

	private:
		GameDataRef _data;

		sf::Text _scoreText;
		sf::Text _birdsText;
		sf::Text _genText;

	};
}