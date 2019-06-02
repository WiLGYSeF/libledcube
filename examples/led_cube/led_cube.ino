#include <libledcube.h>
#include <charmaps/chm_shape.h>

//controls
#define _PANIMITER 23

//status pins
#define STATCOUNT 5
#define _PSTAT0 20
#define _PSTAT1 19
#define _PSTAT2 18
#define _PSTAT3 17
#define _PSTAT4 16

//random pins
#define _PRAND1 14
#define _PRAND2 15

#define ANIMATIONS 10

using namespace ledcube;

struct animation {
	Cubeframe *frames;
	size_t framecount;
};

const uint8_t statPins[] = {
	_PSTAT0,
	_PSTAT1,
	_PSTAT2,
	_PSTAT3,
	_PSTAT4
};

uint8_t cur_animation = 0;

struct animation anim0;
struct animation anim1;

struct animation *animlist[2] = {
	&anim0, &anim1
};

volatile uint32_t lastButtonPress = 0;

void setup()
{
	//pin setup

	pinMode(_PNA, OUTPUT);
	pinMode(_PNB, OUTPUT);
	pinMode(_PNC, OUTPUT);
	pinMode(_PND, OUTPUT);
	pinMode(_PNE, OUTPUT);

	pinMode(_PDATA, OUTPUT);
	pinMode(_PCLOCK, OUTPUT);
	pinMode(_PLATCH, OUTPUT);

	pinMode(_PANIMITER, INPUT_PULLUP);

	pinMode(_PSTAT0, OUTPUT);
	pinMode(_PSTAT1, OUTPUT);
	pinMode(_PSTAT2, OUTPUT);
	pinMode(_PSTAT3, OUTPUT);
	pinMode(_PSTAT4, OUTPUT);

#ifdef USE_SPI
	setup_SPI();
#endif

	digitalWrite(_PNA, LOW);
	digitalWrite(_PNB, LOW);
	digitalWrite(_PNC, LOW);
	digitalWrite(_PND, LOW);
	digitalWrite(_PNE, LOW);

	digitalWrite(_PDATA, LOW);
	digitalWrite(_PCLOCK, LOW);
	digitalWrite(_PLATCH, LOW);

	uint8_t ca = cur_animation + 1;
	if(ca > (1 << STATCOUNT) - 1)
		ca = (1 << STATCOUNT) - 1;

	for (uint8_t i = 0;  i < STATCOUNT; i++)
		digitalWrite(statPins[i], (ca & (1 << i)) ? HIGH : LOW);

	attachInterrupt(digitalPinToInterrupt(_PANIMITER), button_ISR, CHANGE);

	srand(analogRead(_PRAND1));

	//animation setup

	anim0.frames = charmap::buildstr("WILGYSEF", &anim0.framecount, 500, false);
	anim1.frames = new Cubeframe[3];
	if(anim1.frames)
	{
		anim1.framecount = 3;

		charmap::buildframe(anim1.frames[0], charmap::_chm_heart, 1000);
		charmap::buildframe(anim1.frames[1], charmap::_chm_smileyface, 1000);
		charmap::buildframe(anim1.frames[2], charmap::_chm_star, 1000);
	}

	Cubeframe empty(1);
	empty.set(0);
	empty.draw_frame();

	//delete anim0.frames;
	//delete anim1.frames;
}

void loop()
{
	if(g_patternKillFlag)
	{
		cur_animation = (cur_animation + 1) % ANIMATIONS;

		uint8_t ca = cur_animation + 1;
		if(ca > (1 << STATCOUNT) - 1)
			ca = (1 << STATCOUNT) - 1;

		for (uint8_t i = 0;  i < STATCOUNT; i++)
			digitalWrite(statPins[i], (ca & (1 << i)) ? HIGH : LOW);

		g_patternKillFlag = 0;
	}

	switch(cur_animation)
	{
		case 0:
			pattern::random_set(1, 40);
			Cubeframe::delay_frame(500);
			pattern::random_set(0, 40);
			break;
		case 1:
			pattern::plane_bounce(16, 100);
			break;
		case 2:
			pattern::rain(500, 80);
			break;
		case 3:
			pattern::stream(AXISDIR(rand() % 3, rand() & 1), (rand() & 1) ? 30 : 60, 2, 80);
			break;
		case 4:
			pattern::send_voxel(rand() % 3, 35, 150, 60);
			break;
		case 5:
			pattern::border_bounce(16, 175);
			break;
		case 6:
			pattern::firework(75, 150);
			Cubeframe::delay_frame(rand() % (500 - 50 - 1) + 50);
			break;
		case 7:
			pattern::border_spin(1, 6, 150, 75);
			break;
		case 8:
		case 9:
			{
				struct animation *cur = animlist[cur_animation - 8];
				Cubeframe *fr = cur->frames;

				if(fr)
				{
					for (size_t i = 0; i < cur->framecount; i++, fr++)
					{
					#ifdef PATTERN_KILLFLAG
						if(g_patternKillFlag)
							return;
					#endif

						fr->draw_frame();
					}
				}
			}
			break;
		default:
			break;
	}
}

void button_ISR()
{
	if(digitalRead(_PANIMITER))
	{
		//released
	}else
	{
		//pressed
		if(millis() - lastButtonPress > 750)
		{
			g_patternKillFlag = 1;
			lastButtonPress = millis();
		}
	}
}
