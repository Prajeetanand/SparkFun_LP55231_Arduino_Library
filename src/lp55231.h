#pragma once

#ifndef _LP55231_H_
#define _LP55231_H_

#include <stdint.h>

class Lp55231
{
public:
  Lp55231(uint8_t address = 0x32);

  // values for dimensioning and input validation
  static const uint8_t NumChannels = 9;
  static const uint8_t NumFaders = 3;
  static const uint8_t NumEngines = 3;
  static const uint8_t NumInstructions = 96;


  // Initialization routines
  void Begin();
  void Enable();
  void Disable();
  void Reset();

  // control outputs directly
  bool SetChannelPWM(uint8_t channel, uint8_t value);
  bool SetMasterFader(uint8_t fader, uint8_t value);

  // More detailed channel configuration
  bool SetLogBrightness(uint8_t channel, bool enable);
  bool SetDriveCurrent(uint8_t channel, uint8_t value);

  // Configure outputs
  bool AssignChannelToMasterFader(uint8_t channel, uint8_t fader);


protected:
  // private methods

  uint8_t ReadReg(uint8_t reg);
  void    WriteReg(uint8_t reg, uint8_t val);

  // private data
  uint8_t _address;

};

class Lp55231Engines: public Lp55231
{
public:
  Lp55231Engines(uint8_t address = 0x32): Lp55231(address)
  { };

  bool SetRatiometricDimming(uint8_t channel, bool value);

  // Execution engine related items.
  bool LoadProgram(const uint16_t* prog, uint8_t len);
  bool VerifyProgram(const uint16_t* prog, uint8_t len);
  bool SetEngineEntryPoint(uint8_t engine, uint8_t addr);
  bool SetEnginePC(uint8_t engine, uint8_t addr);
  uint8_t GetEnginePC(uint8_t engine);
  uint8_t GetEngineMap(uint8_t engine);

  // Set engine execution modes
  bool SetEngineModeHold(uint8_t engine);
  bool SetEngineModeStep(uint8_t engine);
  bool SetEngineModeOnce(uint8_t engine);
  bool SetEngineModeFree(uint8_t engine);
  uint8_t GetEngineMode(uint8_t engine);

  // start an engine.
  bool SetEngineRunning(uint8_t engine);

  // Interrupt related
  uint8_t ClearInterrupt();
  void overrideIntToGPO(bool overrideOn );
  bool setIntGPOVal(bool value);


  // Internal diagnostic features
  int8_t readDegC();
  float  readLEDADC(uint8_t channel);
  float  readVoutADC();
  float  readVddADC();
  float  readIntADC();


private:
  void    WaitForBusy();
  uint8_t ReadADCInternal(uint8_t channel);

};

#if 0
class lp55231dep
{
  public:

    lp55231dep(uint8_t address = 0x32);
    void init();

    // fundamental operations
    uint8_t clearInterrupt();

    // basic LED control functions
    bool setBrightness(uint8_t channel, uint8_t value);
    bool setLogBrightness(uint8_t channel);
    bool setDriveCurrent(uint8_t channel, uint8_t value);





  private:
    void waitForBusy();
    uint8_t readADCInternal(uint8_t channel);

    // private methods
    uint8_t readReg(uint8_t reg);
    void   writeReg(uint8_t reg, uint8_t val);

    // private data
    uint8_t _address;



};

#endif // if 0

#endif
