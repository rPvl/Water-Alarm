//무게센서를 연결한다면 시간마다 값을 저장해서 이전값과 다른지 비교후 부저를 울리거나 시간을 확인하는 작업을 반복.
//관련라이브러리를 다운로드 해야한다.
#include "HX711.h" //HX711로드셀 엠프 관련 함수 호출
#define calibration_factor -7050.0 //로스셀 스케일 값 선언
#define DOUT 3 //엠프 데이터 아웃 핀 넘버 선언
#define CLK 2 //엠프 클락 핀 넘버
HX711 scale(DOUT, CLK); //엠프 핀 선언
float value;//무게 값 저장
void setup(){
  Serial.begin(9600);
  Serial.print("HX711 scale TEST");
  scale.set_scale(calibration_factor); //스케일 지정
  scale.tare(); //스케일 설정
}
void loop(){
  value = 453.592 * scale.get_units(5); //파운드 단위를 g으로 변환, 5회 측정 평균값, 순수한 물이라 가정하여 1g=1ml로 간주.
  Serial.print("Reading: ");
  Serial.print(value); // 무게 출력
  Serial.print(" g"); //단위
}
