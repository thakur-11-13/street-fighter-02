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
	Texture hit;
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
constexpr auto chunli_light_hit = 1 << 9;
constexpr auto chunli_heavy_hit = 1 << 10;
constexpr auto PUNCH_C_LIGHT = 1 << 11;				//Light punch chunli
constexpr auto KICK_C_LIGHT = 1 << 12;				//light kick chunli
constexpr auto PUNCH_C_HEAVY = 1 << 13;				//heavy punch chunli
constexpr auto KICK_C_HEAVY = 1 << 14;				//heavy kick chunli
constexpr auto HURT_C = 1 << 15;

//RYU INPUT STATES

constexpr auto _W_ = 1 << 1;
constexpr auto _D_ = 1 << 2;
constexpr auto _A_ = 1 << 3;
constexpr auto _S_ = 1 << 4;
constexpr auto _Q_ = 1 << 5;
constexpr auto _W_L = 1 << 6;
constexpr auto _W_R = 1 << 7;
constexpr auto ryu_light_hit = 1 << 9;
constexpr auto ryu_heavy_hit = 1 << 10;
constexpr auto PUNCH_R_LIGHT = 1 << 11;			//Light Punch ryu
constexpr auto KICK_R_LIGHT = 1 << 12;			//Light kick ryu
constexpr auto PUNCH_R_HEAVY = 1 << 13;			//heavy punch ryu
constexpr auto KICK_R_HEAVY = 1 << 14;			//Heavy kick ryu

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


void chunli_jump_animation(Sprite& chunli_char, int& random_bool_store, int& frame_counter_c, int& key_press_state, float time_frame_accum_c) {

	frame_counter_c = frame_counter_c + 1;

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {

		if (frame_counter_c >= 86) {
			random_bool_store = random_bool_store & (~(1 << 0));
			frame_counter_c = 0;
		}

		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 2);
		switch (frame_counter_c) {
		case 10:
			chunli_char.setTextureRect(IntRect(74, 2340, 47, 109));
			chunli_char.setOrigin(19.0, 12.0);
			break;
		case 29:
			chunli_char.setTextureRect(IntRect(148, 2365, 50, 84));
			chunli_char.setOrigin(29.0 / 2, 12.0);
			break;
		case 48:
			chunli_char.setTextureRect(IntRect(222, 2374, 52, 75));
			chunli_char.setOrigin(15.0, 12.0);
			break;
		case 67:
			chunli_char.setTextureRect(IntRect(296, 2384, 57, 65));
			chunli_char.setOrigin(35.0 / 2, 12.0);
			break;
		}
	}
	else if ((random_bool_store & (1 << 0)) != (1 << 0) && (random_bool_store & (1 << 1)) != (1 << 1)) {

		if (frame_counter_c >= 86) {
			random_bool_store = random_bool_store | (1 << 1);
		}

		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y + 2);
		switch (frame_counter_c) {
		case 18:
			chunli_char.setTextureRect(IntRect(370, 2374, 52, 75));
			chunli_char.setOrigin(15.0, 12.0);
			break;
		case 36:
			chunli_char.setTextureRect(IntRect(444, 2365, 50, 84));
			chunli_char.setOrigin(29.0 / 2, 12.0);
			break;
		case 54:
			chunli_char.setTextureRect(IntRect(518, 2340, 47, 109));
			chunli_char.setOrigin(19.0, 12.0);
			break;
		case 74:
			chunli_char.setTextureRect(IntRect(592, 2368, 74, 81));
			chunli_char.setOrigin(74.0 / 2, 12.0);
			break;
		}
	}
	else if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~SPACE_0);
		key_press_state = key_press_state & (~ANYKEY);
		key_press_state = key_press_state & (~ANIMATION_ON);
		frame_counter_c = 0;
		time_frame_accum_c = 5;
	};
}

void chunli_jump_animation_L(Sprite& chunli_char, int& frame_counter_c, int& random_bool_store, int& key_press_state, float& dt, Sprite& chunli_shadow, float& time_frame_accum_c) {

	frame_counter_c = frame_counter_c + 1;

	chunli_shadow.setPosition(chunli_char.getPosition().x, chunli_shadow.getPosition().y);

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {

		if (frame_counter_c >= 86) {
			random_bool_store = random_bool_store & (~(1 << 0));
			frame_counter_c = 0;
		};

		if (chunli_char.getPosition().x >= 30) {
			chunli_char.setPosition(chunli_char.getPosition().x - 1, chunli_char.getPosition().y);
		};

		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 2);

		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(16, 3718, 74, 81));
			chunli_char.setOrigin(29, 36);
			break;
		case 10:
			chunli_char.setTextureRect(IntRect(580, 3689, 47, 109));
			chunli_char.setOrigin(21, 37);
			break;
		case 29:
			chunli_char.setTextureRect(IntRect(153, 3723, 95, 76));
			chunli_char.setOrigin(42, 20);
			break;
		case 48:
			chunli_char.setTextureRect(IntRect(256, 3733, 119, 66));
			chunli_char.setOrigin(35, 34);
			break;
		case 67:
			chunli_char.setTextureRect(IntRect(1037, 3718, 110, 81));
			chunli_char.setOrigin(36, 51);
			break;
		}
	}
	else if ((random_bool_store & (1 << 0)) != (1 << 0) && (random_bool_store & (1 << 1)) != (1 << 1)) {

		if (chunli_char.getPosition().y > 202) {
			random_bool_store = random_bool_store | (1 << 1);
		}

		if (chunli_char.getPosition().x >= 30) {
			chunli_char.setPosition(chunli_char.getPosition().x - 1, chunli_char.getPosition().y);
		};

		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y + 2);

		switch (frame_counter_c) {
		case 14:
			chunli_char.setTextureRect(IntRect(977, 3695, 52, 104));
			chunli_char.setOrigin(31, 69);
			break;
		case 29:
			chunli_char.setTextureRect(IntRect(860, 3711, 109, 88));
			chunli_char.setOrigin(77, 56);
			break;
		case 44:
			chunli_char.setTextureRect(IntRect(383, 3738, 45, 61));
			chunli_char.setOrigin(26, 29);
			break;
		case 59:
			chunli_char.setTextureRect(IntRect(580, 3689, 47, 109));
			chunli_char.setOrigin(21, 37);
			break;
		case 74:
			chunli_char.setTextureRect(IntRect(16, 3718, 74, 81));
			chunli_char.setOrigin(29, 36);
			break;
		}
	}

	else if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~ANYKEY);
		key_press_state = key_press_state & (~SPACE_L);
		key_press_state = key_press_state & (~ANIMATION_ON);
		frame_counter_c = 0;
		time_frame_accum_c = 5;
	}
}
void chunli_jump_animation_R(Sprite& chunli_char, int& frame_counter_c, int& random_bool_store, int& key_press_state, float& dt, int& pos_x_c, int& pos_y_c, Sprite& ryu_char, float time_frame_accum_c, Sprite& chunli_shadow) {

	frame_counter_c = frame_counter_c + 1;

	chunli_shadow.setPosition(chunli_char.getPosition().x, chunli_shadow.getPosition().y);

	if ((random_bool_store & (1 << 0)) == (1 << 0)) {

		if (frame_counter_c >= 86) {
			random_bool_store = random_bool_store & (~(1 << 0));
			frame_counter_c = 0;
		};

		if (chunli_char.getPosition().x <= ryu_char.getPosition().x - 70) {
			chunli_char.setPosition(chunli_char.getPosition().x + 1, chunli_char.getPosition().y);
		};

		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 2);

		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(16, 3718, 74, 81));
			chunli_char.setOrigin(29, 36);
			break;
		case 12:
			chunli_char.setTextureRect(IntRect(580, 3689, 47, 109));
			chunli_char.setOrigin(21, 37);
			break;
		case 27:
			chunli_char.setTextureRect(IntRect(635, 3718, 88, 81));
			chunli_char.setOrigin(42, 20);
			break;
		case 42:
			chunli_char.setTextureRect(IntRect(731, 3751, 121, 48));
			chunli_char.setOrigin(86, 20);
			break;
		case 57:
			chunli_char.setTextureRect(IntRect(860, 3711, 109, 88));
			chunli_char.setOrigin(77, 56);
			break;
		case 72:
			chunli_char.setTextureRect(IntRect(977, 3695, 52, 104));
			chunli_char.setOrigin(31, 69);
			break;
		}
	}
	else if ((random_bool_store & (1 << 0)) != (1 << 0) && (random_bool_store & (1 << 1)) != (1 << 1)) {

		if (chunli_char.getPosition().y > 202) {
			random_bool_store = random_bool_store | (1 << 1);
		}

		if (chunli_char.getPosition().x <= ryu_char.getPosition().x - 70) {
			chunli_char.setPosition(chunli_char.getPosition().x + 1, chunli_char.getPosition().y);
		};
		chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y + 2);

		switch (frame_counter_c) {
		case 15:
			chunli_char.setTextureRect(IntRect(1037, 3718, 110, 81));
			chunli_char.setOrigin(36, 51);
			break;
		case 31:
			chunli_char.setTextureRect(IntRect(1155, 3733, 119, 66));
			chunli_char.setOrigin(37, 35);
			break;
		case 46:
			chunli_char.setTextureRect(IntRect(1282, 3723, 95, 76));
			chunli_char.setOrigin(43, 21);
			break;
		case 61:
			chunli_char.setTextureRect(IntRect(1386, 3689, 47, 109));
			chunli_char.setOrigin(20, 37);
			break;
		case 74:
			chunli_char.setTextureRect(IntRect(1440, 3718, 74, 81));
			chunli_char.setOrigin(26, 36);
			break;
		}
	}

	else if ((random_bool_store & (1 << 1)) == (1 << 1)) {
		key_press_state = key_press_state & (~ANYKEY);
		key_press_state = key_press_state & (~SPACE_R);
		key_press_state = key_press_state & (~ANIMATION_ON);
		frame_counter_c = 0;
		time_frame_accum_c = 5;
	}
}

void chunli_idle_animation(Sprite& chunli_char, int& frame_counter_c) {

	chunli_char.setPosition(chunli_char.getPosition().x, 247);
	chunli_char.setOrigin(72.0 / 2, 87);

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(16, 32, 80, 87));
		break;
	case 34:
		chunli_char.setTextureRect(IntRect(97, 32, 80, 87));
		break;
	case 67:
		chunli_char.setTextureRect(IntRect(178, 32, 80, 87));
		break;
	case 100:
		chunli_char.setTextureRect(IntRect(259, 32, 80, 87));
		break;
	case 133:
		chunli_char.setTextureRect(IntRect(16, 32, 80, 87));
		frame_counter_c = 1;
		break;
	}
}

void chunli_walk_f_animation(Sprite& chunli_char, int& frame_counter_c, int& key_press_state, Sprite& chunli_shadow, float& time_frame_accum_c) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(0, 164, 78, 84));
		chunli_char.setOrigin(73.0 / 2, 84);
		break;
	case 17:
		chunli_char.setTextureRect(IntRect(81, 161, 71, 87));
		chunli_char.setOrigin(58.0 / 2, 87);
		break;
	case 33:
		chunli_char.setTextureRect(IntRect(162, 160, 65, 88));
		chunli_char.setOrigin(40.0 / 2, 88);
		break;
	case 49:
		chunli_char.setTextureRect(IntRect(243, 159, 62, 89));
		chunli_char.setOrigin(31.0 / 2, 89);
		break;
	case 65:
		chunli_char.setTextureRect(IntRect(324, 160, 67, 88));
		chunli_char.setOrigin(35.0 / 2, 88);
		chunli_char.setPosition(chunli_char.getPosition().x, 248);
		break;
	case 81:
		chunli_char.setTextureRect(IntRect(405, 161, 77, 87));
		chunli_char.setOrigin(54.0 / 2, 87);
		break;
	case 97:
		chunli_char.setTextureRect(IntRect(486, 162, 82, 86));
		chunli_char.setOrigin(68.0 / 2, 86);
		break;
	case 113:
		chunli_char.setTextureRect(IntRect(591, 161, 77, 87));
		chunli_char.setOrigin(54.0 / 2, 87);
		break;
	case 129:
		chunli_char.setTextureRect(IntRect(672, 160, 67, 88));
		chunli_char.setOrigin(35.0 / 2, 88);
		break;
	case 145:
		chunli_char.setTextureRect(IntRect(753, 159, 62, 89));
		chunli_char.setOrigin(31.0 / 2, 89);
		chunli_char.setPosition(chunli_char.getPosition().x, 247);
		break;
	case 161:
		chunli_char.setTextureRect(IntRect(834, 160, 65, 88));
		chunli_char.setOrigin(43.0 / 2, 88);
		break;
	case 177:
		chunli_char.setTextureRect(IntRect(915, 161, 71, 87));
		chunli_char.setOrigin(58.0 / 2, 87);
		break;
	case 193:
		chunli_char.setTextureRect(IntRect(0, 164, 78, 84));
		chunli_char.setOrigin(73.0 / 2, 84);
		frame_counter_c = 1;
		break;
	}

	chunli_shadow.setPosition(chunli_char.getPosition().x - 2, chunli_shadow.getPosition().y);
}
void chunli_walk_b_animation(Sprite& chunli_char, int& frame_counter_c, int& key_press_state, Sprite& chunli_shadow, float time_frame_accum_c) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(0, 293, 73, 86));
		chunli_char.setOrigin(73.0 / 2, 86);
		break;
	case 17:
		chunli_char.setTextureRect(IntRect(89, 290, 63, 89));
		chunli_char.setOrigin(58.0 / 2, 89);
		break;
	case 33:
		chunli_char.setTextureRect(IntRect(162, 289, 60, 90));
		chunli_char.setOrigin(51.0 / 2, 90);
		break;
	case 49:
		chunli_char.setTextureRect(IntRect(235, 288, 63, 91));
		chunli_char.setOrigin(51.0 / 2, 91);
		break;
	case 65:
		chunli_char.setTextureRect(IntRect(308, 289, 64, 90));
		chunli_char.setOrigin(52.0 / 2, 90);
		break;
	case 81:
		chunli_char.setTextureRect(IntRect(381, 290, 65, 89));
		chunli_char.setOrigin(54.0 / 2, 89);
		break;
	case 97:
		chunli_char.setTextureRect(IntRect(454, 291, 72, 88));
		chunli_char.setOrigin(68.0 / 2, 88);
		break;
	case 113:
		chunli_char.setTextureRect(IntRect(531, 290, 65, 89));
		chunli_char.setOrigin(54.0 / 2, 89);
		break;
	case 129:
		chunli_char.setTextureRect(IntRect(600, 289, 64, 90));
		chunli_char.setOrigin(52.0 / 2, 89);
		break;
	case 145:
		chunli_char.setTextureRect(IntRect(673, 288, 63, 91));
		chunli_char.setOrigin(51.0 / 2, 91);
		break;
	case 161:
		chunli_char.setTextureRect(IntRect(746, 289, 60, 90));
		chunli_char.setOrigin(51.0 / 2, 90);
		break;
	case 177:
		chunli_char.setTextureRect(IntRect(819, 290, 63, 89));
		chunli_char.setOrigin(58.0 / 2, 89);
		break;
	case 193:
		chunli_char.setTextureRect(IntRect(0, 293, 73, 86));
		chunli_char.setOrigin(73.0 / 2, 86);
		frame_counter_c = 1;
		break;
	}

	chunli_shadow.setPosition(chunli_char.getPosition().x, chunli_shadow.getPosition().y);
}

void chunli_sit(Sprite& chunli_char, int& frame_counter_c, int& key_press_state, Sprite& chunli_shadow, float& time_frame_accum_c) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(0, 1998, 74, 81));
		chunli_char.setOrigin(74.0 / 2, 81);
		break;
	case 13:
		chunli_char.setTextureRect(IntRect(74, 2007, 73, 72));
		chunli_char.setOrigin(73.0 / 2, 72);
		break;
	case 25:
		chunli_char.setTextureRect(IntRect(147, 2013, 72, 66));
		chunli_char.setOrigin(72.0 / 2, 66);
		key_press_state = key_press_state & (~ANIMATION_ON);
		break;
	}

	chunli_shadow.setPosition(chunli_char.getPosition().x, chunli_shadow.getPosition().y);

	if (frame_counter_c >= 25) {
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			chunli_char.setTextureRect(IntRect(309, 3857, 73, 68));
			chunli_char.setOrigin(73.0 / 2, 68);
		}
		else {
			frame_counter_c = 24;
			key_press_state = key_press_state & (~UP);
		}
	}
}

void chunli_block(Sprite& chunli_char, int& key_press_state, int& frame_counter_c, float time_frame_accum_c, int x = 1) {

	key_press_state = key_press_state & (~DOWN);
	chunli_char.setTextureRect(IntRect(0, 3839, 73, 86));
	chunli_char.setOrigin(73.0 / 2, 86);

}

void chunli_light_punch(Sprite& chunli_char, float& time_frame_accum_c, int& frame_counter_c, int& key_press_state, int& random_bool_store, int& pos_x_c, int& pos_y_c, Sprite& chunli_shadow) {

	frame_counter_c = frame_counter_c + 1;

	if ((random_bool_store & (1 << 4)) == (1 << 4)) {
		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(16, 428, 78, 87));
			chunli_char.setOrigin(0, 87);
			chunli_char.setPosition(pos_x_c - 35, chunli_char.getPosition().y);
			break;
		case 15:
			chunli_char.setTextureRect(IntRect(102, 426, 101, 89));
			chunli_char.setOrigin(0, 89);
			chunli_char.setPosition(pos_x_c - 35, chunli_char.getPosition().y);
			break;
		case 30:
			chunli_char.setTextureRect(IntRect(211, 419, 87, 96));
			chunli_char.setOrigin(0, 96);
			chunli_char.setPosition(pos_x_c - 35, chunli_char.getPosition().y);
			break;
		case 45:
			chunli_char.setTextureRect(IntRect(102, 426, 101, 89));
			chunli_char.setOrigin(0, 89);
			chunli_char.setPosition(pos_x_c - 35, chunli_char.getPosition().y);
			break;
		case 60:
			chunli_char.setTextureRect(IntRect(16, 428, 78, 87));
			chunli_char.setOrigin(0, 87);
			chunli_char.setPosition(pos_x_c - 35, chunli_char.getPosition().y);
			break;
		case 74:
			frame_counter_c = 0;
			time_frame_accum_c = 5;
			key_press_state = key_press_state & (~ANIMATION_ON);
			key_press_state = key_press_state & (~PUNCH_C_LIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			chunli_char.setPosition(pos_x_c, pos_y_c);
			break;
		};
	}
	else {
		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(541, 431, 101, 84));
			chunli_char.setOrigin(0, 84);
			chunli_char.setPosition(pos_x_c - 36, pos_y_c + 1);
			chunli_shadow.setTextureRect(IntRect(14, 135, 74, 12));
			chunli_shadow.setOrigin(74.0 / 2, 12.0 / 2);
			chunli_shadow.setPosition(chunli_char.getPosition().x + 60, chunli_shadow.getPosition().y);
			break;
		case 12:
			chunli_char.setTextureRect(IntRect(650, 434, 119, 81));
			chunli_char.setOrigin(0, 81);
			chunli_char.setPosition(pos_x_c - 36, pos_y_c);
			chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
			chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
			chunli_shadow.setPosition(chunli_char.getPosition().x + 60, chunli_shadow.getPosition().y);
			break;
		case 28:
			chunli_char.setTextureRect(IntRect(777, 434, 143, 82));
			chunli_char.setOrigin(0, 82);
			chunli_char.setPosition(pos_x_c - 36, pos_y_c + 1);
			chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
			chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
			chunli_shadow.setPosition(chunli_char.getPosition().x + 70, chunli_shadow.getPosition().y);
			break;
		case 44:
			chunli_char.setTextureRect(IntRect(650, 434, 119, 81));
			chunli_char.setOrigin(0, 81);
			chunli_char.setPosition(pos_x_c - 36, pos_y_c + 1);
			chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
			chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
			chunli_shadow.setPosition(chunli_char.getPosition().x + 60, chunli_shadow.getPosition().y);
			break;
		case 60:
			chunli_char.setTextureRect(IntRect(541, 431, 101, 84));
			chunli_char.setOrigin(0, 84);
			chunli_char.setPosition(pos_x_c - 36, pos_y_c + 1);
			chunli_shadow.setTextureRect(IntRect(14, 135, 74, 12));
			chunli_shadow.setOrigin(74.0 / 2, 12.0 / 2);
			chunli_shadow.setPosition(chunli_char.getPosition().x + 60, chunli_shadow.getPosition().y);
			break;
		case 71:
			frame_counter_c = 0;
			time_frame_accum_c = 5;
			key_press_state = key_press_state & (~ANIMATION_ON);
			key_press_state = key_press_state & (~PUNCH_C_LIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			chunli_char.setPosition(pos_x_c, pos_y_c);
			chunli_shadow.setPosition(pos_x_c, pos_y_c);
			chunli_shadow.setTextureRect(IntRect(14, 135, 74, 12));
			chunli_shadow.setOrigin(74.0 / 2, 12.0 / 2);
			break;
		}
	}
}

void chunli_light_kick(Sprite& chunli_char, int& frame_counter_c, float& time_frame_accum_c, int& key_press_state, int& pos_x_c, int& pos_y_c, int& random_bool_store, FloatRect& chunli_damage_box) {

	frame_counter_c = frame_counter_c + 1;

	if ((random_bool_store & (1 << 6)) == (1 << 6)) {
		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(476, 962, 66, 89));
			chunli_char.setOrigin(18, 89);
			chunli_char.setPosition(pos_x_c - 27, pos_y_c);
			break;
		case 21:
			chunli_char.setTextureRect(IntRect(550, 958, 71, 93));
			chunli_char.setOrigin(22, 93);
			break;
		case 42:
			chunli_char.setTextureRect(IntRect(629, 956, 109, 95));
			chunli_char.setOrigin(33, 95);
			break;
		case 63:
			chunli_char.setTextureRect(IntRect(746, 958, 71, 93));
			chunli_char.setOrigin(23, 93);
			break;
		case 84:
			chunli_char.setTextureRect(IntRect(476, 962, 66, 89));
			chunli_char.setOrigin(18, 89);
			break;
		case 104:
			key_press_state = key_press_state & (~ANIMATION_ON);
			key_press_state = key_press_state & (~KICK_C_LIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			chunli_char.setPosition(pos_x_c, pos_y_c);
			time_frame_accum_c = 5;
			frame_counter_c = 0;
			chunli_damage_box.left = -100;
			break;
		};
	}
	else {
		switch (frame_counter_c) {
		case 1:
			chunli_char.setTextureRect(IntRect(522, 1096, 96, 98));
			chunli_char.setOrigin(60, 97);
			chunli_char.setPosition(pos_x_c + 28, pos_y_c);
			break;
		case 18:
			chunli_char.setTextureRect(IntRect(626, 1098, 86, 96));
			chunli_char.setOrigin(53, 96);
			break;
		case 36:
			chunli_char.setTextureRect(IntRect(720, 1097, 87, 97));
			chunli_char.setOrigin(19, 97);
			break;
		case 54:
			chunli_char.setTextureRect(IntRect(815, 1091, 64, 103));
			chunli_char.setOrigin(20, 103);
			chunli_damage_box.left = chunli_char.getTextureRect().left + 65;
			chunli_damage_box.top = chunli_char.getTextureRect().top + 40;
			chunli_damage_box.width = 18;
			chunli_damage_box.height = 18;
			break;
		case 72:
			chunli_char.setTextureRect(IntRect(720, 1097, 87, 97));
			chunli_char.setOrigin(19, 97);
			break;
		case 90:
			chunli_char.setTextureRect(IntRect(626, 1098, 86, 96));
			chunli_char.setOrigin(53, 96);
			break;
		case 108:
			chunli_char.setTextureRect(IntRect(522, 1096, 96, 98));
			chunli_char.setOrigin(60, 97);
			break;
		case 125:
			key_press_state = key_press_state & (~ANIMATION_ON);
			key_press_state = key_press_state & (~KICK_C_LIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			chunli_char.setPosition(pos_x_c, pos_y_c);
			time_frame_accum_c = 5;
			frame_counter_c = 0;
			chunli_damage_box.left = -100;
			break;
		};
	}
}

void chunli_heavy_punch(Sprite& chunli_char, int& frame_counter_c, float& time_frame_accum_c, int& key_press_state, int& pos_x_c, int& pos_y_c, Sprite& chunli_shadow) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(16, 561, 101, 84));
		chunli_char.setOrigin(7, 84);
		chunli_char.setPosition(pos_x_c - 28, pos_y_c);
		chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
		chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
		chunli_shadow.setPosition(chunli_char.getPosition().x + 40, chunli_shadow.getPosition().y);
		break;
	case 18:
		chunli_char.setTextureRect(IntRect(125, 566, 119, 79));
		chunli_char.setOrigin(8, 79);
		chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
		chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
		chunli_shadow.setPosition(chunli_char.getPosition().x + 50, chunli_shadow.getPosition().y);
		break;
	case 36:
		chunli_char.setTextureRect(IntRect(252, 567, 131, 78));
		chunli_char.setOrigin(10, 78);
		chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
		chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
		chunli_shadow.setPosition(chunli_char.getPosition().x + 50, chunli_shadow.getPosition().y);
		break;
	case 54:
		chunli_char.setTextureRect(IntRect(390, 566, 119, 79));
		chunli_char.setOrigin(8, 79);
		chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
		chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
		chunli_shadow.setPosition(chunli_char.getPosition().x + 50, chunli_shadow.getPosition().y);
		break;
	case 72:
		chunli_char.setTextureRect(IntRect(517, 561, 101, 84));
		chunli_char.setOrigin(7, 84);
		chunli_shadow.setTextureRect(IntRect(776, 517, 136, 12));
		chunli_shadow.setOrigin(136.0 / 2, 12.0 / 2);
		chunli_shadow.setPosition(chunli_char.getPosition().x + 40, chunli_shadow.getPosition().y);
		break;
	case 89:
		key_press_state = key_press_state & (~ANIMATION_ON);
		key_press_state = key_press_state & (~KICK_C_HEAVY);
		key_press_state = key_press_state & (~ANYKEY);
		chunli_char.setPosition(pos_x_c, pos_y_c);
		time_frame_accum_c = 5;
		frame_counter_c = 0;
		chunli_shadow.setPosition(pos_x_c, pos_y_c);
		chunli_shadow.setTextureRect(IntRect(14, 135, 74, 12));
		chunli_shadow.setOrigin(74.0 / 2, 12.0 / 2);
		break;
	};
}

void chunli_heavy_kick(Sprite& chunli_char, int& frame_counter_c, float& time_frame_accum_c, int& key_press_state, int& pos_x_c, int& pos_y_c) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(939, 973, 64, 78));
		chunli_char.setOrigin(60, 78);
		chunli_char.setPosition(pos_x_c + 32, 247);
		break;
	case 16:
		chunli_char.setTextureRect(IntRect(1011, 959, 70, 92));
		chunli_char.setOrigin(51, 92);
		break;
	case 32:
		chunli_char.setTextureRect(IntRect(1089, 961, 82, 90));
		chunli_char.setOrigin(57, 90);
		break;
	case 48:
		chunli_char.setTextureRect(IntRect(1179, 954, 123, 97));
		chunli_char.setOrigin(62, 97);
		break;
	case 64:
		chunli_char.setTextureRect(IntRect(1310, 968, 102, 83));
		chunli_char.setOrigin(62, 83);
		break;
	case 80:
		chunli_char.setTextureRect(IntRect(1420, 970, 70, 81));
		chunli_char.setOrigin(61, 81);
		break;
	case 95:
		key_press_state = key_press_state & (~ANIMATION_ON);
		key_press_state = key_press_state & (~KICK_C_HEAVY);
		key_press_state = key_press_state & (~ANYKEY);
		chunli_char.setPosition(pos_x_c, 247);
		time_frame_accum_c = 5;
		frame_counter_c = 0;
		break;
	};
}

void chunli_sit_punch(Sprite& chunli_char, int& frame_counter_c, float& time_frame_accum_c, int& key_press_state, int& pos_x_c, int& pos_y_c) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(16, 2120, 71, 66));
		chunli_char.setOrigin(8, 66);
		chunli_char.setPosition(pos_x_c - 27, pos_y_c);
		break;
	case 16:
		chunli_char.setTextureRect(IntRect(95, 2120, 77, 66));
		chunli_char.setOrigin(8, 66);
		break;
	case 32:
		chunli_char.setTextureRect(IntRect(180, 2122, 107, 64));
		chunli_char.setOrigin(7, 63);
		break;
	case 48:
		chunli_char.setTextureRect(IntRect(95, 2120, 77, 66));
		chunli_char.setOrigin(8, 66);
		break;
	case 64:
		chunli_char.setTextureRect(IntRect(16, 2120, 71, 66));
		chunli_char.setOrigin(8, 66);
		break;
	case 79:
		key_press_state = key_press_state & (~ANIMATION_ON);
		key_press_state = key_press_state & (~PUNCH_C_LIGHT);
		time_frame_accum_c = 5;
		frame_counter_c = 22;
		chunli_char.setTextureRect(IntRect(147, 2013, 72, 66));
		chunli_char.setOrigin(72.0 / 2, 66);
		chunli_char.setPosition(pos_x_c, 247);
		break;
	};
}

void chunli_sit_kick(Sprite& chunli_char, int& frame_counter_c, float& time_frame_accum_c, int& key_press_state, int& pos_x_c, int& pos_y_c) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(16, 2241, 63, 58));
		chunli_char.setOrigin(6, 58);
		chunli_char.setPosition(pos_x_c - 27, pos_y_c);
		break;
	case 16:
		chunli_char.setTextureRect(IntRect(87, 2241, 61, 58));
		chunli_char.setOrigin(22, 56);
		break;
	case 32:
		chunli_char.setTextureRect(IntRect(156, 2251, 107, 48));
		chunli_char.setOrigin(23, 47);
		break;
	case 48:
		chunli_char.setTextureRect(IntRect(87, 2241, 61, 58));
		chunli_char.setOrigin(22, 56);
		break;
	case 64:
		chunli_char.setTextureRect(IntRect(16, 2241, 63, 58));
		chunli_char.setOrigin(6, 58);
		break;
	case 79:
		key_press_state = key_press_state & (~ANIMATION_ON);
		key_press_state = key_press_state & (~PUNCH_C_LIGHT);
		time_frame_accum_c = 5;
		frame_counter_c = 22;
		chunli_char.setTextureRect(IntRect(147, 2013, 72, 66));
		chunli_char.setOrigin(72.0 / 2, 66);
		chunli_char.setPosition(pos_x_c, 247);
		break;
	};
}



//			______________________________________RYU ANIMATION_____________________________________________________________



void ryu_idle(int& frame_counter_r, float& time_accum_4, Sprite& ryu_char, Sprite& ryu_shadow) {

	frame_counter_r = frame_counter_r + 1;

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(0, 3, 59, 90));
		ryu_char.setOrigin(36, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 167);
		break;
	case 20:
		ryu_char.setTextureRect(IntRect(75, 4, 60, 89));
		ryu_char.setPosition(ryu_char.getPosition().x, 168);
		break;
	case 39:
		ryu_char.setTextureRect(IntRect(151, 3, 59, 90));
		ryu_char.setPosition(ryu_char.getPosition().x, 167);
		break;
	case 58:
		ryu_char.setTextureRect(IntRect(226, 0, 55, 93));
		ryu_char.setPosition(ryu_char.getPosition().x, 164);
		break;
	case 77:
		ryu_char.setTextureRect(IntRect(0, 3, 59, 90));
		ryu_char.setPosition(ryu_char.getPosition().x, 167);
		frame_counter_r = 1;
		break;
	}
	ryu_shadow.setPosition(ryu_char.getPosition().x, ryu_shadow.getPosition().y);
};

void ryu_walk_f(int& frame_counter_r, float& time_frame_accum_r, Sprite& ryu_char, int& key_press_state_r, int& pos_x_r, Sprite& chunli_char) {

	/*if ((chunli_char.getGlobalBounds().left + chunli_char.getGlobalBounds().width - 17) < ryu_char.getGlobalBounds().left) {
		pos_x_r = pos_x_r - 1;
		ryu_char.setPosition(ryu_char.getPosition().x - 1, ryu_char.getPosition().y);
	}*/

	frame_counter_r = frame_counter_r + 1;

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(9, 136, 52, 83));
		ryu_char.setOrigin(39, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 174);
		break;
	case 11:
		ryu_char.setTextureRect(IntRect(78, 130, 60, 88));
		ryu_char.setOrigin(46, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 168);
		break;
	case 21:
		ryu_char.setTextureRect(IntRect(162, 126, 64, 92));
		ryu_char.setOrigin(47, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 163);
		break;
	case 31:
		ryu_char.setTextureRect(IntRect(259, 127, 63, 90));
		ryu_char.setOrigin(41, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 164);
		break;
	case 41:
		ryu_char.setTextureRect(IntRect(352, 127, 54, 91));
		ryu_char.setOrigin(37, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 165);
		break;
	case 51:
		ryu_char.setTextureRect(IntRect(432, 131, 50, 89));
		ryu_char.setOrigin(36, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 168);
		break;
	case 61:
		ryu_char.setTextureRect(IntRect(9, 136, 52, 83));
		ryu_char.setOrigin(39, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 174);
		frame_counter_r = 1;
		break;
	}

};

void ryu_walk_b(Sprite& ryu_char, float& time_frame_accum_r, int& key_press_state_r, int& frame_counter_r) {

	frame_counter_r = frame_counter_r + 1;

	/*if (ryu_char.getPosition().x <= 365) {
		ryu_char.setPosition(ryu_char.getPosition().x + 1, ryu_char.getPosition().y);
	}*/

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(542, 132, 61, 87));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 170);
		break;
	case 14:
		ryu_char.setTextureRect(IntRect(628, 128, 59, 90));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 166);
		break;
	case 27:
		ryu_char.setTextureRect(IntRect(713, 126, 57, 90));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 165);
		break;
	case 40:
		ryu_char.setTextureRect(IntRect(797, 126, 58, 90));
		ryu_char.setOrigin(35, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 163);
		break;
	case 53:
		ryu_char.setTextureRect(IntRect(883, 127, 58, 91));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(ryu_char.getPosition().x, 166);
		frame_counter_r = 0;
		break;
	}
};

void ryu_sit(Sprite& ryu_char, float& time_frame_accum_r, int& frame_counter_r, int& key_press_state_r, int& pos_x_r, int& pos_y_r) {

	frame_counter_r = frame_counter_r + 1;

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(26, 1213, 53, 83));
		ryu_char.setOrigin(34, 10);
		ryu_char.setPosition(pos_x_r, 174);
		break;
	case 12:
		ryu_char.setTextureRect(IntRect(115, 1227, 57, 69));
		ryu_char.setOrigin(32, 10);
		ryu_char.setPosition(pos_x_r, 188);
		break;
	case 23:
		ryu_char.setTextureRect(IntRect(197, 1235, 61, 61));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(pos_x_r, 196);
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		break;
	}

	if (frame_counter_r >= 23) {
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			ryu_char.setTextureRect(IntRect(38, 2368, 55, 61));
			ryu_char.setOrigin(30, 9);
			ryu_char.setPosition(pos_x_r, 196);
		}
		else {
			frame_counter_r = 22;
			key_press_state_r = key_press_state_r & (~_Q_);
		}
	}
};

void ryu_jump_animation(Sprite& ryu_char, float& time_frame_accum_r, int& key_press_state_r, int& frame_counter_r, int& random_bool_store) {

	frame_counter_r = frame_counter_r + 1;

	if ((random_bool_store & (1 << 2)) == (1 << 2)) {

		if (frame_counter_r >= 58) {
			random_bool_store = random_bool_store & (~(1 << 2));
			frame_counter_r = 0;
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 3);
		switch (frame_counter_r) {
		case 9:
			ryu_char.setTextureRect(IntRect(100, 823, 56, 104));
			ryu_char.setOrigin(31, 10);
			break;
		case 25:
			ryu_char.setTextureRect(IntRect(176, 805, 50, 89));
			ryu_char.setOrigin(30, 10);
			break;
		case 41:
			ryu_char.setTextureRect(IntRect(251, 798, 54, 77));
			ryu_char.setOrigin(35, 10);
			break;
		}
	}
	else {

		if (frame_counter_r >= 58) {
			random_bool_store = random_bool_store | (1 << 3);
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 3);
		switch (frame_counter_r) {
		case 12:
			ryu_char.setTextureRect(IntRect(327, 813, 48, 70));
			ryu_char.setOrigin(37, 10);
			break;
		case 25:
			ryu_char.setTextureRect(IntRect(397, 810, 48, 89));
			ryu_char.setOrigin(30, 13);
			break;
		case 38:
			ryu_char.setTextureRect(IntRect(464, 819, 55, 109));
			ryu_char.setOrigin(38, 10);
			break;
		case 50:
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
		frame_counter_r = 0;
		time_frame_accum_r = 7.5;
	};
};

void ryu_jump_animation_R(Sprite& ryu_char, int& frame_counter_r, int& random_bool_store, int& key_press_state_r, Sprite& ryu_shadow, float& time_frame_accum_r, Sprite& chunli_char) {

	frame_counter_r = frame_counter_r + 1;

	if ((random_bool_store & (1 << 2)) == (1 << 2)) {

		if (frame_counter_r >= 58) {
			random_bool_store = random_bool_store & (~(1 << 2));
			frame_counter_r = 0;
		};

		if (ryu_char.getPosition().x < 362) {
			ryu_char.setPosition(ryu_char.getPosition().x + 1, ryu_char.getPosition().y);
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 3);

		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(637, 657, 60, 94));
			ryu_char.setOrigin(25, 41);
			break;
		case 8:
			ryu_char.setTextureRect(IntRect(594, 823, 55, 103));
			ryu_char.setOrigin(24, 39);
			break;
		case 20:
			ryu_char.setTextureRect(IntRect(1064, 806, 71, 87));
			ryu_char.setOrigin(41, 27);
			break;
		case 32:
			ryu_char.setTextureRect(IntRect(927, 808, 122, 44));
			ryu_char.setOrigin(50, 19);
			break;
		case 44:
			ryu_char.setTextureRect(IntRect(864, 79, 53, 82));
			ryu_char.setOrigin(31, 42);
			break;
		}
	}
	else {

		if (frame_counter_r >= 58) {
			random_bool_store = random_bool_store | (1 << 3);
		};

		if (ryu_char.getPosition().x < 362) {
			ryu_char.setPosition(ryu_char.getPosition().x + 1, ryu_char.getPosition().y);
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 3);

		switch (frame_counter_r) {
		case 8:
			ryu_char.setTextureRect(IntRect(744, 811, 104, 42));
			ryu_char.setOrigin(65, 18);
		case 22:
			ryu_char.setTextureRect(IntRect(669, 813, 61, 78));
			ryu_char.setOrigin(26, 28);
			break;
		case 36:
			ryu_char.setTextureRect(IntRect(1149, 802, 55, 109));
			ryu_char.setOrigin(26, 51);
			break;
		case 50:
			ryu_char.setTextureRect(IntRect(637, 657, 60, 94));
			ryu_char.setOrigin(25, 41);
			break;
		}
	};

	ryu_shadow.setPosition(ryu_char.getPosition().x, ryu_shadow.getPosition().y);

	if ((random_bool_store & (1 << 3)) == (1 << 3)) {
		key_press_state_r = key_press_state_r & (~ANYKEY);
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		key_press_state_r = key_press_state_r & (~_W_R);
		frame_counter_r = 0;
		time_frame_accum_r = 7.5;
	}
};

void ryu_jump_animation_L(Sprite& ryu_char, int& frame_counter_r, int& random_bool_store, int& key_press_state_r, Sprite& ryu_shadow, float& time_frame_accum_r, Sprite& chunli_char) {

	frame_counter_r = frame_counter_r + 1;

	if ((random_bool_store & (1 << 2)) == (1 << 2)) {

		if (frame_counter_r >= 58) {
			random_bool_store = random_bool_store & (~(1 << 2));
			frame_counter_r = 0;
		};

		if (ryu_char.getGlobalBounds().left > (chunli_char.getGlobalBounds().left + chunli_char.getGlobalBounds().width)) {
			ryu_char.setPosition(ryu_char.getPosition().x - 2, ryu_char.getPosition().y);
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y - 3);

		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(637, 657, 60, 94));
			ryu_char.setOrigin(25, 41);
			break;
		case 8:
			ryu_char.setTextureRect(IntRect(594, 823, 55, 103));
			ryu_char.setOrigin(24, 39);
			break;
		case 20:
			ryu_char.setTextureRect(IntRect(669, 813, 61, 78));
			ryu_char.setOrigin(26, 28);
			break;
		case 32:
			ryu_char.setTextureRect(IntRect(744, 811, 104, 42));
			ryu_char.setOrigin(65, 18);
			break;
		case 44:
			ryu_char.setTextureRect(IntRect(864, 79, 53, 82));
			ryu_char.setOrigin(31, 42);
			break;
		}
	}
	else {

		if (frame_counter_r >= 58) {
			random_bool_store = random_bool_store | (1 << 3);
		};

		if (ryu_char.getGlobalBounds().left > (chunli_char.getGlobalBounds().left + chunli_char.getGlobalBounds().width)) {
			ryu_char.setPosition(ryu_char.getPosition().x - 2, ryu_char.getPosition().y);
		};

		ryu_char.setPosition(ryu_char.getPosition().x, ryu_char.getPosition().y + 3);

		switch (frame_counter_r) {
		case 8:
			ryu_char.setTextureRect(IntRect(927, 808, 122, 44));
			ryu_char.setOrigin(50, 19);
			break;
		case 22:
			ryu_char.setTextureRect(IntRect(1064, 806, 71, 87));
			ryu_char.setOrigin(41, 27);
			break;
		case 36:
			ryu_char.setTextureRect(IntRect(1149, 802, 55, 109));
			ryu_char.setOrigin(26, 51);
			break;
		case 50:
			ryu_char.setTextureRect(IntRect(637, 657, 60, 94));
			ryu_char.setOrigin(25, 41);
			break;
		}
	};

	ryu_shadow.setPosition(ryu_char.getPosition().x, ryu_shadow.getPosition().y);

	if ((random_bool_store & (1 << 3)) == (1 << 3)) {
		key_press_state_r = key_press_state_r & (~ANYKEY);
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		key_press_state_r = key_press_state_r & (~_W_L);
		frame_counter_r = 0;
		time_frame_accum_r = 7.5;
	}
};

void ryu_block(Sprite& ryu_char, int& key_press_state_r, float& time_frame_accum_r, int& frame_counter_r, int& pos_x_r, int x = 1) {

	key_press_state_r = key_press_state_r & (~_S_);
	ryu_char.setTextureRect(IntRect(443, 2335, 63, 92));
	ryu_char.setOrigin(30, 9);
	ryu_char.setPosition(pos_x_r + 7, 164);

};

void ryu_light_punch(Sprite& ryu_char, int& frame_counter_r, int& key_press_state_r, int& random_bool_store, float& time_frame_accum_r, int& pos_x_r, int& pos_y_r, Sprite& ryu_shadow, FloatRect& ryu_damage_box) {

	frame_counter_r = frame_counter_r + 1;

	if (((random_bool_store & (1 << 5)) == (1 << 5))) {
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(253, 269, 60, 94));
			ryu_char.setOrigin(0, 94);
			ryu_char.setPosition(pos_x_r + 32, 247);
			ryu_shadow.setPosition(ryu_char.getPosition().x - 28, ryu_shadow.getPosition().y);
			break;
		case 16:
			ryu_char.setTextureRect(IntRect(108, 272, 92, 91));
			ryu_char.setOrigin(7, 91);
			ryu_char.setPosition(pos_x_r + 32, 247);
			ryu_shadow.setPosition(ryu_char.getPosition().x - 28, ryu_shadow.getPosition().y);
			ryu_damage_box.width = 18;
			ryu_damage_box.height = 18;
			ryu_damage_box.left = ryu_char.getGlobalBounds().left + 14;
			ryu_damage_box.top = ryu_char.getGlobalBounds().top;
			break;
		case 32:
			ryu_char.setTextureRect(IntRect(253, 269, 60, 94));
			ryu_char.setOrigin(0, 94);
			ryu_char.setPosition(pos_x_r + 32, 247);
			ryu_shadow.setPosition(ryu_char.getPosition().x - 28, ryu_shadow.getPosition().y);
			ryu_damage_box.left = -100;
			break;
		case 47:
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;
			key_press_state_r = key_press_state_r & (~ANIMATION_ON);
			key_press_state_r = key_press_state_r & (~PUNCH_R_LIGHT);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			ryu_char.setPosition(pos_x_r, pos_y_r);
			ryu_shadow.setPosition(pos_x_r, ryu_shadow.getPosition().y);
		}
	}
	else {
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(253, 269, 60, 94));
			ryu_char.setOrigin(37, 10);
			ryu_char.setPosition(pos_x_r - 5, 163);
			ryu_shadow.setPosition(ryu_char.getPosition().x + 10, ryu_shadow.getPosition().y);
			break;
		case 10:
			ryu_char.setTextureRect(IntRect(333, 268, 74, 95));
			ryu_char.setOrigin(50, 10);
			ryu_char.setPosition(pos_x_r - 15, 163);
			ryu_shadow.setPosition(ryu_char.getPosition().x + 12, ryu_shadow.getPosition().y);
			break;
		case 23:
			ryu_char.setTextureRect(IntRect(432, 268, 108, 94));
			ryu_char.setOrigin(57, 10);
			ryu_char.setPosition(pos_x_r - 25, 163);
			ryu_shadow.setPosition(ryu_char.getPosition().x + 22, ryu_shadow.getPosition().y);
			ryu_damage_box.width = 18;
			ryu_damage_box.height = 18;
			ryu_damage_box.left = ryu_char.getGlobalBounds().left + 22;
			ryu_damage_box.top = ryu_char.getGlobalBounds().top;
			break;
		case 36:
			ryu_char.setTextureRect(IntRect(333, 268, 74, 95));
			ryu_char.setOrigin(50, 10);
			ryu_char.setPosition(pos_x_r - 15, 163);
			ryu_shadow.setPosition(ryu_char.getPosition().x + 12, ryu_shadow.getPosition().y);
			ryu_damage_box.left = -100;
			break;
		case 49:
			ryu_char.setTextureRect(IntRect(253, 269, 60, 94));
			ryu_char.setOrigin(37, 10);
			ryu_char.setPosition(pos_x_r - 5, 163);
			ryu_shadow.setPosition(ryu_char.getPosition().x, ryu_shadow.getPosition().y);
			ryu_shadow.setPosition(ryu_char.getPosition().x + 10, ryu_shadow.getPosition().y);
			break;
		case 58:
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;
			key_press_state_r = key_press_state_r & (~ANIMATION_ON);
			key_press_state_r = key_press_state_r & (~PUNCH_R_LIGHT);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			ryu_char.setPosition(pos_x_r, pos_y_r);
			ryu_shadow.setPosition(300, 247);
		}
	}
};

void ryu_light_kick(Sprite& ryu_char, int& frame_counter_r, int& key_press_state_r, int& random_bool_store, float& time_frame_accum_r, int& pos_x_r, int& pos_y_r, Sprite& ryu_shadow, FloatRect& ryu_damage_box) {

	frame_counter_r = frame_counter_r + 1;

	if ((random_bool_store & (1 << 6)) == (1 << 6)) {
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(606, 269, 60, 94));
			ryu_char.setOrigin(9, 94);
			ryu_char.setPosition(pos_x_r + 21, 247);
			break;
		case 16:
			ryu_char.setTextureRect(IntRect(689, 267, 66, 92));
			ryu_char.setOrigin(28, 92);
			break;
		case 32:
			ryu_char.setTextureRect(IntRect(777, 265, 114, 94));
			ryu_char.setOrigin(50, 94);
			ryu_damage_box.width = 18;
			ryu_damage_box.height = 18;
			ryu_damage_box.left = ryu_char.getGlobalBounds().left + 7;
			ryu_damage_box.top = ryu_char.getGlobalBounds().top - 10;
			break;
		case 48:
			ryu_char.setTextureRect(IntRect(689, 267, 66, 92));
			ryu_char.setOrigin(28, 92);
			ryu_damage_box.left = -100;
			break;
		case 64:
			ryu_char.setTextureRect(IntRect(606, 269, 60, 94));
			ryu_char.setOrigin(9, 94);
			break;
		case 79:
			key_press_state_r = key_press_state_r & (~ANIMATION_ON);
			key_press_state_r = key_press_state_r & (~KICK_R_LIGHT);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			ryu_char.setPosition(pos_x_r, ryu_char.getPosition().y);
			time_frame_accum_r = 7.5;
			frame_counter_r = 0;
			break;
		}
	}
	else {
		switch (frame_counter_r) {
		case 1:
			ryu_char.setTextureRect(IntRect(637, 657, 60, 94));
			ryu_char.setOrigin(48, 94);
			ryu_char.setPosition(pos_x_r - 10, 247);
			break;
		case 18:
			ryu_char.setTextureRect(IntRect(720, 657, 54, 94));
			ryu_char.setOrigin(27, 94);
			break;
		case 36:
			ryu_char.setTextureRect(IntRect(797, 629, 49, 122));
			ryu_char.setOrigin(22, 122);
			break;
		case 51:
			ryu_char.setTextureRect(IntRect(875, 640, 93, 111));
			ryu_char.setOrigin(14, 111);
			ryu_damage_box.width = 18;
			ryu_damage_box.height = 18;
			ryu_damage_box.left = ryu_char.getGlobalBounds().left + 13;
			ryu_damage_box.top = ryu_char.getGlobalBounds().top + 17;
			break;
		case 72:
			ryu_char.setTextureRect(IntRect(989, 657, 48, 94));
			ryu_char.setOrigin(27, 94);
			ryu_damage_box.left = -100;
			break;
		case 89:
			key_press_state_r = key_press_state_r & (~ANIMATION_ON);
			key_press_state_r = key_press_state_r & (~KICK_R_LIGHT);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			ryu_char.setPosition(pos_x_r, ryu_char.getPosition().y);
			time_frame_accum_r = 7.5;
			frame_counter_r = 0;
			break;
		}
	}
};

void ryu_heavy_punch(Sprite& ryu_char, int& frame_counter_r, int& key_press_state_r, float& time_frame_accum_r, int& pos_x_r, int& pos_y_r, Sprite& ryu_shadow, FloatRect& ryu_damage_box) {

	frame_counter_r = frame_counter_r + 1;

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(759, 519, 66, 93));
		ryu_char.setOrigin(9, 93);
		ryu_char.setPosition(pos_x_r + 28, 247);
		break;
	case 16:
		ryu_char.setTextureRect(IntRect(848, 518, 93, 94));
		ryu_char.setOrigin(8, 94);
		ryu_char.setPosition(pos_x_r + 28, 247);
		break;
	case 32:
		ryu_char.setTextureRect(IntRect(950, 500, 82, 113));
		ryu_char.setOrigin(7, 112);
		ryu_char.setPosition(pos_x_r + 28, 247);
		ryu_damage_box.width = 18;
		ryu_damage_box.height = 18;
		ryu_damage_box.left = ryu_char.getGlobalBounds().left;
		ryu_damage_box.top = ryu_char.getGlobalBounds().top + 22;
		break;
	case 48:
		ryu_char.setTextureRect(IntRect(18, 519, 60, 94));
		ryu_char.setOrigin(9, 94);
		ryu_char.setPosition(pos_x_r + 28, 247);
		ryu_damage_box.left = -100;
		break;
	case 63:
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		key_press_state_r = key_press_state_r & (~PUNCH_R_HEAVY);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		ryu_char.setPosition(pos_x_r, ryu_char.getPosition().y);
		time_frame_accum_r = 7.5;
		frame_counter_r = 0;
		break;
	}
	ryu_shadow.setPosition(ryu_char.getPosition().x - 14, ryu_shadow.getPosition().y);
};

void ryu_heavy_kick(Sprite& ryu_char, int& frame_counter_r, int& key_press_state_r, float& time_frame_accum_r, int& pos_x_r, int& pos_y_r, Sprite& ryu_shadow, FloatRect& ryu_damage_box) {

	frame_counter_r = frame_counter_r + 1;

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(16, 398, 61, 90));
		ryu_char.setOrigin(50, 90);
		ryu_char.setPosition(pos_x_r - 3, 247);
		break;
	case 12:
		ryu_char.setTextureRect(IntRect(99, 394, 94, 94));
		ryu_char.setOrigin(57, 94);
		break;
	case 24:
		ryu_char.setTextureRect(IntRect(211, 394, 120, 94));
		ryu_char.setOrigin(61, 94);
		ryu_damage_box.width = 18;
		ryu_damage_box.height = 18;
		ryu_damage_box.left = ryu_char.getGlobalBounds().left + 11;
		ryu_damage_box.top = ryu_char.getGlobalBounds().top;
		break;
	case 36:
		ryu_char.setTextureRect(IntRect(351, 411, 101, 76));
		ryu_char.setOrigin(60, 77);
		ryu_damage_box.left = -100;
		break;
	case 48:
		ryu_char.setTextureRect(IntRect(482, 407, 64, 81));
		ryu_char.setOrigin(56, 81);
		break;
	case 59:
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		key_press_state_r = key_press_state_r & (~KICK_R_HEAVY);
		key_press_state_r = key_press_state_r & (~ANYKEY);
		ryu_char.setPosition(pos_x_r, ryu_char.getPosition().y);
		time_frame_accum_r = 7.5;
		frame_counter_r = 0;
		break;
	}
};

void ryu_sit_punch(Sprite& ryu_char, int& frame_counter_r, int& key_press_state_r, float& time_frame_accum_r, int& pos_x_r, int& pos_y_r, int& x) {

	frame_counter_r = frame_counter_r + 1;

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(265, 1344, 64, 61));
		ryu_char.setOrigin(32, 60);
		ryu_char.setPosition(pos_x_r + 1, pos_y_r + 50);
		break;
	case 15:
		ryu_char.setTextureRect(IntRect(359, 1344, 66, 61));
		ryu_char.setPosition(pos_x_r + 1, pos_y_r + 50);
		break;
	case 30:
		ryu_char.setTextureRect(IntRect(450, 1343, 92, 62));
		ryu_char.setPosition(pos_x_r + 1, pos_y_r + 49);
		break;
	case 45:
		ryu_char.setTextureRect(IntRect(359, 1344, 66, 61));
		ryu_char.setPosition(pos_x_r + 1, pos_y_r + 50);
		break;
	case 60:
		ryu_char.setTextureRect(IntRect(265, 1344, 64, 61));
		ryu_char.setPosition(pos_x_r + 1, pos_y_r + 50);
		break;
	case 74:
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		key_press_state_r = key_press_state_r & (~PUNCH_R_LIGHT);
		time_frame_accum_r = 7.5;
		frame_counter_r = 22;
		ryu_char.setTextureRect(IntRect(197, 1235, 61, 61));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(pos_x_r, 196);
		break;
	}
}

void ryu_sit_kick(Sprite& ryu_char, int& frame_counter_r, int& key_press_state_r, float& time_frame_accum_r, int& pos_x_r, int& pos_y_r) {

	frame_counter_r = frame_counter_r + 1;

	switch (frame_counter_r) {
	case 1:
		ryu_char.setTextureRect(IntRect(26, 1444, 70, 64));
		ryu_char.setOrigin(29, 64);
		ryu_char.setPosition(pos_x_r + 3, pos_y_r + 51);
		break;
	case 14:
		ryu_char.setTextureRect(IntRect(125, 1449, 97, 60));
		ryu_char.setOrigin(19, 59);
		ryu_char.setPosition(pos_x_r + 3, pos_y_r + 51);
		break;
	case 28:
		ryu_char.setTextureRect(IntRect(241, 1455, 146, 53));
		ryu_char.setOrigin(37, 52);
		ryu_char.setPosition(pos_x_r + 3, pos_y_r + 51);
		break;
	case 42:
		ryu_char.setTextureRect(IntRect(125, 1449, 97, 60));
		ryu_char.setOrigin(19, 59);
		ryu_char.setPosition(pos_x_r + 3, pos_y_r + 51);
		break;
	case 56:
		ryu_char.setTextureRect(IntRect(26, 1444, 70, 64));
		ryu_char.setOrigin(29, 64);
		ryu_char.setPosition(pos_x_r + 3, pos_y_r + 51);
		break;
	case 69:
		key_press_state_r = key_press_state_r & (~ANIMATION_ON);
		key_press_state_r = key_press_state_r & (~KICK_R_LIGHT);
		time_frame_accum_r = 7.5;
		frame_counter_r = 22;
		ryu_char.setTextureRect(IntRect(197, 1235, 61, 61));
		ryu_char.setOrigin(33, 10);
		ryu_char.setPosition(pos_x_r, 196);
		break;
	}
}



void chunli_hurt(Sprite& chunli_char, Sprite& ryu_char, int& frame_counter_c, float& time_frame_accum_c, Sprite& chunli_shadow, int& pos_x_c, int& pos_y_c, int& key_press_state, Sprite& hit, FloatRect& ryu_damage_box, Sprite& ryu_shadow) {

	frame_counter_c = frame_counter_c + 1;

	switch (frame_counter_c) {
	case 1:
		chunli_char.setTextureRect(IntRect(16, 4288, 73, 92));
		chunli_char.setOrigin(38, 92);
		chunli_char.setPosition(pos_x_c, pos_y_c);
		hit.setPosition(ryu_damage_box.left - 30, ryu_damage_box.top);
		hit.setTextureRect(IntRect(160, 16, 9, 10));
		break;
	case 17:
		chunli_char.setTextureRect(IntRect(97, 4288, 76, 92));
		chunli_char.setOrigin(83.0 / 2, 92);
		hit.setPosition(hit.getPosition().x - 20, hit.getPosition().y);
		hit.setTextureRect(IntRect(178, 15, 13, 11));
		break;
	case 33:
		chunli_char.setTextureRect(IntRect(181, 4290, 87, 90));
		chunli_char.setOrigin(104.0 / 2, 90);
		hit.setPosition(hit.getPosition().x - 10, hit.getPosition().y);
		hit.setTextureRect(IntRect(199, 15, 13, 11));
		break;
	case 49:
		chunli_char.setTextureRect(IntRect(97, 4288, 76, 92));
		chunli_char.setOrigin(83.0 / 2, 92);
		hit.setPosition(-300, 0);
		break;
	case 65:
		chunli_char.setTextureRect(IntRect(16, 4288, 73, 92));
		chunli_char.setOrigin(38, 92);
		break;
	case 81:
		frame_counter_c = 0;
		time_frame_accum_c = 5;
		key_press_state = key_press_state & (~ANIMATION_ON);
		key_press_state = key_press_state & (~ANYKEY);
		key_press_state = key_press_state & (~HURT_C);
		break;
	}

	pos_x_c = pos_x_c - 1;
	chunli_char.setPosition(pos_x_c, pos_y_c);
	chunli_shadow.setPosition(pos_x_c, chunli_shadow.getPosition().y);

}







int main() {

	int case_store = 1;

	float dt;

	float time_frame_accum_c = 5;
	float time_frame_accum_r = 7.5;

	int x = 0;

	float time_accum = 0;

	int frame_counter_c = 0;				//CHUNLI FRAME COUNTER
	int frame_counter_r = 0;				//RYU FRAME COUNTER
	int key_press_state = 0;
	int key_press_state_r = 0;
	int key_press_state_last = 0;
	int key_press_state_last_r = 0;

	int pos_x_c;
	int pos_y_c;
	int pos_x_r;
	int pos_y_r;

	int random_bool_store = 0;				// 0,1 for chunli_jumping 2,3 for ryu jumping 

	VideoMode vm(1920, 1080);
	RenderWindow window1(vm, "New Game", Style::Fullscreen);
	window1.setVerticalSyncEnabled(true);

	//BACKGROUND ELEMENTS:

	(texture_elements.chunli_bg_t).loadFromFile("ChunLi Sprites/final-chunli-bg4.png");
	(texture_elements.hit).loadFromFile("ChunLi Sprites/effects.png");

	Sprite chunli_bg_stage;
	Sprite chunli_bg_fishermen;
	Sprite chunli_bg_mom;
	Sprite chunli_bg_hen;
	Sprite chunli_bg_laundry;
	Sprite chunli_bg_display;
	Sprite hit;
	Sprite blocked_hit;

	chunli_bg_stage.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_fishermen.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_mom.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_hen.setTexture(texture_elements.chunli_bg_t);
	chunli_bg_laundry.setTexture(texture_elements.chunli_bg_t);
	hit.setTexture(texture_elements.hit);
	blocked_hit.setTexture(texture_elements.hit);

	chunli_bg_stage.setTextureRect(IntRect(0, 0, 704, 269));

	RenderTexture bg_stage;
	bg_stage.create(704, 269);
	chunli_bg_stage.setPosition(0, 0);
	chunli_bg_mom.setPosition(53, 129);
	chunli_bg_hen.setPosition(266, 168);
	chunli_bg_fishermen.setPosition(158, 136);
	chunli_bg_laundry.setPosition(606, 170);
	hit.setPosition(-1000, 0);
	blocked_hit.setPosition(-1000, 0);
	hit.setScale(3, 3);
	blocked_hit.setScale(3, 3);

	bg_stage.setSmooth(false);

	chunli_bg_display.setTexture(bg_stage.getTexture());
	chunli_bg_display.setTextureRect(IntRect(0, 44, 400, 225));

	//________CHUNLI ELEMENTS______________________

	(texture_elements.chunli_char_t).loadFromFile("ChunLi Sprites/ChunLi2.png");

	Sprite chunli_char;
	Sprite chunli_shadow;

	FloatRect chunli_damage_box;
	FloatRect chunli_hitbox;

	chunli_char.setTexture(texture_elements.chunli_char_t);
	chunli_shadow.setTexture(texture_elements.chunli_char_t);
	chunli_shadow.setTextureRect(IntRect(14, 135, 74, 12));

	chunli_shadow.setOrigin(74.0 / 2, 12.0 / 2);

	chunli_shadow.setPosition(94, 247);
	chunli_char.setPosition(99, 247);

	key_press_state = key_press_state & (~ANYKEY);
	random_bool_store = random_bool_store | (1 << 4);	//for light punch chunli

	texture_elements.chunli_char_t.setSmooth(false);

	//__________RYU ELEMENTS_______________________

	(texture_elements.ryu_char_t).loadFromFile("Ryu Sprites/Ryu.png");

	Sprite ryu_char;
	Sprite ryu_shadow;

	FloatRect ryu_damage_box;
	FloatRect ryu_hitbox;

	ryu_shadow.setTexture(texture_elements.chunli_char_t);
	ryu_char.setTexture(texture_elements.ryu_char_t);
	ryu_shadow.setTextureRect(IntRect(14, 135, 74, 12));

	ryu_shadow.setOrigin(74.0 / 2, 12.0 / 2);
	ryu_char.setScale(-1.0f, 1.0f);
	ryu_shadow.setScale(-1.0f, 1.0f);

	ryu_char.setPosition(300, 247);
	ryu_shadow.setPosition(300, 247);

	key_press_state_r = key_press_state_r & (~ANYKEY);
	random_bool_store = random_bool_store | (1 << 5);	//for light punch ryu

	Clock clock1;

	while (window1.isOpen()) {

		dt = (clock1.restart()).asMilliseconds();
		time_accum = time_accum + dt;
		time_frame_accum_c = time_frame_accum_c + dt;
		time_frame_accum_r = time_frame_accum_r + dt;
		chunli_bg_display.setScale(1.0f, 1.0f);

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window1.close();
		};


		//____________________________________________________CHUNLI INPUT_________________________________________________________________


		if (Keyboard::isKeyPressed(Keyboard::Space) && ((key_press_state & ANIMATION_ON) != ANIMATION_ON) && (key_press_state_last & SPACE_0) != SPACE_0) {
			key_press_state = 0;
			key_press_state = key_press_state | ANIMATION_ON;
			key_press_state = key_press_state | ANYKEY;
			key_press_state_last = 1;
			random_bool_store = random_bool_store | (1 << 0);
			random_bool_store = random_bool_store & (~(1 << 1));
			frame_counter_c = 0;
			time_frame_accum_c = 5;
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				key_press_state = key_press_state | SPACE_L;
				chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 45);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				key_press_state = key_press_state | SPACE_R;
				chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 45);
			}
			else {
				key_press_state = key_press_state | SPACE_0;
				chunli_char.setTextureRect(IntRect(0, 2368, 74, 81));
				chunli_char.setOrigin(74.0 / 2, 12.0);
				chunli_char.setPosition(chunli_char.getPosition().x, chunli_char.getPosition().y - 70);
			}
		};

		if (Keyboard::isKeyPressed((Keyboard::Right)) && (key_press_state & ANYKEY) != ANYKEY) {
			key_press_state = 0;
			key_press_state = key_press_state | RIGHT;
			key_press_state = key_press_state | ANYKEY;
			frame_counter_c = 0;
			time_frame_accum_c = 5;
		}

		else if (Keyboard::isKeyPressed((Keyboard::Left)) && (key_press_state & ANYKEY) != ANYKEY) {
			key_press_state = 0;
			key_press_state = key_press_state | LEFT;
			key_press_state = key_press_state | ANYKEY;
			frame_counter_c = 0;
			time_frame_accum_c = 5;
		}

		else if ((key_press_state & RIGHT) == RIGHT && !Keyboard::isKeyPressed(Keyboard::Right)) {
			key_press_state = key_press_state & (~RIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			frame_counter_c = 0;
			time_frame_accum_c = 5;
			chunli_shadow.setPosition(chunli_char.getPosition().x + 2, chunli_shadow.getPosition().y);
		}

		else if ((key_press_state & LEFT) == LEFT && !Keyboard::isKeyPressed(Keyboard::Left)) {
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~ANYKEY);
			frame_counter_c = 0;
			time_frame_accum_c = 5;
		};

		if (Keyboard::isKeyPressed(Keyboard::Up) && ((key_press_state & ANIMATION_ON) != ANIMATION_ON) && (key_press_state & UP) != UP) {
			key_press_state = key_press_state | UP;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
			pos_x_c = chunli_char.getPosition().x;
			pos_y_c = chunli_char.getPosition().y;
			time_frame_accum_c = 5;
			frame_counter_c = 26;
		}

		else if ((key_press_state & UP) == UP && !(Keyboard::isKeyPressed(Keyboard::Up))) {
			key_press_state = key_press_state & (~UP);
			key_press_state = key_press_state & (~ANYKEY);
			frame_counter_c = 0;
			if ((key_press_state & DOWN) == DOWN) {
				key_press_state = key_press_state | DOWN;
				key_press_state = key_press_state | ANYKEY;
				frame_counter_c = 24;
			}
			time_frame_accum_c = 5;
		};

		if (Keyboard::isKeyPressed(Keyboard::Down) && (key_press_state & ANIMATION_ON) != ANIMATION_ON && (key_press_state & DOWN) != DOWN && (key_press_state & UP) != UP) {
			key_press_state = key_press_state | DOWN;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state | ANIMATION_ON;
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~RIGHT);
			frame_counter_c = 0;
			time_frame_accum_c = 5;
		}

		else if ((!Keyboard::isKeyPressed(Keyboard::Down)) && (key_press_state & DOWN) == DOWN && (key_press_state & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state = key_press_state & (~DOWN);
			key_press_state = key_press_state & (~UP);
			key_press_state = key_press_state & (~ANYKEY);
			time_frame_accum_c = 5;
			frame_counter_c = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::PageDown) && (key_press_state & ANIMATION_ON) != ANIMATION_ON && (key_press_state_last & PUNCH_C_LIGHT) != PUNCH_C_LIGHT && (key_press_state & UP) != UP) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				key_press_state = 0;
				key_press_state = key_press_state | PUNCH_C_HEAVY;
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | ANYKEY;
				frame_counter_c = -1;
				time_frame_accum_c = 5;
				key_press_state_last = key_press_state_last | PUNCH_C_LIGHT;
				pos_x_c = chunli_char.getPosition().x;
				pos_y_c = chunli_char.getPosition().y;	//Heavy punch towards front
				chunli_char.setPosition(chunli_char.getPosition().x, 247);
				chunli_char.setOrigin(72.0 / 2, 87);
				chunli_char.setTextureRect(IntRect(16, 32, 80, 87));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				key_press_state = 0;
				key_press_state = key_press_state | PUNCH_C_LIGHT;
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | ANYKEY;
				frame_counter_c = -1;
				time_frame_accum_c = 5;
				key_press_state_last = key_press_state_last | PUNCH_C_LIGHT;
				pos_x_c = chunli_char.getPosition().x;
				pos_y_c = chunli_char.getPosition().y;
				random_bool_store = random_bool_store & (~(1 << 4));	//Light punch but phase 2
				chunli_char.setPosition(chunli_char.getPosition().x, 247);
				chunli_char.setOrigin(72.0 / 2, 87);
				chunli_char.setTextureRect(IntRect(16, 32, 80, 87));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				key_press_state = 0;
				key_press_state = key_press_state | ANYKEY;
				key_press_state = key_press_state | DOWN;
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | PUNCH_C_LIGHT;
				key_press_state_last = key_press_state_last | PUNCH_C_LIGHT;
				frame_counter_c = 0;
				time_frame_accum_c = 5;
				pos_x_c = chunli_char.getPosition().x;
				pos_y_c = chunli_char.getPosition().y;
			}
			else {
				key_press_state = 0;
				key_press_state = key_press_state | PUNCH_C_LIGHT;
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | ANYKEY;
				frame_counter_c = 0;
				time_frame_accum_c = 5;
				key_press_state_last = key_press_state_last | PUNCH_C_LIGHT;
				pos_x_c = chunli_char.getPosition().x;
				pos_y_c = chunli_char.getPosition().y;
				random_bool_store = random_bool_store | (1 << 4);
			}
		};

		if (Keyboard::isKeyPressed(Keyboard::PageUp) && (key_press_state & ANIMATION_ON) != ANIMATION_ON && (key_press_state_last & KICK_C_LIGHT) != KICK_C_LIGHT && (key_press_state & UP) != UP) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				key_press_state = 0;
				key_press_state = key_press_state | KICK_C_HEAVY;
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | ANYKEY;
				frame_counter_c = -1;
				time_frame_accum_c = 5;
				key_press_state_last = key_press_state_last | KICK_C_HEAVY;
				pos_x_c = chunli_char.getPosition().x;
				chunli_char.setPosition(pos_x_c, 247);
				chunli_char.setOrigin(72.0 / 2, 87);
				chunli_char.setTextureRect(IntRect(16, 32, 80, 87));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				key_press_state = 0;
				key_press_state = key_press_state | KICK_C_LIGHT;
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | ANYKEY;
				frame_counter_c = -1;
				time_frame_accum_c = 5;
				key_press_state_last = key_press_state_last | KICK_C_LIGHT;
				random_bool_store = random_bool_store & (~(1 << 6));
				pos_x_c = chunli_char.getPosition().x;
				pos_y_c = chunli_char.getPosition().y;
				chunli_char.setPosition(chunli_char.getPosition().x, 247);
				chunli_char.setOrigin(72.0 / 2, 87);
				chunli_char.setTextureRect(IntRect(16, 32, 80, 87));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				key_press_state = 0;
				key_press_state = key_press_state | ANYKEY;
				key_press_state = key_press_state | (DOWN);
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | KICK_C_LIGHT;
				key_press_state_last = key_press_state_last | KICK_C_LIGHT;
				frame_counter_c = 0;
				time_frame_accum_c = 5;
				pos_x_c = chunli_char.getPosition().x;
				pos_y_c = chunli_char.getPosition().y;
			}
			else {
				key_press_state = 0;
				key_press_state = key_press_state | KICK_C_LIGHT;
				key_press_state = key_press_state | ANIMATION_ON;
				key_press_state = key_press_state | ANYKEY;
				frame_counter_c = 0;
				time_frame_accum_c = 5;
				key_press_state_last = key_press_state_last | KICK_C_LIGHT;
				pos_x_c = chunli_char.getPosition().x;
				pos_y_c = chunli_char.getPosition().y;
				random_bool_store = random_bool_store | (1 << 6);
			}
		};

		if (key_press_state_last) { //____to prevent abuse of button press____
			if (!(Keyboard::isKeyPressed(Keyboard::Space))) {
				key_press_state_last = key_press_state_last & (~SPACE_0);
			}
			if (!(Keyboard::isKeyPressed(Keyboard::PageDown))) {
				key_press_state_last = key_press_state_last & (~PUNCH_C_LIGHT);
			}
			if (!(Keyboard::isKeyPressed(Keyboard::PageUp))) {
				key_press_state_last = key_press_state_last & (~KICK_C_LIGHT);
			}
		};

		if (chunli_hitbox.intersects(ryu_damage_box)) {
			key_press_state = 0;
			key_press_state = key_press_state | ANIMATION_ON;
			key_press_state = key_press_state | ANYKEY;
			key_press_state = key_press_state | HURT_C;
			chunli_damage_box.left = -100;
			frame_counter_c = 0;
			time_frame_accum_c = 5;
			pos_x_c = chunli_char.getPosition().x;
			pos_y_c = chunli_char.getPosition().y;
		}


		// _____________________________________________________________________ RYU INPUT___________________________________________________________________________________


		if (Keyboard::isKeyPressed(Keyboard::W) && ((key_press_state_r & ANIMATION_ON) != ANIMATION_ON) && (key_press_state_last_r & _W_) != _W_) {
			key_press_state_r = 0;
			key_press_state_r = key_press_state_r | ANIMATION_ON;
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_last_r = key_press_state_last_r | _W_;
			random_bool_store = random_bool_store | (1 << 2);
			random_bool_store = random_bool_store & (~(1 << 3));
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				key_press_state_r = key_press_state_r | _W_L;
				ryu_char.setPosition(ryu_char.getPosition().x + 16, 194);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				key_press_state_r = key_press_state_r | _W_R;
				ryu_char.setPosition(ryu_char.getPosition().x, 194);
			}
			else {
				key_press_state_r = key_press_state_r | _W_;
				ryu_char.setTextureRect(IntRect(17, 847, 55, 85));
				ryu_char.setOrigin(40, 10);
				ryu_char.setPosition(ryu_char.getPosition().x, 172);
			};
		};

		if (Keyboard::isKeyPressed(Keyboard::Q) && ((key_press_state_r & ANIMATION_ON) != ANIMATION_ON) && (key_press_state_r & _Q_) != _Q_) {
			key_press_state_r = key_press_state_r | _Q_;
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_r = key_press_state_r & (~_A_);
			key_press_state_r = key_press_state_r & (~_D_);
			pos_x_r = ryu_char.getPosition().x;
			pos_y_r = ryu_char.getPosition().y;
			time_frame_accum_r = 7.5;
			frame_counter_r = 26;
		}

		else if ((key_press_state_r & _Q_) == _Q_ && !(Keyboard::isKeyPressed(Keyboard::Q))) {
			key_press_state_r = key_press_state_r & (~_Q_);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			ryu_char.setPosition(pos_x_r, ryu_char.getPosition().y);
			frame_counter_r = 0;
			if ((key_press_state_r & _S_) == _S_) {
				frame_counter_r = 22;
				key_press_state_r = key_press_state_r | ANYKEY;
			}
			time_frame_accum_r = 7.5;
		};

		if (Keyboard::isKeyPressed(Keyboard::S) && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON && (key_press_state_r & _S_) != _S_ && (key_press_state_r & _Q_) != _Q_) {
			key_press_state_r = key_press_state_r | _S_;
			key_press_state_r = key_press_state_r | ANYKEY;
			key_press_state_r = key_press_state_r | ANIMATION_ON;
			key_press_state_r = key_press_state_r & (~_A_);
			key_press_state_r = key_press_state_r & (~_D_);
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;
			pos_x_r = ryu_char.getPosition().x;
			pos_y_r = ryu_char.getPosition().y;
		}

		else if ((!Keyboard::isKeyPressed(Keyboard::S)) && (key_press_state_r & _S_) == _S_ && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state_r = key_press_state_r & (~_S_);
			key_press_state_r = key_press_state_r & (~UP);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			time_frame_accum_r = 7.5;
			frame_counter_r = 0;
		}

		if (Keyboard::isKeyPressed((Keyboard::D)) && (key_press_state_r & ANYKEY) != ANYKEY && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state_r = 0;
			key_press_state_r = key_press_state_r | _D_;
			key_press_state_r = key_press_state_r | ANYKEY;
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;
		}

		else if (Keyboard::isKeyPressed((Keyboard::A)) && (key_press_state_r & ANYKEY) != ANYKEY && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON) {
			key_press_state_r = 0;
			key_press_state_r = key_press_state_r | _A_;
			key_press_state_r = key_press_state_r | ANYKEY;
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;
			pos_x_r = ryu_char.getPosition().x;
			ryu_char.setPosition(ryu_char.getPosition().x - 14, 168);
		}

		else if ((key_press_state_r & _A_) == _A_ && !Keyboard::isKeyPressed(Keyboard::A)) {
			key_press_state_r = key_press_state_r & (~_A_);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;
			ryu_char.setPosition(pos_x_r, 168);
		}

		else if ((key_press_state_r & _D_) == _D_ && !Keyboard::isKeyPressed(Keyboard::D)) {
			key_press_state_r = key_press_state_r & (~_D_);
			key_press_state_r = key_press_state_r & (~ANYKEY);
			frame_counter_r = 0;
			time_frame_accum_r = 7.5;
		};

		if (Keyboard::isKeyPressed(Keyboard::E) && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON && (key_press_state_last_r & PUNCH_R_LIGHT) != PUNCH_R_LIGHT && (key_press_state_r & _Q_) != _Q_) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | PUNCH_R_HEAVY;
				key_press_state_last_r = key_press_state_last_r | PUNCH_R_HEAVY;
				time_frame_accum_r = 7.5;
				frame_counter_r = 0;
				ryu_char.setPosition(pos_x_r, 167);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | PUNCH_R_LIGHT;
				key_press_state_last_r = key_press_state_last_r | PUNCH_R_LIGHT;
				time_frame_accum_r = 7.5;
				frame_counter_r = -1;
				pos_x_r = ryu_char.getPosition().x;
				pos_y_r = ryu_char.getPosition().y;
				random_bool_store = random_bool_store & (~(1 << 5));
			}
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | (_S_);
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | PUNCH_R_LIGHT;
				key_press_state_last_r = key_press_state_last_r | PUNCH_R_LIGHT;
				frame_counter_r = 0;
				time_frame_accum_r = 7.5;
				pos_x_r = ryu_char.getPosition().x;
				pos_y_r = ryu_char.getPosition().y;
			}
			else {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | PUNCH_R_LIGHT;
				key_press_state_last_r = key_press_state_last_r | PUNCH_R_LIGHT;
				random_bool_store = random_bool_store | (1 << 5);
				time_frame_accum_r = 7.5;
				frame_counter_r = 0;
				pos_x_r = ryu_char.getPosition().x;
				pos_y_r = ryu_char.getPosition().y;
			}
		};

		if (Keyboard::isKeyPressed(Keyboard::R) && (key_press_state_r & ANIMATION_ON) != ANIMATION_ON && (key_press_state_last_r & KICK_R_LIGHT) != KICK_R_LIGHT && (key_press_state_r & _Q_) != _Q_) {

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | KICK_R_HEAVY;
				key_press_state_last_r = key_press_state_last_r | KICK_R_HEAVY;
				time_frame_accum_r = 7.5;
				frame_counter_r = 0;
				ryu_char.setTextureRect(IntRect(0, 3, 59, 90));
				ryu_char.setOrigin(36, 10);
				ryu_char.setPosition(pos_x_r, 167);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | KICK_R_LIGHT;
				key_press_state_last_r = key_press_state_last_r | KICK_R_LIGHT;
				time_frame_accum_r = 7.5;
				frame_counter_r = -1;
				random_bool_store = random_bool_store & (~(1 << 6));
				pos_x_r = ryu_char.getPosition().x;
				pos_y_r = ryu_char.getPosition().y;
				ryu_char.setTextureRect(IntRect(0, 3, 59, 90));
				ryu_char.setOrigin(36, 10);
				ryu_char.setPosition(ryu_char.getPosition().x, 167);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | (_S_);
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | KICK_R_LIGHT;
				key_press_state_last_r = key_press_state_last_r | KICK_R_LIGHT;
				frame_counter_r = 0;
				time_frame_accum_r = 7.5;
				pos_x_r = ryu_char.getPosition().x;
				pos_y_r = ryu_char.getPosition().y;
			}
			else {
				key_press_state_r = 0;
				key_press_state_r = key_press_state_r | ANYKEY;
				key_press_state_r = key_press_state_r | ANIMATION_ON;
				key_press_state_r = key_press_state_r | KICK_R_LIGHT;
				key_press_state_last_r = key_press_state_last_r | KICK_R_LIGHT;
				time_frame_accum_r = 7.5;
				frame_counter_r = 0;
				random_bool_store = random_bool_store | (1 << 6);
				pos_x_r = ryu_char.getPosition().x;
				pos_y_r = ryu_char.getPosition().y;
			}
		};

		if (key_press_state_last_r) { //____to prevent abuse of button press____
			if (!(Keyboard::isKeyPressed(Keyboard::W))) {
				key_press_state_last_r = key_press_state_last_r & (~_W_);
			}
			if (!(Keyboard::isKeyPressed(Keyboard::E))) {
				key_press_state_last_r = key_press_state_last_r & (~PUNCH_R_LIGHT);
			}
			if (!(Keyboard::isKeyPressed(Keyboard::R))) {
				key_press_state_last_r = key_press_state_last_r & (~KICK_R_LIGHT);
			}
			if (!(Keyboard::isKeyPressed(Keyboard::T))) {
				key_press_state_last_r = key_press_state_last_r & (~PUNCH_R_HEAVY);
			}
			if (!(Keyboard::isKeyPressed(Keyboard::Y))) {
				key_press_state_last_r = key_press_state_last_r & (~KICK_R_HEAVY);
			}
		}


		//_________________CHUNLI ANIMATION LOOP ONLY_____________________


		while (time_frame_accum_c >= 5) {

			time_frame_accum_c = time_frame_accum_c - 5;

			switch (key_press_state) {
			case 5:
				chunli_walk_b_animation(chunli_char, frame_counter_c, key_press_state, chunli_shadow, time_frame_accum_c);
				if (chunli_char.getPosition().x >= 35) {
					chunli_char.setPosition(chunli_char.getPosition().x - 1, chunli_char.getPosition().y);
				};
				break;
			case 9:
				chunli_walk_f_animation(chunli_char, frame_counter_c, key_press_state, chunli_shadow, time_frame_accum_c);
				if ((chunli_char.getGlobalBounds().left + chunli_char.getGlobalBounds().width + 4) < ryu_char.getGlobalBounds().left) {
					chunli_char.setPosition(chunli_char.getPosition().x + 1, chunli_char.getPosition().y);
				};
				break;
			case 17:
				chunli_sit(chunli_char, frame_counter_c, key_press_state, chunli_shadow, time_frame_accum_c);
				break;
			case 33:
				chunli_block(chunli_char, key_press_state, frame_counter_c, time_frame_accum_c);
				break;
			case 49:
				chunli_sit(chunli_char, frame_counter_c, key_press_state, chunli_shadow, time_frame_accum_c);
				break;
			case 259:
				chunli_jump_animation(chunli_char, random_bool_store, frame_counter_c, key_press_state, time_frame_accum_c);
				break;
			case 273:
				chunli_sit(chunli_char, frame_counter_c, key_press_state, chunli_shadow, time_frame_accum_c);
				break;
			case 321:
				chunli_jump_animation_L(chunli_char, frame_counter_c, random_bool_store, key_press_state, dt, chunli_shadow, time_frame_accum_c);
				break;
			case 385:
				chunli_jump_animation_R(chunli_char, frame_counter_c, random_bool_store, key_press_state, dt, pos_x_c, pos_y_c, ryu_char, time_frame_accum_c, chunli_shadow);
				break;
			case 2305:
				chunli_light_punch(chunli_char, time_frame_accum_c, frame_counter_c, key_press_state, random_bool_store, pos_x_c, pos_y_c, chunli_shadow);
				break;
			case 2321:
				chunli_sit_punch(chunli_char, frame_counter_c, time_frame_accum_c, key_press_state, pos_x_c, pos_y_c);
				break;
			case 4353:
				chunli_light_kick(chunli_char, frame_counter_c, time_frame_accum_c, key_press_state, pos_x_c, pos_y_c, random_bool_store, chunli_damage_box);
				break;
			case 4369:
				chunli_sit_kick(chunli_char, frame_counter_c, time_frame_accum_c, key_press_state, pos_x_c, pos_y_c);
				break;
			case 8449:
				chunli_heavy_punch(chunli_char, frame_counter_c, time_frame_accum_c, key_press_state, pos_x_c, pos_y_c, chunli_shadow);
				break;
			case 16641:
				chunli_heavy_kick(chunli_char, frame_counter_c, time_frame_accum_c, key_press_state, pos_x_c, pos_y_c);
				break;
			case 33025:
				chunli_hurt(chunli_char, ryu_char, frame_counter_c, time_frame_accum_c, chunli_shadow, pos_x_c, pos_y_c, key_press_state, hit, ryu_damage_box, ryu_shadow);
				break;
			};

			if (((key_press_state & ANYKEY) != ANYKEY)) {
				chunli_idle_animation(chunli_char, frame_counter_c);
			};

		}

		chunli_hitbox.left = chunli_char.getGlobalBounds().left;
		chunli_hitbox.top = chunli_char.getGlobalBounds().top;						// ____CHUNLI HITBOX SETTINGS____
		chunli_hitbox.width = chunli_char.getTextureRect().width;
		chunli_hitbox.height = chunli_char.getTextureRect().height;


		//_____________________________RYU ANIMATION LOOP_______________________________//


		while (time_frame_accum_r >= 7.5) {

			time_frame_accum_r = time_frame_accum_r - 7.5;

			switch (key_press_state_r) {
			case 5:
				ryu_walk_b(ryu_char, time_frame_accum_r, key_press_state_r, frame_counter_r);
				ryu_shadow.setPosition(ryu_char.getPosition().x, ryu_shadow.getPosition().y);
				break;
			case 9:
				ryu_walk_f(frame_counter_r, time_frame_accum_r, ryu_char, key_press_state_r, pos_x_r, chunli_char);
				ryu_shadow.setPosition(ryu_char.getPosition().x + 20, ryu_shadow.getPosition().y);
				break;
			case 17:
				ryu_sit(ryu_char, time_frame_accum_r, frame_counter_r, key_press_state_r, pos_x_r, pos_y_r);
				break;
			case 33:
				ryu_block(ryu_char, key_press_state_r, time_frame_accum_r, frame_counter_r, pos_x_r);
				break;
			case 49:
				ryu_sit(ryu_char, time_frame_accum_r, frame_counter_r, key_press_state_r, pos_x_r, pos_y_r);
				break;
			case 259:
				ryu_jump_animation(ryu_char, time_frame_accum_r, key_press_state_r, frame_counter_r, random_bool_store);
				break;
			case 273:
				ryu_sit(ryu_char, time_frame_accum_r, frame_counter_r, key_press_state_r, pos_x_r, pos_y_r);
				break;
			case 321:
				ryu_jump_animation_L(ryu_char, frame_counter_r, random_bool_store, key_press_state_r, ryu_shadow, time_frame_accum_r, chunli_char);
				break;
			case 385:
				ryu_jump_animation_R(ryu_char, frame_counter_r, random_bool_store, key_press_state_r, ryu_shadow, time_frame_accum_r, chunli_char);
				break;
			case 2305:
				ryu_light_punch(ryu_char, frame_counter_r, key_press_state_r, random_bool_store, time_frame_accum_r, pos_x_r, pos_y_r, ryu_shadow, ryu_damage_box);
				break;
			case 2321:
				ryu_sit_punch(ryu_char, frame_counter_r, key_press_state_r, time_frame_accum_r, pos_x_r, pos_y_r, x);
				break;
			case 4353:
				ryu_light_kick(ryu_char, frame_counter_r, key_press_state_r, random_bool_store, time_frame_accum_r, pos_x_r, pos_y_r, ryu_shadow, ryu_damage_box);
				break;
			case 4369:
				ryu_sit_kick(ryu_char, frame_counter_r, key_press_state_r, time_frame_accum_r, pos_x_r, pos_y_r);
				break;
			case 8449:
				ryu_heavy_punch(ryu_char, frame_counter_r, key_press_state_r, time_frame_accum_r, pos_x_r, pos_y_r, ryu_shadow, ryu_damage_box);
				break;
			case 16641:
				ryu_heavy_kick(ryu_char, frame_counter_r, key_press_state_r, time_frame_accum_r, pos_x_r, pos_y_r, ryu_shadow, ryu_damage_box);
				break;
			};

			if ((key_press_state_r & ANYKEY) != ANYKEY) {
				ryu_idle(frame_counter_r, time_frame_accum_r, ryu_char, ryu_shadow);
			};

		}

		ryu_hitbox.left = ryu_char.getGlobalBounds().left;
		ryu_hitbox.top = ryu_char.getGlobalBounds().top;						// ____RYU HITBOX SETTINGS____
		ryu_hitbox.width = ryu_char.getTextureRect().width;
		ryu_hitbox.height = ryu_char.getTextureRect().height;









		bg_animation(time_accum, chunli_bg_fishermen, chunli_bg_mom, chunli_bg_hen, chunli_bg_laundry);


		bg_stage.clear();
		bg_stage.draw(chunli_bg_stage);
		bg_stage.draw(chunli_bg_fishermen);
		bg_stage.draw(chunli_bg_hen);
		bg_stage.draw(chunli_bg_laundry);
		bg_stage.draw(chunli_bg_mom);
		bg_stage.draw(chunli_shadow);
		bg_stage.draw(ryu_shadow);
		bg_stage.draw(chunli_char);
		bg_stage.draw(ryu_char);
		bg_stage.draw(hit);
		bg_stage.display();

		bg_stage.setSmooth(false);

		chunli_bg_display.setScale(3.0f, 3.0f);

		window1.clear();
		window1.draw(chunli_bg_display);
		window1.display();
	}
}