#include "Level.h"
#include <ctime>

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{	
	srand(time(0));
	// initialise game objects
	m_player.setPosition({ m_window.getSize().x / 2.f,m_window.getSize().y / 2.f });
	m_player.setFillColor(sf::Color::Cyan);
	m_player.setRadius(15);

	m_food.setRadius(10);
	m_food.setFillColor(sf::Color::Red);
	spawnFood();

	m_score = 0;
	m_gameTime = 0.f;

}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::W)) {
		m_previousKey = KeyState::UP;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A)) {
		m_previousKey = KeyState::LEFT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S)) {
		m_previousKey = KeyState::DOWN;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::D)) {
		m_previousKey = KeyState::RIGHT;
	}
}

// Update game objects
void Level::update(float dt)
{
	if (m_score >= m_scoreGoal) {
		spawnFood();
	}
	if (m_isGameOver) {
		return;
	}

	m_gameTime += dt;

	switch (m_previousKey) {
	case KeyState::UP:
		m_player.move({ 0.0f, -m_speed * dt });
		break;
	case KeyState::DOWN:
		m_player.move({ 0.0f, m_speed * dt });
		break;
	case KeyState::LEFT:
		m_player.move({ -m_speed * dt, 0.0f });
		break;
	case KeyState::RIGHT:
		m_player.move({ m_speed * dt, 0.0f });
	}

	if (m_player.getPosition().x > m_window.getSize().x || m_player.getPosition().x < 0 || m_player.getPosition().y > m_window.getSize().y || m_player.getPosition().y < 0) {
		std::cout << "GAME OVER\n";
		std::cout << "You scored: " << m_score << "\n";
		std::cout << "You lasted: " << m_gameTime << " seconds\n";
		m_isGameOver = true;
	}

	float x_dist = (m_player.getPosition().x + m_player.getRadius()) - (m_food.getPosition().x + m_food.getRadius());
	float y_dist = (m_player.getPosition().y + m_player.getRadius()) - (m_food.getPosition().y + m_food.getRadius());

	float squared_dist = (x_dist * x_dist) + (y_dist * y_dist);
	float radii_sum = m_player.getRadius() + m_food.getRadius();
	if (squared_dist < radii_sum * radii_sum){
		spawnFood();
		m_speed *= 1.1;
		m_score++;
	}


	if (m_score >= m_scoreGoal) {
		spawnFood();
		m_player.setRadius(150);
		std::cout << "You win!\n";
		std::cout << "You scored: " << m_score << "\n";
		std::cout << "It took you: " << m_gameTime << " seconds\n";
		m_isGameOver = true;
	}
}

// Render level
void Level::render()
{


	beginDraw();
	m_window.draw(m_player);
	m_window.draw(m_food);

	endDraw();
}


void Level::spawnFood() {
	float x = rand() % m_window.getSize().x;
	float y = rand() % m_window.getSize().y;

	m_food.setPosition({ x, y });
}
