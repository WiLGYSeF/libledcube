#ifndef ARDUINO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../../libledcube.h"

using namespace ledcube;

int main()
{
	g_verboseprint = 1;
	srand(time(NULL));

	Cubeframe empty(0);
	empty.set(0);

	size_t count = 0;
	Cubeframe *frames = charmap::buildstr("123", &count, 500, true);

	if(!frames)
	{
		printf("ENOMEM\n");
		return 1;
	}

	for (int i = 0; i < 24; i++)
		empty.draw_frame();
	Cubeframe::delay_frame(500);

	for (size_t i = 0; i < count; i++)
		frames[i].draw_frame();
	//charmap::scrolltext(frames, count, DIR_LEFT, 1);

	delete frames;

	pattern::send_voxel(1, 30, 150, 20);

	pattern::random_set(1, 50);
	Cubeframe::delay_frame(750);
	pattern::random_set(0, 50);

	Cubeframe::delay_frame(750);

	Cubeframe fr(400);
	fr.set(0);

	fr.draw_frame();

	//draw a smiley face

	fr.set_voxel(1, 0, 0, 0);
	fr.draw_frame();

	fr.set_voxel(1, 0, 1, 0);
	fr.draw_frame();

	fr.set_voxel(1, 4, 0, 0);
	fr.draw_frame();

	fr.set_voxel(1, 4, 1, 0);
	fr.draw_frame();

	fr.set_voxel(1, 0, 3, 0);
	fr.set_voxel(1, 1, 4, 0);
	fr.set_voxel(1, 2, 4, 0);
	fr.set_voxel(1, 3, 4, 0);
	fr.set_voxel(1, 4, 3, 0);
	fr.draw_frame();

	return 0;
}

#endif //ndef ARDUINO
