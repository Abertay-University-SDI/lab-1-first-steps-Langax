#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setPosition({ m_window.getSize().x / 2.f,m_window.getSize().y / 2.f });
	m_player.setFillColor(sf::Color::Cyan);
	m_player.setRadius(15);
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
		m_player.setPosition({ m_window.getSize().x / 2.f,m_window.getSize().y / 2.f});
	}
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}

