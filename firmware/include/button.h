#ifndef __BUTTON_H
#define __BUTTON_H

#define BUTTON_DDR DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND
#define BUTTON_INDEX 2

#define button_is_pressed() ((BUTTON_PIN & _BV(BUTTON_INDEX)) == 0)

void configure_button_interrupt() {
  EICRA |= _BV(ISC00); // any change triggers INT0
  EIMSK |= _BV(INT0); // enable INT0 interrupt
}

void configure_button() {
  BUTTON_PORT |= _BV(BUTTON_INDEX); // enable pull up
  BUTTON_DDR &= ~_BV(BUTTON_INDEX); // define button as input

  configure_button_interrupt();
}

#endif
