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
	Texture ryu_char_t;
}texture_elements;

//CHUNLI INPUT STATES

constexpr auto ANYKEY = 1 << 0;
constexpr auto SPACE = 1 << 1;
constexpr auto LEFT = 1 << 2;
constexpr auto RIGHT = 1 << 3;
constexpr auto DOWN = 1 << 4;
constexpr auto UP = 1 << 5;

//RYU INPUT STATES

constexpr auto _W_ = 1 << 1;
constexpr auto _D_ = 1 << 2;
constexpr auto _A_ = 1 << 3;
constexpr auto _S_ = 1 << 4;

void bg_animation(int& time_accum, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_mom, Sprite& chunli_bg_hen, Sprite& chunli_bg_laundry) {

	if ((time_accum <= 1500) || (time_accum > 1950 && time_accum <= 2950)) {
		chunli_bg_hen.setTextureRect(IntRect(913, 83, 50, 50));
	}
	else if ((1500 < time_accum && time_accum <= 1650) || (1800 < time_accum && time_accum <= 1950) || (2950 < time_accum && time_accum <= 3100) || (3250 < time_accum && time_accum <= 3400)) {
		chunli_bg_hen.setTextureRect(IntRect(913, 134, 50, 50));
	}
	else if ((time_accum > 1650 && time_accum <= 1800) || (time_accum > 3100 && time_accum <= 3250)) {
		chunli_bg_hen.setTextureRect(IntRect(913, 185, 50, 50));
	};

	if ((time_accum <= 1000) || (time_accum > 1900 && time_accum <= 2900)) {
		chunli_bg_fishermen.setTextureRect(IntRect(808, 82, 100, 80));
	}
	else if ((1000 < time_accum && time_accum <= 1180) || (1360 < time_accum && time_accum <= 1540) || (1720 < time_accum && time_accum <= 1900) || (2900 < time_accum && time_accum <= 3080) || (3260 < time_accum && time_accum <= 3400)) {
		chunli_bg_fishermen.setTextureRect(IntRect(808, 1, 100, 80));
	}
	else if ((1180 < time_accum && time_accum <= 1360) || (1540 < time_accum && time_accum <= 1720) || (3080 < time_accum && time_accum <= 3260)) {
		chunli_bg_fishermen.setTextureRect(IntRect(808, 163, 100, 80));
	};

	if ((time_accum <= 2000) || (3100 < time_accum && time_accum <= 3400)) {
		chunli_bg_mom.setTextureRect(IntRect(706, 1, 100, 90));
	}
	else if ((2000 < time_accum && time_accum <= 2200) || (3000 < time_accum && time_accum <= 3100)) {
		chunli_bg_mom.setTextureRect(IntRect(706, 92, 100, 90));
	}
	else if (2200 < time_accum && time_accum <= 3000) {
		chunli_bg_mom.setTextureRect(IntRect(706, 183, 100, 90));
	};
	if (time_accum > 3400) {
		time_accum = 0;
	};
}


void bg_upward_animation(Sprite& chunli_bg_display, Sprite& chunli_bg_mom, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_hen, int& key_press_state, int& time_accum_2, int& time_accum_3, int& random_bool_store, int& frame_counter_c, Sprite& char_shadow) {

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {
		while (time_accum_2 >= 20) {
			chunli_bg_display.setScale(1.0f, 1.0f);
			chunli_bg_display.setTextureRect(IntRect(0, (chunli_bg_display.getTextureRect().top - 1), 400, 225));
			char_shadow.setPosition(char_shadow.getPosition().x, char_shadow.getPosition().y + 4.8);
			chunli_bg_display.setScale(4.8f, 4.8f);
			time_accum_2 = time_accum_2 - 10;

			if (chunli_bg_display.getTextureRect().top <= 0) {
				random_bool_store = random_bool_store & (~(1 << 0));

			}
		}
	}
	else if ((random_bool_store & (1 << 0)) != (1 << 0)) {
		while (time_accum_2 >= 20) {
			chunli_bg_display.setScale(1.0f, 1.0f);
			chunli_bg_display.setTextureRect(IntRect(0, (chunli_bg_display.getTextureRect().top + 1), 400, 225));
			char_shadow.setPosition(char_shadow.getPosition().x, char_shadow.getPosition().y - 4.8);
			time_accum_2 = time_accum_2 - 10;
			chunli_bg_display.setScale(4.8f, 4.8f);

			if (chunli_bg_display.getTextureRect().top >= 44) {
				random_bool_store = random_bool_store | (1 << 1);
				chunli_bg_display.setTextureRect(IntRect(0, 44, 400, 225));
			};
		}
	};

	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~SPACE);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
	}
}


//_________________________________CHUNLI ANIMATIONS______________________________________________________________


void chunli_jump_animation(Sprite& chunli_char, int& key_press_state, int& time_accum_2, int& time_accum_3, int& random_bool_store, int& frame_counter_c) {

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {
		while (time_accum_3 >= 10) {
			time_accum_3 = time_accum_3 - 10;
			frame_counter_c = frame_counter_c + 1;
			if (4 <= frame_counter_c && frame_counter_c <= 17) {
				chunli_char.setTextureRect(IntRect(74, 2340, 47, 109));
				chunli_char.setOrigin(19.0, 12.0);
			}
			else if (18 <= frame_counter_c && frame_counter_c <= 22) {
				chunli_char.setTextureRect(IntRect(148, 2365, 50, 84));
				chunli_char.setOrigin(29.0 / 2, 12.0);
			}
			else if (23 <= frame_counter_c && frame_counter_c <= 27) {
				chunli_char.setTextureRect(IntRect(222, 2374, 52, 75));
				chunli_char.setOrigin(15.0, 12.0);
			}
			else if (28 <= frame_counter_c && frame_counter_c <= 32) {
				chunli_char.setTextureRect(IntRect(296, 2384, 57, 65));
				chunli_char.setOrigin(35.0 / 2, 12.0);
			}
		}
		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 3);
	}
	else {
		while (time_accum_3 >= 10) {
			time_accum_3 = time_accum_3 - 10;
			frame_counter_c = frame_counter_c + 1;
			if (33 <= frame_counter_c && frame_counter_c <= 37) {
				chunli_char.setTextureRect(IntRect(370, 2374, 52, 75));
				chunli_char.setOrigin(15.0, 12.0);
			}
			else if (38 <= frame_counter_c && frame_counter_c <= 42) {
				chunli_char.setTextureRect(IntRect(444, 2365, 50, 84));
				chunli_char.setOrigin(29.0 / 2, 12.0);
			}
			else if (43 <= frame_counter_c && frame_counter_c <= 59) {
				chunli_char.setTextureRect(IntRect(518, 2340, 47, 109));
				chunli_char.setOrigin(19.0, 12.0);
			}
			else if (60 <= frame_counter_c && frame_counter_c <= 64) {

				chunli_char.setTextureRect(IntRect(592, 2368, 74, 81));
				chunli_char.setOrigin(74.0 / 2, 12.0);

			};
		}
		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y + 3);
	};
	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
		chunli_char.setOrigin(72.0 / 2, 87);
		chunli_char.setPosition(chunli_char.getPosition().x, 248);
		random_bool_store = random_bool_store & (~(1 << 1));
	};
}

void chunli_idle_animation(Sprite& chunli_char, int& time_accum_3) {

	if (time_accum_3 >= 160 && (chunli_char.getTextureRect()).left >= 256) {
		chunli_char.setTextureRect(IntRect(-65, 32, 72, 87));
	}
	while (time_accum_3 >= 160 && ((chunli_char.getTextureRect()).left) < 256) {
		time_accum_3 = time_accum_3 - 160;
		chunli_char.setTextureRect(IntRect(((chunli_char.getTextureRect()).left) + 81, 32, 80, 87));
	}
}

void chunli_walk_f_animation(Sprite& chunli_char, int& time_accum_3, int& frame_counter_c, int& key_press_state, Sprite& char_shadow) {

	while (time_accum_3 >= 75) {
		time_accum_3 = time_accum_3 - 75;
		frame_counter_c = frame_counter_c + 1;
	}

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(0, 164, 78, 84));
		chunli_char.setOrigin(73.0 / 2, 84);
		break;
	case 2:
		chunli_char.setTextureRect(IntRect(81, 161, 71, 87));
		chunli_char.setOrigin(58.0 / 2, 87);
		break;
	case 3:
		chunli_char.setTextureRect(IntRect(162, 160, 65, 88));
		chunli_char.setOrigin(40.0 / 2, 88);
		break;
	case 4:
		chunli_char.setTextureRect(IntRect(243, 159, 62, 89));
		chunli_char.setOrigin(31.0 / 2, 89);
		break;
	case 5:
		chunli_char.setTextureRect(IntRect(324, 160, 67, 88));
		chunli_char.setOrigin(35.0 / 2, 88);
		break;
	case 6:
		chunli_char.setTextureRect(IntRect(405, 161, 77, 87));
		chunli_char.setOrigin(54.0 / 2, 87);
		break;
	case 7:
		chunli_char.setTextureRect(IntRect(486, 162, 82, 86));
		chunli_char.setOrigin(68.0 / 2, 86);
		break;
	case 8:
		chunli_char.setTextureRect(IntRect(591, 161, 77, 87));
		chunli_char.setOrigin(54.0 / 2, 87);
		break;
	case 9:
		chunli_char.setTextureRect(IntRect(672, 160, 67, 88));
		chunli_char.setOrigin(35.0 / 2, 88);
		break;
	case 10:
		chunli_char.setTextureRect(IntRect(753, 159, 62, 89));
		chunli_char.setOrigin(31.0 / 2, 89);
		break;
	case 11:
		chunli_char.setTextureRect(IntRect(834, 160, 65, 88));
		chunli_char.setOrigin(43.0 / 2, 88);
		break;
	case 12:
		chunli_char.setTextureRect(IntRect(915, 161, 71, 87));
		chunli_char.setOrigin(58.0 / 2, 87);
		frame_counter_c = 0;
		break;
	}

	char_shadow.setPosition(chunli_char.getPosition().x - 20, char_shadow.getPosition().y);

	if (!(Keyboard::isKeyPressed(Keyboard::Right))) {
		key_press_state = key_press_state & (~RIGHT);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
		chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
		chunli_char.setOrigin(72.0 / 2, 87);
		chunli_char.setPosition(chunli_char.getPosition().x + 8, chunli_char.getPosition().y);
	}
}
void chunli_walk_b_animation(Sprite& chunli_char, int& time_accum_3, int& frame_counter_c, int& key_press_state, Sprite& char_shadow) {

	while (time_accum_3 >= 80) {
		time_accum_3 = time_accum_3 - 80;
		frame_counter_c = frame_counter_c + 1;
	}

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(0, 293, 73, 86));
		chunli_char.setOrigin(73.0 / 2, 86);
		break;
	case 2:
		chunli_char.setTextureRect(IntRect(89, 290, 63, 89));
		chunli_char.setOrigin(58.0 / 2, 89);
		break;
	case 3:
		chunli_char.setTextureRect(IntRect(162, 289, 60, 90));
		chunli_char.setOrigin(51.0 / 2, 90);
		break;
	case 4:
		chunli_char.setTextureRect(IntRect(235, 288, 63, 91));
		chunli_char.setOrigin(51.0 / 2, 91);
		break;
	case 5:
		chunli_char.setTextureRect(IntRect(308, 289, 64, 90));
		chunli_char.setOrigin(52.0 / 2, 90);
		break;
	case 6:
		chunli_char.setTextureRect(IntRect(381, 290, 65, 89));
		chunli_char.setOrigin(54.0 / 2, 89);
		break;
	case 7:
		chunli_char.setTextureRect(IntRect(454, 291, 72, 88));
		chunli_char.setOrigin(68.0 / 2, 88);
		break;
	case 8:
		chunli_char.setTextureRect(IntRect(531, 290, 65, 89));
		chunli_char.setOrigin(54.0 / 2, 89);
		break;
	case 9:
		chunli_char.setTextureRect(IntRect(600, 289, 64, 90));
		chunli_char.setOrigin(52.0 / 2, 89);
		break;
	case 10:
		chunli_char.setTextureRect(IntRect(673, 288, 63, 91));
		chunli_char.setOrigin(51.0 / 2, 91);
		break;
	case 11:
		chunli_char.setTextureRect(IntRect(746, 289, 60, 90));
		chunli_char.setOrigin(51.0 / 2, 90);
		break;
	case 12:
		chunli_char.setTextureRect(IntRect(819, 290, 63, 89));
		chunli_char.setOrigin(58.0 / 2, 89);
		frame_counter_c = 0;
		break;
	}

	char_shadow.setPosition(chunli_char.getPosition().x, char_shadow.getPosition().y);

	if (!(Keyboard::isKeyPressed(Keyboard::Left))) {
		key_press_state = key_press_state & (~LEFT);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
		chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
		chunli_char.setOrigin(72.0 / 2, 87);
	}
}

void chunli_down(Sprite& chunli_char, int& time_accum_3, int& frame_counter_c, int& key_press_state, Sprite& char_shadow) {

	while (time_accum_3 >= 30) {
		time_accum_3 = time_accum_3 - 10;
		frame_counter_c = frame_counter_c + 1;
		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(74, 2007, 73, 72));
			chunli_char.setOrigin(73.0 / 2, 72);
		case 2:
			chunli_char.setTextureRect(IntRect(147, 2013, 72, 66));
			chunli_char.setOrigin(72.0 / 2, 66);
			frame_counter_c = frame_counter_c - 1;
		}
	}

	char_shadow.setPosition(chunli_char.getPosition().x, char_shadow.getPosition().y);

	if (!(Keyboard::isKeyPressed(Keyboard::Down))) {
		key_press_state = key_press_state & (~DOWN);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
		chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
		chunli_char.setOrigin(72.0 / 2, 87);
	}
}

void chunli_block(Sprite& chunli_char, int& key_press_state, int& time_accum_3, int x = 1) {
	if (x == 2) {
		chunli_char.setTextureRect(IntRect(73, 3840, 83, 85));
	}	//hit
	else {
		if (!(Keyboard::isKeyPressed(Keyboard::Down))) {
			chunli_char.setTextureRect(IntRect(0, 3839, 73, 86));
			chunli_char.setOrigin(73.0 / 2, 86);
		}
		else {
			chunli_char.setTextureRect(IntRect(309, 3857, 73, 68));
			chunli_char.setOrigin(73.0 / 2, 68.0);
		}
	};	//no hit

	if (!(Keyboard::isKeyPressed(Keyboard::Up))) {
		key_press_state = key_press_state & (~UP);
		if (!((Keyboard::isKeyPressed(Keyboard::Down)))) {
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
			chunli_char.setOrigin(72.0 / 2, 87);
		}
	}
}

//			______________________________________RYU ANIMATION_____________________________________________________________


void ryu_idle(int& frame_counter_r, int& time_accum_4, Sprite& ryu_char) {

	while (time_accum_4 >= 130) {
		time_accum_4 = time_accum_4 - 130;
		frame_counter_r = frame_counter_r + 1;
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(0, 3, 59, 90));
			ryu_char.setOrigin(67.0 / 2, 90);
			break;

		case 2:
			ryu_char.setTextureRect(IntRect(75, 4, 60, 89));
			ryu_char.setOrigin(68.0 / 2, 89);
			break;
		case 3:
			ryu_char.setTextureRect(IntRect(151, 3, 59, 90));
			ryu_char.setOrigin(67.0 / 2, 90);
			break;
		case 4:
			ryu_char.setTextureRect(IntRect(226, 0, 55, 93));
			ryu_char.setOrigin(61.0 / 2, 93);
			frame_counter_r = 0;
			break;
		}
	}
	ryu_char.setPosition(ryu_char.getPosition().x, 247);

}

void ryu_walk_f(int& frame_counter_r, int& time_accum_4, Sprite& ryu_char, int& key_press_state_r) {
	while (time_accum_4 >= 85) {
		time_accum_4 = time_accum_4 - 85;
		frame_counter_r = frame_counter_r + 1;
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(9, 136, 52, 83));
			ryu_char.setOrigin(39, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 5);
			break;
		case 2:
			ryu_char.setTextureRect(IntRect(78, 130, 60, 88));
			ryu_char.setOrigin(46, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 6);
			break;
		case 3:
			ryu_char.setTextureRect(IntRect(162, 126, 64, 92));
			ryu_char.setOrigin(47, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 2);
			break;
		case 4:
			ryu_char.setTextureRect(IntRect(259, 127, 63, 90));
			ryu_char.setOrigin(41, 10);
			break;
		case 5:
			ryu_char.setTextureRect(IntRect(352, 127, 54, 91));
			ryu_char.setOrigin(37, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 1);
			break;
		case 6:
			ryu_char.setTextureRect(IntRect(432, 131, 50, 89));
			ryu_char.setOrigin(36, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 2);
			frame_counter_r = 0;
			break;
		}
	}
	if (!(Keyboard::isKeyPressed(Keyboard::A))) {
		key_press_state_r = key_press_state_r & (~_A_);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		time_accum_4 = 130;
		frame_counter_r = 0;
		ryu_char.setPosition(ryu_char.getPosition().x + 14, 247);
	}
}

void ryu_walk_b(Sprite& ryu_char, int& time_accum_4, int& key_press_state_r, int& frame_counter_r) {

	while (time_accum_4 >= 90) {
		time_accum_4 = time_accum_4 - 90;
		frame_counter_r = frame_counter_r + 1;
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(542, 132, 61, 87));
			ryu_char.setOrigin(32, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 5);
			break;
		case 2:
			ryu_char.setTextureRect(IntRect(628, 128, 59, 90));
			ryu_char.setOrigin(33, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 4);
			break;
		case 3:
			ryu_char.setTextureRect(IntRect(713, 126, 57, 90));
			ryu_char.setOrigin(33, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 2);
			break;
		case 4:
			ryu_char.setTextureRect(IntRect(797, 126, 58, 90));
			ryu_char.setOrigin(35, 10);
			break;
		case 5:
			ryu_char.setTextureRect(IntRect(883, 127, 58, 91));
			ryu_char.setOrigin(33, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 1);
			frame_counter_r = 0;
			break;
		}
	}

	if (!(Keyboard::isKeyPressed(Keyboard::D))) {
		key_press_state_r = key_press_state_r & (~_D_);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		time_accum_4 = 130;
		frame_counter_r = 0;
		ryu_char.setPosition(ryu_char.getPosition().x - 1, 247);
	}
}

int main() {

	float dt;

	int time_accum = 0;
	int time_accum_2 = 0;
	int time_accum_3 = 0;
	int time_accum_4 = 120;
	int frame_counter_c = 1;
	int frame_counter_r = 0;
	int key_press_state = 0;
	int key_press_state_r = 0;
	float dist_accum = 0;
	int random_bool_store = 0;	//first 2 digits for bg_upward_animation()

	VideoMode vm(1920, 1080);
	RenderWindow window1(vm, "New Game", Style::Fullscreen);
	window1.setVerticalSyncEnabled(true);

	//BACKGROUND ELEMENTS:

	(texture_elements.chunli_bg_t).loadFromFile("ChunLi Sprites/final-chunli-bg4.png");

	Sprite chunli_bg_stage;
	Sprite chunli_bg_fishermen;
	Sprite chunli_bg_mom;
	Sprite chunli_bg_hen;
	Sprite chunli_bg_laundry;
	Sprite chunli_bg_display;

	chunli_bg_stage.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_fishermen.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_mom.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_hen.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_laundry.setTexture(texture_elements.chunli_bg_t);

	chunli_bg_stage.setTextureRect(IntRect(0, 0, 704, 269));

	RenderTexture bg_stage;
	bg_stage.create(704, 269);
	chunli_bg_stage.setPosition(0, 0);
	chunli_bg_mom.setPosition(53, 129);
	chunli_bg_hen.setPosition(266, 168);
	chunli_bg_fishermen.setPosition(158, 136);
	chunli_bg_laundry.setPosition(606, 170);

	bg_stage.setSmooth(true);

	chunli_bg_display.setTexture(bg_stage.getTexture());
	chunli_bg_display.setTextureRect(IntRect(0, 44, 400, 225));







	//CHUNLI ELEMENTS

	(texture_elements.chunli_char_t).loadFromFile("ChunLi Sprites/ChunLi2.png");

	Sprite chunli_char;
	Sprite char_shadow;

	chunli_char.setTexture(texture_elements.chunli_char_t);
	char_shadow.setTexture(texture_elements.chunli_char_t);
	chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
	char_shadow.setTextureRect(IntRect(14, 135, 74, 12));

	chunli_char.setOrigin(72.0 / 2, 87);
	char_shadow.setOrigin(74.0 / 2, 12.0 / 2);

	char_shadow.setPosition(99, 247);
	chunli_char.setPosition(99, 247);

	texture_elements.chunli_char_t.setSmooth(false);

	//RYU ELEMENTS

	(texture_elements.ryu_char_t).loadFromFile("Ryu Sprites/Ryu.png");

	Sprite ryu_char;

	ryu_char.setTexture(texture_elements.ryu_char_t);
	ryu_char.setPosition(300, 247);
	ryu_char.setScale(-1.0f, 1.0f);

	key_press_state_r = key_press_state_r & (~ANYKEY);

	Clock clock1;

	while (window1.isOpen()) {

		chunli_bg_display.setScale(1.0f, 1.0f);

		dt = (clock1.restart()).asMilliseconds();
		time_accum = time_accum + dt;
		time_accum_2 = time_accum_2 + dt;
		time_accum_3 = time_accum_3 + dt;
		time_accum_4 = time_accum_4 + dt;

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};

		//SPACE WITHOUT DIRECTION

		if (Keyboard::isKeyPressed(Keyboard::Space) && (key_press_state & SPACE) != SPACE && (key_press_state & UP) != UP) {
			key_press_state = key_press_state | SPACE;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
			random_bool_store = random_bool_store | (1 << 0);
			random_bool_store = random_bool_store & (~(1 << 1));
			chunli_char.setTextureRect(IntRect(0, 2368, 74, 81));
			chunli_char.setOrigin(74.0 / 2, 12.0);
			chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 355);
			time_accum_2 = 0;
			time_accum_3 = 0;
			frame_counter_c = 0;
		};
		if (Keyboard::isKeyPressed((Keyboard::Right)) && (key_press_state & ANYKEY) != ANYKEY) {
			key_press_state = key_press_state | RIGHT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter_c = 1;
			chunli_char.setPosition(chunli_char.getPosition().x - 8, chunli_char.getPosition().y);
		};
		if (Keyboard::isKeyPressed((Keyboard::Left)) && (key_press_state & ANYKEY) != ANYKEY) {
			key_press_state = key_press_state | LEFT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter_c = 1;
		};
		if (Keyboard::isKeyPressed(Keyboard::Up) && (key_press_state & UP) != UP && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | UP;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
		};
		if (Keyboard::isKeyPressed(Keyboard::Down) && (key_press_state & SPACE) != SPACE && (key_press_state & DOWN) != DOWN) {
			key_press_state = key_press_state | DOWN;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(0, 1998, 74, 81));
			chunli_char.setOrigin(74.0 / 2, 81);
			frame_counter_c = 0;
		};



















		if ((key_press_state & SPACE) == SPACE) {
			bg_upward_animation(chunli_bg_display, chunli_bg_mom, chunli_bg_fishermen, chunli_bg_hen, key_press_state, time_accum_2, time_accum_3, random_bool_store, frame_counter_c, char_shadow);
			chunli_jump_animation(chunli_char, key_press_state, time_accum_2, time_accum_3, random_bool_store, frame_counter_c);
		};
		if (((key_press_state & ANYKEY) != ANYKEY)) {
			chunli_idle_animation(chunli_char, time_accum_3);
		};
		if (((key_press_state & RIGHT) == RIGHT) && ((key_press_state & DOWN) != DOWN)) {
			chunli_walk_f_animation(chunli_char, time_accum_3, frame_counter_c, key_press_state, char_shadow);
			chunli_char.setPosition(chunli_char.getPosition().x + round((dt * 0.18) + dist_accum), chunli_char.getPosition().y);
			dist_accum = ((dt * 0.18) + dist_accum) - round((dt * 0.18) + dist_accum);
		}
		else if (((key_press_state & LEFT) == LEFT) && ((key_press_state & DOWN) != DOWN)) {
			chunli_walk_b_animation(chunli_char, time_accum_3, frame_counter_c, key_press_state, char_shadow);
			chunli_char.setPosition(chunli_char.getPosition().x - round((dt * 0.15) + dist_accum), chunli_char.getPosition().y);
			dist_accum = ((dt * 0.15) + dist_accum) - round((dt * 0.15) + dist_accum);
		};
		if (((key_press_state & DOWN) == DOWN) && (key_press_state & UP) != UP) {
			chunli_down(chunli_char, time_accum_3, frame_counter_c, key_press_state, char_shadow);
		};
		if ((key_press_state & UP) == UP) {
			chunli_block(chunli_char, key_press_state, time_accum_3);
		};
		bg_animation(time_accum, chunli_bg_fishermen, chunli_bg_mom, chunli_bg_hen, chunli_bg_laundry);


























		// _____________________________________________________________________ RYU CODE___________________________________________________________________________________



		if (Keyboard::isKeyPressed(Keyboard::W)) {
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_r = key_press_state_r | _W_;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && ((key_press_state_r & _A_) != _A_) && (key_press_state_r & _D_) != _D_) {
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_r = key_press_state_r | _D_;
			time_accum_4 = 90;
			ryu_char.setPosition(ryu_char.getPosition().x + 1, ryu_char.getPosition().y - 83);
		};
		if (Keyboard::isKeyPressed(Keyboard::A) && ((key_press_state_r & _A_) != _A_) && (key_press_state_r & _D_) != _D_) {
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_r = key_press_state_r | _A_;
			time_accum_4 = 85;
			ryu_char.setPosition(ryu_char.getPosition().x - 14, ryu_char.getPosition().y - 80);
		};


















		if ((key_press_state_r & _A_) == _A_) {
			ryu_char.setPosition(ryu_char.getPosition().x - round((dt * 0.14) + dist_accum), ryu_char.getPosition().y);
			dist_accum = ((dt * 0.14) + dist_accum) - round((dt * 0.14) + dist_accum);
			ryu_walk_f(frame_counter_r, time_accum_4, ryu_char, key_press_state_r);
		};
		if ((key_press_state_r & _D_) == _D_) {
			ryu_char.setPosition(ryu_char.getPosition().x + round((dt * 0.12) + dist_accum), ryu_char.getPosition().y);
			dist_accum = ((dt * 0.12) + dist_accum) - round((dt * 0.12) + dist_accum);
			ryu_walk_b(ryu_char, time_accum_4, key_press_state_r, frame_counter_r);
		};
		if ((key_press_state_r & ANYKEY) != ANYKEY) {
			ryu_idle(frame_counter_r, time_accum_4, ryu_char);
		};


































		bg_stage.clear();
		bg_stage.draw(chunli_bg_stage);
		bg_stage.draw(chunli_bg_fishermen);
		bg_stage.draw(chunli_bg_hen);
		bg_stage.draw(chunli_bg_laundry);
		bg_stage.draw(chunli_bg_mom);
		bg_stage.draw(chunli_char);
		bg_stage.draw(ryu_char);
		bg_stage.display();

		chunli_bg_display.setScale(4.8f, 4.8f);

		window1.clear();
		window1.draw(chunli_bg_display);
		window1.display();
	}
}