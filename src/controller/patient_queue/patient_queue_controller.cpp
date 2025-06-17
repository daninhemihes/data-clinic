#include "patient_queue_controller.h"
#include "patient_queue.h"

void adicionarNaFila(PatientQueue* queue, Triage* triage) {
    enqueuePatient(queue, triage);
}

Triage* chamarProximoPaciente(PatientQueue* queue) {
    return dequeueNextPatient(queue);
}
