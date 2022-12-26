// #ifndef PASSENGER_H
// #define PASSENGER_H
#pragma onece
#include <iostream>
#include <stdlib.h>
#include "enum.h"
#include <vector>
class Passenger
{
private:
    int p_id;
    int p_nowStair;
    int p_destination;
    bool p_isin=false;
    bool entering=false;
    int in_e_id;
    int wait_e_id;
    int p_times;
    int all_times=0;        //�˿͵���ʱ��
    int per_time=0;         //�˿͵�ÿ�εȴ�ʱ��
    std::vector<int>times_array;    //��¼�˿͵�ÿ���ȴ�ʱ��
    int waiting_time=0;
    int wandering_time;
    bool hadcalled=false;
    bool finished=false;
    Direction p_direction;
    Direction p_wantto_direction;
    int system_time=0;
    bool recommend=true;
public:
    Passenger(int id,int destination,int times,int nowStair=1,int cooldown=0):p_id(id),p_destination(destination),p_times(times),wandering_time(cooldown),p_nowStair(nowStair),all_times(times)
    {
        // printf("�˿�%d�ִ���ݣ��������ڵ�%d��,����ȥ��%d�㣬%d\n",id,nowStair,destination,p_times);
    }
    int getId();
    int getDestination();
    int getNowStair();
    int getStatus();
    int getwaitingtime();
    int gettimes();
    std::vector<int> gettimearray();
    bool isActive();
    void treat_elevator(int e_id,Direction d,int nowstair);
    void p_update(int hurry_time,int Time,int w_p);
    void changeentering();
    void p_free(int destination);
    void changecalling(int e_id);
    int SelectDest(int system_time);
    bool isfinished();
    bool iswaiting();
    // void passenger_update(int e_id);
};
    
// #endif 

    // void P_EnterE()
    // {
        
    // }
    
        
