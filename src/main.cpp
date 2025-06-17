#include <stdio.h>
#include "patient.h"
#include "triage.h"
#include "patient_controller.h"
#include "triage_controller.h"
#include "patient_view.h"
#include "triage_view.h"
#include "patient_queue.h"
#include "patient_queue_controller.h"
#include "patient_queue_view.h"

void showLogo() {
    printf("\n");
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|           Gerenciamento de Pacientes          |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|          |_______________                     |\n");
    printf("|  |_______|  |  |  |  |  |  |  |  |__          |\n");
    printf("|  |_______|  6  5  4  3  3  2  1  |__|-------  |\n");
    printf("|  |       |_______________________|            |\n");
    printf("|          |                                    |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");
}


int main() {
    showLogo();

    PatientListHeader patientList;
    TriageListHeader triageList;
    PatientQueue queue;

    initPatientList(&patientList);
    loadPatientsFromFile(&patientList, "patients.dat");
    initTriageList(&triageList);
    loadTriagesFromFile(&triageList, "triages.dat");
    resolveTriagePatients(&triageList, &patientList);
    initPatientQueue(&queue);

    int choice;

    while (1) {
        printf("\n===== Selecione uma opção =====\n");
        printf("1. Gerenciar pacientes\n");
        printf("2. Gerenciar triagens\n");
        printf("3. Gerenciar fila de atendimento\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                patientMenu(&patientList);
                break;
            case 2:
                triageMenu(&triageList, &patientList, &queue);
                break;
            case 3:
                patientQueueMenu(&queue);
                break;
            case 0:
                freePatientList(&patientList);
                freeTriageList(&triageList);
                printf("Encerrando...\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    savePatientsToFile(&patientList, "patients.dat");
    saveTriagesToFile(&triageList, "triages.dat");
    return 0;
}