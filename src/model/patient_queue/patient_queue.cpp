#include <stdio.h>
#include <stdlib.h>
#include "patient_queue.h"

void initQueue(PatientQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void enqueue(PatientQueue* queue, Triage* triage) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->triage = triage;
    node->next = NULL;

    if (queue->rear != NULL) {
        queue->rear->next = node;
    } else {
        queue->front = node;
    }

    queue->rear = node;
    queue->size++;

    sortQueueByPriority(queue);
}

Triage* dequeue(PatientQueue* queue) {
    if (queue->front == NULL) return NULL;

    QueueNode* temp = queue->front;
    Triage* triage = temp->triage;

    queue->front = temp->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;

    return triage;
}

Triage* peek(PatientQueue* queue) {
    if (queue->front == NULL) return NULL;
    return queue->front->triage;
}

void sortQueueByPriority(PatientQueue* queue) {
    if (queue->size < 2) return;

    int swapped;
    do {
        swapped = 0;
        QueueNode* current = queue->front;
        QueueNode* prev = NULL;

        while (current != NULL && current->next != NULL) {
            Triage* a = current->triage;
            Triage* b = current->next->triage;

            if (a->priority > b->priority) {
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    queue->front = current->next;
                }

                current->next = current->next->next;
                prev->next->next = current;

                swapped = 1;

                prev = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);

    QueueNode* temp = queue->front;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    queue->rear = temp;
}

void printQueue(PatientQueue* queue) {
    QueueNode* current = queue->front;
    printf("\n--- FILA DA UTI ---\n");
    while (current != NULL) {
        printTriage(current->triage);
        current = current->next;
    }
    printf("-------------------\n");
}

void freeQueue(PatientQueue* queue) {
    QueueNode* current = queue->front;
    while (current != NULL) {
        QueueNode* temp = current;
        current = current->next;
        free(temp);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}