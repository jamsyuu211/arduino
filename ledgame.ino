int Brightness = 0; //LED밝기

int answer = 0;//함수에서 LED반짝인 횟수 반환하는 변수
int count;//노란색 LED깜박이는 횟수
int times;//불꺼짐 유지시간

char input; //게임 시작 OR 종료 입력 변수
int value; //사용자가 입력한 정답

int _time; //깜빡임 유지시간
int choice; //X + 연산을 랜덤으로 선택하는 변수

int first_answer = 0; //첫번째 숫자
int sec_answer = 0; //두번째 숫자

int score = 0;//점수
int level; //난이도
int bonus;
int penalty;

//찰리 플렉싱 알고리즘 변수
int pin2 = 2;
int pin3 = 3;
int pin4 = 4;

void setup() {
  // 찰리플렉싱 led 초기화
  pinMode(pin2, OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4, OUTPUT);


  Serial.begin(9600);
  randomSeed(analogRead(0));
  Serial.print("--Notification--\n");
  Serial.print("Yellow : number, Red : +, Green : *\n");
  Serial.print("Choice the level\n");
  Serial.print("1 : easy, 2 : normal, 3 : hard\n");
}

void loop(){
  answer = 0;
  sec_answer = 0;
  choice = random(1, 3);
      
    if(Serial.available() > 0){
      level = Serial.parseInt();
      OFF_all();
      if(level == 1){
        Serial.print("[level 1] Start\n");
        stage1();
        print_message();
      }
      else if(level == 2){
        Serial.print("[level 2] Start\n");
        stage2();
        print_message();
      }
      else if(level == 3){
        Serial.print("[level 3] Start\n");
        stage3();
        print_message();
      }
    }
    else{
      for(int i = 0; i < 7; i++){
        if(Serial.available() > 0)
          break;
        circle();
      }
      for(int i = 0; i < 5; i++){
        if(Serial.available() > 0)
          break;
        cross();
      }
      for(int i = 0; i < 5; i++){
        if(Serial.available() > 0)
          break;
        up_down();
      }
      for(int i = 0; i < 5; i++){
        if(Serial.available() > 0)
          break;
        snake();
      }
    }
}

void circle(){
  ON_led(pin3, pin2);//노
  delay(70);
  ON_led(pin2, pin3);//노
  delay(70);
  ON_led(pin4, pin2);//빨
  delay(70);
  ON_led(pin4, pin3);//노
  delay(70);
  ON_led(pin2, pin4);//초
  delay(70);
  ON_led(pin3, pin4);//빨
  delay(70);
}

void twinkle_all(){
  for(int i = 0; i < 3000; i++){
    ON_all();
  }
  OFF_all();
  delay(500);
}

void twinkle_red(){
  for(int i = 0; i < 10000; i++){
    ON_led(pin3, pin4);//빨
    OFF_led(pin3, pin4);
    ON_led(pin4, pin2);//빨
    OFF_led(pin4, pin2);
  }
  OFF_all();
  delay(500);
}

void count_down(){
  for(int i = 0; i < 10000; i++){
    ON_all();
  }
  for(int i = 0; i < 8000; i++){
    ON_led(pin2, pin3);//노
    OFF_led(pin2, pin3);
    ON_led(pin4, pin2);//빨
    OFF_led(pin4, pin2);
    ON_led(pin3, pin4);//빨
    OFF_led(pin3, pin4);
    ON_led(pin2, pin4);//초
    OFF_led(pin2, pin4);
    ON_led(pin4, pin3);//노
    OFF_led(pin4, pin3);   
  }
  for(int i = 0; i < 8000; i++){
    ON_led(pin4, pin2);//빨
    OFF_led(pin4, pin2);
    ON_led(pin3, pin4);//빨
    OFF_led(pin3, pin4);
    ON_led(pin2, pin4);//초
    OFF_led(pin2, pin4);
    ON_led(pin4, pin3);//노
    OFF_led(pin4, pin3);   
  }
  for(int i = 0; i < 12000; i++){
    ON_led(pin3, pin4);//빨
    OFF_led(pin3, pin4);
    ON_led(pin2, pin4);//초
    OFF_led(pin2, pin4);
    ON_led(pin4, pin3);//노
    OFF_led(pin4, pin3);   
  }
  for(int i = 0; i < 15000; i++){
    ON_led(pin2, pin4);//초
    OFF_led(pin2, pin4);
    ON_led(pin4, pin3);//노
    OFF_led(pin4, pin3);   
  }
  for(int i = 0; i < 28000; i++){
    ON_led(pin4, pin3);//노
    OFF_led(pin4, pin3);  
  }
  OFF_led(pin4, pin3);  
  delay(1000);
}

void cross(){
  for(int i = 0; i < 3000; i++){
    ON_led(pin3, pin2);//노
    OFF_led(pin3, pin2);
    ON_led(pin4, pin3);//노
    OFF_led(pin4, pin3);
  }
  for(int i = 0; i < 3000; i++){
    ON_led(pin2, pin3);//노
    OFF_led(pin2, pin3);
    ON_led(pin2, pin4);//초
    OFF_led(pin2, pin4);
  }
  for(int i = 0; i < 3000; i++){
    ON_led(pin4, pin2);//빨
    OFF_led(pin4, pin2);
    ON_led(pin3, pin4);//빨
    OFF_led(pin3, pin4);
  }
  for(int i = 0; i < 3000; i++){
    ON_led(pin2, pin3);//노
    OFF_led(pin2, pin3);
    ON_led(pin2, pin4);//초
    OFF_led(pin2, pin4);
  }
}

void up_down(){
  for(int i = 0; i < 2000; i++){
    ON_led(pin3, pin2);//노
    OFF_led(pin3, pin2);
    ON_led(pin2, pin3);//노
    OFF_led(pin2, pin3);
    ON_led(pin4, pin2);//빨
    OFF_led(pin4, pin2);
  }
  for(int i = 0; i < 2000; i++){
    ON_led(pin4, pin3);//노
    OFF_led(pin4, pin3);
    ON_led(pin2, pin4);//초
    OFF_led(pin2, pin4);
    ON_led(pin3, pin4);//빨
    OFF_led(pin3, pin4);
  }
}

void snake(){
  ON_led(pin3, pin2);//노
  delay(100);
  ON_led(pin3, pin4);//빨
  delay(100);
  ON_led(pin2, pin4);//초
  delay(100);
  ON_led(pin2, pin3);//노
  delay(100);
  ON_led(pin4, pin2);//빨
  delay(100);
  ON_led(pin4, pin3);//노
  delay(100);
  ON_led(pin4, pin2);//빨
  delay(100);
  ON_led(pin2, pin3);//노
  delay(100);
  ON_led(pin2, pin4);//초
  delay(100);
  ON_led(pin3, pin4);//빨
  delay(100);
}

int show_number(){
  for(int i = 0; i < count; i++){
    init_time(level);
    ON_yellow();
    delay(_time);
    OFF_yellow();
    delay(times);
  }
  return count;
}

void ON_yellow(){
  ON_led(pin4, pin3);//노
}

void OFF_yellow(){
  OFF_led(pin4, pin3);//노
}

void ON_red(){
  pinMode(pin3, OUTPUT);
  digitalWrite(pin3, HIGH);
  pinMode(pin4, OUTPUT);
  digitalWrite(pin4, LOW);
  pinMode(pin2, INPUT);
}

void OFF_red(){
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
}

void ON_green(){
  ON_led(pin2, pin4);//초
}

void OFF_green(){
  OFF_led(pin2, pin4);
}

void ON_all(){//green
  ON_led(pin3, pin2);//노
  ON_led(pin2, pin3);//빨
  ON_led(pin4, pin2);//노
  ON_led(pin4, pin3);//노
  ON_led(pin2, pin4);//초
  ON_led(pin3, pin4);//빨
}

void OFF_all(){
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

//연산 부호 랜덤선택 함수
void choices() {
  if(choice == 1){//+
    ON_red();
    delay(1000);
    OFF_red();
  }
  else{//x 
    ON_green();
    delay(1000);
    OFF_green();
  }
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
  digitalWrite(pinHigh, LOW);
  digitalWrite(pinLow, LOW);
}

void init_time(int level){
  if(level == 1){
    times = random(250, 1000);//불꺼짐 유지시간
  _time = random(300,1000);//불켜짐 유지시간
  }
  else if(level == 2){
     times = random(200, 800);
    _time = random(100, 800);
  }
  else if(level == 3){
     times = random(100, 800);
    _time = random(100, 500);
  }
}
//변수 초기화 함수
void init_num(int level){
  score = 0;
  if(level == 1){
  count = random(1, 8);//깜빡임 횟수
  times = random(250, 1000);//불꺼짐 유지시간
  _time = random(300,1000);//불켜짐 유지시간
  }
  else if(level == 2){
    count = random(3, 11);
    times = random(200, 800);
    _time = random(100, 800);
  }
  else if(level == 3){
    count = random(5, 13);
    times = random(100, 800);
    _time = random(100, 500);
  }
}

void print_message(){
  Serial.print("Score : ");
  Serial.print(score);
  Serial.print('\n');
  Serial.print("Choice the level\n");
  Serial.print("1 : easy, 2 : normal, 3 : hard\n");
}

//사용자 입력에 따라 출력하는 함수
void stage1(){

    count_down();
  
    init_num(1);
    first_answer = show_number();

    choices();

    init_num(1);
    sec_answer = show_number();

    /*
    //웹에서 횟수 확인용임으로 제거 필요
    if(choice == 1){
      Serial.print('\n');
      Serial.print(first_answer);
      Serial.print("\n+\n");
      Serial.print(sec_answer);
      Serial.print('\n');
      Serial.print(first_answer + sec_answer);
      Serial.print('\n');
    }
    else{
      Serial.print('\n');
      Serial.print(first_answer);
      Serial.print("\nx\n");
      Serial.print(sec_answer);
      Serial.print('\n');
      Serial.print(first_answer * sec_answer);
      Serial.print('\n');
    }
      
    Serial.print('\n');
    //여기까지*/


  //정답 입력받는 중
    Serial.print("answering time\n");
    count_down();
    value = Serial.parseInt();

    //선택
    if(choice == 1){
      if(value == (first_answer + sec_answer)){
        Serial.print("++Success++\n");
        bonus = 3;
        if(first_answer + sec_answer >= 13){
          Serial.print("Smart!!\n");
          score++;
          bonus = 6;
        }
        score++;
        for(int i = 0; i < bonus; i++){
          twinkle_all();
        }
      }
      else{
        Serial.print("Fail\n");
        penalty = 3;
        if(first_answer + sec_answer < 5){
          Serial.print("hmm..\n");
          if(score > 0)
          score--;
          else
           score = 0;
          penalty = 6;
        }
        Serial.print("Answer is ");
        Serial.print(first_answer);
        Serial.print('+');
        Serial.print(sec_answer);
        Serial.print('=');
        Serial.print(first_answer + sec_answer);
        Serial.print('\n');
        if(score > 0)
          score--;
        else
           score = 0;
        for(int i = 0; i < penalty; i++){
          twinkle_red();
        }
      }
    }
    else{
      if(value == (first_answer * sec_answer)){
        Serial.print("**Success**\n");
        bonus = 3;
        if(first_answer * sec_answer >= 49){
          Serial.print("Unbelievable!!\n");
          score += 2;
          bonus = 6;
        }
        score += 2;
        for(int i = 0; i < bonus; i++){
          twinkle_all();
        }
      }
      else{
        Serial.print("Fail\n");
        penalty = 3;
        if(first_answer * sec_answer < 9){
          Serial.print("hmm..\n");
          if(score > 1)
            score -= 2;
          else
           score = 0;
          penalty = 6;
        }
        Serial.print("Answer is ");
        Serial.print(first_answer);
        Serial.print('*');
        Serial.print(sec_answer);
        Serial.print('=');
        Serial.print(first_answer * sec_answer);
        Serial.print('\n');
        if(score > 1)
          score -= 2;
        else
           score = 0;
        for(int i = 0; i < penalty; i++){
          twinkle_red();
        }
      }
    }  
}


void stage2(){

  count_down();

  init_num(2);
  first_answer = show_number();

  choices();

  init_num(2);
  sec_answer = show_number();

    /*
    //웹에서 횟수 확인용임으로 제거 필요
    if(choice == 1){
      Serial.print('\n');
      Serial.print(first_answer);
      Serial.print("\n+\n");
      Serial.print(sec_answer);
      Serial.print('\n');
      Serial.print(first_answer + sec_answer);
      Serial.print('\n');
    }
    else{
      Serial.print('\n');
      Serial.print(first_answer);
      Serial.print("\nx\n");
      Serial.print(sec_answer);
      Serial.print('\n');
      Serial.print(first_answer * sec_answer);
      Serial.print('\n');
    }
      
    Serial.print('\n');
    //여기까지*/


  //정답 입력받는 중
    Serial.print("answering time\n");
    count_down();
    value = Serial.parseInt();

    //선택
    if(choice == 1){
      if(value == (first_answer + sec_answer)){
        Serial.print("++Success++\n");
        bonus = 3;
        if(first_answer + sec_answer >= 16){
          Serial.print("Smart!!\n");
          score += 2;
          bonus = 6;
        }
        score += 2;
        for(int i = 0; i < bonus; i++){
          twinkle_all();
        }
      }
      else{
        Serial.print("Fail\n");
        penalty = 3;
        if(first_answer + sec_answer < 7){
          Serial.print("hmm..\n");
          if(score > 1)
            score -= 2;
          else
           score = 0;
           penalty = 6;
        }
        Serial.print("Answer is ");
        Serial.print(first_answer);
        Serial.print('+');
        Serial.print(sec_answer);
        Serial.print('=');
        Serial.print(first_answer + sec_answer);
        Serial.print('\n');
        if(score > 1)
          score -= 2;
        else
           score = 0;
        for(int i = 0; i < penalty; i++){
          twinkle_red();
        }
      }
    }
    else{
      if(value == (first_answer * sec_answer)){
        Serial.print("**Success**\n");
        bonus = 3;
        if(first_answer * sec_answer >= 90){
          Serial.print("Unbelievable!!\n");
          score += 4;
          bonus = 6;
        }
        score += 4;
        for(int i = 0; i < bonus; i++){
          twinkle_all();
        }
      }
      else{
        Serial.print("Fail\n");
        penalty = 3;
        if(first_answer * sec_answer < 25){
          Serial.print("hmm..\n");
          if(score > 3)
            score -= 4;
          else
           score = 0;
           penalty = 6;
        }
        Serial.print("Answer is ");
        Serial.print(first_answer);
        Serial.print('*');
        Serial.print(sec_answer);
        Serial.print('=');
        Serial.print(first_answer * sec_answer);
        Serial.print('\n');
        if(score > 3)
          score -= 4;
        else
           score = 0;
        for(int i = 0; i < penalty; i++){
          twinkle_red();
        }
      }
    } 
}


void stage3(){

  count_down();

  init_num(3);
  first_answer = show_number();

  choices();

  init_num(3);
  sec_answer = show_number();

    /*
    //웹에서 횟수 확인용임으로 제거 필요
    if(choice == 1){
      Serial.print('\n');
      Serial.print(first_answer);
      Serial.print("\n+\n");
      Serial.print(sec_answer);
      Serial.print('\n');
      Serial.print(first_answer + sec_answer);
      Serial.print('\n');
    }
    else{
      Serial.print('\n');
      Serial.print(first_answer);
      Serial.print("\nx\n");
      Serial.print(sec_answer);
      Serial.print('\n');
      Serial.print(first_answer * sec_answer);
      Serial.print('\n');
    }
      
    Serial.print('\n');
    //여기까지*/


  //정답 입력받는 중
    Serial.print("answering time\n");
    count_down();
    value = Serial.parseInt();

    //선택
    if(choice == 1){
      if(value == (first_answer + sec_answer)){
        Serial.print("++Success++\n");
        bonus = 3;
        if(first_answer + sec_answer >= 20){
          Serial.print("Smart!!\n");
          score += 3;
          bonus = 6;
        }
        score += 3;
        for(int i = 0; i < 3; i++){
          twinkle_all();
        }
      }
      else{
        Serial.print("Fail\n");
        penalty = 3;
        if(first_answer + sec_answer < 10){
          Serial.print("hmm..\n");
          if(score > 2)
            score -= 3;
          else
           score = 0;
           penalty = 6;
        }
        Serial.print("Answer is ");
        Serial.print(first_answer);
        Serial.print('+');
        Serial.print(sec_answer);
        Serial.print('=');
        Serial.print(first_answer + sec_answer);
        Serial.print('\n');
        if(score > 2)
            score -= 3;
        else
           score = 0;
        for(int i = 0; i < penalty; i++){
          twinkle_red();
        }
      }
    }
    else{
      if(value == (first_answer * sec_answer)){
        Serial.print("**Success**\n");
        bonus = 3;
        if(first_answer * sec_answer >= 121){
          Serial.print("Unbelievable!!\n");
          score += 6;
          bonus = 6;
        }
        score += 6;
        for(int i = 0; i < bonus; i++){
          twinkle_all();
        }
      }
      else{
        Serial.print("Fail\n");
        penalty = 3;
        if(first_answer * sec_answer < 25){
          Serial.print("hmm..\n");
          if(score > 5)
            score -= 6;
            else
           score = 0;
           penalty = 6;
        }
        Serial.print("Answer is ");
        Serial.print(first_answer);
        Serial.print('*');
        Serial.print(sec_answer);
        Serial.print('=');
        Serial.print(first_answer * sec_answer);
        Serial.print('\n');
        if(score > 5)
            score -= 6;
        else
           score = 0;
        for(int i = 0; i < penalty; i++){
          twinkle_red();
        }
      }
    } 
}