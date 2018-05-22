//获取将target占用的字符空间调整为统一个5个大小
int getDis(int target, int len_space) {
	int dis = 0;
	if (target >= 100.0) {
		dis = 0;
	}
	else if (target >= 10 && target < 100) {
		dis = len_space * 1;
	}
	else {
		dis = len_space * 2;
	}
	return dis;
}

bool is0or1(int i) {
	return i == 0 || i == 1;
}

bool isNormal(double value) {
	return value<VOL_MAX&&value>VOL_MIN;
}

bool checkData() {
	if (is0or1(wifidata.num_1) && is0or1(wifidata.num_2) && is0or1(wifidata.num_3))
		if (isNormal(wifidata.vol_1) && isNormal(wifidata.vol_2) && isNormal(wifidata.vol_3))
			return true;
	return false;
}

//向串口输出接收到的信息，用于调试
void printConfig() {
	Serial.print("num_1: ");
	Serial.println(wifidata.num_1);
	Serial.print("num_2: ");
	Serial.println(wifidata.num_2);
	Serial.print("num_3: ");
	Serial.println(wifidata.num_3);
	Serial.print("vol_1: ");
	Serial.println(wifidata.vol_1);
	Serial.print("vol_2: ");
	Serial.println(wifidata.vol_2);
	Serial.print("vol_3: ");
	Serial.println(wifidata.vol_3);
}
