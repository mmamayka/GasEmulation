#include <iostream>

#include "tests.hpp"
#include "distribution.hpp"
#include "cellmanager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#define W 400
#define H 400

namespace Phys {
	class ColliderUnit;

	class ContainerPortal {
	public:


	private:
		ColliderUnit* unit1_;
		ColliderUnit* unit2_;
		Math::PolygonD polygon_;
	};

	class ContainerPart {
	public:
		ContainerPart(Math::PolygonD const* polygons, size_t count);
		ContainerPart(std::initializer_list<Math::PolygonD> const& polygons);

	private:
		Math::PolygonD* polygons_;
		size_t polygon_count_;

		ContainerPortal* portals_;
		size_t portal_count_;

		CellManager cell_manager_;
	};

	class Container {
	public:

	private:
		ContainerPart* parts_;
		size_t count_;
	};
}

void DrawPolygon(sf::RenderTarget& target, Math::PolygonD const& polygon) {

}

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
	Phys::SetupPositionDistribution(g.data(), W * H, 300.f, 200.f, D);
	double maxv = Phys::SetupVelocityDistribution(g.data(), W * H, 1.f, 100000.f, 1e-5);

	CellManager cell_manager(400.0, 300.0, R * 5, D * 5, g.data(), W * H);

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
