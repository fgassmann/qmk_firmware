dprintf("changing light\n");
                i2c_status_t i2c_status = i2c_start(PCF8575_ADDR, I2C_TIMEOUT);

                if (i2c_status == I2C_STATUS_ERROR){dprintf("error init\n");}
                if (i2c_status == I2C_STATUS_TIMEOUT){dprintf("timeout init\n");}

                if (out_high){
                    uint8_t all_low = 0;
                    i2c_status = i2c_transmit(PCF8575_ADDR, &all_low, 1, I2C_TIMEOUT);
                    out_high =false;
                }
                else{
                    uint8_t all_high = 0b11111111;
                    i2c_status = i2c_transmit(PCF8575_ADDR, &all_high, 1, I2C_TIMEOUT);
                    out_high =true;
                }
                if (i2c_status == I2C_STATUS_ERROR){dprintf("error init\n");}
                if (i2c_status == I2C_STATUS_TIMEOUT){dprintf("timeout init\n");}

                i2c_stop();
                dprintf("Send to PCF8575 (%d) \n", i2c_status);
