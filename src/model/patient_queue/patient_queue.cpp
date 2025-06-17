#include "patient_queue.h"
#include <stdlib.h>
#include <stdio.h>

void initPatientQueue(PatientQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

void enqueuePatient(PatientQueue* queue, Triage* triage) {
    PatientQueueNode* newNode = (PatientQueueNode*)malloc(sizeof(PatientQueueNode));
    newNode->triage = triage;
    newNode->next = NULL;

    if (!queue->front || triage->priority < queue->front->triage->priority) {
        newNode->next = queue->front;
        queue->front = newNode;
        if (!queue->rear) queue->rear = newNode;
        return;
    }

    PatientQueueNode* current = queue->front;
    while (current->next && current->next->triage->priority <= triage->priority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    if (!newNode->next) queue->rear = newNode;
}

Triage* dequeueNextPatient(PatientQueue* queue) {
    if (!queue->front) return NULL;

    PatientQueueNode* temp = queue->front;
    Triage* triage = temp->triage;
    queue->front = temp->next;
    if (!queue->front) queue->rear = NULL;
    free(temp);
    return triage;
}

void freePatientQueue(PatientQueue* queue) {
    while (queue->front) {
        PatientQueueNode* temp = queue->front;
        queue->front = temp->next;
        free(temp);
    }
}

void printPatientQueue(PatientQueue* queue) {
    PatientQueueNode* current = queue->front;
    while (current) {
        const char* name = current->triage->patient ? current->triage->patient->name : "(desconhecido)";
        printf("Paciente: %s | Prioridade: %d\n", name, current->triage->priority);
        current = current->next;
    }
}