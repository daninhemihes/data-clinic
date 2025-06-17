#include "patient_queue_view.h"
#include "patient_queue_controller.h"
#include <stdio.h>

void mostrarFilaAtual(PatientQueue* queue) {
    printf("Fila de pacientes por prioridade:\n");
    printPatientQueue(queue);
}

void patientQueueMenu(PatientQueue* queue) {
    int option;
    while (1) {
        printf("\n--- Fila de Atendimento ---\n");
        printf("1. Ver fila\n");
        printf("2. Chamar próximo paciente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                mostrarFilaAtual(queue);
                break;
            case 2: {
                Triage* next = chamarProximoPaciente(queue);
                if (next) {
                    const char* name = next->patient ? next->patient->name : "(desconhecido)";
                    printf("Chamando paciente: %s (Prioridade %d)\n",
                           name, next->priority);
                } else {
                    printf("Fila vazia.\n");
                }
                break;
            }
            case 0:
                return;
            default:
                printf("Opção inválida.\n");
        }
    }
}