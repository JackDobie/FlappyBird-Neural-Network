#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace Sonar
{
	class Pipe
	{
	public:
		Pipe(GameDataRef data);
		~Pipe();

		void SpawnBottomPipe();
		void SpawnTopPipe();
		void SpawnInvisiblePipe();
		void SpawnScoringPipe();
		void MovePipes(float dt);
		void DrawPipes();
		void RandomisePipeOffset();
		void PickPipeOffset(int score);

		void Reset();

		const std::vector<sf::Sprite> &GetSprites() const;
		std::vector<sf::Sprite> &GetScoringSprites();
	private:
		GameDataRef _data;
		std::vector<sf::Sprite> _pipeSprites;
		std::vector<sf::Sprite> _scoringPipes;

		int _landHeight;
		int _pipeSpawnYOffset;

		std::vector<int> _offsets;
	};
}