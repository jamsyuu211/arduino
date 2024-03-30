//버튼용 변수
int buttonPin = 13;
int mode = 0;

bool ledState = LOW;         // 현재 LED 상태
bool lastButtonState = LOW;  // 마지막 버튼 상태
bool currentButtonState = LOW; // 현재 버튼 상태

int score = 0;

int level = 1;

typedef struct{
  int i;
  int j;
}num;

num number;

void setup() {
  // 찰리플렉싱 led 초기화
  Serial.begin(9600);
}

void loop(){
  f_score();
  button();
  if(mode % 2 == 0){
    if(level == 5){
      level = 1;
    }
    OFF_all();
  }
  else if(mode % 2 == 1){
    OFF_led(8, 7); //점수 led off
    OFF_led(8, 6);
    OFF_led(7, 8);
    if(level == 5){
      level = 1;
    }
    if(level <= 2){
      game_first();
    }
    else{
      game_second();
    }
  }
}

void game_first(){
    circle(change_time(level));
    if(number.i == 3 && number.j == 6){
      score++;
      for(int i = 0; i < 3; i++){
        //answer func
        led_select(number, 6, 8);
      }
    }
    else if(number.i != 0 && number.j != 0){
      if(score > 0)
        score--;
      else
        score = 0;
      for(int i = 0; i < 3; i++){
        led_select(number, 7, 6);
      }
    }
}

void game_second(){
    if(side_move(change_time_side(level)) == 0){
      if(number.i == 2 && number.j == 6){
        score++;
        for(int i = 0; i < 2; i++){
          //answer func
          ON_led(6, 8);
          delay(300);
          OFF_led(6, 8);
          delay(300);
        }
      }
     else if(number.i != 0 && number.j != 0){
        if(score > 0)
          score--;
          else
          score = 0;
        for(int i = 0; i < 2; i++){
          ON_led(7, 6);
          delay(300);
          OFF_led(7, 6);
          delay(300);
        }
     }
    }
}

int side_move(int time){
  number = {0, 0};
  int i = 2;
  for(int j = 4; j <= 8; j++){
    for(int k = 0; k < time * 50; k++){
      ON_led(i, j);
      if(button() % 2 == 0){
        number.i = i;
        number.j = j;
        return 0;
      }
    }
    OFF_led(i, j);
  }
  for(int j = 8; j >= 4; j--){
    for(int k = 0; k < time * 50; k++){
      ON_led(i, j);
      if(button() % 2 == 0){
        number.i = i;
        number.j = j;
        return 0;
      }
    }
    OFF_led(i, j);
  }
}

int change_time_side(int level){
  return -10 * level + 90;
}

void led_select(num number, int first, int second){
  for(int i = 0; i < 3000; i++){
    ON_led(number.i, number.j);
    OFF_led(number.i, number.j);
    ON_led(first, second);
    OFF_led(first, second);
  }
  delay(300);
}

int change_time(int level){
  return -80 * level + 230;
}

void f_score(){
  if(score == 0){
    OFF_led(8, 7);
    OFF_led(8, 6);
    OFF_led(7, 8);
  }
  else if(score == 1){
    ON_led(8, 7);
  }
  else if(score == 2){
    ON_led(8, 7);
    OFF_led(8, 7);
    ON_led(8, 6);
    OFF_led(8, 6);
  }
  else if(score == 3){
    ON_led(8, 7);
    OFF_led(8, 7);
    ON_led(8, 6);
    OFF_led(8, 6);
    ON_led(7, 8);
    OFF_led(7, 8);
  }
  else if(score == 4){
    for(int j = 0; j < 3; j++){
      for(int i = 0; i < 3000; i++){
        ON_led(8, 7);
        OFF_led(8, 7);
        ON_led(8, 6);
        OFF_led(8, 6);
        ON_led(7, 8);
        OFF_led(7, 8);
        ON_led(7, 6);
        OFF_led(7, 6);
        ON_led(6, 8);
        OFF_led(6, 8);
      }
      OFF_led(8, 7);
      OFF_led(8, 6);
      OFF_led(7, 8);
      OFF_led(6, 8);
      OFF_led(7, 6);
      delay(500);
    }
    score = 0;
    level++;
  }
}

int circle(int time){
  number = {0, 0};
  int i = 2;
  for(int j = 4; j <= 8; j++){
    for(int k = 0; k < time * 30; k++){
      ON_led(i, j);
      if(button() % 2 == 0){
        number.i = i;
        number.j = j;
        return 0;
      }
    }
    OFF_led(i, j);
  }
  i = 3;
  for(int j = 8; j >= 4; j--){
    for(int k = 0; k < time * 30; k++){
      ON_led(i, j);
      if(button() % 2 == 0){
        number.i = i;
        number.j = j;
        return 0;
      }
    }
    OFF_led(i, j);
  }
}

int button(){
  currentButtonState = digitalRead(buttonPin); 
  
  if (currentButtonState == 0 && lastButtonState == 1) {
    mode++;
  }
  lastButtonState = digitalRead(buttonPin);
  return mode;
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

void ON_all(){
  for(int i = 2; i <= 3; i++){
      for(int j = 4; j <= 8; j++){
        ON_led(i, j);
      }
    }
}

void OFF_all(){
  for(int i = 2; i <= 3; i++){
      for(int j = 4; j <= 8; j++){
        OFF_led(i, j);
      }
    }
}