/**
 * 爪子开启关闭实验(带功率约束)
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: kyle.xing@fashionstar.com.hk
 * 更新时间: 2021/07/15
 */
 
#include "FashionStar_UartServoProtocol.h"  // 串口总线舵机通信协议
#include "FashionStar_UartServo.h"          // Fashion Star串口总线舵机
#include "FashionStar_SmartGripper.h"       // Fashion Star智能夹具

// 调试串口的配置
#if defined(ARDUINO_AVR_UNO)
    #include <SoftwareSerial.h>
    #define SOFT_SERIAL_RX 6
    #define SOFT_SERIAL_TX 7
    SoftwareSerial softSerial(SOFT_SERIAL_RX, SOFT_SERIAL_TX); // 创建软串口
    #define DEBUG_SERIAL softSerial
    #define DEBUG_SERIAL_BAUDRATE 4800
#elif defined(ARDUINO_AVR_MEGA2560)
    #define DEBUG_SERIAL Serial
    #define DEBUG_SERIAL_BAUDRATE 115200
#elif defined(ARDUINO_ARCH_ESP32)
    #define DEBUG_SERIAL Serial
    #define DEBUG_SERIAL_BAUDRATE 115200
#endif 

// 串口总线舵机配置
#define SERVO_ID 4      //爪子对应的舵机ID号
#define BAUDRATE 115200 // 波特率

// 爪子的配置
#define SERVO_ANGLE_GRIPPER_OPEN 15.0 // 爪子张开时的角度
#define SERVO_ANGLE_GRIPPER_CLOSE -45.0 // 爪子闭合时的角度

// 创建舵机的通信协议对象
FSUS_Protocol protocol(BAUDRATE);
// 创建舵机的实例
FSUS_Servo uservo(SERVO_ID, &protocol);
// 创建智能机械爪实例
FSGP_Gripper gripper(&uservo, SERVO_ANGLE_GRIPPER_OPEN,SERVO_ANGLE_GRIPPER_CLOSE);

void setup(){
    DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUDRATE); // 软串口
    DEBUG_SERIAL.println("Start To Test Gripper\n"); // 打印日志

    protocol.init();    // 舵机通信协议初始化    
    gripper.init();     // 爪子初始化
    // 参数配置
    gripper.setMaxPower(400); // 设置最大功率，单位mW
}

void loop(){
    DEBUG_SERIAL.println("Gripper Close\n"); // 打印日志
    gripper.close();
    delay(5000); // 等待5s
    DEBUG_SERIAL.println("Gripper Open\n"); // 打印日志
    gripper.open();
    delay(5000); // 等待5s
}