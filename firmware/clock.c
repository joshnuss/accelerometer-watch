#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdbool.h>
#include "display.h"
#include "button.h"
#include "accelerometer.h"

#define MODE_OFF 0
#define MODE_DISPLAY_TIME 1
#define MODE_SET_HOURS 2
#define MODE_SET_MINUTES 3

#define BUTTON_PRESS_SHORT_THRESHOLD 10
#define BUTTON_PRESS_LONG_THRESHOLD 200
#define DISPLAY_AUTO_SHUTOFF_SECONDS 6

volatile struct { 
  uint8_t hours; 
  uint8_t minutes; 
  uint8_t seconds } time, current, temp;

volatile uint8_t mode = MODE_OFF;
volatile uint8_t current_digit = 0;
uint8_t current_digit_val = 0;
volatile uint16_t button_pressed_count = 0;
volatile uint8_t display_on_count = 0;

void configure_clock_timer() {
  TCCR1A = 0;  
  TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);  //set mode = CTC, prescaler = clock/1024
  OCR1A  = 32;
  TIMSK1 = _BV(OCIE1A); //enable interrupt on overflow
}
void configure_display_timer() {
  TCCR0A = _BV(WGM01); // mode = CTC 
  TCCR0B = _BV(CS00); // Mode = CTC, no prescaler
  OCR0A = 100; // increment button presses every 100 ticks
  OCR0B = 5; // update display every 5 ticks
}

void enable_display() {
  display_on_count = 0;
  TIMSK0 |= _BV(OCIE0B); // enable timer
}
void disable_display() {
  display_on_count = 0;
  TIMSK0 &= ~_BV(OCIE0B); // disable timer
  clear_display();
}
void enable_button_counter() {
  TIMSK0 |= _BV(OCIE0A); // enable timer
}
void disable_button_counter() {
  TIMSK0 &= ~_BV(OCIE0A); // disable timer
}

void configure_timers() {
  configure_clock_timer();
  configure_display_timer();
}

void initialize() {
  configure_timers();
  configure_display();
  configure_button();
  configure_accelerometer();
}

void increment_seconds() {
  if (++time.seconds > 59) {
    time.seconds = 0;

    if (++time.minutes > 59) {
      time.minutes = 0;

      if(++time.hours > 12) {
        time.hours = 1;
      }
    }
  }
}

void handle_short_button_press() {
  switch(mode) {
    case MODE_OFF:
      mode = MODE_DISPLAY_TIME;
      enable_display();
      break;
    case MODE_DISPLAY_TIME:
      mode = MODE_OFF;
      disable_display();
      break;
    case MODE_SET_HOURS:
      temp.hours++;
      if (temp.hours > 12)
        temp.hours = 1;
      break;
    case MODE_SET_MINUTES:
      temp.minutes++;
      if (temp.hours > 59)
        temp.hours = 0;
      break;
  }
}

void handle_long_button_press() {
  switch(mode) {
    case MODE_OFF:
    case MODE_DISPLAY_TIME:
      mode = MODE_SET_MINUTES;
      temp.hours = time.hours;
      temp.minutes = time.minutes;
      enable_display();
      break;
    case MODE_SET_MINUTES:
      mode = MODE_SET_HOURS;
      break;
    case MODE_SET_HOURS:
      time = temp;
      mode = MODE_DISPLAY_TIME;
      enable_display();
      break;
  }
}

void handle_button_press() {
  if (button_pressed_count >= BUTTON_PRESS_LONG_THRESHOLD)
    handle_long_button_press();
  else if (button_pressed_count >= BUTTON_PRESS_SHORT_THRESHOLD)
    handle_short_button_press();
}

int main() {
  initialize();

  time.hours = 12;

  sei();

  set_sleep_mode(SLEEP_MODE_IDLE);

  while(1)
    sleep_mode();

  return 0;
}

ISR(INT0_vect) {
  if (button_is_pressed()) {
    button_pressed_count = 0;
    enable_button_counter();
  }
  else {
    handle_button_press();
    disable_button_counter();
  }
}

ISR(TIMER0_COMPB_vect) {
  if (mode == MODE_SET_HOURS || mode == MODE_SET_MINUTES)
    current = temp;
  else
    current = time;

  switch (current_digit) {
    case 0:
      current_digit_val = current.hours / 10; 
      break;
    case 1:
      current_digit_val = current.hours % 10; 
      break;
    case 2:
      current_digit_val = current.minutes / 10; 
      break;
    case 3:
      current_digit_val = current.minutes % 10; 
      break;
  }

  clear_display();
  if (current_digit > 0 || current_digit_val > 0) {
    enable_digit(current_digit);
    update_display(current_digit_val, current_digit == 1);
  }

  if(++current_digit > 3) 
    current_digit = 0;
}

ISR(TIMER0_COMPA_vect) {
  button_pressed_count++;
}

ISR(TIMER1_COMPA_vect) {
  increment_seconds();

  if (mode == MODE_DISPLAY_TIME) {
    display_on_count++;
    if (display_on_count > DISPLAY_AUTO_SHUTOFF_SECONDS) {
      mode = MODE_OFF;
      disable_display();
    }
  }
}
