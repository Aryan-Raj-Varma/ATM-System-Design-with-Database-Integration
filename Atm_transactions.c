#include "headers.h"

void Bal_Enq()
{
                        s8 buffer[20]={0},bal[6]={0};
                        strcpy((char *)buffer,"#REQ$");
                        send_buf_to_uart0(buffer);
                        recv_buf_from_uart0(buffer,sizeof(buffer));
                        CmdLCD(CLEAR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD((s8*)"WAITING FOR RESPONSE");
                        delay_s(1);
                        CmdLCD(CLEAR_LCD);
        if(str_ncmp(buffer,(s8*)"@BAL:",5)==0)
        {
                        strcpy((char*)bal,(const char*)buffer+5);
                        bal[str_len(bal)-1]='\0';
                        CmdLCD(CLEAR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD((s8 *)"AVL BALANCE:");
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD(bal);
                        delay_s(2);
        }
}
u32 Deposit()
{
                        s8 amount[10],buffer[30];
                        u32 paisa;
        while(1)
        {               CmdLCD(CLEAR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD((s8 *)"DEPOSIT AMOUNT");
                        givenpin=Read_String();
                                if(givenpin==NULL)
                                {
                                                        CmdLCD(CLEAR_LCD);
                                                        CmdLCD(GOTO_LINE1_POS0);
                                                        StrLCD((s8*)"SESSION TIMED OUT ! ");
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("PLEASE TRY AGAIN ");
                                                        delay_s(1);
                                                        CmdLCD(CLEAR_LCD);
                                                        send_buf_to_uart0((s8*)"#TIMEOUT$");
                                                        return 1;
                                }
                                paisa=atoi_arm(givenpin);
                                if((paisa>0&&paisa<=MAX_AMOUNT))
                                {
                                                break;  // **Exit loop if amount is valid**
                                }
                                else
                                {
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD("INVALID AMOUNT! ");
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD("AMOUNT <= 30000");
                                                delay_s(1);
                                                /*CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8 *)"DEPOSIT AMOUNT"); */
                                }

        }
                                strcpy((char *)amount,(const char*)givenpin);
                                sprintf((char*)buffer,"#DEP:%s$",amount);
                                send_buf_to_uart0(buffer);
                                recv_buf_from_uart0(buffer,sizeof(buffer));
                                CmdLCD(GOTO_LINE1_POS0);
                                //StrLCD(buffer);
                                delay_ms(400);
                                if(str_ncmp(buffer,(s8*)"@BAL:",5)==0)
                                {
                                                /*strcpy((char*)bal,(const char*)buffer+5);
                                                bal[str_len(bal)-1]='\0';*/
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8 *)"DEPOSIT SUCCESS");
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD(amount);
                                                delay_s(2);
                                }
                                return 0;
}
u32 Withdraw()
{
                        s8 amount[10],buffer[40],bal[6];
                        u32 paisa;

        while(1)
        {
                         CmdLCD(CLEAR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD((s8 *)"WITHDRWAL AMOUNT");
                        givenpin=Read_String();
                                if(givenpin==NULL)
                                {
                                                        CmdLCD(CLEAR_LCD);
                                                        CmdLCD(GOTO_LINE1_POS0);
                                                        StrLCD((s8*)"SESSION TIMED OUT ! ");
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("PLEASE TRY AGAIN ");
                                                        delay_s(1);
                                                        CmdLCD(CLEAR_LCD);
                                                        send_buf_to_uart0((s8*)"#TIMEOUT$");
                                                        return 1;
                                }
                                paisa=atoi_arm(givenpin);
                                //if((givenpin[strlen((const char*)givenpin)-1]!='0')&&(givenpin[strlen((const char*)givenpin)-2]!='0'))
                                if(givenpin[strlen((const char*)givenpin)-1]!='0')
                                {
                                                if(givenpin[strlen((const char*)givenpin)-2]!='0')
                                                {
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD("INVALID AMOUNT! ");
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD("MULTIPLES OF 100's");
                                                delay_s(1);
                                                }
                                        /*
                                        CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8 *)"DEPOSIT AMOUNT");  */
                                }
                                else if(paisa>0&&paisa<=MAX_AMOUNT)
                                {
                                                break;  // **Exit loop if amount is valid**
                                }
                                else
                                {
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD("INVALID AMOUNT! ");
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD("AMOUNT <= 30000");
                                                delay_s(1);
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8 *)"DEPOSIT AMOUNT");
                                }
                }
                                strcpy((char *)amount,(const char*)givenpin);
                                sprintf((char*)buffer,"#WTHD:%s$",amount);
                                send_buf_to_uart0(buffer);
                                recv_buf_from_uart0(buffer,sizeof(buffer));
                                CmdLCD(GOTO_LINE1_POS0);
                        //      StrLCD(buffer);
                                delay_ms(100);
                                if(str_ncmp(buffer,(s8*)"@BAL:",5)==0)
                                {
                                                strcpy((char*)bal,(const char*)buffer+5);
                                                bal[str_len(bal)-1]='\0';
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8 *)"WITHDRAW SUCCESS");
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD(amount);
                                                delay_s(2);
                                }
                                else if(str_cmp(buffer,(s8*)"@ERR$")==0)
                                {
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8*)"ERROR !");
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD((s8 *)"LESS FUNDS !!!");
                                                delay_s(2);
                                }
                                return 0;
}
u32 Pin_Change()
{
                                s8 *oldpassword,newpassword[5],buffer[20];
                                u8 c;
                                u32 cont=0;
                                CmdLCD(GOTO_LINE1_POS0);
                                StrLCD((s8 *)"ENTER OLD PIN");
                                oldpassword=Read_PIN(1);
                                if(oldpassword==NULL)
                                        {
                                                        CmdLCD(CLEAR_LCD);
                                                        CmdLCD(GOTO_LINE1_POS0);
                                                        StrLCD((s8*)"SESSION TIMED OUT ! ");
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("PLEASE TRY AGAIN ");
                                                        delay_s(1);
                                                        CmdLCD(CLEAR_LCD);
                                                        send_buf_to_uart0((s8*)"#TIMEOUT$");
                                                                        return 1;
                                        }
                                CmdLCD(CLEAR_LCD);
                                        attempts++;
                if(str_cmp(pin,oldpassword)==0)
                {
                                        delay_ms(5);
                                        while(1)
                                        {
                                                pinchange++;
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8 *)"ENTER NEW PIN");
                                                oldpassword=Read_PIN(1);
                                                if(oldpassword==NULL)
                                                        {
                                                                CmdLCD(CLEAR_LCD);
                                                                CmdLCD(GOTO_LINE1_POS0);
                                                                StrLCD((s8*)"SESSION TIMED OUT ! ");
                                                                CmdLCD(GOTO_LINE2_POS0);
                                                                StrLCD("PLEASE TRY AGAIN ");
                                                                delay_s(1);
                                                                CmdLCD(CLEAR_LCD);
                                                                send_buf_to_uart0((s8*)"#TIMEOUT$");
                                                                return 1;
                                                        }
                                                strcpy((char*)newpassword,(const char*)oldpassword);
                                                delay_ms(50);
                                                CmdLCD(CLEAR_LCD);
                                                CmdLCD(GOTO_LINE1_POS0);
                                                StrLCD((s8 *)"RE ENTER NEW PIN");
                                                oldpassword=Read_PIN(1);
                                                if(oldpassword==NULL)
                                                        {
                                                                         CmdLCD(CLEAR_LCD);
                                                        CmdLCD(GOTO_LINE1_POS0);
                                                        StrLCD((s8*)"SESSION TIMED OUT ! ");
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("PLEASE TRY AGAIN ");
                                                        delay_s(1);
                                                        CmdLCD(CLEAR_LCD);
                                                        send_buf_to_uart0((s8*)"#TIMEOUT$");
                                                        return 1;
                                                        }
                                                CmdLCD(CLEAR_LCD);
                                                delay_ms(50);
                                                if(str_cmp(oldpassword,newpassword)==0)
                                                {
                                                        strcpy((char *)pin,(const char *)oldpassword);
                                                        sprintf((char*)buffer,"#PINCHG:%s$",pin);
                                                        send_buf_to_uart0(buffer);
                                                        recv_buf_from_uart0(buffer,sizeof(buffer));
                                                        if(str_cmp(buffer,(s8*)"@CGD$")==0)
                                                        {
                                                                CmdLCD(GOTO_LINE1_POS0);
                                                                StrLCD((s8 *)"SUCCEFULLY UPDATED");
                                                                delay_s(2);
                                                                CmdLCD(CLEAR_LCD);
                                                                pinchange=0;
                                                                attempts=0;
                                                                return 0;
                                                        }
                                                }
                                                else
                                                {
                                                        IOSET0=1<<LED;
                                                        CmdLCD(GOTO_LINE1_POS0);
                                                        StrLCD((s8 *)"WRONG NEW PIN!");
                                                        delay_s(2);
                                                        IOCLR0=1<<LED;
                                                        //FOR NEW PIN WROGN ENETRY 3 TIMES
                                                        if(pinchange>=3)
                                                        {
                                                                        send_buf_to_uart0((s8*)"#BLK$");
                                                                        recv_buf_from_uart0(buffer,sizeof(buffer));
                                                                        if(str_cmp(buffer,(s8*)"@BLK$")==0)
                                                                        {
                                                                                        IOSET0=1<<LED;
                                                                                        CmdLCD(CLEAR_LCD);
                                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                                        StrLCD((s8 *)"CARD BLOCKED !");
                                                                                        delay_s(2);
                                                                                        StrLCD((s8 *)"                ");
                                                                                        IOCLR0=1<<LED;
                                                                                        return 1;
                                                                        }
                                                        }
                                                        while(1)
                                                        {
                                                                CmdLCD(GOTO_LINE1_POS0);
                                                                StrLCD((s8 *)"1:TRY AGAIN PIN CHG");
                                                                CmdLCD(GOTO_LINE2_POS0);
                                                                StrLCD((s8 *)"2:EXIT");
                                                                c=Read_key();
                                                                while((ColScan()&1)==0);
                                                                CmdLCD(CLEAR_LCD);
                                                                if(c==TIMEOUT_FLAG)
                                                                {
                                                                         CmdLCD(CLEAR_LCD);
                                                                                CmdLCD(GOTO_LINE1_POS0);
                                                                                StrLCD((s8*)"SESSION TIMED OUT ! ");
                                                                                CmdLCD(GOTO_LINE2_POS0);
                                                                                StrLCD("PLEASE TRY AGAIN ");
                                                                                delay_s(1);
                                                                                CmdLCD(CLEAR_LCD);
                                                                                send_buf_to_uart0((s8*)"#TIMEOUT$");
                                                                                return 1;
                                                                }
                                                                if(c=='1')
                                                                {
                                                                        cont=1;
                                                                        break;
                                                                }
                                                                else if(c=='2')
                                                                {
                                                                        CmdLCD(CLEAR_LCD);
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD((s8 *)"EXIT PIN CHANGE");
                                                                        delay_s(2);
                                                                        StrLCD((s8 *)"                ");
                                                                        break;
                                                                }
                                                                else
                                                                {
                                                                        CmdLCD(CLEAR_LCD);
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD((s8 *)"INVALID ENTRY");
                                                                        delay_s(2);
                                                                        StrLCD((s8 *)"                ");
                                                                }
                                                        }
                                                        if(cont)
                                                        {
                                                                continue;
                                                        }
                                                        else
                                                        {
                                                                return 0;
                                                        }
                                        }
                        }
                }
                else
                {
                        CmdLCD(CLEAR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD((s8 *)"WRONG OLD PIN!");
                        delay_s(2);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD((s8 *)"                ");
                }
                                //FOR 3 ATTEMPTS OVERED
                if(attempts>=3)
                {
                                        send_buf_to_uart0((s8 *)"#BLK$");
                                        recv_buf_from_uart0(buffer,sizeof(buffer));
                                        if(str_cmp(buffer,(s8*)"@BLK$")==0)
                                        {
                                                        CmdLCD(CLEAR_LCD);
                                                        CmdLCD(GOTO_LINE1_POS0);
                                                        StrLCD((s8 *)"CARD BLOCKED !");
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD((s8 *)"CONTACT MAIN BRCH");
                                                        delay_s(2);
                                                        return 1;
                                        }
                }
                return 0;
}
/*void Mini_Statement()
{
        s8 buffer[100];
        send_buf_to_uart0((s8*)"#MINI#REQ$");
        recv_buf_from_uart0(buffer,sizeof(buffer));
        if(str_ncmp(buffer,(s8*)"@OK#STMT:",9)==0)
        {
                strcpy((char*)buffer,(const char*)buffer+9);
                buffer[str_len(buffer)-1]='\0';
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD((s8*)"TRSNC HISTORY");
                rotate_string((const char*)buffer,str_len(buffer),1);
                CmdLCD(CLEAR_LCD);
        }
}*/
void Mini_Statement()
{
    s8 buffer[100], *ptr;
    s8 transaction[30];  // Buffer for individual transaction
    send_buf_to_uart0((s8*)"#MINI#REQ$");
    recv_buf_from_uart0(buffer, sizeof(buffer));

    if (str_ncmp(buffer, (s8*)"@OK#STMT:", 9) == 0)
    {
        strcpy((char*)buffer, (const char*)buffer + 9);  // Remove prefix "@OK#STMT:"
        buffer[str_len(buffer) - 1] = '\0';  // Remove trailing '$'

        // **Process transactions one by one**
        ptr=(s8*)strtok((char*)buffer, "|");  // Split transactions using '|'
        while (ptr != NULL)
        {
            strcpy((char *)transaction,(const char*)ptr);  // Copy individual transaction

            CmdLCD(CLEAR_LCD);
                        CmdLCD(GOTO_LINE1_POS0);
                        StrLCD((s8*)"TRSNC HISTORY");
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD(transaction);  // Display transaction

            delay_s(2);  // Wait 2 seconds before showing next transaction

            ptr=(s8*)strtok(NULL,"|");  // Get the next transaction
        }
    }
}
