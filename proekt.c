#include <stdio.h>   //Необходими библиотеки
#include <math.h>

//Структура от данни за начални изчисления
struct data_measurement{
   float avg_usage;
   float avg_time;
   int mx_usage;
   int mx_time;
};

//Структура от данни за финални изчисления
struct reoder_calculation{
  float safety_stock;
  float reorder_point_level;
  int current_level_stock;
  int MSL;
  int quantity;
};

//Протипни функции  
float average_usage(char* files_for_sales);
int max_usage(char* files_for_sales);
float average_time(int list_time_delivery[], int n);
int max_time(int list_time_delivery[], int n);

//Главна функция
int main(){
    int length;  //Променлива с размер
    do
    {
     printf("Please enter possitive size: "); 
     scanf("%d",&length); // Задължително положително дължина
    }
    while(length <= 0);

    int lst_delivery_times[length];  // Размер на масива елемент(ден за доставка)

    for (int i = 0; i < length; i++)
    {
        printf("Type an element of the array [%d]: ", i); 
        scanf("%d",&lst_delivery_times[i]); 
    }
        printf("The arrays is ");   //Елементи на масива
    for (int i = 0; i < length; i++)
    {
        printf("%d ", lst_delivery_times[i]); 
          //Визуализация на елементите
    }
        printf("\n");

    //Изчислиние на началните стойности от файл и горният масив
    struct data_measurement p1;
    p1.avg_usage  = average_usage("sales.txt");
    p1.mx_usage = max_usage("sales.txt");
    p1.avg_time = average_time(lst_delivery_times, length);
    p1.mx_time = max_time(lst_delivery_times, length);

    //Изчислиние на финалните стойности
    struct reoder_calculation p2;
    p2.safety_stock = (p1.mx_usage * p1.mx_time) - (p1.avg_usage * p1.avg_time);

    if (p2.safety_stock < 0)
    {
       printf("Error: Safety stock cannot be negative. Please check your input data.\n");
    }

    p2.reorder_point_level = (p1.avg_usage * p1.avg_time) + p2.safety_stock;
    float reorder_point_level_round = round(p2.reorder_point_level);   //Закръгляне 
    p2.current_level_stock;
    do
    {
      printf("Please type a current stock level: ");  
      scanf("%d",&p2.current_level_stock); // Задължително положително ниво 
    }
    while(p2.current_level_stock < 0);
    

    p2.MSL;
    printf("Enter a maximum stock level: ");  
    scanf("%d",&  p2.MSL);
    p2.quantity = 0;
    //Проверка дали е необходима поръчка
    if (p2.current_level_stock <= reorder_point_level_round)
    {
       p2.quantity = p2.MSL - p2.current_level_stock;
       printf("You need to reorder. Quntity to reorder: %d\n", p2.quantity);
    }
    else
    {
       printf("Тhe quanity of stock is above the reoder point level");
    }
    //Финално принтиране на данни
    printf("Average usage: %.2f\n", p1.avg_usage);
    printf("Max usage: %d\n", p1.mx_usage);
    printf("Average delivery time: %.2f\n", p1.avg_time);
    printf("Max delivery time: %d\n", p1.mx_time);
    printf("Safety stock: %.0f\n", p2.safety_stock);
    printf("Reorder point level: %.0f\n", reorder_point_level_round);
    printf("The required quantity you need to order is: %d\n ", p2.quantity);
}
//Функция за работа с файл
float average_usage(char* files_for_sales)
{
    FILE *file_name = fopen(files_for_sales, "r");  // Четене на файл
    if(file_name == NULL) //Проверка за файл
     {
      printf("Unable to open file!\n");
      return 1;
     }
    int value_of_number;
    int count_of_number = 0;
    float total= 0;
    while (fscanf(file_name, "%d", &value_of_number) == 1)  //Вземане на число от файл
    {
      total += value_of_number; //Сумата от числата
      count_of_number ++;
    }
    fclose(file_name);
    float avgu = total / count_of_number;

    return avgu;
}
//Функция за работа с файл
int max_usage(char* files_for_sales)
{
    FILE *file_name = fopen(files_for_sales, "r");  // Четене на файл
    if(file_name == NULL)  //Проверка за файл
     {
      printf("Unable to open file!\n");
      return 1;
     }
    int value_of_number;
    int max_value = 0;
    while (fscanf(file_name, "%d", &value_of_number) == 1)  //Вземане на число от файл
    {
     if (value_of_number > max_value)
     {
      max_value = value_of_number;   //Присвояване на максимална стойност
     }
    }
    fclose(file_name);

    return max_value;
  }
//Функция за изчисляване на средно време за доставка
float average_time(int list_time_delivery[], int n)
{
    int total_time = 0;
    if (n <= 0) //Проверка за празен списък
    {
      return 1;
    }
    for (int i = 0; i < n;i++)
    {
       total_time += list_time_delivery[i];  //Сбор от елементи на масиви
    }
    float avgt = (float)total_time / n;   //Изчисляване на средно време за доставка

    return avgt;
}
//Функция за изчисляване на максимално време за доставка
int max_time(int list_time_delivery[], int n)
{
    if (n <= 0)    //Проверка за празен списък
    {
      return 1;
    }
    int max_time = 0;

    for(int i = 0; i < n ; i++)
      {
        if (list_time_delivery[i] > max_time)  //Изчсл на макс.време за доставка
        {
          max_time = list_time_delivery[i];
        }
      }
    return max_time;
}
