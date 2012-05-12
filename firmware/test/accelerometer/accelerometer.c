#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include "display.h"
#include "button.h"

volatile uint16_t last_sample=0;
volatile uint16_t updates=0;
volatile uint8_t digit1 = 0;
volatile uint8_t digit2 = 0;
volatile uint8_t digit3 = 0;
volatile uint8_t digit4 = 0;
volatile uint8_t digit=0;

void set_sample(uint16_t sample) {
  last_sample = sample;
  div_t temp;

  temp = div(sample, 10);
  digit4 = temp.rem;

  temp = div(temp.quot, 10);
  digit3 = temp.rem;

  temp = div(temp.quot, 10);
  digit2 = temp.rem;

  temp = div(temp.quot, 10);
  digit1 = temp.rem;
}

void configure_timer() {
  TCCR0A = _BV(WGM01);  // Mode = CT
  TCCR0B = _BV(CS00); // no prescaler clock
  OCR0A = 50;
  TIMSK0 = _BV(OCIE0A); // enable timer
}

void initialize() {
  configure_timer();
  configure_display();
  configure_button();
}

int main() {
  initialize();

  set_sample(24);

  sei();

  set_sleep_mode(SLEEP_MODE_IDLE);

  while(1)
    sleep_mode();
  
  return 0;
}

ISR(INT0_vect) {
  if (button_is_pressed())
      set_sample(0);
}

uint8_t val;

ISR(TIMER0_COMPA_vect) {
  updates++;
  switch (digit) {
    case 0:
      val = digit1; 
      break;
    case 1:
      val = digit2; 
      break;
    case 2:
      val = digit3; 
      break;
    case 3:
      val = digit4; 
      break;
  }

  clear_display();
  enable_digit(digit);
  update_display(val, false);

  if(++digit > 3) digit = 0;
  if (updates == 10) {
    set_sample(last_sample+1);
    updates = 0;
  }

}
