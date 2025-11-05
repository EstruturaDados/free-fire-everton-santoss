#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// =====================================================
// ESTRUTURAS DE DADOS
// =====================================================

// Estrutura base para o item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =====================================================
// VARIÁVEIS GLOBAIS
// =====================================================
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

No* mochilaLista = NULL;
int totalItensLista = 0;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// =====================================================
// FUNÇÕES AUXILIARES
// =====================================================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirItem(Item item, int indice) {
    printf("%d️⃣  Nome: %s | Tipo: %s | Quantidade: %d\n",
           indice + 1, item.nome, item.tipo, item.quantidade);
}

// =====================================================
// VERSÃO COM VETOR
// =====================================================
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\n⚠️  A mochila (vetor) está cheia!\n");
        return;
    }

    Item novo;
    limparBuffer();
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItensVetor++] = novo;
    printf("\n✅ Item adicionado ao vetor com sucesso!\n");
}

void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("\n⚠️  Nenhum item no vetor.\n");
        return;
    }

    char nomeBusca[30];
    limparBuffer();
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            totalItensVetor--;
            printf("\n🗑️  Item '%s' removido do vetor!\n", nomeBusca);
            return;
        }
    }
    printf("\n❌ Item não encontrado.\n");
}

void listarItensVetor() {
    printf("\n📦 Itens no vetor:\n");
    if (totalItensVetor == 0) {
        printf("(nenhum item cadastrado)\n");
        return;
    }

    for (int i = 0; i < totalItensVetor; i++)
        exibirItem(mochilaVetor[i], i);
}

void ordenarVetor() {
    Item temp;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = i + 1; j < totalItensVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
    printf("\n🔤 Vetor ordenado alfabeticamente!\n");
}

void buscarSequencialVetor() {
    if (totalItensVetor == 0) {
        printf("\n⚠️  Nenhum item no vetor.\n");
        return;
    }

    comparacoesSequencial = 0;
    char nomeBusca[30];
    limparBuffer();
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            exibirItem(mochilaVetor[i], i);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("\n❌ Item não encontrado.\n");
    printf("Comparações realizadas: %d\n", comparacoesSequencial);
}

void buscarBinariaVetor() {
    if (totalItensVetor == 0) {
        printf("\n⚠️  Nenhum item no vetor.\n");
        return;
    }

    ordenarVetor(); // garantir que está ordenado

    comparacoesBinaria = 0;
    char nomeBusca[30];
    limparBuffer();
    printf("Digite o nome do item a buscar (binária): ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int inicio = 0, fim = totalItensVetor - 1;
    while (inicio <= fim) {
        comparacoesBinaria++;
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nomeBusca, mochilaVetor[meio].nome);
        if (cmp == 0) {
            printf("\n✅ Item encontrado (busca binária)!\n");
            exibirItem(mochilaVetor[meio], meio);
            printf("Comparações realizadas: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }

    printf("\n❌ Item não encontrado.\n");
    printf("Comparações realizadas: %d\n", comparacoesBinaria);
}

// =====================================================
// VERSÃO COM LISTA ENCADEADA
// =====================================================
void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("\nErro de memória!\n");
        return;
    }

    limparBuffer();
    printf("Nome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;
    totalItensLista++;
    printf("\n✅ Item adicionado à lista encadeada!\n");
}

void removerItemLista() {
    if (!mochilaLista) {
        printf("\n⚠️  Lista vazia.\n");
        return;
    }

    char nomeBusca[30];
    limparBuffer();
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                mochilaLista = atual->proximo;

            free(atual);
            totalItensLista--;
            printf("\n🗑️  Item '%s' removido da lista!\n", nomeBusca);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("\n❌ Item não encontrado.\n");
}

void listarItensLista() {
    printf("\n📦 Itens na lista encadeada:\n");
    if (!mochilaLista) {
        printf("(nenhum item cadastrado)\n");
        return;
    }

    No* atual = mochilaLista;
    int i = 0;
    while (atual) {
        exibirItem(atual->dados, i++);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    if (!mochilaLista) {
        printf("\n⚠️  Lista vazia.\n");
        return;
    }

    comparacoesSequencial = 0;
    char nomeBusca[30];
    limparBuffer();
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    No* atual = mochilaLista;
    int i = 0;
    while (atual) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            exibirItem(atual->dados, i);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
        i++;
    }

    printf("\n❌ Item não encontrado.\n");
    printf("Comparações realizadas: %d\n", comparacoesSequencial);
}

// =====================================================
// MENU PRINCIPAL
// =====================================================
int main() {
    int escolhaEstrutura;
    int opcao;

    do {
        printf("\n============ 🧩 ESCOLHA A ESTRUTURA ============\n");
        printf("1. Mochila com VETOR (lista sequencial)\n");
        printf("2. Mochila com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("===============================================\n");
        printf("Escolha: ");
        scanf("%d", &escolhaEstrutura);

        if (escolhaEstrutura == 1) {
            do {
                printf("\n==== 🎒 MENU - MOCHILA VETOR ====\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar sequencial\n");
                printf("5. Buscar binária\n");
                printf("0. Voltar\n");
                printf("===============================\n");
                printf("Opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: buscarBinariaVetor(); break;
                }
            } while (opcao != 0);
        }

        else if (escolhaEstrutura == 2) {
            do {
                printf("\n==== 🪢 MENU - LISTA ENCADEADA ====\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar sequencial\n");
                printf("0. Voltar\n");
                printf("===============================\n");
                printf("Opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                }
            } while (opcao != 0);
        }

    } while (escolhaEstrutura != 0);

    printf("\n👋 Saindo do sistema comparativo de mochilas.\n");
    return 0;
}
