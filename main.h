#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Frame();
void Dino();
void DinoUp();
void Lose();
void Dinozavr();

#endif /* MAIN_H_ */