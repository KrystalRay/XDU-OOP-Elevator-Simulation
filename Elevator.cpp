#include "Elevator.h"
// class Elevator;
int Elevator::getNowStair()
{
    return e_currentStair;
}
int Elevator::getId()
{
    return e_id;
}
Direction Elevator::getDirection()
{
    return e_direction;
}
bool Elevator::isNowRun()
{
    return isRun;
}

bool Elevator::e_addPassenger(Passenger *e_passengerptr)
{
    if (this->isFull())
        return false;
    else
    {
        e_currentPassengerAmount++;
        e_passenger.push_back(e_passengerptr);
        isRun = true;
        return true;
    }
}
bool Elevator::isFull()
{
    return e_currentPassengerAmount == e_MaxPassengerAmount;
}

void Elevator::treatpassenger(Passenger *Passenger)//根据乘客改变方向
{
    if (Passenger->getDestination() > e_currentStair)
        e_direction = DirectionUp;
    else if (Passenger->getDestination() < e_currentStair)
        e_direction = DirectionDown;
    else e_direction=DirectionStay;
    e_destination = Passenger->getDestination();
}

void Elevator::e_run()
{
    system_time++;
    if (isNowRun())
    {
        timeHasspent++;
        running_time++;
    }
    else
    {
        spare_time++;
    }
    if (timeHasspent == timePerFloor)
    {
        timeHasspent = 0;
        e_currentStair += e_direction;
        //这是对于上一秒状态的改变 下面的部分是对下一秒状态的改变
        for(int i=0;i<targetpassenger.size();++i)//对目标乘客的处理
        {
            if(targetpassenger[i]->getNowStair()==e_currentStair)
            {
                // e_direction=DirectionStay;//如果接乘客 就先停止 方向为Stay
                if(e_passenger.empty())
                    treatpassenger(targetpassenger.back());
                e_addPassenger(targetpassenger[i]);
                targetpassenger[i]->changeentering();//让乘客上电梯产生一个停留，防止乘客超前运动，因为乘客的update是晚于电梯的
                targetpassenger.erase(targetpassenger.begin()+i);//在目标乘客容器中删除这个乘客
                //注意这里
            }
        }
        if(e_passenger.empty()&&!targetpassenger.empty())
        {
            e_destination=targetpassenger[0]->getNowStair();
        }
        for(int i=0;i<e_passenger.size();++i)//对电梯内乘客的处理
        {
            e_passenger[i]->treat_elevator(e_id,e_direction,e_currentStair);//将电梯状态同步给每位电梯内的乘客
            if(e_passenger[i]->getDestination()==(e_currentStair))//如果电梯抵达了某个乘客的目标层
            {
                e_passenger.erase(e_passenger.begin()+i);//把这个乘客在乘客容器中删除
                if(!e_passenger.empty())//如果乘客容器非空
                    treatpassenger(e_passenger.back());//处理下一个乘客
            }
        }
        if(!e_passenger.empty()) treatpassenger(e_passenger[0]);
        if(e_destination>e_currentStair) e_direction=DirectionUp;
        else if(e_destination<e_currentStair) e_direction=DirectionDown;
        if (e_passenger.empty()&&targetpassenger.empty())//如果目标容器和乘客容器都是空的
        {
            e_direction = DirectionStay;
            isRun = false;//转变电梯状态为空闲状态
        }
    }
}
void Elevator::PrintStatus()
{
    printf("║第%d台电梯，在第%d层,状态是:",e_id,getNowStair());
    if (isNowRun())
    {
        printf("运行中,目的地是第%d层,方向是%d\n",e_destination,e_direction);
    }
    else
        printf("空闲中\n");
    if(targetpassenger.size())
    {
        printf("║**它的目标乘客是");
        for(int i=0;i<targetpassenger.size();i++)
            printf("%d",targetpassenger[i]->getId());
        printf("\n");
    }
        
    if(e_passenger.size())
    {
        std::cout << "║电梯内有" << e_passenger.size() << "人，里面的乘客分别是:";
        for (int i = 0; i < e_passenger.size(); ++i)
            std::cout << e_passenger[i]->getId() << "-" << e_passenger[i]->getDestination();
        std::cout << std::endl;
    }
    else
        printf("║\n");
    }
        
int Elevator::movetopassenger(Passenger* p)
    {  
        int id=e_id;
        p->changecalling(id);
        if(e_currentStair!=p->getNowStair())
            {
                e_direction=p->getNowStair()>e_currentStair?DirectionUp:DirectionDown;
                isRun=true;
                e_destination=p->getNowStair();
                targetpassenger.push_back(p);//将这一个乘客压入
                return id;
            }
        else
        {
            isRun=true;
            if(e_passenger.empty())
                treatpassenger(p);
            e_addPassenger(p);
            // p->changeentering();
        } 
    }
bool Elevator::CanEleGotoThisFloor(int e_id,int dest)
{
    if(dest==1)
        return true;
    if(e_id==0||e_id==1)
        return true;
    else if(e_id==2||e_id==3)
    {
        if(dest>=25&&dest<=40)
            return true;
    }
    else if(e_id==4||e_id==5)
    {
        if(dest>=2&&dest<=24)
            return true;
    }
    else if(e_id==6||e_id==7)
    {
        if(dest>=2&&dest<=40&&dest%2==0)
            return true;
    }
    else if(e_id==8||e_id==9)
    {
        if(dest>=2&&dest<=39&&dest%2==1)
            return true;
    }
    return false;
}
int Elevator::Distance(int dest)
{
    if(dest>=e_currentStair)
        return dest-e_currentStair;
    return e_currentStair-dest;
}
void Elevator::PrintTime()
{
    printf("║电梯%d 总运行时间为%3d秒 空闲时间为%3d秒║\n",e_id,running_time,spare_time);
}
int Elevator::get_running_time()
{
    return running_time;
}