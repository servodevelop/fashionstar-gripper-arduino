/**
 * Fashion Star 智能机械爪
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: kyle.xing@fashionstar.com.hk
 * 更新时间: 2020/11/14
 */
#ifndef _FS_SMART_GRIPPER_H
#define _FS_SMART_GRIPPER_H

#include <Arduino.h>
#include "FashionStar_UartServo.h"

// 爪子默认的功率(单位mW)
#define FSGP_DEFAULT_POWER_MW 400
// 爪子是否有负载的功率阈值(单位 mW)
// 如果小于这个值认为是无负载
#define FSGP_LOAD_POWER_THRESHOLD 150
// 爪子默认的闭合周期
#define FSGP_DEFAULT_INTERVAL 1000

// 爪子状态定义Clamping
#define FSGP_STATUS_OPEN 0          // 爪子开启
#define FSGP_STATUS_CLAMPING 1      // 爪子夹紧中
#define FSGP_STATUS_CLOSE  2        // 爪子关闭(已夹紧)
#define FSGP_STATUS_OBJ_DROP  3     // 负载对象意外掉落, 进入阻尼模式

/* 智能夹具 */
class FSGP_Gripper{
public:
    // 夹具
    FSGP_Gripper(FSUS_Servo *servo, float angleGripperOpen, float angleGripperClose);
    // 初始化舵机
    bool init();
    // 设置电机的最大功率
    void setMaxPower(uint16_t power);
    // 爪子打开
    void open();

    // 爪子关闭
    void close();

    // 判断当前爪子是否有负载
    bool isUnderLoad();
    // 判断爪子的负载是否掉落
    bool isLoadDropped();
    // 查询当前的功率
    uint16_t queryPower();
    // 查询爪子当前的状态
    uint8_t getStatus();
    // 更新当前的状态
    uint8_t updateStatus();
    // 设置舵机角度
    void setAngle(float angle, uint16_t interval, uint16_t power);
    // 舵机对象
    FSUS_Servo* servo;          // 爪子对应的舵机对象

    float angleGripperOpen;     // 爪子张开的角度
    float angleGripperClose;    // 爪子闭合的角度
    uint16_t maxPower;          // 功率保护值
    uint16_t interval;          // 爪子开启/闭合的周期
    uint16_t curPower;          // 电机当前的功率
    uint8_t status;            // 电机当前状态
private:
    
};
#endif