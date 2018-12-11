#include <libledcube.h>
#include <chm_shape.h>

#define ANIMATIONS 10

uint8_t statPins[] = {
	_PSTAT0,
	_PSTAT1,
	_PSTAT2,
	_PSTAT3,
	_PSTAT4
};

struct animation {
	struct cubeframe *frames;
	size_t framecount;
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

#if !defined(TEST_NOTEENSY) && defined(USE_SPI)
	cm_setup_SPI();
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

	anim0.frames = chmap_buildstr("JOANA", &anim0.framecount, 500);
	anim1.frames = (struct cubeframe*)malloc(3 * sizeof(struct cubeframe));
	if(anim1.frames)
	{
		anim1.framecount = 3;

		chmap_buildframe(&anim1.frames[0], _chm_heart);
		anim1.frames[0].delay = 1000;
		chmap_buildframe(&anim1.frames[1], _chm_smileyface);
		anim1.frames[1].delay = 1000;
		chmap_buildframe(&anim1.frames[2], _chm_star);
		anim1.frames[2].delay = 1000;
	}

	struct cubeframe empty;
	empty.delay = 1;
	cm_set(&empty, 0);
	cm_draw_frame(&empty);
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
			pat_random_set(1, 40);
			cm_delay_frame(500);
			pat_random_set(0, 40);
			break;
		case 1:
			pat_plane_bounce(16, 100);
			break;
		case 2:
			pat_rain(500, 80);
			break;
		case 3:
			pat_stream(AXISDIR(rand() % 3, rand() & 1), (rand() & 1) ? 30 : 60, 2, 80);
			break;
		case 4:
			pat_send_voxel(rand() % 3, 35, 100, 60);
			break;
		case 5:
			pat_border_bounce(16, 175);
			break;
		case 6:
			pat_firework(75, 150);
			cm_delay_frame(rand() % (500 - 50 - 1) + 50);
			break;
		case 7:
			pat_border_spin(1, 6, 150, 75);
			break;
		case 8:
		case 9:
			{
				struct animation *cur = animlist[cur_animation - 9];
				struct cubeframe *fr = cur->frames;

				if(fr)
				{
					for (size_t i = 0; i < cur->framecount; i++, fr++)
					{
					#ifdef PATTERN_KILLFLAG
						if(g_patternKillFlag)
							return;
					#endif

						cm_draw_frame(fr);
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
