#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "display.h"

#define BUTTON_DDR DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND
#define BUTTON_INDEX 2

#define button_is_pressed() ((BUTTON_PIN & _BV(BUTTON_INDEX)) == 0)

volatile uint16_t counter=0;

void configure_button() {
  BUTTON_PORT |= _BV(BUTTON_INDEX); // enable pull up
  BUTTON_DDR &= ~_BV(BUTTON_INDEX); // define button as input
}

void configure_interrupts() {
  EICRA |= _BV(ISC00); // any change triggers INT0
  EIMSK |= _BV(INT0); // enable INT0 interrupt
}

void initialize() {
  configure_display();
  configure_button();
  configure_interrupts();
}

int main() {
  initialize();

  enable_digit(3);
  update_display(0, false);

  sei();

  set_sleep_mode(SLEEP_MODE_IDLE);

  while(1)
    sleep_mode();
  
  return 0;
}

ISR(INT0_vect) {
  if (button_is_pressed()) {
    if (++counter > 9)
      counter = 0;

    update_display(counter, false);
  }
}
