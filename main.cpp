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
    init(elevatorptr,passengerptr,numofp);//Ϊ���ݺͳ˿�����ռ䣬���ҳ�ʼ��
    Sleep(500);
    // for(int i=0;i<numofp;i++)   passengerptr[i]->p_update();
    // init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);//��һ�η���
    for(Time=0;Time<=timeLimit;++Time)
    {
        // printf("��%dλ�˿��ڵȴ�����\n",p_waitingfor_e.size());
        
        init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);
        // printf("��*********************�����ǵ�%d��**********************-\n",Time);
        // printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T ����״̬�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        // for(int i=0;i<10;i++)elevatorptr[i]->PrintStatus();
        for(int i=0;i<10;i++)elevatorptr[i]->e_run();
        // printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        // printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �˿�״̬�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        // for(int i=0;i<numofp;i++)passengerptr[i]->getStatus();
        for(int i=0;i<numofp;i++)passengerptr[i]->p_update(HurriesTime,Time,0);
        // printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
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
    std::cout<<"�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��1�ֵ�"<<i+1<<"��ģ����� ��ʱ�䣺"<<Time<<"��"<<"�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n";
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
        printf("%3d��%3d��ȴ�����:%3d ���ʱ��� ƽ��ÿ����%1.2f���ڵȴ�����\n",i*50,i*50+50,a[i]/stimulation_times,a[i]/stimulation_times*1.0/50);
        if(Hurries_Time_w_p<a[i])
        {
            HurriesTime=(i+1)*50;//��¼��Ϊ��æ��ʱ��� 0��0-50 1��50-100�Դ�����
            Hurries_Time_w_p=a[i];
        }
        
    }
    printf("��һ��ģ������������\nƽ����ʱ:%3d �߷�������%.2f\n",AllTime/stimulation_times,Hurries_Time_w_p/stimulation_times*1.0);
//////////////////////////////
    Hurries_Time_w_p=0;AllTime=0;MaxTime=0;tmp_w_p=0;
    for(int i=0;i<40;i++) a[i]=0;
///////////////////////////////
  for(int i=0;i<stimulation_times;i++)
    {
    Elevator* elevatorptr[10];Passenger* passengerptr[1000];
    std::vector<Passenger*> p_waitingfor_e;std::vector<Passenger*>p_waiting;std::vector<Elevator*> spare_e;
    init(elevatorptr,passengerptr,numofp);//Ϊ���ݺͳ˿�����ռ䣬���ҳ�ʼ��
    Sleep(500);
    // for(int i=0;i<numofp;i++)   passengerptr[i]->p_update();
    // init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);//��һ�η���
    for(Time=0;Time<=timeLimit;++Time)
    {
        // printf("��%dλ�˿��ڵȴ�����\n",p_waitingfor_e.size());
        update_p_waiting(p_waiting,passengerptr,numofp,tmp_w_p,a,Time);
        init_update(elevatorptr,passengerptr,numofp,spare_e,p_waitingfor_e);
        // printf("��*********************�����ǵ�%d��**********************-\n",Time);
        // printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T ����״̬�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        // for(int i=0;i<10;i++)elevatorptr[i]->PrintStatus();
        for(int i=0;i<10;i++)elevatorptr[i]->e_run();
        // printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        // printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �˿�״̬�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        // for(int i=0;i<numofp;i++)passengerptr[i]->getStatus();
        for(int i=0;i<numofp;i++)passengerptr[i]->p_update(HurriesTime,Time,0);
        // printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
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
    std::cout<<"�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��1�ֵ�"<<i+1<<"��ģ����� ��ʱ�䣺"<<Time<<"��"<<"�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n";
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
        printf("%3d��%3d��ȴ�����:%3d ���ʱ��� ƽ��ÿ����%1.2f���ڵȴ�����\n",i*50,i*50+50,a[i]/stimulation_times,a[i]/stimulation_times*1.0/50);
        if(Hurries_Time_w_p<a[i])
        {
            HurriesTime=(i+1)*50;//��¼��Ϊ��æ��ʱ��� 0��0-50 1��50-100�Դ�����
            Hurries_Time_w_p=a[i];
        }
    }
    printf("ͨ����ǰԤ��������Ԥ���еĸ߷�ʱ��εĳ˿Ͷ��ε�һ������Ż����ģ�⣺\nƽ����ʱ:%3d �߷�������%.2f\n",AllTime/stimulation_times,Hurries_Time_w_p/stimulation_times*1.0);
    // global_statistic(staptr);
}