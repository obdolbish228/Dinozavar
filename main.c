#define R_WHEEL 0.3

#include "main.h"
#include "LCD.h"

char place[128] = {
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ',
' ', ' ', ' ', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', ' ', ' ', ' ',
'|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', '.', ' ',
' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '.', ' ', ' ',
' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '.', ' ', ' ', ' ', ' ',
' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ',
'|', ' ', ' ', ' ', '?', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' '
};
/*const int place[128] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};*/
/*const char place[16] = {
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' '
};*/
/*uint8_t ovf = 0;
uint16_t tic = 0;
float RPS = 0;
float Omega = 0;
float V = 0;
char str[17]={'\0'};
	

	
void Dino(){
	
}*/
char str[17]={'\0'};

/*ISR(INT0_vect){
	tic = TCNT1H << 8;
	tic |= TCNT1L;
	RPS = 1 / ((float)tic * 0.000032 + (float)ovf * 2.09712);
	Omega = RPS * 60 / 9.554;
	V = Omega * R_WHEEL * 3.6;
	RPS = 0;
	ovf = 0;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	
	sprintf(str, "%2d", (int)V);
	LCD_SetPos(0, 1);
	LCD_String(str);
}

ISR(TIMER1_OVF_vect){  //1 tic = 0.000032 c, 1 ovf = 2.09712
	if(ovf < 250)
		ovf++;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
}*/
	
	uint8_t i = 0;
	uint8_t highScore = 0;
	char frame[17] = {'\0'};
	char din[2] = {'W','\0'};
	const int ms = 150;
	uint8_t j = 0;
	uint16_t seed = 0;
	uint8_t rnd = 0;
	uint16_t score = 0;
	uint8_t stepHard = 0;
	uint8_t readyHard = 0;
	uint8_t btn = 0;

void Frame(){
	seed++;
	srand(seed);
	if (i == 128)
	{
		i = 0;
	}
	
	rnd = rand() % 100 + 1;
	if((rnd < 10 + stepHard) && (place[(15 + i) % 128] == ' ') && (place[(14 + i) % 128] == ' ') ){
		place[(16 + i) % 128] = '|';
	}
	else{
		place[(16 + i) % 128] = ' ';
	}
	
	for (j = 0; j < 16; j++)
	{
		frame[j] = place[(i + j) % 128];
	}
	
	LCD_Clear();
	LCD_SetPos(0, 1);
	LCD_String(frame);
	LCD_SetPos(8, 0);
	LCD_String((char*)"Score:");
	LCD_SetPos(14, 0);
	sprintf(str, "%2d", score);
	LCD_String(str);
	i++;
	if (stepHard < 30)
	{
		readyHard++;
		if(readyHard == 25){
			stepHard++;
			readyHard = 0;
		}	
	}
	
	
}

void Dino(){
	if (frame[0] == '|')
	{
		Lose();
	}
	else{
		LCD_SetPos(0, 1);
		LCD_String(din);
	}
}	

void DinoUp(){
	LCD_SetPos(0, 0);
	LCD_String(din);
	if (frame[0] == '|')
	{
		score++;
	}
}

void Lose(){
	LCD_Clear();
	if (score > highScore)
	{
		highScore = score;
	}
	while(!(PINB &= 0x02)){
		LCD_SetPos(14, 0);
		sprintf(str, "%2d", score);
		LCD_String(str);
		LCD_SetPos(14, 1);
		sprintf(str, "%2d", highScore);
		LCD_String(str);
		LCD_SetPos(0, 0);
		LCD_String((char*)"PIDR .");
		LCD_SetPos(0, 1);
		LCD_String((char*)"SOSI O");
		_delay_ms(ms * 2);
		LCD_SetPos(0, 0);
		LCD_String((char*)"PIDR o");
		LCD_SetPos(0, 1);
		LCD_String((char*)"SOSI o");
		_delay_ms(ms * 2);
		LCD_SetPos(0, 0);
		LCD_String((char*)"PIDR O");
		LCD_SetPos(0, 1);
		LCD_String((char*)"SOSI .");
		_delay_ms(ms * 2);
	}
	LCD_Clear();
	btn = 0;
	score = 0;
	
	for (j = 0; j < 16; j++)
	{
		place[(j + i) % 128] = ' ';
	}
}

void Dinozavr(){
	while(1){
		if (btn == 0 && !(PINB &= 0x02))
		{
			seed++;
			LCD_SetPos(0, 0);
			LCD_String((char*)"  DINOZAVAR!!!  ");
		}
		else{
			if (btn == 0)
			{
				btn = 1;
				LCD_Clear();
			}
		
			if (!(PINB &= 0x01))
			{
				Frame();
				Dino();
				_delay_ms(ms);
			}
			else
			{
				Frame();
				DinoUp();
				_delay_ms(ms);
				Frame();
				DinoUp();
				_delay_ms(ms);
				Frame();
				Dino();
				_delay_ms(ms);
			}
			seed++;
		}	
	}
}

int main(void)
{
    DDRC = 0x3F;
	DDRB = 0x00;
	DDRD = 0x00;
	
	PORTC = 0x00;
	PORTB = 0x00;
	PORTD = 0x00;
	
	LCD_Init();
	LCD_Clear();
	
    while (1){
		
		
		Dinozavr();
		
		
		
		
    }
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	//LCD_SetPos(0, 0);
	//LCD_String((char*)"SUKA BLYATT!!");
	//_delay_ms(100);
	
	/*sei();
	
	TIMSK1 = 0x01;
	TCCR1B = 0x05;
	
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	
	EICRA = 0x02;
	EIMSK = 0x01;
	uint8_t inc = 0;*/

