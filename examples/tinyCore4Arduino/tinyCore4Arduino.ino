#include <tinyCore.hpp>
static tinyCore tc;

uint32_t delayMsec = 10;

void setup(void) {
  Serial.begin( 115200 ); while(!Serial);
  Serial.print("t0 start");
//  tc.begin();  // default 1msec delay
  tc.begin((uint32_t)delayMsec);
}

void loop(void) {
  static uint8_t cnt = 0;
  Serial.print("t0 "); Serial.println(cnt);
  cnt++;
  delay(delayMsec);
}

void setupN(void) {
  Serial.print("t1 start");
}

void loopN(void) {
  static uint8_t cnt = 0;
  Serial.print("t1 "); Serial.println(cnt);
  cnt++;
}
