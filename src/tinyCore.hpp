//=======================================================================
// program name   : tinyCore.hpp
// date/author    : 2022/06/20 @chrmlinux03
// update/author  : 2022/06/20 @chrmlinux03
// license        : mit
//=======================================================================

#ifndef __TINYCORE_HPP__
#define __TINYCORE_HPP__

enum {TINYCORE0 = 0, TINYCORE1};

#include <Arduino.h>

void loopN(void);
void setupN(void);
static TaskHandle_t pBehindTask = NULL;
static volatile bool bBehindTaskEnd = false;

void BehindTask(void *param) {
  while (!bBehindTaskEnd) {
    loopN();
    yield();
  }
  vTaskDelete(pBehindTask);
}

class tinyCore {
  public:
    void begin(uint16_t core) {
      _core = core;
      begin();
    }

    void begin(void) {
      setupN();
      xTaskCreatePinnedToCore(BehindTask, "BehindTask", 8192, NULL, 1, NULL, _core);
    }

    void end(void) {
      bBehindTaskEnd = true;
    }

  private:
    uint16_t _core = 0;
};

#endif
