#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

char filename[7];

char P[50];

typedef struct{
    int bact; // bacteriologico (0)/1 //1
    double turbidez; // em unidades de turbidez (turbidez <= 5) //3
    double CRL; // Cloro residual livre em mg/L (0,5 <= CRL <= 2,0) //2
    double cor; // em unidades Hazen ( cor <= 15) //4
}water;
//water *p_water=NULL;

typedef struct{
    unsigned int n_habitantes; // %u
    char UF[3];
    water state_water;
}state;

state *p_UF;

//char STATE[27][3]; // FAZER MALLOC

state state_data;
water water_data;

void find_file();

int verify_file_existence();

void while_update_info();

void reopen_File();

void delete_data();

void update_data();

void read_file();

void print_data_and_problems();


int main(){
    int choice, choice2, excluded=1;
    p_UF = malloc(27 * sizeof(state));

    system("cls");
    printf("Ola, servidor(a)! Bem-vindo(a) ao WQRegister. Para comecar, selecione uma opcao: \n");
    printf("(1) Registrar um estado\n(2) Visualizar um registro\n(3) Alterar um registro\n(4) Deletar um registro\n(5) Encerrar o programa\n");
    scanf("%d", &choice);

    switch(choice){
        case 1: // COMPLETO
        printf("Voce escolheu registrar um estado. Insira o UF: "); // deve ser maiusculo
        scanf("%s%*c", state_data.UF);

        find_file();  

        if(verify_file_existence() == 1){ //se um arquivo com a UF desse estado ja existe (1a linha != 0)
            printf("Esse estado ja foi registrado. O que deseja fazer?\n");
            printf("(1) Alterar os dados\n(2) Visualizar dados\n(3) Deletar os dados\n");
            scanf("%d%*c", &choice2);
            
            switch(choice2){
                case 1: // Alteração OKAY
                update_data();
                break;


                case 2: //Visualização INCOMPLETO
                read_file();
                print_data_and_problems();
                break;


                case 3: // Deletar OKAY
                delete_data();
                break;


                default: //INCOMPLETO
                printf("Essa opcao nao existe! Tente novamente.\n");
                break;
            }

        }
        
        
        else{ //Registrando um novo estado (1a linha do arquivo = 0 )
            printf("Voce esta registrando os dados de um novo estado.\n");
            
            printf("Insira a quantidade de habitantes: ");
            scanf("%u%*c", &state_data.n_habitantes);
    
            printf("Insira o resultado do teste bacteriologico (0 para ausente e 1 para presente): ");
            scanf("%d%*c", &state_data.state_water.bact);
    
            printf("Insira o valor da turbidez em Unidade de Turbidez Nefelometrica: ");
            scanf("%lf%*c", &state_data.state_water.turbidez);

            printf("Insira a quantidade de Cloro Residual Livre em mg/L: ");
            scanf("%lf%*c", &state_data.state_water.CRL);

            printf("Insira o valor da cor em graus Hazen: ");
            scanf("%lf%*c", &state_data.state_water.cor);
    
            write_in_file();
            //fclose(file);
        }
        break;   

        
        case 2: // Visualização OKAY INCOMPLETO!!!!!
        printf("Voce escolheu visualizar um registro. Insira o UF: "); // deve ser maiusculo
        scanf("%s", state_data.UF);

        find_file();
        if(verify_file_existence() == -1){ // se não há registros
            printf("Ainda nao ha registros cadastrados no sistema. Gostaria de registrar?\n"); //INCOMPLETO!!!!!!!!!!
        }
        else{ // se há registros
            read_file(); //sscanf
            print_data_and_problems();
        }

        break;
            

        case 3: //Alteração OKAY INCOMPLETO!!!!!
        printf("Voce escolheu alterar dados. Insira o UF: ");
        scanf("%s", state_data.UF);

        find_file();
        if(verify_file_existence() == -1){
            printf("Ainda nao ha registros cadastrados no sistema. Gostaria de registrar?\n");
        }
        else update_data();
        break;


        case 4: // Deletar OKAY
        while(excluded==1)
        {
            if(excluded == 0) break;
            printf("Escolha um estado para deletar todos os dados: ");
            scanf("%s%*c", state_data.UF);
            find_file();
            
            if(verify_file_existence() == 1){
                printf("Os dados de %s estao sendo deletados.\n", state_data.UF);
                delete_data();
                excluded=0;
            }
            else{
                //fclose(file);
                //FILE *file;
                printf("Nao ha registro desse estado. Gostaria de escolher outro estado para deletar seus dados? Digite '0' para Nao, e '1' para Sim.\n");
                scanf("%d", &excluded);
            }
        } 
        break;

        case 5: // sair 
        return 0;
        break;

        default:
        printf("Essa opcao nao existe! Tente novamente.\n");
        break;
    }
    

    fclose(file); // Luiza approved this xD kkkkk
    return 0; //ADD funcao de agradecimento. SIIIIIIIIIM!
}

void find_file()
{
    if(strcmp(state_data.UF, "AC") == 0) file = fopen("AC.txt", "r+");
    else if(strcmp(state_data.UF, "AL") == 0) file = fopen("AL.txt", "r+");
    else if(strcmp(state_data.UF, "AP") == 0) file = fopen("AP.txt", "r+");
    else if(strcmp(state_data.UF, "AM") == 0) file = fopen("AM.txt", "r+");
    else if(strcmp(state_data.UF, "BA") == 0) file = fopen("BA.txt", "r+");
    else if(strcmp(state_data.UF, "CE") == 0) file = fopen("CE.txt", "r+");
    else if(strcmp(state_data.UF, "DF") == 0) file = fopen("DF.txt", "r+");
    else if(strcmp(state_data.UF, "ES") == 0) file = fopen("ES.txt", "r+");
    else if(strcmp(state_data.UF, "GO") == 0) file = fopen("GO.txt", "r+");
    else if(strcmp(state_data.UF, "MA") == 0) file = fopen("MA.txt", "r+");
    else if(strcmp(state_data.UF, "MG") == 0) file = fopen("MG.txt", "r+");
    else if(strcmp(state_data.UF, "MS") == 0) file = fopen("MS.txt", "r+");
    else if(strcmp(state_data.UF, "MT") == 0) file = fopen("MT.txt", "r+");
    else if(strcmp(state_data.UF, "PA") == 0) file = fopen("PA.txt", "r+");
    else if(strcmp(state_data.UF, "PB") == 0) file = fopen("PB.txt", "r+");
    else if(strcmp(state_data.UF, "PE") == 0) file = fopen("PE.txt", "r+");
    else if(strcmp(state_data.UF, "PI") == 0) file = fopen("PI.txt", "r+");
    else if(strcmp(state_data.UF, "PR") == 0) file = fopen("PR.txt", "r+");
    else if(strcmp(state_data.UF, "RJ") == 0) file = fopen("RJ.txt", "r+");
    else if(strcmp(state_data.UF, "RN") == 0) file = fopen("RN.txt", "r+");
    else if(strcmp(state_data.UF, "RS") == 0) file = fopen("RS.txt", "r+");
    else if(strcmp(state_data.UF, "RO") == 0) file = fopen("RO.txt", "r+");
    else if(strcmp(state_data.UF, "RR") == 0) file = fopen("RR.txt", "r+");
    else if(strcmp(state_data.UF, "SC") == 0) file = fopen("SC.txt", "r+");
    else if(strcmp(state_data.UF, "SE") == 0) file = fopen("SE.txt", "r+");
    else if(strcmp(state_data.UF, "SP") == 0) file = fopen("SP.txt", "r+");
    else if(strcmp(state_data.UF, "TO") == 0) file = fopen("TO.txt", "r+");
}

void while_update_info(){
    int num_altera;

    while(1)
    {
        printf("Escreva o indice que voce deseja alterar: ");
        scanf("%d", &num_altera);

        switch(num_altera)
        {
            case 1: //habit
                printf("Informe o novo valor do numero de habitantes: ");
                scanf("%u", &state_data.n_habitantes);
                break;
            case 2: //bact
                printf("Informe o novo valor do exame bacteriologico (0 ou 1): ");
                scanf("%d", &state_data.state_water.bact);
                break;
            case 3: //turbidez
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

void delete_data()
{
    sprintf(P,"0");
                
    rewind(file);
    fwrite(P, sizeof(char), sizeof(P), file);
}

void update_data()
{
    rewind(file); //volta para o começo do arquivo

    printf("Esses sao os dados atuais.\n");

    fscanf(file, "%u%*c", &state_data.n_habitantes);
    printf("[1] Quantidade de habitantes: %u\n", state_data.n_habitantes);

    fscanf(file, "%d%*c", &state_data.state_water.bact);
    printf("[2] Presenca de bacterias(0/1): %d\n", state_data.state_water.bact);

    fscanf(file, "%lf%*c", &state_data.state_water.turbidez);
    printf("[3] Turbidez: %.3lfuT\n", state_data.state_water.turbidez);

    fscanf(file, "%lf%*c", &state_data.state_water.CRL);
    printf("[4] Cloro residual livre: %.3lfmg/L\n", state_data.state_water.CRL);

    fscanf(file, "%lf%*c", &state_data.state_water.cor);
    printf("[5] Cor em unidades Hazen: %.3lfuH\n", state_data.state_water.cor);

    while_update_info(); //altera o dado escolhido
    
    write_in_file();

}

void write_in_file(){
    memset(P, '\0', strlen(P)); //Apaga 
    sprintf(P, "%u\n%d\n%.2lf\n%.2lf\n%.2lf", state_data.n_habitantes, state_data.state_water.bact, state_data.state_water.turbidez, state_data.state_water.CRL, state_data.state_water.cor);
    printf("%s\n",P);
    rewind(file);
    if (fwrite(P, sizeof(char), sizeof(P), file) != sizeof(P)) printf("when you try your best, but you dont succeed.");
    else printf("deu certo");
}

void reopen_File(){
    file = fopen(filename, "r+");
    fclose(file);       //fechamos o arquivo em r+, para colocar w+
}

void print_data_and_problems()
{
    
    printf("Numero de habitantes de %s: %u\n", state_data.UF, state_data.n_habitantes);

    printf("Presenca de bacterias(0/1): %d\n", state_data.state_water.bact);
 
    printf("Turbidez: %.3lfuT\n", state_data.state_water.turbidez);
 
    printf("Cloro residual livre: %.3lfmg/L\n", state_data.state_water.CRL);
 
    printf("Cor em unidades Hazen: %.3lfuH\n", state_data.state_water.cor);

    //printf("\nOs problemas "); // FALTA!!!

}

void read_file()
{
    rewind(file);
    fscanf(file, "%u%*c", &state_data.n_habitantes);
    fscanf(file, "%d%*c", &state_data.state_water.bact);
    fscanf(file, "%lf%*c", &state_data.state_water.turbidez);
    fscanf(file, "%lf%*c", &state_data.state_water.CRL);
    fscanf(file, "%lf%*c", &state_data.state_water.cor);
    
    printf("Li sim\n");
}

int verify_file_existence(){
    rewind(file);
    
    fscanf(file, "%u%*c", &state_data.n_habitantes); 

    if(state_data.n_habitantes==0)
    {
        printf("N tem registro desse estado\n");
        return -1; //arquivo nao foi registrado
    }
    else
    {    
        printf("O arquivo existe sim amore\n");
        return 1;
    }
}
