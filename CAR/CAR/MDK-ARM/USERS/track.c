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



u16 Track_Input=0;              //����ģ�鷵��ֵ
u16 Not_Find_Black_flag =0;   //��ʱ���ж�ʱ���־λ������ͣ���ж�
u8  Stop_Flag=0;                 //ͣ����־λ��5sδ��⵽����ʱΪ1.

//brief:�������ģ�����ϰ���
void Track_explore(void)
{
    Track_Input=0;
    Track_Input=(((u16)GPIOE->IDR) & 0X07) ;    //ȡ��PE0��1��2��λ
}


// ����ѭ�����
//---------------------------------------------------------------------
//#define		Not_Black		    	0x00	// δ���ֺ���
//#define		Middle_Black			0x02	// �м䷢�ֺ���
//#define		Left_Black		        0x01	// ��෢�ֺ���
//#define		Left_Middle_Black	    0x03	// ���в෢�ֺ���
//#define		Right_Black			    0x04	// �Ҳ෢�ֺ���
//#define		Right_Middle_Black	    0x06	// ���в෢�ֺ���
//#define		Left_Right_Black		0x05	// ���Ҳ෢�ֺ���
//#define		All_Black   			0x07	// ȫ�����ֺ���
//-----------------------------------------------------------------------------------


//    void Stop(void);
//    void Turnfoward(void);
//    void Turnback(void);
//    void Turnleft(void);
//    void Turnright(void);


//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//   if(htim==(&htim2))
//    {
//        LED0=!LED0;        //LED1��ת,�����ж���
//    }
//}


/*
* brief:    δ���ֺ���
*           5s��̽�ⲻ�����ߣ��Զ�ͣ����
*           tim2����Ϊ1ms,����5000��
* attention:����ͬʱ���жϻص�����
*/
void Not_Find_Black(void) 
{

 if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET)
    {
        if (__HAL_TIM_GET_IT_SOURCE(&htim2, TIM_IT_UPDATE) != RESET)
        {
				__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
	
                Not_Find_Black_flag ++;
            if(Not_Find_Black_flag >= 5000)		// δ���ֺ��߼�ʱ5��
            {
                Not_Find_Black_flag = 0;
                
                Stop_Flag = 1 ;		// ����ʱ��δ���ֺ��߱�־λ����1	
            }
        }
    }    

}
    


//ѭ�����ƺ���
void Track_control(void)
{
    if(Track_Input==Not_Black)
    {
        if(Stop_Flag==1)        //5sδ���ֺ���
        {
            Stop();                  //ֹͣ
        }
        else
            Turnfoward();
    }

    else        //���ֺ���
    {
        switch(Track_Input)
      {
        Stop_Flag=0;                //ֻҪ�к��߱�־λ������
        Not_Find_Black_flag=0;  
          
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
            Turnfoward();         //ֹͣ
      }
    }

}
         
