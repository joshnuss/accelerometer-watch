#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define LED_DIGIT1_DDR DDRB
#define LED_DIGIT1_PORT PORTB
#define LED_DIGIT1_PIN 0

#define LED_DIGIT2_DDR DDRB
#define LED_DIGIT2_PORT PORTB
#define LED_DIGIT2_PIN 1

#define LED_DIGIT3_DDR DDRB
#define LED_DIGIT3_PORT PORTB
#define LED_DIGIT3_PIN 2

#define LED_DIGIT4_DDR DDRC
#define LED_DIGIT4_PORT PORTC
#define LED_DIGIT4_PIN 5

#define LED_A_DDR DDRC
#define LED_A_PORT PORTC
#define LED_A_PIN 4

#define LED_B_DDR DDRC
#define LED_B_PORT PORTC
#define LED_B_PIN 3

#define LED_C_DDR DDRC
#define LED_C_PORT PORTC
#define LED_C_PIN 2

#define LED_D_DDR DDRC
#define LED_D_PORT PORTC
#define LED_D_PIN 1

#define LED_E_DDR DDRC
#define LED_E_PORT PORTC
#define LED_E_PIN 0

#define LED_F_DDR DDRD
#define LED_F_PORT PORTD
#define LED_F_PIN 3

#define LED_G_DDR DDRD
#define LED_G_PORT PORTD
#define LED_G_PIN 4

#define LED_DP_DDR DDRD
#define LED_DP_PORT PORTD
#define LED_DP_PIN 5

void configure_outputs() {
  LED_DIGIT1_DDR |= _BV(LED_DIGIT1_PIN);
  LED_DIGIT2_DDR |= _BV(LED_DIGIT2_PIN);
  LED_DIGIT3_DDR |= _BV(LED_DIGIT3_PIN);
  LED_DIGIT4_DDR |= _BV(LED_DIGIT4_PIN);

  LED_A_DDR |= _BV(LED_A_PIN);
  LED_B_DDR |= _BV(LED_B_PIN);
  LED_C_DDR |= _BV(LED_C_PIN);
  LED_D_DDR |= _BV(LED_D_PIN);
  LED_E_DDR |= _BV(LED_E_PIN);
  LED_F_DDR |= _BV(LED_F_PIN);
  LED_G_DDR |= _BV(LED_G_PIN);
  LED_DP_DDR |= _BV(LED_DP_PIN);
}

void initialize() {
  configure_outputs();
}

void enable_digit(uint8_t digit) {
  switch(digit) {
    case 0:
      LED_DIGIT1_PORT |= _BV(LED_DIGIT1_PIN);
      break;
    case 1:
      LED_DIGIT2_PORT |= _BV(LED_DIGIT2_PIN);
      break;
    case 2:
      LED_DIGIT3_PORT |= _BV(LED_DIGIT3_PIN);
      break;
    case 3:
      LED_DIGIT4_PORT |= _BV(LED_DIGIT4_PIN);
      break;
  }
}

void disable_digit(uint8_t digit) {
  switch(digit) {
    case 0:
      LED_DIGIT1_PORT &= ~_BV(LED_DIGIT1_PIN);
      break;
    case 1:
      LED_DIGIT2_PORT &= ~_BV(LED_DIGIT2_PIN);
      break;
    case 2:
      LED_DIGIT3_PORT &= ~_BV(LED_DIGIT3_PIN);
      break;
    case 3:
      LED_DIGIT4_PORT &= ~_BV(LED_DIGIT4_PIN);
      break;
  }
}

void clear_display() {
  LED_A_PORT &= ~_BV(LED_A_PIN);
  LED_B_PORT &= ~_BV(LED_B_PIN);
  LED_C_PORT &= ~_BV(LED_C_PIN);
  LED_D_PORT &= ~_BV(LED_D_PIN);
  LED_E_PORT &= ~_BV(LED_E_PIN);
  LED_F_PORT &= ~_BV(LED_F_PIN);
  LED_G_PORT &= ~_BV(LED_G_PIN);
  LED_DP_PORT &= ~_BV(LED_DP_PIN);
}

void update_display(uint8_t number, bool show_dp) {
  clear_display();

  if (show_dp)
    LED_DP_PORT |= _BV(LED_DP_PIN);

  if (number == 0 || number == 2 || number == 3 || number > 4)
    LED_A_PORT |= _BV(LED_A_PIN);

  if (number < 5 || number > 6)
    LED_B_PORT |= _BV(LED_B_PIN);

  if (number != 2)
    LED_C_PORT |= _BV(LED_C_PIN);

  if ( !(number == 1 || number == 4 || number == 7) )
    LED_D_PORT |= _BV(LED_D_PIN);

  if (number == 0 || number == 2 || number == 6 || number == 8)
    LED_E_PORT |= _BV(LED_E_PIN);

  if (number == 0 || (number > 3 && number != 7))
    LED_F_PORT |= _BV(LED_F_PIN);

  if (number > 1 && number != 7)
    LED_G_PORT |= _BV(LED_G_PIN);
}

int main() {
  initialize();

  while(1) {
    uint8_t digit, number;

    for (digit=0; digit<4;digit++) {
      enable_digit(digit);

      for (number=0;number<=9;number++) {
        update_display(number, true);
        _delay_ms(1000);
      }

      disable_digit(digit);
    }
  }

  return 0;
}
