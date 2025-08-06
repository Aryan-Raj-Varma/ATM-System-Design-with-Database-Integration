
# 🏧 ATM System Design with Database Integration (RFID + PIN Auth)

## 🔒 Objective
The main aim of this project is to develop a secure ATM system using RFID authentication and a PIN-based interface, with backend banking database integration implemented in C using data structures.

---

## 🧩 Project Overview

### Front-End (Microcontroller - LPC2148 Side)
Acts like a real ATM interface:

- **RFID card reader** to identify user
- **Keypad** for PIN entry and transaction inputs
- **LCD display** for menu and status messages
- Communicates with backend PC via **UART**
- Handles ATM interface components

### Back-End (PC - Linux Side Application in C)
Simulates a banking system:

- Stores user and transaction data using **struct** and **file I/O**
- Receives commands via **UART** from MCU
- Sends results and balance info back to MCU
- Simulates banking database using data structures

---

## 🧰 Hardware Requirements

| Component | Purpose |
|----------|---------|
| LPC2148 Microcontroller | Core MCU |
| RFID Reader & Cards | User authentication |
| 16x2 LCD Display | Display for UI |
| 4x4 Matrix Keypad | For PIN/amount input |
| MAX232 | UART level shifting |
| Buzzer | Alerts/notifications |
| USB-to-UART Converter / DB9 Cable | MCU ↔ PC Communication |

---

## 🛠️ Software Requirements

- **Embedded C**: For microcontroller code
- **Keil uVision IDE**: Development environment for MCU code
- **Flash Magic**: Flashing program to MCU
- **GCC Compiler**: Compiling PC-side C application

---

## 🧠 Microcontroller Side Implementation

### Hardware Interface Modules

- `lcd.c`, `lcd.h`: LCD control
- `delay.c`, `delay.h`: Timing functions
- `uart.c`, `uart.h`: UART communication (UART0 & UART1)
- `keypad.c`, `keypad.h`: Keypad input

### Testing Individual Modules

- LCD Test: Display characters and strings
- Keypad Test: Read and display input values
- UART Test: Send/receive test strings using UART0 and UART1
- RFID Test: Read card data via UART1 and display on LCD

### Main Program Flow

- **Initialization**: Initialize peripherals, display title
- **RFID Authentication**: Read 10-byte frame → Extract 8-byte ID → Send to PC: `#CARD:12345678$`
- **PIN Verification**: Wait for PC validation → On success, prompt PIN entry → Send: `#CARD:12345678#PIN:4321$`
- **Main Menu Options**:
  - BALANCE
  - DEPOSIT
  - WITHDRAW
  - PIN CHANGE
  - MINI STATEMENT
  - EXIT
- Implement 30-second timeout using interrupts

---

## 💻 PC-Side Backend Implementation (Linux, C)

### Flow:

1. Load users and transactions from text files
2. Initialize UART
3. Handle commands from MCU and send responses:
   - Validate RFID & PIN
   - Balance inquiry, deposit, withdrawal
   - PIN change and mini-statement
4. Update files after each transaction

---

## 🔄 ATM Communication Protocol

| # | Type | MCU → PC | PC Response | Description |
|--|------|-----------|--------------|-------------|
| 1 | Card Verification | `#C:<RFID>$` | `@OK:ACTIVE:<Name>$`, `@ERR:BLOCK$`, `@ERR:INVALID$` | Card status |
| 2 | PIN Verification | `#V:<RFID>:<PIN>$` | `@OK:MATCHED$`, `@ERR:WRONG$` | PIN match |
| 3 | Withdraw | `#A:WTD:<RFID>:<Amount>$` | `@OK:DONE$`, `@ERR:LOWBAL$` | Withdraw money |
| 4 | Deposit | `#A:DEP:<RFID>:<Amount>$` | `@OK:DONE$` | Deposit money |
| 5 | Balance Inquiry | `#A:BAL:<RFID>$` | `@OK:BAL=<Amount>$` | Show balance |
| 6 | Mini Statement | `#A:MST:<RFID>:<TxNo>$` | `@TXN:<Type>:<Date>:<Amount>$`, `@TXN:7$` | Last transactions |
| 7 | PIN Change | `#A:PIN:<RFID>:<NewPIN>$` | `@OK:DONE$` | PIN update |
| 8 | Card Block | `#A:BLK:<RFID>$` | `@OK:DONE$` | Block card |
| 9 | Line Check | `#X:LINEOK$` | `@X:LINEOK$` | Keep alive |
| 10 | End Session | `#Q:SAVE$` | (None) | Logout |

---

## 🔄 ATM System Working Flow

1. **Initialization**: Peripheral setup → Welcome message → Send keep-alive
2. **Card Scan**: RFID → Send to PC → Display validation response
3. **PIN Entry**: 3 tries max → Block on failure
4. **Menu Navigation**: Use keypad (A/B scroll, 1-6 select)
5. **Transaction Handling**: Balance, deposit, withdraw, mini-statement, PIN change
6. **Session Termination**: Manual exit or timeout

---

## 📌 MCU Hardware Connections

### LCD 16x2 ↔ LPC2148

| LCD Pin | LPC2148 Pin | Description |
|---------|--------------|-------------|
| D0-D7 | P1.16 - P1.23 | Data lines |
| RS | P0.16 | Register Select |
| RW | P0.17 | Read/Write |
| EN | P0.26 | Enable |
| VCC | 5V | Power |
| GND | GND | Ground |

### Keypad ↔ LPC2148

| Line | Pin | |
|------|-----|--|
| R0-R3 | P1.24 - P1.27 | Rows |
| C0-C3 | P1.28 - P1.31 | Columns |

### RFID ↔ LPC2148

| RFID Pin | LPC2148 Pin |
|----------|--------------|
| TX | P0.9 (UART1 RX) |
| VCC | 5V |
| GND | GND |

### PC ↔ LPC2148 (UART0 via MAX232)

| DB9 Pin | LPC2148 Pin |
|---------|--------------|
| RX (Pin 2) | P0.0 (TX) |
| TX (Pin 3) | P0.1 (RX) |

---

## 🔐 Security & Error Handling

- Card Blocking: 3 failed attempts → Blocked
- Timeout: 30-second inactivity = logout
- Frame-based protocol: Commands use `#` and `$` framing
- File locking: Prevents data corruption

---

## 🙋‍♂️ Author

**Aryan Raj Varma**  



