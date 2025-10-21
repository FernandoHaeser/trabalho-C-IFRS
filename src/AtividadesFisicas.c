/*
 * Registro de Atividades Fisícas - Projeto de Aprendizagem
 * Autores: Fernando A. Haeser, Isadora S. Feijó, Nicolas G. Cafarete.
 * Data: outubro/2025
 * Objetivo: Desenvolver uma ferramenta que auxilie o usuário no registro das atividades fisícas,
 * monitorando suas atividades e demonstrando de forma simples e prática.
 */
#include <stdio.h>    
#include <stdlib.h>   // Biblioteca para funções utilitárias 
#include <string.h>   // Biblioteca para manipulação de strings 
#include <math.h>     // Biblioteca matemática 

#define MAX_REGISTROS 100  // Define o número máximo de registros de atividades que podem ser armazenados

// Estruturas de dados globais para armazenar informações das atividades
char titulo_atividade[MAX_REGISTROS][100];  
char tipo_atividade[MAX_REGISTROS][50];    
float calorias[MAX_REGISTROS];             
float tempo_minutos[MAX_REGISTROS];      
int freq_cardiaca_media[MAX_REGISTROS]; 
float ritmo_medio[MAX_REGISTROS];         

int contador_registros = 0;  // Contador para o número atual de registros (inicia em 0)

// Função utilitária para ler um número real positivo do usuário
// Repete até que o usuário digite um valor válido (> 0)
float ler_real_positivo(const char *mensagem) {
    float valor;
    int scan_result;
    
    do {
        printf("%s", mensagem);  
        
        scan_result = scanf("%f", &valor);  // Tenta ler um float
        
        if (scan_result != 1) {  // Se a leitura falhou (não é um número)
            printf("Entrada inválida! Digite um número.\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada até o newline
            continue;  // Volta ao início do loop
        }
        
        if (valor <= 0) {  // Se o valor não é positivo
            printf("Valor inválido! Digite um número maior que zero.\n");
        }
    } while (valor <= 0);  // Repete enquanto o valor não for positivo
    
    return valor;  // Retorna o valor válido
}

// Função utilitária para ler um número inteiro positivo do usuário
// Similar à anterior, mas para inteiros
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

// Função utilitária para ler uma string não vazia do usuário
// Usa fgets para ler a linha inteira e remove o newline
void ler_cadeia_nao_vazia(const char *mensagem, char *destino, int tamanho) {
    do {
        printf("%s", mensagem);
        getchar();  
        fgets(destino, tamanho, stdin);  
        destino[strcspn(destino, "\n")] = 0;  
        if (strlen(destino) == 0) {  // Se a string estiver vazia
            printf("Entrada inválida! Não pode ser vazia.\n");
        }
    } while (strlen(destino) == 0);  // Repete até que não seja vazia
}

// Função para registrar uma nova atividade
void registrar_atividade() {
    // Limpa a tela antes de exibir o formulário de registro
    #if defined(_WIN32)
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux/Mac
    #endif

    // Verifica se atingiu o limite de registros
    if (contador_registros >= MAX_REGISTROS) {
        printf("\nLimite máximo de registros atingido (%d).\n", MAX_REGISTROS);
        return;  // Sai da função sem registrar
    }

    // Exibe cabeçalho
    printf("======================================\n");
    printf("|      Registrar Nova Atividade      |\n");
    printf("======================================\n");

    // Lê o título da atividade
    ler_cadeia_nao_vazia("Digite um título para a atividade: ", titulo_atividade[contador_registros], 100);

    // Lê o tipo de atividade via menu numérico
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

    // Define o tipo baseado na opção escolhida
    switch (tipo_opcao) {
        case 1: strcpy(tipo_atividade[contador_registros], "Corrida"); break;
        case 2: strcpy(tipo_atividade[contador_registros], "Musculação"); break;
        case 3: strcpy(tipo_atividade[contador_registros], "Yoga"); break;
        case 4: strcpy(tipo_atividade[contador_registros], "Natação"); break;
        case 5: strcpy(tipo_atividade[contador_registros], "Caminhada"); break;
        case 6: strcpy(tipo_atividade[contador_registros], "Outros"); break;
    }

    // Lê o ritmo médio baseado no tipo de atividade
    if (strcmp(tipo_atividade[contador_registros], "Corrida") == 0 || strcmp(tipo_atividade[contador_registros], "Caminhada") == 0) {
        ritmo_medio[contador_registros] = ler_real_positivo("Informe o ritmo médio (Km/h): ");
    } else if (strcmp(tipo_atividade[contador_registros], "Musculação") == 0) {
        ritmo_medio[contador_registros] = ler_real_positivo("Informe o peso médio utilizado (kg): ");
    } else if (strcmp(tipo_atividade[contador_registros], "Yoga") == 0) {
        ritmo_medio[contador_registros] = 0;  // Yoga não tem ritmo
    } else if (strcmp(tipo_atividade[contador_registros], "Natação") == 0) {
        ritmo_medio[contador_registros] = ler_real_positivo("Informe o ritmo médio (m/min): ");
    } else {
        ritmo_medio[contador_registros] = 0;  // Outros tipos não têm ritmo
    }

    // Lê os outros dados da atividade
    calorias[contador_registros] = ler_real_positivo("Calorias queimadas (kcal): ");
    tempo_minutos[contador_registros] = ler_real_positivo("Tempo de atividade (minutos): ");
    freq_cardiaca_media[contador_registros] = ler_inteiro_positivo("Frequência cardíaca média (BPM): ");

    contador_registros++;  // Incrementa o contador de registros

    printf("\nAtividade '%s' registrada com sucesso!\n", titulo_atividade[contador_registros - 1]);
}

// Função para exibir o resumo das atividades registradas
void exibir_resumo() {
    // Limpa a tela antes de exibir o resumo
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif

    // Se não há registros, exibe mensagem e sai
    if (contador_registros == 0) {
        printf("==========================================\n");
        printf("|       NENHUMA ATIVIDADE REGISTRADA     |\n");
        printf("==========================================\n");
        return;
    }

    // Exibe cabeçalho do resumo
    printf("==========================================\n");
    printf("|         RESUMO DE ATIVIDADES           |\n");
    printf("==========================================\n");
    printf("TOTAL DE ATIVIDADES: %d\n", contador_registros);

    // tipos possíveis para iterar
    const char *tipos[] = {"Corrida", "Musculação", "Yoga", "Natação", "Caminhada", "Outros"};

    // Variáveis para somar estatísticas gerais
    float soma_calorias = 0;
    float soma_tempo = 0;
    int soma_freq = 0;
    float soma_ritmo = 0;

    // Loop para cada tipo de atividade
    for (int t = 0; t < 6; t++) {
        const char *tipo_atual = tipos[t];
        int encontrou = 0;  // Flag para verificar se há atividades desse tipo

        // Verifica se existe pelo menos uma atividade desse tipo
        for (int i = 0; i < contador_registros; i++) {
            if (strcmp(tipo_atividade[i], tipo_atual) == 0) {
                encontrou = 1;
                break;
            }
        }

        // Se encontrou, exibe as atividades desse tipo
        if (encontrou) {
            printf("\n==========================================\n");
            printf("        ATIVIDADES - %s\n", tipo_atual);
            printf("==========================================\n");

            // Loop para exibir cada atividade desse tipo
            for (int i = 0; i < contador_registros; i++) {
                if (strcmp(tipo_atividade[i], tipo_atual) == 0) {
                    printf("Título:              %s\n", titulo_atividade[i]);
                    printf("Calorias:            %.2f kcal\n", calorias[i]);

                    // Exibe tempo em horas se >= 60 min, senão em minutos
                    if (tempo_minutos[i] >= 60) {
                        printf("Tempo:               %.2f horas\n", tempo_minutos[i] / 60.0);
                    } else {
                        printf("Tempo:               %.2f minutos\n", tempo_minutos[i]);
                    }

                    printf("Frequência Cardíaca: %d BPM\n", freq_cardiaca_media[i]);

                    // Exibe ritmo apenas se > 0
                    if (ritmo_medio[i] > 0) {
                        printf("Ritmo/Peso Médio:    %.2f\n", ritmo_medio[i]);
                    }

                    printf("------------------------------------------\n");

                    // Soma para estatísticas gerais
                    soma_calorias += calorias[i];
                    soma_tempo += tempo_minutos[i];
                    soma_freq += freq_cardiaca_media[i];
                    soma_ritmo += ritmo_medio[i];
                }
            }
        }
    }

    // Exibe estatísticas gerais
    printf("\n==========================================\n");
    printf("|         ESTATÍSTICAS GERAIS            |\n");
    printf("==========================================\n");
    printf("Total de calorias:        %.2f kcal\n", soma_calorias);
    printf("Tempo médio por atividade: %.2f min\n", soma_tempo / contador_registros);
    printf("Frequência cardíaca média: %.2f BPM\n", (float) soma_freq / contador_registros);
    printf("Ritmo/Peso médio geral:   %.2f\n", soma_ritmo / contador_registros);

    // Exibe estatísticas por tipo de atividade
    printf("\n==========================================\n");
    printf("|  ESTATÍSTICAS POR TIPO DE ATIVIDADE    |\n");
    printf("==========================================\n");

    // Loop para calcular e exibir estatísticas por tipo
    for (int t = 0; t < 6; t++) {
        const char *tipo = tipos[t];
        int qtd = 0;  // Quantidade de atividades desse tipo
        float total_cal = 0;
        float total_temp = 0;
        int total_freq = 0;
        float total_ritmo = 0;

        // Soma os valores para esse tipo
        for (int i = 0; i < contador_registros; i++) {
            if (strcmp(tipo_atividade[i], tipo) == 0) {
                qtd++;
                total_cal += calorias[i];
                total_temp += tempo_minutos[i];
                total_freq += freq_cardiaca_media[i];
                total_ritmo += ritmo_medio[i];
            }
        }

        // Se há atividades desse tipo, exibe as estatísticas
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

// Função principal: loop do menu
int main() {
    int opcao;  // Variável para armazenar a opção do menu

    while (1) {  // Loop infinito até o usuário escolher sair
        // Limpa a tela a cada iteração do menu
        #if defined(_WIN32)
            system("cls");
        #else
            system("clear");
        #endif

        // Exibe o menu
        printf("======================================\n");
        printf("|   Menu de Registro de Atividades   |\n");
        printf("======================================\n");
        printf("1. Registrar Nova Atividade\n");
        printf("2. Exibir Resumo de Atividades\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);  // Lê a opção

        // Switch para executar a ação baseada na opção
        switch (opcao) {
            case 1:
                registrar_atividade();  // Chama a função de registro
                printf("\nPressione ENTER para voltar ao menu...");
                getchar(); getchar();  // Pausa para o usuário pressionar ENTER
                break;
            case 2:
                exibir_resumo();  // Chama a função de resumo
                printf("\nPressione ENTER para voltar ao menu...");
                getchar(); getchar();  // Pausa
                break;
            case 3:
                printf("\nSaindo do programa. Até a próxima!\n");
                exit(0);  // Sai do programa
            default:
                printf("\nOpção inválida! Retornando ao menu...\n");
                getchar(); getchar();  // Pausa mesmo em erro
        }
    }
    
}
