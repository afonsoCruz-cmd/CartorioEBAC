#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Função para abrir o arquivo
FILE* abrir_arquivo(const char *arquivo, const char *modo) {
    FILE *file = fopen(arquivo, modo);
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo);
    }
    return file;
}

// Função de retorno ao menu inicial, caso o usuário deseje
char menu(char c) {
    printf("\nDeseja voltar ao menu? (s/n): ");
    scanf(" %c", &c); // Lê o caractere e ignora espaços em branco e novas linhas
    while (getchar() != '\n'); // Limpa o buffer de entrada até encontrar uma nova linha
    return c;
}

// Função para adicionar dados ao arquivo
void adicionar_dado(const char *arquivo, const char *dado) {
    FILE *file = abrir_arquivo(arquivo, "a");
    fprintf(file, "%s,", dado);
    fclose(file);
}

// Função Registrar Usuario - O CPF e o ID
void registrar() {
    char arquivo[40], cpf[40], nome[40], sobrenome[40], cargo[40];
    printf("Você escolheu Registrar um nome\n");

    // Coletando CPF e Iniciando o arquivo
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);
    strcpy(arquivo, cpf); // Nome do arquivo é o CPF

    //Tenta abrir o file com o numero de CPF, para saber se ja existe
    //Caso ja exista este usuario cadastrado, retorna ao menu.
    FILE *file = fopen(cpf, "r");// aqui nao foi utlizado a função ABRIR_ARQUIVO, porque aqui o arquivo ser NULL não é necessario ser tratado como erro.
    if(file == NULL){

            //Chama a função adiconar dado com o CPF digitado acima
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

            printf("Cadastro concluído!\n");
    }else if(file!=NULL){
        printf("Usuario ja cadastrado");
        }
}

// Função Consultar Usuario - O CPF e o ID
void consultar() {
    char cpf[40];
    char conteudo[200];

    printf("Você escolheu Consultar um nome\n");
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
    FILE *file = abrir_arquivo(cpf, "r");

    // Lê e imprime as informações contidas no arquivo
    while (fgets(conteudo, 200, file) != NULL) {
        printf("\nEssas são as informações do usuário: %s\n", conteudo);
    }
    fclose(file);
}

// Função Deletar Usuario - O CPF e o ID
void deletar() {
    char cpf[40];

    printf("Você escolheu Deletar um nome\n");
    printf("Digite o CPF a ser removido: ");
    scanf("%s", cpf);

    if (remove(cpf) == 0) {
        printf("Usuário removido com sucesso!\n");
    } else {
        FILE *file = abrir_arquivo(cpf, "r");
    }
}

int main() {
    char c = 's'; // Inicializa c com 's' para entrar no loop
    int opcao = 0; // Inicializa a opção com 0
    setlocale(LC_ALL, "Portuguese"); // Linguagem para teclado em português

    do {
        printf("Cartório da EBAC \n\n");
        printf("Escolha a opção desejada no menu\n\n");
        // Menu
        printf("\t1  - Registrar Nome \n");
        printf("\t2  - Consultar Nome \n");
        printf("\t3  - Deletar Nome \n");
        printf("\t4  - Sair \n\n");

        // Lê a opção
        printf("Opção: ");
        scanf("%d", &opcao); // Lê a entrada do Usuário (1,2,3) para seguir ao CASE
        while (getchar() != '\n'); // Limpa o buffer de entrada após ler a opção

        switch (opcao) {
            case 1:
                registrar(); // Chama a função registrar
                c = menu(c); // Atribui a c, a opção de retorno ao menu (S,N) informado pelo usuário
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
                printf("Você escolheu sair, até logo!\n");
                return 0;
            default:
                printf("Essa opção não está disponível\n");
                c = menu(c);
                system("cls");
                break;
        }
    } while (c == 's');

    return 0; // Adiciona um retorno para a função main
}
