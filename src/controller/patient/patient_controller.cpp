#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_controller.h"

void initPatientList(PatientListHeader* list) {
    list->top = NULL;
    list->end = NULL;
    list->lastId = 0;
}

void addPatient(PatientListHeader* list, const char* name, const char* cpf) {
    Patient* newPatient = createPatient(++list->lastId, name, cpf);

    if (list->top == NULL) {
        list->top = newPatient;
        list->end = newPatient;
    } else {
        list->end->next = newPatient;
        newPatient->prev = list->end;
        list->end = newPatient;
    }
    savePatientsToFile(list, "patients.dat");
}

Patient* getPatientById(PatientListHeader* list, long id) {
    Patient* current = list->top;
    while (current != NULL) {
        if (current->id == id)
            return current;
        
        current = current->next;
    }
    return NULL;
}

Patient* getPatientByCpf(PatientListHeader* list, const char* cpf) {
    Patient* current = list->top;
    while (current != NULL) {
        if (strcmp(current->cpf, cpf) == 0)
            return current;
        
        current = current->next;
    }
    return NULL;
}

void printAllPatients(PatientListHeader* list) {
    Patient* current = list->top;
    while (current != NULL) {
        printPatient(current);
        printf("-------------\n");
        current = current->next;
    }
}

int updatePatientById(PatientListHeader* list, long id, const char* newName, const char* newCpf) {
  Patient* current = list->top;
    while (current != NULL) {
        if (current->id == id) {
            if (newName != NULL) {
                strncpy(current->name, newName, sizeof(current->name));
                current->name[sizeof(current->name)-1] = '\0';
            }
            if (newCpf != NULL) {
                strncpy(current->cpf, newCpf, sizeof(current->cpf));
                current->cpf[sizeof(current->cpf)-1] = '\0';
            }
            savePatientsToFile(list, "patients.dat");
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
            savePatientsToFile(list, "patients.dat");
            return 1;
        }
        current = current->next;
    }
    return 0;
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

void savePatientsToFile(PatientListHeader* list, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    fwrite(&list->lastId, sizeof(long), 1, file);

    Patient* current = list->top;
    while (current != NULL) {
        fwrite(current, sizeof(Patient), 1, file);
        current = current->next;
    }

    fclose(file);
}

void loadPatientsFromFile(PatientListHeader* list, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return;
    }

    fread(&list->lastId, sizeof(long), 1, file);

    Patient temp;
    while (fread(&temp, sizeof(Patient), 1, file)) {
        Patient* newPatient = (Patient*)malloc(sizeof(Patient));
        *newPatient = temp;
        newPatient->prev = list->end;
        newPatient->next = NULL;

        if (list->top == NULL)
            list->top = newPatient;
        else
            list->end->next = newPatient;

        list->end = newPatient;
    }

    fclose(file);
}