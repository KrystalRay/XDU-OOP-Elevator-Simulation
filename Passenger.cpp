#include "Passenger.h"
// class Passenger;
    int Passenger::getId() 
    {//��ȡid
        return p_id;
    }
    int Passenger::getDestination()
    {//��ȡĿ�ĵ�
        return p_destination;
    }
    int Passenger::getNowStair() 
    {//��ȡ��ǰ¥��
        return p_nowStair;
    }
    bool Passenger::isfinished()
    {//��ȡ�Ƿ��Ѿ����ģ��
        if(finished)
            return true;
        return false;
    }
    int Passenger::getwaitingtime()
    {//��ȡ�ȴ�ʱ��
        return waiting_time;
    }
    int Passenger::gettimes()
    {//��ȡʱ�������Ĵ�С
        return times_array.size();
    }
    std::vector<int> Passenger::gettimearray()
    {//��ȡʱ������
        return times_array;
    }
    int Passenger::getStatus()
    {
        
        if(p_isin)
            printf("�U�˿�%d�ڵ���%d��,��%d��,Ŀ�ĵ�%d��,������˵���%d��\n",p_id,in_e_id,p_nowStair,p_destination,p_times+1);
        else if(!p_isin&&p_times>=0)
        {
            printf("�U�˿�%d",p_id);
            if(wandering_time>0)
                printf("Ŀǰ�����ε����ε�ʱ�仹��%d��,Ŀ�ĵ�%d��,������˵���%d��\n",wandering_time,p_destination,p_times+1);
            else if(hadcalled)
                printf("�Ѿ�������һ̨���ݣ��ǵ�%d̨���ݣ�Ŀǰ��%d¥�ȴ��ϵ��ݣ�Ŀ�ĵ�%d��,������˵���%d��,ddʱ��%d\n",wait_e_id,p_nowStair,p_destination,p_times+1,per_time);
            else
                printf("Ŀǰ�ڵȵ���,Ŀ�ĵ�%d��,������˵���%d��\n",p_destination,p_times+1);
        }
        else if(p_times<0)
        {
             printf("�U�˿�%d�Ѿ������˵���ģ��\n",p_id);
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
    {//��������Ϣ����˿�
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
    {//�˿͸��º��� ÿ�����һ��
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
            {//����ִ���Ŀ���
                p_isin=false;
                p_times--;
                if(p_times>0)//������г������ݵĴ���
                    p_free(rand()%40+2);
                else if(p_times==0)//���һ�γ��� ǰ��һ��
                    p_free(1);
                else if(p_times<0)
                {//����Ѿ�û��ʣ��ĳ������ݵĴ���
                    wandering_time=9999999;
                    finished=true;
                    // std::cout << "�U�˿�" << p_id << "���ͷţ��������˵���ģ�⡪������������������������������������������������������������������" <<std::endl;
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
        // std::cout << "�U�˿�" << p_id << "���ͷ�" << "�����ε�ʱ����" << wandering_time << "Ŀ�ĵ���" <<p_destination<<std::endl;
    };
    void Passenger::changecalling(int e_id)
    {
        hadcalled=true;
        wait_e_id=e_id;
    }
    int Passenger::SelectDest(int system_time)
    {//����ʱ����Ϊ�˿ͷ���Ŀ�ĵ� 
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
    