#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdbool.h>
#include "display.h"

void initialize() {
  configure_display();
}

int main() {
  initialize();

  enable_digit(3);
  update_display(0, false);
  _delay_ms(1000);
  update_display(1, false);
  _delay_ms(1000);
  update_display(2, false);
  _delay_ms(1000);
  disable_digit(3);

  while(1) {
    uint8_t digit, number, i;

    for (number=0;number<=9;number++) {
      for (i=0;i<250;i++) {
        for (digit=0; digit<4;digit++) {
          enable_digit(digit);

          update_display(number, false);
          _delay_us(100);

          disable_digit(digit);
        }
      }
    }
  }

  return 0;
}
