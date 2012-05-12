#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "display.h"
#include "button.h"

volatile uint16_t counter=0;

void initialize() {
  configure_display();
  configure_button();
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
