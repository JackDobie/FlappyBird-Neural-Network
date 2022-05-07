#include "Bird.hpp"

namespace Sonar
{
	Bird::Bird(GameDataRef data, Chrom* c) : _data(data)
	{
		_animationIterator = 0;

		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 1"));
		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 2"));
		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 3"));
		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 4"));

		_birdSprite.setTexture(_animationFrames.at(_animationIterator));

		_birdSprite.setPosition((_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2));
	
		_birdState = BIRD_STATE_STILL;

		sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width / 2, _birdSprite.getGlobalBounds().height / 2);

		_birdSprite.setOrigin(origin);

		_rotation = 0;

		_shouldFlap = false;

		_neuralNet = new NeuralNetwork(c);

		_alive = true;

		_chrom = c;

		_waitingToOutput = false;

		SetScore(0);
	}

	Bird::~Bird()
	{
		if (_neuralNet) delete(_neuralNet);
		if (_chrom) delete(_chrom);
	}

	void Bird::Reset()
	{
		_animationIterator = 0;
		_birdSprite.setTexture(_animationFrames.at(_animationIterator));
		_birdSprite.setPosition((_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2));
		_rotation = 0;
		_shouldFlap = false;
		_alive = true;
		SetScore(0);
		_movementClock.restart();
		_birdState = BIRD_STATE_STILL;
		_waitingToOutput = false;
	}

	void Bird::Draw()
	{
		if(_alive)
			_data->window.draw(_birdSprite);
	}

	void Bird::Animate(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size())
		{
			if (_animationIterator < _animationFrames.size() - 1)
			{
				_animationIterator++;
			}
			else
			{
				_animationIterator = 0;
			}

			_birdSprite.setTexture(_animationFrames.at(_animationIterator));

			_clock.restart();
		}
	}

	void Bird::Update(float dt)
	{
		//static int it = 0;
		switch (_birdState)
		{
		case BIRD_STATE_FALLING:
			//it = 0;
			_birdSprite.move(0, GRAVITY * dt);

			_rotation += ROTATION_SPEED * dt;

			if (_rotation > 25.0f)
			{
				_rotation = 25.0f;
			}

			_birdSprite.setRotation(_rotation);
			break;

		case BIRD_STATE_FLYING:
			//std::cout << it++ << std::endl;
			_birdSprite.move(0, -FLYING_SPEED * dt);

			if (_birdSprite.getPosition().y < 0)
			{
				sf::Vector2f v = _birdSprite.getPosition();
				v.y = 0;
				_birdSprite.setPosition(v);
			}

			_rotation -= ROTATION_SPEED * dt;

			if (_rotation < -25.0f)
			{
				_rotation = -25.0f;
			}

			_birdSprite.setRotation(_rotation);
			break;

		default:
			break;
		}
		
		if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
		{
			_movementClock.restart();
			_birdState = BIRD_STATE_FALLING;
		}
	}

	void Bird::Tap()
	{
		_movementClock.restart();
		_birdState = BIRD_STATE_FLYING;
	}

	void Bird::Calculate(std::vector<float> inputs)
	{
		_neuralNet->Update();
		_neuralNet->Calculate(inputs);
	}

	/*void Bird::Mutate()
	{
		_neuralNet.Mutate(_score);
	}*/

	const sf::Sprite &Bird::GetSprite() const
	{
		return _birdSprite;
	}

	void Bird::GetHeight(int& x, int& y)
	{
		sf::Vector2f v = _birdSprite.getPosition();
		x = (int)v.x;
		y = (int)v.y;
	}
}