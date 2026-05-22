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
	Texture chunli_char_t;
}texture_elements;

constexpr auto ANYKEY = 1 << 0;
constexpr auto SPACE = 1 << 1;
constexpr auto L_ARRROW = 1 << 2;

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

void bg_upward_animation(Sprite& chunli_bg_s, Sprite& chunli_bg_mom, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_hen, int& key_press_state, int& time_accum_2, int& random_bool_store) {
	while ((time_accum_2 >= 10) && ((random_bool_store & (1 << 0)) == (1 << 0))) {
		chunli_bg_s.setTextureRect(IntRect(0, (chunli_bg_s.getTextureRect().top - 5), 1920, 1080));
		chunli_bg_fishermen.setPosition(800, chunli_bg_fishermen.getPosition().y + 5);
		chunli_bg_mom.setPosition(280, chunli_bg_mom.getPosition().y + 5);
		chunli_bg_hen.setPosition(1360, chunli_bg_hen.getPosition().y + 5);
		time_accum_2 = time_accum_2 - 10;
		if (chunli_bg_s.getTextureRect().top == 0) {
			random_bool_store = random_bool_store & (~(1 << 0));
		}
	}
	while ((time_accum_2 >= 10) && ((random_bool_store & (1 << 0)) != (1 << 0))) {
		chunli_bg_s.setTextureRect(IntRect(0, (chunli_bg_s.getTextureRect().top + 5), 1920, 1080));
		chunli_bg_fishermen.setPosition(800, chunli_bg_fishermen.getPosition().y - 5);
		chunli_bg_mom.setPosition(280, chunli_bg_mom.getPosition().y - 5);
		chunli_bg_hen.setPosition(1360, chunli_bg_hen.getPosition().y - 5);
		time_accum_2 = time_accum_2 - 10;
		if (chunli_bg_s.getTextureRect().top == 160) {
			random_bool_store = key_press_state | (1 << 1);
		}
	}
	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~SPACE);
	}
}

void chunli_idle_animation(Sprite &chunli_char) {
	chunli_char.setTextureRect(IntRect(16, 34, 72, 85));
	chunli_char.setPosition(272,544);
}

int main() {

	int time_accum = 0;
	int time_accum_2 = 0;
	int key_press_state = 0;
	int random_bool_store = 0;	//first 2 digits for bg_upward_animation()

	srand(time(0));

	VideoMode vm(1920, 1080);
	RenderWindow window1(vm, "New Game", Style::Fullscreen);

	(texture_elements.chunli_bg_t).loadFromFile("ChunLi Sprites/final-chunli-bg2.png");
	(texture_elements.chunli_bg_animation_t).loadFromFile("ChunLi Sprites/bg_elements.png");
	(texture_elements.chunli_char_t).loadFromFile("ChunLi Sprites/ChunLi.png");

	(texture_elements.chunli_bg_t).setSmooth(false);
	(texture_elements.chunli_bg_animation_t).setSmooth(false);
	(texture_elements.chunli_char_t).setSmooth(false);

	Sprite chunli_bg_s;
	Sprite chunli_bg_fishermen;
	Sprite chunli_bg_mom;
	Sprite chunli_bg_hen;
	Sprite chunli_char;

	Sprite* drawing[] = { &chunli_bg_s,&chunli_bg_fishermen,&chunli_bg_mom,&chunli_bg_hen };

	chunli_bg_s.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_fishermen.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_bg_mom.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_bg_hen.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_char.setTexture(texture_elements.chunli_char_t);

	chunli_bg_s.setTextureRect(IntRect(0, 160, 1920, 1080));
	
	chunli_char.setScale(5.0f, 5.0f);
	chunli_bg_fishermen.setPosition(800, 420);
	chunli_bg_mom.setPosition(280, 380);
	chunli_bg_hen.setPosition(1360, 580);

	Clock clock1;
	while (window1.isOpen()) {
		time_accum = time_accum + (clock1.restart()).asMilliseconds();
		time_accum_2 = time_accum_2 + (clock1.restart()).asMilliseconds();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};

		if (Keyboard::isKeyPressed(Keyboard::Space) && (key_press_state&SPACE)!=SPACE) {
			key_press_state = key_press_state | SPACE;
			random_bool_store = random_bool_store | (1 << 0);
			random_bool_store = random_bool_store & (~(1 << 1));
			time_accum_2 = 0;
		}

		if ((key_press_state & SPACE) == SPACE) {
			bg_upward_animation(chunli_bg_s, chunli_bg_mom, chunli_bg_fishermen, chunli_bg_hen, key_press_state, time_accum_2, random_bool_store);
		}

		bg_animation(time_accum,chunli_bg_fishermen,chunli_bg_mom,chunli_bg_hen);
		chunli_idle_animation(chunli_char);

		window1.clear();
		for (Sprite* i : drawing) {
			window1.draw(*i);
		}
		window1.display();
	}
}


