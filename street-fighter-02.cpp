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


void bg_upward_animation(Sprite& chunli_bg_s, Sprite& chunli_bg_mom, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_hen, int& key_press_state, int& time_accum_2, int& time_accum_3, int& random_bool_store, int& frame_counter, Sprite& char_shadow) {

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {
		while (time_accum_2 >= 10) {
			chunli_bg_s.setTextureRect(IntRect(0, (chunli_bg_s.getTextureRect().top - 5), 1920, 1080));
			chunli_bg_fishermen.setPosition(800, chunli_bg_fishermen.getPosition().y + 5);
			chunli_bg_mom.setPosition(280, chunli_bg_mom.getPosition().y + 5);
			chunli_bg_hen.setPosition(1360, chunli_bg_hen.getPosition().y + 5);
			char_shadow.setPosition(char_shadow.getPosition().x, char_shadow.getPosition().y + 5);
			time_accum_2 = time_accum_2 - 10;

			if (chunli_bg_s.getTextureRect().top <= 0) {
				random_bool_store = random_bool_store & (~(1 << 0));

			}
		}
	}
	else if ((random_bool_store & (1 << 0)) != (1 << 0)) {
		while (time_accum_2 >= 10) {
			chunli_bg_s.setTextureRect(IntRect(0, (chunli_bg_s.getTextureRect().top + 5), 1920, 1080));
			chunli_bg_fishermen.setPosition(800, chunli_bg_fishermen.getPosition().y - 5);
			chunli_bg_mom.setPosition(280, chunli_bg_mom.getPosition().y - 5);
			chunli_bg_hen.setPosition(1360, chunli_bg_hen.getPosition().y - 5);
			char_shadow.setPosition(char_shadow.getPosition().x, char_shadow.getPosition().y - 5);
			time_accum_2 = time_accum_2 - 10;

			if (chunli_bg_s.getTextureRect().top >= 160) {
				random_bool_store = random_bool_store | (1 << 1);
			};
		}
	};

	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~SPACE);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
	}
}

void chunli_jump_animation(Sprite& chunli_char, int& key_press_state, int& time_accum_2, int& time_accum_3, int& random_bool_store, int& frame_counter) {

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {
		while (time_accum_3 >= 10) {
			time_accum_3 = time_accum_3 - 10;
			frame_counter = frame_counter + 1;
			if (4 <= frame_counter && frame_counter <= 17) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(74, 2340, 47, 109));
				chunli_char.setOrigin(47 / 2, 109 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			}
			else if (18 <= frame_counter && frame_counter <= 22) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(148, 2365, 50, 84));
				chunli_char.setOrigin(50 / 2, 84 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			}
			else if (23 <= frame_counter && frame_counter <= 27) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(222, 2374, 52, 75));
				chunli_char.setOrigin(52 / 2, 75 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			}
			else if (28 <= frame_counter && frame_counter <= 32) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(296, 2384, 57, 65));
				chunli_char.setOrigin(57 / 2, 65 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			}
		}
		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 18);
	}
	else {
		while (time_accum_3 >= 10) {
			time_accum_3 = time_accum_3 - 10;
			frame_counter = frame_counter + 1;
			if (33 <= frame_counter && frame_counter <= 37) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(370, 2374, 52, 75));
				chunli_char.setOrigin(52.0 / 2, 75.0 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			}
			else if (38 <= frame_counter && frame_counter <= 42) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(444, 2365, 50, 84));
				chunli_char.setOrigin(50.0 / 2, 84.0 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			}
			else if (43 <= frame_counter && frame_counter <= 59) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(518, 2340, 47, 109));
				chunli_char.setOrigin(47.0 / 2, 109.0 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			}
			else if (60 <= frame_counter && frame_counter <= 64) {
				chunli_char.setScale(1.0f, 1.0f);
				chunli_char.setTextureRect(IntRect(592, 2368, 74, 81));
				chunli_char.setOrigin(74.0 / 2, 81.0 / 2);
				chunli_char.setScale(5.0f, 5.0f);
			};
		}
		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y + 18);
	};
	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
		chunli_char.setOrigin(72.0 / 2, 87);
		chunli_char.setScale(5.0f, 5.0f);
		chunli_char.setPosition(chunli_char.getPosition().x, 961);
		random_bool_store = random_bool_store & (~(1 << 1));
	};
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
void chunli_walk_f_animation(Sprite& chunli_char, int& time_accum_3, int& frame_counter) {

	while (time_accum_3 >= 60) {
		time_accum_3 = time_accum_3 - 60;
		frame_counter = frame_counter + 1;
	}

	switch (frame_counter) {
	case 1:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(0, 164, 78, 84));
		chunli_char.setOrigin(78.0 / 2, 84);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 2:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(81, 161, 71, 87));
		chunli_char.setOrigin(71.0 / 2, 87);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 3:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(162, 160, 65, 88));
		chunli_char.setOrigin(65.0 / 2, 88);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 4:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(243, 159, 62, 89));
		chunli_char.setOrigin(62.0 / 2, 89);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 5:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(324, 160, 67, 88));
		chunli_char.setOrigin(67.0 / 2, 88);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 6:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(405, 161, 76, 87));
		chunli_char.setOrigin(76.0 / 2, 87);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 7:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(486, 162, 81, 86));
		chunli_char.setOrigin(81.0 / 2, 86);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 8:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(567, 161, 76, 87));
		chunli_char.setOrigin(76.0 / 2, 87);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 9:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(648, 160, 67, 88));
		chunli_char.setOrigin(67.0 / 2, 88);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 10:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(729, 159, 62, 89));
		chunli_char.setOrigin(62.0 / 2, 89);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 11:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(810, 160, 65, 88));
		chunli_char.setOrigin(65.0 / 2, 88);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 12:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(891, 161, 71, 87));
		chunli_char.setOrigin(71.0 / 2, 87);
		chunli_char.setScale(5.0f, 5.0f);
		frame_counter = 0;
		break;
	}
}
void chunli_walk_b_animation(Sprite& chunli_char, int& time_accum_3, int& frame_counter) {

	while (time_accum_3 >= 60) {
		time_accum_3 = time_accum_3 - 60;
		frame_counter = frame_counter + 1;
	}

	switch (frame_counter) {
	case 1:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(0, 293, 73, 86));
		chunli_char.setOrigin(73.0 / 2, 86);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 2:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(73, 290, 63, 89));
		chunli_char.setOrigin(63.0 / 2, 89);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 3:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(146, 289, 60, 90));
		chunli_char.setOrigin(60.0 / 2, 90);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 4:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(219, 288, 63, 91));
		chunli_char.setOrigin(63.0 / 2, 91);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 5:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(292, 289, 64, 90));
		chunli_char.setOrigin(64.0 / 2, 90);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 6:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(365, 290, 65, 89));
		chunli_char.setOrigin(65.0 / 2, 89);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 7:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(438, 291, 72, 88));
		chunli_char.setOrigin(72.0 / 2, 88);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 8:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(511, 290, 65, 89));
		chunli_char.setOrigin(65.0 / 2, 89);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 9:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(584, 289, 64, 90));
		chunli_char.setOrigin(64.0 / 2, 89);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 10:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(651, 288, 63, 91));
		chunli_char.setOrigin(63.0 / 2, 91);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 11:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(730, 289, 60, 90));
		chunli_char.setOrigin(60.0 / 2, 90);
		chunli_char.setScale(5.0f, 5.0f);
		break;
	case 12:
		chunli_char.setScale(1.0f, 1.0f);
		chunli_char.setTextureRect(IntRect(803, 290, 63, 89));
		chunli_char.setOrigin(63.0 / 2, 89);
		chunli_char.setScale(5.0f, 5.0f);
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

	chunli_char.setOrigin(72.0 / 2, 87);
	char_shadow.setOrigin(char_shadow.getLocalBounds().width / 2, char_shadow.getLocalBounds().height / 2);
	chunli_char.setScale(5.0f, 5.0f);
	char_shadow.setScale(5.0f, 5.0f);

	chunli_bg_fishermen.setPosition(800, 420);
	chunli_bg_mom.setPosition(280, 380);
	chunli_bg_hen.setPosition(1360, 580);
	chunli_char.setPosition(505, 961);
	char_shadow.setPosition(505, 961);

	key_press_state = key_press_state & (~ANYKEY);

	Clock clock1;
	while (window1.isOpen()) {

		dt = (clock1.restart()).asMilliseconds();

		time_accum = time_accum + dt;
		time_accum_2 = time_accum_2 + dt;
		time_accum_3 = time_accum_3 + dt;

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};

		//SPACE WITHOUT DIRECTION

		if (Keyboard::isKeyPressed(Keyboard::Space) && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | SPACE;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
			random_bool_store = random_bool_store | (1 << 0);
			random_bool_store = random_bool_store & (~(1 << 1));
			chunli_char.setScale(1.0f, 1.0f);
			chunli_char.setTextureRect(IntRect(0, 2368, 74, 81));
			chunli_char.setOrigin(74 / 2, 81 / 2);
			chunli_char.setScale(5.0f, 5.0f);
			chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 202);
			time_accum_2 = 0;
			time_accum_3 = 0;
			frame_counter = 0;
		};
		if (Keyboard::isKeyPressed((Keyboard::Right)) && (key_press_state & RIGHT) != RIGHT && (key_press_state & LEFT) != LEFT && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | RIGHT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter = 1;
			char_shadow.setPosition(char_shadow.getPosition().x - 40, char_shadow.getPosition().y);
		}
		else if ((!(Keyboard::isKeyPressed((Keyboard::Right)))) && ((key_press_state & RIGHT) == RIGHT)) {
			key_press_state = key_press_state & (~RIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
			chunli_char.setOrigin(35.8, 86.8);
			char_shadow.setPosition(char_shadow.getPosition().x + 40, char_shadow.getPosition().y);
			dist_accum = 0;
		};
		if (Keyboard::isKeyPressed((Keyboard::Left)) && (key_press_state & LEFT) != LEFT && (key_press_state & RIGHT) != RIGHT && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | LEFT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter = 1;
			char_shadow.setPosition(char_shadow.getPosition().x - 40, char_shadow.getPosition().y);
		}
		else if ((!(Keyboard::isKeyPressed((Keyboard::Left)))) && ((key_press_state & LEFT) == LEFT)) {
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
			chunli_char.setOrigin(35.8, 86.8);
			char_shadow.setPosition(char_shadow.getPosition().x + 40, char_shadow.getPosition().y);
			dist_accum = 0;
		};



















		if ((key_press_state & SPACE) == SPACE) {
			bg_upward_animation(chunli_bg_s, chunli_bg_mom, chunli_bg_fishermen, chunli_bg_hen, key_press_state, time_accum_2, time_accum_3, random_bool_store, frame_counter, char_shadow);
			chunli_jump_animation(chunli_char, key_press_state, time_accum_2, time_accum_3, random_bool_store, frame_counter);
		};
		if (((key_press_state & ANYKEY) != ANYKEY)) {
			chunli_idle_animation(chunli_char, time_accum_3);
		};
		if ((key_press_state & RIGHT) == RIGHT) {
			chunli_walk_f_animation(chunli_char, time_accum_3, frame_counter);
			char_shadow.setPosition(char_shadow.getPosition().x + floor((dt * 0.95) + dist_accum), char_shadow.getPosition().y);
			chunli_char.setPosition(chunli_char.getPosition().x + floor((dt * 0.95) + dist_accum), chunli_char.getPosition().y);
			dist_accum = ((dt * 0.95) + dist_accum) - floor((dt * 0.95) + dist_accum);
		}
		else if ((key_press_state & LEFT) == LEFT) {
			chunli_walk_b_animation(chunli_char, time_accum_3, frame_counter);
			char_shadow.setPosition(char_shadow.getPosition().x - floor((dt * 0.9) + dist_accum), char_shadow.getPosition().y);
			chunli_char.setPosition(chunli_char.getPosition().x - floor((dt * 0.9) + dist_accum), chunli_char.getPosition().y);
			dist_accum = ((dt * 0.9) + dist_accum) - floor((dt * 0.9) + dist_accum);
		};
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


