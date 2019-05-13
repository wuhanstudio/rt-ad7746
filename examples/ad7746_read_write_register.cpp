#include <rtthread.h>
#include <stdlib.h>
#include <AD7746.h>

#ifndef AD7746_I2C_NAME
    #define AD7746_I2C_NAME "i2c2"
#endif

static unsigned char c[2];

static void ad7746_read(int argc,char *argv[])
{
    rt_kprintf("%c\n", argc);
    if(argc < 2)
    {
        rt_kprintf("Usage: ad7746_read [subaddr]\n");
        return;
    }
    AD7746 ad7746;
    rt_uint8_t addr = atoi(argv[1]);
    ad7746.begin(AD7746_I2C_NAME);
    c[0] = 0;
    c[1] = 0;
    ad7746.read(addr, c, 1);
    rt_kprintf("Reading from %d:%02X\n", addr, c[0]);
}
MSH_CMD_EXPORT(ad7746_read, ad7746 read command);

static void ad7746_write(int argc,char *argv[])
{
    if(argc < 3)
    {
        rt_kprintf("Usage: ad7746_write [subaddr] [data] \n");
        return;
    }
    AD7746 ad7746;
    rt_uint8_t addr = atoi(argv[1]);
    ad7746.begin(AD7746_I2C_NAME);
    c[0] = atoi(argv[2]);
    c[1] = 0;
    ad7746.write(addr, c, 1);
    rt_kprintf("Writing to %d:%02X\n", addr, c[0]);
}
MSH_CMD_EXPORT(ad7746_write, ad7746 write command);
