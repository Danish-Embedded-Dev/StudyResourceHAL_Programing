# StudyResourceHAL_Programing
Improve your coding skill with HAL based structural programing 

Summative Coursework 

# Phase 1: Traffic Lights
Look at Example 2 from Week 7 lab notes. This shows you how you can create a bare-metal lights sequencer with four states and varying times. It will not take much effort to use the concepts here to extend this from four states to nine states, adjusting the light patterns and timings for each state, for a full traffic lights sequencer.

# Phase 2: Debouncers
The sample code from Week 8 shows you how you can debounce a single switch SW1 (on Pin A0). Modify this code for bare metal (Example 1 from Week 7 shows you how to read this particular switch using bare metal).

Add the module 1 code from this example into your main code (from Phase 1). Copy the code from setup() in this example to the setup() in the main code. Similarly copy the code from loop() in the example to the loop() function in the main code. Copy across the global variables. Also copy across the test code from the bottom of the example code. You should now have the traffic lights and a single debouncer running together.

Now create a second debouncer (call this module 2) based on module 1 - use SW2 on pin A1 and have a new variable called B2_state - this should be a careful copy-paste exercise with a handful of small modifications. Duplicate the test code for SW2. At this point you should have the traffic lights and both debouncers working concurrently.

# Phase 3: Heartbeat
Look at the example from Week 4 lecture. There are examples of code with 2-state FSMs capable of blinking LEDs on and off. Use one of these modules as a template for the heartbeat. Create a global byte variable to store the state of the heartbeat. Instead of switching an LED on or off, simply set or clear the Most Significant Bit of this variable.

From the Formative Assignment you should have written a function capable of driving a 7-segment display from the shift register. You should already have HAL code to drive the DATA, CLOCK and LATCH pins high and low. Firstly convert these HAL functions to bare metal - please see Example 1 from Week 7 lab notes - as a massive hint, the LED_ON / LED_OFF macros can be used directly for LATCH_HI / LATCH_LO (due to the mapping of the LATCH line).   

The last line of the loop() function should be a call to your shift register function - using your heartbeat variable as its parameter. 

# Phase 4: Button Counter
Using guidance from section 5 from Week 8 lab notes, implement the button counter. Declare a second global byte variable to store the state of a character. Instead of writing the count directly to the shift register, write it to this global variable.

Instead of writing the heartbeat variable to the shift register (in the last line of the loop() function), write the bitwise-OR combination of both variables to the shift register.

# Phase 5: Scheduler - Part 1
Without the scheduler, the traffic lights and button counter will run concurrently (Mode 4). You should be able to use what you have to create a scheduler to implement Mode 1 (traffic lights only), Mode 2 (button counter only) and Mode 4 (traffic lights and button counter). Use SW2 to change between modes.

# Phase 6: Orientation Code
Create a new code module within your loop() function. Instead of a finite state machine in the "Do Step", simply have code to read the accelerometer, determine the orientation, and write the orientation value to your global variable that stores the state of the character (the one used for the button counter). You should be able to use the bulk of the code from Formative Assignment Part 3 for this.

# Phase 7: Scheduler - Part 2
Extend your scheduler to implement Mode 3 (Accelerometer only) and Mode 5 (Traffic Lights and Accelerometer)

At this stage, the bulk of the functionality will be completed. If you go beyond this stage, BACK UP YOUR WORK then work off any back-ups. If anything goes wrong beyond this point, you have something to fall back on.

Further Work - if you have time
Priority switching: in mode 5, use the value of the orientation to change the green time settings in states 3 and 7 of the traffic lights sequencer.
Try to use some form of encapsulation to modularize your code. The Concurrent.h and Concurrent.cpp files provided in the example code from Lecture 6 make a good start point.
 
# Hint: 
especially for inexperienced coders. When writing code write a few lines of code at a time then hit "Compile". You should then be able to easily eliminate any compilation errors (such as typos, undeclared variables, missing semicolons, etc) from the code you have just written. The compiler will highlight the line it is not happy with, along with an error message towards the bottom of the IDE. The error message generally gives a very good clue to what the compilation error is. You may possibly need to look at the line above (or below) the highlighted line of code. Try to avoid writing hundreds of lines of code in one go, hitting "Compile", and expecting to compile first time - you could give yourself a headache!
 
