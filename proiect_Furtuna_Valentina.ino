#include "pitches.h"
#include <SPI.h>

const int buzzerPin = 6;
int x = 500; 
int Tbit_us = 1000000/100;

#define LED12 12
#define LED08 8
#define LED10 10
#define BUTON1 2
#define BUTON2 9
#define BUTON3 1

#define SID 11
#define SS_PIN 4
#define SCK_PIN 13
#define RS_PIN 7

int melody1[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int durations1[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

int melody2[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4, 
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4, 
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
  NOTE_A4
};

int durations2[] = {
  8, 8, 4, 4,
  8, 8, 4, 4,
  8, 8, 4, 4,
  2
};

int melody3[] = {
  NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_C4, NOTE_F4,
  NOTE_E4, NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_C4, NOTE_C4,
  
  NOTE_C5, NOTE_A4, NOTE_F4, 
  NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_F4
};

int durations3[] = {
  4, 8, 
  4, 4, 4,
  2, 4, 8, 
  4, 4, 4,
  2, 4, 8,
  
  4, 4, 4, 
  4, 4, 4, 8,
  4, 4, 4,
  2
};

void setup()
{
	pinMode(BUTON3, INPUT);
	pinMode(LED10, OUTPUT);
	pinMode(BUTON1, INPUT);
	pinMode(LED08, OUTPUT);
	pinMode(BUTON2, INPUT);
	pinMode(LED12, OUTPUT);
	pinMode(buzzerPin, OUTPUT);
	for(int i = 3; i<=8; i++)
		pinMode(i, OUTPUT);

	pinMode(SID, OUTPUT);
	pinMode(SCK_PIN, OUTPUT);
	pinMode(SS_PIN, OUTPUT);
	pinMode(RS_PIN,OUTPUT);

}

void loop()
{

	if(digitalRead(BUTON1) == LOW)
	{	
		delay(10); 
		if(digitalRead(BUTON1) == LOW)
		{	
			displaySongName("Merry Christmas");
			delay(10);

			digitalWrite(LED10, HIGH); 

			int size1 = sizeof(durations1) / sizeof(int);

			for (int note1 = 0; note1 < size1; note1++) {
				int duration1 = 1000 / durations1[note1];
				tone(buzzerPin, melody1[note1], duration1);

				int pauseBetweenNotes1 = duration1 * 1.30;
				delay(pauseBetweenNotes1);

				noTone(buzzerPin);
			}
			digitalWrite(LED10, LOW);
		}

	}

	if(digitalRead(BUTON2) == LOW)
	{	
		delay(10); 
		if(digitalRead(BUTON2) == LOW)
		{	
			displaySongName("Nokia Song");
			delay(10);
			digitalWrite(LED08, HIGH); 

			int size2 = sizeof(durations2) / sizeof(int);

			for (int note2 = 0; note2 < size2; note2++) {
				int duration2 = 1000 / durations2[note2];
				tone(buzzerPin, melody2[note2], duration2);

				int pauseBetweenNotes2 = duration2 * 1.30;
				delay(pauseBetweenNotes2);

				noTone(buzzerPin);
			}
			digitalWrite(LED08, LOW);

		}

	}

	if(digitalRead(BUTON3) == LOW)
	{	
		delay(10); 
		if(digitalRead(BUTON3) == LOW)
		{	

			displaySongName("Happy Birthday");
			delay(10);
			digitalWrite(LED12, HIGH); 

			int size3 = sizeof(durations3) / sizeof(int);

			for (int note3 = 0; note3 < size3; note3++) {
				int duration3 = 1000 / durations3[note3];
				tone(buzzerPin, melody3[note3], duration3);

				int pauseBetweenNotes3 = duration3 * 1.30;
				delay(pauseBetweenNotes3);

				noTone(buzzerPin);
			}
			digitalWrite(LED12, LOW);

		}

	}
}

void displaySongName(const char* songName) {
	digitalWrite(SS_PIN, LOW);
	linie_in_repaus();
	LCD_init();

	for (int i = 0; songName[i] != '\0'; ++i) {
		SPI_wr_byte(songName[i]); 
	}

	linie_in_repaus();
	digitalWrite(SS_PIN, HIGH);
	delay(2000);  
}

void linie_in_repaus(){
	digitalWrite(SID, HIGH);
	digitalWrite(SCK_PIN, LOW);
}

void pulsCeas(){
	delayMicroseconds(Tbit_us/2);
	digitalWrite(SCK_PIN, HIGH);
	delayMicroseconds(Tbit_us/2);
	digitalWrite(SCK_PIN, LOW);
}

void LCD_init(){
	delay(15); 
	digitalWrite(RS_PIN, LOW);
	SPI_wr_byte(0x30); 
	delay(5); 
	for(int i=0; i<2; i++){	
		SPI_wr_byte(0b00111000); 
		delayMicroseconds(160);
	}
	SPI_wr_byte(0x10); 
	delayMicroseconds(40);
	SPI_wr_byte(0b00000001);
	delay(2); 
	SPI_wr_byte(0b00000110);
	delayMicroseconds(40); 
	SPI_wr_byte(0b00001111); 
	delayMicroseconds(40);
	SPI_wr_byte(0x80);
	delayMicroseconds(40);
	digitalWrite(RS_PIN, HIGH); 
	delayMicroseconds(40);
}

void SPI_wr_byte(char x){
	int bitActual;
	for(int j=7; j>=0; j--){
		bitActual=bitRead(x, j);
		if (bitActual == 0)
			digitalWrite(SID, LOW);
		else
			digitalWrite(SID, HIGH);
		pulsCeas();
	}
}
