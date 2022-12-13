
// These definitions would belong in the HAL module.
// These can easily be converted to bare metal
#define HAL_BUTTON1         A0    //button pin
#define HAL_SW1_RELEASED    digitalRead(HAL_BUTTON1)
#define HAL_SW1_PRESSED     !HAL_SW1_RELEASED
#define HAL_SETUP_SW1       pinMode(HAL_BUTTON1, INPUT_PULLUP)


//module1 variables    
bool init_module1_clock;

//button states
typedef enum
{
  NOT_PRESSED,
  PARTIAL_PRESS,
  DEBOUNCED_PRESS
} switch_state_t;


#define debounce  500         // debounce duration

switch_state_t    B1_state;   // buttons state variables


void setup() {
  HAL_SETUP_SW1;
  init_module1_clock=true;
  Serial.begin(9600);
}

void loop() {


  { // module 1
    static unsigned long module_time, module_delay;
    static unsigned long debounce_count;
    static bool module_doStep;
    static switch_state_t state; // state variable for module 0
    
    if (init_module1_clock) {
      module_delay = 15;
      module_time=millis();
      module_doStep=false;
      init_module1_clock=false;
      state = NOT_PRESSED;
    }
    else {
      unsigned long m=millis();
      if ( ( (long)(m - module_time) ) > module_delay ) {
        module_time = m; module_doStep = true;
      }
      else module_doStep = false;
    }

    if (module_doStep) {
      switch(state){
          case NOT_PRESSED: 
            if (HAL_SW1_RELEASED) state = NOT_PRESSED;
            else {
              debounce_count = millis();
              state = PARTIAL_PRESS;
            }
            break;
          case PARTIAL_PRESS: 
            if (HAL_SW1_RELEASED) state = NOT_PRESSED;
            else if ((millis()-debounce_count) < debounce) state = PARTIAL_PRESS;
            else state = DEBOUNCED_PRESS;
            break;
          case DEBOUNCED_PRESS: 
            if (HAL_SW1_RELEASED) state = NOT_PRESSED;
            else state = DEBOUNCED_PRESS;
            break;
          
          default: 
            state = NOT_PRESSED; 
            break;
      }  
      B1_state = state;
    }
  }
    
  {
    static switch_state_t   old;
    if (old != B1_state)
    {
      old = B1_state;
      switch(old)
      {
      case DEBOUNCED_PRESS:
        Serial.println("B1 = debounced");
        break;
      case PARTIAL_PRESS:
        Serial.println("B1 = de-bouncing");
        break;
      default:
        Serial.println("B1 = not pressed");
      }
    }
  }

}
