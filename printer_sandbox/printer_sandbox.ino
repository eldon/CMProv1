#include "Adafruit_Thermal.h"
Adafruit_Thermal printer(&Serial1);

#define PROP_PIN 11

/*
 * ICE BREAKER STRINGS AND UTILITIES
 */

#define NUM_STRINGS 18
#define MAX_LENGTH 140
#define PRINT_DELAY 10000

bool print_message = false;
int last_print_time;

static const char* string_table[] = {
    "If you could invent anything, what would you make?",
    "If you could have an endless supply of any food, what would you get?",
    "If you were an animal, what would you be and why?",
    "What is one goal you’d like to accomplish during your lifetime?",
    "When you were little, who was your favorite super hero and why?",
    "What’s your favorite thing to do in the summer?",
    "If someone made a movie of your life, what would it be about and which actor would you want to play you?",
    "If you were an ice cream flavor, which one would you be and why?",
    "What’s your favorite cartoon character, and why?",
    "If you could visit any place in the world, where would you choose to go and why?",
    "What’s the ideal dream job for you?",
    "What are your pet peeves or interesting things about you that you dislike?",
    "Are you a morning or night person?",
    "What are your favorite hobbies?",
    "Name one of your favorite things about someone in your family.",
    "Tell us about unique or quirky habit or yours.",
    "Let’s play: Hangman! Your word is: C R I T I C A L"
    "Let’s play: Hangman! Your word is: M A K I N G"
};

void setPrintMessage() {
  if ((millis() - last_print_time) > PRINT_DELAY) {
    print_message = true;
    last_print_time = millis();
  }
}

char* getRandomIceBreaker()
{
    int index = random(NUM_STRINGS);
    return getIceBreakerAtIndex(index);
}


char* getIceBreakerAtIndex(int i)
{
    return (char*)string_table[i];
}

/*
 * MAIN FUNCTIONS OF PROGRAM
 */

void setup() {
  Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.setDefault(); // Restore printer to defaults
  attachInterrupt(PROP_PIN, setPrintMessage, RISING);
  pinMode(13, OUTPUT);
  last_print_time = millis();
  interrupts();
}

void loop() {
  if (print_message) {
    printRandomString();
    print_message = false;
  }
  digitalWrite(13, digitalRead(PROP_PIN));
  delay(10);
}

void printRandomString() {
  //noInterrupts();
  printer.println(getRandomIceBreaker());
  printer.feed(1);
  //interrupts();
}

