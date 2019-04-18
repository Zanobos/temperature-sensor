# temperature-sensor

## build

Use the script provided "build.sh" in order to build the application itself and the tests

## tests

Launch the 2 executables created "utils_module_tests" and "sensor_module_tests" in order to perform unit testing
Launch the script "src/tests/main_tests.sh" in order to test a different sets of input for the application

## run

launch the application "sensor" after having built

## notes

the application has been tested on a raspberry device:
Linux raspberrypi 4.14.79-v7+ #1159 SMP Sun Nov 4 17:50:20 GMT 2018 armv7l GNU/Linux
the i2c bus has been mocked by the file "i2c_api.c"
