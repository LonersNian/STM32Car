#include "track.h"

/**
* ѭ������
* ������ģ��,
    PD11 ��
    PD12 ��
    PD13 ��
* �Ǻ���,���յ������   ��D0���ŵ͵�ƽ->0
* ����,δ���յ������   ��D0���Ÿߵ�ƽ->1
*/


//����ģ�鷵��ֵ
u16 Track_Input=0;


//brief:�������ģ�����ϰ���
void Track_explore(void)
{
    Track_Input=0;
    Track_Input=(((u16)GPIOD->IDR) & 0X3800)>>11 ;    //ȡ��PD11��12��13��λ
}

//// ����ѭ�����
////-----------------------------------------------------------------
//#define		No_BLACK                0x07	// δ���ֺ���     111
//#define		Middle_BLACK		    0x05	// �м䷢�ֺ���   101
//#define		Left_BLACK			    0x06	// ��߷��ֺ���   110
//#define		Left_Middle_BLACK   	0x04	// ���в෢�ֺ��� 100
//#define		Right_BLACK             0x03	// �ұ߷��ֺ���   011 
//#define		Right_Middle_BLACK      0x01	// ���в෢�ֺ��� 001
//#define		Left_Right_BLACK		0x02	// ���Ҳⷢ�ֺ��� 010
////-----------------------------------------------------------------


//    void Stop(void);
//    void Turnfoward(void);
//    void Turnback(void);
//    void Turnleft(void);
//    void Turnright(void);

//ѭ�����ƺ���
void Track_control(void)
{
	delay_init(168);        //��ʼ����ʱ����
    switch(Track_Input)
      {
        case Middle_BLACK:  //�м䷢�ֺ���
            Turnfoward();   //ǰ��
            break;
        case Right_BLACK:   // �ұ߷��ֺ���    
        case Right_Middle_BLACK:
            Turnright();    //��ת
            break;
        case Left_BLACK:    // ��߷��ֺ���   
        case Left_Middle_BLACK:
            Turnleft();     //��ת
            break;
        default:            //�������������̧��
            Stop();         //ֹͣ
      }
}
                        
    
    
    
    
