#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <time.h>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

struct {
	Texture chunli_bg_t;
	Texture chunli_bg_animation_t;
}texture_elements;

void bg_animation(int &time_accum, Sprite &chunli_bg_fishermen, Sprite &chunli_bg_mom) {
	if (time_accum <= 3000) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 360, 480, 360));
		chunli_bg_mom.setTextureRect(IntRect(640, 0, 440, 400));
	}
	else if (3000 < time_accum && time_accum < 3800) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 0, 480, 360));
		chunli_bg_mom.setTextureRect(IntRect(640, 400, 440, 400));
	}
	else if (3800 <= time_accum && time_accum <= 5000) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 720, 480, 360));
		chunli_bg_mom.setTextureRect(IntRect(640, 800, 440, 400));
	}
	else if (time_accum > 5000) {
		time_accum = 0;
	}
}

int main() {

	Time dt;

	int time_accum = 0;
	srand(time(0));

	VideoMode vm(1920, 1080);
	RenderWindow window1(vm, "New Game", Style::Fullscreen);

	(texture_elements.chunli_bg_t).loadFromFile("ChunLi Sprites/final-chunli-bg2.png");
	(texture_elements.chunli_bg_animation_t).loadFromFile("ChunLi Sprites/bg_elements.png");

	Sprite chunli_bg_s;
	Sprite chunli_bg_fishermen;
	Sprite chunli_bg_mom;

	chunli_bg_s.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_fishermen.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_bg_mom.setTexture(texture_elements.chunli_bg_animation_t);

	chunli_bg_s.setTextureRect(IntRect(0, 160, 1920, 1080));

	Clock clock1;
	while (window1.isOpen()) {
		dt = clock1.restart();
		time_accum = time_accum + dt.asMilliseconds();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};
		chunli_bg_fishermen.setPosition(800, 420);
		chunli_bg_mom.setPosition(280, 380);
		bg_animation(time_accum,chunli_bg_fishermen,chunli_bg_mom);
		window1.clear();
		window1.draw(chunli_bg_s);
		window1.draw(chunli_bg_fishermen);
		window1.draw(chunli_bg_mom);
		window1.display();
	}
}


