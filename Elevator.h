// #ifndef ELEVATOR_H
// #define ELEVATOR_H
#pragma onece
#include <iostream>
#include <vector>
#include "enum.h"
#include "Passenger.cpp"
class Elevator
{
private:
    int e_id; //电梯编号
    int xTop;
    int xBottom;
    int e_currentStair = 1;
    Direction e_direction=DirectionStay;
    std::vector<Passenger *> e_passenger;
    std::vector<Passenger *> targetpassenger;
    int e_MaxPassengerAmount = 100;   //当前电梯最大人数
    int e_currentPassengerAmount = 0; //当前电梯内人数
    int e_destination = 1;            //电梯目标层
    bool isRun=false;                       //电梯是否在运行
    int timePerFloor = 1;             //上下行一层所需时间
    int timeHasspent = 0;
    int running_time=0;         //电梯运行时间
    int spare_time=0;          //电梯的空闲时间
    int system_time=0;
public:
    Elevator(int top, int bottom, int id) : e_currentStair(1), xTop(top), xBottom(bottom), isRun(false), e_id(id)
    {
    }
    int getNowStair();
    int getId();
    Direction getDirection();
    bool isNowRun();
    bool e_addPassenger(Passenger *e_passengerptr);
    bool isFull();
    void treatpassenger(Passenger *Passenger);
    void e_run();
    void PrintStatus();
    int movetopassenger(Passenger* p);
    bool CanEleGotoThisFloor(int e_id,int dest);
    int Distance(int dest);
    void PrintTime();
    int get_running_time();
};
// #endif 