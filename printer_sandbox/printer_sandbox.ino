#include "Adafruit_Thermal.h"
Adafruit_Thermal printer(&Serial1);

/*
 * ICE BREAKER STRINGS AND UTILITIES
 */

#define NUM_STRINGS 5
#define MAX_LENGTH 140

static const char* string_table[] = {
    "Hi there, I'm string 0.",
    "Hi there, I'm string 1.",
    "Hi there, I'm string 2.",
    "Hi there, I'm string 3.",
    "Hi there, I'm string 4.",
};

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
  //Serial1.begin(19200); // Use this instead if using hardware serial
  //printer.begin();        // Init printer (same regardless of serial type)
  Serial.begin(9600);
}

void loop() {
  Serial.println(getRandomIceBreaker());
  delay(5000);
}

