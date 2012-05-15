#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <avr/pgmspace.h>
#include <stdbool.h>

#define LED_DIGIT1_DDR DDRB
#define LED_DIGIT1_PORT PORTB
#define LED_DIGIT1_INDEX 0

#define LED_DIGIT2_DDR DDRB
#define LED_DIGIT2_PORT PORTB
#define LED_DIGIT2_INDEX 1

#define LED_DIGIT3_DDR DDRB
#define LED_DIGIT3_PORT PORTB
#define LED_DIGIT3_INDEX 2

#define LED_DIGIT4_DDR DDRC
#define LED_DIGIT4_PORT PORTC
#define LED_DIGIT4_INDEX 5

#define LED_A_DDR DDRC
#define LED_A_PORT PORTC
#define LED_A_INDEX 4

#define LED_B_DDR DDRC
#define LED_B_PORT PORTC
#define LED_B_INDEX 3

#define LED_C_DDR DDRC
#define LED_C_PORT PORTC
#define LED_C_INDEX 2

#define LED_D_DDR DDRC
#define LED_D_PORT PORTC
#define LED_D_INDEX 1

#define LED_E_DDR DDRC
#define LED_E_PORT PORTC
#define LED_E_INDEX 0

#define LED_F_DDR DDRD
#define LED_F_PORT PORTD
#define LED_F_INDEX 3

#define LED_G_DDR DDRD
#define LED_G_PORT PORTD
#define LED_G_INDEX 4

#define LED_DP_DDR DDRD
#define LED_DP_PORT PORTD
#define LED_DP_INDEX 5

#define SEGMENT_A _BV(0)
#define SEGMENT_B _BV(1)
#define SEGMENT_C _BV(2)
#define SEGMENT_D _BV(3)
#define SEGMENT_E _BV(4)
#define SEGMENT_F _BV(5)
#define SEGMENT_G _BV(6)

/*
 -- A --
|       |
F       B
|       |
 -- G -- 
|       |
E       C
|       |
 -- D -- 
*/

static uint8_t character_map[] PROGMEM = {
  SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,              // 0
  SEGMENT_B | SEGMENT_C,                                                              // 1
  SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,                          // 2
  SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,                          // 3
  SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,                                      // 4
  SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,                          // 5
  SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,              // 6
  SEGMENT_A | SEGMENT_B | SEGMENT_C,                                                  // 7
  SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,  // 8
  SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G               // 9
};

void configure_display() {
  LED_DIGIT1_DDR |= _BV(LED_DIGIT1_INDEX);
  LED_DIGIT2_DDR |= _BV(LED_DIGIT2_INDEX);
  LED_DIGIT3_DDR |= _BV(LED_DIGIT3_INDEX);
  LED_DIGIT4_DDR |= _BV(LED_DIGIT4_INDEX);

  LED_A_DDR |= _BV(LED_A_INDEX);
  LED_B_DDR |= _BV(LED_B_INDEX);
  LED_C_DDR |= _BV(LED_C_INDEX);
  LED_D_DDR |= _BV(LED_D_INDEX);
  LED_E_DDR |= _BV(LED_E_INDEX);
  LED_F_DDR |= _BV(LED_F_INDEX);
  LED_G_DDR |= _BV(LED_G_INDEX);
  LED_DP_DDR |= _BV(LED_DP_INDEX);
}

void enable_digit(uint8_t digit) {
  switch(digit) {
    case 0:
      LED_DIGIT2_PORT &= ~_BV(LED_DIGIT2_INDEX);
      LED_DIGIT3_PORT &= ~_BV(LED_DIGIT3_INDEX);
      LED_DIGIT4_PORT &= ~_BV(LED_DIGIT4_INDEX);
      LED_DIGIT1_PORT |= _BV(LED_DIGIT1_INDEX);
      break;
    case 1:
      LED_DIGIT1_PORT &= ~_BV(LED_DIGIT1_INDEX);
      LED_DIGIT3_PORT &= ~_BV(LED_DIGIT3_INDEX);
      LED_DIGIT4_PORT &= ~_BV(LED_DIGIT4_INDEX);
      LED_DIGIT2_PORT |= _BV(LED_DIGIT2_INDEX);
      break;
    case 2:
      LED_DIGIT1_PORT &= ~_BV(LED_DIGIT1_INDEX);
      LED_DIGIT2_PORT &= ~_BV(LED_DIGIT2_INDEX);
      LED_DIGIT4_PORT &= ~_BV(LED_DIGIT4_INDEX);
      LED_DIGIT3_PORT |= _BV(LED_DIGIT3_INDEX);
      break;
    case 3:
      LED_DIGIT1_PORT &= ~_BV(LED_DIGIT1_INDEX);
      LED_DIGIT2_PORT &= ~_BV(LED_DIGIT2_INDEX);
      LED_DIGIT3_PORT &= ~_BV(LED_DIGIT3_INDEX);
      LED_DIGIT4_PORT |= _BV(LED_DIGIT4_INDEX);
      break;
  }
}

void disable_digit(uint8_t digit) {
  switch(digit) {
    case 0:
      LED_DIGIT1_PORT &= ~_BV(LED_DIGIT1_INDEX);
      break;
    case 1:
      LED_DIGIT2_PORT &= ~_BV(LED_DIGIT2_INDEX);
      break;
    case 2:
      LED_DIGIT3_PORT &= ~_BV(LED_DIGIT3_INDEX);
      break;
    case 3:
      LED_DIGIT4_PORT &= ~_BV(LED_DIGIT4_INDEX);
      break;
  }
}

void clear_display() {
  PORTC |= _BV(LED_A_INDEX) | _BV(LED_B_INDEX) | _BV(LED_C_INDEX) | _BV(LED_D_INDEX) | _BV(LED_E_INDEX);
  PORTD |= _BV(LED_F_INDEX) | _BV(LED_G_INDEX) | _BV(LED_DP_INDEX);
}

void update_display(uint8_t number, bool show_dp) {
  uint8_t map = pgm_read_byte(&character_map[number]);
  uint8_t cmask = PORTC | _BV(LED_A_INDEX) | _BV(LED_B_INDEX) | _BV(LED_C_INDEX) | _BV(LED_D_INDEX) | _BV(LED_E_INDEX);
  uint8_t dmask = PORTD | _BV(LED_F_INDEX) | _BV(LED_G_INDEX) | _BV(LED_DP_INDEX);

  if (map & SEGMENT_A)
    cmask &= ~_BV(LED_A_INDEX);

  if (map & SEGMENT_B)
    cmask &= ~_BV(LED_B_INDEX);

  if (map & SEGMENT_C)
    cmask &= ~_BV(LED_C_INDEX);

  if (map & SEGMENT_D)
    cmask &= ~_BV(LED_D_INDEX);

  if (map & SEGMENT_E)
    cmask &= ~_BV(LED_E_INDEX);

  if (map & SEGMENT_F)
    dmask &= ~_BV(LED_F_INDEX);

  if (map & SEGMENT_G)
    dmask &= ~_BV(LED_G_INDEX);

  if (show_dp)
    dmask &= ~_BV(LED_DP_INDEX);

  PORTC = cmask;
  PORTD = dmask;
}

#endif
