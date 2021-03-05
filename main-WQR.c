#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

char P[50];

typedef struct{
    int bact; // bacteriologico (0)/1 //1
    double turbidez; // em unidades de turbidez (turbidez <= 5) //3
    double CRL; // Cloro residual livre em mg/dl (0,2 <= CRL <= 2,0) //2
    double cor; // em unidades Hazen ( cor <= 15) //4
}water;
//water *p_water=NULL;

typedef struct{
    unsigned int n_habitantes; // %u
    char UF[3];
    water state_water;
}state;

state *p_UF;

/*
[main-WQR.c 2021-03-05 01:09:28.874]
,,main-WQR.c:23:14: error: initializer element is not constant
   23 | state *p_UF= (state *) malloc(27 * sizeof(state));
      |              ^

[main-WQR.c 2021-03-05 01:09:45.808]
,,main-WQR.c:23:14: error: initializer element is not constant
   23 | state *p_UF= malloc(27 * sizeof(state));
      |              ^~~~~~

*/

//char STATE[27][3]; // FAZER MALLOC

state state_data;
water water_data;

void find_file(char* UF);

void while_update_info();


int main(){
    int choice, choice2;
    p_UF = malloc(27 * sizeof(state));



//-----------------------screen1--------------------------------
    system("clear");
    printf("Ola, servidor(a)! Bem-vindo(a) ao WQRegister. Para comecar, selecione uma opcao: \n");
    printf("(1) Registrar um estado\n(2) Visualizar um registro\n(3) Alterar um registro\n(4) Deletar um registro\n(5) Encerrar o programa\n");
    scanf("%d", &choice);

    //file = fopen("GO.txt", "r+");
    

    switch(choice){
        case 1: // INCOMPLETO - estudar 2o argumento da funcao "fopen"
        printf("Voce escolheu registrar um estado. Insira o UF: "); // deve ser maiusculo
        scanf("%s%*c", state_data.UF); //tem & ?

        find_file(state_data.UF);
        
        if(fscanf(file, "%u%*c", &state_data.n_habitantes) != 0){ //se um arquivo com a UF desse estado ja existe (1a linha != 0) 
            printf("Esse estado ja foi registrado. O que deseja fazer?\n");
            printf("(1) Alterar os dados\n(2) Visualizar dados\n(3) Deletar os dados\n");
            scanf("%d%*c", &choice2);
            //printf("hab:%d\n",state_data.n_habitantes);
            switch(choice2){
                case 1: // Alteração OKAY
                
                rewind(file);  //volta para o começo do arquivo

                
                printf("Esses sao os dados atuais.\n");
                
                fscanf(file,"%u%*c", &state_data.n_habitantes);
                printf("[1] Quantidade de habitantes: %u\n",state_data.n_habitantes);

                fscanf(file, "%d%*c", &state_data.state_water.bact);
                printf("[2] Presenca de bacterias(0/1): %d\n", state_data.state_water.bact);

                fscanf(file, "%lf%*c", &state_data.state_water.turbidez);
                printf("[3] Turbidez: %.3lfuT\n", state_data.state_water.turbidez);

                fscanf(file, "%lf%*c", &state_data.state_water.CRL);
                printf("[4] Cloro residual livre: %.3lfmg/dl\n", state_data.state_water.CRL);

                fscanf(file, "%lf%*c", &state_data.state_water.cor);
                printf("[5] Cor em unidades Hazen: %.3lfuH\n", state_data.state_water.cor);
                
                while_update_info();   //altera o dado escolhido
                
                //printf("%u\n%d\n%.3lf\n%.3lf\n%.3lf\n", state_data.n_habitantes, state_data.state_water.bact, state_data.state_water.turbidez, state_data.state_water.CRL,state_data.state_water.cor);
                memset(P,'\0',strlen(P));
                sprintf(P,"%u\n%d\n%lf\n%lf\n%lf", state_data.n_habitantes, state_data.state_water.bact, state_data.state_water.turbidez, state_data.state_water.CRL,state_data.state_water.cor);
                
                rewind(file);
                if(fwrite(P, sizeof(char), sizeof(P), file) != sizeof(P)){ //unsigned fwrite(void *bUFfer,int numero_de_bytes,int count,FILE *fp);
                    printf("when you try your best, but you dont succeed.");
                }
                else{
                    printf("deu certo");
                }

                break;


                case 2: //Visualização OKAY
                rewind(file);

                fscanf(file, "%u%*c", &state_data.n_habitantes);
                
                printf("Numero de habitantes de %s: %u\n", state_data.UF, state_data.n_habitantes);

                fscanf(file, "%d%*c", &state_data.state_water.bact);
                printf("Presenca de bacterias(0/1): %d\n", state_data.state_water.bact);

                fscanf(file, "%lf%*c", &state_data.state_water.turbidez);
                printf("Turbidez: %.3lfuT\n", state_data.state_water.turbidez);

                fscanf(file, "%lf%*c", &state_data.state_water.CRL);
                printf("Cloro residual livre: %.3lfmg/dl\n", state_data.state_water.CRL);

                fscanf(file, "%lf%*c", &state_data.state_water.cor);
                printf("Cor em unidades Hazen: %.3lfuH\n", state_data.state_water.cor);


                break;

                case 3: // Deletar OKAY
                sprintf(P,"0");
                
                rewind(file);
                fwrite(P, sizeof(char), sizeof(P), file);
                break;

                default:
                break;
            }

        }
        
        
        else{ // FALTA ! Registrando um novo estado (1a linha do arquivo = 0 (?))
            
            //create_file();
            
        }

        break;   

        
        case 2: // INCOMPLETO
        printf("Voce escolheu visualizar um registro. Insira o UF: "); // deve ser maiusculo
        scanf("%s", state_data.UF);
        if(fscanf(file, "%d%*c", &state_data.n_habitantes) == 0){ // se não há registros
            printf("Ainda nao ha registros cadastrados no sistema.\n");
        }
        else{
            rewind(file);

            fscanf(file, "%u%*c", &state_data.n_habitantes);
                
            printf("Numero de habitantes de %s: %u\n", state_data.UF, state_data.n_habitantes);

            fscanf(file, "%d%*c", &state_data.state_water.bact);
            printf("Presenca de bacterias(0/1): %d\n", state_data.state_water.bact);

            fscanf(file, "%lf%*c", &state_data.state_water.turbidez);
            printf("Turbidez: %.3lfuT\n", state_data.state_water.turbidez);

            fscanf(file, "%lf%*c", &state_data.state_water.CRL);
            printf("Cloro residual livre: %.3lfmg/dl\n", state_data.state_water.CRL);

            fscanf(file, "%lf%*c", &state_data.state_water.cor);
            printf("Cor em unidades Hazen: %.3lfuH\n", state_data.state_water.cor);
        }

        break;
            

        /*case 3:
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
        return 0;
        break;

        default:
        printf("Essa opcao nao existe! Tente novamente.\n"); // como implementar isso?
        break; */
    }

    fclose(file);
    return 0;
}

void find_file(char* UF)
{
    //state *p_UF=NULL;
    strcpy(p_UF[0].UF, "AC");
    strcpy(p_UF[1].UF, "AL");
    strcpy(p_UF[2].UF, "AP");
    strcpy(p_UF[3].UF, "AM");
    strcpy(p_UF[4].UF, "BA");
    strcpy(p_UF[5].UF, "CE");
    strcpy(p_UF[6].UF, "DF");
    strcpy(p_UF[7].UF, "ES");
    strcpy(p_UF[8].UF, "GO");
    strcpy(p_UF[9].UF, "MA");
    strcpy(p_UF[10].UF, "MG");
    strcpy(p_UF[11].UF, "MS");
    strcpy(p_UF[12].UF, "MT");
    strcpy(p_UF[13].UF, "PA");
    strcpy(p_UF[14].UF, "PB");
    strcpy(p_UF[15].UF, "PE");
    strcpy(p_UF[16].UF, "PI");
    strcpy(p_UF[17].UF, "PR");
    strcpy(p_UF[18].UF, "RJ");
    strcpy(p_UF[19].UF, "RN");
    strcpy(p_UF[20].UF, "RS");
    strcpy(p_UF[21].UF, "RO");
    strcpy(p_UF[22].UF, "RR");
    strcpy(p_UF[23].UF, "SC");
    strcpy(p_UF[24].UF, "SE");
    strcpy(p_UF[25].UF, "SP");
    strcpy(p_UF[26].UF, "TO");

    char filename[7];
    int i;
    for(i=0;i<27;i++)
    {
        if(strcmp(UF, p_UF[i].UF)==0) break;
    }

    sprintf(filename, "%s.txt", p_UF[6].UF); // -> ou .]
    printf("arquivo:%s\n",filename);
    file = fopen(filename, "w+");


    /*
    int k;
    for (k = 0; k < 27; k++) {
        char filename[7]; // UF.txt
        sprintf(filename, "%s.txt", p_UF[k]->UF); // Teste-00.txt; Teste-01.txt; .; Teste-99.txt
        file = fopen(filename, "w+");
        if (file != NULL) {
            fclose(file);
        } else {
            perror(filename);
            exit(EXIT_FAILURE);
        }
    }*/

}

void while_update_info()
{
    int num_altera;

    while(1)
    {
        printf("Escreva o indice que voce deseja alterar: ");
        scanf("%d", &num_altera);

        switch (num_altera)
        {
            case 1:
                printf("Informe o novo valor do numero de habitantes: ");
                scanf("%u", &state_data.n_habitantes);
                break;
            case 2:
                printf("Informe o novo valor do exame bacteriologico (0 ou 1): ");
                scanf("%d", &state_data.state_water.bact);
                break;
            case 3:
                printf("Informe o novo valor da turbidez: ");
                scanf("%lf", &state_data.state_water.turbidez);
                break;
                    

            case 4: // CRL
                printf("Informe o novo valor do CRL: ");
                scanf("%lf", &state_data.state_water.CRL);
                break;

            case 5: // Cor
                printf("Informe o novo valor da cor em unidades Hazen: ");
                scanf("%lf", &state_data.state_water.cor);
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n"); // como faz mesmo?
                break;
        }
                    printf("Deseja alterar alguma outra informacao?\n(1) Sim\n(2) Nao\n");
                
                    scanf("%d", &num_altera); //reciclado
                    if(num_altera==2) break;
                
    }
}

