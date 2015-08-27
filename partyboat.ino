#include <Servo.h> 
Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
 
int pos = 90;    // variable to store the servo position 

int speakerPin = 12;
int lightsPin = 13;

//int length = 
15; // the number of notes
int length = 89;
//char notes[] = "ccggaagffeeddc "; // a space represents a rest
char notes[] = "e e e e e e e e e e a a a a a a a c c c c c c c g e e e e e e e e e e e e a e e e e e a";
//int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int beats[] = { 2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1 };
//int tempo = 100;
int tempo = 25;
int ledState = LOW;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(lightsPin, OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {  
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  if (sensorValue > 100) {
    int i;
    for (i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW)
          ledState = HIGH;
        else
          ledState = LOW;
        digitalWrite(lightsPin, ledState);
        playNote(notes[i], beats[i] * tempo);
        pos *= -1;
        myservo.write(pos + 90);
      }
  
      // pause between notes
      delay(tempo / 2); 
    }
    i = 0;
  }
}

