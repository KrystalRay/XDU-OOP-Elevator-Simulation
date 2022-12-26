#include "Passenger.h"
// class Passenger;
    int Passenger::getId() 
    {//获取id
        return p_id;
    }
    int Passenger::getDestination()
    {//获取目的地
        return p_destination;
    }
    int Passenger::getNowStair() 
    {//获取当前楼层
        return p_nowStair;
    }
    bool Passenger::isfinished()
    {//获取是否已经完成模拟
        if(finished)
            return true;
        return false;
    }
    int Passenger::getwaitingtime()
    {//获取等待时间
        return waiting_time;
    }
    int Passenger::gettimes()
    {//获取时间容器的大小
        return times_array.size();
    }
    std::vector<int> Passenger::gettimearray()
    {//获取时间容器
        return times_array;
    }
    int Passenger::getStatus()
    {
        
        if(p_isin)
            printf("║乘客%d在电梯%d中,第%d层,目的地%d层,他还会乘电梯%d次\n",p_id,in_e_id,p_nowStair,p_destination,p_times+1);
        else if(!p_isin&&p_times>=0)
        {
            printf("║乘客%d",p_id);
            if(wandering_time>0)
                printf("目前还在游荡，游荡时间还有%d秒,目的地%d层,他还会乘电梯%d次\n",wandering_time,p_destination,p_times+1);
            else if(hadcalled)
                printf("已经呼唤了一台电梯，是第%d台电梯，目前在%d楼等待上电梯，目的地%d层,他还会乘电梯%d次,dd时间%d\n",wait_e_id,p_nowStair,p_destination,p_times+1,per_time);
            else
                printf("目前在等电梯,目的地%d层,他还会乘电梯%d次\n",p_destination,p_times+1);
        }
        else if(p_times<0)
        {
             printf("║乘客%d已经结束了电梯模拟\n",p_id);
             finished=true;
        }
        return p_isin;
    }
    bool Passenger::isActive()
    {
        if(wandering_time==0&&p_times>=0&&hadcalled==false&&!p_isin)
            return true;
        else 
            return false;
    }
    void Passenger::treat_elevator(int e_id,Direction d,int nowstair)
    {//将电梯信息存入乘客
        p_isin=true;
        in_e_id=e_id;
        p_direction=d;
        p_nowStair=nowstair;
    }
    void Passenger::changeentering()
    {
        entering=true;
    }
    void Passenger::p_update(int hurry_time,int Time,int w_p)
    {//乘客更新函数 每秒调用一次
        system_time++;
        if(p_isin)
        {
            wandering_time=999;
            if(!entering)
            {
                // p_nowStair+=p_direction;
            }
            else
            {
                entering=false;
                times_array.push_back(per_time);
                per_time=0;
            }

            if(p_nowStair==p_destination)
            {//如果抵达了目标层
                p_isin=false;
                p_times--;
                if(p_times>0)//如果仍有乘坐电梯的次数
                    p_free(rand()%40+2);
                else if(p_times==0)//最后一次乘坐 前往一层
                    p_free(1);
                else if(p_times<0)
                {//如果已经没有剩余的乘坐电梯的次数
                    wandering_time=9999999;
                    finished=true;
                    // std::cout << "║乘客" << p_id << "被释放，他结束了电梯模拟——————————————————————————————————" <<std::endl;
                }
            }
        }
        else
        {
            
            if(wandering_time>0)
            {
                if(wandering_time<=5&&Time>hurry_time-100&&Time<hurry_time+20&&recommend)  
                {wandering_time+=rand()%80;recommend=false;}
                wandering_time--;
            }
            else if(wandering_time==0)
            {
                waiting_time++;
                per_time++;
            }
            
        }
    }
    void Passenger::p_free(int destination)
    {
        p_isin=false;
        hadcalled=false;
        int ran = SelectDest(system_time);
        p_nowStair = ran;
        p_destination = destination;
        while (p_nowStair == p_destination )
            p_destination = SelectDest(system_time);
        wandering_time = rand() % 5 + 10;
        // std::cout << "║乘客" << p_id << "被释放" << "他的游荡时间是" << wandering_time << "目的地是" <<p_destination<<std::endl;
    };
    void Passenger::changecalling(int e_id)
    {
        hadcalled=true;
        wait_e_id=e_id;
    }
    int Passenger::SelectDest(int system_time)
    {//按照时间来为乘客分配目的地 
        int weight=rand()%100+1;
        int dest;
        if(system_time<300)
        {
            if(weight<=80) dest=rand()%19+2;
            else    dest=rand()%20+21;
        }
        else if(system_time>=300&&system_time<=500)
        {
            if(weight<=50) dest=rand()%19+2;
            else    dest=rand()%20+21;
        }
        else if(system_time>500&&system_time<=700)
        {
            if(weight<=20) dest=rand()%19+2;
            else    dest=rand()%20+21;
        }
        else
        {
            if(weight<=80) dest=rand()%19+2;
            else    dest=rand()%20+21;
        }
        return dest;
    }
    bool Passenger::iswaiting()
    {
        if(wandering_time==0)
            return true;
        return false;
    }
    