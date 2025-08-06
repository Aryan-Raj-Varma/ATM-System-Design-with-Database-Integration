#include "header.h"
void Transfer_Money(void)
{
        SLL *temp1,*temp2;
        int acc_num1,acc_num2,max=24753289,min=23186489;
        double amount;
        size_t now;
        struct tm *current_time;
        time(&now);
        current_time=localtime(&now);
        printf("Enter your Account Number:");
        __fpurge(stdin);
        scanf("%d",&acc_num1);
        temp1=Account_Details;
        while(temp1)
        {
                if(temp1->Account_Number==acc_num1)
                {
                        break;
                }
                temp1=temp1->next;
        }
        if(temp1==NULL)
        {
                printf("Invalid Account Number!\n");
        }
        else
        {
                printf("Enter Amount to be Transfered account number:");
                __fpurge(stdin);
                scanf("%d",&acc_num2);
                temp2=Account_Details;
                while(temp2)
                {
                        if(temp2->Account_Number==acc_num2)
                        {
                                break;
                        }
                        temp2=temp2->next;
                }
                if(temp2==NULL)
                {
                        printf("Invalid account number!\n");
                }
                else
                {
amount:         amount=Read_Bal(0);
                if(amount>temp1->Account_Balance)
                {
                        printf("Insufficient Balance!\n");
                        goto amount;
                }
                else
                {
                        temp1->Account_Balance=(temp1->Account_Balance-amount);
                        temp1->Trasnction_Count++;
                        temp2->Account_Balance=(temp2->Account_Balance+amount);
                        temp2->Trasnction_Count++;
                        printf("TRANSFER SUCCESSFUL\n");
                        if(temp1->number>=5)
                        {
                                temp1->number=0;
                                temp1->flag1=1;
                        }
                        memmove(&temp1->history[1],&temp1->history[0],4*sizeof(Trsnc));
                        strcpy(temp1->history[0].type,"Transfer Out");
                        temp1->history[0].amount=amount;
                        temp1->history[0].Acc_Num=temp1->Account_Number;
                        temp1->history[0].year=current_time->tm_year+1900;
                        temp1->history[0].month=current_time->tm_mon+1;
                        temp1->history[0].day=current_time->tm_mday;
                        temp1->history[0].hour=current_time->tm_hour;
                        temp1->history[0].min=current_time->tm_min;
                        temp1->history[0].trsncid=(rand()%(max-min+1))+min;
                        temp1->number++;
                        if(temp2->number>=5)
                        {
                                temp2->number=0;
                                temp2->flag1=1;
                        }
                        memmove(&temp2->history[1],&temp2->history[0],4*sizeof(Trsnc));
                        strcpy(temp2->history[0].type,"Transfer In");
                        temp2->history[0].amount=amount;
                        temp2->history[0].Acc_Num=temp2->Account_Number;
                        temp2->history[0].year=current_time->tm_year+1900;
                        temp2->history[0].month=current_time->tm_mon+1;
                        temp2->history[0].day=current_time->tm_mday;
                        temp2->history[0].hour=current_time->tm_hour;
                        temp2->history[0].min=current_time->tm_min;
                        temp2->history[0].trsncid=(rand()%(max-min+1))+min;
                        temp2->number++;
                }
                }
        }
}
