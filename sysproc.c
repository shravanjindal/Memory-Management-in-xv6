#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_numpp(void)
{
    struct proc *curproc = myproc();
    return numpp(curproc); // Call the `numpp` function with the current process
}
int sys_numvp(void) {
    struct proc *p = myproc();  // Get the current process
    // Calculate the number of virtual pages
    int num_pages = PGROUNDUP(p->sz) / PGSIZE;  // Round up to account for partial pages
    // Add 1 to count the stack guard page
    num_pages += 1; 
    return num_pages;  // Return the total number of virtual pages
}
// sysproc.c
int sys_mmap(void) {
    int bytes;

    // Get the argument for the mmap call
    if (argint(0, &bytes) < 0 || bytes <= 0 || bytes % PGSIZE != 0) {
        return 0;  // Return 0 for invalid input
    }

    struct proc *p = myproc();
    uint oldsz = p->sz;
    uint newsz = oldsz + bytes;

    // Increase the virtual address space without allocating physical memory
    p->sz = newsz;

    return oldsz;  // Return the starting address of the newly added memory region
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
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
