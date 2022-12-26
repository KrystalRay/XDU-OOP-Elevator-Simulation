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

void Elevator::treatpassenger(Passenger *Passenger)//���ݳ˿͸ı䷽��
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
        //���Ƕ�����һ��״̬�ĸı� ����Ĳ����Ƕ���һ��״̬�ĸı�
        for(int i=0;i<targetpassenger.size();++i)//��Ŀ��˿͵Ĵ���
        {
            if(targetpassenger[i]->getNowStair()==e_currentStair)
            {
                // e_direction=DirectionStay;//����ӳ˿� ����ֹͣ ����ΪStay
                if(e_passenger.empty())
                    treatpassenger(targetpassenger.back());
                e_addPassenger(targetpassenger[i]);
                targetpassenger[i]->changeentering();//�ó˿��ϵ��ݲ���һ��ͣ������ֹ�˿ͳ�ǰ�˶�����Ϊ�˿͵�update�����ڵ��ݵ�
                targetpassenger.erase(targetpassenger.begin()+i);//��Ŀ��˿�������ɾ������˿�
                //ע������
            }
        }
        if(e_passenger.empty()&&!targetpassenger.empty())
        {
            e_destination=targetpassenger[0]->getNowStair();
        }
        for(int i=0;i<e_passenger.size();++i)//�Ե����ڳ˿͵Ĵ���
        {
            e_passenger[i]->treat_elevator(e_id,e_direction,e_currentStair);//������״̬ͬ����ÿλ�����ڵĳ˿�
            if(e_passenger[i]->getDestination()==(e_currentStair))//������ݵִ���ĳ���˿͵�Ŀ���
            {
                e_passenger.erase(e_passenger.begin()+i);//������˿��ڳ˿�������ɾ��
                if(!e_passenger.empty())//����˿������ǿ�
                    treatpassenger(e_passenger.back());//������һ���˿�
            }
        }
        if(!e_passenger.empty()) treatpassenger(e_passenger[0]);
        if(e_destination>e_currentStair) e_direction=DirectionUp;
        else if(e_destination<e_currentStair) e_direction=DirectionDown;
        if (e_passenger.empty()&&targetpassenger.empty())//���Ŀ�������ͳ˿��������ǿյ�
        {
            e_direction = DirectionStay;
            isRun = false;//ת�����״̬Ϊ����״̬
        }
    }
}
void Elevator::PrintStatus()
{
    printf("�U��%d̨���ݣ��ڵ�%d��,״̬��:",e_id,getNowStair());
    if (isNowRun())
    {
        printf("������,Ŀ�ĵ��ǵ�%d��,������%d\n",e_destination,e_direction);
    }
    else
        printf("������\n");
    if(targetpassenger.size())
    {
        printf("�U**����Ŀ��˿���");
        for(int i=0;i<targetpassenger.size();i++)
            printf("%d",targetpassenger[i]->getId());
        printf("\n");
    }
        
    if(e_passenger.size())
    {
        std::cout << "�U��������" << e_passenger.size() << "�ˣ�����ĳ˿ͷֱ���:";
        for (int i = 0; i < e_passenger.size(); ++i)
            std::cout << e_passenger[i]->getId() << "-" << e_passenger[i]->getDestination();
        std::cout << std::endl;
    }
    else
        printf("�U\n");
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
                targetpassenger.push_back(p);//����һ���˿�ѹ��
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
    printf("�U����%d ������ʱ��Ϊ%3d�� ����ʱ��Ϊ%3d��U\n",e_id,running_time,spare_time);
}
int Elevator::get_running_time()
{
    return running_time;
}