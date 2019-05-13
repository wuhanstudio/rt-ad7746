#include "AD7746.h"

AD7746::AD7746()
{
    devAddr = AD7746_ADDRESS;
};

AD7746::AD7746(uint8_t address)
{
    devAddr = address;
}

rt_bool_t AD7746::begin(const char* bus_name)
{
    i2c_bus = rt_i2c_bus_device_find(bus_name);
    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("[AD7746] Failed to find bus %s\n", bus_name);
        return RT_ERROR;
    }
    return RT_EOK;
};

rt_uint8_t AD7746::reset()
{
    unsigned char cmd[2];

    cmd[0] = AD7746_RESET_CMD;

    struct rt_i2c_msg msgs;

    msgs.addr = AD7746_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf = cmd;
    msgs.len = 1;

    if (rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

// Read from Register
rt_uint8_t AD7746::read(unsigned char subAddr,
                unsigned char* dataBuffer,
                unsigned char bytesNumber)
{

    struct rt_i2c_msg msgs[2];

    msgs[0].addr = AD7746_ADDRESS;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = &subAddr;
    msgs[0].len = 1;

    msgs[1].addr = AD7746_ADDRESS;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = dataBuffer;
    msgs[1].len = bytesNumber;

    if (rt_i2c_transfer(i2c_bus, msgs, 2) == 2)
    {
        return bytesNumber;
    }
    else
    {
        return 0;
    }
};

// Write to Register
rt_uint8_t AD7746::write(unsigned char subAddr,
                unsigned char* dataBuffer,
                unsigned char bytesNumber)
{
    unsigned char sendBuffer[10] = {0, };
    unsigned char byte = 0;

    sendBuffer[0] = subAddr;
    for(byte = 1; byte <= bytesNumber; byte++)
    {
        sendBuffer[byte] = dataBuffer[byte - 1];
    }

    struct rt_i2c_msg msgs;

    msgs.addr = AD7746_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf = sendBuffer;
    msgs.len = bytesNumber + 2;

    if (rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
    {
        return bytesNumber;
    }
    else
    {
        return 0;
    }
};

unsigned long AD7746::getVTData(void)
{
    unsigned char receiveBuffer[3] = {0, 0, 0};
    unsigned long vtData = 0;

    receiveBuffer[0] = AD7746_STATUS_RDYVT;
    while(!(receiveBuffer[0] & AD7746_STATUS_RDYVT))
    {
        read(AD7746_REG_STATUS,
            receiveBuffer,
            1);
    }
    read(AD7746_REG_VT_DATA_HIGH,
            receiveBuffer,
            3);
    vtData = ((unsigned long)receiveBuffer[0] << 16) +
             ((unsigned short)receiveBuffer[1] << 8) +
             receiveBuffer[0];

    return vtData;
};

unsigned long AD7746::getCapData(void)
{
    unsigned char receiveBuffer[3] = {0, 0, 0};
    unsigned long capData = 0;

    receiveBuffer[0] = AD7746_STATUS_RDYCAP;
    while(!(receiveBuffer[0] & AD7746_STATUS_RDYCAP))
    {
        read(AD7746_REG_STATUS,
                receiveBuffer,
                1);
    }
    read(AD7746_REG_CAP_DATA_HIGH,
                receiveBuffer,
                3);
    capData = ((unsigned long)receiveBuffer[0] << 16) +
              ((unsigned short)receiveBuffer[1] << 8) +
              receiveBuffer[0];

    return capData;
};
