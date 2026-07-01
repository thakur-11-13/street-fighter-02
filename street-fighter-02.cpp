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
constexpr auto SPACE_0 = 1 << 1;
constexpr auto LEFT = 1 << 2;
constexpr auto RIGHT = 1 << 3;
constexpr auto DOWN = 1 << 4;
constexpr auto UP = 1 << 5;
constexpr auto SPACE_L = 1 << 6;
constexpr auto SPACE_R = 1 << 7;
constexpr auto ANIMATION_ON = 1 << 8;

//RYU INPUT STATES

constexpr auto _W_ = 1 << 1;
constexpr auto _D_ = 1 << 2;
constexpr auto _A_ = 1 << 3;
constexpr auto _S_ = 1 << 4;
constexpr auto _Q_ = 1 << 5;
constexpr auto _W_L = 1 << 6;
constexpr auto _W_R = 1 << 7;

void bg_animation(float& time_accum, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_mom, Sprite& chunli_bg_hen, Sprite& chunli_bg_laundry) {

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


//_________________________________CHUNLI ANIMATIONS______________________________________________________________


void chunli_jump_animation(Sprite& chunli_char, float& time_accum_3, int& random_bool_store, int& frame_counter_c, float& time_accum_2, int& key_press_state) {

	while (time_accum_3 >= 10) {
		time_accum_3 = time_accum_3 - 10;
		frame_counter_c = frame_counter_c + 1;
	}

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {
		if (time_accum_2 >= 430) {
			random_bool_store = random_bool_store & (~(1 << 0));
			time_accum_2 = 0;
			frame_counter_c = 0;
		};

		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 3);
		switch (frame_counter_c) {
		case 8:
			chunli_char.setTextureRect(IntRect(74, 2340, 47, 109));
			chunli_char.setOrigin(19.0, 12.0);
			break;
		case 9:
			chunli_char.setTextureRect(IntRect(74, 2340, 47, 109));
			chunli_char.setOrigin(19.0, 12.0);
			break;
		case 24:
			chunli_char.setTextureRect(IntRect(148, 2365, 50, 84));
			chunli_char.setOrigin(29.0 / 2, 12.0);
			break;
		case 25:
			chunli_char.setTextureRect(IntRect(148, 2365, 50, 84));
			chunli_char.setOrigin(29.0 / 2, 12.0);
			break;
		case 32:
			chunli_char.setTextureRect(IntRect(222, 2374, 52, 75));
			chunli_char.setOrigin(15.0, 12.0);
			break;
		case 33:
			chunli_char.setTextureRect(IntRect(222, 2374, 52, 75));
			chunli_char.setOrigin(15.0, 12.0);
			break;
		case 42:
			chunli_char.setTextureRect(IntRect(296, 2384, 57, 65));
			chunli_char.setOrigin(35.0 / 2, 12.0);
			break;
		case 43:
			chunli_char.setTextureRect(IntRect(296, 2384, 57, 65));
			chunli_char.setOrigin(35.0 / 2, 12.0);
			break;
		}
	}
	else {
		if (time_accum_2 >= 430) {
			random_bool_store = random_bool_store | (1 << 1);
		};

		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y + 3);
		switch (frame_counter_c) {
		case 4:
			chunli_char.setTextureRect(IntRect(370, 2374, 52, 75));
			chunli_char.setOrigin(15.0, 12.0);
			break;
		case 5:
			chunli_char.setTextureRect(IntRect(370, 2374, 52, 75));
			chunli_char.setOrigin(15.0, 12.0);
			break;
		case 13:
			chunli_char.setTextureRect(IntRect(444, 2365, 50, 84));
			chunli_char.setOrigin(29.0 / 2, 12.0);
			break;
		case 14:
			chunli_char.setTextureRect(IntRect(444, 2365, 50, 84));
			chunli_char.setOrigin(29.0 / 2, 12.0);
			break;
		case 20:
			chunli_char.setTextureRect(IntRect(518, 2340, 47, 109));
			chunli_char.setOrigin(19.0, 12.0);
			break;
		case 21:
			chunli_char.setTextureRect(IntRect(518, 2340, 47, 109));
			chunli_char.setOrigin(19.0, 12.0);
			break;
		case 36:
			chunli_char.setTextureRect(IntRect(592, 2368, 74, 81));
			chunli_char.setOrigin(74.0 / 2, 12.0);
			break;
		}
	};
	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~SPACE_0);
		key_press_state = key_press_state & (~ANYKEY);
		key_press_state = key_press_state & (~ANIMATION_ON);
		frame_counter_c = 1;
		chunli_char.setPosition(chunli_char.getPosition().x, 248);
		time_accum_3 = 0;
	};
}

void chunli_jump_animation_L() {

}

void chunli_jump_animation_R(Sprite& chunli_char, float& time_accum_3, int& frame_counter_c, int& random_bool_store, float& time_accum_2, int& key_press_state) {

	while (time_accum_3 >= 10) {
		time_accum_3 = time_accum_3 - 10;
		frame_counter_c = frame_counter_c + 1;
	}

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {
		if (time_accum_2 >= 430) {
			random_bool_store = random_bool_store & (~(1 << 0));
			time_accum_2 = 0;
			frame_counter_c = 0;
		};
		chunli_char.setPosition(chunli_char.getPosition().x + 1, chunli_char.getPosition().y - 3);
		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(580, 3689, 47, 109));
			chunli_char.setOrigin(20, 37);
			break;
		case 2:
			chunli_char.setTextureRect(IntRect(580, 3689, 47, 109));
			chunli_char.setOrigin(20, 37);
			break;
		case 14:
			chunli_char.setTextureRect(IntRect(635, 3718, 88, 81));
			chunli_char.setOrigin(42, 20);
			break;
		case 15:
			chunli_char.setTextureRect(IntRect(635, 3718, 88, 81));
			chunli_char.setOrigin(42, 20);
			break;
		case 18:
			chunli_char.setTextureRect(IntRect(731, 3751, 121, 48));
			chunli_char.setOrigin(86, 20);
			break;
		case 19:
			chunli_char.setTextureRect(IntRect(731, 3751, 121, 48));
			chunli_char.setOrigin(86, 20);
			break;
		case 24:
			chunli_char.setTextureRect(IntRect(860, 3695, 52, 104));
			chunli_char.setOrigin(77, 56);
			break;
		case 25:
			chunli_char.setTextureRect(IntRect(860, 3695, 52, 104));
			chunli_char.setOrigin(77, 56);
			break;
		case 32:
			chunli_char.setTextureRect(IntRect(977, 3695, 52, 104));
			chunli_char.setOrigin(31, 69);
			break;
		case 33:
			chunli_char.setTextureRect(IntRect(977, 3695, 52, 104));
			chunli_char.setOrigin(31, 69);
			break;
		}
	}
	else {
		if (time_accum_2 >= 430) {
			random_bool_store = random_bool_store | (1 << 1);
		};
		chunli_char.setPosition(chunli_char.getPosition().x + 1, chunli_char.getPosition().y + 3);
		switch (frame_counter_c) {
		case 4:
			chunli_char.setTextureRect(IntRect(1037, 3718, 110, 81));
			chunli_char.setOrigin(36, 51);
			break;
		case 5:
			chunli_char.setTextureRect(IntRect(1037, 3718, 110, 81));
			chunli_char.setOrigin(36, 51);
			break;
		case 10:
			chunli_char.setTextureRect(IntRect(1155, 3733, 119, 66));
			chunli_char.setOrigin(37, 35);
			break;
		case 11:
			chunli_char.setTextureRect(IntRect(1155, 3733, 119, 66));
			chunli_char.setOrigin(37, 35);
			break;
		case 17:
			chunli_char.setTextureRect(IntRect(1282, 3723, 95, 76));
			chunli_char.setOrigin(43, 21);
			break;
		case 18:
			chunli_char.setTextureRect(IntRect(1282, 3723, 95, 76));
			chunli_char.setOrigin(43, 21);
			break;
		case 24:
			chunli_char.setTextureRect(IntRect(1386, 3689, 47, 109));
			chunli_char.setOrigin(20, 37);
			break;
		case 25:
			chunli_char.setTextureRect(IntRect(1386, 3689, 47, 109));
			chunli_char.setOrigin(20, 37);
			break;
		case 37:
			chunli_char.setTextureRect(IntRect(1440, 3718, 74, 81));
			chunli_char.setOrigin(26, 36);
			break;
		case 38:
			chunli_char.setTextureRect(IntRect(1440, 3718, 74, 81));
			chunli_char.setOrigin(26, 36);
			break;
		}
	};

	if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~ANYKEY);
		key_press_state = key_press_state & (~ANIMATION_ON);
		key_press_state = key_press_state & (~SPACE_R);
		frame_counter_c = 1;
		time_accum_3 = 0;
		chunli_char.setPosition(chunli_char.getPosition().x, 248);
	}
}


void chunli_idle_animation(Sprite& chunli_char, float& time_accum_3, int& frame_counter_c) {

	while (time_accum_3 >= 160) {
		time_accum_3 = time_accum_3 - 160;
		frame_counter_c = frame_counter_c + 1;
	}

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(16, 32, 80, 87));
		chunli_char.setOrigin(72.0 / 2, 87);
		break;
	case 2:
		chunli_char.setTextureRect(IntRect(97, 32, 80, 87));
		break;
	case 3:
		chunli_char.setTextureRect(IntRect(178, 32, 80, 87));
		break;
	case 4:
		chunli_char.setTextureRect(IntRect(259, 32, 80, 87));
		frame_counter_c = 0;
		break;
	}
}

void chunli_walk_f_animation(Sprite& chunli_char, float& time_accum_3, int& frame_counter_c, int& key_press_state, Sprite& chunli_shadow, float dist_accum_c) {

	while (time_accum_3 >= 70) {
		time_accum_3 = time_accum_3 - 70;
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

	chunli_shadow.setPosition(chunli_char.getPosition().x - 2, chunli_shadow.getPosition().y);

	if (!(Keyboard::isKeyPressed(Keyboard::Right))) {
		key_press_state = key_press_state & (~RIGHT);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
		frame_counter_c = 1;
		chunli_shadow.setPosition(chunli_char.getPosition().x + 2, chunli_shadow.getPosition().y);
	}
}
void chunli_walk_b_animation(Sprite& chunli_char, float& time_accum_3, int& frame_counter_c, int& key_press_state, Sprite& chunli_shadow, float dist_accum_c) {

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

	chunli_shadow.setPosition(chunli_char.getPosition().x, chunli_shadow.getPosition().y);

	if (!(Keyboard::isKeyPressed(Keyboard::Left))) {
		key_press_state = key_press_state & (~LEFT);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
		frame_counter_c = 1;
	}
}

void chunli_sit(Sprite& chunli_char, float& time_accum_3, int& frame_counter_c, int& key_press_state, Sprite& chunli_shadow) {

	while (time_accum_3 >= 40) {
		time_accum_3 = time_accum_3 - 40;
		frame_counter_c = frame_counter_c + 1;
	}
	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(0, 1998, 74, 81));
		chunli_char.setOrigin(74.0 / 2, 81);
		break;
	case 2:
		chunli_char.setTextureRect(IntRect(74, 2007, 73, 72));
		chunli_char.setOrigin(73.0 / 2, 72);
		break;
	case 3:
		chunli_char.setTextureRect(IntRect(147, 2013, 72, 66));
		chunli_char.setOrigin(72.0 / 2, 66);
		break;
	default:
		chunli_char.setTextureRect(IntRect(147, 2013, 72, 66));
		chunli_char.setOrigin(72.0 / 2, 66);
		break;
	}

	chunli_shadow.setPosition(chunli_char.getPosition().x, chunli_shadow.getPosition().y);

	if (!(Keyboard::isKeyPressed(Keyboard::Down))) {
		key_press_state = key_press_state & (~DOWN);
		key_press_state = key_press_state & (~ANYKEY);
		time_accum_3 = 0;
		frame_counter_c = 1;
	}
}

void chunli_block(Sprite& chunli_char, int& key_press_state, float& time_accum_3, int& frame_counter_c, int x = 1) {
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
		frame_counter_c = 3;
		if (!(Keyboard::isKeyPressed(Keyboard::Down))) {
			frame_counter_c = 1;
			key_press_state = key_press_state & (~DOWN);
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
		}
	}
}



//			______________________________________RYU ANIMATION_____________________________________________________________



void ryu_idle(int& frame_counter_r, float& time_accum_4, Sprite& ryu_char, Sprite& ryu_shadow) {

	while (time_accum_4 >= 130) {
		time_accum_4 = time_accum_4 - 130;
		frame_counter_r = frame_counter_r + 1;
	}

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(0, 3, 59, 90));
		ryu_char.setOrigin(36, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 167);
		break;

	case 2:
		ryu_char.setTextureRect(IntRect(75, 4, 60, 89));
		ryu_char.setPosition(ryu_char.getPosition().x, 168);
		break;
	case 3:
		ryu_char.setTextureRect(IntRect(151, 3, 59, 90));
		ryu_char.setPosition(ryu_char.getPosition().x, 167);
		break;
	case 4:
		ryu_char.setTextureRect(IntRect(226, 0, 55, 93));
		ryu_char.setPosition(ryu_char.getPosition().x, 164);
		frame_counter_r = 0;
		break;
	}
	ryu_shadow.setPosition(ryu_char.getPosition().x, ryu_shadow.getPosition().y);

}

void ryu_walk_f(int& frame_counter_r, float& time_accum_4, Sprite& ryu_char, int& key_press_state_r, float& dist_accum_r) {

	while (time_accum_4 >= 85) {
		time_accum_4 = time_accum_4 - 85;
		frame_counter_r = frame_counter_r + 1;
	}

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(9, 136, 52, 83));
		ryu_char.setOrigin(39, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 174);
		break;
	case 2:
		ryu_char.setTextureRect(IntRect(78, 130, 60, 88));
		ryu_char.setOrigin(46, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 168);
		break;
	case 3:
		ryu_char.setTextureRect(IntRect(162, 126, 64, 92));
		ryu_char.setOrigin(47, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 163);
		break;
	case 4:
		ryu_char.setTextureRect(IntRect(259, 127, 63, 90));
		ryu_char.setOrigin(41, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 164);
		break;
	case 5:
		ryu_char.setTextureRect(IntRect(352, 127, 54, 91));
		ryu_char.setOrigin(37, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 165);
		break;
	case 6:
		ryu_char.setTextureRect(IntRect(432, 131, 50, 89));
		ryu_char.setOrigin(36, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 168);
		frame_counter_r = 0;
		break;
	}

	if (!(Keyboard::isKeyPressed(Keyboard::A))) {
		key_press_state_r = key_press_state_r & (~_A_);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		frame_counter_r = 1;
		time_accum_4 = 0;
		dist_accum_r = 0;
		ryu_char.setPosition(ryu_char.getPosition().x + 14, ryu_char.getPosition().y);
	}
}

void ryu_walk_b(Sprite& ryu_char, float& time_accum_4, int& key_press_state_r, int& frame_counter_r, float& dist_accum_r) {

	while ((time_accum_4 >= 90)) {
		time_accum_4 = time_accum_4 - 90;
		frame_counter_r = frame_counter_r + 1;
	}

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(542, 132, 61, 87));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 170);
		break;
	case 2:
		ryu_char.setTextureRect(IntRect(628, 128, 59, 90));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 166);
		break;
	case 3:
		ryu_char.setTextureRect(IntRect(713, 126, 57, 90));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 165);
		break;
	case 4:
		ryu_char.setTextureRect(IntRect(797, 126, 58, 90));
		ryu_char.setOrigin(35, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 163);
		break;
	case 5:
		ryu_char.setTextureRect(IntRect(883, 127, 58, 91));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 166);
		frame_counter_r = 0;
		break;
	}

	if (!(Keyboard::isKeyPressed(Keyboard::D))) {
		key_press_state_r = key_press_state_r & (~_D_);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		frame_counter_r = 1;
		time_accum_4 = 0;
	}
}

void ryu_sit(Sprite& ryu_char, float& time_accum_4, int& frame_counter_r, int& key_press_state_r) {

	while (time_accum_4 >= 45) {
		time_accum_4 = time_accum_4 - 45;
		frame_counter_r = frame_counter_r + 1;
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(26, 1213, 53, 83));
			ryu_char.setOrigin(34, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, 174);
			break;
		case 2:
			ryu_char.setTextureRect(IntRect(115, 1227, 57, 69));
			ryu_char.setOrigin(32, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, 188);
			break;
		case 3:
			ryu_char.setTextureRect(IntRect(197, 1235, 61, 61));
			ryu_char.setOrigin(33, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, 196);
			break;
		default:
			ryu_char.setTextureRect(IntRect(197, 1235, 61, 61));
			ryu_char.setOrigin(33, 10);
			ryu_char.setPosition(ryu_char.getPosition().x, 196);
			break;
		}
	}

	if (!(Keyboard::isKeyPressed(Keyboard::S))) {
		key_press_state_r = key_press_state_r & (~_S_);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		time_accum_4 = 0;
		frame_counter_r = 1;
	}
}

void ryu_jump_animation(Sprite& ryu_char, float& time_accum_4, int& key_press_state_r, int& frame_counter_r, int& random_bool_store, float& time_accum_5) {

	while (time_accum_4 >= 10) {
		time_accum_4 = time_accum_4 - 10;
		frame_counter_r = frame_counter_r + 1;
	}

	if ((random_bool_store & (1 << 2)) == (1 << 2)) {
		if (time_accum_5 >= 430) {
			random_bool_store = random_bool_store & (~(1 << 2));
			time_accum_5 = 0;
			frame_counter_r = 0;
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 3);
		switch (frame_counter_r) {
		case 8:
			ryu_char.setTextureRect(IntRect(100, 823, 56, 104));
			ryu_char.setOrigin(31, 10);
			break;
		case 9:
			ryu_char.setTextureRect(IntRect(100, 823, 56, 104));
			ryu_char.setOrigin(31, 10);
			break;
		case 26:
			ryu_char.setTextureRect(IntRect(176, 805, 50, 89));
			ryu_char.setOrigin(30, 10);
			break;
		case 27:
			ryu_char.setTextureRect(IntRect(176, 805, 50, 89));
			ryu_char.setOrigin(30, 10);
			break;
		case 34:
			ryu_char.setTextureRect(IntRect(251, 798, 54, 77));
			ryu_char.setOrigin(35, 10);
			break;
		case 35:
			ryu_char.setTextureRect(IntRect(251, 798, 54, 77));
			ryu_char.setOrigin(35, 10);
			break;
		}
	}
	else {
		if (time_accum_5 >= 430) {
			random_bool_store = random_bool_store | (1 << 3);
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 3);
		switch (frame_counter_r) {
		case 3:
			ryu_char.setTextureRect(IntRect(327, 813, 48, 70));
			ryu_char.setOrigin(37, 10);
			break;
		case 4:
			ryu_char.setTextureRect(IntRect(327, 813, 48, 70));
			ryu_char.setOrigin(37, 10);
			break;
		case 15:
			ryu_char.setTextureRect(IntRect(397, 810, 48, 89));
			ryu_char.setOrigin(30, 13);
			break;
		case 16:
			ryu_char.setTextureRect(IntRect(397, 810, 48, 89));
			ryu_char.setOrigin(30, 13);
			break;
		case 20:
			ryu_char.setTextureRect(IntRect(464, 819, 55, 109));
			ryu_char.setOrigin(38, 10);
			break;
		case 21:
			ryu_char.setTextureRect(IntRect(464, 819, 55, 109));
			ryu_char.setOrigin(38, 10);
			break;
		case 37:
			ryu_char.setTextureRect(IntRect(17, 847, 55, 85));
			ryu_char.setOrigin(31, 10);
			break;
		case 38:
			ryu_char.setTextureRect(IntRect(17, 847, 55, 85));
			ryu_char.setOrigin(31, 10);
			break;
		}
	};

	if ((random_bool_store & (1 << 3)) == (1 << 3)) {
		key_press_state_r = key_press_state_r & (~_W_);
		key_press_state_r = key_press_state_r & (~_S_);
		key_press_state_r = key_press_state_r & (~_Q_);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		frame_counter_r = 1;
		time_accum_4 = 0;
	};
}

void ryu_jump_animation_L() {

}

void ryu_jump_animation_R() {

}

void ryu_block(Sprite& ryu_char, int& key_press_state_r, float& time_accum_4, int& frame_counter_r, int& pos_x_r, int x = 1) {

	if (x == 2) {
		ryu_char.setTextureRect(IntRect(73, 3840, 83, 85));
	}	//hit
	else {
		if (!(Keyboard::isKeyPressed(Keyboard::S))) {
			ryu_char.setTextureRect(IntRect(443, 2335, 63, 92));
			ryu_char.setOrigin(30, 9);
			ryu_char.setPosition(pos_x_r + 7, 164);
		}
		else {
			ryu_char.setTextureRect(IntRect(38, 2368, 55, 61));
			ryu_char.setOrigin(30, 9);
			ryu_char.setPosition(pos_x_r, 196);
		}
	};	//no hit


	if (!(Keyboard::isKeyPressed(Keyboard::Q))) {
		key_press_state_r = key_press_state_r & (~_Q_);
		ryu_char.setPosition(pos_x_r, ryu_char.getPosition().y);
		frame_counter_r = 3;
		if (!(Keyboard::isKeyPressed(Keyboard::S))) {
			frame_counter_r = 1;
			key_press_state_r = key_press_state_r & (~_S_);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			time_accum_4 = 0;
		}
	}
}

int main() {

	int case_store = 1;

	float dt;

	float time_accum = 0;					//BG TIME ACCUM
	float time_accum_2 = 0;					//BG TIME ACCUM
	float time_accum_3 = 0;					//CHUNLI TIME ACCUM
	float time_accum_4 = 0;					//RYU TIME ACCUM
	float time_accum_5 = 0;
	int frame_counter_c = 1;				//CHUNLI FRAME COUNTER
	int frame_counter_r = 1;				//RYU FRAME COUNTER
	int key_press_state = 0;
	int key_press_state_r = 0;
	float dist_accum_c = 0;
	float dist_accum_r = 0;

	int pos_x_c;
	int pos_y_c;
	int pos_x_r;
	int pos_y_r;


	int random_bool_store = 0;				//0 and 1 for chunli_jumping    2 and 3 for ryu jumping    4 for ryu block animation cancel

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

	bg_stage.setSmooth(false);

	chunli_bg_display.setTexture(bg_stage.getTexture());
	chunli_bg_display.setTextureRect(IntRect(0, 44, 400, 225));

	//CHUNLI ELEMENTS

	(texture_elements.chunli_char_t).loadFromFile("ChunLi Sprites/ChunLi2.png");

	Sprite chunli_char;
	Sprite chunli_shadow;

	chunli_char.setTexture(texture_elements.chunli_char_t);
	chunli_shadow.setTexture(texture_elements.chunli_char_t);
	chunli_shadow.setTextureRect(IntRect(14, 135, 74, 12));

	chunli_shadow.setOrigin(74.0 / 2, 12.0 / 2);

	chunli_shadow.setPosition(94, 247);
	chunli_char.setPosition(99, 247);

	texture_elements.chunli_char_t.setSmooth(false);

	//RYU ELEMENTS

	(texture_elements.ryu_char_t).loadFromFile("Ryu Sprites/Ryu.png");

	Sprite ryu_char;
	Sprite ryu_shadow;

	ryu_shadow.setTexture(texture_elements.chunli_char_t);
	ryu_char.setTexture(texture_elements.ryu_char_t);
	ryu_shadow.setTextureRect(IntRect(14, 135, 74, 12));

	ryu_shadow.setOrigin(74.0 / 2, 12.0 / 2);
	ryu_char.setScale(-1.0f, 1.0f);
	ryu_shadow.setScale(-1.0f, 1.0f);

	ryu_char.setPosition(300, 247);
	ryu_shadow.setPosition(300, 247);

	key_press_state_r = key_press_state_r & (~ANYKEY);

	Clock clock1;

	while (window1.isOpen()) {

		chunli_bg_display.setScale(1.0f, 1.0f);

		dt = (clock1.restart()).asMilliseconds();
		time_accum = time_accum + dt;
		time_accum_2 = time_accum_2 + dt;
		time_accum_3 = time_accum_3 + dt;
		time_accum_4 = time_accum_4 + dt;
		time_accum_5 = time_accum_5 + dt;

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};

		//______________________CHUNLI INPUT______________________________________________

		if (Keyboard::isKeyPressed(Keyboard::Space) && ((key_press_state & ANIMATION_ON) != ANIMATION_ON)) {

			key_press_state = key_press_state & (~UP);
			key_press_state = key_press_state & (~DOWN);
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
			key_press_state = key_press_state | ANIMATION_ON;
			key_press_state = key_press_state | ANYKEY;
			random_bool_store = random_bool_store | (1 << 0);
			random_bool_store = random_bool_store & (~(1 << 1));
			time_accum_2 = 0;
			time_accum_3 = 0;
			frame_counter_c = 1;

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				key_press_state = key_press_state | SPACE_L;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				key_press_state = key_press_state | SPACE_R;
				chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 73);
			}
			else {
				key_press_state = key_press_state | SPACE_0;
				chunli_char.setTextureRect(IntRect(0, 2368, 74, 81));
				chunli_char.setOrigin(74.0 / 2, 12.0);
				chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 70);

			}

		};

		if (Keyboard::isKeyPressed((Keyboard::Right)) && (key_press_state & ANYKEY) != ANYKEY && (key_press_state & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state = key_press_state | RIGHT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter_c = 1;
			dist_accum_c = 0;
		};

		if (Keyboard::isKeyPressed((Keyboard::Left)) && (key_press_state & ANYKEY) != ANYKEY && (key_press_state & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state = key_press_state | LEFT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter_c = 1;
			dist_accum_c = 0;
		};

		if (Keyboard::isKeyPressed(Keyboard::Up) && ((key_press_state & ANIMATION_ON) != ANIMATION_ON) && (key_press_state & UP) != UP) {
			key_press_state = key_press_state | UP;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
		};

		if (Keyboard::isKeyPressed(Keyboard::Down) && (key_press_state & ANIMATION_ON) != ANIMATION_ON && (key_press_state & DOWN) != DOWN) {
			key_press_state = key_press_state | DOWN;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
			time_accum_3 = 0;
			frame_counter_c = 1;
		};

		//________________________CHUNLI ANIMATION_______________________________________________

		if ((key_press_state & SPACE_0) == SPACE_0) {
			chunli_jump_animation(chunli_char, time_accum_3, random_bool_store, frame_counter_c, time_accum_2, key_press_state);
		}

		else if ((key_press_state & SPACE_L) == SPACE_L) {
			chunli_jump_animation_L();
		}

		else if ((key_press_state & SPACE_R) == SPACE_R) {
			chunli_jump_animation_R(chunli_char, time_accum_3, frame_counter_c, random_bool_store, time_accum_2, key_press_state);
		}

		else if ((key_press_state & RIGHT) == RIGHT) {
			chunli_walk_f_animation(chunli_char, time_accum_3, frame_counter_c, key_press_state, chunli_shadow, dist_accum_c);
			if ((chunli_char.getGlobalBounds().left + chunli_char.getGlobalBounds().width + 4) < ryu_char.getGlobalBounds().left) {
				//chunli_char.setPosition(chunli_char.getPosition().x + round((dt * 0.18) + dist_accum_c), chunli_char.getPosition().y);
				dist_accum_c = ((dt * 0.18) + dist_accum_c) - round((dt * 0.18) + dist_accum_c);
				//}
			}
		}

		else if (((key_press_state & LEFT) == LEFT)) {
			chunli_walk_b_animation(chunli_char, time_accum_3, frame_counter_c, key_press_state, chunli_shadow, dist_accum_c);
			if (chunli_char.getPosition().x >= 35) {
				chunli_char.setPosition(chunli_char.getPosition().x - round((dt * 0.15) + dist_accum_c), chunli_char.getPosition().y);
				dist_accum_c = ((dt * 0.15) + dist_accum_c) - round((dt * 0.15) + dist_accum_c);
			}
		}

		else if ((key_press_state & UP) == UP) {
			chunli_block(chunli_char, key_press_state, time_accum_3, frame_counter_c);
		}

		else if (((key_press_state & DOWN) == DOWN) && (key_press_state & UP) != UP) {
			chunli_sit(chunli_char, time_accum_3, frame_counter_c, key_press_state, chunli_shadow);
		};

		if (((key_press_state & ANYKEY) != ANYKEY)) {
			chunli_idle_animation(chunli_char, time_accum_3, frame_counter_c);
		};

		// _____________________________________________________________________ RYU INPUT___________________________________________________________________________________


		if (Keyboard::isKeyPressed(Keyboard::W) && ((key_press_state_r & ANIMATION_ON) != ANIMATION_ON)) {

			key_press_state_r = key_press_state_r & (~_Q_);
			key_press_state_r = key_press_state_r & (~_S_);

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				key_press_state_r = key_press_state_r | _W_L;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | ANYKEY;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				key_press_state_r = key_press_state_r | _W_R;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | ANYKEY;
			}
			else {
				key_press_state_r = key_press_state_r | _W_;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r & (~_A_);
				key_press_state_r = key_press_state_r & (~_D_);
				random_bool_store = random_bool_store | (1 << 2);
				random_bool_store = random_bool_store & (~(1 << 3));
				ryu_char.setTextureRect(IntRect(17, 847, 55, 85));
				ryu_char.setOrigin(40, 10);
				ryu_char.setPosition(ryu_char.getPosition().x, 172);
				time_accum_5 = 0;
				time_accum_4 = 0;
				frame_counter_r = 1;
			};

		};

		if (Keyboard::isKeyPressed(Keyboard::Q) && ((key_press_state_r & ANIMATION_ON) != ANIMATION_ON) && (key_press_state_r & _Q_) != _Q_) {
			key_press_state_r = key_press_state_r | _Q_;
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_r = key_press_state_r & (~_A_);
			key_press_state_r = key_press_state_r & (~_D_);
			pos_x_r = ryu_char.getPosition().x;
			pos_y_r = ryu_char.getPosition().y;
			random_bool_store = random_bool_store & (~(1 << 4));
		};

		if (Keyboard::isKeyPressed((Keyboard::D)) && (key_press_state_r & ANYKEY) != ANYKEY && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state_r = key_press_state_r | _D_;
			key_press_state_r = key_press_state_r | ANYKEY;
			time_accum_4 = 0;
			frame_counter_r = 1;
			dist_accum_r = 0;
		};

		if (Keyboard::isKeyPressed((Keyboard::A)) && (key_press_state_r & ANYKEY) != ANYKEY && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state_r = key_press_state_r | _A_;
			key_press_state_r = key_press_state_r | ANYKEY;
			time_accum_4 = 0;
			frame_counter_r = 1;
			dist_accum_r = 0;
			ryu_char.setPosition(ryu_char.getPosition().x - 14, 168);
		};

		if (Keyboard::isKeyPressed(Keyboard::S) && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON && (key_press_state_r & _S_) != _S_) {
			key_press_state_r = key_press_state_r | _S_;
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_r = key_press_state_r & (~_A_);
			key_press_state_r = key_press_state_r & (~_D_);
			time_accum_4 = 0;
			frame_counter_r = 1;
		};

		//________________________________RYU ANIMATION_______________________

		if ((key_press_state_r & _W_) == _W_) {
			ryu_jump_animation(ryu_char, time_accum_4, key_press_state_r, frame_counter_r, random_bool_store, time_accum_5);
		}

		else if ((key_press_state_r & _W_L) == _W_L) {
			ryu_jump_animation_L();
		}

		else if ((key_press_state_r & _W_R) == _W_R) {
			ryu_jump_animation_R();
		}

		else if ((key_press_state_r & _A_) == _A_) {
			ryu_walk_f(frame_counter_r, time_accum_4, ryu_char, key_press_state_r, dist_accum_r);
			if ((chunli_char.getGlobalBounds().left + chunli_char.getGlobalBounds().width - 10) < ryu_char.getGlobalBounds().left) {
				ryu_char.setPosition(ryu_char.getPosition().x - round((dt * 0.14) + dist_accum_r), ryu_char.getPosition().y);
				dist_accum_r = ((dt * 0.14) + dist_accum_r) - round((dt * 0.14) + dist_accum_r);
			}
			ryu_shadow.setPosition(ryu_char.getPosition().x + 20, ryu_shadow.getPosition().y);
		}

		else if (((key_press_state_r & _D_) == _D_)) {
			ryu_walk_b(ryu_char, time_accum_4, key_press_state_r, frame_counter_r, dist_accum_r);
			if (ryu_char.getPosition().x <= 365) {
				ryu_char.setPosition(ryu_char.getPosition().x + round((dt * 0.12) + dist_accum_r), ryu_char.getPosition().y);
				dist_accum_r = ((dt * 0.12) + dist_accum_r) - round((dt * 0.12) + dist_accum_r);
			}
			ryu_shadow.setPosition(ryu_char.getPosition().x, ryu_shadow.getPosition().y);
		}

		else if ((key_press_state_r & _Q_) == _Q_) {
			ryu_block(ryu_char, key_press_state_r, time_accum_4, frame_counter_r, pos_x_r);
		}

		else if (((key_press_state_r & _S_) == _S_) && (key_press_state_r & _Q_) != _Q_) {
			ryu_sit(ryu_char, time_accum_4, frame_counter_r, key_press_state_r);
		};

		if ((key_press_state_r & ANYKEY) != ANYKEY) {
			ryu_idle(frame_counter_r, time_accum_4, ryu_char, ryu_shadow);
		};


		bg_animation(time_accum, chunli_bg_fishermen, chunli_bg_mom, chunli_bg_hen, chunli_bg_laundry);


		//_____________________________________________________________DISPLAY________________________________________________________


		bg_stage.clear();
		bg_stage.draw(chunli_bg_stage);
		bg_stage.draw(chunli_bg_fishermen);
		bg_stage.draw(chunli_bg_hen);
		bg_stage.draw(chunli_bg_laundry);
		bg_stage.draw(chunli_bg_mom);
		bg_stage.draw(chunli_shadow);
		//bg_stage.draw(ryu_shadow);
		bg_stage.draw(chunli_char);
		//bg_stage.draw(ryu_char);
		bg_stage.display();

		bg_stage.setSmooth(false);

		chunli_bg_display.setScale(4.8f, 4.8f);

		window1.clear();
		window1.draw(chunli_bg_display);
		window1.display();
	}
}