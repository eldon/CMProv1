#include "Adafruit_Thermal.h"
Adafruit_Thermal printer(&Serial1);

#define PROP_PIN 11

/*
 * ICE BREAKER STRINGS AND UTILITIES
 */

#define NUM_STRINGS 5
#define MAX_LENGTH 140
#define PRINT_DELAY 10000

bool print_message = false;
int last_print_time;

static const char* string_table[] = {
    "Hi there, I'm string 0.",
    "Hi there, I'm string 1.",
    "Hi there, I'm string 2.",
    "Hi there, I'm string 3.",
    "Hi there, I'm string 4.",
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

