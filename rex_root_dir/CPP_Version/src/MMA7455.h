#ifndef MMA7455_H_
#define MMA7455_H_

#include "i2c-common.h"

#define I2CBUS 2
#define I2CADDR 0x1d
#define MMA_XOUT10 0x00
#define MMA_YOUT10 0x02
#define MMA_ZOUT10 0x04
#define MMA_XOUT8 0x06
#define MMA_YOUT8 0x07
#define MMA_ZOUT8 0x08
#define MMA_STATUS 0x09 // Status Register (Read only)
#define MMA_DRDY_bit (1<<0) // 1: Data is ready
#define MMA_DOVR_bit (1<<1) // 1: Data is over written
#define MMA_PERR_bit (1<<2) // 1: Parity error is detected in trim data
#define MMA_I2CAD 0x0d // I2C Device Address
#define MMA_I2CDIS_bit (0<<7) // 0: is enable , 1: I2C is disabled
#define MMA_WhoAMi 0x0F // Who am i value
#define MMA_XOFFL 0x10 // Offset Drift X LSB
#define MMA_YOFFL 0x12 // Offset Drift Y LSB
#define MMA_ZOFFL 0x14 // Offset Drift Z LSB
#define MMA_MCTL 0x16 // Mode Control Register
#define MMA_CTL1 0x18 // Control 1
#define MMA_CTL2 0x19 // Control 2
#define MMA_DFBW_bit (1<<7) // Digital filter band width (0: 62.5 Hz, 1: 125 Hz)

class MMA7455{
private:
	SlaveDevice slave;
public:
	bool begin();
	bool end();
	int acc_x();
	int acc_y();
	int acc_z();

};

#endif
