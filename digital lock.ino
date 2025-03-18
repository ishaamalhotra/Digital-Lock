#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

Servo myservo;
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);

const byte rows = 4, cols = 3;
char key[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[rows] = {0, 1, 2, 3};
byte colPins[cols] = {4, 5, 6};
Keypad keypad = Keypad(makeKeymap(key), rowPins, colPins, rows, cols);

const char* password = "1234";
char input[5] = "";
int currentPosition = 0;

void setup() {
  myservo.attach(9);
  lcd.begin(16, 2);
  displayScreen();
}

void loop() {
  char code = keypad.getKey();
  if (code) {
    if (currentPosition < 4) {
      input[currentPosition] = code;
      input[currentPosition + 1] = '\0'; 
      lcd.setCursor(0, 0);
      lcd.setCursor(9, 1);
      for (int l = 0; l <= currentPosition; ++l) lcd.print("*");
      currentPosition++;
    }
    
    if (currentPosition == 4) {
      if (strcmp(input, password) == 0) {
        unlockDoor();
      } else {
        incorrect();
      }
      currentPosition = 0;
    }
  }
}

void unlockDoor() {
  lcd.clear();
  lcd.print("Access Granted");
  lcd.setCursor(4, 1);
  lcd.print("WELCOME");

  for (int pos = 0; pos <= 180; pos += 5) {
    myservo.write(pos);
    delay(30);
  }
  countdown();
  for (int pos = 180; pos >= 0; pos -= 5) {
    myservo.write(pos);
    delay(5);
  }
  lcd.clear();
  displayScreen();
}

void incorrect() {
  lcd.clear();
  lcd.print("INCORRECT CODE!");
  delay(2000);
  lcd.clear();
  displayScreen();
}

void displayScreen() {
  lcd.setCursor(0, 0);
  lcd.print("ENTER CODE:");
  memset(input, 0, sizeof(input)); 
}

void countdown() {
  for (int i = 5; i >= 0; --i) {
    lcd.clear();
    lcd.print("ENTER IN: ");
    lcd.print(i);
    delay(100);
  }

  for (int pos = 180; pos >= 0; pos -= 5) {
    myservo.write(pos);
    delay(5);
  }

  lcd.clear();
  lcd.print("LOCKED!");
  delay(1000);
}




