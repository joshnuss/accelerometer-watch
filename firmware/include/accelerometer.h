#ifndef __ACCELEROMTER_H
#define __ACCELEROMTER_H

#define ACCELEROMTER_SLEEP_DDR DDRD
#define ACCELEROMTER_SLEEP_PORT PORTD
#define ACCELEROMTER_SLEEP_INDEX 6

#define X_ADC_CHANNEL 6
#define Y_ADC_CHANNEL 7

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

#endif
