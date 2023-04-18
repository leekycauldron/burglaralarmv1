void led(int pin = -1);
void alert_buzz();
bool getMotion();


const int red = 13;   
const int yellow = 12;
const int green = 11;
const int blue = 10;
int sensor = 9;
int buzzer = 8;

         
int state = LOW; // Current sensor state.
int val = 0; // Saved sensor state.
unsigned long last = millis(); // Keeps track of time for strobing lamp during alert.


void setup() {
  Serial.begin(115200);

  // Set pins
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(blue, OUTPUT); 

  pinMode(sensor, INPUT);    


  led(blue);

        
}

void loop(){
  

  switch(state){
    case LOW:
      led(green);
      break;
    case HIGH:
      alert_buzz();
      led(red);
      break;
  }

  
  if (getMotion() && state == LOW) {           
      state = HIGH;      
  } else if (!getMotion() && state == HIGH){      
        state = LOW;       
  }

}