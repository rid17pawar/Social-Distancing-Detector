// C++ code
/*
*****This system is used to get alert when any moving entity comes closer to you. 
i.e. when distance between you and him is less than 200 
*/


//importing library for LCD
#include<LiquidCrystal.h>

//setting function for LCD 16x2. passing arduino pin nos that are connected as parameters.
LiquidCrystal lcd(A0, A1, 5, 4, 3, 2);

//pins connected to ultrasonic distance sensor
int triggerPin = 7;
int echoPin = 6;
//variables
unsigned long duration;
int distance;
//buzzer pin connected to piezo
int pinBuzzer =13;
//pins connected to red color and green color of LED RGB
int rPin =10;
int gPin =8; 
//pin connected to PIR sensor
int pirPin =12;
//variable
int isHuman =0;



void setup()
{
  //setting pin mode for each of the pins declared above of arduino
  //whether pin is for input or output
  pinMode(triggerPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(pirPin, INPUT);
  //initializing for monitor
  Serial.begin(9600);
  //initializing LCD 16x2
  lcd.begin(16, 2); 
   
}

//we haven't used any function. If functions are used, they must be called within void loop

void loop()
{
  //if PIR pin finds any motion, it will be store in isHuman variable
  isHuman = digitalRead(pirPin);
  Serial.println(isHuman);
  
  if (isHuman ==1){
    //when human is present, calculating distance 
    
	digitalWrite(triggerPin, LOW);
 	delayMicroseconds(2);
    //clearing the trigger
  	digitalWrite(triggerPin, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(triggerPin, LOW);
  
    // capturing the time duration for sound wave to travel in microseconds
  	duration = pulseIn(echoPin, HIGH);
  	distance = 0.01723 * duration; //formula to calculate distance
  	Serial.print(distance); //print distance
  	Serial.println("cm");
    
    if  (isHuman == 1 && distance < 200 ){
    //when distance is less than 200, send a message on LCD 16x2, LED RGB will turn red, buzzer/piezo will sound
  
    //LCD RGB will be red  
    digitalWrite(rPin, HIGH);
    digitalWrite(gPin, LOW);
    
    //piezo/buzzer will sound  
    tone(pinBuzzer,293);
      
    //display message on LCD 16x2  
    lcd.clear();
    lcd.setCursor(0,0);          
  	lcd.print("   STAY!!"); 
  	lcd.setCursor(0,1);           
  	lcd.print("   AWAY!!");
      
    //after 200sec stop buzzer/piezo sound, LCD RGB will be off, LCD 16x2 display will be cleared  
    delay(200);    
    noTone(pinBuzzer);
    digitalWrite(rPin, LOW);
    lcd.clear();     
    
  }
  else {
  	//if human is present, but distance is more than 200
    
    //LCD RGB will glow green
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, HIGH);
    
    //LCD 16x2 will show safe message
    lcd.setCursor(0,0);          
  	lcd.print(" You are safe"); 
  	lcd.setCursor(0,1);           
  	lcd.print("    ");
    
  }
      
 }
    
}