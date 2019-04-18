#include <stdio.h>
#include "sensor.h"


int main(int argc, char **argv)
{
    printf("==== Testing change_bit_byte\n");
    printf("TEST PASSED: %s\n", (change_bit_byte(0x40,0,0))==0x40? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (change_bit_byte(0x40,5,1))==0x60? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (change_bit_byte(0x40,7,1))==0xC0? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (change_bit_byte(0x40,6,0))==0x00? "TRUE" : "FALSE");
    open_bus();
    printf("==== Testing configure_sensor\n");
    configure_sensor(0,1);
    printf("TEST PASSED: %s\n", (read_configuration())==0x60? "TRUE" : "FALSE");
    configure_sensor(1,0);
    printf("TEST PASSED: %s\n", (read_configuration())==0xC0? "TRUE" : "FALSE");
    configure_sensor(1,1);
    printf("TEST PASSED: %s\n", (read_configuration())==0xE0? "TRUE" : "FALSE");
    configure_sensor(0,0);
    printf("TEST PASSED: %s\n", (read_configuration())==0x40? "TRUE" : "FALSE");
}