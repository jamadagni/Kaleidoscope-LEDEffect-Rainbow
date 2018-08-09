#pragma once

#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {

class LEDRainbowEffectBase : public LEDMode {
 public:
  LEDRainbowEffectBase(void) {}
  void update(void) final;

  int8_t hue_steps = 1;
  uint8_t hue_update_interval = 40;
  uint8_t saturation = 255;
  bool breathe = false;
  uint8_t brightness = 50;

 protected:
  virtual void update_helper(void) = 0;
  uint8_t hue = 0;
  uint16_t now;

 private:
  uint16_t last_hue_update = 0;
  uint16_t last_update = 0;
};

class LEDRainbowEffect : public LEDRainbowEffectBase {
 protected:
  virtual void update_helper(void) final;
};

class LEDRainbowWaveEffect : public LEDRainbowEffectBase {
 protected:
  virtual void update_helper(void) final;
};

class LEDRainbowCheckerboardEffect : public LEDRainbowEffectBase {
 protected:
  virtual void update_helper(void) final;
};
}

extern kaleidoscope::LEDRainbowEffect LEDRainbowEffect;
extern kaleidoscope::LEDRainbowWaveEffect LEDRainbowWaveEffect;
extern kaleidoscope::LEDRainbowCheckerboardEffect LEDRainbowCheckerboardEffect;
