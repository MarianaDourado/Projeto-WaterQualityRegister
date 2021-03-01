#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char bact; // bacteriologico (A)/P
    float turbidez; // em unidades de turbidez (turbidez <= 5)
    float CRL; // Cloro residual livre em mg/dl (0,2 <= CRL <= 2,0)
    float cor; // em unidades Hazen ( cor <= 15)
}water;

typedef struct{
    unsigned int n_habitantes; // %u
    char UF[2];
}state;

int main(){
    int choice;
    water agua;
    state estado;
    FILE *f;

    printf("Ola, servidor(a)! Bem-vindo(a) ao QWRegister. Para comecar, selecione uma opcao: \n");
    printf("(1) Registrar um Estado\n(2) Ler um registro\n(3) Alterar um registro\n(4) Deletar um registro\n (5) Encerrar o programa");
    scanf("%d", &choice);

    switch(choice){
        case 1:
        printf("Voce escolheu registrar um Estado. Insira o UF: "); // deve ser maiusculo
        scanf("%s", &estado.UF); //tem & ?
        if(){ //se um arquivo com a UF desse estado ja existe
            printf("Esse estado ja foi registrado. O que deseja fazer?\n");
            printf("(1) Alterar os dados\n(2) Ver dados\n(3) Apagar os dados");
            /* FORMA 2 
            printf("Esse estado ja foi registrado. Pressione qualquer tecla para ser redirecionado ao menu principal.\n");
            getchar();
            // como redirecionar ao menu principal?
            */
        }else{ // Registrando o estado

        }

        break;

        case 2:
        if(){ // se não há registros
            printf("Ainda nao ha registros cadastrados no sistema.\n");
        }
        break;
            

        case 3:
        if(){ // se não há registros
                printf("Ainda nao ha registros cadastrados no sistema.\n");
        }
        break;

        case 4:
        if(){ // se não há registros
                printf("Ainda nao ha registros cadastrados no sistema.\n");
        }
        break;

        case 5:
        if(){ // se não há registros
            printf("Ainda nao ha registros cadastrados no sistema.\n");
        }
        break;

        default:
        printf("Essa opcao nao existe! Tente novamente.\n");
        break;
    }

    return 0;
}

int verifica_existencia_registros(){ // implementar depois

}
