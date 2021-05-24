#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
LINKS: 
    1- https://www.quora.com/How-can-I-create-a-login-system-in-C
    2- 
*/

/*
salvei como uma estrutura em um único arquivo
*/

FILE *login_file;


typedef struct
{
    int code;
    char username[15];
    char password[12];
} user_data;

user_data user;

int verify_login(char *nomelogin, char *passwordlogin)
{
    int login = 1;
    if (strcmp(user.username, nomelogin) == 0 && strcmp(user.password, passwordlogin) == 0) return 1;
    else return -1;
}

int verify_user_existence()
{
	char 
	login_file = fopen("%s.txt", "r+");
	
	if(login_file==NULL) return -1
	else return 1;

}



int main()
{
    char *login_matrix[2];


    int sign_in=2;

    printf("\n--------------LOGIN--------------\n"); //centralizar depois
    printf("Eh cadastrado?\t(1)SIM (2)NAO\n");
    scanf("%d%*c", &sign_in);
    
    if(sign_in==2){
            printf("\n--------------CADASTRO--------------\n");
            printf("Voce esta sendo cadastrado.\n");

            printf("Crie seu nome de usuario:(maximo 14 caracteres)\t");
            scanf("%[^\n]%*c", user.username);

            printf("Crie sua senha: (maximo 11 caracteres)\t");
            scanf("%[^\n]%*c", user.password);
    }

    printf("\n--------------LOGIN--------------\n");
    printf("Digite seu nome de usuario:\n");
    scanf("%[^\n]%*c", user.username);
    // SE O USERNAME N ESTA CADASTRADO? if()

    printf("Digite sua senha: \n");
    scanf("%[^\n]%*c", user.password);

    if(verify_login() == -1){
        printf("O nome ou a senha estao errados.\n");
    }
    
    free(p);
    return 0;
}
