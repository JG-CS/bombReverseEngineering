# bombReverseEngineering

Students were tasked with reverse engineering a C program's code to find 6 "passwords" required to "defuse the bomb". After analyzing the code,
students had to produce C, C++ or Python code that followed the program's logic as proof that they were able to successfully reverse engineer the 
program. 

In practice, the C program had 6 functions, each of which required a specific input to run without terminating the program. Students 
had to analyze the compiled C program's ASM code to determine these 6 inputs to be able to run the program while preventing early termination.

Contents: 
  justification.pdf
    Contains my hand tracing of the ASM code. To better understand the code I was working with, I did multiple passes through the code. The initial 
    simply translated ASM into easier to understand pseudo code, the second pass focused on following the code's execution and determining a higher level
    structure, and, when necessary, third passes focused on analyzing what was written in previous passes to ascertain how the whole function worked and 
    handled different types of inputs. 
  bomb.c
    Contains C++ code that is equivalent to the ASM code that was reverse engineered. 
  bomb
    Bomb program binary that was reverse engineered.
   
