#include "kernel/types.h"
#include "user/user.h"

// One stage of the sieve: rd is the pipe with the numbers from the left.
void sieve(int rd) __attribute__((noreturn));

void
sieve(int rd)
{
  int p, n;

  if(read(rd, &p, sizeof(p)) != sizeof(p)){   // nothing left: the chain ends
    close(rd);
    exit(0);
  }
  printf("prime %d\n", p);                    // the first number is a prime

  int pp[2];
  pipe(pp);
  if(fork() == 0){
    close(pp[1]);                             // the next stage only reads
    close(rd);
    sieve(pp[0]);
  }
  close(pp[0]);                               // this stage only writes
  while(read(rd, &n, sizeof(n)) == sizeof(n)){
    if(n % p != 0)
      write(pp[1], &n, sizeof(n));            // forward what p does not divide
  }
  close(rd);
  close(pp[1]);                               // the next stage sees end of file
  wait(0);
  exit(0);
}

int
main(int argc, char *argv[])
{
  int fd[2];

  pipe(fd);
  if(fork() == 0){
    close(fd[1]);
    sieve(fd[0]);
  }
  close(fd[0]);
  for(int i = 2; i <= 35; i++)
    write(fd[1], &i, sizeof(i));
  close(fd[1]);
  wait(0);
  exit(0);
}
