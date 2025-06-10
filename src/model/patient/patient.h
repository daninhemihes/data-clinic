#ifndef PATIENT_H
#define PATIENT_H

typedef struct Patient {
    long id;
    char name[100];
    char cpf[11];

    struct Patient* prev;
    struct Patient* next;
} Patient;

typedef struct PatientListHeader {
    struct Patient *top;
    struct Patient *end;
    long lastId;
} PatientListHeader;

Patient* createPatient(long id, const char* name, const char* cpf);
void printPatient(Patient* p);
void freePatient(Patient* p);

#endif