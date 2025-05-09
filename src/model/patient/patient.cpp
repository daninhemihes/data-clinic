#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"

Patient* createPatient(long id, const char* name, const char* diagnosis) {
    Patient* p = (Patient*)malloc(sizeof(Patient));

    p->id = id;
    strcpy(p->name, name);
    strcpy(p->diagnosis, diagnosis);

    p->prev = NULL;
    p->next = NULL;
    
    return p;
}

void printPatient(Patient* p) {
    printf("Nome: %s\nDiagnóstico: %s\n", p->name, p->diagnosis);
}

void freePatient(Patient* p) {
    free(p);
}