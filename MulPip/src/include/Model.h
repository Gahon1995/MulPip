struct 
{
	volatile bool isOpen=false;
	bool isConnected = false;
	int connectedId = -1;
	volatile int isAllowSend= 200;	//SEND_REJECT
}WIFISTATE;


//Wi-Fi��Ϣ����
struct WIFIDATA
{
	
	int num_1;
	int num_2;
	int num_3;
	int vol_1;
	int vol_2;
	int vol_3;
};


struct CONINFO
{
	bool needControl;		//�Ƿ���п���
	volatile double target;		//���Ƶ�Ŀ��ֵ
	volatile double nowflow;		//ʵʱĿ��ֵ
	int pipNum;			//����Ŀ��Ĺܵ������ڴ��ж�
	int pipOpenKey;		//����Ŀ�꿪�����ź�
	volatile int finish;		//�����Ƿ����
	void (*countFunction)(void);
	volatile long lastCount;
};


struct DISCONFIG
{
	volatile double _1_target;		//���Ƶ�Ŀ��ֵ
	volatile double _1_nowflow;		//ʵʱĿ��ֵ
	volatile int    _1_finish;		//�����Ƿ����
	volatile double _2_target;		//���Ƶ�Ŀ��ֵ
	volatile double _2_nowflow;		//ʵʱĿ��ֵ
	volatile int    _2_finish;		//�����Ƿ����
	volatile double _3_target;		//���Ƶ�Ŀ��ֵ
	volatile double _3_nowflow;		//ʵʱĿ��ֵ
	volatile int    _3_finish;		//�����Ƿ����
};

struct PIPCONFIG
{
	//int control;	//�Ƿ���п��Ʊ�־
	volatile double flow;	//ʵʱ����
	volatile bool state;	//����״̬
	volatile double step;
};

