#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  //library needed for backpack and LCD

/*GND - GND         // LCD I2C backpack
VCC - 5V
SDA - ANALOG Pin 4
SCL - ANALOG pin 5
*/

int photocell = 0;    //analog pin
int redLEDpin = 9;
int yelLEDpin = 8;
int temperature = 1;  //analog pin
int soil = 2;         //analog pin

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

pinMode(photocell,INPUT);
pinMode(temperature,INPUT);
pinMode(soil,INPUT);
pinMode(redLEDpin,OUTPUT);
pinMode(yelLEDpin,OUTPUT);
Serial.begin(9600);             //start serial monitor

lcd.init();                      // initialize the lcd 
lcd.backlight();                // Print a message to the LCD.
}

void loop() {

int tempReading = analogRead(temperature);
float cellRead = analogRead(photocell);
float soilRead = analogRead(soil);
float voltage = tempReading * 5.0;     //converting reading to voltage
voltage /= 1024;
float Celsius = (voltage - 0.5) * 100; // 10mV per degree

Serial.println("Voltage: ");           //print volts to serial monitor
Serial.print(voltage);        
Serial.println("V ");

Serial.println("Temperature: ");       //print temperature to serial monitor
Serial.print(Celsius);
Serial.println(" degrees celsius");

Serial.println("Moisture: ");          //print moisture to serial monitor
Serial.print(soilRead);
Serial.println(" ");

lcd.setCursor(0, 0);                   //celsius to LCD
lcd.print("Temperature: ");
lcd.setCursor(0, 1);
lcd.print(Celsius);      
lcd.print(" degrees C ");
delay(3000);
lcd.clear();

lcd.setCursor(0, 0);                   //photocell to LCD
lcd.print("Light: ");
lcd.setCursor(0, 1);
lcd.print(cellRead);     
delay(3000);
lcd.clear();

lcd.setCursor(0, 0);                   //moisture value to LCD
lcd.print("Moisture: ");
lcd.setCursor(0, 1);
lcd.print(soilRead);
delay(3000);
lcd.clear();


if (cellRead > 550 && Celsius > 21 && soilRead < 800) //LED sequences
{
  digitalWrite(yelLEDpin,HIGH);        // yellow LED if all of the conditions above is true
  digitalWrite(redLEDpin,LOW);
}else
{
  digitalWrite(redLEDpin,HIGH);        // red LED if one of the conditions above is false
  digitalWrite(yelLEDpin,LOW);
}
}



