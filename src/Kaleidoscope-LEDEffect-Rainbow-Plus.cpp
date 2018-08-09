#include "Kaleidoscope-LEDEffect-Rainbow-Plus.h"
#include "LEDUtils.h"

namespace kaleidoscope {

void LEDRainbowEffectBase::update(void) {
  now = millis();
  if ((now - last_hue_update) < hue_update_interval) {
#define UPDATE_INTERVAL 50  // milliseconds between two LED updates to avoid overloading; 20 fps
    if (!breathe || (now - last_update) < UPDATE_INTERVAL) {  // no updates either due to hue change or breathing
      return;
    }
  } else {
    hue += hue_steps;
    last_hue_update = now;
  }
  last_update = now;
  update_helper();
}

void LEDRainbowEffect::update_helper(void) {
  cRGB rainbow = breathe ?
                 breath_compute_helper(hue, saturation, now) :
                 hsvToRgb(hue, saturation, brightness);
  ::LEDControl.set_all_leds_to(rainbow);
}

void LEDRainbowWaveEffect::update_helper(void) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    uint8_t key_hue = hue + 16 * (i / 4);
    cRGB rainbow = breathe ?
                   breath_compute_helper(key_hue, saturation, now) :
                   hsvToRgb(key_hue, saturation, brightness);
    ::LEDControl.setCrgbAt(i, rainbow);
  }
}

void LEDRainbowCheckerboardEffect::update_helper(void) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    uint8_t key_hue = hue + 4 * (i / 2) + 128 * (i % 2);
    cRGB rainbow = breathe ?
                   breath_compute_helper(key_hue, saturation, now) :
                   hsvToRgb(key_hue, saturation, brightness);
    ::LEDControl.setCrgbAt(i, rainbow);
  }
}

} // namespace kaleidoscope

kaleidoscope::LEDRainbowEffect LEDRainbowEffect;
kaleidoscope::LEDRainbowWaveEffect LEDRainbowWaveEffect;
kaleidoscope::LEDRainbowCheckerboardEffect LEDRainbowCheckerboardEffect;
