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
    if (file != NULL) {
        fprintf(file, "%s,", dado);
        fclose(file);
    }
}

// Fun��o Registrar Usuario
void registrar() {
    char arquivo[40], cpf[40], nome[40], sobrenome[40], cargo[40];
    printf("Voc� escolheu Registrar um nome\n");

    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);
    strncpy(arquivo, cpf, sizeof(arquivo) - 1);//Uso do strncpy para melhor seguran�a, nao vai haver estouro de buffer.
    arquivo[sizeof(arquivo) - 1] = '\0'; //Tratativa do strncpy, garantindo que a string vai caber no array.

    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        adicionar_dado(arquivo, cpf);

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
    } else {
        printf("Usu�rio j� cadastrado\n");
        fclose(file);
    }
}

// Fun��o Consultar Usuario
void consultar() {
    char cpf[40], conteudo[200];
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
    FILE *file = abrir_arquivo(cpf, "r");

    if (file != NULL) {
        while (fgets(conteudo, 200, file) != NULL) {
            printf("\nEssas s�o as informa��es do usu�rio: %s\n", conteudo);
        }
        fclose(file);
    }else{
        printf("Usu�rio n�o encontrado");
        }
}

// Fun��o Deletar Usuario
void deletar() {
    char cpf[40];
    printf("Digite o CPF a ser removido: ");
    scanf("%s", cpf);

    FILE *file = abrir_arquivo(cpf, "r");
    if (file == NULL) {
        printf("Usu�rio n�o encontrado.\n");
        return;
    }

    fclose(file);

    if (remove(cpf) == 0) {
        printf("Usu�rio removido com sucesso!\n");
    } else {
        printf("Erro ao remover o usu�rio.\n");
    }
}

int main() {
    char c = 's';
    int opcao = 0;
    setlocale(LC_ALL, "Portuguese");

    do {
        printf("Cart�rio da EBAC\n\n");
        printf("Escolha a op��o desejada no menu\n\n");
        printf("\t1  - Registrar Nome\n");
        printf("\t2  - Consultar Nome\n");
        printf("\t3  - Deletar Nome\n");
        printf("\t4  - Sair\n\n");

        printf("Op��o: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1: registrar(); c = menu(c); system("cls"); break;
            case 2: consultar(); c = menu(c); system("cls"); break;
            case 3: deletar(); c = menu(c); system("cls"); break;
            case 4: printf("Voc� escolheu sair, at� logo!\n"); return 0;
            default: printf("Essa op��o n�o est� dispon�vel\n"); c = menu(c); system("cls"); break;
        }
    } while (c == 's');

    return 0;
}
