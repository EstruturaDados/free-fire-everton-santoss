#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

// -------------------------------------------------
// Estrutura que representa um componente da torre
// -------------------------------------------------
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade; // 1 a 10
} Componente;

// -------------------------------------------------
// Protótipos das funções
// -------------------------------------------------
void lerString(const char *prompt, char *buffer, int tamanho);
void mostrarComponentes(Componente vet[], int n);
void cadastrarComponentes(Componente vet[], int *n);

void bubbleSortNome(Componente vet[], int n, long long *comparacoes, double *tempo_ms);
void insertionSortTipo(Componente vet[], int n, long long *comparacoes, double *tempo_ms);
void selectionSortPrioridade(Componente vet[], int n, long long *comparacoes, double *tempo_ms);

int buscaBinariaPorNome(Componente vet[], int n, const char *chave, long long *comparacoes);

// -------------------------------------------------
// Função utilitária: remove '\n' e lê linha com fgets
// -------------------------------------------------
void lerString(const char *prompt, char *buffer, int tamanho) {
    printf("%s", prompt);
    if (fgets(buffer, tamanho, stdin) != NULL) {
        // remove newline
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        // em caso de erro, garante string vazia
        buffer[0] = '\0';
    }
}

// -------------------------------------------------
// Exibe vetor de componentes formatado
// -------------------------------------------------
void mostrarComponentes(Componente vet[], int n) {
    printf("\n---- Componentes (%d) ----\n", n);
    if (n == 0) {
        printf("(nenhum componente cadastrado)\n");
        return;
    }
    printf("%-3s %-30s %-15s %s\n", "No", "Nome", "Tipo", "Prioridade");
    for (int i = 0; i < n; i++) {
        printf("%-3d %-30s %-15s %d\n", i + 1, vet[i].nome, vet[i].tipo, vet[i].prioridade);
    }
    printf("-------------------------\n");
}

// -------------------------------------------------
// Cadastro de componentes (até MAX_COMPONENTES)
// Usa fgets para strings e atoi para prioridade
// -------------------------------------------------
void cadastrarComponentes(Componente vet[], int *n) {
    char buffer[64];
    while (1) {
        if (*n >= MAX_COMPONENTES) {
            printf("\n⚠️  Limite de %d componentes atingido.\n", MAX_COMPONENTES);
            return;
        }
        printf("\nCadastrar novo componente? (s/n): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;
        if (buffer[0] == 'n' || buffer[0] == 'N') return;
        // nome
        lerString("Nome (ex: chip central): ", vet[*n].nome, TAM_NOME);
        // tipo
        lerString("Tipo (ex: controle, suporte, propulsao): ", vet[*n].tipo, TAM_TIPO);
        // prioridade (1..10)
        while (1) {
            lerString("Prioridade (1 a 10): ", buffer, sizeof(buffer));
            int p = atoi(buffer);
            if (p >= 1 && p <= 10) {
                vet[*n].prioridade = p;
                break;
            } else {
                printf("Prioridade inválida. Tente novamente.\n");
            }
        }
        (*n)++;
        printf("✅ Componente cadastrado.\n");
    }
}

// -------------------------------------------------
// Bubble Sort por nome (string)
// Conta comparações e mede tempo em ms
// -------------------------------------------------
void bubbleSortNome(Componente vet[], int n, long long *comparacoes, double *tempo_ms) {
    *comparacoes = 0;
    clock_t start = clock();

    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                // troca
                Componente tmp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break; // otimização: se não trocou, já está ordenado
    }

    clock_t end = clock();
    *tempo_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}

// -------------------------------------------------
// Insertion Sort por tipo (string)
// Conta comparações e mede tempo em ms
// -------------------------------------------------
void insertionSortTipo(Componente vet[], int n, long long *comparacoes, double *tempo_ms) {
    *comparacoes = 0;
    clock_t start = clock();

    for (int i = 1; i < n; i++) {
        Componente key = vet[i];
        int j = i - 1;
        // comparar tipos; cada strcmp é uma comparação
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(vet[j].tipo, key.tipo) > 0) {
                vet[j + 1] = vet[j];
                j--;
            } else {
                break;
            }
        }
        vet[j + 1] = key;
    }

    clock_t end = clock();
    *tempo_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}

// -------------------------------------------------
// Selection Sort por prioridade (int)
// Conta comparações e mede tempo em ms
// -------------------------------------------------
void selectionSortPrioridade(Componente vet[], int n, long long *comparacoes, double *tempo_ms) {
    *comparacoes = 0;
    clock_t start = clock();

    for (int i = 0; i < n - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (vet[j].prioridade < vet[idxMin].prioridade) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            Componente tmp = vet[i];
            vet[i] = vet[idxMin];
            vet[idxMin] = tmp;
        }
    }

    clock_t end = clock();
    *tempo_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}

// -------------------------------------------------
// Busca binária por nome (após vetor ordenado por nome)
// Retorna índice (>=0) se encontrado, -1 se não.
// Conta comparações feitas.
// -------------------------------------------------
int buscaBinariaPorNome(Componente vet[], int n, const char *chave, long long *comparacoes) {
    *comparacoes = 0;
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, vet[meio].nome);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1;
}

// -------------------------------------------------
// Função principal: menu e integração
// -------------------------------------------------
int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao_main = -1;
    char buffer[64];

    printf("=== Módulo Avançado: Prioritização e Montagem da Torre de Fuga ===\n");

    // loop principal
    while (1) {
        printf("\nMenu principal:\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Mostrar componentes\n");
        printf("3 - Ordenar por NOME (Bubble Sort) e buscar binária por nome\n");
        printf("4 - Ordenar por TIPO (Insertion Sort)\n");
        printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6 - Limpar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        opcao_main = atoi(buffer);

        if (opcao_main == 0) break;

        if (opcao_main == 1) {
            cadastrarComponentes(componentes, &n);
            mostrarComponentes(componentes, n);
        } else if (opcao_main == 2) {
            mostrarComponentes(componentes, n);
        } else if (opcao_main == 3) {
            if (n == 0) {
                printf("Nenhum componente cadastrado.\n");
                continue;
            }
            // fazer uma cópia para não perder a ordem original (opcional)
            Componente copia[MAX_COMPONENTES];
            for (int i = 0; i < n; i++) copia[i] = componentes[i];

            long long compBubble = 0;
            double tempoBubble = 0.0;
            bubbleSortNome(copia, n, &compBubble, &tempoBubble);
            printf("\nResultado do Bubble Sort (por nome):\n");
            mostrarComponentes(copia, n);
            printf("Comparações: %lld | Tempo: %.3f ms\n", compBubble, tempoBubble);

            // busca binária: pede nome
            char chave[TAM_NOME];
            lerString("Digite o NOME do componente-chave para busca binária: ", chave, TAM_NOME);
            long long compBin = 0;
            int idx = buscaBinariaPorNome(copia, n, chave, &compBin);
            printf("Comparações (busca binária): %lld\n", compBin);
            if (idx >= 0) {
                printf("✅ Componente-chave encontrado na posição %d:\n", idx + 1);
                printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                    copia[idx].nome, copia[idx].tipo, copia[idx].prioridade);
            } else {
                printf("❌ Componente-chave NÃO encontrado.\n");
            }

        } else if (opcao_main == 4) {
            if (n == 0) {
                printf("Nenhum componente cadastrado.\n");
                continue;
            }
            Componente copia[MAX_COMPONENTES];
            for (int i = 0; i < n; i++) copia[i] = componentes[i];

            long long compIns = 0;
            double tempoIns = 0.0;
            insertionSortTipo(copia, n, &compIns, &tempoIns);
            printf("\nResultado do Insertion Sort (por tipo):\n");
            mostrarComponentes(copia, n);
            printf("Comparações: %lld | Tempo: %.3f ms\n", compIns, tempoIns);
        } else if (opcao_main == 5) {
            if (n == 0) {
                printf("Nenhum componente cadastrado.\n");
                continue;
            }
            Componente copia[MAX_COMPONENTES];
            for (int i = 0; i < n; i++) copia[i] = componentes[i];

            long long compSel = 0;
            double tempoSel = 0.0;
            selectionSortPrioridade(copia, n, &compSel, &tempoSel);
            printf("\nResultado do Selection Sort (por prioridade ascendente):\n");
            mostrarComponentes(copia, n);
            printf("Comparações: %lld | Tempo: %.3f ms\n", compSel, tempoSel);
        } else if (opcao_main == 6) {
            printf("Confirmar limpeza de todos os componentes? (s/n): ");
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                if (buffer[0] == 's' || buffer[0] == 'S') {
                    n = 0;
                    printf("Componentes limpos.\n");
                } else {
                    printf("Operação cancelada.\n");
                }
            }
        } else {
            printf("Opção inválida.\n");
        }
    }

    printf("\nSaindo. Boa sorte na construção da torre!\n");
    return 0;
}
