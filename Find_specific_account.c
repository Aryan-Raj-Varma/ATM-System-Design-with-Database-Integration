#include "header.h"
char* getstring(void)
{
        int i=0;
        char *p=NULL;
        __fpurge(stdin);
        do
        {
                p=realloc(p,(i+1)*sizeof(char));
                p[i]=getchar();
        }while(p[i++]!='\n');
        p[i-1]='\0';
        return p;
}
long int myatoi(char *name)
{
        int i;
        long int num=0;
        for(i=0;name[i]!='\0';i++)
        {
                num=(num*10)+(name[i]-48);
        }
        return num;
}
void Find_Specific_Account(void)
{
        SLL *temp;
        char *name;
        long int acc_num;
        printf("Enter Account Number/Aadhar Number:");
        name=getstring();
        temp=Account_Details;
        if((name[0]>='0')&&(name[0]<='9'))
        {
                acc_num=myatoi(name);
                while(temp)
                {
                        if((acc_num==temp->Account_Number)||(acc_num==temp->Aadhar_Number))
                        {
                                break;
                        }
                        temp=temp->next;
                }
                if(temp==NULL)
                {
                        printf("Invalid account/Contact Number!\n");

                }
                else
                {
                        printf("name:%s\n",temp->Name);
                        printf("Account Number:%d\n",temp->Account_Number);
                        printf("Contact Number: +91 %ld\n",temp->Contact_Number);
                        printf("Aadhar Number:%ld\n",temp->Aadhar_Number);
                        printf("No.of Trasnctions:%d\n",temp->Trasnction_Count);
                }

        }
        else
        {

                printf("Account Details Should BE Displayed Only on Account/AAddhar Number\n");
        }
}
