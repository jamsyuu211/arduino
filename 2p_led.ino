#include <math.h>
int check_case = 0;

int buttonPin = 13;

int currentButtonState = LOW;
int lastButtonState = HIGH;

int speed_currentButtonState = LOW;
int speed_lastButtonState = HIGH;

int speed_first = LOW;
int speed_second = HIGH;

int type = 1;

int k = 0;

int time = 20000;

int num = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(button()){
    int count;
    int number = 0;
    num = 0;
    time = 15000;
    if(type == 1){
        while(true){
        count = front_move(time);
        num += count;
        time = -5392 * log(num) + 15858;
        if(!count){
          break;
        }
        count = back_move(time);
        num += count;
        time = -5392 * log(num) + 15858;
        if(!count){
          break;
        }
      }
      type = 2;
    }
    else if(type == 2){
      while(true){
        count = back_move(time);
        num += count;
        time = -5392 * log(num) + 15858;
        if(!count){
          break;
        }
        count = front_move(time);
        num += count;
        time = -5392 * log(num) + 15858;
        if(!count){
          break;
        }
      }
      type = 1;
    }
  }
  if(k < 0) k = 0;
  k++;
  currentButtonState = LOW;
  lastButtonState = HIGH;
}

int front_move(int time){
  int count;
  int i = 2;
  for(int j = 4; j <= 9; j++){
    for(int t = 0; t < time; t++){
      ON_led(i, j);
    }
    OFF_led(i, j);
  }
  i = 3;
  for(int j = 9; j >= 5; j--){
    for(int t = 0; t < time; t++){
      ON_led(i, j);
    }
    OFF_led(i, j);
  }
  for(int t = 0; t < time; t++){
    count = speed_button();
    if(count){
      OFF_led(3, 4);
      return count;
    }
    ON_led(3, 4);
  }
  OFF_led(3, 4);
  defeat(3);
  return count;
}

int back_move(int time){
  int count;
  int i = 3;
  for(int j = 4; j <= 9; j++){
    for(int t = 0; t < time; t++){
      ON_led(i, j);
    }
    OFF_led(i, j);
  }
  i = 2;
  for(int j = 9; j >= 5; j--){
    for(int t = 0; t < time; t++){
      ON_led(i, j);
    }
    OFF_led(i, j);
  }
  for(int t = 0; t < time; t++){
    count = speed_button();
    if(count){
      OFF_led(2, 4);
      return count;
    }
    ON_led(2, 4);
  }
  OFF_led(2, 4);
  defeat(2);
  return count;
}

void defeat(int i){
  for(int j = 0; j < 2; j++){
    for(int t = 0; t < 5000; t++){
      ON_led(i, 10);
    }
    for(int t = 0; t < 5000; t++){
      OFF_led(i, 10);
    }
  }
}

int button(){
  currentButtonState = digitalRead(buttonPin); 
  
  if (currentButtonState == 0 && lastButtonState == 1 && k > 50) {
    k = 0;
    return 1;
  }
  
  lastButtonState = digitalRead(buttonPin);

  return 0;
}

int speed_button(){
  int count = 0;
  speed_first = digitalRead(buttonPin);
  if(speed_first == 0 && speed_second == 1){
    count++;
    k = 0;
    for(int i = 0; i < 32000; i++){
      if(count >= 3){
        return count;
      }
    speed_currentButtonState = digitalRead(buttonPin);
    if(speed_currentButtonState == 0 && speed_lastButtonState == 1 && k > 500){
      k = 0;
      i = 0;
      count++;
    }
    speed_lastButtonState = digitalRead(buttonPin);
    if(k < 0) k = 0;
    k++;
    }
  }
  speed_second = digitalRead(buttonPin);
  return count;
}

void ON_led(int pinHigh, int pinLow) {
  // 해당되지 않는 핀을 고임피던스 상태로 설정
  for (int pin = 2; pin <= 4; pin++) {
    if (pin != pinHigh && pin != pinLow) {
      pinMode(pin, INPUT); // 고임피던스 상태로 설정
    }
  }
  
  pinMode(pinHigh, OUTPUT);
  pinMode(pinLow, OUTPUT);
  digitalWrite(pinHigh, HIGH);
  digitalWrite(pinLow, LOW);
}

void OFF_led(int pinHigh, int pinLow) {
  // 해당되지 않는 핀을 고임피던스 상태로 설정
  pinMode(pinHigh, INPUT);
  pinMode(pinLow, INPUT);
}