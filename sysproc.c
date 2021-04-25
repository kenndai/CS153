#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
    int status;

    if (argint(0, &status) < 0)
        return -1;
    exit(status); //no return
    return 0; // not reached
}

//int
//sys_exitstatus(void)
//{
//    int status;
//
//    if (argint(0, &status) < 0)
//        return -1;
//    exitstatus(status); //no return
//    return 0; // not reached
//}

int
sys_wait(void)
{
    int* status;

    //get the int* from arguments
    //argptr(int n, char **pp, int size), char** => array of cstrings, "word-sized system call argument"
    // Fetch the nth word-sized argument as a pointer to a block of memory of size bytes.
    // Check that the pointer lies within the process address space."
    if (argptr(0, (char**)&status, sizeof(int)) < 0) {
        return -1;
    }
    return wait(status); //pass in the argument here
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

