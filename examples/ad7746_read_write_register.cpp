#include <rtthread.h>
#include <stdlib.h>
#include <string.h>
#include <AD7746.h>

#ifndef AD7746_I2C_NAME
    #define AD7746_I2C_NAME "i2c2"
#endif

static unsigned char c[2];

static void ad7746_read(int argc,char *argv[])
{
    AD7746 ad7746;
    rt_uint8_t addr = atoi(argv[1]);
    if(argc < 2)
    {
        rt_kprintf("Usage: ad7746_read [subaddr]\n");
        rt_kprintf("Example: ad7746_read 0x0A\n");
        rt_kprintf("Example: ad7746_read 10\n");
        return;
    }

    if (strcmp(argv[1], "0x"))
    {
      addr = (rt_uint8_t)strtol(argv[1], NULL, 0);
    }
    else 
    {
      addr = atoi(argv[1]);
    }
    
    ad7746.begin(AD7746_I2C_NAME);
    c[0] = 0;
    c[1] = 0;
    ad7746.read(addr, c, 1);
    rt_kprintf("Reading from %d:%02X\n", addr, c[0]);
}
MSH_CMD_EXPORT(ad7746_read, ad7746 read command);

static void ad7746_write(int argc,char *argv[])
{
    AD7746 ad7746;
    rt_uint8_t addr, data;
    if(argc < 3)
    {
        rt_kprintf("Usage  : %s [subaddr] [data] \n", argv[0]);
        rt_kprintf("Example: %s 0x0A 0x1B \n", argv[0]);
        rt_kprintf("Example: %s   10 0x1B \n", argv[0]);
        rt_kprintf("Example: %s   10   27 \n", argv[0]);
        return;
    }

    if (strcmp(argv[1], "0x"))
    {
      addr = (rt_uint8_t)strtol(argv[1], NULL, 0);
    }
    else
    {
      addr = atoi(argv[1]);
    }

    if( strcmp(argv[2], "0x"))
    {
      data = (rt_uint8_t)strtol(argv[2], NULL, 0);
    }
    else
    {
      data = atoi(argv[2]);
    }

    ad7746.begin(AD7746_I2C_NAME);
    c[0] = data;
    c[1] = 0;
    ad7746.write(addr, c, 1);
    rt_kprintf("Writing to %d:%02X\n", addr, c[0]);
}
MSH_CMD_EXPORT(ad7746_write, ad7746 write command);
