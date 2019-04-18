#include <stdio.h>
#include "i2c_api.h"
#include "sensor.h"

int open_bus(void) {
    return i2c_open();
}

int close_bus(void) {
    return i2c_close();
}

int configure_sensor(int operation_mode, int alert_mode, int alert_polarity) {
    
    unsigned char buffer = read_configuration();
    buffer = change_bit_byte(buffer,POWER_DOWN_BIT,operation_mode);
    buffer = change_bit_byte(buffer,ALERT_EN_BIT,alert_mode);
	buffer = change_bit_byte(buffer,ALERT_POLARITY_BIT,alert_polarity);
    int result = set_configuration(buffer);
    
    return result;
}

void read_temperature_oneshot(unsigned char* buffer) {

    unsigned char conf = read_configuration();
    conf = change_bit_byte(conf,ONE_SHOT_BIT,1);
    set_configuration(conf);
    read_temperature(buffer);
}

unsigned char read_configuration() {
   return read_register(REG_CONFIG_ADDR);
}

unsigned char read_temp_high() {
    return read_register(REG_T_HIGH_ADDR);
}

unsigned char read_temp_low() {
    return read_register(REG_T_LOW_ADDR);
}

int set_configuration(unsigned char data) {
    return write_register(REG_CONFIG_ADDR,data);
}

int set_temp_high(unsigned char data) {
    return write_register(REG_T_HIGH_ADDR,data);
}

int set_temp_low(unsigned char data) {
    return write_register(REG_T_LOW_ADDR,data);
}

void read_temperature(unsigned char* buffer) {
    unsigned char address = REG_TEMP_ADDR;
    sensor_write_one_byte(&address);
    sensor_read_two_bytes(buffer);
}

unsigned char read_register(unsigned char address) {
    unsigned char buffer;
    sensor_write_one_byte(&address);
    sensor_read_one_byte(&buffer);
    return buffer;
}

int write_register(unsigned char address, unsigned char data){
    unsigned char buffer[2];
    int result;
    
    buffer[0] = address;
    buffer[1] = data;
    result = sensor_write_two_bytes(buffer);
    return result;
}

//Atomic read of a single byte
int sensor_read_one_byte(unsigned char* buf) {
    return i2c_read((char*)buf, BUFF_SIZE, ADDR_DEVICE) - BUFF_SIZE;
}

//Atomic read of a single byte
int sensor_read_two_bytes(unsigned char* buf) {
    return i2c_read((char*)buf, BUFF_SIZE *2, ADDR_DEVICE) - BUFF_SIZE*2;
}

//Atomic write of a single byte
//I return 0 in case of success
int sensor_write_one_byte(unsigned char* buf) {
    return i2c_write((char*)buf, BUFF_SIZE, ADDR_DEVICE) - BUFF_SIZE;
}

//Atomic write of two bytes
//I return 0 in case of success
int sensor_write_two_bytes(unsigned char* buf) {
    return i2c_write((char*)buf, BUFF_SIZE *2, ADDR_DEVICE) - BUFF_SIZE*2;
}

unsigned char change_bit_byte(unsigned char number, unsigned char bit_position, int value) {
    unsigned long newbit_op = !!value;    // Also booleanize to force 0 or 1
    number ^= (-newbit_op ^ number) & (1UL << bit_position);
    return number;
}
