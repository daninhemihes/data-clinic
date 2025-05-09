#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_controller.h"

void initPatientList(PatientListHeader* list) {
    list->top = NULL;
    list->end = NULL;
    list->lastId = 0;
}

void addPatient(PatientListHeader* list, const char* name, const char* diagnosis) {
    Patient* newPatient = createPatient(++list->lastId, name, diagnosis);

    if (list->top == NULL) {
        list->top = newPatient;
        list->end = newPatient;
    } else {
        list->end->next = newPatient;
        newPatient->prev = list->end;
        list->end = newPatient;
    }
}

void printAllPatients(PatientListHeader* list) {
    Patient* current = list->top;
    while (current != NULL) {
        printPatient(current);
        printf("-------------\n");
        current = current->next;
    }
}

int updatePatientById(PatientListHeader* list, long id, const char* newName, const char* newDiagnosis) {
  Patient* current = list->top;
    while (current != NULL) {
        if (current->id == id) {
            if (newName != NULL) {
                strncpy(current->name, newName, sizeof(current->name));
                current->name[sizeof(current->name)-1] = '\0';
            }
            if (newDiagnosis != NULL) {
                strncpy(current->diagnosis, newDiagnosis, sizeof(current->diagnosis));
                current->diagnosis[sizeof(current->diagnosis)-1] = '\0';
            }
            return 1; // Sucesso
        }
        current = current->next;
    }
    return 0; // Não encontrado
}

int removePatientById(PatientListHeader* list, long id) {
    Patient* current = list->top;
    while (current != NULL) {
        if (current->id == id) {
            if (current->prev) current->prev->next = current->next;
            else list->top = current->next;

            if (current->next) current->next->prev = current->prev;
            else list->end = current->prev;

            freePatient(current);
            return 1; // Sucesso
        }
        current = current->next;
    }
    return 0; // Não encontrado
}

void freePatientList(PatientListHeader* list) {
    Patient* current = list->top;
    while (current != NULL) {
        Patient* next = current->next;
        freePatient(current);
        current = next;
    }
    list->top = NULL;
    list->end = NULL;
    list->lastId = 0;
}