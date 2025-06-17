#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triage_controller.h"
#include "triage_queue.h"
#include "triage_queue_view.h"

void initTriageList(TriageListHeader* list) {
    list->top = NULL;
    list->end = NULL;
    list->lastId = 0;
}

void freeTriageList(TriageListHeader* list) {
    TriageNode* current = list->top;
    while (current != NULL) {
        TriageNode* temp = current;
        current = current->next;
        freeTriage(temp->data);
        free(temp);
    }
    list->top = NULL;
    list->end = NULL;
    list->lastId = 0;
}

Triage* addTriage(
    TriageListHeader* list,
    long patientId,
    int bloodPressureSystolic,
    int bloodPressureDiastolic,
    int heartRate,
    float bodyTemperature,
    int oxygenSaturation,
    int painScale,
    const char* description
) {
    Triage* t = createTriage(
        patientId,
        bloodPressureSystolic,
        bloodPressureDiastolic,
        heartRate,
        bodyTemperature,
        oxygenSaturation,
        painScale,
        description
    );
    t->id = ++list->lastId;
    t->priority = calculatePriority(t); 
    TriageNode* node = (TriageNode*)malloc(sizeof(TriageNode));
    node->data = t;
    node->next = NULL;
    node->prev = list->end;

    if (list->end != NULL) {
        list->end->next = node;
    } else {
        list->top = node;
    }

    list->end = node;

    return t;
}

int removeTriageById(TriageListHeader* list, long id) {
    TriageNode* current = list->top;

    while (current != NULL) {
        if (current->data->id == id) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                list->top = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                list->end = current->prev;
            }

            freeTriage(current->data);
            free(current);
            return 1;
        }
        current = current->next;
    }

    return 0;
}

Triage* findTriageById(TriageListHeader* list, long id) {
    TriageNode* current = list->top;

    while (current != NULL) {
        if (current->data->id == id) {
            return current->data;
        }
        current = current->next;
    }

    return NULL;
}

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
) {
    Triage* t = findTriageById(list, id);
    if (t == NULL) return 0;

    if (bloodPressureSystolic) t->bloodPressureSystolic = *bloodPressureSystolic;
    if (bloodPressureDiastolic) t->bloodPressureDiastolic = *bloodPressureDiastolic;
    if (heartRate) t->heartRate = *heartRate;
    if (bodyTemperature) t->bodyTemperature = *bodyTemperature;
    if (oxygenSaturation) t->oxygenSaturation = *oxygenSaturation;
    if (painScale) t->painScale = *painScale;
    if (description) strncpy(t->description, description, sizeof(t->description) - 1);
    t->priority = priority;

    return 1;
}

void printAllTriages(TriageListHeader* list) {
    TriageNode* current = list->top;

    while (current != NULL) {
        printTriage(current->data);
        current = current->next;
    }
}

void listOrderedTriages(TriageListHeader* list) {
    return;
    // TriageQueue queue;
    // TriageNode* current = list->top; 

    // while (current != nullptr) {
    //     queue.enqueue(current);
    //     current = current->next;
    // }

    // // Mostrar na linha de comando
    // queue.print();

    // // Mostrar na janela GUI
    // showTriageQueueGUI(&queue);
}