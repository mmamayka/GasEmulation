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

#define W 300
#define H 300

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

void DrawCells(sf::RenderTarget& target, Phys::CellManager const& manager) {
	float cell_width = manager.getCellSize();
	float cell_height = manager.getCellSize();

	size_t ncellsx = manager.getNumCellsX();
	size_t ncellsy = manager.getNumCellsY();

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(cell_width, cell_height));

	float V0 = cell_width * cell_height;

	for(size_t i = 0; i < ncellsx; ++i)
		for(size_t j = 0; j < ncellsy; ++j) {
			float V = manager.getCountAt(i, j, 0) * Math::PId * Phys::R * Phys::R;
			float part = V / V0;
			if(part > 1.f)
				part = 1.f;

			//part *= 50;

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

	CellManager cell_manager(400.0, 300.0, R * 8, D * 8, g.data(), W * H);

	g.clear();

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
		
		DrawCells(window, cell_manager);

		window.display();

	}
}
