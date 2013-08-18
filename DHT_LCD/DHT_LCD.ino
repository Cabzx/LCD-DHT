/*
** Cab R.DE@IEEE.ORG
** Example for reading DHT11 sensor imput with an LCD screen - SainSmart I2C LCD2004 adapter for HD44780 LCD
** Address pins 0,1 & 2 are all permenantly tied high so the address is fixed at 0x27
** Does not work with DHT22
** LICENSE: GNU General Public License, version 3 (GPL-3.0)
**
** NOTE: TEsted on Arduino Duemilanove whose I2C pins are A4==SDA, A5==SCL
** For more on I2C pins check: http://arduino.cc/en/reference/wire
*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT11PIN 2        //DHT11 signal PIN
#define I2C_ADDR    0x3F  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

DHT DHT11;       //Create a new DHT object named "DHT11"
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); //a new LCD_I2C objecct

void setup()
{
  lcd.begin (20,4); //width then height of LCD screen
  DHT11.setup(DHT11PIN);
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();                   // sets the cursor to top left (0,0)

  lcd.print("DHT11 Sensor Read");  
  lcd.setCursor ( 0, 1 );        // go to the 2nd line
  lcd.print("Sensor Status: ");
  
  lcd.setCursor ( 0, 2 );        // go to the third line
  lcd.print("Temperature(C): ");
  lcd.setCursor ( 0, 3 );        // go to the fourth line
  lcd.print("Humidity(%): ");
}

void loop()
{
 
  lcd.setCursor (15,1);
    switch (DHT11.getStatus())
  {
    case 0:
		lcd.print("OK  "); //Sensor working fine
		break;
    case 2:   //data error, most likely faulty connections
		lcd.print("ChkSm"); 
		break;
    case 1:   //PIN is not connected
		lcd.print("TOUT"); 
		break;
    default: 
		lcd.print("ERROR"); //Unknown! May be damaged sensor.
		break;
  }
  lcd.setCursor (16,2);        // go col 16 of line 2
  lcd.print((float)DHT11.getTemperature(), 1);
  lcd.setCursor (16,3);        // go col 15 of line 3
  lcd.print((float)DHT11.getHumidity(), 1);
  delay(DHT11.getMinimumSamplingPeriod()+10);    //If this is too small you wont read data correctly. (chksm error)
}


