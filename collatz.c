#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int collatz(int num);

int main(int argc, char *argv[]) {

   int test_count;
   int min_value;
   int max_value;

   sscanf(argv[1], "%d", &test_count);
   sscanf(argv[2], "%d", &min_value);
   sscanf(argv[3], "%d", &max_value);

   FILE *file_ptr;
   file_ptr = fopen("collatzdata.csv", "w+");
   fprintf(file_ptr, "Number, Steps\n");

   srand(time(NULL));
   for (int i=0; i < test_count; i++) {
      int rand_num = rand() * (RAND_MAX + 1) + rand();      //RAND_MAX was only 32727 in my environment; this line was to allow for higher number generation.
      int test_value = rand_num % (max_value - min_value + 1) + min_value;
      int result = collatz(test_value);
      fprintf(file_ptr, "%d, %d\n", test_value, result);
   }

   fclose(file_ptr);
   return 0;
}


int collatz_caching(int num) {
   return collatz(num);
}

int collatz(int num) {

   if (num == 1) {
      return 0;
   }

   int steps;
   if (num % 2 == 0) {
      steps = 1 + collatz_caching(num / 2);
   }
   else {
      steps = 1 + collatz_caching(num * 3 + 1);
   }

   return steps;
}