#include <stdio.h>
#include "cpu6502.h"
#include "cpu6502_debug.h"

int data[65536]={
  #include "rom.inc"
};

int _read(void *ref, int adr) {
  return data[adr];
}

void _write(void *ref, int adr, int value) {
  data[adr]=value;
}

int main(int argc, char *argv[]) {
  cpu6502_t cpu;

  cpu6502_init(&cpu, 0, _read, _write);

  cpu.reg_PC=0x400;

  cpu6502_run(&cpu, 100000000); // run 100 Million Clock Cycles

  if (cpu.reg_PC==0x3399) {
    printf("=== All tests successfull! ===\n");
    return 0;
  }
  else {
    printf("=== Test failed: PC=$%04X ===\n", cpu.reg_PC);
    return 1;
  }

}
