#ifndef PATIENT_QUEUE_H
#define PATIENT_QUEUE_H

#include "triage.h"

typedef struct QueueNode {
    Triage* triage;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} PatientQueue;

void initQueue(PatientQueue* queue);
void enqueue(PatientQueue* queue, Triage* triage);
Triage* dequeue(PatientQueue* queue);
Triage* peek(PatientQueue* queue);
void sortQueueByPriority(PatientQueue* queue);
void printQueue(PatientQueue* queue);
void freeQueue(PatientQueue* queue);

#endif