#include <stdio.h>
#include <string.h>

#define ARQUIVO "consultasIdosos.txt"

int main() {
    int opcao, especialidade, encontrado, contador;
    char nome[100], data[20], hora[10], tipo[20], lembrete[200], busca[100];

    printf("\n=== AGENDA OFTALMOLOGICA 60+ ===\n");
    printf("1. Cadastrar Consulta\n");
    printf("2. Ver Consultas Agendadas\n");
    printf("3. Buscar por Nome do Paciente\n");
    printf("0. Sair\n");
    printf("opcao --> ");
    scanf("%d", &opcao);

    while (opcao != 0) {

        while (opcao < 0 || opcao > 3) {
            printf("OPCAO INEXISTENTE.\n");
            printf("\n=== AGENDA OFTALMOLOGICA 60+ ===\n");
            printf("1. Cadastrar Consulta\n");
            printf("2. Ver Consultas Agendadas\n");
            printf("3. Buscar por Nome do Paciente\n");
            printf("0. Sair\n");
            printf("opcao --> ");
            scanf("%d", &opcao);
        }

        switch (opcao) {

            case 1:
                printf("\n--- CADASTRAR CONSULTA ---\n");

                printf("Nome do paciente: ");
                scanf(" %[^\n]", nome);

                printf("Data da consulta (ex: 10/06/2026): ");
                scanf(" %[^\n]", data);

                printf("Hora da consulta (ex: 14:30): ");
                scanf(" %[^\n]", hora);

                printf("\nEspecialidade:\n");
                printf("1. Refracao\n");
                printf("2. Glaucoma\n");
                printf("3. Retina\n");
                printf("4. VSN\n");
                printf("opcao --> ");
                scanf("%d", &especialidade);

                while (especialidade < 1 || especialidade > 4) {
                    printf("OPCAO INEXISTENTE.\n");
                    printf("opcao --> ");
                    scanf("%d", &especialidade);
                }

                switch (especialidade) {
                    case 1: strcpy(tipo, "Refracao"); break;
                    case 2: strcpy(tipo, "Glaucoma"); break;
                    case 3: strcpy(tipo, "Retina");   break;
                    case 4: strcpy(tipo, "VSN");      break;
                }

                printf("Lembrete / observacao (ex: levar oculos, retorno, etc): ");
                scanf(" %[^\n]", lembrete);

                FILE *arqCad = fopen(ARQUIVO, "a");
                fprintf(arqCad, "%s;%s;%s;%s;%s\n", nome, data, hora, tipo, lembrete);
                fclose(arqCad);

                printf("Consulta cadastrada com sucesso!\n");
                break;

            case 2:
                contador = 0;
                printf("\n--- CONSULTAS AGENDADAS ---\n");

                FILE *arqList = fopen(ARQUIVO, "r");

                if (arqList == NULL) {
                    printf("Nenhuma consulta cadastrada ainda.\n");
                } else {
                    while (fscanf(arqList, "%99[^;];%19[^;];%9[^;];%19[^;];%199[^\n]\n",
                                  nome, data, hora, tipo, lembrete) == 5) {
                        contador++;
                        printf("\n[%d]\n", contador);
                        printf("  Paciente     : %s\n", nome);
                        printf("  Data         : %s\n", data);
                        printf("  Hora         : %s\n", hora);
                        printf("  Especialidade: %s\n", tipo);
                        printf("  Lembrete     : %s\n", lembrete);
                    }

                    if (contador == 0)
                        printf("Nenhuma consulta encontrada.\n");
                    else
                        printf("\nTotal: %d consulta(s) agendada(s).\n", contador);

                    fclose(arqList);
                }
                break;

            case 3:
                encontrado = 0;
                printf("\n--- BUSCAR POR NOME ---\n");
                printf("Digite o nome do paciente: ");
                scanf(" %[^\n]", busca);

                FILE *arqBus = fopen(ARQUIVO, "r");

                if (arqBus == NULL) {
                    printf("Nenhuma consulta cadastrada ainda.\n");
                } else {
                    while (fscanf(arqBus, "%99[^;];%19[^;];%9[^;];%19[^;];%199[^\n]\n",
                                  nome, data, hora, tipo, lembrete) == 5) {
                        if (strstr(nome, busca) != NULL) {
                            encontrado++;
                            printf("\nResultado %d:\n", encontrado);
                            printf("  Paciente     : %s\n", nome);
                            printf("  Data         : %s\n", data);
                            printf("  Hora         : %s\n", hora);
                            printf("  Especialidade: %s\n", tipo);
                            printf("  Lembrete     : %s\n", lembrete);
                        }
                    }

                    if (encontrado == 0)
                        printf("Nenhum paciente encontrado com esse nome.\n");

                    fclose(arqBus);
                }
                break;
        }

        printf("\n=== AGENDA OFTALMOLOGICA 60+ ===\n");
        printf("1. Cadastrar Consulta\n");
        printf("2. Ver Consultas Agendadas\n");
        printf("3. Buscar por Nome do Paciente\n");
        printf("0. Sair\n");
        printf("opcao --> ");
        scanf("%d", &opcao);
    }

    printf("Encerrando o sistema. Ate logo!\n");
    printf("FIM DE PROGRAMA.");
    return 0;
}
