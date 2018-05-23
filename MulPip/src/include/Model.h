struct 
{
	volatile bool isOpen=false;
	bool isConnected = false;
	int connectedId = -1;
	volatile int isAllowSend= 201;	//SEND_REJECT
}WIFISTATE;


//Wi-Fi��Ϣ����
typedef struct WIFIDATA
{
	
	int num_1;
	int num_2;
	int num_3;
	int vol_1;
	int vol_2;
	int vol_3;
};


typedef struct CONINFO
{
	bool needControl;		//�Ƿ���п���
	volatile double target;		//���Ƶ�Ŀ��ֵ
	volatile double nowflow;		//ʵʱĿ��ֵ
	int pipNum;			//����Ŀ��Ĺܵ������ڴ��ж�
	int pipOpenKey;		//����Ŀ�꿪�����ź�
	volatile int finish;		//�����Ƿ����
};


//typedef struct CONFIG
//{
//	int num;
//	double flow;
//	int pip;
//	int switchKey;
//};

typedef struct PIPCONFIG
{
	//int control;	//�Ƿ���п��Ʊ�־
	volatile double flow;	//ʵʱ����
	volatile bool state;	//����״̬
};