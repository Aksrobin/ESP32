#include <M5StickC.h>

float accX = 0;
float accY = 0;
float accZ = 0;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;
bool predicate = false;
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

float temp = 0;
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(40, 0, 2);
  M5.Lcd.println("RTC TEST");
  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = 1;
  TimeStruct.Minutes = 42;
  TimeStruct.Seconds = 0;
  M5.Rtc.SetTime(&TimeStruct);
  RTC_DateTypeDef DateStruct;
  DateStruct.WeekDay = 3;
  DateStruct.Month = 3;
  DateStruct.Date = 22;
  DateStruct.Year = 2020;
  M5.Rtc.SetData(&DateStruct);
  M5.MPU6886.Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.MPU6886.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.MPU6886.getAccelData(&accX,&accY,&accZ);
  M5.MPU6886.getTempData(&temp);
//&& ((accX*1000 >= -750 && accX*1000 <= -660) && (accY*1000 >= -170 && accY*1000 <= -120) && (accZ*1000 >= 720 && accZ*1000 <= 780))
  if (((gyroX >= -4 && gyroX <=1) && (gyroY >= -5 && gyroY <= -1) && (gyroZ >= -8 && gyroZ <= -4)) ) {
  if ((accX*1000 >= -900 && accX*1000 <= -600) && (accY*1000 >= -120 && accY*1000 <= 10) && (accZ*1000 >= 550 && accZ*1000 <= 950)){
    predicate = true;
  }}


  if(predicate == true){
  M5.Axp.SetLDO2(true);

  M5.Rtc.GetTime(&RTC_TimeStruct);
  M5.Rtc.GetData(&RTC_DateStruct);
  M5.Lcd.setCursor(0, 15);
  M5.Lcd.printf("Data: %04d-%02d-%02d\n",RTC_DateStruct.Year, RTC_DateStruct.Month,RTC_DateStruct.Date);
  M5.Lcd.printf("Week: %d\n",RTC_DateStruct.WeekDay);
  M5.Lcd.printf("Time: %02d : %02d : %02d\n",RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
  delay(500);



  predicate = false;
  delay(2000);
  
  }
  else{
    //delay(300);
    M5.Axp.SetLDO2(false);
    
    }
}
