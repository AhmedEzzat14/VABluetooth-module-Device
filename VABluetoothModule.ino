#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define analogInput A0
#define pb 13

SoftwareSerial HC06(0,1); //Define RX and TX pins

int a,b,c;
long volt,current;
float Vout = 0.00;
float Vin = 0.00;
float R1 = 10000.00;           // R1 10K
float R2 = 1000.00;           //R2 1K
int val = 0;
const float Max_current = 5.00; //Amps
const int rs=12 , e=11 , d4=5 , d5=4 , d6=3 , d7=2;
LiquidCrystal lcd(rs,e,d4,d5,d6,d7);

void setup() 
{
  Serial.begin(9600);          //Baud rate
  HC06.begin(9600);           // Initialize software serial communication with HC-06 module
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  pinMode(pb,INPUT_PULLUP);
  pinMode(analogInput,INPUT); //Assigning the input port
}

void loop()
{  
  if (digitalRead(pb)==LOW)
  {
    val = analogRead(analogInput);
    Vout = (val*5.00)/1023;  //formula for calculating voltage output 
    Vin = Vout*((R2+R1)/R2); //formula for calculating voltage input
    if(Vin<0.09)
    {
      Vin = 0.00;            //statement to remove undesired reading
    } 
    Serial.print("Voltage by the source = ");
    Serial.println(Vin);
    delay(1000);             //for maintaining the speed of the output in serial monitor
    lcd.setCursor(0,0);
    lcd.print("Voltage: ");
    lcd.setCursor(0,1);
    lcd.println(Vin);
  }

  else if(digitalRead(pb)==HIGH)
  {
    
  // Read the voltage from the ACS712 current sensor module
  float voltage = analogRead(A0);

  // Convert the voltage to current
  float current = (voltage / 1023.0) * Max_current;


  Serial.print("Current by the source = ");
  Serial.println(current);
  delay(1000);             //for maintaining the speed of the output in serial monitor
  lcd.setCursor(0,0);
  lcd.print("Current: ");
  lcd.setCursor(0,1);
  lcd.println(current);

  }
  
  
}

