
void initLiquidCrystal() {
  int buttonPin = 0;
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("Ready"); // print a simple message
  pinMode(buttonPin, INPUT);
}



void readTM1638() {
  unsigned char buttons = ioi.readKey();;
#define buffer_len 9
  char buffer[buffer_len];
  String vars;

  if (buttons)  {
    Serial.println(buttons);
    vars = padS(String(buttons), 8, " ");
    vars.toCharArray(buffer, buffer_len);
   ioi.DisplayStr(buffer, 0);
  }

}

//-------------liquid crystal
void scrollLiquidCrystal() {
  static long previous = millis();
  String stri;
  int msStop = 500;
  if (previous + msStop <= millis()) {
    previous =  millis();
    elabKey();
    lcd.setCursor(0, 1);
    stri=ScrollFunction(line1, 0);
    lcd.print( stri);
    Serial.println(stri);
  }
}

String ScrollFunction(String lline, int riga) {
  int copySize = 16;
  static int ppos = 0;
  static String stToPrnt = padS("",copySize," ");

  ppos = ppos % lline.length();
  stToPrnt = stToPrnt.substring(1) + lline.substring(ppos ,ppos + 1 );
  ppos++;

  return stToPrnt;
}


void elabKey() {
  int lcd_key     = 0;
  lcd.setCursor(0, 1);           // move to the begining of the second line
  lcd_key = read_LCD_buttons();  // read the buttons

  switch (lcd_key) {              // depending on which button was pushed, we perform an action
    case btnRIGHT:
      lcd.print(F("RIGHT "));
      Serial.println("RIGHT ");
      break;
    case btnLEFT:
      lcd.print(F("LEFT   "));
      Serial.println(F("LEFT "));
      break;
    case btnUP:
      lcd.print(F("UP    "));
      Serial.println(F("UP "));
      break;
    case btnDOWN:
      lcd.print(F("DOWN  "));
      Serial.println(F("DOWN "));
      break;
    case btnSELECT:
      //   lcd.print(F("SELECT"));
      Serial.println(F("SELECT "));
      break;
    case btnNONE:
      // lcd.print("NONE  ");
      break;
  }
}

int read_LCD_buttons() {
  int adc_key_in  = 0;
  adc_key_in = analogRead(0);      // read the value from the sensor
  Serial.println(adc_key_in);
  if (adc_key_in < 60)   return btnRIGHT;
  else if (adc_key_in < 150) return btnUP;
  else if (adc_key_in < 300) return btnDOWN;
  else if (adc_key_in < 500) return btnLEFT;
  else if (adc_key_in < 800) return btnSELECT;
  else if (adc_key_in > 800) return btnNONE;
  Serial.println(adc_key_in);

  return btnNONE;  // when all others fail, return this...
}
String padD(String sstt, int lens, String charsub) {
  //pad a dx
  String spaces = "";
  for (int i = sstt.length(); i < lens; i++) spaces = spaces + charsub;
  return sstt + spaces;
}
String padS(String sstt, int lens, String charsub) {
  //pad a sx
  String spaces = "";
  for (int i = sstt.length(); i < lens; i++) spaces = spaces + charsub;
  return spaces + sstt;
}
