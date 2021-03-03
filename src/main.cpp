#include "tests.hpp"
#include "gasunit.hpp"

#include <SFML/Graphics.hpp>

int main() 
{
	using namespace Phys;
	using namespace Math;

	Tests::RunAllTests();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Gas");

	GasUnit g1(Vec4(-50, -100, 0), Vec4(250, 170, 0));
	GasUnit g2(Vec4(150, 100, 0), Vec4(-220, 190, 0));

	sf::CircleShape g1shape;
	sf::CircleShape g2shape;
	sf::RectangleShape cshape;
	cshape.setSize(sf::Vector2f(400.f, 400.f));
	cshape.setPosition(200.f, 200.f);
	cshape.setOrigin(200.f, 200.f);
	cshape.setFillColor(sf::Color::White);

	g1shape.setRadius(R);
	g1shape.setOrigin(R, R);
	g1shape.setFillColor(sf::Color::Green);
	g2shape.setRadius(R);
	g2shape.setOrigin(R, R);
	g2shape.setFillColor(sf::Color::Red);

	ContainerCollider collider(200.f, 200.f, 200.f);

	sf::Clock clock;

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}

		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		g1.move(dt);
		g2.move(dt);
		ResolveCollision(g1, g2);
		ResolveCollision(g1, collider);
		ResolveCollision(g2, collider);

		g1shape.setPosition(g1.pos().x + 200, g1.pos().y + 200);
		g2shape.setPosition(g2.pos().x + 200, g2.pos().y + 200);

		window.clear();

		window.draw(cshape);
		window.draw(g1shape);
		window.draw(g2shape);

		window.display();
	}
}
