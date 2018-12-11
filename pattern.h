#ifndef __PATTERN_H
#define __PATTERN_H

#include "cubemap.h"

#ifdef __cplusplus
extern "C" {
#endif

void pat_alternate_full(struct cubeframe *fr, uint8_t zero_on);
void pat_border(struct cubeframe *fr, uint8_t led_on, uint8_t width);
void pat_random(struct cubeframe *fr);
void pat_random_modify(struct cubeframe *fr, struct cubeframe *ref, size_t count);

void pat_border_bounce(size_t count, uint16_t delay);
void pat_border_spin(uint8_t clockwise, cubeperim voxelperlevel, size_t count, uint16_t delay);
void pat_firework(uint16_t launchdelay, uint16_t explosiondelay);
void pat_plane_bounce(size_t count, uint16_t delay);
void pat_rain(size_t count, uint16_t delay);
void pat_random_set(uint8_t led_on, uint16_t delay);
void pat_send_voxel(uint8_t axis, size_t count, uint16_t delay, uint16_t leveldelay);
void pat_stream(uint8_t axdir, size_t count, size_t spacing, uint16_t delay);

#ifdef __cplusplus
}
#endif

#endif //ndef __PATTERN_H
