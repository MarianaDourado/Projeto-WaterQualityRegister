#include "WQR.h"


int main(){
    setlocale(LC_ALL,"Portuguese");

    int i, choice=0, choice2=0;

    //variável do tipo time_t para armazenar o tempo em seconds
    time_t seconds;
 

    //obtendo o tempo em seconds
    time(&seconds);

    //para converter de seconds para o tempo local
    //utilizamos a função localtime
    calend = localtime(&seconds);

    char *Weekdays[] = {"o domingo", "a segunda-feira", "a terca-feira", "a quarta-feira", "a quinta-feira", "a sexta-feira", "o sabado"};

    
    p_UF = malloc(27 * sizeof(state));
    
    system("cls"); 

    printf("Ola, servidor(a)! Bem-vindo(a) ao WQRegister. Otim%s para voce!\n", Weekdays[calend->tm_wday]);
    while(finish!=2)
    {
        printf("Selecione uma opcao:\n");
        printf("(1) Registrar um estado\n(2) Visualizar um registro\n(3) Alterar um registro\n(4) Deletar um registro\n(5) Encerrar o programa\n");

        while (choice < 1 || choice > 5){
           
            if(choice == -1) printf("Essa opcao nao existe! Tente novamente.\n");
            
            scanf("%d%*c", &choice);
            switch (choice)
            {
            case 1: // Registrar COMPLETO
                printf("Voce escolheu registrar um estado. Insira o UF: ");
                scanf("%s%*c", state_data.UF);

                while (find_file() == -1)
                {
                    printf("Essa sigla de estado nao existe. Insira o UF novamente: ");
                    scanf("%s%*c", state_data.UF);
                    find_file();
                }

                if (verify_data_existence() == 1)
                { //se um arquivo com a UF desse estado ja existe (1a linha != 0)
                    printf("Esse estado ja foi registrado. O que deseja fazer?\n");
                    printf("(1) Alterar os dados\n(2) Visualizar dados\n(3) Deletar os dados\n");

                    while (choice2 != 1 && choice2 != 2 && choice2 != 3)
                    {
                        if(choice2 == -1)
                            printf("Essa opcao nao existe. Tente novamente.\n");
                        scanf("%d%*c", &choice2);
                        switch (choice2)
                        {
                        case 1: // Alteração OKAY
                            update_data();
                            break;

                        case 2: //Visualização OKAY
                            read_file();
                            print_data_and_problems();
                            break;

                        case 3: // Deletar OKAY
                            delete_data();
                            break;

                        default: // OKAY
                            choice2 = -1;
                            break;
                        }
                    }
                    choice2=0;
                }

                else  register_data();
                break;

            case 2: // Visualização OKAY
                printf("Voce escolheu visualizar um registro. Insira o UF: ");
                scanf("%s", state_data.UF);
                    
                while (find_file() == -1)
                {
                    printf("Essa sigla de estado nao existe. Insira o UF novamente: ");
                    scanf("%s%*c", state_data.UF);
                    
                    find_file();
                }
                if (verify_data_existence() == -1) register_or_not(); // se não há registros
                else{ // se há registros
                
                    read_file(); //sscanf
                    print_data_and_problems();
                }

                break;

            case 3: //Alteração OKAY
                printf("Voce escolheu alterar dados. Insira o UF: ");
                scanf("%s", state_data.UF);

                while (find_file() == -1)
                {
                    printf("Essa sigla de estado nao existe. Insira o UF novamente: ");
                    scanf("%s%*c", state_data.UF);
                    
                    find_file();
                }
                if (verify_data_existence() == -1)
                    register_or_not();
                else
                    update_data();
                break;

            case 4: // Deletar OKAY 
                printf("Voce escolheu deletar dados. ");
                while_delete_data();
                break;

            case 5: // sair
                thanks_return();
                return 0;
                break;

            default:
                choice = -1;
                break;
            }
        }
        choice=0; //n apagar isso, se n na volta, ele buga 

        printf("\nO programa esta prestes a ser finalizado. Deseja registrar, consultar, alterar ou deletar outro dado?\n(1) Sim\t(2) Nao\n"); //gostei desse '/t'. Vamos mudar?
        scanf("%d", &finish);
    }
    fclose(file); // Luiza approved this xD kkkkk
    free(p_UF);
    thanks_return();
    return 0; 
}






// FUNCOES USADAS


int find_file()
{
    int existe=1;
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
    else  existe=-1;
    
    return existe;
}

int verify_data_existence(){
    rewind(file);
    
    fscanf(file, "%u%*c", &state_data.n_habitantes); 

    // não tem registro desse estado
    if(state_data.n_habitantes==0) return -1;

    // tem registro
    return 1;
}

void write_in_file()
{
    memset(P, '\0', strlen(P)); //Deleta dados
    sprintf(P, "%u\n%d\n%.2lf\n%.2lf\n%.2lf", state_data.n_habitantes,
                                              state_data.state_water.bact,
                                              state_data.state_water.turbidez,
                                              state_data.state_water.CRL,
                                              state_data.state_water.cor);
    rewind(file);
    if (fwrite(P, sizeof(char), sizeof(P), file) != sizeof(P)) printf("when you try your best, but you dont succeed.");
    
    // Para que as mudanças sejam atualizadas durante a execução do programa
    fclose(file);
    if(find_file() != 1) printf("Erro ao abrir arquivo.\n");
}

void register_data()
{
    printf("Voce esta registrando os dados de um novo estado.\n");

    printf("Insira a quantidade de habitantes: ");
    scanf("%u%*c", &state_data.n_habitantes);

    printf("Insira o resultado do teste bacteriologico (0 para ausente e 1 para presente): ");
    scanf("%d%*c", &state_data.state_water.bact);

    printf("Insira o valor da turbidez em Unidade de Turbidez Nefelometrica: ");
    scanf("%lf%*c", &state_data.state_water.turbidez);

    printf("Insira a quantidade de Cloro Residual Livre em mg/L: ");
    scanf("%lf%*c", &state_data.state_water.CRL);

    printf("Insira o valor da cor em unidades Hazen: ");
    scanf("%lf%*c", &state_data.state_water.cor);

    write_in_file();
}

void register_or_not()
{
    printf("Ainda nao ha registros cadastrados no sistema. Gostaria de registrar?\n(1) Sim, registrar.\n(2) Nao registrar e finalizar programa.\n");
    while (temp != 1 && temp != 2)
    {
        if (temp == -1)
            printf("Essa opcao nao existe. Tente novamente.\n");
        scanf("%d%*c", &temp);

        switch (temp)
        {
        case 1: //Sim, quero registrar
            register_data();
            fclose(file);
            break;

        case 2: //Nao, nao quero registrar e finalizar
            //thanks_return();
            fclose(file);
            break;

        default:
            temp = -1;
            //printf("Essa opcao nao existe! Tente novamente.\n");
            break;
        }
    }
    temp = 3; //NAO APAGAR
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


void while_update_info()
{
    int num_altera;

    while (1)
    {
        printf("Escreva o indice que voce deseja alterar: ");
        scanf("%d", &num_altera);

        switch (num_altera)
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
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
        printf("Deseja alterar alguma outra informacao?\n(1) Sim\n(2) Nao\n");

        scanf("%d", &num_altera); //reciclado
        if (num_altera == 2)
            break;
    }
}


void read_file()
{
    rewind(file);
    fscanf(file, "%u%*c", &state_data.n_habitantes);
    fscanf(file, "%d%*c", &state_data.state_water.bact);
    fscanf(file, "%lf%*c", &state_data.state_water.turbidez);
    fscanf(file, "%lf%*c", &state_data.state_water.CRL);
    fscanf(file, "%lf%*c", &state_data.state_water.cor);
}


void print_data_and_problems()
{
    time_t start_t, end_t;
    int i;

    printf("Imprimindo dados");
    time(&start_t);

    for (i = 0; i < 3; i++)
    {
        sleep(1);
        printf(".");
    }
    time(&end_t);
    printf("\n\n");

    printf("\nNumero de habitantes de %s: %u\n", state_data.UF, state_data.n_habitantes);
    printf("Presenca de bacterias(0/1): %d\n", state_data.state_water.bact);
    printf("Turbidez: %.3lfuT\n", state_data.state_water.turbidez);
    printf("Cloro residual livre: %.3lfmg/L\n", state_data.state_water.CRL);
    printf("Cor em unidades Hazen: %.3lfuH\n", state_data.state_water.cor);
/*
    int bact; // bacteriologico (0)/1 //1
    double turbidez; // em unidades de turbidez (turbidez <= 5) //3
    double CRL; // Cloro residual livre em mg/L (0,5 <= CRL <= 2,0) //2
    double cor; // em unidades Hazen ( cor <= 15) //4
*/
    int ans=0;
    printf("\nSituacao da agua: ");
    if(state_data.state_water.bact == 1 || state_data.state_water.turbidez > 5 || (state_data.state_water.CRL < 0.5 || state_data.state_water.CRL > 2.0) || state_data.state_water.cor > 15)
    {
        printf("Nao potavel\nGostaria de checar os problemas?\n\n(1) Sim\n(2) Nao\n");
        
        while(ans != 1 && ans != 2){
            if(ans == -1) printf("Essa opcao nao existe. Tente novamente.\n");
            scanf("%d", &ans);

            switch(ans){
            case 1: //sim, imprimir problemas
                if(state_data.state_water.bact==1) printf("Bacterias presentes na agua.\n");
                if(state_data.state_water.turbidez > 5) printf("A turbidez se encontra acima do valor adequado.\n");

                if(state_data.state_water.CRL < 0.5) printf("A quantidade de Cloro Residual Livre esta abaixo do adequado.\n");
                else if(state_data.state_water.CRL > 2.0) printf("A quantidade de Cloro Residual Livre esta acima do adequado.\n");

                if(state_data.state_water.cor > 15) printf("A agua tem coloracao acima do adequado.\n");

                printf("\nUma vez que os problemas foram citados, gostaria de acessar suas respectivas solucoes?\n(1) Sim\n(2) Nao\n");
                int ans2;
                while(ans2 != 1 && ans2 != 2){
                    if(ans2 == -1) printf("Essa opcao nao existe. Tente novamente.\n");
                    scanf("%d", &ans2);

                    switch(ans2){
                    case 1: //sim, acessar solucoes
                        if(state_data.state_water.bact==1) printf("\nRecomenda-se adicionar um agente desinfetante (Cloro) a agua, alem de averiguar os demais processos de tratamento.\n");
                        if(state_data.state_water.turbidez > 5){
                            printf("Checar eficiencia do processo de filtracao. Dentre os problemas estao:\n");
                            printf("A velocidade pode estar acima do adequado para o sistema em questao;\nO leite filtrante pode estar saturado;\nA quantidade do agente coagulante pode estar inadequada.\n");
                            
                        }
                        if(state_data.state_water.CRL < 0.5) printf("Adicionar o agente desinfetante (Cloro) ate que alcance, no minimo, 0,5mg/L.\n");
                        else if(state_data.state_water.CRL > 2.0) printf("Diminua a quantidade do agente desinfetante (Cloro) ate que alcance, no maximo, 2mg/L.\n");

                        if(state_data.state_water.cor > 15) printf("Identificar o motivo da presenca da cor a fim de adequar o processo de tratamento conforme as metodologias especificas.\n");

                        break;

                    case 2:
                        // Nao acessar solucoes
                        break;
        
                    default:
                        ans2 = -1;
                        break;
                    }
                }
                

                break;

            case 2:
                // Nao acessar problemas
                break;
        
            default:
                ans = -1;
                break;
            }
        }
        ans=0; //n apagar, se n buga
    }
    else printf("Potavel\nNao ha problemas para visualizar.\n");

    printf("\nPressione qualquer tecla para continuar.\n");
    //getch();
}


void delete_data()
{
    while (excluded == 1)
    {
        if (excluded == 2) break;

        printf("Tem certeza que deseja excluir todos os dados do arquivo?\n(1) Sim\n(2) Nao\n");
        int are_yousure = 1;
        scanf("%d", &are_yousure);

        if (are_yousure == 2)
        {
            printf("O arquivo selecionado nao tera seus dados apagados.\n");
            break;
        }
        else
        {
            printf("Os dados de %s estao sendo deletados.\n", state_data.UF);

            //deletando os dados
            sprintf(P, "0");
            rewind(file);
            fwrite(P, sizeof(char), sizeof(P), file);

            //fechando e reabrindo arquivo
            fclose(file);
            
            if (find_file() != 1) printf("Erro ao reabrir arquivo.\n");

            excluded = 0;
        }
    }
excluded = 1; // n apagar isso, se n na volta ele buga
}


void while_delete_data()
{
    int num_altera2=1;

    while(1)
    {
        printf("Informe a UF do estado: ");
        
        scanf("%[^\n]%*c", state_data.UF);
        
        if(find_file() == -1) printf("Esse estado nao existe!\n");
        else if(verify_data_existence() == 1) delete_data();
        else printf("Nao ha dados no arquivo do estado selecionado.\n");
        
        printf("Deseja deletar dado de algum outro estado?\n(1) Sim\n(2) Nao\n");

        scanf("%d", &num_altera2);
        if (num_altera2 == 2) break;
    }
    
}


void thanks_return(){
    time_t start_t2, end_t2;
    int i;
    char v[]={"\t\t\t\t\t\t\t\t\t"};
    
    printf("\nO programa esta sendo finalizado");

    time(&start_t2);

    for (i = 0; i < 3; i++)
    {
        sleep(1);
        printf(".");
    }
    time(&end_t2);
    system("cls");
    
    
    printf("\n%sREFERENCIAS\n*Ministerio da Saude. Portaria de Consolidacao numero 5/2018. Anexo XX. (Antiga Portaria numero 2914). (BRASIL, 2011).\n", v); //referencias (portaria)

    time(&start_t2);
    for (i = 0; i < 2; i++) sleep(1);
    time(&end_t2);
    system("cls");


    printf("\n%sDEVELOPERS\n*Luiza de Oliveira Costa (oliveiraluiza2012ufg@gmail.com)\n*Mariana Dourado Ximenes de Sena Santos (marianadourado@discente.ufg.br)\n", v); //developers
    time(&start_t2);
    for (i = 0; i < 4; i++) sleep(1);
    time(&end_t2);
    system("cls");

    
    
    printf("%sAGRADECIMENTOS\n*Prof. Dr. Ronaldo Martins da Costa\n*Dra. Silene Lima Dourado Ximenes Santos\n*Arnaldo de Sena Santos\n*Ismael Batuira da Costa\n*Joice Eliane de Oliveira Costa\n", v); //agradecimentos
    printf("*Tallya Barbosa de Jesus\n*Gabriel Freitas dos Reis\n*Wendel Marques de Jesus Souza\n");
    time(&start_t2);
    for (i = 0; i < 5; i++) sleep(1);
    time(&end_t2);
    system("cls");

    
    printf("\nObrigada por utilizar o WQRegister. Na versao 2.0 sera disponibilizado o acesso aos municipios.\n");
    
}
