#include "headers.h"

s8 MENU[][16]={"1:BALANCE","2:DEPOSIT","3:WITHDRAW","4:PIN CHANGE","5:MINI STATEMENT","6:EXIT"};
s8 KPMLUT[][4]={'1','2','3','*','4','5','6','/','7','8','9','-','c','0','=','+'};
s8 pin[5],*givenpin;
u32 flag1=0,chances,attempts=0,pinchange=0;
volatile s8 uart0_rx_buf[MAX_BUF_LEN2]={0};
volatile u32 uart0_rx_index = 0;
volatile u32 uart0_rx_complete = 0;

volatile s8 uart1_rx_buf[MAX_BUF_LEN1]={0};
volatile u32 uart1_rx_index = 0;
volatile u32 uart1_rx_complete = 0;
volatile u32 uart1_rx_started = 0;
u32 uart0_rx_valid=0;

volatile unsigned int uart_checksum = 0;
int main()
{
        IODIR0|=1<<LED;
        InitKPM();
        InitLCD();
        Init_UART0();
        Init_UART1();
        while(1)
        {
                CmdLCD(CLEAR_LCD);
                rotate_string("WELCOME TO ATM ",strlen("WELCOME TO ATM "),0);
                attempts=0;
                pinchange=0;
                if(validate_RFID())
                {
                                U1IER = 0x00;  // Disable UART1 interrupts
                                VICIntEnClr = (1 << 7);  // Clear VIC interrupt enable bit for UART1
                                if(validate_PIN())
                                {
                                        main_MENU();
                                }
                                U1IER = 0x01;  // Enable UART1 Receive Data Available interrupt
                                VICIntEnable |= (1 << 7);  // Re-enable VIC interrupt for UART1
                }
        }
}
