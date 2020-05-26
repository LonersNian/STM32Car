#include "track.h"

/**
* ѭ������
* ������ģ��,
    PE2 ��
    PE1 ��
    PE0 ��
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


// ����ѭ�����
//---------------------------------------------------------------------
#define		Not_Black		    	0x00	// δ���ֺ���
#define		Middle_Black			0x02	// �м䷢�ֺ���
#define		Left_Black		        0x01	// ��෢�ֺ���
#define		Left_Middle_Black	    0x03	// ���в෢�ֺ���
#define		Right_Black			    0x04	// �Ҳ෢�ֺ���
#define		Right_Middle_Black	    0x06	// ���в෢�ֺ���
#define		Left_Right_Black		0x05	// ���Ҳ෢�ֺ���
#define		All_Black   			0x07	// ȫ�����ֺ���
//-----------------------------------------------------------------------------------


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
        case Middle_Black:  //�м䷢�ֺ���
            Turnfoward();   //ǰ��
            break;
        case Right_Black:   // �ұ߷��ֺ���    
        case Right_Middle_Black:
            Turnright();    //��ת
            break;
        case Left_Black:    // ��߷��ֺ���   
        case Left_Middle_Black:
            Turnleft();     //��ת
            break;
        default:            //�������������̧��
            Stop();         //ֹͣ
      }
}
                        
    
    
    
    
