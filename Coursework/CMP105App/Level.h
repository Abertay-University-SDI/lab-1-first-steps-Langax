#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	enum class KeyState { UP, DOWN, LEFT, RIGHT };

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void spawnFood();
	// Default variables for level class.
	sf::CircleShape m_player;
	sf::CircleShape m_food;
	int m_speed = 200;
	KeyState m_previousKey;
	sf::Vector2f m_distance;
	bool m_isGameOver = false;
	int m_score;
	int m_scoreGoal = 10;
	float m_gameTime;

};