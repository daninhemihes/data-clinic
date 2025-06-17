#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"

Patient* createPatient(long id, const char* name, const char* cpf) {
    Patient* p = (Patient*)malloc(sizeof(Patient));

    p->id = id;
    strcpy(p->name, name);
    strcpy(p->cpf, cpf);

    p->prev = NULL;
    p->next = NULL;
    
    return p;
}

void printPatient(Patient* p) {
    printf("Id: %ld\nNome: %s\nCpf: %s\n", p->id, p->name, p->cpf);
}

void freePatient(Patient* p) {
    free(p);
}