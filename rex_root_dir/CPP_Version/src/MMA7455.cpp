
#include "MMA7455.h"

bool MMA7455 :: begin(){
	slave.init_device(I2CBUS, I2CADDR);
	char buffer[2];
	buffer[0] = MMA_MCTL;
	buffer[1] = 0b0001;
	return slave.accept(buffer, 2);
}

bool MMA7455 :: end(){
	char buffer[2];
        buffer[0] = MMA_MCTL;
        buffer[1] = 0;
        return slave.accept(buffer, 2);
}

int MMA7455 :: acc_x(){
	char buffer[2];
	bool dir = false; // false --> positive, true --> negative
	slave.reveal(MMA_XOUT10, 2, buffer);
	if (buffer[1] & 0x02)
		dir = true;
	int value = buffer[0];
	if(dir)
		return (-1 * value);
	return value;
}

int MMA7455 :: acc_y(){
	char buffer[2];
        bool dir = false; // false --> positive, true --> negative
        slave.reveal(MMA_YOUT10, 2, buffer);                      
        if (buffer[1] & 0x02)                                     
                dir = true;                 
        int value = (buffer[1] & 0x01) * 128 + buffer[0];
        if(dir)                                          
                return (-1 * value);                     
        return value;
}

int MMA7455 :: acc_z(){
	char buffer[2];             
        bool dir = false; // false --> positive, true --> negative
        slave.reveal(MMA_YOUT10, 2, buffer);                      
        if (buffer[1] & 0x02)                                     
                dir = true;                                       
        int value = (buffer[1] & 0x01) * 128 + buffer[0];         
        if(dir)                                                   
                return (-1 * value);                     
        return value;
}
