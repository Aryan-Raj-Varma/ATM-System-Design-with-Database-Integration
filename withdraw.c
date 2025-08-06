#include "header.h"
int count(long int num)
{
        int d=0,j;
        while(num>0)
        {
                j=num%10;
                d++;
                num/=10;
        }
        if(d>10)
        return 1;
        else
        return 0;
}
void Withdraw(void)
{
        SLL *temp;
        size_t now;
        struct tm *current_time;
        long int acc_num;
        int i,max=27835438,min=26857429;
        double amount;
        time(&now);
        current_time=localtime(&now);
        printf("Enter Account Number/Aadhar Number:");
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
                printf("Invalid Account Number!\n");
        }
        else
        {
                if(count(acc_num))
                {
OTP:printf("Enter the OTP sent to your mobile number:");
                        scanf("%d",&i);
                        if(i<0)
                        {
                                printf("Invalid OTP !");
                                goto OTP;
                        }
                }

amount:         amount=Read_Bal(0);
                if(amount>temp->Account_Balance)
                {
                        printf("Insufficient balance!\n");
                        goto amount;
                }
                else
                {
                        if(temp->number>=5)
                        {
                                temp->number=0;
                                temp->flag1=1;
                        }
                        temp->Account_Balance=(temp->Account_Balance-amount);
                        temp->Trasnction_Count++;
                        memmove(&temp->history[1],&temp->history[0],4*sizeof(Trsnc));
                        strcpy(temp->history[0].type,"wITHDRAW");
                        temp->history[0].amount=amount;
                        temp->history[0].Acc_Num=temp->Account_Number;
                        temp->number++;
                        temp->history[0].year=current_time->tm_year+1900;
                        temp->history[0].month=current_time->tm_mon+1;
                        temp->history[0].day=current_time->tm_mday;
                        temp->history[0].hour=current_time->tm_hour;
                        temp->history[0].min=current_time->tm_min;
                        temp->history[0].trsncid=(rand()%(max-min+1))+min;
                        printf("WITHDRAWAL SUCCESSFUL\n");
                }
        }
}
