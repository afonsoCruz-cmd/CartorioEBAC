#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Fun��o para abrir o arquivo
FILE* abrir_arquivo(const char *arquivo, const char *modo) {
    FILE *file = fopen(arquivo, modo);
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo);
    }
    return file;
}

// Fun��o de retorno ao menu inicial, caso o usu�rio deseje
char menu(char c) {
    printf("\nDeseja voltar ao menu? (s/n): ");
    scanf(" %c", &c); // L� o caractere e ignora espa�os em branco e novas linhas
    while (getchar() != '\n'); // Limpa o buffer de entrada at� encontrar uma nova linha
    return c;
}

// Fun��o para adicionar dados ao arquivo
void adicionar_dado(const char *arquivo, const char *dado) {
    FILE *file = abrir_arquivo(arquivo, "a");
    fprintf(file, "%s,", dado);
    fclose(file);
}

// Fun��o Registrar Usuario - O CPF e o ID
void registrar() {
    char arquivo[40], cpf[40], nome[40], sobrenome[40], cargo[40];
    printf("Voc� escolheu Registrar um nome\n");

    // Coletando CPF e Iniciando o arquivo
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);
    strcpy(arquivo, cpf); // Nome do arquivo � o CPF

    //Tenta abrir o file com o numero de CPF, para saber se ja existe
    //Caso ja exista este usuario cadastrado, retorna ao menu.
    FILE *file = fopen(cpf, "r");// aqui nao foi utlizado a fun��o ABRIR_ARQUIVO, porque aqui o arquivo ser NULL n�o � necessario ser tratado como erro.
    if(file == NULL){

            //Chama a fun��o adiconar dado com o CPF digitado acima
            adicionar_dado(arquivo, cpf);//Adicionar CPF

            // Coletando e adicionando o nome, sobrenome e cargo
            printf("Digite o nome a ser cadastrado: ");
            scanf("%s", nome);
            adicionar_dado(arquivo, nome);

            printf("Digite o sobrenome a ser cadastrado: ");
            scanf("%s", sobrenome);
            adicionar_dado(arquivo, sobrenome);

            printf("Digite o cargo a ser cadastrado: ");
            scanf("%s", cargo);
            adicionar_dado(arquivo, cargo);

            printf("Cadastro conclu�do!\n");
    }else if(file!=NULL){
        printf("Usuario ja cadastrado");
        }
}

// Fun��o Consultar Usuario - O CPF e o ID
void consultar() {
    char cpf[40];
    char conteudo[200];

    printf("Voc� escolheu Consultar um nome\n");
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
    FILE *file = abrir_arquivo(cpf, "r");

    // L� e imprime as informa��es contidas no arquivo
    while (fgets(conteudo, 200, file) != NULL) {
        printf("\nEssas s�o as informa��es do usu�rio: %s\n", conteudo);
    }
    fclose(file);
}

// Fun��o Deletar Usuario - O CPF e o ID
void deletar() {
    char cpf[40];

    printf("Voc� escolheu Deletar um nome\n");
    printf("Digite o CPF a ser removido: ");
    scanf("%s", cpf);

    if (remove(cpf) == 0) {
        printf("Usu�rio removido com sucesso!\n");
    } else {
        FILE *file = abrir_arquivo(cpf, "r");
    }
}

int main() {
    char c = 's'; // Inicializa c com 's' para entrar no loop
    int opcao = 0; // Inicializa a op��o com 0
    setlocale(LC_ALL, "Portuguese"); // Linguagem para teclado em portugu�s

    do {
        printf("Cart�rio da EBAC \n\n");
        printf("Escolha a op��o desejada no menu\n\n");
        // Menu
        printf("\t1  - Registrar Nome \n");
        printf("\t2  - Consultar Nome \n");
        printf("\t3  - Deletar Nome \n");
        printf("\t4  - Sair \n\n");

        // L� a op��o
        printf("Op��o: ");
        scanf("%d", &opcao); // L� a entrada do Usu�rio (1,2,3) para seguir ao CASE
        while (getchar() != '\n'); // Limpa o buffer de entrada ap�s ler a op��o

        switch (opcao) {
            case 1:
                registrar(); // Chama a fun��o registrar
                c = menu(c); // Atribui a c, a op��o de retorno ao menu (S,N) informado pelo usu�rio
                system("cls"); // Limpa a Tela (funciona no Windows)
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
            case 4:
                printf("Voc� escolheu sair, at� logo!\n");
                return 0;
            default:
                printf("Essa op��o n�o est� dispon�vel\n");
                c = menu(c);
                system("cls");
                break;
        }
    } while (c == 's');

    return 0; // Adiciona um retorno para a fun��o main
}
