#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "financeiro_lib.c"

// Função auxiliar para comparar doubles
int quaseIgual(double a, double b, double tol) {
    return fabs(a - b) < tol;
}

void testarFinanceiro() {
    printf("=== TESTES FINANCEIRO ===\n");

    // Caso 1: apenas investimento inicial
    double r1 = simularInvestimento(1000, 0, 1, 0.12); // 12% a.a.
    assert(quaseIgual(r1, 1126.82, 1.0));

    // Caso 2: aporte mensal
    double r2 = simularInvestimento(1000, 100, 2, 0.10); // 10% a.a.
    assert(r2 > 3800 && r2 < 4200);

    // Caso 3: zero inicial, só aportes
    double r3 = simularInvestimento(0, 200, 3, 0.09); // 9% a.a.
    assert(r3 > 7600 && r3 < 8400);

    printf("✅ Todos os testes financeiros passaram!\n");
}

int main() {
    testarFinanceiro();
    return 0;
}
