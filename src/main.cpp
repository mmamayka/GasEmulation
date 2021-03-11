#include "tests.hpp"
#include "gasunit.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include <type_traits>

template<typename Type>
class LinearAllocator {
public:
	LinearAllocator(size_t max_elements);
	~LinearAllocator();

private:
	Type* memory_;
};

void DrawVec(sf::RenderTarget& target, Math::Vec4 where, Math::Vec4 vec, 
	sf::Color c = sf::Color::Magenta) 
{
	sf::VertexArray a(sf::PrimitiveType::Lines, 2);
	a[0].position.x = where.x;
	a[0].position.y = where.y;
	a[0].color = c;

	a[1].position.x = where.x + vec.x;
	a[1].position.y = where.y + vec.y;
	a[1].color = c;

	target.draw(a);
}

sf::Color linear(float v) {
	sf::Color r;

	r.r = (unsigned char)(255 * v);
	r.g = (unsigned char)(255 * (1 - v));
	r.b = 0;
	return r;
}

Math::Vec4 rand_vel(float len) {
	float phi = (float)(rand() % 1000 - 500) / 500 * Math::PI;
	return Math::Vec4(cosf(phi), sinf(phi), 0.f) * len;
}

#define MV 40

#define W 165
#define H 20

float GetPart(float mk, float T, float v, float step) {
	float A = mk / (2 * T);
	float sqrtA = Math::Sqrt(A);

	float vend = v + step;

	return Math::Sqrt(Math::PI) / 2 * (erff(vend * sqrtA) - erff(v * sqrtA)) +
		2 * sqrtA * (exp(-v * v * A) * v - exp(-vend * vend * A) * vend);
}

int main() 
{
	using namespace Phys;
	using namespace Math;

	float step = 1e-2f;
	size_t N = 1000000;
	size_t total = 0;
	for(float v = 0.f; v < 3.f; v += step) {
		float count = (float)(GetPart(1e-4f, 397.f, v, step) * (float)N);
		total += count;

		std::cout << "vel = " << v << " n = " << count  << std::endl;
	}
	std::cout << "total = " << total << std::endl;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Gas");
	window.setFramerateLimit(60);

	Container gas_container(1e-4f, 1e-4f, 1e-4f, 1, 273.17);

	GasUnit* g = (GasUnit*)malloc(sizeof(GasUnit) * W * H);
	for(size_t i = 0; i < W; ++i) {
		for(size_t j = 0; j < H; ++j) {
			new (g + i * H + j) GasUnit(Vec4((float)(i * D * 1.2f) - 400.f + D, (float)(j * D * 1.2f) - 300.f + D, 0.f),
				rand_vel((float)(rand() % MV)));
		}
	}


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

	sf::Clock clock;


	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}

		float dt = clock.getElapsedTime().asSeconds();
		// std::cout << "FPS = " << 1.f / dt << std::endl;
		// std::cout << dt << std::endl;
		clock.restart();

		for(size_t i = 0; i < W * H; ++i)
			g[i].move(dt);

		bool found = true;
		while(found) {
			found = false;

			for(size_t i = 0; i < W * H; ++i) {
				for(size_t j = 0; j < W * H; ++j) {
					if(i == j)
						continue;

					ResolveCollision(g[i], g[j]);
				}
			}
		}
		for(size_t i = 0; i < W * H; ++i)
			ResolveCollision(g[i], collider);

		window.clear();

		window.draw(cshape);

		float E = 0.f;
		for(size_t i = 0; i < W * H; ++i) {
			E += g[i].vel().sqlen();

			gshape.setFillColor(linear(g[i].vel().len() / MV));
			gshape.setPosition(g[i].pos().x + 400, g[i].pos().y + 300);
			window.draw(gshape);
		}
		// std::cout << E << std::endl;
		//
		window.display();

	}

	free(g);
}
