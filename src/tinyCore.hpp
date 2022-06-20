#ifndef __TINYCORE_HPP__
#define __TINYCORE_HPP__

#include <Arduino.h>

void loop0(void);
void setup0(void);
static TaskHandle_t pBehindTask = NULL;
static volatile bool bBehindTaskEnd = false;

void BehindTask(void *param) {
  while (!bBehindTaskEnd) {
    loop0();
    yield();
  }
  vTaskDelete(pBehindTask);
}

class tinyCore {
  public:
    void begin(void) {
      setup0();
      xTaskCreatePinnedToCore(BehindTask, "BehindTask", 8192, NULL, 1, NULL, _core);
    }
    void end(void) {
      bBehindTaskEnd = true;
    }

  private:
    uint16_t _core = 0;
};

#endif
