# Reverse String

This assembly code is designed to perform the reversal of a string entered by the user. 
It uses **x86 DOS interrupts** (via `INT 21H`) to handle input/output and processes the string in memory. Here's a detailed breakdown:

### Data Segment
The `DATA SEGMENT` contains data declarations and memory allocations for the program:
- `ST1 DB 100 DUP(?)`: Allocates 100 bytes for the string input (the buffer).
- `MSG1 DB "ENTER THE STRING $"`: Message prompting the user to enter a string.
- `MSG2 DB "REVERSED STRING $"`: Message indicating the reversed string will follow.
- `NEWLINE DB 10,13,"$"`: Stores a newline and carriage return (`10, 13` are ASCII values) for formatting output.

### Code Segment
The `CODE SEGMENT` contains the logic to reverse the input string.

#### Initialization
- `MOV AX,DATA`: Moves the address of the data segment into register `AX`.
- `MOV DS,AX`: Loads the address stored in `AX` into the `DS` (Data Segment) register to set up the data segment for memory operations.
- `LEA DX,MSG1`: Loads the offset address of the `MSG1` string into `DX`.
- `MOV AH,09H`: Prepares for string output by setting the function code `09H` (for string output) in `AH`.
- `INT 21H`: Interrupt to print the string in `DX` (`MSG1` = "ENTER THE STRING $").

#### String Input
- `LEA SI,ST1`: Loads the offset of the string buffer `ST1` into `SI` (Source Index).
- `MOV CL,00`: Clears `CL`, which will count the number of characters entered.

**L1 (Input Loop):**
- `MOV AH,01H`: Sets the function code `01H` in `AH` to read a single character from the keyboard.
- `INT 21H`: Interrupt to read the character into `AL`.
- `CMP AL,0DH`: Compares the input character (`AL`) to `0DH` (ASCII for carriage return, Enter key).
  - If Enter (`0DH`) is detected, the program jumps to `L2`, ending input.
  - Otherwise, it continues:
- `INC CL`: Increments `CL` to keep track of the number of characters.
- `INC SI`: Increments `SI` to point to the next position in the buffer.
- `MOV [SI],AL`: Stores the character entered (`AL`) into the current position of the string buffer.
- `JMP L1`: Jumps back to the start of the loop to continue reading characters.

#### String Reverse Output
- `L2: LEA DX,NEWLINE`: Loads the offset of the newline into `DX`.
- `MOV AH,09H`: Prepares to output a string.
- `INT 21H`: Outputs the newline (`NEWLINE`).
- `LEA DX,MSG2`: Loads the offset of the `MSG2` string into `DX`.
- `MOV AH,09H`: Prepares for string output.
- `INT 21H`: Outputs the message "REVERSED STRING $".

**L3 (Reverse Output Loop):**
- `MOV DL,[SI]`: Loads the character at the current position pointed to by `SI` (from the end of the string).
- `MOV AH,02H`: Prepares to output a single character (`DL`).
- `INT 21H`: Outputs the character.
- `DEC SI`: Decrements `SI` to move backward in the string.
- `DEC CL`: Decrements `CL`, reducing the character count.
- `CMP CL,00H`: Compares the character count to zero.
  - If not zero, the program jumps back to `L3` to continue outputting characters in reverse order.
  
#### Exit Program
- `MOV AH,4CH`: Sets the function code `4CH` to terminate the program.
- `INT 21H`: Interrupt to exit.

### Summary
- **Input Phase (L1):** The program reads a string from the user and stores it in the `ST1` buffer.
- **Output Phase (L2, L3):** The program first prints a newline and a "REVERSED STRING" message, then prints the entered string in reverse order by decrementing the buffer pointer.
- **End:** The program terminates after the reversed string is displayed.
