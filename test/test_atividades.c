#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/AtividadesFisicas.c"   // inclui seu código

// Função auxiliar para inserir registros sem usar scanf
void inserirAtividade(const char* titulo, const char* tipo, float cal, float tempo, int freq, float ritmo) {
    strcpy(titulo_atividade[contador_registros], titulo);
    strcpy(tipo_atividade[contador_registros], tipo);
    calorias[contador_registros] = cal;
    tempo_minutos[contador_registros] = tempo;
    freq_cardiaca_media[contador_registros] = freq;
    ritmo_medio[contador_registros] = ritmo;
    contador_registros++;
}

void testarAtividades() {
    printf("=== TESTES ATIVIDADES FÍSICAS ===\n");

    // Reset
    contador_registros = 0;

    inserirAtividade("Corrida manhã", "Corrida", 300, 30, 150, 10);
    inserirAtividade("Musculação peito", "Musculação", 200, 45, 120, 50);
    inserirAtividade("Yoga relax", "Yoga", 100, 60, 90, 0);
    inserirAtividade("Natação treino", "Natação", 400, 40, 140, 20);
    inserirAtividade("Caminhada parque", "Caminhada", 150, 50, 100, 6);

    // Testar total de registros
    assert(contador_registros == 5);

    // Testar valores individuais
    assert(strcmp(titulo_atividade[0], "Corrida manhã") == 0);
    assert(calorias[1] == 200);
    assert(freq_cardiaca_media[2] == 90);
    assert(ritmo_medio[4] == 6);

    // Testar médias
    float somaCalorias = 0;
    for (int i = 0; i < contador_registros; i++) somaCalorias += calorias[i];
    assert(somaCalorias == (300 + 200 + 100 + 400 + 150));

    printf("✅ Todos os testes de atividades passaram!\n");
}

int main() {
    testarAtividades();
    return 0;
}