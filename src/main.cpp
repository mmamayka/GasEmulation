#include "tests.hpp"
#include "gasunit.hpp"
#include "collision.hpp"
#include "maxwell.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#define W 250
#define H 250

#define GW 100
#define GH 100

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
			float V = cells[i * GH + j].units.size() * Math::PI * Phys::R * Phys::R;

			sf::Color c((V / V0) * 255, 0, 0);

			shape.setFillColor(c);
			shape.setPosition(i * cell_width, j * cell_height);
			target.draw(shape);
		}
}

void CollideCells(Cell& a, Cell& b) {
	for(auto ua : a.units)
		for(auto ub : b.units) {
			if(ua == ub)
				continue;
			ResolveCollision(*ua, *ub);
		}
}

int main() 
{
	using namespace Phys;
	using namespace Math;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Gas");
	window.setFramerateLimit(60);

	// GasUnit* g = new GasUnit[W * H];
	std::vector<GasUnit> g(W * H);

	// Cell* cells = new Cell[GW * GH];
	std::vector<Cell> cells(GW * GH);

	Phys::SetupPositionDistribution(g.data(), W * H, 200.f, 200.f, Phys::R);
	float maxv = Phys::SetupVelocityDistribution(g.data(), W * H, 1.f, 100.f, 1e-2f);

	sf::CircleShape gshape;
	sf::RectangleShape cshape;
	cshape.setSize(sf::Vector2f(800.f, 600.f));
	cshape.setPosition(400.f, 300.f);
	cshape.setOrigin(400.f, 300.f);
	cshape.setFillColor(sf::Color::White);

	gshape.setRadius(R);
	gshape.setOrigin(R, R);
	gshape.setFillColor(sf::Color::Green);

	ContainerCollider collider(400.f, 300.f, 200.f);

	window.setFramerateLimit(120);

	float dt = D / maxv;

	float cell_width = 800.f / GW;
	float cell_height = 600.f / GH;


	// XXXX
	// XXXX
	// XXOX
	// XXXX
	// XXXX
	
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

		for(size_t i = 0; i < W * H; ++i) {
			g[i].move(dt);
			MATH_VEC4_ASSERT(g[i].pos());
			MATH_VEC4_ASSERT(g[i].vel());
		}

		for(size_t i = 0; i < W * H; ++i)
			ResolveCollision(g[i], collider);

		for(size_t i = 0; i < GW * GH; ++i) {
			cells[i].units.clear();
		}

		for(size_t i = 0; i < W * H; ++i) {
			float fidx = ((g[i].pos().x + 400.f) / cell_width);
			float fidy = ((g[i].pos().y + 300.f) / cell_height);

			if(fidx < 0.f) fidx = 0.f;
			if(fidy < 0.f) fidy = 0.f;

			size_t idx = fidx;
			size_t idy = fidy;

			if(idx >= GW) idx = GW - 1;
			if(idy >= GH) idy = GH - 1;

			cells.at(idx * GH + idy).units.push_back(g.data() + i);

		}

		for(size_t cx = 0; cx < GW; ++cx)
			for(size_t cy = 0; cy < GH; ++cy) {
				Cell& main = cells.at(cx * GH + cy);


				for(size_t cxx = (cx == 0 ? 0 : cx - 1); cxx <= (cx == GW - 1 ? cx : cx + 1); cxx++) {
					for(size_t cyy = (cy == 0 ? 0 : cy - 1); cyy <= (cy == GH - 1 ? cy : cy + 1); cyy++) {
						// std::cout << cx << ' ' << cy << ", " << cxx << ' ' << cyy << std::endl;
						CollideCells(main, cells.at(cxx * GH + cyy));
					}
				}
				
			
			}
#if 0
		for(size_t cx = 0; cx < GW - 1; ++cx)
			for(size_t cy = 1; cy < GH - 1; ++cy) {
				// Cell& main = cells[(cx + 0) * GH + (cy + 0)];
				// Cell& c1 = cells[(cx + 1) * GH + (cy - 1)];
				// Cell& c2 = cells[(cx + 1) * GH + (cy + 1)];
				// Cell& c3 = cells[(cx + 1) * GH + (cy + 0)];
				// Cell& c4 = cells[(cx + 0) * GH + (cy + 1)];
				Cell& main = cells.at((cx + 0) * GH + (cy + 0));
				Cell& c1 = cells.at((cx + 1) * GH + (cy - 1));
				Cell& c2 = cells.at((cx + 1) * GH + (cy + 1));
				Cell& c3 = cells.at((cx + 1) * GH + (cy + 0));
				Cell& c4 = cells.at((cx + 0) * GH + (cy + 1));

				CollideCells(main, main);
				CollideCells(main, c1);
				CollideCells(main, c2);
				CollideCells(main, c3);
				CollideCells(main, c4);
			}
		// cy = 0
		for(size_t cx = 0; cx < GW - 1; ++cx) {
			Cell& main = cells[(cx + 0) * GH + (0)];
			Cell& c1 = cells[(cx + 1) * GH + (0)];
			Cell& c2 = cells[(cx + 1) * GH + (1)];
			Cell& c3 = cells[(cx + 0) * GH + (1)];

			CollideCells(main, main);
			CollideCells(main, c1);
			CollideCells(main, c2);
			CollideCells(main, c3);
		}

		// cy = GH - 1
		for(size_t cx = 0; cx < GW - 1; ++cx) {
				Cell& main = cells[(cx + 0) * GH + (GH - 1)];
				Cell& c1 = cells[(cx + 1) * GH + (GH - 2)];
				Cell& c2 = cells[(cx + 0) * GH + (GH - 1)];

				CollideCells(main, main);
				CollideCells(main, c1);
				CollideCells(main, c2);
		}

		// cx = GW - 1
		for(size_t cy = 0; cy < GH - 1; ++cy) {
				Cell& main = cells[(GW - 1) * GH + (cy + 0)];
				Cell& c1 = cells[(GW - 1) * GH + (cy + 1)];

				CollideCells(main, main);
				CollideCells(main, c1);
		}

		CollideCells(cells[GW * GH - 1], cells[GW * GH - 1]);
#endif
		/*k
		for(size_t i = 0; i < W * H; ++i) {
			for(size_t j = 0; j < W * H; ++j) {
				if(i == j)
					continue;

				ResolveCollision(g[i], g[j]);
			}
		}
		*/

		// while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
		// while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));


		window.clear();
		
		window.draw(cshape);

		DrawCells(window, cells);

		// DrawGrid(window, sf::Vector2u(800, 600));

		/*
		float E = 0.f;
		for(size_t i = 0; i < W * H; ++i) {
			E += g[i].vel().sqlen();

			gshape.setFillColor(sf::Color::Red);
			gshape.setPosition(g[i].pos().x + 400, g[i].pos().y + 300);
			window.draw(gshape);
		}
		*/


		window.display();

	}

	// delete[] g;
	// delete[] cells;
}
