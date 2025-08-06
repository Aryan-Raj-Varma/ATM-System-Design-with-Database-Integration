#include "header.h"
void Balance_Enquery(void)
{
        SLL *temp;
        long int acc_num;
        int i;
        temp=Account_Details;
        if(temp==NULL)
        {
                printf("no Account created upto now\n");
        }
        printf("Enter Account Number/Aadhar Number:");
        __fpurge(stdin);
        scanf("%ld",&acc_num);
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
otp:printf("Enter OTP sent to your phone number:");
                        scanf("%d",&i);
                        if(i<0)
                        {
                                printf("Invalid OTP!\n");
                                goto otp;
                        }
                }
                printf("Amount is:%.3lf\n",temp->Account_Balance);
        }
}
