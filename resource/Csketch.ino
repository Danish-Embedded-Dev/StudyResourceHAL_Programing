/* Hello All, I found this open source code which includes all C programming commands
 *  you are likely to use when working with an arduino ( Refrence :  (http://bit.ly/arduinotut)). 
 *  I have added extra comments - I hope this helps! (including reading values from accelorometer)
 *  
 *  This is a global variable meaning it can be accessed by any
 
 Define an integer that will always have the value of 3

Note: This is a constant (Integer Values : -32,768 to 32,767)*/
const int ledPin = 3;
 
void setup() {
  // Opens a serial port and sets how many bits per second
  // 9600 is 960 characters per second
  Serial.begin(9600);
  
  // PinMode: Set to use pin 3 for output
  pinMode(ledPin, OUTPUT);
 
/* ///// FOR LOOP ///////////
 
 A for loop performs an action multiple times

Each time through the loop we decrement i as long as it is > 0
Some other operators you can use : > < >= <=
  for(int i = 3; i > 0; i--){
    Serial.print(i);
    Serial.print(", ");
  }
  Serial.println("GO...\n");
*/

/////// Calling a Function////////

  // Below the function has been called a parameter has been passed
  countDown(5);
 
///// While Loops ////////
/* While Loops will carry on running as long as a condition is true
 *  
 * Local varriables e.g. (int j =3) can be set up within functions.
 * Local varriable can only be accesed within the function. Therefore,
 * The  local variable that can only be accessed in the setup function
 */
  
  int j = 3;
  while(j > 0){
    Serial.print(j);
    Serial.print(", ");
    j--;
  }
  Serial.println("GO...\n");
 
  ////// Add floating point numbers ////////////
  
  Serial.print("3.11111111 + 4.11111111 = ");
 
  // You can define how many decimals to print (in this case 8)
  Serial.println(addFloats(3.11111111, 4.11111111), 8);
 
  
  ///////// Add Doubbles //////////////
  // This section is looking at Adding doubles (Double & Floats are the same)
  
  Serial.print("3.11111111 + 4.11111111 = ");
  Serial.println(addDoubles(3.11111111, 4.11111111), 8);
 
  ////////// Boolean Operators and Ternary operators //////////////
  
  // Booleans have a value of true or false
  bool canVote = true;
 
  // The ternary operator returns the 1st value if the condition 
  // is true and other wise the 2nd
  Serial.print("Can I Vote? ");
  Serial.println(((canVote == true) ? "Yes" : "No"));

  ////////////////// Data Types ////////////////////////////
 
  // chars can hold any of 256 single characters
  // They must be surrounded by ' and you can't add numbers
  char letD = 'D';
  Serial.println(letD);
 
  // Other data types
  // byte : 0 - 255
  // unsigned int : 0 - 65535
  // long : -2,147,483,648 - 2,147,483,647
  // unsigned long : 0 - 4,294,967,295
  
  
}


void loop() {
  // These are local variables
  // The amount of time to delay between actions
  
  // Each time loop executes delayPeriods value would be reset to
  // 100 unless it is marked as static
  // static means to only initialize this variable 1 time
  static int delayPeriod = 100;
 
  // Used to increase/decrease the delayPeriod
  static int countDir = 1;
  
  // Turn pin 13 on
  digitalWrite(ledPin, HIGH);
 
  // Wait 1/10th a second
  delay(delayPeriod);
 
  // Turn pin 13 off
  digitalWrite(ledPin, LOW);
 
  // Wait 1/10th a second
  delay(delayPeriod);
 
  ///// Change direction with a function /////////
  
  countDir = checkDirChange(delayPeriod, countDir);
 
  /*
  // Switches the direction of the increment when limits are hit
  // || means we should execute code if the 1st condition OR the other is true
  // && is true only if both conditions are true
  if((delayPeriod == 1000) || (delayPeriod == 0)) {
    direction *= -1;
 
    // You can use > < >= <= ==, or !=
    if(direction < 0){
      Serial.println("Going Down");
    } else {
      Serial.println("Going Up");
    }
  }
  */
 
// Increase / descrease the delay period depending of current direction
  delayPeriod += 100 * countDir;
  
  // Print to the serial monitor
  Serial.print("New Wait Time : ");
  Serial.println(delayPeriod);
}

///////// Change Direction Function ///////////

//This function receives 2 int parameters and returns 1 int
int checkDirChange(int delayPeriod, int countDir){
  if((delayPeriod == 1000) || (delayPeriod == 0)) {
    countDir *= -1;
 
    if(countDir < 0){
      Serial.println("Going Down");
    } else {
      Serial.println("Going Up");
    }
  }
  return countDir;
}
 
// Receive a parameter and adjust the for loop
// void means this function returns no value
void countDown(int max){
  for(int i = max; i > 0; i--){
    Serial.print(i);
    Serial.print(", ");
  }
  Serial.println("GO...\n");
}
 
/////////////// Float and Doubles Functions ///////

//Adds and returns floats
float addFloats(float num1, float num2){
  return num1 + num2;
}
 
// Add and return a double
double addDoubles(double num1, double num2){
  return num1 + num2;
}
 

 
const int ledPin = 13;
 
////////////////Arrays & Strings ///////////////////////////

// Arrays can contain many values which are accessed using
// their index starting at 0
 
// We'll create an array of numbers that will set how many times
// the LED blinks
int numOfBlinks[] = {1,2,3,4};
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
 
}
 
void loop() {
  
  int delayPeriod = 1000;
 
  // Change a value in the array
  numOfBlinks[0] = 5;
 
  // You can define an array size
  int array2[10];
  
  // You can store a string of characters or a String
  // A string ends with a \0 Null
  char array3[] = "Embedded";
 
  // Strings are normally assigned this way and this is 
  // actually a pointer that points to the first chars address
  // in the char array
  char *str = "Systems";
 
  // You can print the string
  Serial.println(str);
 
  // There is also a String object with many functions
  String myName = "Embedded Systems";
 
  // You can combine strings
  Serial.println("Name : " + myName);
 
  // Get length
  Serial.println(myName.length());
 
  // Check equality (also equalsIgnoreCase())
  Serial.println(myName.equals("Embedded"));
 
  // Get a character at an index
  Serial.println(myName.charAt(6));
 
  // Get index of match
  Serial.println(myName.indexOf('b'));
 
  // Remove starting at index and the number of items to remove
  myName.remove(0, 6);
  Serial.println(myName);
 
  // Replace 1 substring with another
  myName.replace("tem", "s");
  Serial.println(myName);
 
  // Get a substring
  Serial.println(myName.substring(0,3));
 
  // Change to upper and lowercase
  myName.toUpperCase();
  Serial.println(myName);
  myName.toLowerCase();
  Serial.println(myName);
 
  // Convert String to int or float with toFloat()
  String one = "1";
  int num1 = one.toInt();
  int sum = num1 + num1;
  Serial.println(sum);
 
  // Cycle through array
  for(int i = 0; i < 5; i++){
    Serial.print(array3[i]);
  }
 
  // Cycle through each number of blinks in the array
  for(int i = 0; i < 4; i++){
    blinkLED(numOfBlinks[i]);
    delay(delayPeriod);
  }
  
}
 
// Blink lights with a delay a set number of times
void blinkLED(int numOfBlinks){
  for(int j = 0; j < numOfBlinks; j++){
    digitalWrite(ledPin, HIGH);
    delay(400);
    digitalWrite(ledPin, LOW);
    delay(400);
  }
}

 
///////////////////////// Switch Case ///////////////////////////////

void setup() {
  Serial.begin(9600);
  
  // Switch performs different actions based on a limited
  // number of possible values
  char grade = 'Z';
  switch(grade){
    case 'A':
      Serial.println("Great");
      break;
    case 'B':
      Serial.println("Good");
      break;
    case 'C':
      Serial.println("Average");
      break;
    case 'D':
      Serial.println("Bad");
      break;
    case 'F':
      Serial.println("Terrible");
      break;
    default:
      Serial.println("Confused");
      break;
  }
 
  // Print all odds until i == 14 then quit
  int i = 0;
  while(i < 20){
 
    // If odd print (Modulus returns 0 with evens)
    if(i % 2){
      Serial.println(i);
      i++;
 
      // Skips rest of the while loop
      continue;
    } 
    
    if(i == 14){
      // Jump out of while loop
      break;
    }
    i++;
  }
 
  Serial.println(5 + 2);
  Serial.println(5 - 2);
  Serial.println(5 * 2);
  Serial.println(5 / 2);
  Serial.println(5 % 2);
 
  /////////////// Absolute value ///////////////
  Serial.println(fabs(-2));
 
  ///////////////// Min & Max///////////////
  Serial.println(fmin(2.5,3));
  Serial.println(fmax(2.5,3));
  
  ///////////////// Rounding///////////////
  Serial.println(round(2.5));
  Serial.println(floor(2.5));
  Serial.println(ceil(2.5));
 
  ///////////////// Square Root///////////////
  Serial.println(sqrt(25));
 
  ///////////////// Square ///////////////
  Serial.println(square(3));
 
  ///////////////// Power///////////////
  Serial.println(pow(5, 2));
 
  ///////////////// Cube Root///////////////
  Serial.println(cbrt(8));
 
  ///////////////// Logarithm ///////////////
  Serial.println(log(2.718));
  Serial.println(log10(1000));
 
  // Constrain a value between a range
  // If (x, a, b) 
  // Return x if x is between a & b
  // Return a if x < than a
  // Return b if x > than b
  Serial.println(constrain(5, 1, 6));
 
  ///////////////// Trig Functions ///////////////
  Serial.println(sin(1.57));
  Serial.println(cos(1.57));
  Serial.println(tan(3.14));
  Serial.println(sinh(1.57));
  Serial.println(cosh(1.57));
  Serial.println(tanh(1.57));
  Serial.println(asin(1.57));
  Serial.println(acos(1.57));
  Serial.println(atan(1.57));
  
  
  //////////////////////// Generating Random Numbers //////////////////////
  
  // Generate 10 random numbers between 1 to 9
  // Initialize the random number generator with
  // a random seed value using an unconnected pin
  // which has a floating value
  randomSeed(analogRead(0));
  for(int i = 0; i < 10; i++){
    Serial.println(random(1,10));
  }
 
  // Bit Manipulation
  // Their are 8 bits in a byte
  // A bit (Binary Digit) has a value of 0 or 1
  // 1111 = 1*2^3 + 1*2^2 + 1*2^1 + 1*2^0
  // 15 = 8 + 4 + 2 + 1
 
  // Return 1 if both are 1 with &
  int bin1 = 0b10101010; // 170
  int bin2 = 0b11111111; // 255
  Serial.println(bin1 & bin2); // 170
 
  // Return 1 if either are 1
  Serial.println(bin1 | bin2); // 255
 
  // XOR returns 1 only if one is 1 and other is 0
  Serial.println(bin1 ^ bin2); // 85
 
  // Bitwise not converts each to its opposite
  Serial.println(~0b0111); // -8 because highest bit 
  // (sign bit) was changed to 1 making it negative
 
  // Shift bits right
  Serial.println(bin2 >> 2); // 00111111 = 63
 
  // Shift bits left
  Serial.println(bin2 << 2); // 1111111100 = 1020
 
  // Structs allow you to create custom data types
  struct RGB{
    byte red;
    byte green;
    byte blue;
  };
 
  RGB color = {0,255,0};
  if(color.red == 0 && color.green == 255 && color.blue == 0){
    Serial.println("It's Green");
  }
 
  // sprintf creates formatted strings
  printTime(1, 12);
 
  // Pointers
  // A pointer refers to a memory location of a variable
 
  // Create a pointer for an int
  int *ptr;
  int val1 = 15;
 
  // Store the memory location in a pointer
  ptr = &val1;
 
  // Print the value pointed at
  Serial.println(*ptr);
 
  // An array is a pointer
  int primes[] = {2,3,5,7};
 
  // Print the 1st index
  Serial.println(*primes);
 
  // Print the 2nd index
  Serial.println(*primes + 1);
 
  // Pass an array to a function
  printArray(primes, 4);
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
}
 
void printTime(int hour, int minute){
  // Will store the time in a char array
  char buffer[6] = "";
 
  // ints with a : between 02 guarantees 2 digits show
  sprintf(buffer, "%02d:%02d", hour, minute);
  Serial.println(buffer);
}
 
// Prints out the array
void printArray(int arr[], int size){
  for(int i = 0; i < size; i++){
    Serial.println(arr[i]);
  }
}
 
///////////////// Read values from accelrometer //////////////
//      Serial.print("AcX = "); Serial.println(AcX);
    //      Serial.print("AcY = "); Serial.println(AcY);
    //      Serial.print("AcZ = "); Serial.println(AcZ); Serial.println();
    //      delay(1500);
    //      return;
