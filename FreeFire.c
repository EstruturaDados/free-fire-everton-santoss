#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -------------------------------------------------------------
// Estrutura principal: representa um item da mochila do jogador
// -------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor global de itens e contador de quantos itens estão cadastrados
Item mochila[MAX_ITENS];
int totalItens = 0;

// -------------------------------------------------------------
// Função para limpar o buffer do teclado (evita problemas com fgets)
// -------------------------------------------------------------
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// -------------------------------------------------------------
// Função para inserir um novo item na mochila
// -------------------------------------------------------------
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️  A mochila está cheia! Máximo de %d itens.\n", MAX_ITENS);
        return;
    }

    Item novoItem;

    printf("\nDigite o nome do item: ");
    limparBuffer();
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // remove o '\n'

    printf("Digite o tipo (arma, municao, cura, etc): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);

    // Adiciona o item no vetor
    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\n✅ Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

// -------------------------------------------------------------
// Função para remover um item pelo nome
// -------------------------------------------------------------
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️  Nenhum item cadastrado.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja remover: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Move todos os itens seguintes uma posição para trás
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\n🗑️  Item '%s' removido com sucesso!\n", nomeBusca);
            return;
        }
    }

    printf("\n❌ Item '%s' não encontrado.\n", nomeBusca);
}

// -------------------------------------------------------------
// Função para listar todos os itens cadastrados
// -------------------------------------------------------------
void listarItens() {
    printf("\n📦 Itens na mochila:\n");
    if (totalItens == 0) {
        printf("  (nenhum item cadastrado)\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d️⃣  Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// -------------------------------------------------------------
// Função de busca sequencial por nome
// -------------------------------------------------------------
void buscarItem() {
    if (totalItens == 0) {
        printf("\n⚠️  Nenhum item cadastrado.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item '%s' não encontrado.\n", nomeBusca);
}

// -------------------------------------------------------------
// Função principal (menu interativo)
// -------------------------------------------------------------
int main() {
    int opcao;

    do {
        printf("\n=========== 🎒 MENU MOCHILA ===========\n");
        printf("1. Cadastrar novo item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("=======================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n👋 Saindo do sistema... Até logo!\n");
                break;
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
