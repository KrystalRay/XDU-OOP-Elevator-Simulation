#ifndef STAIR_H
#define STAIR_H
#include <iostream>
#include "Elevator.cpp"
class statistics_elevator
{
    private:
    std::vector<int> time_array;
    // int* average_time;
    int size=1;
    int times=0;//ͳ�Ƶ�ģ�����
    int time_gap=50;//ͳ�Ƶ�ʱ����
    public:
    statistics_elevator()
    {
    };
    // void print_elevator_time(int time,int op=0)
    // {
    //     if(op==1)
    //     {
    //         for(int i=1;i<=size;++i) printf("%d~%d ƽ������:%d��",i*time_gap,i*time_gap-time_gap,average_time+i);
    //         return;
    //     }
    //     int tmp_time=0;
    //     int i=0;
    //     while(tmp_time<time)
    //     {
    //         printf("%d��~%d��:����:%d��  ",time-time_gap,time,average_time[i++]);
    //         tmp_time+=time_gap;
    //     }
    //     printf("\n");
        
    // }
    void sta_update(int running_time,int time)
    {
        int i=time/50;
        if(!i)
            time_array.push_back(0);
        else
            time_array.push_back(running_time-time_array.back());
        if(size<i)
            size=i;
    }
    // void averge_update()
    // {
    //     times++;
    //     // for(int i=1;i<=time_array.size();++i)
    //     // average_time[i]+=time_array[i];
    // }
};
void SpareElevator(Elevator* elevatorptr[],std::vector<Elevator*> &e)
{
    while(!e.empty()) e.pop_back();
    for(int i=0;i<10;++i) if(!elevatorptr[i]->isNowRun()) e.push_back(elevatorptr[i]);  
}
bool ActivePassenger(Passenger* passenegerptr[],std::vector<Passenger*> &p,int numofp)
{
    while(!p.empty()) p.pop_back();
    for(int i=0;i<numofp;++i) if(passenegerptr[i]->isActive()) p.push_back(passenegerptr[i]);
    for(int i=0;i<numofp;++i) 
        if(passenegerptr[i]->isfinished()==false) return true;
    return false;
}
void init_sta(statistics_elevator* staptr[])
{
    for(int i=0;i<10;++i) staptr[i]= new statistics_elevator();
}
void init(Elevator* elevatorptr[],Passenger* passengerptr[],int numofp)
{
    for(int i=0;i<10;++i) elevatorptr[i]= new Elevator(40,0,i);

    for(int i=0;i<numofp;++i) passengerptr[i] = new Passenger(i,rand()%38+2,rand()%10+3,1,i*(rand()%5));//����-top����������
}
void freeptr(Elevator* elevatorptr[],Passenger* passengerptr[],int numofp)
{
    for(int i=0;i<10;++i) free(elevatorptr[i]);
    for(int i=0;i<numofp;++i) free(passengerptr[i]);//����-top����������
}
int SelectBest(Elevator* elevatorptr[],Passenger* passengerptr)
{
    int best_id=-1;
    int min=999;
    int i=0;
    for(i=0;i<10;++i)
    {
        if(elevatorptr[i]->CanEleGotoThisFloor(elevatorptr[i]->getId(),passengerptr->getNowStair())&&elevatorptr[i]->CanEleGotoThisFloor(elevatorptr[i]->getId(),passengerptr->getDestination()))
        {
            int tmp=passengerptr->getNowStair()-passengerptr->getDestination();
            Direction p_direction;
            if(tmp>0) p_direction=DirectionDown;
            else p_direction=DirectionUp;
            if(elevatorptr[i]->getDirection()==p_direction||elevatorptr[i]->getDirection()==DirectionStay)
            {//���ݵķ�����Ҫ�ͳ˿�����Ҫ�ƶ��ķ���һ�»��ߵ����ǿ���״̬
                if(elevatorptr[i]->getDirection()==DirectionUp&&elevatorptr[i]->getNowStair()<passengerptr->getNowStair())
                {//���ݵ��ƶ�����Ϊ���� ���ҵ��ݵ�λ��С�ڵ�ǰ�ĳ˿�λ��
                    if(elevatorptr[i]->Distance(passengerptr->getNowStair())<min) best_id=elevatorptr[i]->getId();
                }

                else if(elevatorptr[i]->getDirection()==DirectionDown&&elevatorptr[i]->getNowStair()>passengerptr->getNowStair())
                {//���ݵķ���Ϊ���� ���ҵ��ݵ�λ�ô��ڵ�ǰ�ĳ˿�λ��
                    if(elevatorptr[i]->Distance(passengerptr->getNowStair())<min) best_id=elevatorptr[i]->getId();
                }
                else if(elevatorptr[i]->getDirection()==DirectionStay) 
                {//���ݵķ����Ǿ�ֹ
                    if(elevatorptr[i]->Distance(passengerptr->getNowStair())<min) best_id=elevatorptr[i]->getId();
                }
            }
           
        }
    }
    return best_id;
}
void init_update(Elevator* elevatorptr[],Passenger* passengerptr[],int numofp,std::vector<Elevator*> &spare_e,std::vector<Passenger*> &p_waitingfor_e)
{//Ϊÿ��ѭ��������ݸ���Ҫ���ݵĵȴ��˿�
    
        while(!p_waitingfor_e.empty())
        {
            if(!p_waitingfor_e.empty())
            {
                int best=SelectBest(elevatorptr,p_waitingfor_e.back());
                // printf("best:%d\n",best);
                if(best!=-1)
                {//�����������������
                    elevatorptr[best]->movetopassenger(p_waitingfor_e.back());
                    p_waitingfor_e.pop_back();
                    continue;
                }
            }
            p_waitingfor_e.pop_back();
            //��ʱ ���е��ݶ�������
        }
}
void update_p_waiting(std::vector<Passenger*> &p_waiting,Passenger* passengerptr[],int numofp,int &tmp_w_p,int a[],int Time)
{
    p_waiting.clear();
    for(int i=0;i<numofp;i++)
    {
        if(passengerptr[i]->iswaiting()) p_waiting.push_back(passengerptr[i]);
    }
    tmp_w_p+=p_waiting.size();
    if(Time%50==0&&Time)
    {
        a[Time/50-1]+=tmp_w_p;
        tmp_w_p=0;
    }
}
void time_statistic(Elevator* elevatorptr[],Passenger* passengerptr[],int numofp,statistics_elevator* staptr[])
{
    // for(int i=1;i<=10;++i) staptr[i]->averge_update();
    for(int i=0;i<10;++i) elevatorptr[i]->PrintTime();
    for(int i=0;i<numofp;++i)
    {
        printf("�˿�%2d �ܵĵȴ�ʱ��Ϊ%3d��",passengerptr[i]->getId(),passengerptr[i]->getwaitingtime());
        printf("��һ��������%d�ε��ݣ�ÿ�εĵȴ���ʱ��",passengerptr[i]->gettimes());
        for(int j=0;j<passengerptr[i]->gettimearray().size();++j)
        {
            printf("�U��%d��:%2d��U",j+1,passengerptr[i]->gettimearray()[j]);
        }
        printf("\n");
    }
}
void global_statistic(statistics_elevator* staptr[])
{
    // for(int i=0;i<10;++i) staptr[i]->print_elevator_time(0,1);
}
class Stair
{
private:

public:

};
#endif