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

void bg_upward_animation(Sprite& chunli_bg_s, Sprite& chunli_bg_mom, Sprite& chunli_bg_fishermen, Sprite& chunli_bg_hen, int& key_press_state, int& time_accum_2, int& time_accum_3, int& random_bool_store) {
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
		time_accum_3 = 0;
	}
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
void chunli_walk_f_animation(Sprite& chunli_char, int& time_accum_3,int &frame_counter,FloatRect &damage_box) {

	if (time_accum_3 >= 60 && chunli_char.getTextureRect().left >= 891) {
		chunli_char.setTextureRect(IntRect(-81, 159, 81, 89));
		frame_counter = 0;
	}
	while (time_accum_3 >= 60 && chunli_char.getTextureRect().left < 891) {
		time_accum_3 = time_accum_3 - 60;
		frame_counter = frame_counter + 1;
		chunli_char.setTextureRect(IntRect(chunli_char.getTextureRect().left + 81, 159, 81, 89));
	}

	switch (frame_counter) {
	case 1:
		damage_box.width = 78;
		damage_box.height = 84;
		break;
	case 2:
		damage_box.width = 71;
		damage_box.height = 87;
		break;
	case 3:
		damage_box.width = 65;
		damage_box.height = 88;
		break;
	case 4:
		damage_box.width = 62;
		damage_box.height = 89;
		break;
	case 5:
		damage_box.width = 67;
		damage_box.height = 88;
		break;
	case 6:
		damage_box.width = 76;
		damage_box.height = 87;
		break;
	case 7:
		damage_box.width = 81;
		damage_box.height = 86;
		break;
	case 8:
		damage_box.width = 76;
		damage_box.height = 87;
		break;
	case 9:
		damage_box.width = 67;
		damage_box.height = 88;
		break;
	case 10:
		damage_box.width = 62;
		damage_box.height = 89;
		break;
	case 11:
		damage_box.width = 65;
		damage_box.height = 88;
		break;
	case 12:
		damage_box.width = 71;
		damage_box.height = 87;
		break;
	}

	damage_box.left = chunli_char.getPosition().x;
	damage_box.top = 5 * (89 - damage_box.height) + chunli_char.getPosition().y;
}
void chunli_walk_b_animation(Sprite& chunli_char, int& time_accum_3, int& frame_counter, FloatRect& damage_box) {
	
	if (time_accum_3 >= 60 && chunli_char.getTextureRect().left >= 803) {
		chunli_char.setTextureRect(IntRect(-73, 288, 73, 91));
		frame_counter = 0;
	}
	while (time_accum_3 >= 60 && chunli_char.getTextureRect().left < 803) {
		time_accum_3 = time_accum_3 - 60;
		frame_counter = frame_counter + 1;
		chunli_char.setTextureRect(IntRect(chunli_char.getTextureRect().left + 73, 288, 73, 91));
	}
	switch (frame_counter) {
	case 1:
		damage_box.width = 73;
		damage_box.height = 86;
		break;
	case 2:
		damage_box.width = 63;
		damage_box.height = 89;
		break;
	case 3:
		damage_box.width = 60;
		damage_box.height = 90;
		break;
	case 4:
		damage_box.width = 63;
		damage_box.height = 91;
		break;
	case 5:
		damage_box.width = 64;
		damage_box.height = 90;
		break;
	case 6:
		damage_box.width = 65;
		damage_box.height = 89;
		break;
	case 7:
		damage_box.width = 72;
		damage_box.height = 83;
		break;
	case 8:
		damage_box.width = 65;
		damage_box.height = 88;
		break;
	case 9:
		damage_box.width = 64;
		damage_box.height = 90;
		break;
	case 10:
		damage_box.width = 63;
		damage_box.height = 91;
		break;
	case 11:
		damage_box.width = 60;
		damage_box.height = 90;
		break;
	case 12:
		damage_box.width = 63;
		damage_box.height = 89;
		break;
	}

	damage_box.left = chunli_char.getPosition().x;
	damage_box.top = 5 * (91 - damage_box.height) + chunli_char.getPosition().y;
}

int main() {

	float dt;

	int time_accum = 0;
	int time_accum_2 = 0;
	int time_accum_3 = 0;
	int frame_counter = 1;
	int key_press_state = 0;
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
	chunli_char.setTextureRect(IntRect(-64, 32, 72, 87));
	char_shadow.setTextureRect(IntRect(14, 135, 74, 12));

	chunli_bg_fishermen.setPosition(800, 420);
	chunli_bg_mom.setPosition(280, 380);
	chunli_bg_hen.setPosition(1360, 580);
	chunli_char.setPosition(326, 527);
	char_shadow.setPosition(318, 927);

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
		if (Keyboard::isKeyPressed(Keyboard::Space) && (key_press_state & SPACE) != SPACE) {
			key_press_state = key_press_state | SPACE;
			random_bool_store = random_bool_store | (1 << 0);
			random_bool_store = random_bool_store & (~(1 << 1));
			time_accum_2 = 0;
		};
		if (Keyboard::isKeyPressed((Keyboard::Right)) && (key_press_state & RIGHT) != RIGHT && (key_press_state & LEFT) != LEFT) {
			key_press_state = key_press_state | RIGHT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter = 1;
			chunli_char.setTextureRect(IntRect(0, 159, 81, 89));
			chunli_char.setPosition(chunli_char.getPosition().x, 517);
			char_shadow.setPosition(char_shadow.getPosition().x - 40, char_shadow.getPosition().y);
		}
		else if ((!(Keyboard::isKeyPressed((Keyboard::Right)))) && ((key_press_state & RIGHT) == RIGHT)) {
			key_press_state = key_press_state & (~RIGHT);
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
			chunli_char.setPosition(chunli_char.getPosition().x, 527);
			damage_box.left = chunli_char.getPosition().x;
			damage_box.top = 527;
			damage_box.width = 72;
			damage_box.height = 87;
			char_shadow.setPosition(char_shadow.getPosition().x + 40, char_shadow.getPosition().y);
		};
		if (Keyboard::isKeyPressed((Keyboard::Left)) && (key_press_state & LEFT) != LEFT && (key_press_state & RIGHT) != RIGHT) {
			key_press_state = key_press_state | LEFT;
			key_press_state = key_press_state | ANYKEY;
			time_accum_3 = 0;
			frame_counter = 1;
			chunli_char.setTextureRect(IntRect(0, 288, 73, 91));
			chunli_char.setPosition(chunli_char.getPosition().x, 507);
			char_shadow.setPosition(char_shadow.getPosition().x - 40, char_shadow.getPosition().y);
		}
		else if ((!(Keyboard::isKeyPressed((Keyboard::Left)))) && ((key_press_state & LEFT) == LEFT)) {
			key_press_state = key_press_state & (~LEFT);
			key_press_state = key_press_state & (~ANYKEY);
			time_accum_3 = 0;
			chunli_char.setTextureRect(IntRect(16, 32, 72, 87));
			chunli_char.setPosition(chunli_char.getPosition().x, 527);
			damage_box.left = chunli_char.getPosition().x;
			damage_box.top = 527;
			damage_box.width = 72;
			damage_box.height = 87;
			char_shadow.setPosition(char_shadow.getPosition().x + 40, char_shadow.getPosition().y);
		};





















		if ((key_press_state & SPACE) == SPACE) {
			key_press_state = key_press_state | ANYKEY;
			bg_upward_animation(chunli_bg_s, chunli_bg_mom, chunli_bg_fishermen, chunli_bg_hen, key_press_state, time_accum_2, time_accum_3, random_bool_store);
		};
		if (((key_press_state & ANYKEY) != ANYKEY)) {
			chunli_idle_animation(chunli_char, time_accum_3);
		};
		if ((key_press_state & RIGHT) == RIGHT) {
			chunli_char.setPosition(chunli_char.getPosition().x + round(dt * 0.95), chunli_char.getPosition().y);
			char_shadow.setPosition(char_shadow.getPosition().x + round(dt * 0.95), char_shadow.getPosition().y);
			chunli_walk_f_animation(chunli_char, time_accum_3, frame_counter, damage_box);
		}
		else if ((key_press_state & LEFT) == LEFT) {
			chunli_char.setPosition(chunli_char.getPosition().x - round(dt * 0.9), chunli_char.getPosition().y);
			char_shadow.setPosition(char_shadow.getPosition().x - round(dt * 0.9), char_shadow.getPosition().y);
			chunli_walk_b_animation(chunli_char, time_accum_3, frame_counter, damage_box);
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


