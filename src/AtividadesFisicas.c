#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_REGISTROS 100

// Estruturas de dados
char titulo_atividade[MAX_REGISTROS][100];
char tipo_atividade[MAX_REGISTROS][50];
float calorias[MAX_REGISTROS];
float tempo_minutos[MAX_REGISTROS];
int freq_cardiaca_media[MAX_REGISTROS];
float ritmo_medio[MAX_REGISTROS];

int contador_registros = 0;

// Funções utilitárias para leitura segura
float ler_real_positivo(const char *mensagem) {
    float valor;
    int scan_result;
    
    do {
        printf("%s", mensagem);
        
        scan_result = scanf("%f", &valor);
        
        if (scan_result != 1) {
            printf("Entrada inválida! Digite um número.\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (valor <= 0) {
            printf("Valor inválido! Digite um número maior que zero.\n");
        }
    } while (valor <= 0);
    
    return valor;
}

int ler_inteiro_positivo(const char *mensagem) {
    int valor;
    int scan_result;
    
    do {
        printf("%s", mensagem);
        
        scan_result = scanf("%d", &valor);
        
        if (scan_result != 1) {
            printf("Entrada inválida! Digite um número.\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (valor <= 0) {
            printf("Valor inválido! Digite um número maior que zero.\n");
        }
    } while (valor <= 0);
    
    return valor;
}

void ler_cadeia_nao_vazia(const char *mensagem, char *destino, int tamanho) {
    do {
        printf("%s", mensagem);
        getchar(); // limpa buffer
        fgets(destino, tamanho, stdin);
        destino[strcspn(destino, "\n")] = 0; // remove \n
        if (strlen(destino) == 0) {
            printf("Entrada inválida! Não pode ser vazia.\n");
        }
    } while (strlen(destino) == 0);
}

// Função registrar atividade
void registrar_atividade() {
    if (contador_registros >= MAX_REGISTROS) {
        printf("\nLimite máximo de registros atingido (%d).\n", MAX_REGISTROS);
        return;
    }

    printf("======================================\n");
    printf("|      Registrar Nova Atividade      |\n");
    printf("======================================\n");

    ler_cadeia_nao_vazia("Digite um título para a atividade: ", titulo_atividade[contador_registros], 100);

    int tipo_opcao;
    do {
        printf("\nEscolha o tipo de atividade:\n");
        printf("1. Corrida\n");
        printf("2. Musculação\n");
        printf("3. Yoga\n");
        printf("4. Natação\n");
        printf("5. Caminhada\n");
        printf("6. Outros\n");
        printf("Digite a opção: ");
        
        if (scanf("%d", &tipo_opcao) != 1) {
            printf("Entrada inválida! Por favor, digite um número.\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (tipo_opcao < 1 || tipo_opcao > 6) {
            printf("Opção inválida! Por favor, escolha uma opção de 1 a 6.\n");
        }
    } while (tipo_opcao < 1 || tipo_opcao > 6);

    switch (tipo_opcao) {
        case 1: strcpy(tipo_atividade[contador_registros], "Corrida"); break;
        case 2: strcpy(tipo_atividade[contador_registros], "Musculação"); break;
        case 3: strcpy(tipo_atividade[contador_registros], "Yoga"); break;
        case 4: strcpy(tipo_atividade[contador_registros], "Natação"); break;
        case 5: strcpy(tipo_atividade[contador_registros], "Caminhada"); break;
        case 6: strcpy(tipo_atividade[contador_registros], "Outros"); break;
    }

    if (strcmp(tipo_atividade[contador_registros], "Corrida") == 0 || strcmp(tipo_atividade[contador_registros], "Caminhada") == 0) {
        ritmo_medio[contador_registros] = ler_real_positivo("Informe o ritmo médio (Km/h): ");
    } else if (strcmp(tipo_atividade[contador_registros], "Musculação") == 0) {
        ritmo_medio[contador_registros] = ler_real_positivo("Informe o peso médio utilizado (kg): ");
    } else if (strcmp(tipo_atividade[contador_registros], "Yoga") == 0) {
        ritmo_medio[contador_registros] = 0;
    } else if (strcmp(tipo_atividade[contador_registros], "Natação") == 0) {
        ritmo_medio[contador_registros] = ler_real_positivo("Informe o ritmo médio (m/min): ");
    } else {
        ritmo_medio[contador_registros] = 0;
    }

    calorias[contador_registros] = ler_real_positivo("Calorias queimadas (kcal): ");
    tempo_minutos[contador_registros] = ler_real_positivo("Tempo de atividade (minutos): ");
    freq_cardiaca_media[contador_registros] = ler_inteiro_positivo("Frequência cardíaca média (BPM): ");

    contador_registros++;

    printf("\nAtividade '%s' registrada com sucesso!\n", titulo_atividade[contador_registros - 1]);
}

// Função exibir resumo
void exibir_resumo() {
    // Limpa a tela antes de exibir o resumo
    defined(_WIN32)
        system("cls");  // Para Windows
    #else
        system("clear");  // Para Linux/Mac
    #endif

    if (contador_registros == 0) {
        printf("==========================================\n");
        printf("|       NENHUMA ATIVIDADE REGISTRADA     |\n");
        printf("==========================================\n");
        return;
    }

    printf("==========================================\n");
    printf("|         RESUMO DE ATIVIDADES           |\n");
    printf("==========================================\n");
    printf("TOTAL DE ATIVIDADES: %d\n", contador_registros);

    const char *tipos[] = {"Corrida", "Musculação", "Yoga", "Natação", "Caminhada", "Outros"};

    float soma_calorias = 0;
    float soma_tempo = 0;
    int soma_freq = 0;
    float soma_ritmo = 0;

    for (int t = 0; t < 6; t++) {
        const char *tipo_atual = tipos[t];
        int encontrou = 0;

        for (int i = 0; i < contador_registros; i++) {
            if (strcmp(tipo_atividade[i], tipo_atual) == 0) {
                encontrou = 1;
                break;
            }
        }

        if (encontrou) {
            printf("\n==========================================\n");
            printf("        ATIVIDADES - %s\n", tipo_atual);
            printf("==========================================\n");

            for (int i = 0; i < contador_registros; i++) {
                if (strcmp(tipo_atividade[i], tipo_atual) == 0) {
                    printf("Título:              %s\n", titulo_atividade[i]);
                    printf("Calorias:            %.2f kcal\n", calorias[i]);

                    if (tempo_minutos[i] >= 60) {
                        printf("Tempo:               %.2f horas\n", tempo_minutos[i] / 60.0);
                    } else {
                        printf("Tempo:               %.2f minutos\n", tempo_minutos[i]);
                    }

                    printf("Frequência Cardíaca: %d BPM\n", freq_cardiaca_media[i]);

                    if (ritmo_medio[i] > 0) {
                        printf("Ritmo/Peso Médio:    %.2f\n", ritmo_medio[i]);
                    }

                    printf("------------------------------------------\n");

                    soma_calorias += calorias[i];
                    soma_tempo += tempo_minutos[i];
                    soma_freq += freq_cardiaca_media[i];
                    soma_ritmo += ritmo_medio[i];
                }
            }
        }
    }

    printf("\n==========================================\n");
    printf("|         ESTATÍSTICAS GERAIS            |\n");
    printf("==========================================\n");
    printf("Total de calorias:        %.2f kcal\n", soma_calorias);
    printf("Tempo médio por atividade: %.2f min\n", soma_tempo / contador_registros);
    printf("Frequência cardíaca média: %.2f BPM\n", (float) soma_freq / contador_registros);
    printf("Ritmo/Peso médio geral:   %.2f\n", soma_ritmo / contador_registros);

    printf("\n==========================================\n");
    printf("|  ESTATÍSTICAS POR TIPO DE ATIVIDADE    |\n");
    printf("==========================================\n");

    for (int t = 0; t < 6; t++) {
        const char *tipo = tipos[t];
        int qtd = 0;
        float total_cal = 0;
        float total_temp = 0;
        int total_freq = 0;
        float total_ritmo = 0;

        for (int i = 0; i < contador_registros; i++) {
            if (strcmp(tipo_atividade[i], tipo) == 0) {
                qtd++;
                total_cal += calorias[i];
                total_temp += tempo_minutos[i];
                total_freq += freq_cardiaca_media[i];
                total_ritmo += ritmo_medio[i];
            }
        }

        if (qtd > 0) {
            printf("\n>>> %s <<<\n", tipo);
            printf("Quantidade:              %d\n", qtd);
            printf("Total de calorias:       %.2f kcal\n", total_cal);
            printf("Tempo médio:             %.2f min\n", total_temp / qtd);
            printf("Frequência cardíaca:     %.2f BPM\n", (float) total_freq / qtd);
            printf("Ritmo/Peso médio:        %.2f\n", total_ritmo / qtd);
        }
    }
}

// Função principal
int main() {
    int opcao;

    while (1) {
        printf("======================================\n");
        printf("|   Menu de Registro de Atividades   |\n");
        printf("======================================\n");
        printf("1. Registrar Nova Atividade\n");
        printf("2. Exibir Resumo de Atividades\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrar_atividade();
                break;
            case 2:
                exibir_resumo();
                printf("\nDigite qualquer tecla para voltar ao menu...");
                getchar(); getchar(); // pausa
                break;
            case 3:
                printf("\nSaindo do programa. Até a próxima!\n");
                exit(0);
            default:
                printf("\nOpção inválida! Retornando ao menu...\n");
        }
    }
    
    return 0;
}