#ifndef PATIENT_CONTROLLER_H
#define PATIENT_CONTROLLER_H

#include "patient.h"

void initPatientList(PatientListHeader* list);
void addPatient(PatientListHeader* list, const char* name, const char* cpf);
Patient* getPatientById(PatientListHeader* list, long id);
Patient* getPatientByCpf(PatientListHeader* list, const char* cpf);
void printAllPatients(PatientListHeader* list);
int updatePatientById(PatientListHeader* list, long id, const char* newName, const char* newCpf);
int removePatientById(PatientListHeader* list, long id);
void freePatientList(PatientListHeader* list);

#endif
