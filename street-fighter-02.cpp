#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <time.h>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

struct {
	Texture bg_t;
}texture_elements;

Clock clock1;
Time dt;
void bg_animation();

int main() {
	srand(time(0));

	VideoMode vm(1920, 1080);
	RenderWindow window1(vm, "New Game", Style::Fullscreen);

	(texture_elements.bg_t).loadFromFile("ChunLi Sprites/final-chunli-bg2.png");
	Sprite chunli_bg_s;
	chunli_bg_s.setTexture(texture_elements.bg_t);
	chunli_bg_s.setTextureRect(IntRect(0, 160, 1920, 1080));

	while (window1.isOpen()) {
		dt = clock1.restart();
		int fps = 1 / dt.asSeconds();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};
		window1.clear();
		window1.draw(chunli_bg_s);
		window1.display();
	}
}

void bg_animation() {
	 
}
