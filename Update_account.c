#include"header.h"
void Update_Menu()
{
        printf("n/N:Update Name\n"
                "a/A:Update Aadhar number\n"
                "m/M:Update mobile number\n"
                "r/R:update RFID number\n"
                "p/P:Update PIN\n"
                "e/E:Exit\n");
        printf("enter your option:\n");
}

void Update_Account()
{
        int account_num;
        char c;
        SLL *node=Account_Details;
        if(node==NULL)
        {
                printf("no account details\n");
        }
        else
        {
                printf("ENTER ACCOUNT NUMBER:");
                scanf("%d",&account_num);
                while(node!=NULL)
                {
                        if(account_num==node->Account_Number)
                        {
                                break;
                        }
                        node=node->next;
                }

                if(node!=NULL)
                {

                        while(1)
                        {
                                Update_Menu();
                                __fpurge(stdin);
                                scanf("%c",&c);
                                switch(c)
                                {
                                        case 'a':
                                        case 'A':node->Aadhar_Number=Read_Aadhar();
                                                 printf("UPDATED AADHAR NUMBER SUCCESSFULLY\n");
                                                 break;
                                        case 'm':
                                        case 'M':node->Contact_Number=Read_Contact();
                                                 printf("UPDATED MOBILE NUMBER SUCCESSFULLY\n");
                                                 break;
                                        case 'r':
                                        case 'R':strcpy(node->RFID,Read_RFID());
                                                 printf("UPDATED RFID SUCCESSFULLY\n");
                                                 break;
                                        case 'p':
                                        case 'P':strcpy(node->pin,Read_PIN());
                                                 printf("UPDATED PIN SUCCESSFULLY\n");
                                                 break;
                                        case 'n':
                                        case 'N':strcpy(node->Name,Read_Name());
                                                 printf("UPDATED NAME SUCCESSFULLY\n");
                                                 break;
                                        case 'e':
                                        case 'E':printf("EXITED FROM UPDATION\n");
                                                 return ;
                                }
                        }

                }
                else
                {
                        printf("NO ACCOUNT FOUND ON THIS NUMBER :%d\n",account_num);

                }
        }
}
