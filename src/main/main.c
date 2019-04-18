#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int main(int argc, char **argv)
{
    
    //Fields declaration
    int alert_mode, operation_mode;
    int t_high = -300, t_low = -300; //initializing thresholds to non valid values
    unsigned char buffer[2];
    unsigned char threshold;
    float temperature;
    
    //Fields for user interaction
    char line[5];
    int answer, sscanf_result;
    
    //First check minimal amount of arguments
    if(argc < 3) {
        print_instruction(argv[0]);
        return EXIT_FAILURE;
    }
    
    //Extracting operation_mode
    operation_mode = argv[1][0] == '1';
    
    //If we get here, ALERT mode is setted
    alert_mode = argv[2][0] == '1';
    if(alert_mode && argc < 5) {
        printf("ALERT mode is ON, but no T_high and T_low are passed!\n");
        print_instruction(argv[0]);
        return EXIT_FAILURE;
    }
    
    //If ALERT mode is ON, I can extract threshold values
    if(alert_mode) {
        //parsing t_high
        if(!valid_input(argv[3])) {
            printf("T_high not in valid range\n");
            print_instruction(argv[0]);
            return EXIT_FAILURE;
        } else {
            t_high = atoi(argv[3]);
        }
        //parsing t_low
        if(!valid_input(argv[4])) {
            printf("T_low not in valid range\n");
            print_instruction(argv[0]);
            return EXIT_FAILURE;
        } else {
            t_low = atoi(argv[4]);
        }
        //T_low must be < T_high
        if(t_high < t_low) {
            printf("T_high must be > T_low\n");
            print_instruction(argv[0]);
            return EXIT_FAILURE;
        }
    }
    
    //From this point on, input should be sanitized
    
    //1. Opening i2c bus
    if(open_bus() < 0) {
        printf("Impossible to connect to I2C bus!\n");
        return EXIT_FAILURE;
    }
    
    //2. Configuring the device
    configure_sensor(operation_mode, alert_mode);
    
    //3. Set up alarm thresholds
    if(!alert_mode) {
        threshold = convert_threshold(t_high);
        set_temp_high(threshold);
        threshold = convert_threshold(t_low);
        set_temp_high(threshold);
    }
    
    //4. Start acquiring, depending on operation_mode
    if(operation_mode) {
        //Operation mode ONESHOT
        answer = -1;
        while (answer != 0){
            printf("Enter:\n");
            printf(" [1] to acquire the temperature\n");
            printf(" [0] to exit\n");
            fgets (line, sizeof(line), stdin);
            sscanf_result = sscanf (line, "%d", &answer); // get answer
            if ((sscanf_result == 0) | (sscanf_result == EOF)) {
                answer = -1; // set answer to a value that falls through
            }
            switch (answer) {
                case 0:
                    break;
                case 1:
                    read_temperature_oneshot(buffer);
                    temperature = convert_temperature(buffer);
                    printf ("Temperature is %f\n", temperature);
                    break;
                default:
                    break;
            }
        }
    } else {
        //Operation mode CONTINUOS
        while (1){
            read_temperature(buffer);
            temperature = convert_temperature(buffer);
            printf("Temperature is %f\n", temperature);
            fflush(stdout);
            sleep_ms(800);
        }
    }
    
    close_bus();
    
    return EXIT_SUCCESS;
}
