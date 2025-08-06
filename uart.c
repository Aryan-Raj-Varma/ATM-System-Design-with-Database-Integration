#include "headers.h"

void Init_UART0(void)
{
        PINSEL0=((PINSEL0&~(3<<(2*0)))|(1<<(2*0)));
        PINSEL0=((PINSEL0&~(3<<(2*1)))|(1<<(2*1)));
        U0LCR=((1<<DLAB_BIT)|(WORD_LEN_SEL_BITS));
        U0DLL=(DIVISOR);
        U0DLM=(DIVISOR>>8);
        U0LCR&=~(1<<DLAB_BIT);
        U0IER = 0x01;
  VICIntSelect = 0x00000000;
  VICIntEnable |= (1 << 6);
  VICVectAddr0 = (unsigned int)UART0_ISR;
  VICVectCntl0 = 0x20 | 6;
}
void U0_TxByte(u8 sByte)
{
        U0THR=sByte;
        while(((U0LSR>>TEMT_BIT)&1)==0);
}
u8  U0_RxByte(void)
{
        while(((U0LSR>>DR_BIT)&1)==0);
        return U0RBR;
}
void U0_TxStr(s8 *str)
{
        while(*str)
                U0_TxByte(*str++);
}

s8* U0_RxStr(void)
{
        static s8 buffer[100];
        u32 i=0;
        while(1)
        {
                buffer[i]=U0_RxByte();
                if(buffer[i]=='$')
                {
                        break;
                }
                i++;
        }
        buffer[i+1]='\0';
        return buffer;
}

void Init_UART1(void)
{
        PINSEL0=((PINSEL0&~(3<<(2*8)))|(1<<(2*8)));
        PINSEL0=((PINSEL0&~(3<<(2*9)))|(1<<(2*9)));
        U1LCR=((1<<DLAB_BIT)|(WORD_LEN_SEL_BITS));
        U1DLL=(DIVISOR);
        U1DLM=(DIVISOR>>8);
        U1LCR&=~(1<<DLAB_BIT);
        U1IER = 0x01;
  VICIntSelect =0x00000000;
  VICIntEnable |= (1 << 7);
  VICVectAddr1 = (unsigned int)UART1_ISR;
  VICVectCntl1 = 0x20 | 7;
}
void U1_TxByte(u8 sByte)
{
        U1THR=sByte;
        while(((U1LSR>>TEMT_BIT)&1)==0);
}
u8  U1_RxByte(void)
{
        while(((U1LSR>>DR_BIT)&1)==0);
        return U1RBR;
}
void U1_TxStr(s8 *str)
{
        while(*str)
                U1_TxByte(*str++);
}

s8* U1_RxStr(void)
{
        static s8 buffer[100];
        u32 i=0;
        while(1)
        {
                buffer[i]=U1_RxByte();
                if(buffer[i]=='$')
                {
                        break;
                }
                i++;
        }
        buffer[i+1]='\0';
        return buffer;
}
void UART1_ISR(void)__irq
{
    u8 ch;
                u32 iirval=U1IIR;
                IOSET0=1<<LED;
    if((iirval&0x0F)==0x04)
    {
        ch=U1RBR;
                        if(!uart1_rx_complete)
                        {
                                if(!uart1_rx_started)
                                {
                                        if(ch==0x02)
                                        //if(ch=='2')
                                        {
                                                uart1_rx_index=0;
                                                uart1_rx_started=1;
                                        }
                                }
                                else
                                {
                                        //      if(ch=='3')
                                        if(ch==0x03)
                                        {
                                                uart1_rx_buf[uart1_rx_index]='\0';
                                                        uart1_rx_complete=1;
                                                        uart1_rx_started=0;
                                                        uart1_rx_index=0;
                                        }
                                        else if((uart1_rx_index<MAX_BUF_LEN1-1)&&((ch>=48)&&(ch<=57)))
                                        {
                                            uart1_rx_buf[uart1_rx_index++]=ch;
                                        }
                                }
                        }
                }
                IOCLR0=1<<LED;
    VICVectAddr=0x00;
}
void UART0_ISR(void) __irq
{
    char ch;
    static int receiving = 0;
    u32 iirval = U0IIR;

    if ((iirval & 0x0F) == 0x04)
    {
        ch = U0RBR;

        if (ch == '@')
        {
            receiving = 1;
            uart0_rx_index = 0;
            uart_checksum = 0;
        }

        if (receiving && uart0_rx_index < MAX_BUF_LEN2 - 1)
        {
            if (ch == '@' || ch == '#' || ch == '$' || ch == ':' || ch == '_' || ch=='.'||ch=='|'||ch=='-'||
                (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            {
                uart0_rx_buf[uart0_rx_index++] = ch;
                uart_checksum += ch;
            }

            // Check if `$` is received
            if (ch == '$')
                                //              if(ch=='3')
            {
                uart0_rx_buf[uart0_rx_index] = '\0';
                receiving = 0;

                if (uart_checksum > 0 && uart0_rx_index > 1)
                {
                    uart0_rx_complete = 1;
                    uart0_rx_valid = 1;
                }
                else
                {
                    uart0_rx_complete = 0;
                    uart0_rx_valid = 0;
                }

                uart0_rx_index = 0;
            }
        }
    }

    // **If `$` was never received, force retransmission**
    if (receiving && uart0_rx_index > 0 && uart0_rx_buf[uart0_rx_index - 1] != '$')
    {
        uart0_rx_valid = 0; // Mark as invalid
        uart0_rx_complete = 0; // Ensure retry happens
    }

    VICVectAddr = 0x00;
}
