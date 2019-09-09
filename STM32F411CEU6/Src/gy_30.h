#ifndef GY_30_C_
#define GY_30_C_

//#define FY-30_ADDR_L 0b0100011	//when addr pin is low
//#define FY-30_ADDR_H 0b1011100	//when addr pin is high
//#define GY_30_ADDR 0b101110000
#define GY_30_ADDR 0x46

#define ONE_RIME_H_MODE		0b00100000
#define ONE_RIME_H_MODE2	0b00100001
#define ONE_RIME_L_MODE		0b00100011

extern void gy_30_test(void);

#endif /* GY_30_C_ */
