#ifndef PATIENT_QUEUE_CONTROLLER_H
#define PATIENT_QUEUE_CONTROLLER_H

#include "patient.h"
#include "patient_queue.h"

void adicionarNaFila(PatientQueue* queue, Triage* triage);
Triage* chamarProximoPaciente(PatientQueue* queue);

#endif
