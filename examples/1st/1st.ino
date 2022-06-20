#include <tinyCore.hpp>
static tinyCore tc;

void setup(void) {
  Serial.begin( 115200 ); while (!Serial);
  tc.begin(TINYCORE0);  // is tc.begin();
  // tc.begin(TINYCORE1);
  Serial.print("c"); Serial.print(xPortGetCoreID()); Serial.println(" start");
}

void loop(void) {
  static uint8_t i = 0;
  Serial.print("c"); Serial.print(xPortGetCoreID()); Serial.print(" "); Serial.println(i);
  i++;
  delay(1);
}

void setupN(void) {
  Serial.print("c"); Serial.print(xPortGetCoreID()); Serial.println(" start");
}

void loopN(void) {
  static uint8_t i = 0;
  Serial.print("c"); Serial.print(xPortGetCoreID()); Serial.print(" "); Serial.println(i);
  i++;
  delay(1);
}
