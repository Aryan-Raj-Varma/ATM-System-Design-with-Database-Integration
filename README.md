# 🏧 ATM System Design with Database Integration (RFID + PIN Auth)

## 🔒 Objective
The primary goal of this project is to develop a **secure ATM system** using **RFID-based authentication** and **PIN verification**, with a PC-side simulated banking backend. The backend is implemented in **C language** using **data structures and file I/O**, and communicates with an LPC2148 microcontroller over **UART**.

---

## 🧩 System Overview

### 🖥️ Backend (PC Side - Linux)
- Developed in **C using GCC**
- Acts as a **simulated banking database**
- Stores and processes:
  - User details (`users.txt`)
  - Transactions (`transactions.txt`)
- Handles communication with the MCU via **UART**
- Responds to various commands like balance inquiry, withdrawals, PIN change, etc.

### 📟 Front-End (Microcontroller - LPC2148)
- Embedded C code developed using **Keil uVision IDE**
- Interacts with:
  - **RFID Reader** (for card detection)
  - **4x4 Keypad** (for PIN and transaction inputs)
  - **16x2 LCD Display** (for UI)
  - **Buzzer** (alerts and feedback)
  - Communicates with PC via **UART0**

---

## 🧰 Hardware Requirements

| Component | Purpose |
|----------|---------|
| **LPC2148** | Core microcontroller |
| **RFID Reader & Tags** | Card-based user authentication |
| **16x2 LCD Display** | Menu & feedback display |
| **4x4 Keypad** | PIN/amount input |
| **MAX232** | RS-232 level shifting |
| **USB-to-UART/DB9 Cable** | PC ↔ MCU UART Communication |
| **Buzzer** | User alerts |

---

## 🛠️ Software Requirements

| Software | Use |
|---------|-----|
| **Keil uVision** | Embedded C development |
| **Flash Magic** | Program flashing to MCU |
| **GCC Compiler (Linux)** | Compiling PC-side application |
| **GTKTerm / Minicom** | Optional: Debug UART |
| **Any Text Editor** | For .txt database files |

---

## 🧠 Functional Workflow

### 1. System Initialization
- MCU boots, initializes LCD, UART, keypad, and RFID reader
- Sends a test packet to PC: `#X:LINEOK$`

### 2. Card Authentication
- Waits for card scan → sends RFID data: `#C:<CARD_ID>$`
- PC validates card → responds:
  - `@OK:ACTIVE:<Name>$`
  - `@ERR:BLOCK$` or `@ERR:INVALID$`

### 3. PIN Verification
- Accepts 4-digit PIN → sends: `#V:<CARD_ID>:<PIN>$`
- PC replies: `@OK:MATCHED$` or `@ERR:WRONG$`
- Blocks card after 3 failed attempts

### 4. Main Menu Options
- `1. Balance Inquiry`
- `2. Deposit`
- `3. Withdraw`
- `4. Mini Statement`
- `5. PIN Change`
- `6. Exit ATM`

### 5. Transaction Handling
- Commands like:
  - `#A:BAL:<CARD_ID>$` → `@OK:BAL=<Amount>$`
  - `#A:DEP:<CARD_ID>:<Amount>$` → `@OK:DONE$`
  - `#A:WTD:<CARD_ID>:<Amount>$` → `@OK:DONE$` or errors
  - `#A:MST:<CARD_ID>:<TxNo>$` → Mini-statement details
  - `#A:PIN:<CARD_ID>:<NewPIN>$` → PIN change

### 6. Exit
- User selects Exit or timeout occurs → `#Q:SAVE$` sent to PC

---

## 📡 UART Communication Protocol

| Type | Format (MCU → PC) | PC Response |
|------|------------------|-------------|
| Card Auth | `#C:<RFID>$` | `@OK:ACTIVE:<Name>$` / `@ERR:BLOCK$` / `@ERR:INVALID$` |
| PIN Verify | `#V:<RFID>:<PIN>$` | `@OK:MATCHED$` / `@ERR:WRONG$` |
| Withdraw | `#A:WTD:<RFID>:<Amount>$` | `@OK:DONE$` / `@ERR:LOWBAL$` |
| Deposit | `#A:DEP:<RFID>:<Amount>$` | `@OK:DONE$` |
| Balance | `#A:BAL:<RFID>$` | `@OK:BAL=<Amount>$` |
| Mini Statement | `#A:MST:<RFID>:<TxNo>$` | `@TXN:<Type>:<Date>:<Amt>$` |
| PIN Change | `#A:PIN:<RFID>:<NewPIN>$` | `@OK:DONE$` |
| Block Card | `#A:BLK:<RFID>$` | `@OK:DONE$` |
| Connection Check | `#X:LINEOK$` | `@X:LINEOK$` |

---

## 🧾 File Descriptions


