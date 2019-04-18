#include <stdio.h>
#include "utils.h"

int main(int argc, char **argv)
{
    printf("==== Testing valid_input\n");
    printf("TEST PASSED: %s\n", valid_input("120")==1? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", valid_input("140")==0? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", valid_input("-10")==1? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", valid_input("-58")==0? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", valid_input("125")==1? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", valid_input("-40")==1? "TRUE" : "FALSE");
    
    printf("==== Testing convert_temperature\n");
    unsigned char data[][2] = { 
        {0x00, 0x00},
        {0x32, 0x00},
        {0xFF, 0xC0},
        {0x4B, 0x80},
    };
    printf("TEST PASSED: %s\n", (convert_temperature(data[0])==0.0)? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (convert_temperature(data[1])==50.0)? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (convert_temperature(data[2])==-0.25)? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (convert_temperature(data[3])==75.5)? "TRUE" : "FALSE");
    printf("==== Testing convert_threshold\n");
    int thresholds[] = { -14, -1, 0, 32, 120 };
    printf("TEST PASSED: %s\n", (convert_threshold(thresholds[0])==0xF2U)? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (convert_threshold(thresholds[1])==0xFFU)? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (convert_threshold(thresholds[2])==0x00U)? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (convert_threshold(thresholds[3])==0x20U)? "TRUE" : "FALSE");
    printf("TEST PASSED: %s\n", (convert_threshold(thresholds[4])==0x78U)? "TRUE" : "FALSE");
}
