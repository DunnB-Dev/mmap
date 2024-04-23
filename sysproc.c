#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

uint64
sys_mmap(void) {

/*
  uint64 addr;
  uint64 length;
  int permission;
  int flag;
  int fd;
  int offset;
  int used;

  // Get the arguments from the user space
  if (argaddr(0, &addr) < 0 || argaddr(1, &length) < 0 || argint(2, &permission) < 0 ||
      argint(3, &flag) < 0 || argfd(4, &fd, NULL) < 0 || argint(5, &offset) < 0) {
    return -1;
  }

  // Find a free VMA slot in the process's vmas array
  struct proc *p = myproc();
  int i;
  for (i = 0; i < VMASIZE; i++) {
    if (!p->vmas[i].used) {
      break;
    }
  }
  if (i == VMASIZE) {
    return -1; // No free VMA slot found
  }

  // Find a free region in the user address space to map the file
  addr = PGROUNDUP(p->sz);
  p->sz = addr + length;

  // Initialize the VMA
  struct vma *vma = &p->vmas[i];
  vma->addr = addr;
  vma->length = length;
  vma->permission = permission;
  vma->flag = flag;
  vma->offset = offset;
  vma->used = used;

  // Get the file structure from the file descriptor
  struct file *f = p->ofile[fd];
  if (f == NULL) {
    return -1; // Invalid file descriptor
  }
  vma->file = filedup(f); // Increment the file reference count

  // Mark the VMA as used
  vma->used = 1;

  return addr;
*/
	return -1;

}

uint64
sys_munmap(void)
{
	return -1;
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
