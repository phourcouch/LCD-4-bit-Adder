#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

const int buttonPin1 = 5; // Button 1
const int buttonPin2 = 4; // Button 2
const int buttonPin3 = 3; // Button 3
const int buttonPin4 = 2; // Button 4

static int previous = 0;

int a0 = 0; // variable for input state of the button 1
int a1 = 0; // variable for input state of the button 2
int a2 = 0; // variable for input state of the button 3
int a3 = 0; // variable for input state of the button 4

int s0 = 0, s1 = 0, s2 = 0, s3 = 0; // initialize variable for sum

int total = 0;
int L1 = 0, L2 = 0, L3 = 0, L4 = 0;


void setup() {
  Serial.begin(9600);

  // set buttons as input, the open button logic state for all will be HIGH with "PULLUP" after "INPUT"
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  lcd.init();           
  lcd.clear();          // Clear all text on LCD
  lcd.backlight();      // Make sure backlight is on
  lcd.setCursor(2,0);   // Set cursor to character 2 on line 0
  lcd.print((String)total); // Display 0 to display on start
}

void loop() { 
  a0 = digitalRead(buttonPin1);
  a0 = !a0;
  a1 = digitalRead(buttonPin2);
  a1 = !a1;
  a2 = digitalRead(buttonPin3);
  a2 = !a2;
  a3 = digitalRead(buttonPin4);
  a3 = !a3;

  s0 = a0;
  s1 = a1;
  s2 = a2;
  s3 = a3;

  if(s0 == HIGH) {
    L1 = 1;
  } else {
    L1 = 0;
  }

  if(s1 == HIGH) {
    L2 = 1;
  } else {
    L2 = 0;
  }

  if(s2 == HIGH) {
    L3 = 1;
  } else {
    L3 = 0;
  }

  if(s3 == HIGH) {
    L4 = 1;
  } else {
    L4 = 0;
  }

  total = ((1*L1) + (2*L2) + (4*L3) + (8*L4));

  if(previous != total)   // only update screen of changes in total occur from previous loop
  {
    Serial.println(total);
    lcd.clear();          // Clear all text on LCD
    lcd.setCursor(2,0);   // Set cursor to character 2 on line 0
    lcd.print((String)total); // Display total onto LCD
  }
  previous = total;   // update previous
}
