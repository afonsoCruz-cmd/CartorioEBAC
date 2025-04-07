#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Fiz uma fun��o para adiconar a virgula quando escreve o arquivo
int virgula(arquivo){
    FILE *file;
    file= fopen(arquivo, "a");
    fprintf(file,",");
    fclose(file);
}
//Fun��o Registrar Usuario - O CPF e o ID
int registrar(){
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];


    printf("Voc� escolheu Registrar um nome\n");
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);

    strcpy(arquivo, cpf); //copia valor das strings

    FILE *file; //cria o arquivo
    file = fopen(arquivo, "w"); //cria o arquivo
    fprintf(file,cpf); // imprime o CPF no arquivo
    fclose(file); //fecha arquivo
    virgula(arquivo); // fun��o virgula, para imprimir a virgula no arquivo

    //file= fopen(arquivo, "a");
    //fprintf(file,",");
    //fclose(file);

    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);

    file=fopen(arquivo,"a"); //"a" porque esta Atualizando
    fprintf(file,nome);
    fclose(file);
    virgula(arquivo);

    printf("Digite o sobrenome a ser cadastrado: ");
    scanf("%s", sobrenome);

    file=fopen(arquivo,"a");
    fprintf(file,sobrenome);
    fclose(file);
    virgula(arquivo);

    printf("Digite o cargo a ser cadastrado: ");
    scanf("%s", cargo);

    file=fopen(arquivo,"a");
    fprintf(file,cargo);
    fclose(file);
}
//Fun��o Consultar Usuario - O CPF e o ID
int consultar(){
    char cpf[40];
    char conteudo[200];

    printf("Voc� escolheu Consultar um nome\n");
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen(cpf, "r");
    //Caso nao seja possivel localizar, retorna informa��o ao usuario.
    if(file == NULL){
        printf("\nNao foi possivel localizar\n");
    }
    //Tras as informa��es contidas na linha do arquivo, e imprime como um unico char.
    while(fgets(conteudo, 200, file) != NULL){
        printf("\n Essas s�o as informa��es do usuario: ");
        printf("%s", conteudo);
        printf("\n\n");
    }
}
//Fun��o Deletar Usuario - O CPF e o ID
int deletar(){
    char cpf[40];

    printf("Voc� escolheu Deletar um nome\n");
    printf("Digite o CPF a ser removido: ");
    scanf("%s", cpf);
    remove(cpf);

    FILE *file;
    file = fopen(cpf, "r");
    //Caso nao seja possivel localizar, retorna informa��o ao usuario.
    if(file == NULL){
        printf("\nNao foi possivel localizar\n");
    }
}
//Fun��o de retorno ao menu inicial, caso o usuario deseje.
char menu(char c) {
    printf("\nDeseja voltar ao menu? (s/n): ");
    scanf(" %c", &c); // L� o caractere e ignora espa�os em branco e novas linhas
    while (getchar() != '\n'); // Limpa o buffer de entrada at� encontrar uma nova linha
    return c;
}

int main() {
    char c = 's'; // Inicializa c com 's' para entrar no loop
    int opcao = 0; //Inicializa op��o com 0;
    setlocale(LC_ALL, "Portuguese"); //Linguagem para teclado em portugues

    do {
        printf("Cartorio da EBAC \n  \n");
        printf("Escolha a op��o desejada no menu\n\n");
        // Menu
        printf("\t1  - Registar Nome \n");
        printf("\t2  - Consultar Nome \n");
        printf("\t3  - Deletar Nome \n\n");
        // L� a op��o
        printf("Op��o: ");
        scanf("%d", &opcao); //Le a entreda do Usuario (1,2,3) para seguir ao CASE.
        while (getchar() != '\n'); // Limpa o buffer de entrada ap�s ler a op��o.

        switch (opcao) {
            case 1:
                registrar(); //Chama a  fun��o registar
                c = menu(c); //Atribui a C, a op��o de retorno ao menu (S,N) informado pelo usuario.
                system("cls"); //Limpar a Tela.
                break;
            case 2:
                consultar();
                c = menu(c);
                system("cls");
                break;
            case 3:
                deletar();
                c = menu(c);
                system("cls");
                break;
            default:
                printf("Essa op��o n�o est� dispon�vel\n");
                c = menu(c);
                system("cls");
                break;
        }
    } while (c == 's');

    return 0; // Adiciona um retorno para a fun��o main
}

