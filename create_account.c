#include "header.h"
void SortList(SLL *node)
{
        if(Account_Details==NULL||strcmp(node->Name,Account_Details->Name)<0)
        {
                node->next=Account_Details;
                Account_Details=node;
                return;
        }
        SLL *current=Account_Details;
        while(current->next!=NULL&& strcmp(current->next->Name,node->Name)<0)
        {
                current=current->next;
        }
        node->next=current->next;
        current->next=node;
}
int AccountNumber(void)
{
        int i,j;
        int acc_num;
        acc_num=0;
        for(i=0;i<5;i++)
        {
                j=rand()%10;
                acc_num=(acc_num*10)+j;
        }
        return acc_num;
}
char* Read_Name(void) {
            static char Name[50];
                int i, flag, hasAlpha;
                __fpurge(stdin);
                    while (1)
                    {
                            printf("Enter Account Holder Name: ");
                            fgets(Name, sizeof(Name), stdin);
                            Name[strcspn(Name, "\n")] = '\0';
                            if (strlen(Name) == 0)
                            {
                                    printf("Invalid Name! Please enter again.\n");
                                    continue;
                            }
                            i = 0;
                            while (Name[i] == ' ')
                            {
                                    i++;
                            }
                            if (Name[i] == '\0')
                            {
                                    printf("Invalid Name! Please enter again.\n");
                                    continue;
                            }
                            memmove(Name, Name + i, strlen(Name) - i + 1);
                            hasAlpha = 0;
                            for (i = 0; Name[i] != '\0'; i++)
                            {
                                    if (!isalpha(Name[i]) && Name[i] != ' ')
                                    {
                                            printf("Invalid Name! Please enter again.\n");
                                            hasAlpha = -1;
                                            break;
                                    }
                                    if (isalpha(Name[i]))
                                    {
                                            hasAlpha = 1;
                                    }
                            }
                            if (hasAlpha <= 0)
                            {
                                    continue;
                            }
                            flag = 1;
                            for (i = 0; Name[i] != '\0'; i++)
                            {
                                    if (isalpha(Name[i]) && flag)
                                    {
                                            Name[i] = toupper(Name[i]);
                                            flag = 0;
                                    }
                                    else if (Name[i] == ' ')
                                    {
                                            flag = 1;
                                    }
                            }
                            return Name;
                    }
}

char* Read_PIN(void)
{
        static char pin[5];
        while(1)
        {
                printf("ENTER PIN:");
                __fpurge(stdin);
                scanf("%s",pin);
                if(Compare_int(pin))
                {
                        printf("ENTER NUMERIC CHARACTERS ONLY\n");
                        continue;
                }
                else if(strlen(pin)!=4)
                {
                        printf("ENTER 4 DIGIT PIN\n");
                        continue;
                }
                else
                {
                        return pin;
                }
        }
}
char* Read_RFID(void)
{
        static char rfid[10];
        while(1)
        {
                printf("ENTER 8 DIGIT RFID:");
                __fpurge(stdin);
                scanf("%s",rfid);
                if(Compare_RFID(rfid))
                {
                        printf("RFID IS ALREADY EXISTED\n");
                        continue;
                }
                else if(Compare_int(rfid))
                {
                        printf("ENTER NUMERIC CHARACTERS ONLY\n");
                        continue;
                }
                else if(strlen(rfid)!=8)
                {
                        printf("RFID MUST & SHOULD CONTAIN 8 DIGITS !\n");
                        continue;
                }
                else
                {
                        return rfid;
                }
        }
}
long int Read_Aadhar(void)
{
        long int Aadhar_Number,j;
        int i;
        char ch;
        while(1)
        {
                printf("ENTER 12 DIGIT AADHAR NUMBER:");
                __fpurge(stdin);
                if(scanf("%ld",&Aadhar_Number)!=1)
                {
                        printf("ENTER NUMERIC CHARACTERS ONLY\n");
                        while((ch = getchar()) != '\n' && ch != EOF);
                        continue;
                }
                j=Aadhar_Number;
                i=0;
                while(j>0)
                {
                        j/=10;
                        i++;
                }
                if((i>12)||(i<12))
                {
                        printf("INVALID AADHAR NUMBER!\n");
                }
                else if(Compare_Aadhar(Aadhar_Number))
                {
                        printf("ACCOUNT DETECTED WITH THIS AADHAR NUMBER\n");
                }
                else
                {

                        return Aadhar_Number;
                }
        }
}
long int Read_Contact(void)
{
        long int j,Contact_Number;
        int i;
        char ch;
        while(1)
        {
                printf("ENTER 10 DIGIT CONTACT NUMBER:");
                __fpurge(stdin);
                if(scanf("%ld",&Contact_Number)!=1)
                {
                        printf("YOU HAVE ENTERED NON NUMERIC CHARACTERS ONLY\n");
                        while((ch = getchar()) != '\n' && ch != EOF);
                        continue;
                }
                j=Contact_Number;
                i=0;
                while(j)
                {
                        j/=10;
                        i++;
                }
                if((i>10))
                {
                        printf("INVALID CONTACT NUMBER!\n");
                        printf("YOU HAVE ENTERED MORE THAN 10 NUMERICS\n");
                        continue;
 }
                else if(i<10)
                {
                        printf("INVALID CONTACT NUMBER!\n");
                        printf("YOU HAVE ENTERED LESS THAN 10 NUMERICS\n");
                        continue;
                }
                else if((Contact_Number<6000000000)||(Contact_Number>9999999999))
                {
                        printf("ENTER VALID CONTACT NUMBER\n");
                        continue;
                }
                else
                {
                        return Contact_Number;
                }
        }

}
double Read_Bal(int min)
{
        double Account_Balance;
        char ch;
        while(1)
        {
                printf("ENTER AMOUNT:");
                __fpurge(stdin);
                if(scanf("%lf",&Account_Balance)!=1)
                {
                        printf("ENTER NUMERIC CHARACTERS ONLY\n");
                        while((ch = getchar()) != '\n' && ch != EOF);
                        continue;
                }
                if((Account_Balance<500)&&min)
                {
                        printf("MINIMUN BALANCE SHOULD BE 500\- \n");
                        continue;
                }
                else if(Account_Balance<10)
                {
                        printf("AMOUNT SHOULD BE IN MULTIPLES OF 10'S,100'S etc...\n");
                        continue;
                }
                else
                {
                        return Account_Balance;
                }
        }
}
void Create_Account(void)
{
        size_t now;
        struct tm *current_time;
        char c;
        int i,flag=1,max,min;
        long int j;
        time(&now);
        current_time=localtime(&now);
        SLL *New_Account=NULL;

        New_Account=calloc(1,sizeof(SLL));

        New_Account->number=0;
        New_Account->flag1=0;
        New_Account->flag2=0;
        New_Account->block=0;

        strcpy(New_Account->Name,Read_Name());

        strcpy(New_Account->RFID,Read_RFID());

        strcpy(New_Account->pin,Read_PIN());

        New_Account->Account_Number=AccountNumber();

        New_Account->Contact_Number=Read_Contact();
        New_Account->history[New_Account->number].year=current_time->tm_year+1900;
        New_Account->history[New_Account->number].month=current_time->tm_mon+1;
        New_Account->history[New_Account->number].day=current_time->tm_mday;
        New_Account->history[New_Account->number].hour=current_time->tm_hour;
        New_Account->history[New_Account->number].min=current_time->tm_min;
        New_Account->next=0;
        max=23782548;min=24748728;
        New_Account->history[New_Account->number].trsncid=(rand()%(max-min+1))+min;
        New_Account->number++;
        if(Account_Details==NULL)
        {
                New_Account->next=0;
                Account_Details=New_Account;
        }
        else
        {
                New_Account->next=Account_Details;
                Account_Details=New_Account;
        //      SortList(New_Account);
        }
}
   
