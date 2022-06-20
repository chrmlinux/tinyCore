#include <tinyCore.hpp>
static tinyCore tc;

void setup(void) {
  Serial.begin( 115200 ); while (!Serial);
  tc.begin();

  Serial.println("c1 start");
}

void loop(void) {
  static uint8_t i = 0;
  Serial.print("c1 "); Serial.println(i);
  i++;
}

void setup0(void) {
  Serial.println("c0 start");

}

void loop0(void) {
  static uint8_t i = 0;
  Serial.print("c0 "); Serial.println(i);
  i++;

}
