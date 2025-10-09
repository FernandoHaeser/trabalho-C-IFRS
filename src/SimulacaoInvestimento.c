#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Variáveis globais
double totalGeralInvestido = 0.0;
double totalGeralJuros = 0.0;
double totalGeralFinal = 0.0;
int totalSimulacoes = 0;

// Função para arredondar com casas decimais
double arredondar(double valor, int casas) {
    double fator = pow(10, casas);
    return round(valor * fator) / fator;
}

int main() {
    int repetir = 1;

    while (repetir == 1) {
        double investimentoInicial;
        double investMensal;
        int anosSimulacao;
        double taxaAnual;
        double valorAtual;
        int meses;
        int opcaoInvestimento;
        double capitalTotalInvestido = 0.0;

        printf("==================================================\n");
        printf("|       SIMULADOR BÁSICO DE INVESTIMENTOS        |\n");
        printf("==================================================\n");

        printf("➤ Olá! Vamos simular o crescimento do seu dinheiro!\n\n");

        printf("Qual o valor que você vai investir inicialmente? R$ ");
        scanf("%lf", &investimentoInicial);
        capitalTotalInvestido += investimentoInicial;

        printf("Qual o valor que você pretende investir mensalmente? R$ ");
        scanf("%lf", &investMensal);

        printf("Por quantos anos você quer simular o investimento? ");
        scanf("%d", &anosSimulacao);

        system("clear || cls"); // limpa tela (Linux/Windows)

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

        system("clear || cls");

        printf("================================================\n");
        printf("|         ESCOLHA DO INVESTIMENTO              |\n");
        printf("================================================\n\n");

        switch (opcaoInvestimento) {
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
                taxaAnual /= 100.0;
                printf("➡️  Taxa Personalizada (%.2f%% a.a.) selecionada!\n", taxaAnual * 100);
                break;
            default:
                printf("❌ Opção inválida. Usando taxa padrão de 10%% a.a.\n");
                taxaAnual = 0.10;
                break;
        }

        printf("\n================================================\n");
        printf("|        INICIANDO SIMULAÇÃO DE INVESTIMENTO   |\n");
        printf("================================================\n");


        valorAtual = investimentoInicial;
        meses = anosSimulacao * 12;
        double taxaMensal = taxaAnual / 12.0;

        printf("📆 Duração: %d anos (%d meses)\n", anosSimulacao, meses);
        printf("💰 Taxa Mensal: %.4f%%\n", taxaMensal * 100);
        printf("-----------------------------------------------\n");

        for (int mes = 1; mes <= meses; mes++) {
            valorAtual = valorAtual * (1.0 + taxaMensal);
            if (mes > 1) {
                valorAtual += investMensal;
                capitalTotalInvestido += investMensal;
            }
            if (mes % 12 == 0) {
                printf("📅 Ano %d: R$ %.2f\n", mes / 12, arredondar(valorAtual, 2));
            }
        }

        double jurosGanhos = valorAtual - capitalTotalInvestido;

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

        // Atualizar totais
        totalSimulacoes++;
        totalGeralInvestido += capitalTotalInvestido;
        totalGeralJuros += jurosGanhos;
        totalGeralFinal += valorAtual;

        printf("\n===============================================\n");
        printf("|               RESUMO GERAL                  |\n");
        printf("===============================================\n");

        printf("➤ Simulações realizadas: %d\n", totalSimulacoes);
        printf("➤ Total investido: R$ %.2f\n", arredondar(totalGeralInvestido, 2));
        printf("➤ Total em juros ganhos: R$ %.2f\n", arredondar(totalGeralJuros, 2));
        printf("➤ Total acumulado geral: R$ %.2f\n", arredondar(totalGeralFinal, 2));

        printf("\nDeseja simular outro investimento? (1 - Sim / 2 - Não): ");
        scanf("%d", &repetir);
        system("clear || cls");
    }

    printf("\nObrigado por usar o Simulador de Investimentos! Até a próxima.\n");
    return 0;
}