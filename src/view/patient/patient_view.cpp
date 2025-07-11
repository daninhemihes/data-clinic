#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_view.h"
#include "patient_controller.h"

void createPatientFromView(PatientListHeader* list){
    char name[100];
    char cpf[11];

    printf("Nome: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Cpf: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    addPatient(list, name, cpf);
    printf("Paciente adicionado.\n");
}

void patientMenu(PatientListHeader* list) {
    int choice;
    char name[100];
    char cpf[11];
    long id;

    while (1) {
        printf("\n===== MENU PACIENTES =====\n");
        printf("1. Adicionar paciente\n");
        printf("2. Listar pacientes\n");
        printf("3. Atualizar paciente\n");
        printf("4. Remover paciente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                createPatientFromView(list);
                break;

            case 2:
                printAllPatients(list);
                break;

            case 3:
                printf("ID do paciente a atualizar: ");
                scanf("%ld", &id);
                getchar();

                printf("Novo nome (deixe vazio para manter): ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Novo Cpf (deixe vazio para manter): ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = 0;

                if (updatePatientById(list, id,
                        strlen(name) > 0 ? name : NULL,
                        strlen(cpf) > 0 ? cpf : NULL)) {
                    printf("Paciente atualizado.\n");
                } else {
                    printf("Paciente não encontrado.\n");
                }
                break;

            case 4:
                printf("ID do paciente a remover: ");
                scanf("%ld", &id);
                getchar();
                if (removePatientById(list, id)) {
                    printf("Paciente removido.\n");
                } else {
                    printf("Paciente não encontrado.\n");
                }
                break;

            case 0:
                return;

            default:
                printf("Opção inválida.\n");
        }
    }
}
