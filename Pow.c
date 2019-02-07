#include "stdio.h"
int main(){
  printf("Pow: \n");
  float sum, num, pow, i;
  sum =  num = pow = i = 0;
  scanf("%f %f", &num, &pow);
  if(pow == 0){
   sum = 1;
   printf("Pow %f %f: %f", num, pow, sum);
   return 0;
  }
  sum = num;
  for(++i; i < pow; i++){
    sum = sum*num;
  }
  printf("Pow %f %f: %f\n", num, pow, sum);
  return 0;
}
