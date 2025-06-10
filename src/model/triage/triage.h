#ifndef TRIAGE_H
#define TRIAGE_H

#include "patient.h"

typedef enum {
    EMERGENCY = 1,
    URGENT = 2,
    LESS_URGENT = 3,
    NON_URGENT = 4
} PriorityLevel;

typedef struct {
    long id;
    long patientId;
    Patient* patient;
    PriorityLevel priority;
    char description[200];

    int bloodPressureSystolic;
    int bloodPressureDiastolic;
    int heartRate;
    float bodyTemperature;
    int oxygenSaturation;
    int painScale;
} Triage;

typedef struct TriageNode {
    Triage* data;
    struct TriageNode* next;
    struct TriageNode* prev;
} TriageNode;

typedef struct {
    TriageNode* top;
    TriageNode* end;
    long lastId;
} TriageListHeader;

// Funções utilitárias
Triage* createTriage(
    long patientId,
    int bloodPressureSystolic,
    int bloodPressureDiastolic,
    int heartRate,
    float bodyTemperature,
    int oxygenSaturation,
    int painScale,
    const char* description
);
void printTriage(Triage* t);
void freeTriage(Triage* t);
PriorityLevel calculatePriority(Triage* t);

#endif