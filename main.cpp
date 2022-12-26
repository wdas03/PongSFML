#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;

void handleBallCollision(sf::CircleShape ball, sf::RectangleShape paddle);

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int PADDLE_HEIGHT = 200;
const int PADDLE_WIDTH = 20;
const float PADDLE_SPEED = 0.4f;
const float BALL_SPEED = 0.4f;
const int BALL_RADIUS = 10;

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong!");

	sf::RectangleShape playerPaddle(sf::Vector2f((float) PADDLE_WIDTH, (float) PADDLE_HEIGHT));
	playerPaddle.setFillColor(sf::Color::White);
	playerPaddle.setPosition(0, 0);

	sf::RectangleShape cpuPaddle(sf::Vector2f((float) PADDLE_WIDTH, (float) PADDLE_HEIGHT));
	cpuPaddle.setFillColor(sf::Color::White);
	cpuPaddle.setPosition(WINDOW_WIDTH - PADDLE_WIDTH, 0);

	sf::CircleShape ball((float) BALL_RADIUS);
	ball.setFillColor(sf::Color::Blue);
	ball.setPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT/ 2.0);

	float velocity_x = BALL_SPEED;
	float velocity_y = 0.f;

	sf::Clock clock;
	sf::Time timer;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playerPaddle.getPosition().y <= WINDOW_HEIGHT - PADDLE_HEIGHT) {
			playerPaddle.move(0.f, PADDLE_SPEED);
			//cout << "y: " << playerPaddle.getPosition().y << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerPaddle.getPosition().y >= 0.f) {
			playerPaddle.move(0.f, -PADDLE_SPEED);
		}

		if (ball.getPosition().x >= WINDOW_WIDTH) {
			velocity_x = -BALL_SPEED;
		}
		else if (ball.getPosition().x <= 0.f) {
			velocity_x = BALL_SPEED;
			//handleBallCollision(velocity_x, velocity_y, ball, playerPaddle);
		}

		ball.move(velocity_x, velocity_y);
	
		window.clear(sf::Color::Black);
		window.draw(playerPaddle);
		window.draw(cpuPaddle);
		window.draw(ball);
		window.display();
	}
}

void handleBallCollision(float &velocity_x, float &velocity_y, sf::CircleShape ball, sf::RectangleShape paddle) {
	sf::Vector2f ballPosition = ball.getPosition();
	float ball_x = ballPosition.x;
	float ball_y = ballPosition.y;

	sf::Vector2f paddlePosition = paddle.getPosition();
	float paddle_x = paddlePosition.x;
	float paddle_y = paddlePosition.y;

	if (ball_y >= paddle_y && ball_y <= paddle_y + (float) PADDLE_HEIGHT) {
		cout << "Good" << endl;
	}
	else {
		cout << "Miss" << endl;
	}
}
