#include <stdio.h>
#include "i2c_api.h"
#include "sensor.h"
#include "utils.h"

int valid_input(char* temperature) {
    int temp = atoi(temperature);
    if(temp > MAX_TEMP || temp < MIN_TEMP) {
        return 0;
    }
    return 1;
}

float convert_temperature(unsigned char* buffer) {
    //LSB 10..0
    unsigned short temperature = (((int)buffer[0]) << 2) | (buffer[1] >> 6);
    //Checking sign
    if(buffer[0] & 0x80) {
        temperature |= 0xFC00;
    }
    short temp_sign = *(unsigned short*)&temperature;
    float temp = temp_sign / 4.0;
    return temp;
}

unsigned char convert_threshold(int temperature) {
    //easy cast, I consider only the LSB 8..0
    char temp = (char) temperature;
    //reinterpret cast
    unsigned char data = *(unsigned char*)&temp;
    return data;
}

void print_instruction(char* program_name){
    printf("Correct usage:\n%s operation_mode alert_mode [T_high T_low]\n", program_name);
    printf("- operation_mode: 0: CONTINUOUS mode, 1 ONESHOT mode\n");
    printf("- alert_mode: 0: ALERT mode OFF, 1: ALERT mode ON\n");
    printf("- T_high: if ALERT mode is ON, T_high is temperature threshold high [%d,%d]\n",MIN_TEMP,MAX_TEMP);
    printf("- T_high: if ALERT mode is ON, T_low is temperature threshold low [%d,%d]\n",MIN_TEMP,MAX_TEMP);
    printf("Note:\n1) if ALERT is OFF, T_high and T_low are not considered\n2) T_high must be >= T_low\n");
}

void sleep_ms(int milliseconds) 
{
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}