int recvWifiData() {
	//有信息，需要接收，然后处理
	String recv = "";
	int flag_RECV,flag_Data;
	String data="";
	flag_Data =getRightData(recv);

	if (flag_Data == 1) {
		initWiFiConfig();
		flag_RECV = formatData(recv);
		//flag = revData(); //接收信息，并且保存到config结构体中
		//printConfig(); //打印接收到的信息，供调试使用
		if (flag_RECV == FIND_STATUS) {
			sendData(WIFISTATE.isAllowSend);
		}
		if (WIFISTATE.isAllowSend == SEND_REJECT) {	//当前不允许接收数据
										//data=esp8266.recvString();
			sendData(SEND_REJECT);
			return STOP;
		}
		if (flag_RECV == RECV_WRONG) {
			sendData(RECV_WRONG);
		}
		else if (flag_RECV == RECV_SUCCESS && WIFISTATE.isAllowSend == SEND_ALLOWED) {
			sendData(RECV_SUCCESS);
			return START;
		}
		else if (flag_RECV == RECV_FAILD) {
			sendData(RECV_FAILD);
		}
			
	}
	return STOP;	
	/***********TODO --- 硬件复位，或者变量复位***********************/
}

int getRightData(String &recv) {
	String tmpdata="";
	int flag = 0;
	delay(1);
	tmpdata = recvString();
	Serial.print("data recv: ");
	Serial.println(tmpdata);
	if (tmpdata.indexOf("+IPD") != -1) {
		flag = 1;
		int pos = tmpdata.indexOf(":");
		/*Serial.print("':'pos:");
		Serial.println(pos);*/
		recv = tmpdata.substring(pos + 1, tmpdata.length());
	}
	else if (tmpdata.indexOf(",CONNECTED") != -1) {
		Serial.print("have connection: id = ");
		int id;
		id = tmpdata.toInt()  ;
		Serial.println(id);
		WIFISTATE.connectedId = id;
		WIFISTATE.isConnected = true;
	}
	return flag;
}


int formatData(String &recv) {
	//String data;
	int flagRecv;
	//flagRecv = getRightData(data);

	//esp8266.sendString(data);
	if ( recv != "") {
		const size_t bufferSize = JSON_OBJECT_SIZE(7) + 80;
		DynamicJsonBuffer jsonBuffer(bufferSize);

		/**************
		{"mode": 0,"num_1":1,"num_2":1,"num_3":1,"vol_1":23,"vol_2":34,"vol_3":132}
		
		******************/

		JsonObject& root = jsonBuffer.parseObject(recv);
		if (!root.success()) {
			//sendData(404);
			return RECV_FAILD; //接收错误
		}
		int mode = (int)root["mode"];
		if (mode == 0) return FIND_STATUS; //查询目前状态

		wifidata.num_1 = root["num_1"]; // 1
		wifidata.num_2 = root["num_2"]; // 0
		wifidata.num_3 = root["num_3"]; // 0
		wifidata.vol_1 = root["vol_1"]; // 125
		wifidata.vol_2 = root["vol_2"]; // 56
		wifidata.vol_3 = root["vol_3"]; // 19

		if (checkData()) {
			conPIP1.needControl = wifidata.num_1;
			conPIP1.target = wifidata.vol_1;

			conPIP2.needControl = wifidata.num_2;
			conPIP2.target = wifidata.vol_2;

			conPIP3.needControl = wifidata.num_3;
			conPIP3.target = wifidata.vol_3;
			return RECV_SUCCESS; //正确接收
		}
			
		return RECV_WRONG;
	}
	return 123;
}