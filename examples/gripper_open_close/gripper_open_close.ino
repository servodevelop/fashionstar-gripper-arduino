/**
 * 爪子开启关闭实验(带功率约束)
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: kyle.xing@fashionstar.com.hk
 * 更新时间: 2020/11/14
 */
 
#include <SoftwareSerial.h>
#include "FashionStar_UartServoProtocol.h"  // 串口总线舵机通信协议
#include "FashionStar_UartServo.h"          // Fashion Star串口总线舵机
#include "FashionStar_SmartGripper.h"       // Fashion Star智能夹具

// 软串口的配置
#define SOFT_SERIAL_RX 6    // 软串口发送端的GPIO
#define SOFT_SERIAL_TX 7    // 软串口接收端的GPIO
#define SOFT_SERIAL_BAUDRATE 4800   // 软串口的波特率

// 串口总线舵机配置
#define SERVO_ID 4      //爪子对应的舵机ID号
#define BAUDRATE 115200 // 波特率

// 爪子的配置
#define SERVO_ANGLE_GRIPPER_OPEN 15.0 // 爪子张开时的角度
#define SERVO_ANGLE_GRIPPER_CLOSE -45.0 // 爪子闭合时的角度

// 软串口初始化
SoftwareSerial softSerial(SOFT_SERIAL_RX, SOFT_SERIAL_TX); // 创建软串口
// 创建舵机的通信协议对象
FSUS_Protocol protocol(BAUDRATE);
// 创建舵机的实例
FSUS_Servo uservo(SERVO_ID, &protocol);
// 创建智能机械爪实例
FSGP_Gripper gripper(&uservo, SERVO_ANGLE_GRIPPER_OPEN,SERVO_ANGLE_GRIPPER_CLOSE);

void setup(){
    softSerial.begin(SOFT_SERIAL_BAUDRATE); // 软串口
    softSerial.println("Start To Test Gripper\n"); // 打印日志

    protocol.init();    // 舵机通信协议初始化    
    gripper.init();     // 爪子初始化
    // 参数配置
    gripper.setMaxPower(400); // 设置最大功率，单位mW
}

void loop(){
    softSerial.println("Gripper Close\n"); // 打印日志
    gripper.close();
    delay(5000); // 等待5s
    softSerial.println("Gripper Open\n"); // 打印日志
    gripper.open();
}