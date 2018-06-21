#include "notes.h"
// Which pin the buzzer is attached to
int buzzerPin = 5;
int delayTime = 500;

const int C1 = 2093;
const int C = 1046;

//RGB Light
int redLed = 11;
int greenLed = 9;
int blueLed = 10;

//Light Sensor
int sensorPin = A2;
int lightValue;

// Pin del motor
int motorPin = 6;

//Game Logics
int lives = 3;
boolean alive = true;

//TONES
const int gameover[] = {15,                                               // Array for Game over song
  NOTE_C4, 8, NOTE_H, 8, NOTE_H, 8, NOTE_G3, 8, NOTE_H, 4, NOTE_E3, 4, NOTE_A3, 6, NOTE_B3, 6, NOTE_A3, 6, NOTE_GS3, 6, NOTE_AS3, 6, 
  NOTE_GS3, 6, NOTE_G3, 8, NOTE_F3, 8, NOTE_G3, 4};

//SETUP---------------------------------------------------------------
void setup() {

  // Which pin the buzzer is attached to
  //int buzzerPin = 7;

  //RGB Light
  int analogColor(int redValue, int greenValue, int blueValue);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  //Light Sensor
  pinMode(sensorPin, INPUT);

  //Vibration Motor
  pinMode(motorPin, OUTPUT); // output interface defines vibration sensor

  //-----------------------------------------------------
  //GAME

//LE MIERDER
tone(buzzerPin,660,100);
delay(150);
tone(buzzerPin,660,100);
delay(300);
tone(buzzerPin,660,100);
delay(300);
tone(buzzerPin,510,100);
delay(100);
tone(buzzerPin,660,100);
delay(300);
tone(buzzerPin,770,100);
delay(550);
tone(buzzerPin,380,100);
delay(575);
  noTone(buzzerPin);
  //Set RGB Green
  analogColor(0, 255, 20);

}
//--------------------------------------------------------

void loop() {
  // Get the current light level
  lightValue = analogRead(sensorPin);

  if (alive == true) {
    isHit();
    checkLives();
  } else {
    //Do NOTHING
  }

}



//RGB METHODS
int analogColor(int redValue, int greenValue, int blueValue) {
  int redConverted = 255 - redValue;
  int greenConverted = 255 - greenValue;
  int blueConverted = 255 - blueValue;
  analogWrite(redLed, redConverted);
  analogWrite(greenLed, greenConverted);
  analogWrite(blueLed, blueConverted);
}

//Check how many lives and change Color
void checkLives() {
  if (lives == 3) {
    analogColor(0, 250, 0);
  }
  if (lives == 2) {
    analogColor(255, 0, 180);
  }
  if (lives == 1) {
    analogColor(255, 140, 0);
  }
  if (lives <= 0) {
    analogColor(255, 0, 0);
    alive = false;

    //----------------------------------
    // ASÍ SONARÁ CUANDO MUERA
      for (int thisNote = 1; thisNote < (gameover[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
      tone(buzzerPin, gameover[thisNote], (1000/gameover[thisNote + 1]));// Play the single note
      delay((1000/gameover[thisNote + 1]) * 1.30);                        // Delay for the specified time
      noTone(buzzerPin);                                                 // Silence the note that was playing
    }
  }
}

void isHit() {
  //SI EL VALOR DE LUZ ES MAYOR A 700, SE RESTA UNA VIDA
  if (lightValue >= 700) {
    lives--;
    tone(buzzerPin, C);// SUENA EL BUZZER
    digitalWrite(motorPin, HIGH); // VIBRA EL MOTOR
    delay(1000);//TIEMPO DE ESPERA
    digitalWrite(motorPin, LOW); //EL MOTOR NO VIBRA

    noTone(buzzerPin); //Silencia Buzzer

    return; //SALE DEL MÉTODO
  }
}

void KillSwithch() {
  //TODO - Recibe la señal del boton y reinicia el juego
}


