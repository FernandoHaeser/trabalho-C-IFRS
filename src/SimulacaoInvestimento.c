/*
 * Simulação de Investimentos - Projeto de Aprendizagem
 * Autores: Fernando A. Haeser, Isadora S. Feijó, Nicolas G. Cafarete.
 * Data: Setembro/2025
 * Objetivo: Desenvolver uma ferramenta que auxilie o usuário na simulação de investimentos,
 * monitorando seus resultados e demonstrando de forma simples e prática como o dinheiro pode render.
 */

#include <stdio.h>   // Biblioteca padrão para entrada e saída de dados.
#include <stdlib.h>  // Biblioteca padrão para funções do sistema (ex: system()).
#include <math.h>    // Biblioteca matemática usada para cálculos e arredondamentos.

// VARIÁVEIS GLOBAIS PARA SOMAR TODOS OS INVESTIMENTOS
double totalGeralInvestido = 0.0;
double totalGeralJuros = 0.0;
double totalGeralFinal = 0.0;
int totalSimulacoes = 0;

// Função auxiliar para arredondar valores com número definido de casas decimais
double arredondar(double valor, int casas) {
    double fator = pow(10, casas);          // Calcula o fator de multiplicação (10^casas)
    return round(valor * fator) / fator;    // Arredonda e retorna o valor final
}

int main() {
    int repetir = 1; // Controle do laço principal (permite simular várias vezes)

    while (repetir == 1) { // Enquanto o usuário quiser repetir a simulação
        // --- Declaração das variáveis locais da simulação ---
        double investimentoInicial;     // Valor que o usuário aplicará no início
        double investMensal;            // Valor que o usuário investirá mensalmente
        int anosSimulacao;              // Quantidade de anos a simular
        double taxaAnual;               // Taxa de juros anual
        double valorAtual;              // Valor acumulado ao longo do tempo
        int meses;                      // Contador de meses
        int opcaoInvestimento;          // Tipo de investimento escolhido
        double capitalTotalInvestido = 0.0; // Soma total investida pelo usuário

        // --- Exibe o título e boas-vindas ---
        printf("==================================================\n");
        printf("|       SIMULADOR BÁSICO DE INVESTIMENTOS        |\n");
        printf("==================================================\n");
        printf("➤ Olá! Vamos simular o crescimento do seu dinheiro!\n\n");

        // --- Entrada de dados do usuário ---
        printf("Qual o valor que você vai investir inicialmente? R$ ");
        scanf("%lf", &investimentoInicial);
        capitalTotalInvestido += investimentoInicial;

        printf("Qual o valor que você pretende investir mensalmente? R$ ");
        scanf("%lf", &investMensal);

        printf("Por quantos anos você quer simular o investimento? ");
        scanf("%d", &anosSimulacao);

        system("clear || cls"); // Limpa a tela (funciona em Windows ou Linux)

        // --- Menu de tipos de investimento (estrutura condicional) ---
        printf("==================================================================\n");
        printf("|                💰 Tipos de Investimento 💰                       |\n");
        printf("==================================================================\n");
        printf("| 1 - Tesouro Selic (Taxa ≈ 10.5%% a.a.)                          |\n");
        printf("| 2 - Fundo Imobiliário (Taxa ≈ 9.0%% a.a.)                       |\n");
        printf("| 3 - CDB/LCI (Taxa ≈ 11.0%% a.a.)                                |\n");
        printf("| 4 - Outra Taxa (Definida pelo usuário)                         |\n");
        printf("==================================================================\n");

        printf("Digite a opção desejada (1 a 4): ");
        scanf("%d", &opcaoInvestimento);

        system("clear || cls"); // Limpa novamente antes da próxima tela

        // --- Exibe o tipo de investimento escolhido ---
        printf("================================================\n");
        printf("|         ESCOLHA DO INVESTIMENTO              |\n");
        printf("================================================\n\n");

        switch (opcaoInvestimento) { // Estrutura de escolha (switch-case)
            case 1:
                taxaAnual = 0.105;
                printf("➡️  Tesouro Selic (10.5%% a.a.) selecionado!\n");
                break;
            case 2:
                taxaAnual = 0.09;
                printf("➡️  Fundo Imobiliário (9.0%% a.a.) selecionado!\n");
                break;
            case 3:
                taxaAnual = 0.11;
                printf("➡️  CDB/LCI (11.0%% a.a.) selecionado!\n");
                break;
            case 4:
                printf("Digite a taxa anual desejada (%%): ");
                scanf("%lf", &taxaAnual);
                taxaAnual /= 100.0; // Converte o valor percentual para decimal
                printf("➡️  Taxa Personalizada (%.2f%% a.a.) selecionada!\n", taxaAnual * 100);
                break;
            default:
                printf("❌ Opção inválida. Usando taxa padrão de 10%% a.a.\n");
                taxaAnual = 0.10;
                break;
        }

        // --- Início dos cálculos da simulação ---
        printf("\n================================================\n");
        printf("|        INICIANDO SIMULAÇÃO DE INVESTIMENTO   |\n");
        printf("================================================\n");

        valorAtual = investimentoInicial;       // Valor inicial aplicado
        meses = anosSimulacao * 12;             // Converte anos em meses
        double taxaMensal = taxaAnual / 12.0;   // Calcula a taxa mensal equivalente

        printf("📆 Duração: %d anos (%d meses)\n", anosSimulacao, meses);
        printf("💰 Taxa Mensal: %.4f%%\n", taxaMensal * 100);
        printf("-----------------------------------------------\n");

        // --- Laço de repetição para simular mês a mês ---
        for (int mes = 1; mes <= meses; mes++) {
            valorAtual = valorAtual * (1.0 + taxaMensal); // Aplica juros mensais
            if (mes > 1) { // A partir do segundo mês, adiciona o investimento mensal
                valorAtual += investMensal;
                capitalTotalInvestido += investMensal;
            }
            // Exibe o resultado ao final de cada ano
            if (mes % 12 == 0) {
                printf("📅 Ano %d: R$ %.2f\n", mes / 12, arredondar(valorAtual, 2));
            }
        }

        // --- Cálculo dos juros ganhos ---
        double jurosGanhos = valorAtual - capitalTotalInvestido;

        // --- Exibição dos resultados finais ---
        printf("\n===============================================\n");
        printf("|              RESULTADO FINAL                |\n");
        printf("===============================================\n");

        printf("💵 Investimento Inicial: R$ %.2f\n", arredondar(investimentoInicial, 2));
        printf("📈 Aporte Mensal: R$ %.2f\n", arredondar(investMensal, 2));
        printf("🕓 Tempo Total: %d anos\n", anosSimulacao);
        printf("💹 Taxa Anual: %.2f%%\n", taxaAnual * 100);
        printf("-----------------------------------------------\n");
        printf("💰 Capital Investido: R$ %.2f\n", arredondar(capitalTotalInvestido, 2));
        printf("💸 Juros Ganhos: R$ %.2f\n", arredondar(jurosGanhos, 2));
        printf("🏦 Montante Final: R$ %.2f\n", arredondar(valorAtual, 2));
        printf("-----------------------------------------------\n");
        printf("📢 Lembre-se: Esta é uma simulação. Os valores reais podem variar.\n");

        // --- Atualização dos totais gerais ---
        totalSimulacoes++;
        totalGeralInvestido += capitalTotalInvestido;
        totalGeralJuros += jurosGanhos;
        totalGeralFinal += valorAtual;

        // --- Exibição do resumo geral acumulado ---
        printf("\n===============================================\n");
        printf("|               RESUMO GERAL                  |\n");
        printf("===============================================\n");
        printf("➤ Simulações realizadas: %d\n", totalSimulacoes);
        printf("➤ Total investido: R$ %.2f\n", arredondar(totalGeralInvestido, 2));
        printf("➤ Total em juros ganhos: R$ %.2f\n", arredondar(totalGeralJuros, 2));
        printf("➤ Total acumulado geral: R$ %.2f\n", arredondar(totalGeralFinal, 2));

        // --- Pergunta se o usuário quer simular novamente ---
        printf("\nDeseja simular outro investimento? (1 - Sim / 2 - Não): ");
        scanf("%d", &repetir);
        system("clear || cls"); // Limpa tela antes da nova simulação
    }

    // --- Mensagem final de encerramento ---
    printf("\nObrigado por usar o Simulador de Investimentos! Até a próxima.\n");
    return 0;
}
