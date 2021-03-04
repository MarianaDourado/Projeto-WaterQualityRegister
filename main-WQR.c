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

char STATE[27][3]; // FAZER MALLOC

state state_data;
water water_data;

void find_file(char* UF);


int main(){
    int i;
    int choice, choice2;



//-----------------------screen1--------------------------------
    system("clear");
    printf("Ola, servidor(a)! Bem-vindo(a) ao QWRegister. Para comecar, selecione uma opcao: \n");
    printf("(1) Registrar um estado\n(2) Visualizar um registro\n(3) Alterar um registro\n(4) Deletar um registro\n(5) Encerrar o programa\n");
    scanf("%d", &choice);

    file = fopen("GO.txt", "r+");
    
    if(file==NULL)
    {
        printf("Arquivo nao encontrado\n");
        return 0;
    }
    

    switch(choice){
        case 1:
        printf("Voce escolheu registrar um estado. Insira o UF: "); // deve ser maiusculo
        scanf("%s", &state_data.UF); //tem & ?

        //find_file(state_data.UF);
        if(file == NULL){
            printf("Erro na abertura do arquivo!");
            return 0;
        }
        
        if(fscanf(file, "%u%*c", &state_data.n_habitantes) != 0){ //se um arquivo com a UF desse estado ja existe (1a linha != 0)
            printf("Esse estado ja foi registrado. O que deseja fazer?\n");
            printf("(1) Alterar os dados\n(2) Visualizar dados\n(3) Apagar os dados\n");
            scanf("%d%*c", &choice2);
            //printf("hab:%d\n",state_data.n_habitantes);
            switch(choice2){
                case 1:
                
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
                
                //printf("%u\n%d\n%.3lf\n%.3lf\n%.3lf\n", state_data.n_habitantes, state_data.state_water.bact, state_data.state_water.turbidez, state_data.state_water.CRL,state_data.state_water.cor);
                memset(P,'\0',strlen(P));
                sprintf(P,"%u\n%d\n%lf\n%lf\n%lf\n", state_data.n_habitantes, state_data.state_water.bact, state_data.state_water.turbidez, state_data.state_water.CRL,state_data.state_water.cor);
                
                rewind(file);
                if(fwrite(P, sizeof(char), sizeof(P), file) != sizeof(P)){//unsigned fwrite(void *buffer,int numero_de_bytes,int count,FILE *fp);
                    printf("but you dont succeed...");
                }
                else{
                    printf("deu certo");
                }

                


                break;


                case 2:
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
            }

        }
        
        else{ // Registrando o estado (1a linha do arquivo = 0)
            //colocar fputs (escreve) no arquivo da uf

        }

        break;   

        
        case 2:
        printf("Voce escolheu visualizar um registro. Insira o UF: "); // deve ser maiusculo
        scanf("%s", &state_data.UF);
        if(fscanf(file, "%d%*c", &state_data.n_habitantes) == 0){ // se não há registros
            printf("Ainda nao ha registros cadastrados no sistema.\n");
        }
        else{

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
    //file = fopen(".txt", "rw");
    if(strcmp(UF, "AC") == 0){ //1
        file = fopen("AC.txt", "r+"); 
    }
    if(strcmp(UF, "AL") == 0){
        file = fopen("AL.txt", "r+");
        
    }
    if(strcmp(UF, "AP") == 0){
        file = fopen("AP.txt", "r+");
        
    }
    if(strcmp(UF, "AM") == 0){
        file = fopen("AP.txt", "r+");
        
    } 
    if(strcmp(UF, "BA") == 0){ //5
        file = fopen("BA.txt", "r+");
        
    }
    if(strcmp(UF, "CE") == 0){
        file = fopen("CE.txt", "r+");
        
    } 
    if(strcmp(UF, "DF") == 0){
        file = fopen("DF.txt", "r+");
        
    }
    if(strcmp(UF, "ES") == 0){
        file = fopen("ES.txt", "r+");
        
    } 
    if(strcmp(UF, "GO") == 0){
        file = fopen("GO.txt", "r+");
        
    } 
    if(strcmp(UF, "MA") == 0){ //10
    file = fopen("MA.txt", "r+");
        
    }
    if(strcmp(UF, "MT") == 0){
        file = fopen("MT.txt", "r+");
        
    } 
    if(strcmp(UF, "MS") == 0){
        file = fopen("MS.txt", "r+");
        
    } 
    if(strcmp(UF, "MG") == 0){
        file = fopen("MG.txt", "r+");
        
    } 
    if(strcmp(UF, "PA") == 0){
      file = fopen("PA.txt", "r+");  
    } 
    if(strcmp(UF, "PB") == 0){ //15
        file = fopen("PB.txt", "r+");
    }
    if(strcmp(UF, "PR") == 0){
        file = fopen("PR.txt", "r+");
    } 
    if(strcmp(UF, "PE") == 0){
        file = fopen("PE.txt", "r+");
    } 
    if(strcmp(UF, "PI") == 0){
        file = fopen("PI.txt", "r+");
    }
    if(strcmp(UF, "RJ") == 0){
        file = fopen("RJ.txt", "r+");
    }
    if(strcmp(UF, "RN") == 0){ //20
        file = fopen("RN.txt", "r+");
    }
    if(strcmp(UF, "RS") == 0){
        file = fopen("RS.txt", "r+");
    } 
    if(strcmp(UF, "RO") == 0){
        file = fopen("RO.txt", "r+");
    } 
    if(strcmp(UF, "RR") == 0){
        file = fopen("RR.txt", "r+");
    } 
    if(strcmp(UF, "SC") == 0){
        file = fopen("SC.txt", "r+");
    } 
    if(strcmp(UF, "SP") == 0){ //25
        file = fopen("SP.txt", "r+");
    } //25
    if(strcmp(UF, "SE") == 0){
        file = fopen("SE.txt", "r+");
    } 
    if(strcmp(UF, "TO") == 0){ //27
        file = fopen("TO.txt", "r+");
    }

}
