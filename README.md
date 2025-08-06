ATM System Design with Database Integration
OBJECTIVE: The main aim of this project is to develop a secure ATM system using RFID authentication and a PIN-based interface, with backend banking database integration implemented in C using data structures

PROJECT OVERVIEW: The system consists of two main components:

Front-End (Microcontroller (LPC2148) side):
Acts like a real ATM interface:

RFID card reader to identify user
Keypad for PIN entry and transaction inputs
LCD display for menu and status messages
Communicates with backend PC via UART
Handles the ATM interface (LCD, keypad, RFID reader)
Back-End (PC (Linux) side Application in C):
Simulates a banking system:

Stores user and transaction data using struct and file I/O
Receives commands via UART from MCU
Sends results and balance info back to MCU
Simulates a banking database using data structures and file handling
BLOCK DIAGRAM:

Screenshot 2025-05-23 092351

HARDWARE REQUIREMENTS:

LPC2148 Microcontroller: The brain of your ATM system
RFID Reader and Cards: For user authentication
16x2 LCD Display: For user interface
4x4 Matrix Keypad: For PIN and amount input
MAX232: For UART level shifting
Buzzer: For alerts/notifications
USB-to-UART Converter/DB-9 Cable: For communication between MCU and PC
SOFTWARE REQUIREMENTS:

Embedded C: For microcontroller programming
Keil uVision IDE: For development environment
Flash Magic: For flashing the program to MCU
GCC Compiler: For PC-side program compilation
MICROCONTROLLER SIDE IMPLEMENTATION:

Hardware Interface Modules:
Create the Baisc Modules files:

lcd.c, lcd.h (LCD control)
delay.c, delay.h (timing functions)
uart.c, uart.h (UART communication)
keypad.c, keypad.h (keypad input)
Testing Individual Modules:
Before integration, test each module separately:

LCD Test: Display characters and strings
Keypad Test: Read and display input values
UART Test: Send/receive test strings using UART0 and UART1
RFID Test: Read card data via UART1 and display on LCD
Main Program Flow (main.c)

Initialization:

Initialize all hardware modules (LCD, UART, keypad, RFID)
Display project title briefly on LCD
RFID Authentication:

Continuously wait for RFID card
When card is detected, read the 10-byte frame (starts with 0x02, ends with 0x03)
Extract the 8-byte card number (middle bytes)
Send to PC in format: #CARD:12345678$
PIN Verification:

If PC responds with @OK#VALID_CARDS, display "Enter PIN"
Read 4-digit PIN from keypad
Send to PC in format: #CARD:12345678#PIN:4321$
Wait for validation response
Main Menu:

On successful login, display menu options:
BALANCE
DEPOSIT
WITHDRAW
PIN CHANGE
MINI STATEMENT
EXIT
Implement 30-second timeout using timer interrupts
Transaction Handling:

For each menu option, send appropriate request to PC and handle response
PC-SIDE DATABASE IMPLEMENTATION

Main Program Flow

Initialization:
Load user data from users.txt into an array/list
Load transaction history from transactions.txt into a linked list
Initialize UART communication with MCU
RFID Validation:
Wait for #CARD:12345678$
Search user list for matching RFID
Respond with @OK#VALID_CARDS or @ERR#INVALID_CARDS
PIN Validation:
Wait for #CARD:12345678#PIN:4321$
Verify PIN matches stored PIN for that RFID
Respond with @OK#LOGIN_SUCCESS or @ERR#INVALID_PINS
Transaction Handling:
Balance Enquiry (#TXN:BALANCE#REQS):
- Fetch and return balance: @OK#BALANCE:XXXX.XX$
Deposit (#TXN:DEPOSIT#AMOUNT:1000$):
- Add amount to balance
- Log transaction
- Return new balance
Withdrawal (#TXN:WITHDRAW#AMOUNT:500$):
- Check sufficient balance
- Deduct amount if available
- Log transaction
- Return new balance or error
PIN Change (#PINCHANGE#NEWPINS):
- Update PIN in user structure
- Save to file
Mini Statement (#MINISTMT#REQS):
- Find last 3 transactions for user
- Format as: @OK#MINISTMT:TXN1|TXN2|TXN3$
File Handling:
After each transaction that modifies data, update the text files
Implement proper file locking to prevent corruption
ATM Communication Protocol: MCU ↔ PC Commands

Sr. No.	Transaction Type	Direction	Command Format	Response Format	Description
1	Card Verification	MCU → PC	#C:<RFID>$	@OK:ACTIVE:<Name>$	Valid card with account name
@ERR:BLOCK$	Card is blocked
@ERR:INVALID$	Card not registered
2	PIN Verification	MCU → PC	#V:<RFID>:<PIN>$	@OK:MATCHED$	Correct PIN
@ERR:WRONG$	Incorrect PIN
3	Withdrawal	MCU → PC	#A:WTD:<RFID>:<Amount>$	@OK:DONE$	Withdrawal successful
@ERR:LOWBAL$	Insufficient balance
@ERR:NEGAMT$	Negative amount invalid
@ERR:MAXAMT$	Exceeds ₹30,000 limit
4	Deposit	MCU → PC	#A:DEP:<RFID>:<Amount>$	@OK:DONE$	Deposit successful
@ERR:NEGAMT$	Negative amount invalid
@ERR:MAXAMT$	Exceeds ₹30,000 limit
5	Balance Inquiry	MCU → PC	#A:BAL:<RFID>$	@OK:BAL=<Amount>$	Returns current balance (e.g., @OK:BAL=25000$)
6	Mini-Statement	MCU → PC	#A:MST:<RFID>:<TxNo>$	@TXN:<Type>:<Date>:<Amount>$	Transaction details (type, date, amount)
@TXN:7$	No more transactions to show
7	PIN Change	MCU → PC	#A:PIN:<RFID>:<NewPIN>$	@OK:DONE$	PIN updated successfully
8	Card Blocking	MCU → PC	#A:BLK:<RFID>$	@OK:DONE$	Card blocked (after 3 failed PIN attempts)
9	System	MCU → PC	#X:LINEOK$	@X:LINEOK$	Connection test (keep-alive)
10	Session End	MCU → PC	#Q:SAVE$	(None)	Graceful termination (no response expected)
ATM Project's Working Flow
1. System Initialization [MCU BOOT] → [Peripheral Initialization] → [Welcome Screen]

Actions:

MCU powers on and initializes:
UART (for PC communication)
LCD (16x2 display)
Keypad (4x4 matrix)
RFID reader
Displays: "Welcome To ATM"
Sends test command: #X:LINEOK$ to verify PC connection.
2. Card Authentication [RFID Scan] → [Card Validation] → [Block/Proceed]

Steps:

User places card → RFID reader detects card and extracts 8-digit ID.
MCU sends to PC: #C:12345678$
PC responds with:
Valid: @OK:ACTIVE:JohnDoe$ (shows name on LCD)
Blocked: @ERR:BLOCK$ → Display "Card Blocked"
Invalid: @ERR:INVALID$ → Display "Card Not Found"
3. PIN Verification [PIN Entry] → [Server Check] → [Access Granted/Block]

Process:

User enters 4-digit PIN (masked as **** on LCD)
MCU sends: #V:12345678:1111$
PC checks and replies:
Correct: @OK:MATCHED$ → Proceeds to menu
Wrong: @ERR:WRONG$ → Retry (3 attempts → blocks card)
Timeout: 30-second inactivity → auto-exit
4. Main Menu Navigation [Menu Display] → [Keypad Input] → [Transaction Execution]

Menu Options:

WITHDRAW CASH
DEPOSIT CASH
VIEW BALANCE
MINI STATEMENT
PIN CHANGE
EXIT ATM
Navigation:

A key: Scroll up
B key: Scroll down
1-6 keys: Select option
5. Transaction Processing

A. Withdrawal [Amount Entry] → [MCU: #A:WTD:12345678:5000$] → [PC Checks] → [Dispense Cash]

Responses:

@OK:DONE$ → Dispenses cash + shows success
@ERR:LOWBAL$ → Shows "Low Balance"
@ERR:MAXAMT$ → Shows "Exceeds Limit (₹30,000)"
B. Deposit [Amount Entry] → [MCU: #A:DEP:12345678:10000$] → [PC Updates Balance] → [Confirmation]

Responses: Same as withdrawal (success/error codes)

C. Balance Inquiry [MCU: #A:BAL:12345678$] → [PC: @OK:BAL=25000$] → [LCD Shows Balance]

D. Mini-Statement [MCU: #A:MST:12345678:1$] → [PC: @TXN:1:01/06/2023:5000$] → [LCD Shows Last 3 Transactions]

E. PIN Change [Old PIN → New PIN → Confirm] → [MCU: #A:PIN:12345678:2222$] → [PC: @OK:DONE$]

Behavior:

Failure: Mismatch → decrement tries
Success: Resets try counter
6. Session Termination [Exit Selected] → [MCU: #Q:SAVE$] → [LCD: "Thank You"] → [Return to Card Scan]

Timeout: 30s inactivity → auto-logout with message: "Session Time-Out"
Error Handling & Security

Card Blocking: After 3 failed PIN attempts → MCU sends #A:BLK:12345678$
Protocol Security:
All commands use #/@ framing to prevent corruption
Timeouts prevent infinite hangs
MCU HARDWARE CONNECTIONS

LPC2148 Interfacing Connections
LCD 16x2 ↔ LPC2148
LCD Pin	LPC2148 Pin	Description
D0	P1.16	Data Line 0
D1	P1.17	Data Line 1
D2	P1.18	Data Line 2
D3	P1.19	Data Line 3
D4	P1.20	Data Line 4
D5	P1.21	Data Line 5
D6	P1.22	Data Line 6
D7	P1.23	Data Line 7
RS	P0.16	Register Select
RW	P0.17	Read/Write
EN	P0.26	Enable
VCC	5V	Power Supply
GND	GND	Ground
Keypad (4x4) ↔ LPC2148
Keypad Line	LPC2148 Pin	Description
R0	P1.24	Row 0
R1	P1.25	Row 1
R2	P1.26	Row 2
R3	P1.27	Row 3
C0	P1.28	Column 0
C1	P1.29	Column 1
C2	P1.30	Column 2
C3	P1.31	Column 3
RFID Reader ↔ LPC2148
RFID Pin	LPC2148 Pin	Description
TX (output)	P0.9	UART1 RX (Receive)
VCC	5V	Power Supply
GND	GND	Ground
PC (via DB9) ↔ LPC2148
DB9 Pin	LPC2148 Pin	Description
RX (Pin 2)	P0.0	UART0 TX (to PC)
TX (Pin 3)	P0.1	UART0 RX (from PC)
📌 Note: Ensure proper voltage level conversion between LPC2148 (3.3V) and peripherals like PC (RS-232 uses ±12V) using MAX232 or level shifter where required.
