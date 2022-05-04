#include "HUD.hpp"

#include <string>

namespace Sonar
{
	HUD::HUD(GameDataRef data) : _data(data)
	{
		_scoreText.setFont(this->_data->assets.GetFont("Flappy Font"));
		_scoreText.setString("0");
		_scoreText.setCharacterSize(128);
		_scoreText.setFillColor(sf::Color::White);
		_scoreText.setOrigin(sf::Vector2f(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2));
		_scoreText.setPosition(sf::Vector2f((float)_data->window.getSize().x / 2, (float)_data->window.getSize().y / 5));

		_birdsText.setFont(this->_data->assets.GetFont("Flappy Font"));
		_birdsText.setString("Birds: 0");
		_birdsText.setCharacterSize(32);
		_birdsText.setFillColor(sf::Color::White);
		_birdsText.setOrigin(sf::Vector2f(0.0f, 0.0f));
		_birdsText.setPosition(sf::Vector2f(0.0f, 0.0f));

		_genText.setFont(this->_data->assets.GetFont("Flappy Font"));
		_genText.setString("Generation: 1");
		_genText.setCharacterSize(32);
		_genText.setFillColor(sf::Color::White);
		_genText.setOrigin(sf::Vector2f(0.0f, 0.0f));
		_genText.setPosition(sf::Vector2f((float)_data->window.getSize().x / 2, 0.0f));
	}

	HUD::~HUD()
	{
	}

	void HUD::Draw()
	{
		_data->window.draw(_scoreText);
		_data->window.draw(_birdsText);
		_data->window.draw(_genText);
	}

	void HUD::UpdateScore(int score)
	{
		_scoreText.setString(std::to_string(score));
	}

	void HUD::UpdateBirdCount(int count)
	{
		_birdsText.setString("Birds: " + std::to_string(count));
	}

	void HUD::UpdateGen(int gen)
	{
		_genText.setString("Generation: " + std::to_string(gen + 1));
	}
}