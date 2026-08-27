#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// -------------------------
// Estrutura da Árvore Binária (Salas)
// -------------------------
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
    char pista[50];  // pista encontrada nesta sala (opcional)
} Sala;

// -------------------------
// Estrutura da Árvore de Busca (Pistas)
// -------------------------
typedef struct Pista {
    char texto[50];
    struct Pista *esq;
    struct Pista *dir;
} Pista;

// Cria uma sala
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strncpy(nova->nome, nome, sizeof(nova->nome));
    strncpy(nova->pista, pista, sizeof(nova->pista));
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Cria uma pista (nó da BST)
Pista* criarPista(const char *texto) {
    Pista *nova = (Pista*) malloc(sizeof(Pista));
    strncpy(nova->texto, texto, sizeof(nova->texto));
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// Insere pista na BST
Pista* inserirPista(Pista *raiz, const char *texto) {
    if (raiz == NULL) {
        return criarPista(texto);
    }

    if (strcmp(texto, raiz->texto) < 0) {
        raiz->esq = inserirPista(raiz->esq, texto);
    } else if (strcmp(texto, raiz->texto) > 0) {
        raiz->dir = inserirPista(raiz->dir, texto);
    }

    return raiz;
}

// Exibe pistas em ordem alfabética
void listarPistas(Pista *raiz) {
    if (raiz == NULL) return;
    listarPistas(raiz->esq);
    printf("• %s\n", raiz->texto);
    listarPistas(raiz->dir);
}

// Exploração das salas
void explorarSalas(Sala *atual, Pista **arvorePistas) {
    char opcao;

    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Se a sala contém uma pista, adiciona à BST
        if (strlen(atual->pista) > 0) {
            printf("Você encontrou uma pista: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        // Se chegou a um nó-folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Você chegou ao último cômodo.\n");
            return;
        }

        printf("\nEscolha seu caminho:\n");
        printf("  e → ir para a esquerda\n");
        printf("  d → ir para a direita\n");
        printf("  p → listar pistas encontradas\n");
        printf("  s → sair da exploração\n");
        printf("Opção: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            atual = atual->esquerda;
        } else if (opcao == 'd') {
            atual = atual->direita;
        } else if (opcao == 'p') {
            printf("\n📜 Pistas encontradas até agora:\n");
            listarPistas(*arvorePistas);
        } else if (opcao == 's') {
            printf("Exploração encerrada.\n");
            return;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
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

    // -------------------------
    // Construção da Mansão (Árvore Binária)
    // -------------------------
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

    // -------------------------
    // Árvore de Pistas (BST)
    // -------------------------
    Pista *arvorePistas = NULL;

    // Início da exploração
    explorarSalas(hall, &arvorePistas);

    printf("\n📌 Pistas finais coletadas:\n");
    listarPistas(arvorePistas);

    return 0;
}

