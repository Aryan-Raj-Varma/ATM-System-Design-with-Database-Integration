#include "header.h"
void Deposit(void)
{
        SLL *temp;
        //Trsnc *New_History;
        int i,max=23578432,min=22548765;
        size_t now;
        struct tm *current_time;
        double amount;
        long int acc_num;
        time(&now);
        current_time=localtime(&now);
        printf("Enter account number/Aadhar Number:");
        __fpurge(stdin);
        scanf("%ld",&acc_num);
        temp=Account_Details;
        while(temp)
        {
                if((temp->Account_Number==acc_num)||(temp->Aadhar_Number==acc_num))
                {
                        break;
                }
                temp=temp->next;
        }
        if(temp==NULL)
        {
                printf("Invalid account number !\n");
        }
        else
        {
                if(count(acc_num))
                {
Otp:printf("Enter OTP sent to your phone number:");
                        scanf("%d",&i);
                        if(i<0)
                        {
                                printf("Invalid OTP!\n");
                                goto Otp;
                        }
                }
                amount=Read_Bal(0);
                temp->Trasnction_Count++;
                temp->Account_Balance=(temp->Account_Balance+amount);
                printf("DEPSOIT SUCCESSFUL\n");
                if(temp->number>=5)
                {
                        temp->number=0;
                        temp->flag1=1;
                }
                memmove(&temp->history[1],&temp->history[0],4*sizeof(Trsnc));
                strcpy(temp->history[0].type,"DEPOSIT");
                temp->history[0].amount=amount;
                temp->history[0].Acc_Num=temp->Account_Number;
                temp->history[0].year=current_time->tm_year+1900;
                temp->history[0].month=current_time->tm_mon+1;
                temp->history[0].day=current_time->tm_mday;
                temp->history[0].hour=current_time->tm_hour;
                temp->history[0].min=current_time->tm_min;
                temp->history[0].trsncid=(rand()%(max-min+1))+min;
                temp->number++;
        }
}
