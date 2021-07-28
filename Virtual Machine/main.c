// Starter code for the LocoVM

#include <stdio.h>

#define SIZE 100
#define SENTINEL -99999

#define TRUE 1
#define FALSE 0

#define READ 10 //done
#define WRITE 11
#define LOAD 20
#define STORE 21

//make sure that the result of these inst over 9999.
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

#define BRANCH 40 //done
#define BRANCHNEG 41 //done
#define BRANCHZERO 42 //done
#define HALT 43 //came done already

void load(int*);
void execute(int*, int*, int*, int*, int*, int*);
void dump(int*, int, int, int, int, int);
int validWord(int);

int main() {
  int memory[SIZE];  // Virtual machine memory
  int acc = 0;       // Accumulator
  int pc = 0;        // Program counter
  int opCode = 0;    // Holds the opcode (first two digits of an instructon)
  int op = 0;        // Holds the operand (last two digits of an instruction)
  int ir =
      0;  // Instruction register -- where we put the instruction to execute

  // Clear memory
  for (int i = 0; i < SIZE; i++) memory[i] = 0;

  // Load program into memory
  load(memory);
  // Execute the program
  execute(memory, &acc, &pc, &ir, &opCode, &op);
  // Dump core
  dump(memory, acc, pc, ir, opCode, op);

  return 0;
}

void load(int* loadMemory) {
  long int instruction;
  int i = 0;

  // Feel free to embellish and customize the output however you want

  printf("%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
         "***           Welcome to LocoVM           ***",
         "*** Please enter your program one instruction ***",
         "*** ( or data word ) at a time. I will type the ***",
         "*** location number and a question mark ( ? ).  ***",
         "*** You then type the word for that location. ***",
         "*** Type the sentinel -99999 to stop entering ***",
         "*** your program.                             ***");

  printf("00 ? ");
  scanf("%ld", &instruction);

  while (instruction != SENTINEL) {
    if (!validWord(instruction))
      printf("Number out of range. Please enter again.\n");
    else {
      loadMemory[i] = instruction;
      i++;
    }

    printf("%02d ? ", i);
    scanf("%ld", &instruction);
  }
}

//We Will only be working on this section
void execute(int* memory, int* accPtr, int* pcPtr, int* irPtr, int* opCodePtr,
             int* opPtr) {
  printf("\n************START LocoVM EXECUTION************\n\n");
  *irPtr = memory[*pcPtr];
  *opCodePtr = *irPtr / 100;  // Get the opcode (the first 2 digits)
  *opPtr = *irPtr % 100;      // Get the operand (the last 2 digits)



//create the while loop to keep reading instructions.
//For the Project you have to create apro
//-9999 for opperants show message saying overflow
while(*opCodePtr != HALT){

  //READ WRITE LOAD STORE
  if(*opCodePtr == READ){
    printf("Enter a integer to read into memory: ");
    scanf("%d", &memory[*opPtr]);
    (*pcPtr)++;
  }

  if(*opCodePtr == WRITE){
    printf("Writing from memory to terminal...");
    printf("%d\n", memory[*opPtr]);
    (*pcPtr)++;
  }

  if(*opCodePtr == LOAD){
    printf("Loading from memory to accumulator...");
    printf("%d\n", memory[*opPtr]);
    *accPtr = memory[*opPtr];
    (*pcPtr)++;
  }

  if(*opCodePtr == STORE){
    printf("Storing from accumulator into memory...");
    memory[*opPtr] = *accPtr;
    (*pcPtr)++;
  }

  //JUMP BRANCHING

  if(*opCodePtr == BRANCH){
    printf("Branching to memory...");
    *pcPtr = *opPtr;
  }

  if(*opCodePtr == BRANCHNEG){
    if(*accPtr < 0){
      *pcPtr = *opPtr;
    }
    else{
      (*pcPtr)++;
    }
  }

  if(*opCodePtr == BRANCHZERO){
    if(*accPtr == 0){
      *pcPtr = *opPtr;
    }
    else{
      (*pcPtr)++;
    }
  }

  //ADD SUB MULT DIV
  if(*opCodePtr == ADD){
    printf("Adding....");
    *accPtr += memory[*opPtr];
    if(*accPtr > 9999 || *accPtr < -9999){
      printf("Error: Cannot be >9999 or <-9999");
    }
    else{
      (*pcPtr)++;
    }
  }

  if(*opCodePtr == SUBTRACT){
    printf("Subtracting....");
    *accPtr -= memory[*opPtr];
    if(*accPtr > 9999 || *accPtr < -9999){
      printf("Error: Cannot be >9999 or <-9999");
    }
    else{
      (*pcPtr)++;
    }
  }

  if(*opCodePtr == DIVIDE){
    printf("Dividing....");
    *accPtr /= memory[*opPtr];
    if(*accPtr > 9999 || *accPtr < -9999){
      printf("Error: Cannot be >9999 or <-9999");
    }
    else{
      (*pcPtr)++;
    }
  }

  if(*opCodePtr == MULTIPLY){
    printf("Multipliying....");
    *accPtr *= memory[*opPtr];
    if(*accPtr > 9999 || *accPtr < -9999){
      printf("Error: Cannot be >9999 or <-9999");
    }
    else{
      (*pcPtr)++;
    }
  }
  
  //fetch and repeat
  *irPtr = memory[*pcPtr];
  *opCodePtr = *irPtr / 100;  // Get the opcode (the first 2 digits)
  *opPtr = *irPtr % 100;      // Get the operand (the last 2 digits)
}

  // COMPLETE THIS FUNCTION TO EXECUTE YOUR CODE
  printf("\n*************END LocoVM EXECUTION*************\n");
}

void dump(int* memory, int accumulator, int programCounter,
          int instructionRegister, int operationCode, int operand) {
  printf("\n%s\n%-23s%+05d\n%-23s%5.2d\n%-23s%+05d\n%-23s%5.2d\n%-23s%5.2d",
         "REGISTERS:", "accumulator", accumulator, "programcounter",
         programCounter, "instructionregister", instructionRegister,
         "operationcode", operationCode, "operand", operand);

  printf("\n\nMEMORY:\n   ");

  for (int i = 0; i <= 9; i++) printf("%5d ", i);

  for (int i = 0; i < SIZE; i++) {
    if (i % 10 == 0) printf("\n%2d ", i);

    printf("%+05d ", memory[i]);
  }

  printf("\n\n Goodbye! ...");
}

int validWord(int word) { return word >= -9999 && word <= 9999; }
