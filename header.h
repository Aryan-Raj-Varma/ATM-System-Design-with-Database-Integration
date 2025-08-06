#ifndef __header_h
#define __header_h

#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#include<stdint.h>
#include<ctype.h>
//#define DEBUG
#define MAX 5
typedef struct trsnc
{
        char type[10];
        double amount;
        int Acc_Num;
        int month,day,year;
        int hour,min;
        int trsncid;
}Trsnc;
typedef struct Manager
{
        char Name[50];
        int Account_Number;
        int flag1,flag2,block;
        char pin[5];
        char RFID[9];
        long int Contact_Number;
        double Account_Balance;
        int Trasnction_Count;
        long int Aadhar_Number;
        Trsnc history[5];
        int number;
        struct Manager *next;
}SLL;

//Global Variables
extern SLL *Account_Details;
extern SLL *Details;
extern char pin[10];
extern SLL* rfid;
//extern Trsnc *history;
//function declarations
char* getstring(void);
long int myatoi(char *);
int count(long int);

void Sync_From_File_H(void);
void Sync_From_File(void);
void Print_Menu(void);
void Create_Account(void);
void History(void);
void Withdraw(void);
void Deposit(void);
void Balance_Enquery(void);
void Transfer_Money(void);
void Display_All_Accounts(void);
void Save_To_File(void);
void Save_To_File_H(void);
void Find_Specific_Account(void);
int  Compare_Aadhar(long int);
int  Compare_RFID(char *);
int  Compare_int(char *);
void SortList(SLL *);
void Update_Account(void);
void Update_Menu(void);
char* Read_Name(void);
char* Read_PIN(void);
char* Read_RFID(void);
long int Read_Aadhar(void);
long int Read_Contact(void);
double Read_Bal(int);

//ARM functions
void Verify_PIN(char *,int);
void Verify_RFID(char *,int);
double extract_dou(char* );
char * extract_int(char* );
void read_str(int fd,char *str,int len);
void Change_Stat(void);
//
void Verify_PIN(char *,int);
void BAL_ENQ(int);
void DEP_BAL(char *,int);
void WITH_BAL(char *,int);
void PIN_CHANG(char *,int);
void BLK_CARD(int);
void MINI_STMT(int);
#endif
