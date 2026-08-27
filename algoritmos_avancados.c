#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_HASH 10

// -------------------------
// Estrutura da Árvore Binária (Salas)
// -------------------------
typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// -------------------------
// Estrutura da Árvore de Busca (Pistas)
// -------------------------
typedef struct Pista {
    char texto[50];
    struct Pista *esq;
    struct Pista *dir;
} Pista;

// -------------------------
// Estrutura da Tabela Hash (Suspeitos)
// -------------------------
typedef struct Suspeito {
    char nome[50];
    int contador;               // quantas pistas apontam para ele
    struct Suspeito *prox;
} Suspeito;

// -------------------------
// Funções da Árvore Binária
// -------------------------
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strncpy(nova->nome, nome, sizeof(nova->nome));
    strncpy(nova->pista, pista, sizeof(nova->pista));
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// -------------------------
// Funções da BST de Pistas
// -------------------------
Pista* criarPista(const char *texto) {
    Pista *nova = (Pista*) malloc(sizeof(Pista));
    strncpy(nova->texto, texto, sizeof(nova->texto));
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

Pista* inserirPista(Pista *raiz, const char *texto) {
    if (raiz == NULL) return criarPista(texto);

    if (strcmp(texto, raiz->texto) < 0)
        raiz->esq = inserirPista(raiz->esq, texto);
    else if (strcmp(texto, raiz->texto) > 0)
        raiz->dir = inserirPista(raiz->dir, texto);

    return raiz;
}

void listarPistas(Pista *raiz) {
    if (raiz == NULL) return;
    listarPistas(raiz->esq);
    printf("• %s\n", raiz->texto);
    listarPistas(raiz->dir);
}

// -------------------------
// Funções da Tabela Hash
// -------------------------
int funcaoHash(const char *nome) {
    return nome[0] % TAM_HASH;
}

Suspeito* criarSuspeito(const char *nome) {
    Suspeito *novo = (Suspeito*) malloc(sizeof(Suspeito));
    strncpy(novo->nome, nome, sizeof(novo->nome));
    novo->contador = 1;
    novo->prox = NULL;
    return novo;
}

void inserirNaHash(Suspeito *tabela[], const char *suspeito) {
    int indice = funcaoHash(suspeito);

    Suspeito *atual = tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->nome, suspeito) == 0) {
            atual->contador++;
            return;
        }
        atual = atual->prox;
    }

    Suspeito *novo = criarSuspeito(suspeito);
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

void listarSuspeitos(Suspeito *tabela[]) {
    printf("\n🔍 Relação de suspeitos e pistas:\n");

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *atual = tabela[i];
        while (atual != NULL) {
            printf("• %s — %d pistas\n", atual->nome, atual->contador);
            atual = atual->prox;
        }
    }
}

char* suspeitoMaisCitado(Suspeito *tabela[]) {
    int maior = -1;
    char *nome = NULL;

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *atual = tabela[i];
        while (atual != NULL) {
            if (atual->contador > maior) {
                maior = atual->contador;
                nome = atual->nome;
            }
            atual = atual->prox;
        }
    }

    return nome;
}

// -------------------------
// Exploração das salas
// -------------------------
void explorarSalas(Sala *atual, Pista **arvorePistas, Suspeito *tabela[]) {
    char opcao;

    while (atual != NULL) {
        printf("\n📍 Você está na sala: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("🔎 Você encontrou uma pista: %s\n", atual->pista);

            *arvorePistas = inserirPista(*arvorePistas, atual->pista);

            // Associa pista → suspeito automaticamente
            if (strcmp(atual->pista, "Livro antigo rasgado") == 0)
                inserirNaHash(tabela, "Sr. Dalton");
            else if (strcmp(atual->pista, "Anotações suspeitas") == 0)
                inserirNaHash(tabela, "Sra. Helena");
            else if (strcmp(atual->pista, "Chave enferrujada") == 0)
                inserirNaHash(tabela, "Jardineiro Marcos");
            else if (strcmp(atual->pista, "Pegadas na terra") == 0)
                inserirNaHash(tabela, "Jardineiro Marcos");
        }

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("🏁 Fim do caminho!\n");
            return;
        }

        printf("\nEscolha seu caminho:\n");
        printf("  e → esquerda\n");
        printf("  d → direita\n");
        printf("  p → listar pistas\n");
        printf("  u → listar suspeitos\n");
        printf("  s → sair\n");
        printf("Opção: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') atual = atual->esquerda;
        else if (opcao == 'd') atual = atual->direita;
        else if (opcao == 'p') listarPistas(*arvorePistas);
        else if (opcao == 'u') listarSuspeitos(tabela);
        else if (opcao == 's') return;
        else printf("Opção inválida!\n");
    }
}

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    // Salas
    Sala *hall = criarSala("Hall de Entrada", "");
    Sala *biblioteca = criarSala("Biblioteca", "Livro antigo rasgado");
    Sala *cozinha = criarSala("Cozinha", "");
    Sala *escritorio = criarSala("Escritório", "Anotações suspeitas");
    Sala *porao = criarSala("Porão", "Chave enferrujada");
    Sala *jardim = criarSala("Jardim", "Pegadas na terra");

    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = escritorio;
    biblioteca->direita = porao;

    cozinha->esquerda = jardim;

    // Estruturas
    Pista *arvorePistas = NULL;
    Suspeito *tabela[TAM_HASH] = {NULL};

    explorarSalas(hall, &arvorePistas, tabela);

    printf("\n📜 Pistas finais:\n");
    listarPistas(arvorePistas);

    printf("\n🧠 Suspeitos analisados:\n");
    listarSuspeitos(tabela);

    char *culpado = suspeitoMaisCitado(tabela);
    printf("\n🏆 Suspeito mais provável: %s\n", culpado);

    return 0;
}

