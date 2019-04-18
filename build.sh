gcc -I src/lib src/main/main.c src/lib/i2c_api.c src/lib/sensor.c src/lib/utils.c -o sensor

gcc -I src/lib src/tests/utils_tests.c src/lib/i2c_api.c src/lib/sensor.c src/lib/utils.c -o utils_module_tests

gcc -I src/lib src/tests/sensor_tests.c src/lib/i2c_api.c src/lib/sensor.c -o sensor_module_tests