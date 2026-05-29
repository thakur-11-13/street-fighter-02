#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <time.h>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

struct {
	Texture chunli_bg_t;
	Texture chunli_bg_animation_t;
	Texture chunli_char_t;
}texture_elements;

constexpr auto ANYKEY = 1 << 0;
constexpr auto SPACE = 1 << 1;
constexpr auto LEFT = 1 << 2;
constexpr auto RIGHT = 1 << 3;

void bg_animation(int& time_accum, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_mom, Sprite& chunli_bg_hen) {
	if ((time_accum <= 1500) || (time_accum > 1950 && time_accum <= 2950)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 592, 160, 160));
	}
	else if ((1500 < time_accum && time_accum <= 1650) || (1800 < time_accum && time_accum <= 1950) || (2950 < time_accum && time_accum <= 3100) || (3250 < time_accum && time_accum <= 3400)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 752, 160, 160));
	}
	else if ((time_accum > 1650 && time_accum <= 1800) || (time_accum > 3100 && time_accum <= 3250)) {
		chunli_bg_hen.setTextureRect(IntRect(1264, 912, 160, 160));
	};

	if ((time_accum <= 1000) || (time_accum > 1900 && time_accum <= 2900)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 360, 480, 360));
	}
	else if ((1000 < time_accum && time_accum <= 1180) || (1360 < time_accum && time_accum <= 1540) || (1720 < time_accum && time_accum <= 1900) || (2900 < time_accum && time_accum <= 3080) || (3260 < time_accum && time_accum <= 3400)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 0, 480, 360));
	}
	else if ((1180 < time_accum && time_accum <= 1360) || (1540 < time_accum && time_accum <= 1720) || (3080 < time_accum && time_accum <= 3260)) {
		chunli_bg_fishermen.setTextureRect(IntRect(0, 720, 480, 360));
	};

	if ((time_accum <= 2000) || (3100 < time_accum && time_accum <= 3400)) {
		chunli_bg_mom.setTextureRect(IntRect(640, 0, 440, 400));
	}
	else if ((2000 < time_accum && time_accum <= 2200) || (3000 < time_accum && time_accum <= 3100)) {
		chunli_bg_mom.setTextureRect(IntRect(640, 400, 440, 400));
	}
	else if (2200 < time_accum && time_accum <= 3000) {
		chunli_bg_mom.setTextureRect(IntRect(640, 800, 440, 400));
	};
	if (time_accum > 3400) {
		time_accum = 0;
	};
}


void bg_upward_animation(Sprite& chunli_bg_s, Sprite& chunli_bg_mom, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_hen, int& key_press_state, int& time_accum_2, int& time_accum_3, int& random_bool_store, Sprite& chunli_char, int& frame_counter, FloatRect& damage_box, Sprite& char_shadow) {

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {
		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 15);
		damage_box.left = chunli_char.getPosition().x;
		damage_box.top = 5 * (109 - damage_box.height) + chunli_char.getPosition().y;
	}
	else {
		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y + 15);
		damage_box.left = chunli_char.getPosition().x;
		damage_box.top = 5 * (109 - damage_box.height) + chunli_char.getPosition().y;
	}
	while ((time_accum_2 >= 10) && ((random_bool_store & (1 << 0)) == (1 << 0))) {
		chunli_bg_s.setTextureRect(IntRect(0, (chunli_bg_s.getTextureRect().top - 5), 1920, 1080));
		chunli_bg_fishermen.setPosition(800, chunli_bg_fishermen.getPosition().y + 5);
		chunli_bg_mom.setPosition(280, chunli_bg_mom.getPosition().y + 5);
		chunli_bg_hen.setPosition(1360, chunli_bg_hen.getPosition().y + 5);
		char_shadow.setPosition(char_shadow.getPosition().x, char_shadow.getPosition().y + 5);
		time_accum_2 = time_accum_2 - 10;

		frame_counter = frame_counter + 1;

		if (frame_counter >= 7 && frame_counter <= 14) {
			chunli_char.setTextureRect(IntRect(74, 2340, 74, 109));
			damage_box.width = 47;
			damage_box.height = 109;
		}
		else if (15 <= frame_counter && frame_counter <= 19) {
			chunli_char.setTextureRect(IntRect(148, 2340, 74, 109));
			damage_box.width = 50;
			damage_box.height = 84;
		}
		else if (20 <= frame_counter && frame_counter <= 26) {
			chunli_char.setTextureRect(IntRect(222, 2340, 74, 109));
			damage_box.width = 52;
			damage_box.height = 75;
		}
		else if (27 <= frame_counter && frame_counter <= 32) {
			chunli_char.setTextureRect(IntRect(296, 2340, 74, 109));
			damage_box.width = 57;
			damage_box.height = 65;
		}

		if (chunli_bg_s.getTextureRect().top == 0) {
			random_bool_store = random_bool_store & (~(1 << 0));
			frame_counter = 1;
		}
	}
	while ((time_accum_2 >= 10) && ((random_bool_store & (1 << 0)) != (1 << 0))) {
		chunli_bg_s.setTextureRect(IntRect(0, (chunli_bg_s.getTextureRect().top + 5), 1920, 1080));
		chunli_bg_fishermen.setPosition(800, chunli_bg_fishermen.getPosition().y - 5);
		chunli_bg_mom.setPosition(280, chunli_bg_mom.getPosition().y - 5);
		chunli_bg_hen.setPosition(1360, chunli_bg_hen.getPosition().y - 5);
		char_shadow.setPosition(char_shadow.getPosition().x, char_shadow.getPosition().y - 5);
		time_accum_2 = time_accum_2 - 10;

		frame_counter = frame_counter + 1;

		if (frame_counter >= 2 && frame_counter <= 7) {

			chunli_char.setTextureRect(IntRect(222, 2340, 74, 109));
			damage_box.width = 52;
			damage_box.height = 75;
			damage_box.left = chunli_char.getPosition().x;
			damage_box.top = 5 * (109 - damage_box.height) + chunli_char.getPosition().y;
		}
		else if (8 <= frame_counter && frame_counter <= 14) {
			chunli_char.setTextureRect(IntRect(148, 2340, 74, 109));
			damage_box.width = 50;
			damage_box.height = 84;
			damage_box.left = chunli_char.getPosition().x;
			damage_box.top = 5 * (109 - damage_box.height) + chunli_char.getPosition().y;
		}
		else if (15 <= frame_counter && frame_counter <= 30) {
			chunli_char.setTextureRect(IntRect(74, 2340, 74, 109));
			damage_box.width = 47;
			damage_box.height = 109;
			damage_box.left = chunli_char.getPosition().x;
			damage_box.top = 5 * (109 - damage_box.height) + chunli_char.getPosition().y;
		}
		else if (31 <= frame_counter && frame_counter <= 32) {
			chunli_char.setTextureRect(IntRect(0, 2340, 74, 109));
			damage_box.width = 74;
			damage_box.height = 81;
			damage_box.left = chunli_char.getPosition().x;
			damage_box.top = 5 * (109 - damage_box.height) + chunli_char.getPosition().y;
		}

		if (chunli_bg_s.getTextureRect().top == 160) {
			random_bool_store = random_bool_store | (1 << 1);
		}
	}
	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~SPACE);
		chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
		chunli_char.setPosition(chunli_char.getPosition().x, 527);
		damage_box.left = chunli_char.getPosition().x;
		damage_box.top = 527;
		damage_box.width = 72;
		damage_box.height = 87;
		time_accum_3 = 0;
	}
}

void jump_right() {

}

void chunli_idle_animation(Sprite& chunli_char, int& time_accum_3) {

	if (time_accum_3 >= 160 && (chunli_char.getTextureRect()).left >= 256) {
		chunli_char.setTextureRect(IntRect(-64, 32, 72, 87));
	}
	while (time_accum_3 >= 160 && ((chunli_char.getTextureRect()).left) < 256) {
		time_accum_3 = time_accum_3 - 160;
		chunli_char.setTextureRect(IntRect(((chunli_char.getTextureRect()).left) + 80, 32, 80, 87));
	}
}
void chunli_walk_f_animation(Sprite& chunli_char, int& time_accum_3, int& frame_counter, FloatRect& damage_box) {

	while (time_accum_3 >= 60) {
		time_accum_3 = time_accum_3 - 60;
		frame_counter = frame_counter + 1;
	}

	switch (frame_counter) {
	case 1:
		chunli_char.setTextureRect(IntRect(0, 164, 78, 84));
		chunli_char.setOrigin(77 / 2, 83);
		break;
	case 2:
		chunli_char.setTextureRect(IntRect(81, 161, 71, 87));
		chunli_char.setOrigin(70 / 2, 86);
		break;
	case 3:
		chunli_char.setTextureRect(IntRect(162, 160, 65, 88));
		chunli_char.setOrigin(64 / 2, 87);
		break;
	case 4:
		chunli_char.setTextureRect(IntRect(243, 159, 62, 89));
		chunli_char.setOrigin(61 / 2, 88);
		break;
	case 5:
		chunli_char.setTextureRect(IntRect(324, 160, 67, 88));
		chunli_char.setOrigin(66 / 2, 87);
		break;
	case 6:
		chunli_char.setTextureRect(IntRect(405, 161, 76, 87));
		chunli_char.setOrigin(75 / 2, 86);
		break;
	case 7:
		chunli_char.setTextureRect(IntRect(486, 162, 81, 86));
		chunli_char.setOrigin(80 / 2, 85);
		break;
	case 8:
		chunli_char.setTextureRect(IntRect(567, 161, 76, 87));
		chunli_char.setOrigin(75 / 2, 86);
		break;
	case 9:
		chunli_char.setTextureRect(IntRect(648, 160, 67, 88));
		chunli_char.setOrigin(66 / 2, 87);
		break;
	case 10:
		chunli_char.setTextureRect(IntRect(729, 159, 62, 89));
		chunli_char.setOrigin(61 / 2, 88);
		break;
	case 11:
		chunli_char.setTextureRect(IntRect(810, 160, 65, 88));
		chunli_char.setOrigin(64 / 2, 87);
		break;
	case 12:
		chunli_char.setTextureRect(IntRect(891, 161, 71, 87));
		chunli_char.setOrigin(70 / 2, 86);
		frame_counter = 0;
		break;
	}
}
void chunli_walk_b_animation(Sprite& chunli_char, int& time_accum_3, int& frame_counter, FloatRect& damage_box) {

	while (time_accum_3 >= 60) {
		time_accum_3 = time_accum_3 - 60;
		frame_counter = frame_counter + 1;
	}

	switch (frame_counter) {
	case 1:
		chunli_char.setTextureRect(IntRect(0,293,73,86));
		chunli_char.setOrigin(72 / 2, 85);
		break;
	case 2:
		chunli_char.setTextureRect(IntRect(73,290,63,89));
		chunli_char.setOrigin(62 / 2, 88);
		break;
	case 3:
		chunli_char.setTextureRect(IntRect(146,289,60,90));
		chunli_char.setOrigin(59 / 2, 89);
		break;
	case 4:
		chunli_char.setTextureRect(IntRect(219,288,63,91));
		chunli_char.setOrigin(62 / 2, 90);
		break;
	case 5:
		chunli_char.setTextureRect(IntRect(292,289,64,90));
		chunli_char.setOrigin(63 / 2, 89);
		break;
	case 6:
		chunli_char.setTextureRect(IntRect(365,290,65,89));
		chunli_char.setOrigin(64 / 2, 88);
		break;
	case 7:
		chunli_char.setTextureRect(IntRect(438,291,72,88));
		chunli_char.setOrigin(71 / 2, 87);
		break;
	case 8:
		chunli_char.setTextureRect(IntRect(511,290,65,89));
		chunli_char.setOrigin(64 / 2, 88);
		break;
	case 9:
		chunli_char.setTextureRect(IntRect(584,289,64,90));
		chunli_char.setOrigin(63 / 2, 89);
		break;
	case 10:
		chunli_char.setTextureRect(IntRect(651,288,63,91));
		chunli_char.setOrigin(62 / 2, 90);
		break;
	case 11:
		chunli_char.setTextureRect(IntRect(730,289,60,90));
		chunli_char.setOrigin(59 / 2, 89);
		break;
	case 12:
		chunli_char.setTextureRect(IntRect(803,290,63,89));
		chunli_char.setOrigin(62 / 2, 88);
		frame_counter = 0;
		break;
	}
}

int main() {

	float dt;

	int time_accum = 0;
	int time_accum_2 = 0;
	int time_accum_3 = 0;
	int frame_counter = 1;
	int key_press_state = 0;
	float dist_accum = 0;
	int random_bool_store = 0;	//first 2 digits for bg_upward_animation()

	srand(time(0));

	VideoMode vm(1920, 1080);
	RenderWindow window1(vm, "New Game", Style::Fullscreen);
	window1.setVerticalSyncEnabled(true);

	(texture_elements.chunli_bg_t).loadFromFile("ChunLi Sprites/final-chunli-bg2.png");
	(texture_elements.chunli_bg_animation_t).loadFromFile("ChunLi Sprites/bg_elements.png");
	(texture_elements.chunli_char_t).loadFromFile("ChunLi Sprites/ChunLi2.png");

	(texture_elements.chunli_bg_t).setSmooth(false);
	(texture_elements.chunli_bg_animation_t).setSmooth(false);
	(texture_elements.chunli_char_t).setSmooth(false);

	Sprite chunli_bg_s;
	Sprite chunli_bg_fishermen;
	Sprite chunli_bg_mom;
	Sprite chunli_bg_hen;
	Sprite chunli_char;
	Sprite char_shadow;
	FloatRect damage_box;

	chunli_bg_s.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_fishermen.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_bg_mom.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_bg_hen.setTexture(texture_elements.chunli_bg_animation_t);
	chunli_char.setTexture(texture_elements.chunli_char_t);
	char_shadow.setTexture(texture_elements.chunli_char_t);

	chunli_bg_s.setTextureRect(IntRect(0, 160, 1920, 1080));
	chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
	char_shadow.setTextureRect(IntRect(14, 135, 74, 12));

	chunli_char.setOrigin(71 / 2, 86);
	char_shadow.setOrigin(73 / 2, 11 / 2);

	chunli_bg_fishermen.setPosition(800, 420);
	chunli_bg_mom.setPosition(280, 380);
	chunli_bg_hen.setPosition(1360, 580);
	chunli_char.setPosition(505, 961);
	char_shadow.setPosition(505, 961);

	chunli_char.setScale(5.0f, 5.0f);
	char_shadow.setScale(5.0f, 5.0f);

	Clock clock1;
	while (window1.isOpen()) {

		dt = (clock1.restart()).asMilliseconds();

		time_accum = time_accum + dt;
		time_accum_2 = time_accum_2 + dt;
		time_accum_3 = time_accum_3 + dt;

		key_press_state = key_press_state & (~ANYKEY);

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};

		//SPACE WITHOUT DIRECTION

		if (Keyboard::isKeyPressed(Keyboard::Space) && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | SPACE;
			random_bool_store = random_bool_store | (1 << 0);
			random_bool_store = random_bool_store & (~(1 << 1));
			time_accum_2 = 0;
			time_accum_3 = 0;
			if ((key_press_state & RIGHT) != RIGHT && (key_press_state & LEFT) != LEFT) {
				chunli_char.setTextureRect(IntRect(0, 2340, 74, 109));
				chunli_char.setPosition(chunli_char.getPosition().x, 427);
				damage_box.width = 74;
				damage_box.height = 81;
				damage_box.left = chunli_char.getPosition().x;
				damage_box.top = 5 * (109 - damage_box.height) + chunli_char.getPosition().y;
				frame_counter = 1;
			}
		};
		if (Keyboard::isKeyPressed((Keyboard::Right)) && (key_press_state & RIGHT) != RIGHT && (key_press_state & LEFT) != LEFT && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | RIGHT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter = 1;
			chunli_char.setPosition(chunli_char.getPosition().x + 3, 961);
			char_shadow.setPosition(char_shadow.getPosition().x - 40, char_shadow.getPosition().y);
		}
		else if ((!(Keyboard::isKeyPressed((Keyboard::Right)))) && ((key_press_state & RIGHT) == RIGHT)) {
			key_press_state = key_press_state & (~RIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
			chunli_char.setOrigin(71 / 2, 86);
			chunli_char.setPosition(chunli_char.getPosition().x - 3, 961);
			char_shadow.setPosition(char_shadow.getPosition().x + 40, char_shadow.getPosition().y);
			dist_accum = 0;
		};
		if (Keyboard::isKeyPressed((Keyboard::Left)) && (key_press_state & LEFT) != LEFT && (key_press_state & RIGHT) != RIGHT && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | LEFT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter = 1;
			chunli_char.setPosition(chunli_char.getPosition().x + 2, 961);
			char_shadow.setPosition(char_shadow.getPosition().x - 40, char_shadow.getPosition().y);
		}
		else if ((!(Keyboard::isKeyPressed((Keyboard::Left)))) && ((key_press_state & LEFT) == LEFT)) {
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
			chunli_char.setOrigin(71 / 2, 86);
			chunli_char.setPosition(chunli_char.getPosition().x - 2, 961);
			char_shadow.setPosition(char_shadow.getPosition().x + 40, char_shadow.getPosition().y);
			dist_accum = 0;
		};



















		if ((key_press_state & SPACE) == SPACE) {
			key_press_state = key_press_state | ANYKEY;
			bg_upward_animation(chunli_bg_s, chunli_bg_mom, chunli_bg_fishermen, chunli_bg_hen, key_press_state, time_accum_2, time_accum_3, random_bool_store, chunli_char, frame_counter, damage_box, char_shadow);
		};
		if (((key_press_state & ANYKEY) != ANYKEY)) {
			chunli_idle_animation(chunli_char, time_accum_3);
		};
		if ((key_press_state & RIGHT) == RIGHT) {
			chunli_walk_f_animation(chunli_char, time_accum_3, frame_counter, damage_box);
			char_shadow.setPosition(char_shadow.getPosition().x + floor((dt * 0.95) + dist_accum), char_shadow.getPosition().y);
			chunli_char.setPosition(chunli_char.getPosition().x + floor((dt * 0.95) + dist_accum), chunli_char.getPosition().y);
			dist_accum = ((dt * 0.95) + dist_accum) - floor((dt * 0.95) + dist_accum);
		}
		else if ((key_press_state & LEFT) == LEFT) {
			chunli_walk_b_animation(chunli_char, time_accum_3, frame_counter, damage_box);
			char_shadow.setPosition(char_shadow.getPosition().x - floor((dt * 0.9) + dist_accum), char_shadow.getPosition().y);
			chunli_char.setPosition(chunli_char.getPosition().x - floor((dt * 0.9) + dist_accum), chunli_char.getPosition().y);
			dist_accum = ((dt * 0.9) + dist_accum) - floor((dt * 0.9) + dist_accum);
		}
		bg_animation(time_accum, chunli_bg_fishermen, chunli_bg_mom, chunli_bg_hen);

		window1.clear();
		window1.draw(chunli_bg_s);
		window1.draw(chunli_bg_fishermen);
		window1.draw(chunli_bg_mom);
		window1.draw(chunli_bg_hen);
		window1.draw(char_shadow);
		window1.draw(chunli_char);
		window1.display();
	}
}


