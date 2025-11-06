#include <stdio.h>
#include <stdlib.h>



const int kNumberData1 = 100;
const int kNumberData2 = 200;
const float kPi = 3.1415f;
static int my_static_1 = 9;
static int my_static_2 = 8;
int g_global_initialized_1 = 1;
int g_global_initialized_2 = 1;
int g_global_1;
int g_global_2;
int g_global_3;
int g_global_4;

void FillAndPrintData(int* data, const int n_data) {
  for (int i = 0; i < n_data; ++i) {
    data[i] = n_data - i;
  }
  for (int i = 0; i < n_data; ++i) {
    printf("%d, ", data[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
#if DEBUG
  printf("Debug mode.\n\n");
#endif

  const int kNumberData3 = 300;
  int number_int_1 = 10;
  int number_int_2 = 6;
  int number_int_3 = 10;
  int number_int_4 = 6;
  int number_int_5 = 10;
  int number_int_6 = 6;
  printf("%d\n", number_int_1);
  printf("%d\n", number_int_2);
  printf("%d\n", number_int_3);
  printf("%d\n", number_int_4);
  printf("%d\n", number_int_5);
  printf("%d\n", number_int_6);

  int* data_1 = (int*)malloc(sizeof(int) * kNumberData1);
  int* data_2 = (int*) malloc(sizeof(int) * kNumberData2);
  FillAndPrintData(data_1, kNumberData1);
  FillAndPrintData(data_2, kNumberData2);

  printf("[Global] %d\n", g_global_1);
  printf("[Global] %d\n", g_global_2);
  printf("[Global] %d\n", g_global_3);
  printf("[Global] %d\n", g_global_4);
  printf("\n");



  printf("\n");
  printf("##Stack:\n");
  printf("[Auto 1] \t %p\n", &number_int_1);
  printf("[Auto 2] \t %p\n", &number_int_2);
  printf("[Auto 3] \t %p\n", &number_int_3);
  printf("[Auto 4] \t %p\n", &number_int_4);
  printf("[Auto 5] \t %p\n", &number_int_5);
  printf("[Auto 6] \t %p\n", &number_int_6);
  printf("[Local Const 3]  %p\n", &kNumberData3);

  printf("##Heap:\n");
  printf("[Dynamic Data 2] %p\n", data_2);
  printf("[Dynamic Data 1] %p\n", data_1);

  printf("##Block started by Symbol segment:\n");
  printf("[Global Const 4] %p\n", &g_global_4);
  printf("[Global Const 3] %p\n", &g_global_3);
  printf("[Global Const 2] %p\n", &g_global_2);
  printf("[Global Const 1] %p\n", &g_global_1);

  printf("##Data segment\n");
  printf("[Static 2] \t %p\n", &my_static_2); 
  printf("[Static 1] \t %p\n", &my_static_1);
  printf("[Init. global 2] %p\n", &g_global_initialized_2);
  printf("[Init. global 1] %p\n", &g_global_initialized_1);

  printf("##Read-Only data segment:\n");
  printf("[Global Const 3] %p\n", &kPi);
  printf("[Global Const 2] %p\n", &kNumberData2);
  printf("[Global Const 1] %p\n", &kNumberData1);

  printf("##Code segment:\n");
  printf("[Function] \t %p\n", &FillAndPrintData);
  printf("[Main] \t\t %p\n", &main);



  return 0;
}
