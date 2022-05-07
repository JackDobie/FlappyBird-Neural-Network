#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

#define SPLASH_STATE_SHOW_TIME 0.0

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/sky.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/sky.png"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/sky.png"

#define GAME_TITLE_FILEPATH "Resources/res/title.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/PlayButton.png"

#define PIPE_UP_FILEPATH "Resources/res/PipeUp.png"
#define PIPE_DOWN_FILEPATH "Resources/res/PipeDown.png"

#define LAND_FILEPATH "Resources/res/land.png"

#define BIRD_FRAME_1_FILEPATH "Resources/res/bird-01.png"
#define BIRD_FRAME_2_FILEPATH "Resources/res/bird-02.png"
#define BIRD_FRAME_3_FILEPATH "Resources/res/bird-03.png"
#define BIRD_FRAME_4_FILEPATH "Resources/res/bird-04.png"

#define SCORING_PIPE_FILEPATH "Resources/res/InvisibleScoringPipe.png"

#define FLAPPY_FONT_FILEPATH "Resources/fonts/FlappyFont.ttf"

#define GAME_OVER_TITLE_FILEPATH "Resources/res/Game-Over-Title.png"
#define GAME_OVER_BODY_FILEPATH "Resources/res/Game-Over-Body.png"

#define BRONZE_MEDAL_FILEPATH "Resources/res/Bronze-Medal.png"
#define SILVER_MEDAL_FILEPATH "Resources/res/Silver-Medal.png"
#define GOLD_MEDAL_FILEPATH "Resources/res/Gold-Medal.png"
#define PLATINUM_MEDAL_FILEPATH "Resources/res/Platinum-Medal.png"

#define HIT_SOUND_FILEPATH "Resources/audio/Hit.wav"
#define POINT_SOUND_FILEPATH "Resources/audio/Point.wav"
#define WING_SOUND_FILEPATH "Resources/audio/Wing.wav"

#define PIPE_MOVEMENT_SPEED (200.0f * TIME_SCALE)
#define PIPE_SPAWN_FREQUENCY (1.5f / TIME_SCALE) // default: 1.5f
#define PIPE_RANDOM_OFFSET false

#define BIRD_ANIMATION_DURATION (0.4f / TIME_SCALE)

#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3

#define GRAVITY (350.0f * TIME_SCALE)
#define FLYING_SPEED (350.0f * TIME_SCALE)

#define FLYING_DURATION (0.25f / TIME_SCALE)

#define ROTATION_SPEED (100.0f * TIME_SCALE)

#define TIME_SCALE 2.0f

enum GameStates
{
	eReady,
	ePlaying,
	eGameOver
};

#define FLASH_SPEED 1500.0f

#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f

#define BRONZE_MEDAL_SCORE 0
#define SILVER_MEDAL_SCORE 5
#define GOLD_MEDAL_SCORE 25
#define PLATINUM_MEDAL_SCORE 100

#define BIRD_COUNT 350

#define GA_PARENT_COUNT 10

#define NN_LAYERS 2
#define NN_NEURONS 3

#define ALLOW_PLAYER_TAP false

// if this is false, it will output on reset instead
#define OUTPUT_ON_UPDATE false