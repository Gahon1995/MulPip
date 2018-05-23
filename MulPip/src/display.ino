struct DIS
{
	int MESSAGE = 20;
	int PIP1_Y = 34;
	int PIP2_Y = 48;
	int PIP3_Y = 62;
}DIS;	//显示屏各行的位置

void drawLogo() {
	//u8g2.clearDisplay();
	u8g2.clearBuffer();

	u8g2.setFont(u8g2_font_helvB12_tr);			//12px
	u8g2.drawStr(28, 25, "Multi-pipe");
	u8g2.setFont(u8g2_font_8x13B_tr);
	u8g2.drawStr(10, 40, "control system");  //8px
	u8g2.drawStr(20,62,"no connection...");
	u8g2.sendBuffer();
}

void drawCon() {
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_helvB12_tr);			//12px
	u8g2.drawStr(28, 25, "Multi-pipe");
	u8g2.setFont(u8g2_font_8x13B_tr);
	u8g2.drawStr(10, 40, "control system");  //8px
	u8g2.setCursor(20, 62);
	u8g2.print("connect id:");
	u8g2.print(WIFISTATE.connectedId);
	//u8g2.drawStr(20, 62, "connect id:");

	u8g2.sendBuffer();
}

void drawDisplay() {
	//u8g2.clearDisplay();
	//u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_8x13B_tr);	//10px
	u8g2.drawStr(40, 10, "STATUS: ");
	u8g2.setFont(u8g2_font_5x8_tr);		//6px
	u8g2.drawStr(0, DIS.MESSAGE, "n  state target      now");
	u8g2.setFont(u8g2_font_8x13B_tr);
	u8g2.drawStr(0, DIS.PIP1_Y, "1  ");
	u8g2.drawStr(0, DIS.PIP2_Y, "2  ");

	u8g2.drawStr(0, DIS.PIP3_Y, "3  ");
	//u8g2.sendBuffer();
}

void drawState() {
	//u8g2.clearDisplay();
	u8g2.clearBuffer();
	drawDisplay();
	u8g2.setFont(u8g2_font_8x13B_tr);
	int len_space = u8g2.getStrWidth(" ");

	if (conPIP1.finish == PIP_RUNNING) {
		u8g2.drawStr(len_space * 3/*len of "2 "*/, DIS.PIP1_Y,"O");
	}
	else u8g2.drawStr(len_space * 3/*len of "2 "*/, DIS.PIP1_Y, "X");
	
	u8g2.setCursor(len_space * 5/*len of "2 X "*/ + getDis(conPIP1.target, len_space), DIS.PIP1_Y);
	u8g2.print(conPIP1.target, 1);
	u8g2.setCursor(len_space * 11/*len of"1 O 116.3 "*/ + getDis(conPIP1.nowflow, len_space), DIS.PIP1_Y);
	u8g2.print(conPIP1.nowflow, 1);

	if (conPIP2.finish == PIP_RUNNING) {
		u8g2.drawStr(len_space * 3/*len of "2 "*/, DIS.PIP2_Y, "O");
	}
	else u8g2.drawStr(len_space * 3/*len of "2 "*/, DIS.PIP2_Y, "X");
	u8g2.setCursor(len_space * 5/*len of "2 X "*/ + getDis(conPIP2.target, len_space), DIS.PIP2_Y);
	u8g2.print(conPIP2.target, 1);
	u8g2.setCursor(len_space * 11/*len of"1 O 116.3 "*/ + getDis(conPIP2.nowflow, len_space), DIS.PIP2_Y);
	u8g2.print(conPIP2.nowflow, 1);

	if (conPIP3.finish == PIP_RUNNING) {
		u8g2.drawStr(len_space * 3/*len of "2 "*/, DIS.PIP3_Y, "O");
	}
	else u8g2.drawStr(len_space * 3/*len of "2 "*/, DIS.PIP3_Y, "X");
	u8g2.setCursor(len_space * 5/*len of "2 X "*/ + getDis(conPIP3.target, len_space), DIS.PIP3_Y);
	u8g2.print(conPIP3.target, 1);
	u8g2.setCursor(len_space * 11/*len of"1 O 116.3 "*/ + getDis(conPIP3.nowflow, len_space), DIS.PIP3_Y);
	u8g2.print(conPIP3.nowflow, 1);
	u8g2.sendBuffer();
}

void drawFinish(bool yes) {
	u8g2.clearBuffer();

	u8g2.setFont(u8g2_font_helvB12_tr);			//12px
	if (yes) {
		u8g2.drawStr(30, 35, "FINISH");
	}
	else {
		u8g2.drawStr(30, 35, "UNFINISH");
	}
	
	u8g2.sendBuffer();
}


void showSerial() {
	Serial.println("\n....run MyDisplay....");
	Serial.print("PIP1 -> state: ");
	if (conPIP1.finish == PIP_RUNNING) {
		Serial.print("running  ");
	}
	else
	{
		Serial.print("not running  ");
	}
	Serial.print("target: ");
	Serial.print(conPIP1.target);
	Serial.print("  nowFlow: ");
	Serial.println(conPIP1.nowflow);

	Serial.print("PIP2 -> state: ");
	if (conPIP2.finish == PIP_RUNNING) {
		Serial.print("running  ");
	}
	else
	{
		Serial.print("not running  ");
	}
	Serial.print("target: ");
	Serial.print(conPIP2.target);
	Serial.print("  nowFlow: ");
	Serial.println(conPIP2.nowflow);

	Serial.print("PIP3 -> state: ");
	if (conPIP3.finish == PIP_RUNNING) {
		Serial.print("running  ");
	}
	else
	{
		Serial.print("not running  ");
	}
	Serial.print("target: ");
	Serial.print(conPIP3.target);
	Serial.print("  nowFlow: ");
	Serial.println(conPIP3.nowflow);
}