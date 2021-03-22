#include <iostream>

#include "tests.hpp"
#include "gasunit.hpp"
#include "collision.hpp"
#include "distribution.hpp"
#include "maxwell.hpp"
#include "debug.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#define W 200
#define H 200

#define GW 200
#define GH 150

void DrawGrid(sf::RenderTarget& target, sf::Vector2u size) {
	size_t width = size.x / GW;
	size_t height = size.y / GH;

	sf::VertexArray lines(sf::PrimitiveType::Lines, (GW + GH) * 2);

	size_t npoint = 0;
	for(size_t i = 0; i < GW; ++i, npoint += 2) {
		lines[npoint].position.x = i * width;
		lines[npoint].position.y = 0;
		lines[npoint].color = sf::Color::Black;

		lines[npoint + 1].position.x = i * width;
		lines[npoint + 1].position.y = size.y;
		lines[npoint + 1].color = sf::Color::Black;
	}

	for(size_t i = 0; i < GH; ++i, npoint += 2) {
		lines[npoint].position.y = i * height;
		lines[npoint].position.x = 0;
		lines[npoint].color = sf::Color::Black;

		lines[npoint + 1].position.y = i * height;
		lines[npoint + 1].position.x = size.x;
		lines[npoint + 1].color = sf::Color::Black;
	}

	target.draw(lines);
}

struct Cell {
	std::vector<Phys::GasUnit*> units;
};

void DrawCells(sf::RenderTarget& target, std::vector<Cell> const& cells) {
	float cell_width = 800.f / GW;
	float cell_height = 600.f / GH;

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(cell_width, cell_height));

	float V0 = cell_width * cell_height;

	for(size_t i = 0; i < GW; ++i)
		for(size_t j = 0; j < GH; ++j) {
			float V = cells[i * GH + j].units.size() * Math::PId * Phys::R * Phys::R;
			float part = V / V0;
			if(part > 1.f)
				part = 1.f;

			sf::Color c(part * 255.0, 0, 0);

			shape.setFillColor(c);
			shape.setPosition(i * cell_width, j * cell_height);
			target.draw(shape);
		}
}

int main() 
{
	using namespace Phys;
	using namespace Math;

	Tests::RunAllTests();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Gas");
	window.setFramerateLimit(60);

	// GasUnit* g = new GasUnit[W * H];
	std::vector<GasUnit> g(W * H);

	// Cell* cells = new Cell[GW * GH];
	Phys::SetupPositionDistribution(g.data(), W * H, 200.f, 200.f, D);
	double maxv = Phys::SetupVelocityDistribution(g.data(), W * H, 1.f, 100.f, 1e-5);

	CellManager cell_manager(400.0, 300.0, R, D, g.data(), W * H);

	g.clear();

	sf::CircleShape gshape;
	sf::RectangleShape cshape;
	cshape.setSize(sf::Vector2f(800.f, 600.f));
	cshape.setPosition(400.f, 300.f);
	cshape.setOrigin(400.f, 300.f);
	cshape.setFillColor(sf::Color::White);

	gshape.setRadius(R);
	gshape.setOrigin(R, R);
	gshape.setFillColor(sf::Color::Green);

	window.setFramerateLimit(120);

	double dt = D / maxv;
	std::cout << dt << std::endl;

	float real_time = 0.f;
	sf::Clock clock;
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		real_time += dt;

		std::cout << "FPS = " << 1.f / time << std::endl;
		std::cout << "TIME = " << real_time << std::endl;

		cell_manager.update(dt);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			window.close();

		window.clear();
		
		// DrawCells(window, cells);

		// DrawGrid(window, sf::Vector2u(800, 600));

		float E = 0.f;
		for(size_t i = 0; i < W * H; ++i) {
			E += g[i].vel().sqlen();

			gshape.setFillColor(sf::Color::Red);
			gshape.setPosition(g[i].pos().x + 400, g[i].pos().y + 300);
			window.draw(gshape);
		}


		window.display();

	}

	// delete[] g;
	// delete[] cells;
}
