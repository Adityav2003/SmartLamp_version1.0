#include<Arduino.h>
char Incoming_value = 0;
const int fadeDelay = 10; // Delay between each color step
const int maxBrightness = 255; // Maximum brightness level
class colorCode{

 public:
    int red;
    int green; 
    int blue;

    colorCode(int r,int g,int b){
        red = r;
        green = g;
        blue = b;
    }

};
int redPin = 7;
int greenPin = 6;
int bluePin =5;

  colorCode rd(255,0,0);   //a
  colorCode yl(255,255,0);  //b
  colorCode orn(255,40,0);  //c
  colorCode gr(0,255,0);    //d
  colorCode yg(160,255,30);   //e
  colorCode vi(128,0,128);    //f
  colorCode aq(0,255,255);    //g
  colorCode wh(255,255,255);   //h
  colorCode bl(0,0,255);       //i
  colorCode mn(215,0,80);
  colorCode black(0,0,0);
 

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void fadeRGB(colorCode c) {
  int targetRed = c.red;
  int targetGreen = c.green;
  int targetBlue = c.blue;
    int currentRed = 0;
    int currentGreen = 0;
    int currentBlue = 0;

    // Fade up to the target color
    while (currentRed < targetRed || currentGreen < targetGreen || currentBlue < targetBlue) {
        if (currentRed < targetRed) {
            currentRed++;
        }
        if (currentGreen < targetGreen) {
            currentGreen++;
        }
        if (currentBlue < targetBlue) {
            currentBlue++;
        }
        analogWrite(redPin, currentRed);
        analogWrite(greenPin, currentGreen);
        analogWrite(bluePin, currentBlue);
        delay(fadeDelay);
    }

    // Fade down to off
    while (currentRed > 0 || currentGreen > 0 || currentBlue > 0) {
        if (currentRed > 0) {
            currentRed--;
        }
        if (currentGreen > 0) {
            currentGreen--;
        }
        if (currentBlue > 0) {
            currentBlue--;
        }
        analogWrite(redPin, currentRed);
        analogWrite(greenPin, currentGreen);
        analogWrite(bluePin, currentBlue);
        delay(fadeDelay);
    }
}

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop()
{
   if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == 'a')             
      setColor(rd); 
    else if(Incoming_value == 'b')             
      setColor(yl);
    if(Incoming_value == 'c')             
      setColor(orn);
    if(Incoming_value == 'd')             
      setColor(gr);
    if(Incoming_value == 'e')             
      setColor(yg);
    if(Incoming_value == 'f')             
      setColor(vi);
    if(Incoming_value == 'g')             
      setColor(aq);
    if(Incoming_value == 'h')             
      setColor(wh);
    if(Incoming_value == 'i')             
      setColor(bl);
    if(Incoming_value == 'j')             
      setColor(mn);
    if(Incoming_value == 'k')             
      party();
    if(Incoming_value == 'l')             
      night();
    else if(Incoming_value == '0')       
      setColor(black);   
  } 

  
}

void setColor(colorCode c)
{
  int r = c.red;
  int g = c.green;
  int b = c.blue;

  #ifdef COMMON_ANODE
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  #endif
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);  
}

void lightUp(int r,int g,int b)
{
  
  #ifdef COMMON_ANODE
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  #endif
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);  
}


void party() {
    for (int hue = 0; hue < 255; hue++) {
        // Convert hue value to RGB color
        int red = rainbowColor(hue + 0);
        int green = rainbowColor(hue + 85);
        int blue = rainbowColor(hue + 170);

        // Set the RGB LED to the calculated color
        analogWrite(redPin, red);
        analogWrite(greenPin, green);
        analogWrite(bluePin, blue);

        delay(fadeDelay);
    }

    // Fade out the RGB LED
    for (int brightness = maxBrightness; brightness > 0; brightness--) {
        analogWrite(redPin, brightness);
        analogWrite(greenPin, brightness);
        analogWrite(bluePin, brightness);

        delay(fadeDelay);
    }
}

int rainbowColor(int hue) {
    int phase = hue / 60;
    int remainder = hue % 60;
    int brightness = maxBrightness;
    if (phase % 2 == 0) {
        // Rising part of the color spectrum
        brightness = map(remainder, 0, 59, 0, maxBrightness);
    } else {
        // Falling part of the color spectrum
        brightness = map(remainder, 0, 59, maxBrightness, 0);
    }
    return brightness;
}

void night(){
  for(int i = 0 ; i <= 255 ; i++){
        lightUp(0,0,i);
        delay(50);
  }
  delay(1000);
  for(int i = 255 ; i >= 0 ; i--){
        lightUp(0,0,i);
        delay(50);
 }
 delay(1000); // blue
   for(int i = 0 ; i <= 255 ; i++){
        lightUp(0,i,0);
        delay(50);
  }
  delay(1000);
  for(int i = 255 ; i >= 0 ; i--){
        lightUp(0,i,0);
        delay(50);
 }
 delay(1000); // green
  for(int i = 0 ; i <= 255 ; i++){
        lightUp(0,i,i);
        delay(50);
  }
  delay(1000);
  for(int i = 255 ; i >= 0 ; i--){
        lightUp(0,i,i);
        delay(50);
 }
 delay(1000); // aqua
}