
//Wi-Fi��Ϣ����
typedef struct INFO
{
	int num_1;
	int num_2;
	int num_3;
	int vol_1;
	int vol_2;
	int vol_3;
}INFO;


typedef struct CONINFO
{
	bool needControl;		//�Ƿ���п���
	volatile double target;		//���Ƶ�Ŀ��ֵ
	volatile double nowflow;		//ʵʱĿ��ֵ
	int pipNum;			//����Ŀ��Ĺܵ������ڴ��ж�
	int pipOpenKey;		//����Ŀ�꿪�����ź�
	volatile int finish;		//�����Ƿ����
};


typedef struct CONFIG
{
	int num;
	double flow;
	int pip;
	int switchKey;
};

typedef struct PIPCONFIG
{
	//int control;	//�Ƿ���п��Ʊ�־
	volatile double flow;	//ʵʱ����
	volatile bool state;	//����״̬
};