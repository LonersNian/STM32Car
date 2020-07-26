#include "elude.h"

/**
* ���Ϲ���
* ������ģ��,
    PD11 ��
    PD12 ��
    PD13 ��
* ���ϰ���,���յ������   ��out���ŵ͵�ƽ->0
* ���ϰ���,δ���յ�����⣺out���Ÿߵ�ƽ->1
*/


//����ģ�鷵��ֵ
u16 Elude_Input=0;


//brief:�������ģ�����ϰ���
void Elude_explore(void)
{
    Elude_Input=0;
    Elude_Input=(((u16)GPIOD->IDR) & 0X3800)>>11 ;    //ȡ��PD11��12��13��λ
}

#define		No_Block                0x07	// δ�����ϰ�     111
#define		Middle_Block		    0x05	// �м䷢���ϰ�   101
#define		Left_Block			    0x06	// ��߷����ϰ�   110
#define		Left_Middle_Block   	0x04	// ���в෢���ϰ� 100
#define		Right_Block             0x03	// �ұ߷����ϰ�   011 
#define		Right_Middle_Block      0x01	// ���в෢���ϰ� 001
#define		Left_Right_Block		0x02	// ���Ҳⷢ���ϰ� 010
#define		All_Block               0x00	// ȫ�������ϰ�   000

//    void Stop(void);
//    void Turnfoward(void);
//    void Turnback(void);
//    void Turnleft(void);
//    void Turnright(void);

//ѭ�����ƺ���
void Elude_control(void)
{
	delay_init(168);               	//��ʼ����ʱ����
    switch(Elude_Input)
      {
        case No_Block:      //û���ϰ�
            Turnfoward();   //ǰ��
            break;
        case Middle_Block:  //�м��ȫ�������ϰ�
        case All_Block:
        case Left_Right_Block: //���෢���ϰ��������ڹս�
            Turnback();     //�Ⱥ���
            delay_ms(500);
        
            Turnleft();     //����ת
            delay_ms(500);

            break;
        case Right_Block:   // �ұ߷����ϰ�    
        case Right_Middle_Block:
            Turnleft();     //��ת
            break;
        case Left_Block:    // ��߷����ϰ�    
        case Left_Middle_Block:
            Turnright();    //��ת
            break;
        default:            //�������
            Turnfoward();   //ǰ��
      }
}
                        
    
    
    
    
