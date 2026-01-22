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

	// Default variables for level class.
	sf::CircleShape m_player;
	int m_speed = 200;
	KeyState m_previousKey;

};