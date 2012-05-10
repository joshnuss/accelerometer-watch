#include <avr/io.h>

#define DIGIT1_PORT PORTB
#define DIGIT1_PIN 0
#define DIGIT2_PORT PORTB
#define DIGIT2_PIN 1
#define DIGIT3_PORT PORTB
#define DIGIT3_PIN 2
#define DIGIT4_PORT PORTC
#define DIGIT4_PIN 5

void initialize() {
  DIGIT1_PORT |= _BV(DIGIT1_PIN);
  DIGIT2_PORT |= _BV(DIGIT2_PIN);
  DIGIT3_PORT |= _BV(DIGIT3_PIN);
  DIGIT4_PORT |= _BV(DIGIT4_PIN);
}

int main() {
  initialize();

  return 0;
}
