/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define LED_R GPIO_NUM_2
#define LED_G GPIO_NUM_14


#include "detection_responder.h"

// This dummy implementation writes person and no person scores to the error
// console. Real applications will want to take some custom action instead, and
// should implement their own versions of this function.
void RespondToDetection(tflite::ErrorReporter* error_reporter,
                        uint8_t person_score, uint8_t no_person_score) {
  TF_LITE_REPORT_ERROR(error_reporter, "person score: %d,   no person score: %d",
                       person_score, no_person_score);

  gpio_pad_select_gpio(LED_R);
  gpio_pad_select_gpio(LED_G);
  /* Set the GPIO as a push/pull output */
  gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
  gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);

  if (person_score < no_person_score) {
      gpio_set_level(LED_R, 1);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  else {
      gpio_set_level(LED_G, 1);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  gpio_set_level(LED_R, 0);
  gpio_set_level(LED_G, 0);

}
