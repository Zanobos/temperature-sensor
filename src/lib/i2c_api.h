/* Performs I2C bus initialization. Must be performed prior to reading from or
writing to any devices on the bus. Returns less than 0 on error.*/
int i2c_open(void);

/* Performs a single I2C write transaction from ‘buf’ of ‘size’ bytes to device ‘addr’ on
a common I2C bus. Returns less than 0 on failed transactions, number of bytes
written on success. */
int i2c_write(char *buf, int size, char device_addr);

/* Performs a single I2C read transaction of ‘size’ bytes and copies read data into the
provided ‘buf’ buffer. Buffer must be large enough to store ‘size’ bytes. Returns less
than 0 on failed transactions, number of bytes read on success. */
int i2c_read(char *buf, int size, char device_addr);

/* Performs I2C bus cleanup. Must be performed after reading from or writing to
any devices on the bus. Returns less than 0 on error. */
int i2c_close(void);