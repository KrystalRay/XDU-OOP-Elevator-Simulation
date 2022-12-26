#include <stdlib.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Stair.h"
#include "Vision.h"
#define numofp 45
int a[40]={0};
int MaxTime=0;
int AllTime=0;
int HurriesTime=-2;
int Hurries_Time_w_p=0;
int main()
{
    int top=40;int Time=0;int timeLimit=3000;int stimulation_times=10;
    statistics_elevator* staptr[10];
    init_sta(staptr);
    int tmp_w_p=0;
    for(int i=0;i<stimulation_times;i++)
    {
    Elevator* elevatorptr[10];Passenger* passengerptr[1000];
    std::vector<Passenger*> p_waitingfor_e;std::vector<Passenger*>p_waiting;std::vector<Elevator*> spare_e;
    init(elevatorptr,passengerptr,numofp);//为电梯和乘客申请空间，并且初始化
    Sleep(500);
    // for(int i=0;i<numofp;i++)   passengerptr[i]->p_update();
    // init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);//第一次分配
    for(Time=0;Time<=timeLimit;++Time)
    {
        // printf("有%d位乘客在等待电梯\n",p_waitingfor_e.size());
        
        init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);
        // printf("—*********************现在是第%d秒**********************-\n",Time);
        // printf("╔══════════════════════════════ 电梯状态═════════════════════════════╗\n");
        // for(int i=0;i<10;i++)elevatorptr[i]->PrintStatus();
        for(int i=0;i<10;i++)elevatorptr[i]->e_run();
        // printf("╚════════════════════════════════════════════════════════════════════╝\n");
        // printf("╔══════════════════════════════ 乘客状态═════════════════════════════╗\n");
        // for(int i=0;i<numofp;i++)passengerptr[i]->getStatus();
        for(int i=0;i<numofp;i++)passengerptr[i]->p_update(HurriesTime,Time,0);
        // printf("╚════════════════════════════════════════════════════════════════════╝\n");
        SpareElevator(elevatorptr,spare_e);
        if(ActivePassenger(passengerptr,p_waitingfor_e,numofp)==false)
            break;
        // Sleep(20);
        // system("cls");
        update_p_waiting(p_waiting,passengerptr,numofp,tmp_w_p,a,Time);
        if(Time%50==0)
        {
            // for(int i=0;i<10;i++)
            // staptr[i]->sta_update(elevatorptr[i]->get_running_time(),Time);
            // printf("2");
            // printf("%d:\n",Time);
            // for(int i=0;i<10;i++) elevatorptr[i]->PrintTime();
        }
    }
    // system("cls");
    std::cout<<"══════════════════════════════第1轮第"<<i+1<<"次模拟结束 总时间："<<Time<<"秒"<<"══════════════════════════════\n";
    // time_statistic(elevatorptr,passengerptr,numofp,staptr);
    if(Time>MaxTime)
        MaxTime=Time;
    AllTime+=Time;
    p_waitingfor_e.clear();
    spare_e.clear();
    p_waiting.clear();
    freeptr(elevatorptr,passengerptr,numofp);
    }

    for(int i=0;i<MaxTime/50;++i)
    {
        printf("%3d到%3d秒等待人数:%3d 这个时间段 平均每秒有%1.2f人在等待电梯\n",i*50,i*50+50,a[i]/stimulation_times,a[i]/stimulation_times*1.0/50);
        if(Hurries_Time_w_p<a[i])
        {
            HurriesTime=(i+1)*50;//记录最为繁忙的时间段 0是0-50 1是50-100以此类推
            Hurries_Time_w_p=a[i];
        }
        
    }
    printf("第一轮模拟结束，结果：\n平均用时:%3d 高峰期人数%.2f\n",AllTime/stimulation_times,Hurries_Time_w_p/stimulation_times*1.0);
//////////////////////////////
    Hurries_Time_w_p=0;AllTime=0;MaxTime=0;tmp_w_p=0;
    for(int i=0;i<40;i++) a[i]=0;
///////////////////////////////
  for(int i=0;i<stimulation_times;i++)
    {
    Elevator* elevatorptr[10];Passenger* passengerptr[1000];
    std::vector<Passenger*> p_waitingfor_e;std::vector<Passenger*>p_waiting;std::vector<Elevator*> spare_e;
    init(elevatorptr,passengerptr,numofp);//为电梯和乘客申请空间，并且初始化
    Sleep(500);
    // for(int i=0;i<numofp;i++)   passengerptr[i]->p_update();
    // init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);//第一次分配
    for(Time=0;Time<=timeLimit;++Time)
    {
        // printf("有%d位乘客在等待电梯\n",p_waitingfor_e.size());
        update_p_waiting(p_waiting,passengerptr,numofp,tmp_w_p,a,Time);
        init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);
        // printf("—*********************现在是第%d秒**********************-\n",Time);
        // printf("╔══════════════════════════════ 电梯状态═════════════════════════════╗\n");
        // for(int i=0;i<10;i++)elevatorptr[i]->PrintStatus();
        for(int i=0;i<10;i++)elevatorptr[i]->e_run();
        // printf("╚════════════════════════════════════════════════════════════════════╝\n");
        // printf("╔══════════════════════════════ 乘客状态═════════════════════════════╗\n");
        // for(int i=0;i<numofp;i++)passengerptr[i]->getStatus();
        for(int i=0;i<numofp;i++)passengerptr[i]->p_update(HurriesTime,Time,0);
        // printf("╚════════════════════════════════════════════════════════════════════╝\n");
        SpareElevator(elevatorptr,spare_e);
        if(ActivePassenger(passengerptr,p_waitingfor_e,numofp)==false)
            break;
        // Sleep(20);
        // system("cls");
        if(Time%50==0)
        {
            // for(int i=0;i<10;i++)
            // staptr[i]->sta_update(elevatorptr[i]->get_running_time(),Time);
            // printf("2");
            // printf("%d:\n",Time);
            // for(int i=0;i<10;i++) elevatorptr[i]->PrintTime();
        }
    }
    // system("cls");
    std::cout<<"══════════════════════════════第1轮第"<<i+1<<"次模拟结束 总时间："<<Time<<"秒"<<"══════════════════════════════\n";
    // time_statistic(elevatorptr,passengerptr,numofp,staptr);
    if(Time>MaxTime)
        MaxTime=Time;
    AllTime+=Time;
    p_waitingfor_e.clear();
    spare_e.clear();
    freeptr(elevatorptr,passengerptr,numofp);
    }
    for(int i=0;i<MaxTime/50;++i)
    {
        printf("%3d到%3d秒等待人数:%3d 这个时间段 平均每秒有%1.2f人在等待电梯\n",i*50,i*50+50,a[i]/stimulation_times,a[i]/stimulation_times*1.0/50);
        if(Hurries_Time_w_p<a[i])
        {
            HurriesTime=(i+1)*50;//记录最为繁忙的时间段 0是0-50 1是50-100以此类推
            Hurries_Time_w_p=a[i];
        }
    }
    printf("通过提前预警，鼓励预测中的高峰时间段的乘客多游荡一会儿，优化后的模拟：\n平均用时:%3d 高峰期人数%.2f\n",AllTime/stimulation_times,Hurries_Time_w_p/stimulation_times*1.0);
    // global_statistic(staptr);
}