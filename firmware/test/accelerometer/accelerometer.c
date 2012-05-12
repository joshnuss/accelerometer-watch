#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include "display.h"
#include "button.h"

#define ACCELEROMTER_SLEEP_DDR DDRD
#define ACCELEROMTER_SLEEP_PORT PORTD
#define ACCELEROMTER_SLEEP_INDEX 6

#define X_ADC_CHANNEL 6
#define Y_ADC_CHANNEL 7

volatile uint16_t last_sample=0;
volatile uint16_t updates=0;
volatile uint8_t digit1 = 0;
volatile uint8_t digit2 = 0;
volatile uint8_t digit3 = 0;
volatile uint8_t digit4 = 0;
volatile uint8_t current_digit=0;

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

uint16_t read_adc(uint8_t channel) {
  ADMUX &= 0b11110000;
  ADMUX |= channel;
  ADCSRA |= _BV(ADSC); // start conversion
  while(!bit_is_set(ADCSRA, ADIF));

  ADCSRA |= _BV(ADIF);

  return ADCW;
}

void configure_accelerometer() {
  ADCSRA = _BV(ADEN); // enable ADC

  ACCELEROMTER_SLEEP_DDR |= _BV(ACCELEROMTER_SLEEP_INDEX);
  ACCELEROMTER_SLEEP_PORT |= _BV(ACCELEROMTER_SLEEP_INDEX);
}

void initialize() {
  configure_timer();
  configure_display();
  configure_button();
  configure_accelerometer();
}

int main() {
  initialize();

  sei();

  set_sleep_mode(SLEEP_MODE_IDLE);

  while(1)
    sleep_mode();
  
  return 0;
}

ISR(INT0_vect) {
}

uint8_t val;

ISR(TIMER0_COMPA_vect) {
  updates++;
  if (updates>50) {
    updates = 0;
    if (button_is_pressed())
      set_sample(read_adc(Y_ADC_CHANNEL));
    else
      set_sample(read_adc(X_ADC_CHANNEL));
  }
  switch (current_digit) {
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
  enable_digit(current_digit);
  update_display(val, last_sample > 500);

  if(++current_digit > 3) current_digit = 0;

}
