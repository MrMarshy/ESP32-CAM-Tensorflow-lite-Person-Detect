
#
# Main component of TF Micro project 'person_detection'.
#

idf_component_register(
    SRCS detection_responder.cpp esp/wifi_sta.c esp/image_provider.cpp esp/main.cpp main_functions.cpp model_settings.cpp person_model_grayscale/person_detect_model_data.cpp esp/app_camera_esp.c esp/app_httpd.cpp
    INCLUDE_DIRS "")
