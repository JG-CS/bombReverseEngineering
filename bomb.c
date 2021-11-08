/*
Joel González
St. ID: 801-13-2812
Computer Architecture
Bomb Lab
*/


/* xxxx REVERSE ENGINEERING xxxx */

#if 0

NOTE: 
    PLEASE SEE justification.pdf FOR HAND TRACING SHOWCASING HOW I FIGURED OUT HOW THE ASM CODE WORKED.


void phase_1(string &input) {
    if(input != "Houses will begat jobs, jobs will begat houses.")
        explode_bomb();
    else
        return;
}

ASM CODE
/*
0x00005555555555a7 <+0>:     endbr64 
   0x00005555555555ab <+4>:     sub    $0x8,%rsp
   0x00005555555555af <+8>:     lea    0x1bd2(%rip),%rsi        # 0x555555557188 
This previous instruction calculates the address of a string stored in memory.
    String is "Houses will begat jobs, jobs will begat houses."
    
   0x00005555555555b6 <+15>:    call   0x5555555559a2 <strings_not_equal>
This previous instruction compares the string stored in memory with the string the user entered. 

   0x00005555555555bb <+20>:    test   %eax,%eax
   0x00005555555555bd <+22>:    jne    0x5555555555c4 <phase_1+29>
If the strings are the not the same(zero flag set after TEST instruction), then the phase explodes
    else the phase continues execution and finishes.
        
   0x00005555555555bf <+24>:    add    $0x8,%rsp
   0x00005555555555c3 <+28>:    ret    
   0x00005555555555c4 <+29>:    call   0x555555555a9d <explode_bomb>
   0x00005555555555c9 <+34>:    jmp    0x5555555555bf <phase_1+24>
*/



void phase_2(string &input) {
    //creating array that will hold numbers
    unsigned int numbers[6] = {0};
    //emulating read_six_numbers function
    //stores each number that is separated by a space into a different array index
    int stringIndex = 0;
    int numberCount = 0;
    for(int i = 0; stringIndex < input.length(); i++){
        bool space = false;
        bool first = true;
        while (!space){
            if (first){
                numbers[i] += input[stringIndex] - '0';
                first = false;
            }
            else{
                numbers[i] *=10;
                numbers[i] += input[stringIndex] - '0';
            }
            if (input[stringIndex+1] == ' ' || input[stringIndex+1] == '\0'){
                space = true;
                stringIndex++;
            }
            stringIndex++;
        }
        numberCount +=1;
    }
    //check if amount of numbers entered at least 6
    if (numberCount < 6)
      explode_bomb();
    
    //check if first number zero
    if (numbers[0] !=0)
        explode_bomb();
    
    //Loop through values and check that the required mathematical expression is met with all entered values
    for (int counter = 1; i < 5; counter++){
        if (i[counter] != 2*i[counter-1] + counter)
            explode_bomb();
    }
    return;
}

ASM CODE
/*
   0x00005555555555cb <+0>:     endbr64 
   0x00005555555555cf <+4>:     push   %rbx
   0x00005555555555d0 <+5>:     sub    $0x20,%rsp
memory allocation
   0x00005555555555d4 <+9>:     mov    %rsp,%rsi
   0x00005555555555d7 <+12>:    call   0x555555555ac9 <read_six_numbers>
Calls function that parses through the string and stores each individual number entered by user into an array in the stack
Function checks to make sure that at least 6 numbers have been entered. 

   0x00005555555555dc <+17>:    cmpl   $0x0,(%rsp)
   0x00005555555555e0 <+21>:    js     0x5555555555e9 <phase_2+30>
Check if first number entered is zero. if not zero, explode

   0x00005555555555e2 <+23>:    mov    $0x1,%ebx
%ebx is a counter for the next loop
   
   0x00005555555555e7 <+28>:    jmp    0x5555555555f8 <phase_2+45>
   0x00005555555555e9 <+30>:    call   0x555555555a9d <explode_bomb>
   0x00005555555555ee <+35>:    jmp    0x5555555555e2 <phase_2+23>
   0x00005555555555f0 <+37>:    call   0x555555555a9d <explode_bomb>
   0x00005555555555f5 <+42>:    add    $0x1,%ebx
increment counter

   0x00005555555555f8 <+45>:    cmp    $0x5,%ebx
   0x00005555555555fb <+48>:    jg     0x555555555613 <phase_2+72>
Loop ends when the counter reaches 6

   0x00005555555555fd <+50>:    movslq %ebx,%rax
   0x0000555555555600 <+53>:    lea    -0x1(%rbx),%edx
   0x0000555555555603 <+56>:    movslq %edx,%rdx
   0x0000555555555606 <+59>:    mov    (%rsp,%rdx,4),%edx
   0x0000555555555609 <+62>:    lea    (%rbx,%rdx,2),%edx
Previous number is stored in %rdx, and then counter + 2* prevNumber is computed and stored in %rdx

   0x000055555555560c <+65>:    cmp    %edx,(%rsp,%rax,4)
   0x000055555555560f <+68>:    je     0x5555555555f5 <phase_2+42>
At this point in the execution, %rax contains a copy of the counter value. 
Memory is accessed to get the current number value corresponding to the counter and number array in stack
If currNumber is not equal to 2 * prevNumber, bomb will explode
    this expression must be true for all values entered by user
    
   0x0000555555555611 <+70>:    jmp    0x5555555555f0 <phase_2+37>
   0x0000555555555613 <+72>:    add    $0x20,%rsp
   0x0000555555555617 <+76>:    pop    %rbx
   0x0000555555555618 <+77>:    ret
 */



void phase_3(string &input) {
    //creating array that will hold numbers
    unsigned int numbers[2] = {0};
    //emulating sscanf function
    //stores each number that is separated by a space into a different array index
    int stringIndex = 0;
    int numberCount = 0;
    for(int i = 0; stringIndex < input.length(); i++){
        bool space = false;
        bool first = true;
        while (!space){
            if (first){
                numbers[i] += input[stringIndex] - '0';
                first = false;
            }
            else{
                numbers[i] *=10;
                numbers[i] += input[stringIndex] - '0';
            }
            if (input[stringIndex+1] == ' ' || input[stringIndex+1] == '\0'){
                space = true;
                stringIndex++;
            }
            stringIndex++;
        }
        numberCount +=1;
    }
    // check that user entered at least 2 numbers
    if (numberCount <2)
        explode_bomb;
    //check that first number is not greater than 7
    if(numbers[0] > 7)
        explode_bomb;
    
    //check that the second number is correct, correct answer depends on the first number entered
    switch(numbers[0]){
        case 0:
            if (numbers[1] != 0x299)
                explode_bomb();
            break;
        case 5:
        case 7:
        case 1:
            if (numbers[1] != 0xfffffd1e)
                explode_bomb();
            break;
        case 2:
            if (numbers[1] != 0x8d)
                explode_bomb();
            break;
        case 3:
            if (numbers[1] != 0xfffffe26)
                explode_bomb();
            break;
        case 4:
            if(numbers[1] != 0x61)
                explode_bomb();
            break;
        case 6:
            if(numbers[1] !=0x2e2)
                explode_bomb();
            break;
    }
    //Check if user entered a first number greater than 4
    if (number > 4)
        explode_bomb();
    return;
}

ASM CODE
/*
   0x0000555555555619 <+0>:     endbr64 
   0x000055555555561d <+4>:     sub    $0x18,%rsp
memory allocation

   0x0000555555555621 <+8>:     lea    0x8(%rsp),%rcx
   0x0000555555555626 <+13>:    lea    0xc(%rsp),%rdx
   0x000055555555562b <+18>:    lea    0x1d1d(%rip),%rsi        # 0x55555555734f
   0x0000555555555632 <+25>:    mov    $0x0,%eax
Previous lines were preparing for function call sscanf

0x0000555555555637 <+30>:    call   0x5555555552c0 <__isoc99_sscanf@plt>
Function parses through string and stores each individual number into an array in the stack

   0x000055555555563c <+35>:    cmp    $0x1,%eax
   0x000055555555563f <+38>:    jle    0x55555555565d <phase_3+68>
if user entered 1 or fewer numbers, explode
    
   0x0000555555555641 <+40>:    mov    0xc(%rsp),%eax
   0x0000555555555645 <+44>:    cmp    $0x7,%eax
   0x0000555555555648 <+47>:    ja     0x555555555687 <phase_3+110>
Checks that the first number entered is between 0 and 7
    if not, explode
        
   0x000055555555564a <+49>:    mov    %eax,%eax
   0x000055555555564c <+51>:    lea    0x1b8d(%rip),%rdx        # 0x5555555571e0
   0x0000555555555653 <+58>:    movslq (%rdx,%rax,4),%rax
Calculates jump target based on the first number the user input

   0x0000555555555657 <+62>:    add    %rdx,%rax
   0x000055555555565a <+65>:    notrack jmp *%rax
   0x000055555555565d <+68>:    call   0x555555555a9d <explode_bomb>
   0x0000555555555662 <+73>:    jmp    0x555555555641 <phase_3+40>
   0x0000555555555664 <+75>:    mov    $0x299,%eax
LAND HERE WHEN FIRST NUMBER 0
second number must be equal to 0x299

   0x0000555555555669 <+80>:    jmp    0x555555555698 <phase_3+127>
   0x000055555555566b <+82>:    mov    $0x8d,%eax
LAND HERE WHEN FIRST NUMBER 2
second number must be equal to 0x8d

   0x0000555555555670 <+87>:    jmp    0x555555555698 <phase_3+127>
   0x0000555555555672 <+89>:    mov    $0xfffffe26,%eax
LAND HERE WHEN FIRST NUMBER 3
second number must be equal to 0xfffffe26

   0x0000555555555677 <+94>:    jmp    0x555555555698 <phase_3+127>
   0x0000555555555679 <+96>:    mov    $0x61,%eax
LAND HERE WHEN FIRST NUMBER 4
second number must be equal to 0x61

   0x000055555555567e <+101>:   jmp    0x555555555698 <phase_3+127>
   0x0000555555555680 <+103>:   mov    $0x2e2,%eax
LAND HERE WHEN FIRST NUMBER 6
second number must be equal to 0x2e2
  
   0x0000555555555685 <+108>:   jmp    0x555555555698 <phase_3+127>
   0x0000555555555687 <+110>:   call   0x555555555a9d <explode_bomb>
   0x000055555555568c <+115>:   mov    $0x0,%eax
   0x0000555555555691 <+120>:   jmp    0x555555555698 <phase_3+127>
   0x0000555555555693 <+122>:   mov    $0xfffffd1e,%eax
LAND HERE WHEN FIRST NUMBER 1 OR 5 OR 7
second number must be equal to 0xfffffd1e

   0x0000555555555698 <+127>:   cmpl   $0x4,0xc(%rsp)
   0x000055555555569d <+132>:   jg     0x5555555556a5 <phase_3+140>
If first number entered is greater than 4, explode

   0x000055555555569f <+134>:   cmp    %eax,0x8(%rsp)
   0x00005555555556a3 <+138>:   je     0x5555555556aa <phase_3+145>
If the second number has the correct value(depends on which value was entered first), then bomb does not explode

   0x00005555555556a5 <+140>:   call   0x555555555a9d <explode_bomb>
   0x00005555555556aa <+145>:   add    $0x18,%rsp
deallocate memory   

   0x00005555555556ae <+149>:   ret
 */



void phase_4(string &input) {
    //creating array that will hold numbers
    unsigned int numbers[2] = {0};
    //emulating sscanf function
    //stores each number that is separated by a space into a different array index
    int stringIndex = 0;
    int numberCount = 0;
    for(int i = 0; stringIndex < input.length(); i++){
        bool space = false;
        bool first = true;
        while (!space){
            if (first){
                numbers[i] += input[stringIndex] - '0';
                first = false;
            }
            else{
                numbers[i] *=10;
                numbers[i] += input[stringIndex] - '0';
            }
            if (input[stringIndex+1] == ' ' || input[stringIndex+1] == '\0'){
                space = true;
                stringIndex++;
            }
            stringIndex++;
        }
        numberCount +=1;
    }
    // check that user entered 2 numbers
    if (numberCount != 2)
        explode_bomb;
    //check that first number is not greater than 9
    if(numbers[0] > 9)
        explode_bomb;
    if (func4(numbers[0],numbers[1])!=160)
        explode_bomb();
}
unsigned int func4(int firstNumber, int secondNumber){
    //BASE CASE
    if(firstNumber <1) 
        return secondNumber;
    //RECURSIVE CASE
    secondNumber *=2; //double second parameter
    firstNumber--; //decrement first parameter
    return func4(firstNumber,secondNumber);
}

ASM CODE
/*
phase_4
   0x00005555555556cd <+0>:     endbr64 
   0x00005555555556d1 <+4>:     sub    $0x18,%rsp
allocate memory

   0x00005555555556d5 <+8>:     lea    0x8(%rsp),%rcx
   0x00005555555556da <+13>:    lea    0xc(%rsp),%rdx
   0x00005555555556df <+18>:    lea    0x1c69(%rip),%rsi        # 0x55555555734f
   0x00005555555556e6 <+25>:    mov    $0x0,%eax
   0x00005555555556eb <+30>:    call   0x5555555552c0 <__isoc99_sscanf@plt>
calls sscanf function
    parses through string, stores user entered numbers into an array in the stack
    returns the amount of numbers entered by user
    second number stored in %rsp + 8, first number stored in %rsp + 0xc
    
   0x00005555555556f0 <+35>:    cmp    $0x2,%eax
   0x00005555555556f3 <+38>:    jne    0x5555555556fc <phase_4+47>
if amount of numbers entered by user is not equal to 2, explode

   0x00005555555556f5 <+40>:    cmpl   $0x9,0x8(%rsp) 
   0x00005555555556fa <+45>:    jle    0x555555555701 <phase_4+52>
if the second number entered is greater than 9, explode
    
   0x00005555555556fc <+47>:    call   0x555555555a9d <explode_bomb>
   0x0000555555555701 <+52>:    mov    0x8(%rsp),%esi
   0x0000555555555705 <+56>:    mov    0xc(%rsp),%edi
store first number entered in %esi
store second number entered in %edi
preparing to call func4 
   0x0000555555555709 <+60>:    call   0x5555555556af <func4>
call func4
see below for func4 analysis

   0x000055555555570e <+65>:    cmp    $0xa0,%eax
   0x0000555555555713 <+70>:    jne    0x55555555571a <phase_4+77>
if return value of func4 function is not equal to 0xa0, explode

   0x0000555555555715 <+72>:    add    $0x18,%rsp
deallocate memory

   0x0000555555555719 <+76>:    ret    
   0x000055555555571a <+77>:    call   0x555555555a9d <explode_bomb>
   0x000055555555571f <+82>:    jmp    0x555555555715 <phase_4+72>
   
------------------------------------------------------------------------------
func4 
   0x00005555555556af <+0>:     endbr64 
   0x00005555555556b3 <+4>:     test   %edi,%edi
   0x00005555555556b5 <+6>:     jle    0x5555555556ca <func4+27>
this comparison defines the BASE CASE
    if the first parameter is a negative number or zero, return the second parameter

   0x00005555555556b7 <+8>:     sub    $0x8,%rsp
allocate memory


   0x00005555555556bb <+12>:    add    %esi,%esi
   0x00005555555556bd <+14>:    sub    $0x1,%edi
   0x00005555555556c0 <+17>:    call   0x5555555556af <func4>
These commands define the recursive case
    value of %esi(second parameter) is doubled
    value of %edi(first parameter) is decreased by 1
recursive case will continue to decrement the first parameter until base case is reached
each time the recusive case is run, the value of the second parameter is doubled

   0x00005555555556c5 <+22>:    add    $0x8,%rsp
deallocate memory

   0x00005555555556c9 <+26>:    ret    
   0x00005555555556ca <+27>:    mov    %esi,%eax
   0x00005555555556cc <+29>:    ret
   
 */




void phase_5(string &input) {
    //array contents
    unsigned int values[16] = {9,11,1,7,2,15,2,6,10,12,14,8,4,13,16,5};
    unsigned int accumulator = 0;
    // use the result of an AND operation to access array values
    // AND result will depend on user input string characters
    // accumulate the total sum of values accessed from array
    for(int counter = 0; counter < 6; counter++){
        accumulator += values[input[counter] & 0xf];
    }
    if (accumulator != 0x3c)
        explode_bomb();
    return;
}

ASM CODE
/*
   0x0000555555555721 <+0>:     endbr64 
   0x0000555555555725 <+4>:     push   %rbx
   0x0000555555555726 <+5>:     mov    %rdi,%rbx
   0x0000555555555729 <+8>:     call   0x55555555598a <string_length>
calls string_length function
    returns the length of the string entered by user
    
   0x000055555555572e <+13>:    cmp    $0x6,%eax
   0x0000555555555731 <+16>:    jne    0x55555555575b <phase_5+58>
if string length not 6, explode
    
   0x0000555555555733 <+18>:    mov    $0x0,%ecx
   0x0000555555555738 <+23>:    mov    $0x0,%eax
set %ecx and %eax to zero. 
    %eax is a counter
    %ecx is an accumulator
    
   0x000055555555573d <+28>:    cmp    $0x5,%eax
   0x0000555555555740 <+31>:    jg     0x555555555762 <phase_5+65>
if counter < 6, continue loop
    
   0x0000555555555742 <+33>:    movslq %eax,%rdx
   0x0000555555555745 <+36>:    movzbl (%rbx,%rdx,1),%edx
access the character in the string in position "counter"
    string[counter]

   0x0000555555555749 <+40>:    and    $0xf,%edx
perform bitwise AND operation between the character extracted from string and 0xf

   0x000055555555574c <+43>:    lea    0x1aad(%rip),%rsi        # 0x555555557200 <array.3468>
   0x0000555555555753 <+50>:    add    (%rsi,%rdx,4),%ecx
   0x0000555555555756 <+53>:    add    $0x1,%eax
access array at position that was the result from the previous AND calculation
    add the value stored in the position accessed to the accumulator
    increment counter
    this process is repeated until all the characters in the string have been used to access the aray

   0x0000555555555759 <+56>:    jmp    0x55555555573d <phase_5+28>
   0x000055555555575b <+58>:    call   0x555555555a9d <explode_bomb>
   0x0000555555555760 <+63>:    jmp    0x555555555733 <phase_5+18>
   0x0000555555555762 <+65>:    cmp    $0x3c,%ecx
   0x0000555555555765 <+68>:    jne    0x555555555769 <phase_5+72>
if the accumulator does not hold a value equal to 0x3c after the loop, explode bomb
   one possible solution is to write 6 characters that access the location where 0x0a is stored
        0x0a x 6 = 0x3c, which would give the required solution
        "((((((" fits this criteria
            '(' & 0xf = 8

   0x0000555555555767 <+70>:    pop    %rbx
   0x0000555555555768 <+71>:    ret    
   0x0000555555555769 <+72>:    call   0x555555555a9d <explode_bomb>
   0x000055555555576e <+77>:    jmp    0x555555555767 <phase_5+70>
------------------------------------------------------------------------------
array contents, in order 
0x09
0x0b
0x01
0x07
0x02
0x0f
0x02
0x06
0x0a index number 8
0x0c
0x0e
0x08
0x04
0x0d
0x10
0x05
 */



//IMPORTANT
//For this last function, I am going to assume that there is a node class defined
//USING THIS IMPLEMENTATION OF LINKED LIST NODES, MADE BY PROFESSOR RAFAEL ARCE:
    https://github.com/ran-research-lab/llist-c01
// Node class objects will have two data members, "data" holds the integer stored in the node, "next" holds the address of // the next node.
//Detailed line-by-line function and interpretation are available in the justification.pdf document. I am aware that the page for this last phase is very disorganized. I can answer any questions you may have about how I found out how specific parts of the code worked if you are unable to ascertain my method from looking at the document. 



void phase_6(string &input) {
    //creating arrays that will hold user numbers and node addresses
    unsigned int numbers[6] = {0};
    //creating nodes with corresponding values
    Node *nodeAddresses[6] = {NULL};
    LList nodes;
    nodes.insert(0x4c);
    nodes.append(0x64);
    nodes.append(0x26d);
    nodes.append(0xf9);
    nodes.append(0x26c);
    nodes.append(0x3e6);

    //emulating read_six_numbers function
    //stores each number that is separated by a space into a different array index
    int stringIndex = 0;
    int numberCount = 0;
    for(int i = 0; stringIndex < input.length(); i++){
        bool space = false;
        bool first = true;
        while (!space){
            if (first){
                numbers[i] += input[stringIndex] - '0';
                first = false;
            }
            else{
                numbers[i] *=10;
                numbers[i] += input[stringIndex] - '0';
            }
            if (input[stringIndex+1] == ' ' || input[stringIndex+1] == '\0'){
                space = true;
                stringIndex++;
            }
            stringIndex++;
        }
        numberCount +=1;
    }
    //Check if all values entered by user are between 1 and 6
    for(unsigned int i:numbers){
        if (i > 6 || i < 1) {
            explode_bomb();
        }
    }
    //Check if user entered any values more than once
    for(int i = 0; i < 5; i++){
        for(int j = i+1; j < 6; j++){
            if (numbers[i]==numbers[j]){
                explode_bomb();
            }
        }
    }
    //save node addresses into an array in the order specified by the user input
    //this array represents the array in the stack that is filled after loops 3 and 4 in ASM code
    for(int i = 0; i < 6; i++){
        nodes.moveToPos(numbers[i]-1);
        nodeAddresses[i] = nodes.curr;
        nodes.moveToStart();
    }

    //LOOP5
    //Change the address to which each node points to
    //Nodes will point to the next node according to the numbers in user input
    for(int i = 0; i < 5; i++){
        nodeAddresses[i]->next = nodeAddresses[i+1];
    }

    //LOOP6
    //Check if the nodes are in decreasing integer value order
    for(int i = 0; i < 5; i++){
        if(nodeAddresses[i]->data < nodeAddresses[i+1]->data)
            explode_bomb();
    }
    return;
}

ASM CODE
/*
   0x0000555555555770 <+0>:     endbr64 
   0x0000555555555774 <+4>:     push   %r12
   0x0000555555555776 <+6>:     push   %rbp
   0x0000555555555777 <+7>:     push   %rbx
   0x0000555555555778 <+8>:     sub    $0x50,%rsp
memory allocation
   0x000055555555577c <+12>:    lea    0x30(%rsp),%rsi
   0x0000555555555781 <+17>:    call   0x555555555ac9 <read_six_numbers>
Parse user entered string, store the first six numbers in an array in the stack
function returns the amount of numbers entered by user

   0x0000555555555786 <+22>:    mov    $0x0,%ebp
%ebp is counter1
    increments every time one user entered value has been compared to the other user entered values and found not to be equal to any other values, over 6 or under 1. 
    
   0x000055555555578b <+27>:    jmp    0x5555555557b6 <phase_6+70>
   0x000055555555578d <+29>:    call   0x555555555a9d <explode_bomb>
   0x0000555555555792 <+34>:    jmp    0x5555555557ca <phase_6+90>
   
LOOP 2 code starts
LOOP 1 code starts
   0x0000555555555794 <+36>:    add    $0x1,%ebx
increment counter2

   0x0000555555555797 <+39>:    cmp    $0x5,%ebx
   0x000055555555579a <+42>:    jg     0x5555555557b3 <phase_6+67>
end loop iteration if counter2 > 5

   0x000055555555579c <+44>:    movslq %ebp,%rax
   0x000055555555579f <+47>:    movslq %ebx,%rdx
   0x00005555555557a2 <+50>:    mov    0x30(%rsp,%rdx,4),%edi
   0x00005555555557a6 <+54>:    cmp    %edi,0x30(%rsp,%rax,4)
   0x00005555555557aa <+58>:    jne    0x555555555794 <phase_6+36>
LOOP 1 code ends
    This loop compares the user entered value at the "counter" position to all the numbers entered afterwards
    If the number is equal to any number entered afterwards, the bomb explodes
    user must not enter repeated numbers in the string to avoid this explosion

   0x00005555555557ac <+60>:    call   0x555555555a9d <explode_bomb>
   0x00005555555557b1 <+65>:    jmp    0x555555555794 <phase_6+36>
   0x00005555555557b3 <+67>:    mov    %r12d,%ebp
   0x00005555555557b6 <+70>:    cmp    $0x5,%ebp
   0x00005555555557b9 <+73>:    jg     0x5555555557d3 <phase_6+99>
end loop iteration if counter1 > 5
   
   0x00005555555557bb <+75>:    movslq %ebp,%rax
   0x00005555555557be <+78>:    mov    0x30(%rsp,%rax,4),%eax
load user entered value for comparison
   
   0x00005555555557c2 <+82>:    sub    $0x1,%eax
   0x00005555555557c5 <+85>:    cmp    $0x5,%eax
   0x00005555555557c8 <+88>:    ja     0x55555555578d <phase_6+29>
if any of the numbers entered by user is greater than 6 or lower than 1, explode bomb
   0x00005555555557ca <+90>:    lea    0x1(%rbp),%r12d
   0x00005555555557ce <+94>:    mov    %r12d,%ebx
counter2 starts at counter1 + 1 for each loop2 iteration
    counter2 increments at each loop1 iteration, which signifies it has compared the value at counter1 position to the value at counter2 position

   0x00005555555557d1 <+97>:    jmp    0x555555555797 <phase_6+39>
LOOP 2 code ends
    this loop cycles through all user entered values, checks to make sure they are between 1 and 6, and calls the other loop that will check if any numbers were repeated.

LOOP3 code starts
   0x00005555555557d3 <+99>:    mov    $0x0,%esi
%esi is counter3, starts at 0
    increment every time a node address is copied to the address array in the stack
    
   0x00005555555557d8 <+104>:   jmp    0x5555555557e1 <phase_6+113>
   0x00005555555557da <+106>:   mov    %rdx,(%rsp,%rcx,8)
copy node address to an array of node addresses in the stack

   0x00005555555557de <+110>:   add    $0x1,%esi
   0x00005555555557e1 <+113>:   cmp    $0x5,%esi
   0x00005555555557e4 <+116>:   jg     0x555555555804 <phase_6+148>
end loop execution if counter3 > 5

   0x00005555555557e6 <+118>:   mov    $0x1,%eax
%eax is counter 4, starts at 1
    increments every time current node to be copied is changed to a subsequent node
    
   0x00005555555557eb <+123>:   lea    0x3a1e(%rip),%rdx        # 0x555555559210 <node1>
reset node address to copy after each loop3 iteration

LOOP 4 code starts
   0x00005555555557f2 <+130>:   movslq %esi,%rcx
   0x00005555555557f5 <+133>:   cmp    %eax,0x30(%rsp,%rcx,4)
   0x00005555555557f9 <+137>:   jle    0x5555555557da <phase_6+106>
repeat loop4 if counter4 < 6
LOOP3 code ends
    loop3 will continue to iterate until the addresses of all six nodes have been copied to the address array in the stack
    
   0x00005555555557fb <+139>:   mov    0x8(%rdx),%rdx
   0x00005555555557ff <+143>:   add    $0x1,%eax
   0x0000555555555802 <+146>:   jmp    0x5555555557f2 <phase_6+130>
LOOP 4 code ends
    Loop4 sets the node address to be copied to the stack at position counter3 to the user entered value
        if user enters "5 4 2 6 3 1"
            first node address copied to stack array will be of node 5
            second of node 4, third of node 2, fourth of node 6, etc.
        actual copy procedure occurs during loop3 code, they are intertwined

after LOOP3 and LOOP4 end, all node addresses will have been copied to the address array in the stack, in order of how the user input the numbers

   0x0000555555555804 <+148>:   mov    (%rsp),%rbx
   0x0000555555555808 <+152>:   mov    %rbx,%rcx
   0x000055555555580b <+155>:   mov    $0x1,%eax
%eax counter 5, starts at 1
    increments every time one node address value is changed
    
LOOP5 code starts
   0x0000555555555810 <+160>:   jmp    0x555555555823 <phase_6+179>
   0x0000555555555812 <+162>:   movslq %eax,%rdx
   0x0000555555555815 <+165>:   mov    (%rsp,%rdx,8),%rdx
   0x0000555555555819 <+169>:   mov    %rdx,0x8(%rcx)
   0x000055555555581d <+173>:   add    $0x1,%eax
   0x0000555555555820 <+176>:   mov    %rdx,%rcx
   0x0000555555555823 <+179>:   cmp    $0x5,%eax
   0x0000555555555826 <+182>:   jle    0x555555555812 <phase_6+162>
LOOP5 code ends
    this loop changes the addresses to which every node points to
    new addresses within each node will correspond to the order of the numbers entered by the user
        user entered "5 4 2 6 3 1"
        before LOOP5: node1 -> node2 -> node3 -> node4 -> node5 -> node6 -> null
        after LOOP5: node5 -> node4 -> node2 -> node6 -> node3 -> node1 -> null
    
   0x0000555555555828 <+184>:   movq   $0x0,0x8(%rcx)
   0x0000555555555830 <+192>:   mov    $0x0,%ebp
%ebp is counter6, starts at 0
    increments every time a comparison is done between a value in current node and a value in next node
    
   0x0000555555555835 <+197>:   jmp    0x55555555583e <phase_6+206>

LOOP6 code starts
   0x0000555555555837 <+199>:   mov    0x8(%rbx),%rbx
increment node

   0x000055555555583b <+203>:   add    $0x1,%ebp
   0x000055555555583e <+206>:   cmp    $0x4,%ebp
   0x0000555555555841 <+209>:   jg     0x555555555854 <phase_6+228>
Loop6 will continue as long as counter6 < 5

   0x0000555555555843 <+211>:   mov    0x8(%rbx),%rax
   0x0000555555555847 <+215>:   mov    (%rax),%eax
   0x0000555555555849 <+217>:   cmp    %eax,(%rbx)
   0x000055555555584b <+219>:   jge    0x555555555837 <phase_6+199>
compares the value in current node with the value in the next node
    if the value in current node is greater than or equal to the value in next node, continue iterations
    if nodes are ordered in descending order according to their stored integer values, the function will finish successfully.
        node values: node1 contains 0x4c, node2 contains 0x64, node3 contains 0x26d, node4 contains 0xf9, node5 contains 0x26c, node6 contains 0x3e6
        correct final order is node6 > node3 > node5 > node4 > node2 > node1
        user must enter "6 3 5 4 2 1" 
        
   0x000055555555584d <+221>:   call   0x555555555a9d <explode_bomb>
   0x0000555555555852 <+226>:   jmp    0x555555555837 <phase_6+199>
   0x0000555555555854 <+228>:   add    $0x50,%rsp
memory deallocation
   0x0000555555555858 <+232>:   pop    %rbx
   0x0000555555555859 <+233>:   pop    %rbp
   0x000055555555585a <+234>:   pop    %r12
   0x000055555555585c <+236>:   ret
 */

void secret_phase(string &input) {

}

ASM CODE
/*

 */

#endif



