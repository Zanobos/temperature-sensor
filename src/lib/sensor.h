#define ADDR_DEVICE 0x64
#define BUFF_SIZE   1

#define REG_TEMP_ADDR    0x00
#define REG_CONFIG_ADDR  0x01 
#define REG_T_HIGH_ADDR  0x02
#define REG_T_LOW_ADDR   0x03

#define MIN_TEMP -40
#define MAX_TEMP 125

#define POWER_DOWN_BIT 7
#define ALERT_EN_BIT 5
#define ONE_SHOT_BIT 2

//Only to have the default data also here
#define REG_ADDR_DEFAULT_VALUE 0x00
#define REG_T_HIGH_DEFAULT_VALUE 0x7F
#define REG_T_LOW_DEFAULT_VALUE 0x80
#define REG_CONFIG_DEFAULT_VALUE 0x40

int open_bus(void);
int close_bus(void);

//READ and WRITE with logic
int configure_sensor(int operation_mode, int alert_mode);
void read_temperature_oneshot(unsigned char* buffer);

//READ on single registers
unsigned char read_configuration(void);
unsigned char read_temp_high(void);
unsigned char read_temp_low(void);
void read_temperature(unsigned char* buffer);
unsigned char read_register(unsigned char address);

//SET on single registers
int set_temp_high(unsigned char buf);
int set_temp_low(unsigned char buf);
int set_configuration(unsigned char buf);
int write_register(unsigned char address, unsigned char data);

//ATOMIC OPERATIONS
int sensor_write_one_byte(unsigned char* buf);
int sensor_read_one_byte(unsigned char* buf);
int sensor_write_two_bytes(unsigned char* buf);
int sensor_read_two_bytes(unsigned char* buf);

//BIT OPERATIONS
unsigned char change_bit_byte(unsigned char number, unsigned char bit_position, int value);