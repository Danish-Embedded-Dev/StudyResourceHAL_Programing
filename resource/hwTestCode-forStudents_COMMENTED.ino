// Adding Wire library for use with Gyroscope. See https://www.arduino.cc/en/Reference/Wire
#include <Wire.h>

// #define is a MACRO. Word 1 is replaced with Word 2
// D
#define OFF LOW // E.g. OFF is replaced with LOW
#define ON HIGH

#define MPU_addr 0x68  // I2C address of the MPU-6050
#define LATCH A3 // storage register LATCH // THIS DEPENDS ON HARDWARE SETUP 
#define DATA 8 // data in // AGAIN DEPENDS ON HARDWARE SETUP. 8 = D8.
#define CLOCK 12 // shift register clock

// Macros for seven segement display STATES
#define LED_OFF ((unsigned char) (0))
#define LED_b ((unsigned char) (4+8+16+32+64)) //128
#define LED_F ((unsigned char) (1+16+32+64)) // 113
#define LED_t ((unsigned char) (8+16+32+64)) //120
#define LED_L ((unsigned char) (8+16+32)) //54
#define LED_U ((unsigned char) (1+2+4+16+32)) //55
#define LED_r ((unsigned char) (8+16)) // 24
#define LED_l ((unsigned char) (1+32)) //33 ** 

// Defining where the digital / analog pin are on the adruino
// macros for buttons - Value 2 depends on hardware setup
#define SW1 A0 //button pin
#define SW2 A1 //button pin
#define SW3 A2 //button pin

// macros for tri led
#define TRI_R 9 // rgb red pin (pwm)
#define TRI_B 10 // rgb blue pin (pwm)
#define TRI_G 11 // rgb green pin (pwm)

// macros for leds
#define RED_1 2 // Define red 1 pin
#define YELLOW_1 3 // Define Yellow 1 pin
#define GREEN_1 4 // Define Green 1 pin
#define RED_2 5 // Define red 2 pin
#define YELLOW_2 6 // Define Yellow  2 pin
#define GREEN_2 7 // Define Green 2 pin

// unsgined char = positive only 
// ledState is a variable that stores the current state of the 7 segment display
unsigned char ledState; // state of the 7 segment display

// int16_t is a variable of size 16 bit (2 byte) 
int16_t AcX; // accelerometer variables for X-orientation
int16_t AcY; // accelerometer variables for Y-orientation
int16_t AcZ; // accelerometer variables for Z-orientation

/* Every arduino program has a setup and loop functions.
 *  setup does not have to be implemented but probably should be to setup
 *  the arduino and other connected device how you want it.
 *  
 *  setup is only run once at the beginning of the program
*/
void setup() {
  // Setup Serial Monitor
  Serial.begin(9600); // for debugging. sets up serial monitor. see Tools -> Serial Monitor or CTRL-SHFT-M. Make sure numbers on serial monitor and number here (9600) match.
  Serial.println("Beginning Program");

  // shift register code
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  // switches PULLUP is so there is a sort of resistance
  pinMode(SW1, INPUT_PULLUP); // 
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);

  // Tri LED
  pinMode(TRI_R, OUTPUT); // Tri LED Red as an output
  digitalWrite(TRI_R, LOW); // off it
  pinMode(TRI_B, OUTPUT); // Tri LED Blue as an output
  digitalWrite(TRI_B, LOW); // off it
  pinMode(TRI_G, OUTPUT); // Tri LED Green as an output
  digitalWrite(TRI_G, LOW); // off it

  // LEDs
  pinMode(RED_1, OUTPUT); // first  Red LED as an output
  digitalWrite(RED_1, OFF); // off it
  pinMode(YELLOW_1, OUTPUT); //first  Yellow LED as an output
  digitalWrite(YELLOW_1, OFF); // off it
  pinMode(GREEN_1, OUTPUT); //first  Green LED as an output
  digitalWrite(GREEN_1, OFF); // off it
  pinMode(RED_2, OUTPUT); // Second  Red LED as an output
  digitalWrite(RED_2, OFF); // off it
  pinMode(YELLOW_2, OUTPUT);// Second  Yellow LED as an output
  digitalWrite(YELLOW_2, OFF); // off it
  pinMode(GREEN_2, OUTPUT); // Second  Green LED as an output
  digitalWrite(GREEN_2, OFF); // off it
  ledState = LED_OFF;

  
  ///////// MPU Setup ////////////
  // wire library: https://www.arduino.cc/en/reference/wire
  Wire.begin(); // Initiate the Wire library and join the I2C bus as a master or slave.
  Wire.beginTransmission(MPU_addr);// Start communication with the MPU (Begin a transmission to the I2C slave device with the given address)
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}


void loop() {
  // Reading the switch
  // If switch 1 is pressed - Turn LED set 1 on and off
  while (!digitalRead(SW1)) {
    // Turn LED set 1 on
    digitalWrite(RED_1, ON); /// Turn Red LED ON
    digitalWrite(YELLOW_1, ON); /// Turn Yellow LED ON
    digitalWrite(GREEN_1, ON); /// Turn Green LED ON
    delay(1000);  /// Delay 1 seconds
    // Turn LED set 1 off
    digitalWrite(RED_1, OFF); /// Turn Red LED OFF
    digitalWrite(YELLOW_1, OFF); /// Turn Yellow LED OFF
    digitalWrite(GREEN_1, OFF); /// Turn Red LED ON
    delay(1000); /// Delay 1 seconds
  }

  // If switch 2 is pressed - Toggle through TRI LED
  while (!digitalRead(SW2)) { 
    digitalWrite(TRI_R, HIGH); /// Turn TRI RED On
    delay(3000); // Delay for 3 seconds
    digitalWrite(TRI_R, LOW); /// Turn TRI RED Off
    delay(500);// Delay for 0.5 sec
    digitalWrite(TRI_G, HIGH); // Turn TRI Green On
    delay(2000); // Delay for 2 seconds
    digitalWrite(TRI_G, LOW); // Turn TRI Green OFF
    delay(500); // Delay for 0.5 sec
    digitalWrite(TRI_B, HIGH); /// Turn TRI BLUE ON
    delay(1000); // Delay for a second
    digitalWrite(TRI_B, LOW); // Turn TRI BLUE OFF
    delay(500); // Delay for 0.5 sec
  }

  // If switch 3 is pressed - Turn LED set 2 on and off
  while (!digitalRead(SW3)) {
    digitalWrite(RED_2, ON); /// Turn RED LED On
    digitalWrite(YELLOW_2, ON); ///Turn Yellow LED On
    digitalWrite(GREEN_2, ON); /// Turn GREEN LED On
    delay(1000); /// Delay a second
    digitalWrite(RED_2, OFF); //  Turn RED LED OFF
    digitalWrite(YELLOW_2, OFF); // Turn Yellow LED OFF
    digitalWrite(GREEN_2, OFF); /// Turn Green LED OFF
    delay(1000); /// Delay for a second
  }

  ////////   MPU ////////
  // visit https://playground.arduino.cc/Main/MPU-6050/ //(To understand 
  {
    static unsigned char module3_i = 0; // state of mpu module
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 6, true); // request a total of 6 registers //https://www.arduino.cc/en/Reference/WireRequestFrom
    AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)// Show word document
    AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

    // Debugging only - printing raw values to serial monitor
    //      Serial.print("AcX = "); Serial.println(AcX);
    //      Serial.print("AcY = "); Serial.println(AcY);
    //      Serial.print("AcZ = "); Serial.println(AcZ); Serial.println();
    //      delay(1500);
    //      return;

    // Tanvir code based on MPU values
    // Check if in portrait right
    if (AcX > 25000 && abs(AcZ) < 10000)
      module3_i = 1;
            
    // Check if in portrait left
    if (AcX < 25000 && abs(AcZ) < 10000 && abs(AcY) < 10000)
      module3_i = 0;
            
    // Check if in flat face down
    if (AcZ < -15000)
      module3_i = 2;
            
    // Check if in flat face up
    if (AcZ > 10000)
      module3_i = 3;
            
    // Check if in landscape
    if (AcY > 10000)
      module3_i = 4;
            
    // Check if in landscape upside down
    if (AcY < -10000)
      module3_i = 5;
      
    //  Jordans Code
//    if (abs(AcZ) > 1.75 * abs(AcX) && abs(AcZ) > 1.75 * abs(AcY)) {
//      if (AcZ < 0) module3_i = 0;
//      else module3_i = 1;
//    }
//    if (abs(AcX) > 1.75 * abs(AcZ) && abs(AcX) > 1.75 * abs(AcY)) {
//      if (AcX < 0) module3_i = 2;
//      else module3_i = 3;
//    }
//    if (abs(AcY) > 1.75 * abs(AcX) && abs(AcY) > 1.75 * abs(AcZ)) {
//      if (AcY < 0) module3_i = 4;
//      else module3_i = 5;
//    }

    //unsigned char msb = 0b10000000 & ledState;
    Serial.print("module3_i = "); Serial.println(module3_i);
    Serial.println(); delay(2000);
    switch (module3_i) {
      case 0: ledState = 0b10000000 | LED_r; break; // portrate right
      case 1: ledState = 0b10000000 | LED_l; break; // portrate left
      case 2: ledState = 0b10000000 | LED_b; break; // flat face down
      case 3: ledState = 0b00000000 | LED_F; break; // flat face up
      case 4: ledState = 0b00000000 | LED_L; break; // landscape
      case 5: ledState = 0b00000000 | LED_U; break; // landscape upside down
      default: module3_i = 0; ledState = LED_OFF;
    }

  }

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, ledState);
  digitalWrite(LATCH, HIGH);
}
