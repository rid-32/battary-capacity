#include <avr/io.h>

void setup() {
  DDRC |= (1<<0);
  PORTC |= (1<<0);
}

void loop() {}

int main(void) {
  setup();

  while (1) {
    loop();
  }

  return 0;
}