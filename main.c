#include <stdio.h>

#define ARQUIVO "consultas.txt"

int main() {
    int opcao, especialidade, encontrado, contador;
    char nome[100], data[20], hora[10], lembrete[200], busca[100];
    char dadoEspecifico[200];

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
                printf("4. VSN (Visao subnormal)\n");
                printf("opcao --> ");
                scanf("%d", &especialidade);

                while (especialidade < 1 || especialidade > 4) {
                    printf("OPCAO INEXISTENTE.\n");
                    printf("opcao --> ");
                    scanf("%d", &especialidade);
                }

                if (especialidade == 1) {
                    printf("Grau dos olhos (ex: OD -2.50 / OE -1.75): ");
                    scanf(" %[^\n]", dadoEspecifico);
                }
                if (especialidade == 2) {
                    printf("Pressao Intraocular - PIO (ex: 14 mmHg): ");
                    scanf(" %[^\n]", dadoEspecifico);
                }
                if (especialidade == 3) {
                    printf("Status da retina (ex: presenca de edema, necessidade de laser): ");
                    scanf(" %[^\n]", dadoEspecifico);
                }
                if (especialidade == 4) {
                    printf("Auxilio optico necessario (ex: Lupa Eletronica 6x com Filtro Seletivo): ");
                    scanf(" %[^\n]", dadoEspecifico);
                }

                printf("Lembrete / observacao (ex: levar oculos, retorno, etc): ");
                scanf(" %[^\n]", lembrete);

                FILE *arqCad = fopen(ARQUIVO, "a");
                fprintf(arqCad, "%s;\n%s;\n%s;\n%d;\n%s;\n%s;\n\n", nome, data, hora, especialidade, dadoEspecifico, lembrete);
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
                    while (fscanf(arqList, "%99[^;];\n", nome) == 1) {
                        fscanf(arqList, "%19[^;];\n", data);
                        fscanf(arqList, "%9[^;];\n", hora);
                        fscanf(arqList, "%d;\n", &especialidade);
                        fscanf(arqList, "%199[^;];\n", dadoEspecifico);
                        fscanf(arqList, "%199[^;];\n\n", lembrete);

                        contador++;
                        printf("\n[%d]\n", contador);
                        printf("  Paciente     : %s\n", nome);
                        printf("  Data         : %s\n", data);
                        printf("  Hora         : %s\n", hora);

                        printf("  Especialidade: ");
                        if (especialidade == 1) { printf("Refracao\n"); }
                        if (especialidade == 2) { printf("Glaucoma\n"); }
                        if (especialidade == 3) { printf("Retina\n"); }
                        if (especialidade == 4) { printf("VSN (Visao subnormal)\n"); }

                        if (especialidade == 1) { printf("  Grau dos olhos: %s\n", dadoEspecifico); }
                        if (especialidade == 2) { printf("  PIO            : %s\n", dadoEspecifico); }
                        if (especialidade == 3) { printf("  Status retina  : %s\n", dadoEspecifico); }
                        if (especialidade == 4) { printf("  Auxilio optico : %s\n", dadoEspecifico); }

                        printf("  Lembrete     : %s\n", lembrete);
                    }

                    if (contador == 0) {
                        printf("Nenhuma consulta encontrada.\n");
                    } else {
                        printf("\nTotal: %d consulta(s) agendada(s).\n", contador);
                    }

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
                    while (fscanf(arqBus, "%99[^;];\n", nome) == 1) {
                        fscanf(arqBus, "%19[^;];\n", data);
                        fscanf(arqBus, "%9[^;];\n", hora);
                        fscanf(arqBus, "%d;\n", &especialidade);
                        fscanf(arqBus, "%199[^;];\n", dadoEspecifico);
                        fscanf(arqBus, "%199[^;];\n\n", lembrete);

                        int i = 0, j = 0, achou = 1;

                        while (busca[j] != '\0') {
                            if (nome[i] == '\0') {
                                achou = 0;
                                j = 0;
                                i = 0;
                                break;
                            }
                            if (nome[i] == busca[j]) {
                                i++;
                                j++;
                            } else {
                                i = i - j + 1;
                                j = 0;
                            }
                        }

                        if (achou == 1) {
                            encontrado++;
                            printf("\nResultado %d:\n", encontrado);
                            printf("  Paciente     : %s\n", nome);
                            printf("  Data         : %s\n", data);
                            printf("  Hora         : %s\n", hora);

                            printf("  Especialidade: ");
                            if (especialidade == 1) { printf("Refracao\n"); }
                            if (especialidade == 2) { printf("Glaucoma\n"); }
                            if (especialidade == 3) { printf("Retina\n"); }
                            if (especialidade == 4) { printf("VSN (Visao subnormal)\n"); }

                            if (especialidade == 1) { printf("  Grau dos olhos: %s\n", dadoEspecifico); }
                            if (especialidade == 2) { printf("  PIO            : %s\n", dadoEspecifico); }
                            if (especialidade == 3) { printf("  Status retina  : %s\n", dadoEspecifico); }
                            if (especialidade == 4) { printf("  Auxilio optico : %s\n", dadoEspecifico); }

                            printf("  Lembrete     : %s\n", lembrete);
                        }
                    }

                    if (encontrado == 0) {
                        printf("Nenhum paciente encontrado com esse nome.\n");
                    }

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
