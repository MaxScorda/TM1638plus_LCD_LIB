#include <IOInt.h>
#include <TM1638plus_Model2.h> //da togliee
#include <LiquidCrystal.h>
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

IOINT ioi(13, 9, 10, 11, 12); //lcd5110
TM1638plus_Model2 TM(37, 35 , 33, true); //da togliere

String line1 = "Il pezzo d'hardware piu' inutile che abbia mai fatto. E ci sto pure a perdere tempo.";
String line2 = " Una realizazione Cane Nico Morto Production (c) 2014 ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ioi.keyboardInit(4, 37, 35, 33);
  initLiquidCrystal();
}

void loop() {
  // put your main code here, to run repeatedly:
  read_LCD_buttons();
  scrollLiquidCrystal();
  readTM1638();
}
