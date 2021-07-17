/**
 * Fashion Star 智能机械爪
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: kyle.xing@fashionstar.com.hk
 * 更新时间: 2020/11/14
 */

#include "FashionStar_SmartGripper.h"

// 夹具
FSGP_Gripper::FSGP_Gripper(){
    
}
// 夹具
FSGP_Gripper::FSGP_Gripper(FSUS_Servo *servo, float angleGripperOpen, float angleGripperClose)
{   
    // 参数赋值
    this->servo = servo;                          // 舵机指针初始化
    this->angleGripperOpen = angleGripperOpen;    // 爪子开启的角度
    this->angleGripperClose = angleGripperClose;  // 爪子闭合的角度
    // 默认参数设置
    this->maxPower = FSGP_DEFAULT_POWER_MW;
    this->interval = FSGP_DEFAULT_INTERVAL;
    this->curPower = 0;
    // 设置状态位
    this->status = FSGP_STATUS_OPEN;
}

// 初始化舵机
bool FSGP_Gripper::init()
{
    // 舵机机初始化
    this->servo->init();
    if(!this->servo->isOnline){
        return false; // 舵机不在线
    }
    // 爪子开启
    this->servo->setAngle(this->angleGripperOpen);  // 设置舵机的角度
    this->servo->wait();
    // this->open();
    
    return true;
}

bool FSGP_Gripper::init(FSUS_Servo *servo, float angleGripperOpen, float angleGripperClose){
    // 参数赋值
    this->servo = servo;                          // 舵机指针初始化
    this->angleGripperOpen = angleGripperOpen;    // 爪子开启的角度
    this->angleGripperClose = angleGripperClose;  // 爪子闭合的角度
    // 默认参数设置
    this->maxPower = FSGP_DEFAULT_POWER_MW;
    this->interval = FSGP_DEFAULT_INTERVAL;
    this->curPower = 0;
    // 设置状态位
    this->status = FSGP_STATUS_OPEN;
    
    this->init();
}

// 设置电机的最大功率
void FSGP_Gripper::setMaxPower(uint16_t power)
{
    this->maxPower = power;
}

// 设置电机的原始角度
void FSGP_Gripper::setAngle(float angle, uint16_t interval, uint16_t power){
    this->servo->setAngle(angle, interval, power);
}

// 爪子打开
void FSGP_Gripper::open()
{
    // 设置状态位
    this->status = FSGP_STATUS_OPEN;
    // 设置舵机角度
    this->servo->setAngle(this->angleGripperOpen, this->interval, 0);
    // 等待舵机旋转到位
    this->servo->wait();
}

// 爪子关闭
void FSGP_Gripper::close()
{
    this->status = FSGP_STATUS_CLOSE;
    this->servo->setAngle(this->angleGripperClose, this->interval, this->maxPower);
}

// 查询当前的功率
uint16_t FSGP_Gripper::queryPower()
{
    return this->servo->queryPower();
}

// 查询爪子当前的状态
uint8_t FSGP_Gripper::getStatus()
{
    return this->status;
}

// 更新当前的状态
uint8_t FSGP_Gripper::updateStatus()
{
    // TODO
}