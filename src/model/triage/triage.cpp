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
    int score = 0;

    if (t->bloodPressureSystolic < 90 || t->bloodPressureSystolic > 180) score += 3;
    else if (t->bloodPressureSystolic < 100 || t->bloodPressureSystolic > 160) score += 2;
    else if (t->bloodPressureSystolic < 110 || t->bloodPressureSystolic > 140) score += 1;

    if (t->bloodPressureDiastolic < 60 || t->bloodPressureDiastolic > 110) score += 2;
    else if (t->bloodPressureDiastolic < 70 || t->bloodPressureDiastolic > 100) score += 1;

    if (t->heartRate < 50 || t->heartRate > 130) score += 3;
    else if (t->heartRate < 60 || t->heartRate > 110) score += 2;
    else if (t->heartRate < 70 || t->heartRate > 100) score += 1;

    if (t->bodyTemperature < 35.0 || t->bodyTemperature > 39.0) score += 3;
    else if (t->bodyTemperature < 36.0 || t->bodyTemperature > 38.0) score += 2;
    else if (t->bodyTemperature < 36.5 || t->bodyTemperature > 37.5) score += 1;

    if (t->oxygenSaturation < 85) score += 4;
    else if (t->oxygenSaturation < 90) score += 3;
    else if (t->oxygenSaturation < 95) score += 2;

    if (t->painScale >= 8) score += 2;
    else if (t->painScale >= 5) score += 1;

    if (score >= 10) return EMERGENCY;
    if (score >= 7) return URGENT;
    if (score >= 4) return LESS_URGENT;
    return NON_URGENT;
}