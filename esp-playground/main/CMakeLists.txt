idf_component_register(SRCS "app_main.c" "playground.c"
                    INCLUDE_DIRS "."
                    REQUIRES common wifi mqtt sensor
                    PRIV_REQUIRES esp_driver_gpio esp_driver_ledc )
