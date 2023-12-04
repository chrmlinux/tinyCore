#include "tinyCore.hpp"

#define BUFSIZE (1024 * 100)
typedef struct {
  uint8_t buf[BUFSIZE];
  uint32_t cnt;
} THREAD_BUF;

static volatile THREAD_BUF tb;
tinyCore tc;

void setup(void) {
  Serial.begin( 115200 ); delay(100);
  tc.begin();
}

void loop(void) {
  Serial.printf("task%d cnt:%d\n", 0, tb.cnt);   
  tb.cnt++;
}

void setupN(void) {
}

void loopN(void) {
  Serial.printf("task%d cnt:%d\n", 1, tb.cnt);   
  tb.cnt++;
}
