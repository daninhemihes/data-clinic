#ifndef PATIENT_QUEUE_H
#define PATIENT_QUEUE_H

#include "patient.h"
#include "triage.h"

typedef struct PatientQueueNode {
    Triage* triage;
    struct PatientQueueNode* next;
} PatientQueueNode;

typedef struct {
    PatientQueueNode* front;
    PatientQueueNode* rear;
} PatientQueue;

void initPatientQueue(PatientQueue* queue);
void enqueuePatient(PatientQueue* queue, Triage* triage);
Triage* dequeueNextPatient(PatientQueue* queue);
void freePatientQueue(PatientQueue* queue);
void printPatientQueue(PatientQueue* queue);

#endif