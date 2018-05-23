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
	WIFISTATE.isOpen = true;
	WIFISTATE.isAllowSend = SEND_ALLOWED;
	return true;
}



bool sendData(int data) {
	//----TODO 将所有的发送命令统一到一起，方便统一管理

	/*Serial.print("send:");
	Serial.println(String(data));*/
	return sendString(String(data));

}

String recvString() {
	char a;
	String tmp_recv = "";
	//if (Serial1.available())
	//{
	//Serial.print("Serial1.available:  ");
		while (Serial1.available())
		{
			//Serial.print(Serial1.available());
			//Serial.print("-");
			a = Serial1.read();
			if (a == '\0' || a == '\n' || a == '\r') continue;
			tmp_recv = tmp_recv + a;
			delay(2);
		}
		//Serial.println(tmp_recv);	
	//}
		Look();
		//Serial1.flush();
	return tmp_recv;
}

bool sendString(String sysdata) {
	bool flag;
	Serial1.print(F("AT+CIPSEND=0,"));
	Serial1.println(sysdata.length());
	if (Serial1.find(">")) //healthy response
	{
		Serial.print("ready to send-->");
		Serial.print(sysdata);
		delay(5);
		Serial1.println(sysdata);
		sysdata = "";
	}
	if (Serial1.find("OK")) //healthy response
	{
		Serial.println("-->SEND OK");
		return true;
	}else return  false;
	
}

void Look() {
	//Serial1.print(F("AT+CIPSTATUS"));
	//Serial1.println(F("AT+CWMODE_CUR?"));
	//Serial1.println(F("AT+CIPBUFSTATUS  =0"));
}