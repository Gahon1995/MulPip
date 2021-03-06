#pragma once
/**** 头文件包含 ***/
#include <Arduino.h>

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_TIMEOUT

#include <TaskScheduler.h>	//多任务调度库
#include <ArduinoJson.h>	//解析WIFI json格式数据使用的库
#include <U8g2lib.h>	//OLED 显示屏库
#include "Model.h"	//使用的数据结构体定义



/** 发送代码定义 *****/

//WIFI接收相关
#define RECV_SUCCESS 100	//数据接收成功
#define RECV_FAILD 101		//数据接收失败
#define RECV_WRONG 102		//数据范围出错
#define SEND_ALLOWED 200	//可以发送数据
#define SEND_REJECT 201		//拒绝发送指令
#define FIND_STATUS 111		//查询命令
#define CONNECCT_SUCESS 103		//连接成功
#define HAVE_CONNECTION 104		//已经有一个连接了，请等待之后的连接

/***机器运行相关*******/
#define START_FAILD 400		//无法启动机器，硬件问题---> WiFi不会发送这个代码
#define JOB_RUNNING 403		//正在运行 --->  WiFi不会发送这个代码
#define JOB_FINISH 401		//完成整套配置过程
#define JOB_UNFINISH 402	//机器执行过程出错，配置失败

//判断管道控制运行是否结束
#define PIP_FINISH 100
#define PIP_UNFINISH 101
#define PIP_RUNNING 102
#define PIP_NOTRUNNING 103


/*****  Arduino 引脚定义  *****/

// 脉冲接口定义   中断口定义  (mega: 2, 3, 18, 19, 20, 21  ---> 0,1,2...)
#define PIP_1 18	//流量计脉冲接口
#define PIP_2 19
#define PIP_3 20

//开关口定义
#define SWITCH_1 31
#define SWITCH_2 32
#define SWITCH_3 33

//简单函数定义	使用模拟方式时不用
#define SWITCH_ON(SWITCH) digitalWrite(SWITCH,LOW)
#define SWITCH_OFF(SWITCH) digitalWrite(SWITCH,HIGH)
#define OPENINTERRUPT(PIP,count) attachInterrupt(digitalPinToInterrupt(PIP), count, FALLING);
#define CLOSEINTERRUPT(PIP) detachInterrupt(digitalPinToInterrupt(PIP));


//常数定义

#define VOL_MAX 550
#define VOL_MIN 0
#define START 1
#define STOP 0

#define STEP 0.6

#define READ_TIME 0.001 


//函数声明

void MyDisplay();
void MyWiFi();
void PIP1();
void PIP2();
void PIP3();
void controlPIP1();
void controlPIP2();
void controlPIP3();