#include <stdio.h>

//Mocking the device and assuming reading and writing only bytes
static unsigned char address;
static unsigned char device[4];

int i2c_open(void) {
    //Assuming always ok
    //default values at power up
    address = 0x00;
    device[0]= 0x00;
    device[1]= 0x40;
    device[2]= 0x7F;
    device[3]= 0x80;
    return 0;
}

int i2c_write(char *buf, int size, char device_addr) {
    //Assuming always ok
    if(size == 1) {
        address = *buf;
    }
    if(size == 2) {
        address = buf[0];
        device[(int)address] = buf[1];
    }
    return size;
}

int i2c_read(char *buf, int size, char device_addr) {
    //Assuming always ok
    if(size == 1) {
        *buf = device[(int)address];
    }
    if(size == 2) {
        buf[0] = device[(int)address];
        buf[1] = 0xA0; //Assuming for simplicity that last 2 bits are 11
    }
    return size;
}

int i2c_close(void) {
     //Assuming always ok
    return 0;
}
