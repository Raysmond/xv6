#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096
// Page table/directory entry flags.
#define PTE_P           0x001   // Present
#define PTE_W           0x002   // Writeable
#define PTE_U           0x004   // User
#define PTE_PWT         0x008   // Write-Through
#define PTE_PCD         0x010   // Cache-Disable
#define PTE_A           0x020   // Accessed
#define PTE_D           0x040   // Dirty
#define PTE_PS          0x080   // Page Size
#define PTE_MBZ         0x180   // Bits must be zero

int getx(char* buf){ // parse hex char into int 
    int ret = 0;
    if(buf[1] == 'x' || buf[1] == 'X')
    	buf += 2; // start by 0x or 0X
    while (*buf) { 
        if (*buf >= 'a') *buf = *buf-'a'+'0'+10;
        ret = ret*16 + *buf - '0';
        ++buf;
    }
    return ret;
}

int
main(int argc, char *argv[])
{
  if (argc == 1 || argc > 3){
  	printf(1, "usage: showmappings 0xstart_addr 0xend_addr\n");
  }
  int start = getx(argv[1]), end = getx(argv[2]);
  printf(1, "start:%x, end:%x\n", start, end);
  for (; start <= end; start += PGSIZE){
    uint pte = (uint)getpte(start);
    printf(1, "page %x mapped to %x, PTE_P: %x, PTE_W: %x, PTE_U: %x\n", 
    		start, (pte & ~0xFFF)+(start & 0xFFF), pte&PTE_P, pte&PTE_W, pte&PTE_U);
  }
  
  exit();
}
