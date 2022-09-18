#include "pwm.h"
#include "headfile.h"


//#define  MAX_PWM 2500  //400hz    ����2.5ms
#define  MAX_PWM 20000  //50hz  ����20ms

void PWM_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//��ʼTIM4 ��ʱ�� ��GPIOBʱ�� ��AFIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//��ʱ��3��ΪPWM���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	//����PA5��PA6��PB0��PB1 Ϊ�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_1;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�������
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

    uint16_t prescalerValue = 0, ccr1_PWMVal = 0;
	PWM_GPIO_Init();
	prescalerValue = (u16) (SystemCoreClock / 1000000)-1;//10us
	//-----TIM3��ʱ����-----//
	TIM_TimeBaseStructure.TIM_Period = MAX_PWM;		//40000/2M=20ms-->50Hz����0��ʼ����,���ֵ��д�뵽Auto-Reload Register��
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	       //��ʱ����Ƶ
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;	       //ʱ�ӷָ�
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	//�ظ��Ƚϴ��������¼�
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_PrescalerConfig(TIM3, prescalerValue, TIM_PSCReloadMode_Immediate);//Ԥ��Ƶ,���ڼ�ʱ��Ƶ��Ϊ20MHz

		//-----PWM����-----//
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ1-->���ϼ���Ϊ��Ч��ƽ
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = ccr1_PWMVal;					//duty cycle
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 	//�������:TIM����Ƚϼ��Ը�

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  					//��ʼ������TIM3 OC1-->Motor1
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  					//��ʼ������TIM3 OC2-->Motor2
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  					//��ʼ������TIM3 OC3-->Motor3
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  					//��ʼ������TIM3 OC4-->Motor4


   	TIM_ARRPreloadConfig(TIM3, ENABLE);//�Զ����ؼĴ���ʹ�ܣ���һ�������¼��Զ�����Ӱ�ӼĴ���
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���,�ڸ����¼�ʱ��ֵ�ű�д�뵽CCR


        TIM_Cmd(TIM3, ENABLE);
        PWM_Set(1000,1000,1000,1001);
}


void PWM2_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

    uint16_t prescalerValue = 0, ccr1_PWMVal = 0;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//��ʱ��2��ΪPWM���
	
	prescalerValue = (u16) (SystemCoreClock / 1000000)-1;//10us
	//-----TIM2��ʱ����-----//
	TIM_TimeBaseStructure.TIM_Period = MAX_PWM;		//40000/2M=20ms-->50Hz����0��ʼ����,���ֵ��д�뵽Auto-Reload Register��
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	       //��ʱ����Ƶ
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;	       //ʱ�ӷָ�
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	//�ظ��Ƚϴ��������¼�
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
TIM_PrescalerConfig(TIM2, prescalerValue, TIM_PSCReloadMode_Immediate);//Ԥ��Ƶ,���ڼ�ʱ��Ƶ��Ϊ20MHz
	

		//-----PWM����-----//
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ1-->���ϼ���Ϊ��Ч��ƽ
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = ccr1_PWMVal;					//duty cycle
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 	//�������:TIM����Ƚϼ��Ը�

TIM_OC2Init(TIM2, &TIM_OCInitStructure);  					//��ʼ������TIM3 OC1-->Motor1


TIM_ARRPreloadConfig(TIM2, ENABLE);

TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	
TIM_Cmd(TIM2, ENABLE);

TIM_SetCompare2(TIM2, 1000);						//************************************************************************	
        
}

/***********************************************************************************
��������void PWM_Set(const u16 pwm1, const u16 pwm2, const u16 pwm3, const u16 pwm4)
˵����PWM�������
��ڣ��ĸ�ͨ����ֵ
���ڣ���
��ע����ռ��Ϊ2.5ms��20ms��    1000<=pwm<=2000
************************************************************************************/
void PWM_Set(const uint16_t pwm1, const uint16_t pwm2, const uint16_t pwm3, const uint16_t pwm4)
{
	TIM_SetCompare1(TIM3, pwm1);
	TIM_SetCompare2(TIM3, pwm2);
	TIM_SetCompare3(TIM3, pwm3);
	TIM_SetCompare4(TIM3, pwm4);
}