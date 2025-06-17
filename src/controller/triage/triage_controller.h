#ifndef TRIAGE_CONTROLLER_H
#define TRIAGE_CONTROLLER_H

#include "triage.h"
#include "patient_queue.h"

void initTriageList(TriageListHeader* list);
void freeTriageList(TriageListHeader* list);

Triage* addTriage(
    TriageListHeader* list,
    PatientQueue* queue,
    long patientId,
    int bloodPressureSystolic,
    int bloodPressureDiastolic,
    int heartRate,
    float bodyTemperature,
    int oxygenSaturation,
    int painScale,
    const char* description
);

int removeTriageById(TriageListHeader* list, long id);

int updateTriageById(
    TriageListHeader* list,
    long id,
    const int* bloodPressureSystolic,
    const int* bloodPressureDiastolic,
    const int* heartRate,
    const float* bodyTemperature,
    const int* oxygenSaturation,
    const int* painScale,
    PriorityLevel priority,
    const char* description
);

Triage* findTriageById(TriageListHeader* list, long id);
void printAllTriages(TriageListHeader* list);
void saveTriagesToFile(TriageListHeader* list, const char* filename);
void loadTriagesFromFile(TriageListHeader* list, const char* filename);
void resolveTriagePatients(TriageListHeader* triageList, PatientListHeader* patientList);

#endif