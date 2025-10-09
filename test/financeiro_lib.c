// Classe para os teste de test_financeiro.c

#include <math.h>

double simularInvestimento(double inicial, double mensal, int anos, double taxaAnual) {
    double valor = inicial;
    double taxaMensal = taxaAnual / 12.0;
    int meses = anos * 12;
    double capitalTotal = inicial;

    for (int i = 1; i <= meses; i++) {
        valor *= (1.0 + taxaMensal);
        if (i > 1) {
            valor += mensal;
            capitalTotal += mensal;
        }
    }
    return valor;
}
