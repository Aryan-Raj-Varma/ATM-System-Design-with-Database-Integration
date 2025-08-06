#include"header.h"

int Compare_Aadhar(long int aadhar)
{
        SLL *node;
        node=Account_Details;
        while(node!=NULL)
        {
                if(node->Aadhar_Number==aadhar)
                {
                        return 1;
                }
                node=node->next;
        }
        return 0;
}
int Compare_RFID(char *str)
{
        SLL *node;
        node=Account_Details;
        while(node!=NULL)
        {
                if(strcmp(node->RFID,str)==0)
                {
                        return 1;
                }
                node=node->next;
        }
        return 0;
}
int Compare_int(char *str)
{
        char c;
        int i=0;
        while(str[i]!='\0')
        {
                c=str[i++];
                if((c>=48)&&(c<=57))
                {
                       continue;
                }
                else
                {
                        return 1;
                }
        }
        return 0;
}
void read_str(int fd,char *str,int len)
{
        int i=0,j=0;
        char ch;

        for(i=0;i<len-1;i++)
        {
                j=read(fd,&ch,1);
                printf("%c",ch);
                if(j==-1)
                {
                        perror("read_str");
                        exit(0);
                }
                else if(j==0)
                {
                        i--;
                        continue;
                }
                str[i]=ch;
#ifdef DEBUG
                if(ch=='\n')
                {
                        str[i]='\0';
                        break;
                }
                else if(ch=='\r')
                {
                        continue;
                }
#else
                if(ch=='$')
                {
                        str[i+1]='\0';
                        break;
                }
#endif
        }
}
void Change_Stat()
{
        char str[10];
        SLL *node=Account_Details;
        while(1)
        {
                printf("Enter 8 digit Card Number:");
                __fpurge(stdin);
                scanf("%s",str);
                if(Compare_int(str))
                {
                        printf("enter integers only\n");
                        continue;
                }
                else if(strlen(str)!=8)
                {
                        printf("Enter 8 Digit Card Number\n");
                        continue;
                }
                else
                {
                        break;
                }
        }
        while(node!=NULL)
        {
                if(strcmp(node->RFID,str)==0)
                {
                       break;
                }
                node=node->next;
        }
        if(!node)
        {
                printf("No Account Found on this Card:%s\n",str);
                return ;
        }
        else if(node->block)
        {
                printf("blocked status is changed\n");
                printf("Card Is Unblocked Now\n");
                node->block=0;
        }
        else if(!node->block)
        {
                printf("account is not blocked\n");
        }

}
