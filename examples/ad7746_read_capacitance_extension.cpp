#include <rtthread.h>
#include <stdlib.h>
#include <AD7746.h>

#ifndef AD7746_I2C_NAME
    #define AD7746_I2C_NAME "i2c2"
#endif

static unsigned char c[2];

static void ad7746_read_capacitance_extension(int argc,char *argv[])
{
    // Initialization
    AD7746 ad7746;
    ad7746.begin(AD7746_I2C_NAME);

    // Setup Cap
    c[0] = 0x81;
    ad7746.write(AD7746_REG_CAP_SETUP, c, 1);

    // Setup Excitation
    c[0] = 0x1B;
    ad7746.write(AD7746_REG_EXC_SETUP, c, 1);

    // Setup Sample
    c[0] = 0xA1;
    ad7746.write(AD7746_REG_CFG, c, 1);

    // Print Capacitance
    for(int i = 0; i< 5; i++)
    {
        rt_kprintf("\nCurrent Capacitance Percentage: %lu%\n", (ad7746.getCapData() - 8388608) * 100 / 8388608);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(ad7746_read_capacitance_extension, ad7746 read capacitance with extension example);
