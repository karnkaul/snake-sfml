#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Constants.h"
#include "Snake.h"
#include "Food.h"
#include "Game.h"

int main() {

    // Game Window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake!", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    // initial window position relative to the desktop
    window.setPosition(sf::Vector2i(50,50));

    Game game;
    Snake snake(400,300);
    Food food;
    food.spawn();
    sf::Text scoreText;
    sf::Font font;
    font.loadFromFile("../fonts/GeosansLight.ttf");

    // Game loop
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        sf::Event event;

        // just testing out Keyboard
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
//            window.close();

        // event pending ?
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){

                switch(event.key.code){
                case sf::Keyboard::Key::A:
                case sf::Keyboard::Key::Left:
                    if(snake.getDirection() == Direction::RIGHT)
                        break;
                    snake.setDirection(Direction::LEFT);
                    break;
                case sf::Keyboard::Key::Right:
                case sf::Keyboard::Key::D:
                    if(snake.getDirection() == Direction::LEFT)
                        break;
                    snake.setDirection(Direction::RIGHT);
                    break;

                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::W:
                    if(snake.getDirection() == Direction::DOWN)
                        break;
                    snake.setDirection(Direction::UP);
                    break;
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down:
                    if(snake.getDirection() == Direction::UP)
                        break;
                    snake.setDirection(Direction::DOWN);
                    break;
                 default:
                    break;
                }
            }
        }

        // Drawing score
        game.setupScore(scoreText, font, snake);
        window.draw(scoreText);

        // For testing spawn points
        // food.spawn();

        // Drawing borders
        game.drawBorders(window);

        // if the snake has eaten the food
        if(snake.getHead().getGlobalBounds().intersects(food.getGlobalBounds())){
            snake++;
            food.spawn();
        }

        snake.draw(window);

        window.draw(food);

        // if the snake collides with itself or with the borders
        if(snake.isDead()
                || snake.getHead().getGlobalBounds().intersects(game.mLeftBorder.getGlobalBounds())
                || snake.getHead().getGlobalBounds().intersects(game.mRightBorder.getGlobalBounds())
                || snake.getHead().getGlobalBounds().intersects(game.mUpBorder.getGlobalBounds())
                || snake.getHead().getGlobalBounds().intersects(game.mDownBorder.getGlobalBounds())){

            while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))){
                sf::Text gameOverText;
                game.setupGameOver(gameOverText, font, snake);
                window.draw(gameOverText);
                window.display();
            }
                window.close();

        }
        snake.move();

        // Drawing the score text lastly because I want it to be on top of anything else
        // I'm also drawing it after checking if the snake is dead, which implies that the score won't be printed on the screen on game over
        window.draw(scoreText);

        window.display();
    }

    return 0;
}
