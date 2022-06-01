#include "bpf_load.h"
#include <stdio.h>

void usage()
{
  printf("Usage: ./load_bpf <bpf_prog.o>\n");
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    usage();
    return -1;
  }
  
  if (load_bpf_file(argv[1]) != 0) {
    printf("Couldn't load the BPF program in %s\n", argv[1]);
    return -1;
  }

  read_trace_pipe();

  return 0;
}
