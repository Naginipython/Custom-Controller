#include <Wire.h>
#include <Nunchuk.h>
#include <XInput.h>

/* Pin to board key
| 09 | 08 | 10 | 16 || 14 | 15 |
| 07 | 06 | 5? | 04 || A0 | A1 |
*/
enum Pins {
  PIN_A = 7,
  PIN_B = 10,
  PIN_X = 9,
  PIN_Y = 8,
  PIN_LB = 5,
  PIN_RB = 16,
  PIN_LT = 4,
  PIN_RT = 6,
  PIN_START = 15,
  PIN_SELECT = 14,
  PIN_LEFT = A0,
  PIN_RIGHT = A1
};

void setup() {
  pinMode(PIN_A,     INPUT_PULLUP);  //A
  pinMode(PIN_B,     INPUT_PULLUP); //B
  pinMode(PIN_X,     INPUT_PULLUP);  //X
  pinMode(PIN_Y,     INPUT_PULLUP);  //Y
  pinMode(PIN_LB,    INPUT_PULLUP);  //LB
  pinMode(PIN_RB,    INPUT_PULLUP);  //RB
  pinMode(PIN_LT,    INPUT_PULLUP);  //LT
  pinMode(PIN_RT,    INPUT_PULLUP); //RT
  pinMode(PIN_START, INPUT_PULLUP); //START
  pinMode(PIN_SELECT,INPUT_PULLUP); //SELECT
  pinMode(PIN_LEFT,  INPUT_PULLUP); //idk. Left?
  pinMode(PIN_RIGHT, INPUT_PULLUP); //idk. Right?
  // pinMode(A2,  INPUT_PULLUP); //temp
  // pinMode(A3,  INPUT_PULLUP); //temp

  Wire.begin(); // D2 is SDA, D3 is SCL
  nunchuk_init();
  // XInput.setAutoSend(false);  // disable automatic output
	XInput.begin();
}

void loop() {
  // Joystick movement
  if (nunchuk_read()) {
    // nunchuk_print();
    int x = nunchuk_joystickX() * 320;
    int y = nunchuk_joystickY() * 320;
    XInput.setJoystickX(JOY_LEFT, x);
    XInput.setJoystickY(JOY_LEFT, y);
  } else {
    Serial.println("No Nunchuk");
  }

  // Button Presses
  int A, B, X, Y, LB, RB, LT, RT, START, SELECT, L3, LEFT, RIGHT;
  A = digitalRead(PIN_A);
  B = digitalRead(PIN_B);
  X = digitalRead(PIN_X);
  Y = digitalRead(PIN_Y);
  LB = digitalRead(PIN_LB);
  RB = digitalRead(PIN_RB);
  LT = digitalRead(PIN_LT);
  RT = digitalRead(PIN_RT) && !nunchuk_buttonZ();
  START = digitalRead(PIN_START);
  SELECT = digitalRead(PIN_SELECT);
  L3 = !nunchuk_buttonC();
  LEFT = digitalRead(PIN_LEFT);
  RIGHT = digitalRead(PIN_RIGHT);

  if(A == LOW) XInput.press(BUTTON_A);
  else XInput.release(BUTTON_A);

  if(B == LOW) XInput.press(BUTTON_B);
  else XInput.release(BUTTON_B);

  if(X == LOW) XInput.press(BUTTON_X);
  else XInput.release(BUTTON_X);

  if(Y == LOW) XInput.press(BUTTON_Y);
  else XInput.release(BUTTON_Y);
  
  if(LB == LOW) XInput.press(BUTTON_LB);
  else XInput.release(BUTTON_LB);
  
  if(RB == LOW) XInput.press(BUTTON_RB);
  else XInput.release(BUTTON_RB);
  
  if(LT == LOW) XInput.press(TRIGGER_LEFT);
  else XInput.release(TRIGGER_LEFT);
  
  if(RT == LOW) XInput.press(TRIGGER_RIGHT);
  else XInput.release(TRIGGER_RIGHT);
  
  if(START == LOW) XInput.press(BUTTON_START);
  else XInput.release(BUTTON_START);
  
  if(SELECT == LOW) XInput.press(BUTTON_BACK);
  else XInput.release(BUTTON_BACK);
  
  if(L3 == LOW) XInput.press(BUTTON_L3);
  else XInput.release(BUTTON_L3);

  XInput.setDpad(0, 0, !LEFT, !RIGHT); //up,down,left,right

  // XInput.send();
  delay(15);
}






