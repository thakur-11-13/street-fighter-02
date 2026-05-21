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

constexpr auto SPACE=1<<0;
constexpr auto L_ARRROW=1<<1;

void bg_animation(int &time_accum, Sprite &chunli_bg_fishermen, Sprite &chunli_bg_mom, Sprite &chunli_bg_hen) {
	if ((time_accum <= 1500) || (time_accum > 1950 && time_accum <= 2950)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 592, 160, 160));
	}
	else if ((1500 < time_accum && time_accum <= 1650) || (1800 < time_accum && time_accum <= 1950) || (2950 < time_accum && time_accum <= 3100) || (3250 < time_accum && time_accum <= 3400)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 752, 160, 160));
	}
	else if ((time_accum > 1650 && time_accum <= 1800) || (time_accum > 3100 && time_accum <= 3250)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 912, 160, 160));
	}

	if ((time_accum <= 1000) || (time_accum > 1900 && time_accum <= 2900)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 360, 480, 360));
	}
	else if ((1000 < time_accum && time_accum <= 1180) || (1360 < time_accum && time_accum <= 1540) || (1720 < time_accum && time_accum <= 1900) || (2900 < time_accum && time_accum <= 3080) || (3260 < time_accum && time_accum <= 3400)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 0, 480, 360));
	}
	else if ((1180 < time_accum && time_accum <= 1360) || (1540 < time_accum && time_accum <= 1720) || (3080 < time_accum && time_accum <= 3260)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 720, 480, 360));
	}

	if ((time_accum <= 2000) || (3100 < time_accum && time_accum <= 3400)) {
		chunli_bg_mom.setTextureRect(IntRect(640, 0, 440, 400));
	}
	else if ((2000 < time_accum && time_accum <= 2200) || (3000 < time_accum && time_accum <= 3100)) {
		chunli_bg_mom.setTextureRect(IntRect(640, 400, 440, 400));
	}
	else if (2200 < time_accum && time_accum <= 3000) {
		chunli_bg_mom.setTextureRect(IntRect(640, 800, 440, 400));
	}
	if (time_accum>3400){
		time_accum = 0;
	}
}

void bg_upward_animation(int &upward_animation_tracker,Sprite &chunli_bg_s,Sprite &chunli_bg_mom,Sprite &chunli_bg_fishermen,Sprite &chunli_bg_hen,int &key_press_state,int &counter) {
	if (counter <= 32) {
		chunli_bg_s.setTextureRect(IntRect(0, (160 - 5 * counter), 1920, 1080));
		chunli_bg_fishermen.setPosition(800, 420 + (5 * counter));
		chunli_bg_mom.setPosition(280, 380 + (5 * counter));
		chunli_bg_hen.setPosition(1360, 580 + (5 * counter));
	}
	else if (32 < counter && counter <= 64) {
		chunli_bg_s.setTextureRect(IntRect(0,5 * (counter-32), 1920, 1080));
		chunli_bg_fishermen.setPosition(800, 580 - (5 * (counter-32)));
		chunli_bg_mom.setPosition(280, 540 - (5 * (counter-32)));
		chunli_bg_hen.setPosition(1360, 740 - (5 * (counter-32)));
	}
	else if (counter > 64) {
		key_press_state = key_press_state & (~SPACE);
	}
}

int main() {

	Time dt;

	int time_accum = 0;
	int time_accum_2 = 0;
	int upward_animation_tracker = 0;
	int key_press_state = 0;
	int counter=1;

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
		time_accum_2 = time_accum_2 + dt.asMilliseconds();
		if (time_accum_2 >= 11) {
			counter = counter + 1;
			time_accum_2 = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};

		if (Keyboard::isKeyPressed(Keyboard::Space) && (key_press_state&SPACE)!=SPACE) {
			key_press_state = key_press_state | SPACE;
			time_accum_2 = 0;
			counter = 1;
		}

		if (key_press_state == SPACE) {
			bg_upward_animation(upward_animation_tracker, chunli_bg_s,chunli_bg_mom,chunli_bg_fishermen,chunli_bg_hen, key_press_state,counter);
		}

		bg_animation(time_accum,chunli_bg_fishermen,chunli_bg_mom,chunli_bg_hen);

		window1.clear();
		for (Sprite* i : drawing) {
			window1.draw(*i);
		}
		window1.display();
	}
}


