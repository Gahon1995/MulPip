bool init_WIFI() {
	Serial1.println(F("AT"));
	if (Serial1.find("OK")) //healthy response
	{
		Serial.println("AT is OK");
		// return true;
	}
	else
	{
		Serial.println("AT is failed");
		return false;
	}
	Serial1.println(F("AT+RST"));
	if (Serial1.find("OK")) //healthy response
	{
		Serial.println("AT + RST is OK");
		// return true;
	}
	else
	{
		Serial.println("AT + RST is failed");
		return false;
	}
	  //Serial1.println(F("AT+UART=9600,8,1,0,0"));
	  //if (Serial1.find("OK")) //healthy response
	  //{
	  //  Serial.println("AT+UART=9600,8,1,0,0 is OK");
	  //  // return true;
	  //}
	  //else
	  //{
	  //  Serial.println("AT+UART=9600,8,1,0,0 is failed");
	  //  //return false;
	  //}
	//Serial1.begin(115200);
	  Serial1.print(F("AT+CWMODE_CUR=3\r\n"));
	delay(100);
	Serial1.print("AT+CWSAP=\"HAN_ARD\",\"\",1,0,4,0\r\n");
	delay(1000);
	if (Serial1.find("OK")) //healthy response
	{
		Serial.println("name config is OK");
		//return true;
	}
	else
	{
		Serial.println("name config is failed");
		// return false;
	}
	Serial1.println(F("AT+CIPMUX=1"));
	if (Serial1.find("OK")) //healthy response
	{
		Serial.println("AT+CIPMUX=1 is OK");
		//return true;
	}
	else
	{
		Serial.println("AT+CIPMUX=1 is failed");
		 return false;
	}
	Serial1.println(F("AT+CIPSERVER=1,8086"));
	delay(2);
	if (Serial1.find("OK")) //healthy response
	{
		Serial.println("AT+CIPSERVER=1,8086 is OK");
		//return true;
	}
	else
	{
		Serial.println("AT+CIPSERVER=1,8086 is failed");
		 return false;
	}
	//WIFISTATE.isOpen = true;
	WIFISTATE.isAllowSend = SEND_ALLOWED;
	return true;
}

bool sendData(int data) {
	return sendString(String(data), WIFISTATE.connectedId);
}

bool sendData(int data,int id) {
	return sendString(String(data),id);
}

String recvString() {
	char a;
	String tmp_recv = "";
		while (Serial1.available())
		{

			a = Serial1.read();
			if (a == '\0' || a == '\n' || a == '\r') continue;
			tmp_recv = tmp_recv + a;
			delay(2);
		}

	return tmp_recv;
}

bool sendString(String sysdata,int id) {
	bool flag;
	Serial1.print(F("AT+CIPSEND="));
	Serial1.print(id);
	Serial1.print(F(","));
	Serial1.println(sysdata.length());
	if (Serial1.find(">")) //healthy response
	{
		Serial.print("ready to send code--> ");
		Serial.print(sysdata);
		delay(5);
		Serial1.println(sysdata);
		sysdata = "";
	}
	if (Serial1.find("OK")) //healthy response
	{
		Serial.println(" -->SEND OK");
		return true;
	}else return  false;
	
}

void disConnect() {
	//TODO ��ӶϿ����ӷ���
}


void Look() {
	//Serial1.print(F("AT+CIPSTATUS"));
	//Serial1.println(F("AT+CWMODE_CUR?"));
	//Serial1.println(F("AT+CIPBUFSTATUS  =0"));
}