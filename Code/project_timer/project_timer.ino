//I2C
//I2C 통신 라이브러리
#include <Wire.h>
//I2C LCD 라이브러리
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32,16,2);//0x27

//4*4 키패드
//열의 수 설정
const int numRows = 4;
//행의 수 설정
const int numCols = 4;

//열과 행에 대하여 문자를 할당
char keys[numRows][numCols]={
  {'Z','W','t','w'},//Z is zeor(무게 영점), W is weight(물이든 컵의 무게), t is timer, w is water(마신 물의 양)
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','+','-','R'}//R is reset
};

int rowPins[] = {3,4,5,6};
int colPins[] = {7,8,10,11};

//부저 설정
int buzzerPin=9;
int songLength=24;
char notes[]="dbagd dbage eCbaf DDCabg";
int beats[]={1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1};
int tempo=150;

long old_time=0;
long time_atack=0;
bool check=false;

void setup(){
//열을 입력 풀업 모드로 설정한다.
  for(int i=0;i<numRows;i++)
    pinMode(rowPins[i], INPUT_PULLUP);

//행을 출력모드로 설정한다. 초기값을 HIGH로 설정
  for(int i=0;i<numCols;i++){
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
//부저 설정
  pinMode(buzzerPin,OUTPUT);
  
  Serial.begin(9600);
  
  lcd.begin(16,2);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Arduino LCD");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Timer Set: ");//11

  lcd.setCursor(0,1);
  lcd.print("Run Time: ");//10
}

void loop(){
//key 변수에 키패드 입력 값을 읽어서 저장한다.
  char key = keypadRead();
  
  //key 변수가 0일때는 입력이 없는 것이고 
  //그 외의 값에서는 입력이 발생한것이다.
  if(key!=0){
    Serial.print("You push ");
    Serial.print(key);
    Serial.println(" key");
    if(key=='t'){
      lcd.setCursor(0,0);
      lcd.print("Timer Set:                ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='w'){
      lcd.setCursor(0,0);
      lcd.print("Drink water:              ");
    }
    if(key=='1'){
      old_time=millis();//1sec = 1000millis
      time_atack=10;//10분. 분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='2'){
      //for test
      old_time=millis();
      time_atack=20;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='3'){
      //for test
      old_time=millis();
      time_atack=30;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='4'){
      old_time=millis();
      time_atack=40;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='5'){
      old_time=millis();
      time_atack=50;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='6'){
      old_time=millis();
      time_atack=60;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='7'){
      old_time=millis();
      time_atack=70;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='8'){
      old_time=millis();
      time_atack=80;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='9'){
      old_time=millis();
      time_atack=90;//분단위
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='+'){
      time_atack+=1;//분단위
      old_time=millis();
      check=true;
      lcd.setCursor(10,0);
      lcd.print("          ");
      lcd.setCursor(10,0);
      lcd.print(time_atack);
    }
    if(key=='-'){
      if(time_atack-1!=0){
        time_atack-=1;//분단위
        old_time=millis();
        check=true;
        lcd.setCursor(10,0);
        lcd.print("          ");
        lcd.setCursor(10,0);
        lcd.print(time_atack);
      }
    }
    if(key=='R'){//리셋
      lcd.clear();
      lcd.print('Rest');
      delay(1000);
      resetFunc();
    }
    if(key=='Z'){//컵 무게 재기
      Serial.println("컵 무게 재기");
    }
    if(key=='W'){//물이든 컵 무게 재기
      Serial.println("물이든 컵 무게 재기");
    }
  }
  
  if(check==true){
    lcd.setCursor(10,1);
    lcd.print((millis()-old_time)/60000);//분 단위
  }
  
  if((millis()-old_time)/60000>=time_atack && check==true){//시간되면 buzzer 울림
    Serial.print(time_atack);
    Serial.println("minute");
    buzzer();
    old_time=millis();
  }
}
char keypadRead(){
  char key =0;
  for(int i=0;i<numCols;i++){
    digitalWrite(colPins[i],LOW);
    for(int j=0;j<numRows;j++){
      if(digitalRead(rowPins[j])==LOW){
        delay(10);//바운싱 방지
        while(digitalRead(rowPins[j])==LOW);//키 놓을 때 까지 기다림.
        key = keys[j][i];
      }
    }
    digitalWrite(colPins[i],HIGH);//LOW 설정했던 행을 다시 HIGH로
  }
  return key;
}

void buzzer(){
  Serial.println("buzzer function");
  int duration;
  for(int i=0;i<songLength;i++){
    duration=beats[i]*tempo;
    if(notes[i]==' '){
      delay(duration);
      }
    else{
      tone(buzzerPin,frequency(notes[i]),duration);
      delay(duration);
      }
      delay(tempo/10);
    }
}
int frequency(char note){
  int i;
  int notes=10;//8
  char names[]={'c','d','x','e','f','g','a','b','C','D'};//x is d#, D is D#
  int frequencies[]={262,294,312,330,349,392,440,494,523,588};
  for(i=0;i<notes;i++){
    if(names[i]==note) return(frequencies[i]);
    }  
    return(0);
  }

//SW 리셋
void resetFunc(){asm volatile("jmp 0");}
