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

#define PIN_YARR {_PNA, _PNB, _PNC, _PND, _PNE}

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

#endif //ndef __PINS_H
