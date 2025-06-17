#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triage_view.h"
#include "triage_controller.h"
#include "patient_controller.h"
#include "patient.h"
#include "patient_view.h"

long getPatientId(PatientListHeader* list, const char* cpf){
    Patient* patient = NULL;

    patient = getPatientByCpf(list, cpf);

    if(patient != NULL){
        printf("Paciente encontrado: \n ");
        printPatient(patient);
        return patient->id;
    }
    else 
    {
        printf("Paciente não encontrado. Cadastre agora o paciente: \n");
        createPatientFromView(list);
        return getPatientId(list, cpf);
    }
}

void triageMenu(TriageListHeader* list, PatientListHeader* patientsList) {
    int choice;
    long id, patientId;
    char patientCpf[11];
    char description[200];

    int systolic, diastolic, heartRate, oxygenSaturation, painScale;
    float temperature;

    while (1) {
        printf("\n===== MENU TRIAGEM =====\n");
        printf("1. Adicionar triagem\n");
        printf("2. Listar triagens\n");
        printf("3. Atualizar triagem\n");
        printf("4. Remover triagem\n");
        printf("5. Mostrar fila de atendimento (Protocolo de Manchester)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Digite o CPF do paciente (sem ponto ou hífen): ");
                fgets(patientCpf, sizeof(patientCpf), stdin);
                patientCpf[strcspn(patientCpf, "\n")] = 0;
                getchar();
                patientId = getPatientId(patientsList, patientCpf);

                printf("Pressão sistólica (mmHg): ");
                scanf("%d", &systolic);
                getchar();

                printf("Pressão diastólica (mmHg): ");
                scanf("%d", &diastolic);
                getchar();

                printf("Frequência cardíaca (bpm): ");
                scanf("%d", &heartRate);
                getchar();

                printf("Temperatura corporal (°C): ");
                scanf("%f", &temperature);
                getchar();

                printf("Saturação de oxigênio (%%): ");
                scanf("%d", &oxygenSaturation);
                getchar();

                printf("Escala de dor (0-10): ");
                scanf("%d", &painScale);
                getchar();

                printf("Descrição: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0;

                addTriage(
                    list,
                    patientId,
                    systolic,
                    diastolic,
                    heartRate,
                    temperature,
                    oxygenSaturation,
                    painScale,
                    description
                );
                printf("Triagem adicionada.\n");
                break;

            case 2:
                printAllTriages(list);
                break;

            case 3:
                printf("ID da triagem a atualizar: ");
                scanf("%ld", &id);
                getchar();

                printf("Nova pressão sistólica (-1 para manter): ");
                scanf("%d", &systolic);
                getchar();

                printf("Nova pressão diastólica (-1 para manter): ");
                scanf("%d", &diastolic);
                getchar();

                printf("Nova frequência cardíaca (-1 para manter): ");
                scanf("%d", &heartRate);
                getchar();

                printf("Nova temperatura (-1 para manter): ");
                scanf("%f", &temperature);
                getchar();

                printf("Nova saturação de oxigênio (-1 para manter): ");
                scanf("%d", &oxygenSaturation);
                getchar();

                printf("Nova escala de dor (-1 para manter): ");
                scanf("%d", &painScale);
                getchar();

                printf("Nova descrição (deixe vazio para manter): ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0;

                if (updateTriageById(
                        list,
                        id,
                        systolic >= 0 ? &systolic : NULL,
                        diastolic >= 0 ? &diastolic : NULL,
                        heartRate >= 0 ? &heartRate : NULL,
                        temperature >= 0 ? &temperature : NULL,
                        oxygenSaturation >= 0 ? &oxygenSaturation : NULL,
                        painScale >= 0 ? &painScale : NULL,
                        (PriorityLevel)0,
                        strlen(description) > 0 ? description : NULL)) {
                    printf("Triagem atualizada.\n");
                } else {
                    printf("Triagem não encontrada.\n");
                }
                break;

            case 4:
                printf("ID da triagem a remover: ");
                scanf("%ld", &id);
                getchar();
                if (removeTriageById(list, id)) {
                    printf("Triagem removida.\n");
                } else {
                    printf("Triagem não encontrada.\n");
                }
                break;
            case 5:
                
                break;
            case 0:
                return;

            default:
                printf("Opção inválida.\n");
        }
    }
}
