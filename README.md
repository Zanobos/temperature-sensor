# temperature-sensor

## build

Use the script provided "build.sh" in order to build the application itself and the tests

## tests

Test on module "utils" -> "utils_module_tests".

Test on module "sensor" -> "sensor_module_tests".

Test on the application -> script "src/tests/main_tests.sh"

## run

launch the application "sensor" (after performing a build)

## notes

the application has been tested on a raspberry device:

Linux raspberrypi 4.14.79-v7+ #1159 SMP Sun Nov 4 17:50:20 GMT 2018 armv7l GNU/Linux.

the i2c bus has been mocked by the file "i2c_api.c"
