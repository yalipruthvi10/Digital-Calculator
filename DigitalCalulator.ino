Digital calculator code
#include <Keypad.h>
#include <LiquidCrystal.h>

// Define LCD pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define keypad setup
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};   // Connect to row pins
byte colPins[COLS] = {A3, A2, A1, A0}; // Connect to column pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables for calculation
float num1 = 0, num2 = 0, result = 0;
char operation = '\0';
bool isSecondNumber = false;

void setup() {
  lcd.begin(16, 2); // Initialize the LCD
  lcd.print("Calculator Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey(); // Get key press

  if (key) {
    lcd.setCursor(0, 0);

    // If a number is pressed
    if (isDigit(key)) {
      if (!isSecondNumber) {
        num1 = num1 * 10 + (key - '0');
        lcd.print(num1);
      } else {
        num2 = num2 * 10 + (key - '0');
        lcd.print(String(num1) + String(operation) + String(num2));
      }
    }
    // If an operator is pressed
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
      operation = key;
      isSecondNumber = true;
      lcd.setCursor(0, 1);
      lcd.print(String(num1) + String(operation));
    }
    // If '=' is pressed, calculate result
    else if (key == '=') {
      switch (operation) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/':
          if (num2 != 0)
            result = num1 / num2;
          else {
            lcd.clear();
            lcd.print("Error: Div by 0");
            delay(2000);
            resetCalculator();
            return;
          }
          break;
      }
      lcd.clear();
      lcd.print("Result: ");
      lcd.setCursor(0, 1);
      lcd.print(result);
      delay(3000);
      resetCalculator();
    }
    // Clear input if 'C' is pressed
    else if (key == 'C') {
      resetCalculator();
    }
  }
}

void resetCalculator() {
  num1 = 0;
  num2 = 0;
  result = 0;
  operation = '\0';
  isSecondNumber = false;
  lcd.clear();
  lcd.print("Enter values");
}
