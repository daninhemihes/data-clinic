#ifndef PATIENT_CONTROLLER_H
#define PATIENT_CONTROLLER_H

#include "patient.h"

void initPatientList(PatientListHeader* list);
void addPatient(PatientListHeader* list, const char* name, const char* diagnosis);
void printAllPatients(PatientListHeader* list);
int updatePatientById(PatientListHeader* list, long id, const char* newName, const char* newDiagnosis);
int removePatientById(PatientListHeader* list, long id);
void freePatientList(PatientListHeader* list);

#endif
