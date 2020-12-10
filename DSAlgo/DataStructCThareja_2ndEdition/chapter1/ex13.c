#include <stdio.h>

int min(int a, int b){
		  if(a>b)
					 return b;
		  return a;
}

int main(int argc, char const *argv[]) {
		  int a, b, c;
		  scanf("%d %d %d", &a, &b, &c);
		  printf("%d\n", min(a, min(b, c)));
		  return 0;
}
