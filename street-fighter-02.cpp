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

void bg_animation(int &time_accum, Sprite &chunli_bg_fishermen, Sprite &chunli_bg_mom, Sprite &chunli_bg_hen) {
	if ((time_accum <= 1500) || (time_accum >= 1900 && time_accum < 2900)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 592, 160, 160));
	}
	else if ((time_accum >= 1500 && time_accum < 1700) || (time_accum >= 2900 && time_accum < 3100) ) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 752, 160, 160));
	}
	else if ((time_accum >= 1700 && time_accum < 1900) || (time_accum >= 3100 && time_accum <= 3400)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 912, 160, 160));
	}

	if ((time_accum <= 1500) || (time_accum>2000 && time_accum<=3000)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 360, 480, 360));
	}
	else if ((time_accum > 1500 && time_accum <= 1750)|| (time_accum>3000 && time_accum<=3200)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 0, 480, 360));
	}
	else if ((time_accum > 1750 && time_accum <= 2000)|| (time_accum>3200)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 720, 480, 360));
	}

	if (time_accum <= 3000) {
		chunli_bg_mom.setTextureRect(IntRect(640, 0, 440, 400));
	}
	else if (3000 < time_accum && time_accum <= 3200) {
		chunli_bg_mom.setTextureRect(IntRect(640, 400, 440, 400));
	}
	else if (3200 < time_accum && time_accum <=3400) {
		chunli_bg_mom.setTextureRect(IntRect(640, 800, 440, 400));
	}
	if (time_accum>3400){
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
	Sprite chunli_bg_hen;

	Sprite* drawing[] = { &chunli_bg_s,&chunli_bg_fishermen,&chunli_bg_mom,&chunli_bg_hen };

	chunli_bg_s.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_fishermen.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_bg_mom.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_bg_hen.setTexture(texture_elements.chunli_bg_animation_t);

	chunli_bg_s.setTextureRect(IntRect(0, 160, 1920, 1080));

	chunli_bg_fishermen.setPosition(800, 420);
	chunli_bg_mom.setPosition(280, 380);
	chunli_bg_hen.setPosition(1360, 580);

	Clock clock1;
	while (window1.isOpen()) {
		dt = clock1.restart();
		time_accum = time_accum + dt.asMilliseconds();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};

		bg_animation(time_accum,chunli_bg_fishermen,chunli_bg_mom,chunli_bg_hen);

		window1.clear();
		for (Sprite* i : drawing) {
			window1.draw(*i);
		}
		window1.display();
	}
}


