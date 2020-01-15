#include <avr/io.h>

void setup() {
  DDRB |= (1<<2)|(1<<1)|(1<<0);
  PORTB &= ~((1<<2)|(1<<1)|(1<<0));

  DDRA &= ~(1<<1);
  PORTA &= ~(1<<1);

  ADCSRA |= (1<<ADEN); // enable ADC
  ADCSRA |= (1<<ADATE); // continuouesly conversion
  // set up F/8
  ADCSRA &= ~(1<<ADPS2);
  ADCSRA |= (1<<ADPS1) | (1<<ADPS0);

  ADMUX |=  (1<<REFS1) | (1<<REFS0); // internal U = 2.56V
  ADMUX &= ~(1<<ADLAR); // adjust by right
  // enable ADC1
  ADMUX |= (1<<MUX0);
  ADMUX &= ~((1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1));

  ADCSRA |= (1<<ADSC);
}

void loop() {
  if (ADCSRA & (1<<ADIF)) {
    if (ADC >= 600) {
      PORTB |= (1<<0);
      PORTB &= ~((1<<2) | (1<<1));
    } else if (ADC >= 560) {
      PORTB |= (1<<1);
      PORTB &= ~((1<<2) | (1<<0));
    } else {
      PORTB |= (1<<2);
      PORTB &= ~((1<<1) | (1<<0));
    }

    ADCSRA |= (1<<ADIF);
  }
}

int main(void) {
  setup();

  while (1) {
    loop();
  }

  return 0;
}