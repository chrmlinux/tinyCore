//=======================================================================
// program name   : tinyCore.hpp
// date/author    : 2022/06/20 @chrmlinux03
// update/author  : 2022/06/21 @chrmlinux03
//     v0.1.1 for core selected
// update/author  : 2022/06/23 @chrmlinux03
//     v0.2.1 for Arduino
// update/author  : 2023/12/01 @chrmlinux03
//     v0.3.0 for SPRESENSE
// license        : MIT
//=======================================================================

#ifndef __TINYCORE_HPP__
#define __TINYCORE_HPP__

#include <Arduino.h>

//=======================================================================
// include
//=======================================================================
#if defined (ARDUINO_ARCH_ESP32)
//-------------------------------------
// for ESP32
//-------------------------------------

#elif defined (ARDUINO_ARCH_SPRESENSE)
//-------------------------------------
// for SPRESENSE
//-------------------------------------

#else
//-------------------------------------
// for Arduino
//-------------------------------------
#include <MsTimer2.h>
#endif

//=======================================================================
// work setup
//=======================================================================
//-------------------------------------
// dummy loopN/setupN
//-------------------------------------
void setupN(void);
void loopN(void);
static volatile bool bBehindTaskEnd = false;

#if defined (ARDUINO_ARCH_ESP32)
//-------------------------------------
// for ESP32
//-------------------------------------
static TaskHandle_t pBehindTask = NULL;

#elif defined (ARDUINO_ARCH_SPRESENSE)
//-------------------------------------
// for SPRESENSE
//-------------------------------------

#else 
//-------------------------------------
// for Arduino
//-------------------------------------
#endif

//=======================================================================
// another task exec
//=======================================================================
#if defined (ARDUINO_ARCH_ESP32)
//-------------------------------------
// for ESP32
//-------------------------------------
void BehindTask(void *param) {
  while (!bBehindTaskEnd) {
    loopN();
    yield();
  }
  vTaskDelete(pBehindTask);
}
#elif defined (ARDUINO_ARCH_SPRESENSE)
//-------------------------------------
// for SPRESENSE
//-------------------------------------
void thread(int argc, char **argv) {
  while (!bBehindTaskEnd) {
    loopN();
    yield();
  }    
}

#else
//-------------------------------------
// for Arduino
//-------------------------------------
#endif

//=======================================================================
// class
//=======================================================================
class tinyCore {

  public:
    tinyCore(){}
    ~tinyCore(){}

    //=======================================================================
    // begin
    //=======================================================================
    void begin(uint32_t msec) { // for Arduino
      _msec = msec;
      begin();
    }
    void begin(uint16_t core) { // for ESP32
      _core = core;
      begin();
    }
    void begin(void) {
      setupN();
      
#if defined (ARDUINO_ARCH_ESP32)
      //-------------------------------------
      // for ESP32
      //-------------------------------------
      xTaskCreatePinnedToCore(BehindTask, "BehindTask", 8192, NULL, 1, NULL, _core);

#elif defined (ARDUINO_ARCH_SPRESENSE)
      //-------------------------------------
      // for SPRESENSE
      //-------------------------------------
      char *argv[4];
      argv[0] = NULL;
      task_create("task1", 121, 2028, thread, argv);

#else
      //-------------------------------------
      // for Arduino
      //-------------------------------------
      MsTimer2::set(_msec, loopN);
      MsTimer2::start();
#endif
    }

    //=======================================================================
    // end
    //=======================================================================
    void end(void) {
      bBehindTaskEnd = true;
    }

  private:
    uint16_t _core = 0;
    uint32_t _msec = 1;
};

#endif
