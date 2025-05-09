#include <stdio.h>
#include "patient.h"
#include "patient_controller.h"
#include "patient_view.h"

void showLogo() {
    printf("\n");
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|           Gerenciamento de Pacientes          |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|  |_______________________                     |\n");
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
    initPatientList(&patientList);

    int choice;

    while (1) {
        printf("\n===== Selecione uma opção =====\n");
        printf("1. Gerenciar pacientes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                patientMenu(&patientList);
                break;
            case 0:
                freePatientList(&patientList);
                printf("Encerrando...\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}