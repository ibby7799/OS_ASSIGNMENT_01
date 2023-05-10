# OS_ASSIGNMENT_01
Aurthor: Muhammad Ibrahim Roll no: K21-3093

Step 01: First we need to download these modules: • sudo apt-get install gcc • sudo apt-get install libncurses5-dev • sudo apt-get install bison • sudo apt-get install flex • sudo apt install make • sudo apt-get install libssl-dev • sudo apt-get install libelf-dev • sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe" • sudo apt-get update • sudo apt-get upgrade

Step 02: Making a new folder called hello:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/889f4bf9-def8-42ac-bfdb-6c5c31759e40)
Step 03: Adding a C code for the system call:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/1be03133-f0aa-4b62-879a-e7af123595df)
Code explanation:

a. We used #include <linux/kernel> because we are building a system call for our linux kernel.

b. Amslinkage simply means that the arguments for this function will be on the stack instead of the CPU registers.

c. Printk is used instead of printf because we are going to print in the kernel’s log file.

d. If the code is run and it returns 0, then it will mean that our program ran successfully and Hello world is written to out kernel’s log file.

Step 04: : Creating a Makefile for the C code:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/303b2892-4589-47fb-8358-8b0577aa271a)
Step 05: Adding the new code into the system table file:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/f31a9cf4-3ccd-4b4c-99ea-805c057c2b5d)
Step 06: Adding the prototype of the new system call into the system calls header file:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/6207a959-57bb-455c-abee-605bb1d7123f)
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/bed22524-14b0-4d8c-948a-e196c39bc74b)
Step 07: Changing version and adding the hello folder in the kernel’s Makefile:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/f94f48fc-40f7-4379-9d93-03e21e423f42)
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/5c00633d-8acb-4f67-b7c8-51f099b9f452)
Step 08: Creating a config file:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/9255be2a-ad17-437e-a8cd-fb522db92c1d)
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/d88f2cb9-b31e-41ae-8525-3910d5204c16)
Step 09: Cleaning and Compiling the kernel:
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/9d276983-2823-4e6f-8a9d-4ac2dca27006)
Step 10: Checking if the System call is Working Properly:

After logging into the newly compiled kernel, we check the system call by making a C code

named “userspace.c” and putting the following code in it:

#include <stdio.h>

#include <linux/kernel.h> #include <sys/syscall.h> #include <unistd.h> int main() { long int i = syscall(335); printf("System call sys_hello returned %ld\n", i); return 0; } Now we compile the code by typing “gcc userspace.c” and executing it by typing “./a.out”. If it returns 0, this means that our code has compiled successfully and the system call is working fine (Note that in calling syscall(335), 335 is the number where we added our system call in the table) and finally, we run “dmesg” to see the kernel messages and we will find “Hello World” written at the end of it.

![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/cd328739-e7e1-4bd7-b3da-5c6d79032593)
![image](https://github.com/ibby7799/OS_ASSIGNMENT_01/assets/127100347/d8ec8df7-4bfe-40af-bea7-76ede9d05397)



