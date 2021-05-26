#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <unistd.h> //Para a função sleep() - Linux

typedef struct
{
    int tm_sec;               //representa os seconds de 0 a 59
    int tm_min;               //representa os minutos de 0 a 59
    int tm_hour;              //representa as horas de 0 a 24
    int tm_mday;              //dia do mês de 1 a 31
    int tm_mon;               //representa os meses do ano de 0 a 11
    int tm_year;              //representa o ano a partir de 1900
    int tm_wday;              //dia da semana de 0 (domingo) até 6 (sábado)
    //int tm_yday;              // dia do ano de 1 a 365
    //int tm_isdst;             //indica horário de verão se for diferente de zero
}tm;

tm *calend; //ponteiro para struct que armazena data e hora   
  

int temp=0, finish=1,excluded=1; //variaveis aux

char filename[7];
char P[50]; 

FILE *file;

typedef struct{
    int bact; // bacteriologico (0)/1
    double turbidez; // em unidades de turbidez (turbidez <= 5) 
    double CRL; // Cloro residual livre em mg/L (0,5 <= CRL <= 2,0) 
    double cor; // em unidades Hazen ( cor <= 15) 
}water;

typedef struct{
    unsigned int n_habitantes; // %u
    char UF[3];
    water state_water;
}state;

//ponteiro para a struct water
state *p_UF;

state state_data;
water water_data;





//========FUNÇÕES=========
int find_file();

int verify_data_existence();

void write_in_file();

void register_data();

void register_or_not();

void update_data();

void while_update_info();

void read_file();

void print_data_and_problems();

void delete_data();

void while_delete_data();

void thanks_return();
