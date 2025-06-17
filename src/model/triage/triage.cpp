#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triage.h"
#include "patient.h"

Triage* createTriage(
    long patientId,
    int bloodPressureSystolic,
    int bloodPressureDiastolic,
    int heartRate,
    float bodyTemperature,
    int oxygenSaturation,
    int painScale,
    const char* description
) {
    Triage* t = (Triage*)malloc(sizeof(Triage));
    if (t == NULL) {
        perror("Erro ao alocar triagem");
        exit(1);
    }

    t->id = 0;
    t->patientId = patientId;
    t->patient = NULL;
    t->priority = NON_URGENT;

    strncpy(t->description, description, sizeof(t->description));
    t->description[sizeof(t->description) - 1] = '\0';

    t->bloodPressureSystolic = bloodPressureSystolic;
    t->bloodPressureDiastolic = bloodPressureDiastolic;
    t->heartRate = heartRate;
    t->bodyTemperature = bodyTemperature;
    t->oxygenSaturation = oxygenSaturation;
    t->painScale = painScale;

    return t;
}

void printTriage(Triage* t) {
    if (t == NULL) return;

    printf("\n--- Triagem ID %ld ---\n", t->id);
    printf("ID Paciente: %ld\n", t->patientId);
    printf("Pressão: %d/%d mmHg\n", t->bloodPressureSystolic, t->bloodPressureDiastolic);
    printf("Frequência cardíaca: %d bpm\n", t->heartRate);
    printf("Temperatura: %.1f °C\n", t->bodyTemperature);
    printf("Saturação O2: %d %%\n", t->oxygenSaturation);
    printf("Escala de dor: %d\n", t->painScale);
    printf("Prioridade: %d\n", t->priority);
    printf("Descrição: %s\n", t->description);
}

void freeTriage(Triage* t) {
    if (t != NULL) {
        free(t);
    }
}

PriorityLevel calculatePriority(Triage* t) {
    if (t == NULL) return BLUE; // Retorna prioridade mais baixa se triagem for inválida

    // 1. Critérios para VERMELHO (Emergência - atendimento imediato)
    if (t->oxygenSaturation < 85 || 
        t->heartRate < 40 || 
        t->heartRate > 140 ||
        t->bloodPressureSystolic < 80 ||
        t->bloodPressureDiastolic < 50 ||
        t->bodyTemperature > 40.0 ||
        t->bodyTemperature < 34.0) {
        return RED;
    }

    // 2. Critérios para LARANJA (Muito urgente - atendimento em 10 min)
    if (t->oxygenSaturation < 90 ||
        t->heartRate < 50 || 
        t->heartRate > 120 ||
        t->bloodPressureSystolic > 200 ||
        t->bloodPressureDiastolic > 120 ||
        t->bodyTemperature > 39.0 ||
        t->bodyTemperature < 35.0 ||
        t->painScale >= 8) {
        return ORANGE;
    }

    // 3. Critérios para AMARELO (Urgente - atendimento em 60 min)
    if (t->oxygenSaturation < 95 ||
        t->heartRate < 60 || 
        t->heartRate > 100 ||
        t->bloodPressureSystolic > 180 ||
        t->bloodPressureDiastolic > 110 ||
        t->bodyTemperature > 38.0 ||
        t->bodyTemperature < 36.0 ||
        (t->painScale >= 5 && t->painScale <= 7)) {
        return YELLOW;
    }

    // 4. Critérios para VERDE (Pouco urgente - atendimento em 120 min)
    if (t->oxygenSaturation < 98 ||
        t->heartRate < 70 || 
        t->heartRate > 90 ||
        t->bloodPressureSystolic > 140 ||
        t->bloodPressureDiastolic > 90 ||
        t->bodyTemperature > 37.5 ||
        t->bodyTemperature < 36.5 ||
        (t->painScale >= 3 && t->painScale <= 4)) {
        return GREEN;
    }

    // 5. AZUL (Não urgente - atendimento em 240 min) - todos os outros casos
    return BLUE;
}