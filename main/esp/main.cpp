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

#include "../main_functions.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_camera.h"
#include "esp_log.h"
#include "nvs_flash.h"


#include "lwip/err.h"
#include "lwip/sys.h"

#include "app_httpd.h"

#include "wifi_sta.h"


static const char *TAG = "main";

int tf_main(int argc, char* argv[]) {
	
  // Start the webserver thread
  startCameraServer();
  
  for(;;);
  
  //setup();
  //while (true) {
  //  loop();
  //}
}


extern "C" {

	void app_main() {
		//Initialize NVS
		esp_err_t ret = nvs_flash_init();
		if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		  ESP_ERROR_CHECK(nvs_flash_erase());
		  ret = nvs_flash_init();
		}
		ESP_ERROR_CHECK(ret);

		ESP_LOGI(TAG, "Connecting to Wifi");
		wifi_init_sta();

		xTaskCreate((TaskFunction_t)&tf_main, "tensorflow", 32 * 1024, NULL, 8, NULL);
		vTaskDelete(NULL);

		for(;;);
	}

}




