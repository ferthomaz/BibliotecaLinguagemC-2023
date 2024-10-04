#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//USUARIO
typedef struct{
    int Id;
    char Nome[50];
    char Endereco[70];
    char Telefone[15];
    struct USUARIO *prox;
}USUARIO;

typedef struct{
    USUARIO *inicio;
}LISTA;

LISTA *criaLista(){
    LISTA *listaUsuario = (LISTA *)malloc(sizeof(LISTA));
    listaUsuario->inicio = NULL;
    return listaUsuario;
};

//AUTOR
typedef struct AUTOR{
    struct AUTOR *ant;
    char Nome[50];
    char Instituicao[50];
    struct AUTOR *prox;
}AUTOR;

typedef struct
{
    AUTOR *inicio;
    AUTOR *fim;
}LISTAautor;

LISTAautor *criaListaAutor(){
    LISTAautor *listaAutores = (LISTAautor *)malloc(sizeof(LISTAautor));
    listaAutores->inicio = NULL;
    return listaAutores;
}

//LIVRO
typedef struct{
    int Identificador;
    char Titulo[100];
    LISTAautor Autores;
    int Ano;
    int Edicao;
    char Editora[50];
    struct LIVRO *prox;
}LIVRO;

typedef struct LivroNode{
    struct LivroNode *ant;
    LIVRO dados;
    struct LivroNode *prox;
}LivroNode;

//RESERVA
typedef struct{
    char dataInicio[11];  // Alterado para armazenar a data no formato xx/xx/xxxx
    char dataFim[11];     // Alterado para armazenar a data no formato xx/xx/xxxx
    int idUser;
    int idLivro;
    struct RESERVA *prox;
}RESERVA;

typedef struct{
    RESERVA *inicio;
}LISTAreserva;

LISTAreserva *criaListaReserva(){
    LISTAreserva *listaUsuario = (LISTAreserva *)malloc(sizeof(LISTAreserva));
    listaUsuario->inicio = NULL;
    return listaUsuario;
};

void incluiUsuario(LISTA *listaUsuario);
void alteraUsuario(LISTA *listaUsuario, const char *nomeAlterar);
void removeUsuario(LISTA *listaUsuario, const char *nomeRemover);
void listarUsuarios(LISTA *listaUsuario);
AUTOR *criarAutor(char nome[], char instituicao[]);
void incluirAutor(LISTAautor *autores, char nome[], char instituicao[]);
void exibirAutores(LISTAautor autores);
void liberarAutores(LISTAautor *autores);
LIVRO *criarLivro(int identificador, char titulo[], LISTAautor autores, int ano, int edicao, char editora[]);
void incluirLivro(LivroNode **listaLivro, int *numLivros);
void exibirLivros(LivroNode *listaLivro);
void removerLivro(LivroNode **listaLivro, int *numLivros, int identificador);
void alterarLivro(LivroNode *listaLivro, int identificador, LISTAautor *listaAutores);
void liberarLivros(LIVRO **listaLivro);
void incluiReserva(LISTAreserva *listaReservas);
void alteraReserva(LISTAreserva *listaReservas, int idAlterar);
void removeReserva(LISTAreserva *listaReservas, int userRemover);
void listarReserva(LISTAreserva *listaReservas);
void listarUserReserva(LISTA *listaUsuarios, LISTAreserva *listaReserva);

int main()
{
    LISTA *listaUsuario = criaLista();
    LISTAautor *listaAutores = criaListaAutor();
    LISTAreserva *listaReservas = criaListaReserva();
    LivroNode *listaLivros = NULL;
    int numLivros = 0;
    int opcao;

    do{
        printf("----MENU PRINCIPAL----\n\n");
        printf("Escolha uma opcao: \n");
        printf("1 - Usuario\n");
        printf("2 - Livro\n");
        printf("3 - Reserva\n");
        printf("4 - Relatorios\n");
        printf("0 - Sair\n\n");

        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            printf("\nEscolha uma opcao:\n");
            int op1;
            printf("1 - Adicionar usuario\n");
            printf("2 - Alterar usuario\n");
            printf("3 - Excluir usuario\n");
            printf("4 - Listar usuarios\n");
            printf("0 - Nao desejo fazer modificacoes.\n\n");
            scanf("%d", &op1);

            switch(op1){
            case 1:
                incluiUsuario(listaUsuario);
                break;
            case 2:
                if(listaUsuario->inicio == NULL){
                    printf("\nNao existem usuarios para serem alterados.\n");
                }
                else{
                    char nomeAlterar[50];
                    printf("\nDigite o nome do usuario que deseja alterar: ");
                    getchar(); // Consumir o caractere de nova linha pendente
                    fgets(nomeAlterar, sizeof(nomeAlterar), stdin);
                    alteraUsuario(listaUsuario, nomeAlterar);
                }
                break;
            case 3:
                if(listaUsuario->inicio == NULL){
                    printf("\nNao existem usuarios para serem removidos!\n\n");
                } else {
                    char nomeRemover[50];
                    printf("\nDigite o nome do usuario a ser removido: ");
                    getchar(); // Consumir o caractere de nova linha pendente
                    fgets(nomeRemover, sizeof(nomeRemover), stdin);
                    removeUsuario(listaUsuario, nomeRemover);
                }
                break;
            case 4:
                listarUsuarios(listaUsuario);
                break;
            case 0:
                printf("Ok.\n");
                break;
            }
            break;
        case 2:
            printf("\nEscolha uma opcao: \n");
            int op2;
            printf("1 - Adicionar livro\n");
            printf("2 - Alterar livro\n");
            printf("3 - Remover livro\n");
            printf("4 - Listar livros\n");
            printf("0 - Sair\n\n");
            scanf("%d", &op2);
            switch(op2){
            case 1:
                incluirLivro(&listaLivros, &numLivros);
                break;
                case 2:
                    if (listaLivros == NULL) {
                    printf("\nNao existem livros para serem alterados.\n");
                } else {
                    int identificadorAlterar;
                    printf("\nDigite o identificador do livro que deseja alterar: ");
                    scanf("%d", &identificadorAlterar);
                    alterarLivro(listaLivros, identificadorAlterar, listaAutores);
                }
                break;
            case 3:
                if (listaLivros == NULL) {
                printf("\nNao existem livros para serem removidos!\n\n");
                } else {
                    int identificadorRemover;
                    printf("\nDigite o identificador do livro a ser removido: ");
                    scanf("%d", &identificadorRemover);
                    removerLivro(&listaLivros, &numLivros, identificadorRemover);
                }
                break;
            case 4:
                exibirLivros(listaLivros);
                break;
            case 0:
                liberarLivros(&listaLivros);
            default:
                printf("Opcao invalida.\n");
            }
            break;
        case 3:
            printf("Escolha uma opcao: \n");
            int op3;
            printf("1 - Reservar um livro\n");
            printf("2 - Alterar reserva\n");
            printf("3 - Remover reserva\n");
            printf("4 - Listar reservas.\n");
            printf("0 - Voltar ao menu principal\n\n");
            scanf("%d", &op3);
            switch(op3){
            case 1:
                incluiReserva(listaReservas);
                break;
            case 2:
                if(listaReservas->inicio == NULL){
                    printf("\nNao existem reservas para serem alteradas.\n");
                }
                else{
                    int idAlterar;
                    printf("\nDigite o identificador do usuario que deseja alterar a reserva: ");
                    scanf("%d", &idAlterar);
                    alteraReserva(listaReservas, idAlterar);
                }
                break;
            case 3:
                if(listaReservas->inicio == NULL){
                    printf("\nNao existem reservas para serem removidas.\n");
                }
                else{
                    int idRemover;
                    printf("\nDigite o identificador do usuario que deseja remover a reserva: ");
                    scanf("%d", &idRemover);
                    removeReserva(listaReservas, idRemover);
                }
                break;
            case 4:
                if(listaReservas->inicio == NULL){
                    printf("\nNao existem reservas para serem listadas.\n");
                }
                else{
                    listarReserva(listaReservas);
                }
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida.\n");
            }
            break;
        case 4:
            printf("Escolha um tipo de relatorio: \n");
            int op4;
            printf("1 - Relatorio de livros\n");
            printf("2 - Relatorio de usuarios\n");
            printf("3 - Relatorio de usuarios com reserva\n");
            printf("0 - Voltar ao menu principal\n");
            scanf("%d", &op4);
            switch(op4){
            case 1:
                exibirLivros(listaLivros);
                break;
            case 2:
                listarUsuarios(listaUsuario);
                break;
            case 3:
                listarUserReserva(listaUsuario, listaReservas);
                break;
            case 0:
                printf("OK!\n");
                break;
            default:
                printf("Opcao invalida.\n");
            }

        case 5:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    }while(opcao != 0);
}

//Implementação das funções relacionadas a usuarios
void incluiUsuario(LISTA *listaUsuario){
    USUARIO *novoUser = calloc(1, sizeof(USUARIO));

    printf("\nDigite o identificador do usuario: ");
    scanf("%d", &novoUser->Id);
    getchar();
    printf("Digite o nome do usuario: ");
    fgets(novoUser->Nome, sizeof(novoUser->Nome), stdin);
    printf("Digite o endereco do usuario: ");
    fgets(novoUser->Endereco, sizeof(novoUser->Endereco), stdin);
    printf("Digite o telefone do usuario: ");
    fgets(novoUser->Telefone, sizeof(novoUser->Telefone), stdin);

    if(listaUsuario->inicio == NULL){
        listaUsuario->inicio = novoUser;
    } else {
        USUARIO *ultimo = listaUsuario->inicio;
        while(ultimo->prox != NULL){
            ultimo = ultimo->prox;
        }
        ultimo->prox = novoUser;
    }
    printf("\nUsuario adicionado com sucesso!\n\n");
}


void alteraUsuario(LISTA *listaUsuario, const char *nomeAlterar) {
    USUARIO *atual = listaUsuario->inicio;
    USUARIO *anterior = NULL;

    int resultComp;

    while (atual != NULL) {
        // Comparar o nome do usuário com o nome fornecido
        resultComp = strcmp(atual->Nome, nomeAlterar);

        if (resultComp == 0) {
            int opcao;
            printf("\nUsuario selecionado:\n");
            printf("Nome: %s", atual->Nome);
            printf("Endereco: %s", atual->Endereco);
            printf("Telefone: %s", atual->Telefone);
            do{
                printf("\nQual campo deseja alterar?:\n");
                printf("1 - Nome\n");
                printf("2 - Endereco\n");
                printf("3 - Telefone\n");
                printf("0 - Nao desejo alterar nenhum campo.\n\n");

                scanf("%d", &opcao);

                switch(opcao){
                case 1:
                    printf("\nInsira o novo nome: ");
                    getchar(); // Consumir o caractere de nova linha pendente
                    fgets(atual->Nome, sizeof(atual->Nome), stdin);
                    printf("Nome alterado com sucesso.\n");
                    break;
                case 2:
                    printf("\nInsira o novo endereco: ");
                    getchar(); // Consumir o caractere de nova linha pendente
                    fgets(atual->Endereco, sizeof(atual->Endereco), stdin);
                    printf("Endereco alterado com sucesso.\n");
                    break;
                case 3:
                    printf("\nInsira o novo telefone: ");
                    getchar(); // Consumir o caractere de nova linha pendente
                    fgets(atual->Telefone, sizeof(atual->Telefone), stdin);
                    printf("Telefone alterado com sucesso.\n");
                    break;
                case 0:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
                }
                printf("Deseja alterar outro campo? (0 - nao. 1 - sim)\n");
                scanf("%d", &opcao);
        }while(opcao != 0);
        return;
    }

        // Avançar para o próximo usuário na lista
        anterior = atual;
        atual = atual->prox;
    }

    printf("Usuario com o nome %s nao encontrado.\n\n", nomeAlterar);
}


void removeUsuario(LISTA *listaUsuario, const char *nomeRemover) {
    USUARIO *atual = listaUsuario->inicio;
    USUARIO *anterior = NULL;

    int resultComp;

    while (atual != NULL) {
        // Comparar o nome do usuário com o nome fornecido
        resultComp = strcmp(atual->Nome, nomeRemover);

        if (resultComp == 0) {
            // Remover o usuário da lista
            if (anterior == NULL) {
                // Se o usuário a ser removido é o primeiro da lista
                listaUsuario->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("Usuario removido com sucesso!\n\n");
            return;
        }

        // Avançar para o próximo usuário na lista
        anterior = atual;
        atual = atual->prox;
    }

    printf("Usuario com o nome %s nao encontrado.\n\n", nomeRemover);
}


void listarUsuarios(LISTA *listaUsuario) {
    if (listaUsuario->inicio == NULL) {
        printf("A lista de usuários está vazia.\n\n");
        return;
    }

    USUARIO *atual = listaUsuario->inicio;

    printf("\nLista de Todos os Usuarios:\n");
    while (atual != NULL) {
        printf("Identificador: %d\n", atual->Id);
        printf("Nome: %s", atual->Nome);
        printf("Endereco: %s", atual->Endereco);
        printf("Telefone: %s", atual->Telefone);
        printf("\n\n");

        atual = atual->prox;
    }
}


//Implementação das funções relacionadas a autores
AUTOR *criarAutor(char nome[], char instituicao[]) {
    AUTOR *novoAutor = calloc(1, sizeof(AUTOR));
    if (novoAutor == NULL) {
        printf("Erro ao alocar memória para o autor.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novoAutor->Nome, nome);
    strcpy(novoAutor->Instituicao, instituicao);
    novoAutor->ant = NULL;
    novoAutor->prox = NULL;

    return novoAutor;
}

void incluirAutor(LISTAautor *autores, char nome[], char instituicao[]) {
    AUTOR *novoAutor = criarAutor(nome, instituicao);

    if (autores->inicio == NULL) {
        autores->inicio = novoAutor;
        autores->fim = novoAutor;
    } else {
        autores->fim->prox = novoAutor;
        novoAutor->ant = autores->fim;
        autores->fim = novoAutor;
    }
}

void exibirAutores(LISTAautor autores) {
    AUTOR *atual = autores.inicio;

    while (atual != NULL) {
        printf("Autor: %s / Instituicao do autor: (%s)\n", atual->Nome, atual->Instituicao);
        atual = atual->prox;
    }
}

void liberarAutores(LISTAautor *autores) {
    AUTOR *atual = autores->inicio;
    AUTOR *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    autores->inicio = NULL;
    autores->fim = NULL;
}

// Implementação das funções relacionadas a livros (lista duplamente encadeada)

LIVRO *criarLivro(int identificador, char titulo[], LISTAautor autores, int ano, int edicao, char editora[]) {
    LivroNode *novoLivro = calloc(1, sizeof(LivroNode));
    if (novoLivro == NULL) {
        printf("Erro ao alocar memória para o livro.\n");
        exit(EXIT_FAILURE);
    }

    novoLivro->dados.Identificador = identificador;
    strcpy(novoLivro->dados.Titulo, titulo);
    novoLivro->dados.Autores = autores;
    novoLivro->dados.Ano = ano;
    novoLivro->dados.Edicao = edicao;
    strcpy(novoLivro->dados.Editora, editora);
    novoLivro->prox = NULL;
    novoLivro->ant = NULL;

    return novoLivro;
}

void incluirLivro(LivroNode **listaLivro, int *numLivros) {
    if (*numLivros < 20) {
        LivroNode *novoLivro;
        LISTAautor autores;

        // Inicializa a lista de autores
        autores.inicio = NULL;
        autores.fim = NULL;

        int identificador;
        char titulo[50];
        int numAutores;

        printf("Identificador: ");
        scanf("%d", &identificador);

        printf("Titulo: ");
        scanf(" %[^\n]", titulo);

        printf("Numero de autores: ");
        scanf("%d", &numAutores);

        for (int i = 0; i < numAutores; i++) {
            char nome[50];
            char instituicao[50];

            printf("Nome do autor %d: ", i + 1);
            scanf(" %[^\n]", nome);

            printf("Instituicao do autor %d: ", i + 1);
            scanf(" %[^\n]", instituicao);

            incluirAutor(&autores, nome, instituicao);
        }

        int ano, edicao;
        char editora[50];

        printf("Ano: ");
        scanf("%d", &ano);

        printf("Edicao: ");
        scanf("%d", &edicao);

        printf("Editora: ");
        scanf(" %[^\n]", editora);

        novoLivro = criarLivro(identificador, titulo, autores, ano, edicao, editora);

        // Inserindo no final da lista
            if (*listaLivro == NULL) {
                *listaLivro = novoLivro;
            } else {
                LivroNode *ultimo = *listaLivro;
                while (ultimo->prox != NULL) {
                    ultimo = ultimo->prox;
                }
                novoLivro->ant = ultimo;
                ultimo->prox = novoLivro;
            }

        (*numLivros)++;

        printf("\nLivro cadastrado com sucesso!\n\n");
    } else {
        printf("Limite de livros atingido. Nao e possivel cadastrar mais livros.\n\n");
    }
}

void exibirLivros(LivroNode *listaLivro) {
    LivroNode *atual = listaLivro;

    while (atual != NULL) {
        printf("\nIdentificador: %d\n", atual->dados.Identificador);
        printf("Titulo: %s\n", atual->dados.Titulo);
        exibirAutores(atual->dados.Autores);
        printf("Ano: %d\n", atual->dados.Ano);
        printf("Edicao: %d\n", atual->dados.Edicao);
        printf("Editora: %s\n", atual->dados.Editora);
        printf("\n");

        atual = atual->prox;
    }
}

void removerLivro(LivroNode **listaLivro, int *numLivros, int identificador) {
    LivroNode *atual = *listaLivro;
    LivroNode *anterior = NULL;

    while (atual != NULL) {
        if (atual->dados.Identificador == identificador) {
            // Remover o livro da lista
            if (anterior == NULL) {
                // Se o livro a ser removido é o primeiro da lista
                *listaLivro = atual->prox;
            } else {
                anterior->prox = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = anterior;
                }
            }

            liberarAutores(&(atual->dados.Autores));
            free(atual);
            (*numLivros)--;
            printf("Livro removido com sucesso!\n\n");
            return;
        }

        // Avançar para o próximo livro na lista
        anterior = atual;
        atual = atual->prox;
    }

    printf("Livro com identificador %d nao encontrado.\n\n", identificador);
}

void alterarLivro(LivroNode *listaLivro, int identificador, LISTAautor *listaAutores) {
    LivroNode *atual = listaLivro;

    while (atual != NULL) {
        if (atual->dados.Identificador == identificador) {
            int opcao;
            int op1;
            printf("\nLivro selecionado:\n");
            printf("Identificador: %d\n", atual->dados.Identificador);
            printf("Titulo: %s\n", atual->dados.Titulo);
            exibirAutores(atual->dados.Autores);
            printf("Ano: %d\n", atual->dados.Ano);
            printf("Edicao: %d\n", atual->dados.Edicao);
            printf("Editora: %s\n", atual->dados.Editora);
            printf("\n");

            do {
                printf("\nQual campo deseja alterar?:\n");
                printf("1 - Titulo\n");
                printf("2 - Ano\n");
                printf("3 - Edicao\n");
                printf("4 - Editora\n");
                printf("0 - Nao desejo alterar nenhum campo.\n\n");

                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("\nInsira o novo titulo: ");
                        getchar();
                        fgets(atual->dados.Titulo, sizeof(atual->dados.Titulo), stdin);
                        printf("Titulo alterado com sucesso.\n");
                        break;
                    case 2:
                        printf("\nInsira o novo ano: ");
                        scanf("%d", &atual->dados.Ano);
                        printf("Ano alterado com sucesso.\n");
                        break;
                    case 3:
                        printf("\nInsira a nova edicao: ");
                        scanf("%d", &atual->dados.Edicao);
                        printf("Edicao alterada com sucesso.\n");
                        break;
                    case 4:
                        printf("\nInsira a nova editora: ");
                        getchar();
                        fgets(atual->dados.Editora, sizeof(atual->dados.Editora), stdin);
                        printf("Editora alterada com sucesso.\n");
                        break;
                    case 0:
                        printf("Saindo...\n\n");
                        break;
                    default:
                        printf("Opcao invalida.\n");
                }
                printf("Deseja alterar mais algum campo? (0 - nao, 1 - sim)\n");
                scanf("%d", &opcao);
            } while (opcao != 0);

            return;
        }

        // Avançar para o próximo livro na lista
        atual = atual->prox;
    }

    printf("Livro com identificador %d nao encontrado.\n\n", identificador);
}


void liberarLivros(LIVRO **listaLivro) {
    LivroNode *atual = *listaLivro;
    LivroNode *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        liberarAutores(&(atual->dados.Autores));
        free(atual);
        atual = proximo;
    }

    *listaLivro = NULL;
}

//Implementação das funções relacionadas a reservas
void incluiReserva(LISTAreserva *listaReservas){
    RESERVA *novaReserva = calloc(1, sizeof(RESERVA));

    printf("\nDigite a data de inicio da reserva (xx/xx/xxxx): \n");
    scanf("%10s", novaReserva->dataInicio);
    printf("Digite a data de fim da reserva (xx/xx/xxxx): \n");
    scanf("%10s", novaReserva->dataFim);
    printf("Digite o identificador do usuario que deseja fazer a reserva: \n");
    scanf("%d", &novaReserva->idUser);
    printf("Digite o identificador do livro que o usuario deseja reservar: \n");
    scanf("%d", &novaReserva->idLivro);

    novaReserva->prox = listaReservas->inicio;
    listaReservas->inicio = novaReserva;

    printf("\Reserva realizada com sucesso!\n\n");
}

void alteraReserva(LISTAreserva *listaReservas, int idAlterar) {
    RESERVA *atual = listaReservas->inicio;

    while (atual != NULL) {
        if (atual->idUser == idAlterar) {
            int opcao;
            printf("\Reserva selecionada:\n");
            printf("Identificador do usuario: %d\n", atual->idUser);
            printf("Identificador do livro: %d\n", atual->idLivro);
            printf("Data de inicio da reserva: %s\n", atual->dataInicio);
            printf("Data de termino da reserva: %s\n", atual->dataFim);
            do{
                printf("\nQual campo deseja alterar?:\n");
                printf("1 - Id do usuario\n");
                printf("2 - Id do livro:\n");
                printf("3 - Data de inicio:\n");
                printf("4 - Data de Termino:\n");
                printf("0 - Nao desejo alterar nenhum campo.\n\n");

                scanf("%d", &opcao);

                switch(opcao){
                    case 1:
                        printf("Insira o novo identificador do usuario:\n");
                        scanf("%d", &atual->idUser);
                        printf("Identificador alterado com sucesso.\n");
                        break;
                    case 2:
                        printf("Insira o novo identificador do livro:\n");
                        scanf("%d", &atual->idLivro);
                        printf("Identificador alterado com sucesso.\n");
                        break;
                    case 3:
                        printf("Insira a nova data de inicio (xx/xx/xxxx):\n");
                        scanf("%10s", atual->dataInicio);
                        printf("Data de inicio alterada com sucesso.\n");
                        break;
                    case 4:
                        printf("Insira a nova data de termino (xx/xx/xxxx):\n");
                        scanf("%10s", atual->dataFim);
                        printf("Data de termino alterada com sucesso.\n");
                        break;
                    case 0:
                        printf("Saindo...\n");
                        break;
                    default:
                        printf("Opção invalida.\n");
                }
                printf("Deseja alterar outro campo? (0 - nao, 1 - sim)\n");
                scanf("%d", &opcao);
            } while (opcao != 0);

            return;
        }
        atual = atual->prox;
    }
    printf("Usuario com o id %d nao encontrado.\n\n", idAlterar);
}

void removeReserva(LISTAreserva *listaReservas, int userRemover) {
    RESERVA *atual = listaReservas->inicio;
    RESERVA *anterior = NULL;

    while (atual != NULL) {
        if (atual->idUser == userRemover) {
            // Remover o usuário da lista
            if (anterior == NULL) {
                // Se o usuário a ser removido é o primeiro da lista
                listaReservas->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("Reserva removida com sucesso!\n\n");
            return;
        }

        // Avançar para o próximo usuário na lista
        anterior = atual;
        atual = atual->prox;
    }

    printf("Reserva do usuario com o identificador %d nao encontrado.\n\n", userRemover);
}

void listarUserReserva(LISTA *listaUsuarios, LISTAreserva *listaReservas) {
    if (listaUsuarios->inicio == NULL || listaReservas->inicio == NULL) {
        printf("A lista de usuarios com reservas esta vazia.\n\n");
        return;
    }

    USUARIO *usuarioAtual = listaUsuarios->inicio;

    printf("\nLista de Usuarios com Reserva:\n");

    while (usuarioAtual != NULL) {
        RESERVA *reservaAtual = listaReservas->inicio;  // Reinicia o ponteiro para o início da lista de reservas

        // Verifica se o usuário possui uma reserva correspondente
        while (reservaAtual != NULL) {
            if (usuarioAtual->Id == reservaAtual->idUser) {
                // Exibe informações do usuário
                printf("Identificador do usuario: %d\n", usuarioAtual->Id);
                printf("Nome: %s", usuarioAtual->Nome);
                printf("Endereco: %s", usuarioAtual->Endereco);
                printf("Telefone: %s\n", usuarioAtual->Telefone);
                printf("\n");

                // Avança para a próxima reserva correspondente
                break;
            }
            reservaAtual = reservaAtual->prox;
        }

        // Avança para o próximo usuário na lista de usuários
        usuarioAtual = usuarioAtual->prox;
    }
}



void listarReserva(LISTAreserva *listaReservas) {
    if (listaReservas->inicio == NULL) {
        printf("A lista de reservas está vazia.\n\n");
        return;
    }

    RESERVA *atual = listaReservas->inicio;

    printf("\nLista de Todas as Reservas:\n");
    while (atual != NULL) {
        printf("Data de inicio: %s\n", atual->dataInicio);
        printf("Data de termino: %s\n", atual->dataFim);
        printf("Identificador do usuario: %d\n", atual->idUser);
        printf("Identificador do livro: %d\n", atual->idLivro);
        printf("\n\n");

        atual = atual->prox;
    }
}

