#ifndef _MMA7455_H_
#define _MMA7455_H_
#define   uchar unsigned char
#define   uint unsigned int	

#define	MMA7455_SlaveAddress	0x1D	//IIC写入时的地址 
#define IIC_READ  						((0x1D << 1) | 0x01)  //定义读指令
#define IIC_WRITE 						(0x1D << 1)  //定义写指令
//************************************
/*模拟IIC端口输出输入定义*/
#define SCL_H         GPIO_SetBits(GPIOF,GPIO_Pin_1) //GPIOB->BSRR = GPIO_Pin_3
#define SCL_L         GPIO_ResetBits(GPIOF,GPIO_Pin_1) //GPIOB->BRR  = GPIO_Pin_3 
   
#define SDA_H         GPIO_SetBits(GPIOF,GPIO_Pin_0)//GPIOA->BSRR = GPIO_Pin_15
#define SDA_L         GPIO_ResetBits(GPIOF,GPIO_Pin_0)//GPIOA->BRR  = GPIO_Pin_15

#define SCL_read      GPIOF->IDR  & GPIO_Pin_1
#define SDA_read      GPIOF->IDR  & GPIO_Pin_0

void MMA7455_data_init(void);
uint8_t MMA7455_self_test7455(void);
void MMA7455_sendxyz(void);

#endif
