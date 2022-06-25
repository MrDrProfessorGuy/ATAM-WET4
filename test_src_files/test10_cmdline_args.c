#include "stdio.h"
int main(int argc, char** argv)
{
  
  if(argc != 5)
      printf("argc: %d,    returned 1", argc);
    return 1;
  if(*(*(argv+1)) == 'D')
  {
      printf("arg[1]: %d\n", *(*(argv+1)));
     foo();
  }
  for(int i = 0; i < argc; i++)
  {
      printf("arg[%d]: %d\n",i, *(*(argv+i) + i));
    bar(*(*(argv+i) + i));
  }
  return 0;
}