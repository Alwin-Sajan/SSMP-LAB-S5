<div>

### Chose
  
  <a href="#add">Addition</a>
  <a href="#res">Reverse</a>
</div>


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


<div id="Add">
  
# Addition 16 bit

This assembly code performs the addition of two multi-digit numbers entered by the user and displays the result. The program uses x86 DOS interrupts for input/output operations and macros for repetitive tasks like reading and displaying characters. Here's a detailed explanation:

### Data Segment
The `data segment` contains three messages that will be displayed during the program's execution:
- `a db 0ah,0dh,"Enter the first Numbers: $"`: Prompt to enter the first number (with newline and carriage return at the beginning).
- `b db 0ah,0dh,"Enter the Second Numbers: $"`: Prompt to enter the second number.
- `d db 0ah,0dh,"The sum is: $"`: Message to display before showing the sum of the two numbers.

### Macros
Two macros (`read` and `display`) are defined for repeated use in the program.

#### `read` Macro
The `read` macro reads a single character from the keyboard and converts it from its ASCII form (0x30 to 0x39 for digits '0' to '9') to its numeric value by subtracting `30H` (hexadecimal 30, which is the ASCII code for '0'):
```asm
mov ah,01h  ; Function 01H: read a character from the keyboard
int 21h     ; DOS interrupt to execute the function
sub al,30h  ; Convert ASCII character to numeric value by subtracting 0x30
```

#### `display` Macro
The `display` macro is used to display a numeric value. Since the numeric values range from 0 to 9 (after the arithmetic operations), they need to be converted back to their ASCII form by adding `30H` before displaying them:
```asm
add dl,30h  ; Convert the number in DL to ASCII by adding 0x30
mov ah,02h  ; Function 02H: display a single character
int 21h     ; DOS interrupt to execute the function
```

### Code Segment
The `code segment` contains the logic to perform the addition of two multi-digit numbers.

#### Initialization
```asm
mov ax,data
mov ds,ax
```
These instructions load the data segment (`data`) into `AX` and move it into `DS` to allow access to the variables defined in the data segment.

#### Input of First Number
```asm
lea dx,a        ; Load the prompt message ("Enter the first Numbers:") into DX
mov ah,09h      ; Function 09H: display a string
int 21h         ; DOS interrupt to print the string
```
This block displays the prompt for the first number. The user enters a two-digit number. The next part reads and processes the input digits.

```asm
read            ; Read the first digit
mov dl,10h
mul dl          ; Multiply the first digit by 10 (shifting it to the tens place)
mov bh,al       ; Store the result in BH (higher byte)
read            ; Read the second digit
add bh,al       ; Add the second digit to complete the two-digit number in BH
```
This reads and processes the two-digit number entered by the user. The first digit is multiplied by 10 to form the tens place, and the second digit is added to form the final number. The number is stored in `BH`.

#### Input of Second Number
```asm
lea dx,b        ; Load the prompt message ("Enter the second Numbers:") into DX
mov ah,09h      ; Function 09H: display a string
int 21h         ; DOS interrupt to print the string
```
This displays the prompt for the second number.

```asm
read            ; Read the first digit
mov dl,10h
mul dl          ; Multiply the first digit by 10 (shifting it to the tens place)
mov ch,al       ; Store the result in CH (higher byte)
read            ; Read the second digit
add ch,al       ; Add the second digit to complete the two-digit number in CH
```
Similarly, this reads and processes the two-digit number entered by the user, storing the result in `CH`.

#### Displaying the Sum
```asm
lea dx,d        ; Load the prompt message ("The sum is:") into DX
mov ah,09h      ; Function 09H: display a string
int 21h         ; DOS interrupt to print the string
```
This displays the prompt before showing the sum.

#### Performing Addition
```asm
add bl,cl       ; Add the ones place of both numbers (BL and CL)
mov al,bl       ; Move the result to AL for Decimal Adjust
daa             ; Decimal Adjust after Addition (corrects binary-coded decimal results)
mov bl,al       ; Store the corrected result back in BL
```
The code adds the ones place of both numbers (`BL` and `CL`), adjusts the result using the `DAA` instruction (Decimal Adjust after Addition), and stores the result back in `BL`.

```asm
jc l1           ; If there's a carry (i.e., sum exceeds 9), jump to l1
jnc l2          ; If no carry, jump to l2
l1:
  inc bh        ; If there was a carry, increment the tens place (BH)
l2:
  add bh,ch     ; Add the tens place of both numbers (BH and CH)
  mov al,bh     ; Move the result to AL for Decimal Adjust
  daa           ; Decimal Adjust after Addition for the tens place
  mov bh,al     ; Store the corrected result in BH
```
This section handles the addition of the tens place. If there was a carry from the ones place, it increments the tens place and adds both tens places (`BH` and `CH`). Again, it uses `DAA` to correct the result for binary-coded decimal (BCD) format.

#### Final Output (Displaying the Sum)
```asm
jnc next
mov dl,01h
display         ; Display carry digit '1' if there was a carry from the tens place
```
If there's a carry in the addition of the tens place, it displays an extra '1' at the start of the result.

```asm
next:
mov ah,00h
mov dh,10h
mov al,bh
div dh          ; Divide the tens place by 10 to split it into two digits
mov cx,ax
mov dl,cl
display         ; Display the first digit (tens place)
mov dl,ch
display         ; Display the second digit (ones place)
```
This part formats and displays the sum of the two numbers. It splits the result into digits by dividing by 10, and then displays each digit using the `display` macro.

```asm
mov ah,4ch
int 21h         ; Terminate the program
```
This exits the program using the DOS interrupt for program termination.

### Summary
- **Input Phase:** The user is prompted to enter two two-digit numbers.
- **Computation Phase:** The program adds the two numbers using proper handling for multi-digit addition and binary-coded decimal adjustments.
- **Output Phase:** The result is displayed digit by digit, with handling for potential carries from the addition.

</div>
