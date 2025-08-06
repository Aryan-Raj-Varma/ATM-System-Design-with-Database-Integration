#include"header.h"
SLL *Account_Details=NULL;
char pin[10];
SLL *rfid;
int open_uart()
{
        struct termios options;
        int fd=open("/dev/ttyUSB0",O_RDWR|O_NOCTTY);
        if(fd==-1)
        {
                perror("unable to open UART");
                exit(0);
        }
        fcntl(fd,F_SETFL,0);

        tcgetattr(fd,&options);

        cfmakeraw(&options);
        cfsetispeed(&options,B9600);
        cfsetospeed(&options,B9600);

        options.c_cflag &=~PARENB;
        options.c_cflag &=~CSTOPB;
        options.c_cflag &=~CSIZE;
        options.c_cflag |=CS8;
        options.c_cflag |=(CREAD|CLOCAL);
        options.c_lflag &=~(ICANON|ECHO|ECHOE|ISIG);
        options.c_oflag &=~OPOST;

        tcsetattr(fd,TCSANOW|TCSAFLUSH,&options);
        usleep(10000);
        return fd;
}
int main()
{
        int fd,i;
        char buff[30];
        fd=open_uart();
        srand(time(NULL));
        printf("%d\n",fd);
        Sync_From_File();
        while(1)
        {
#ifdef  DEBUG
                read_str(0,buff,30);
                //read(0,buff,sizeof(buff));
#else
                puts("in while");
                read_str(fd,buff,30);
                //read(fd,buff,sizeof(buff));
#endif
                printf("*%s*\n",buff);
                //printf("hello\n");
#ifdef DEBUG
                if(strcmp(buff,"#EXIT$")==0)
                {
                        write(1,"exited",strlen("exited"));
                        break;
                }
                if(Account_Details==NULL)
                {
                        write(1,"@ERR#INVALID_CARD$",strlen("@ERR#INVALID_CARD$"));
                        break;
                }
#else
#endif
                if(strcmp(buff,"#OK:CNTD$")==0)
                {
                        printf("CONNECTED\n");
#ifdef DEBUG
                        write(1,"@OK:CNTD$",strlen("@OK:CNTD$"));
#else
                        write(fd,"@OK:CNTD$",strlen("@OK:CNTD$"));
#endif
                }
                switch(buff[1])
                {
                        case 'r':printf("in rfid call\n");
                                 Verify_RFID(buff,fd);
                                 break;
                        case 'p':printf("in pin call\n");
                                 Verify_PIN(buff,fd);
                                 break;
                        case 'B':BLK_CARD(fd);
                                 break;
                        case 'R':BAL_ENQ(fd);
                                 break;
                        case 'D':DEP_BAL(buff,fd);
                                 break;
                        case 'W':WITH_BAL(buff,fd);
                                 break;
                        case 'P':PIN_CHANG(buff,fd);
                                break;
                        case 'M':MINI_STMT(fd);
                                 break;

                }
                for(i=0;buff[i]!='\0';i++)
                {
                        buff[i]=0;
                }
        }
        return 0;
}
