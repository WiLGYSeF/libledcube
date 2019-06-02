#ifndef __PINS_H
#define __PINS_H

//shift register pins
#define _PDATA 11
#define _PCLOCK 13
#define _PLATCH 12

//y pins
#define _PNA 0
#define _PNB 1
#define _PNC 2
#define _PND 3
#define _PNE 4

//array of y pins
const uint8_t PIN_YARR[] = {_PNA, _PNB, _PNC, _PND, _PNE};

#endif //ndef __PINS_H
