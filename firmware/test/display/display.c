#include <avr/io.h>

#define LED_DIGIT1_PORT PORTB
#define LED_DIGIT1_PIN 0
#define LED_DIGIT2_PORT PORTB
#define LED_DIGIT2_PIN 1
#define LED_DIGIT3_PORT PORTB
#define LED_DIGIT3_PIN 2
#define LED_DIGIT4_PORT PORTC
#define LED_DIGIT4_PIN 5

#define LED_A_PORT PORTC
#define LED_A_PIN 4
#define LED_B_PORT PORTC
#define LED_B_PIN 3
#define LED_C_PORT PORTC
#define LED_C_PIN 2
#define LED_D_PORT PORTC
#define LED_D_PIN 1
#define LED_E_PORT PORTC
#define LED_E_PIN 0
#define LED_F_PORT PORTD
#define LED_F_PIN 3
#define LED_G_PORT PORTD
#define LED_G_PIN 4
#define LED_DP_PORT PORTD
#define LED_DP_PIN 5

void configure_outputs() {
  LED_DIGIT1_PORT |= _BV(LED_DIGIT1_PIN);
  LED_DIGIT2_PORT |= _BV(LED_DIGIT2_PIN);
  LED_DIGIT3_PORT |= _BV(LED_DIGIT3_PIN);
  LED_DIGIT4_PORT |= _BV(LED_DIGIT4_PIN);

  LED_A_PORT |= _BV(LED_A_PIN);
  LED_B_PORT |= _BV(LED_B_PIN);
  LED_C_PORT |= _BV(LED_C_PIN);
  LED_D_PORT |= _BV(LED_D_PIN);
  LED_E_PORT |= _BV(LED_E_PIN);
  LED_F_PORT |= _BV(LED_F_PIN);
  LED_G_PORT |= _BV(LED_G_PIN);
  LED_DP_PORT |= _BV(LED_DP_PIN);
}

void initialize() {
  configure_outputs();
}

int main() {
  initialize();

  return 0;
}
