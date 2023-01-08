// incluir Bibliotecas
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Source.h"
#include "Source.c"
#include <windows.h>




// Imprimir um menu para auxiliar a leitura do tipo de atividade
void printSportType() {
	printf("##Introduza o numero correspondente ao desporto ##\n");
	printf("## 0 - Marcha ##\n");
	printf("## 1 - Windsurfing ##\n");
	printf("## 2 - BTT ##\n");
	printf("## 3 - Swimming ##\n");
}


// Imprimir um menu para auxiliar a leitura do tipo de medida
void printMeasurement() {
	printf("##Introduza o numero correspondente a medida a utilizar ##\n");
	printf("## 0 - M ##\n");
	printf("## 1 - KM ##\n");
	printf("## 2 - MN ##\n");
}


// imprimir todos os Praticantes 
void printPartData(pratData** c) {
	int i = 0;
	printf("-----------------pratData------------------\n");

	while ((*c)[i].age != 0) {
		printf("-----------------------------------\n");
		printf("Numero Praticante: %.4d \n", (*c)[i].partNum);
		printf("Nome: %s \n", (*c)[i].name);
		printf("Numero telemovel: %d \n", (*c)[i].tel);
		printf("Idade: %d \n", (*c)[i].age);
		printf("-----------------------------------\n");
		i++;
	}
}


// Imprimir todos os tipos de treinos guardados
void printTrainingType(trainingType** p) {
	int i = 0;
	printf("-----------------trainingType------------------\n");

	while ((*p)[i].partNum != 0) {
		printf("-----------------------------------\n");
		printf("Numero Praticante: %.4d \n", (*p)[i].partNum);
		printf("Data: %d/%d/%d \n", (*p)[i].data.dia, (*p)[i].data.mes, (*p)[i].data.ano);
		printf("Hora: %.2d:%.2d \n", (*p)[i].hora.hora, (*p)[i].hora.minuto);
		printf("tipo de atividade: %s \n", SPORT_NAME[(*p)[i].sport]);
		printf("tempo de duraçao (min): %d \n", (*p)[i].duration);
		printf("Distancia: %d \n", (*p)[i].distance);
		printf("Unidade de medida: %s \n", UNI_MED[(*p)[i].uniMed]);
		printf("-----------------------------------\n");
		i++;
	}
}


// Imprimir todos os planos de treino guardados
void printTrainingPlan(trainingPlan** t) {
	int i = 0;
	printf("-----------------TrainingPlan------------------\n");

	while ((*t)[i].partNum != 0) {
		printf("-----------------------------------\n");
		printf("Numero Praticante: %.4d \n", (*t)[i].partNum);
		printf("Data Inicio: %d/%d/%d \n", (*t)[i].initDate.dia, (*t)[i].initDate.mes, (*t)[i].initDate.ano);
		printf("Hora inicio: %.2d:%.2d \n", (*t)[i].inittime.hora, (*t)[i].inittime.minuto);
		printf("Data fim: %d/%d/%d \n", (*t)[i].endDate.dia, (*t)[i].endDate.mes, (*t)[i].endDate.ano);
		printf("Hora fim: %.2d:%.2d \n", (*t)[i].endtime.hora, (*t)[i].endtime.minuto);
		printf("Atividade: %s\n", SPORT_NAME[(*t)[i].sport]);
		printf("Distancia: %d\n", (*t)[i].distance);
		printf("Unidade de medida: %s \n", UNI_MED[(*t)[i].uniMed]);
		printf("-----------------------------------\n");
		i++;
	}
}


// Imprimir informaçoes de todos os Seguidores
void printNumSeg(seguidores** s) {
	int i = 0, j;
	printf("-----------------Numero de seguidores/A seguir------------------\n");

	while ((*s)[i].partNum != 0) {
		j = 0;
		printf("-----------------------------------\n");
		printf("Numero Praticante: %.4d \n", (*s)[i].partNum);
		printf("Seguidores: ");
		while ((*s)[i].numSeguidores[j] != 0) {
			printf("%.4d ", (*s)[i].numSeguidores[j]);
			j++;
		}
		printf("\n");
		j = 0;
		printf("A seguir: ");
		while ((*s)[i].numSeguir[j] != 0) {
			printf("%.4d ", (*s)[i].numSeguir[j]);
			j++;
		}
		printf("\n");
		printf("-----------------------------------\n");
		i++;
	}
}


// Adicionar Praticante 
void addPratData(pratData** c) {
	int i = 0;

	while ((*c)[i].partNum != 0) {
		i++;
	}

	(*c)[i].partNum = i + 1;
	printf("O seu numero de Praticante e: %.4d\n", (*c)[i].partNum);
	printf("Escreva o seu nome: ");
	gets((*c)[i].name);
	printf("Indique o seu numero de telemovel: ");
	scanf(" %d", &(*c)[i].tel);
	printf("Indique a sua idade: ");
	scanf("%d", &(*c)[i].age);
	while ((*c)[i].age < 1 || (*c)[i].age > 110) {
		printf("Introduza uma idade valida: ");
		scanf("%d", &(*c)[i].age);
	}
	while ((getchar()) != '\n');
}


// Funçao para validar o numero de praticante (retorna 1 se existir e 0 se nao existir)
int validarNum(pratData*** c, int num) {
	int i = 0;

	while ((**c)[i].partNum != 0) {
		if ((**c)[i].partNum == num)
			return 1;
		i++;
	}

	return 0;
}


// Adicionar Tipo de Treino
void addTrainingType(trainingType** p, pratData** c) {
	int i = 0;

	while ((*p)[i].partNum != 0) {
		i++;
	}


	printf("Indique o seu numero de praticante: ");
	scanf("%d", &(*p)[i].partNum);
	while (validarNum(&c, (*p)[i].partNum) == 0) {
		printf("Introduza um numero valido: ");
		scanf("%d", &(*p)[i].partNum);
	}

	printf("Indique a data: AA/MM/DD\n");
	printf("ano:");
	scanf("%d", &(*p)[i].data.ano);
	printf("mes:");
	scanf("%d", &(*p)[i].data.mes);
	while ((*p)[i].data.mes < 1 || (*p)[i].data.mes > 12) {
		printf("Introduza um mes valido: ");
		scanf("%d", &(*p)[i].data.mes);
	}
	printf("dia:");
	scanf("%d", &(*p)[i].data.dia);
	while ((*p)[i].data.dia < 1 || (*p)[i].data.dia > MAX_DAYS[(*p)[i].data.mes - 1]) {
		printf("Introduza um mes valido: ");
		scanf("%d", &(*p)[i].data.dia);
	}

	printf("Indique a hora de inicio: HH:MM\n");
	printf("Hora: ");
	scanf("%d", &(*p)[i].hora.hora);
	while ((*p)[i].hora.hora < 0 || (*p)[i].hora.hora > 23) {
		printf("Indique uma hora valida: ");
		scanf("%d", &(*p)[i].hora.hora);
	}
	printf("Minutos: ");
	scanf("%d", &(*p)[i].hora.minuto);
	while ((*p)[i].hora.minuto < 0 || (*p)[i].hora.minuto > 59) {
		printf("Indique um valor de minutos valido: ");
		scanf("%d", &(*p)[i].hora.minuto);
	}

	printSportType();
	printf("Atividade: ");
	scanf("%d", &(*p)[i].sport);
	while ((*p)[i].sport < marcha || (*p)[i].sport > swimming) {
		printf("Indique uma Atividade valida: ");
		scanf("%d", &(*p)[i].sport);
	}

	printf("Indique a duracao em minutos: ");
	scanf("%d", &(*p)[i].duration);
	while ((*p)[i].duration < 1) {
		printf("Indique uma duracao valida: ");
		scanf("%d", &(*p)[i].duration);
	}

	printf("Indique a distancia pecurrida: ");
	scanf("%d", &(*p)[i].distance);
	while ((*p)[i].distance < 1) {
		printf("Indique uma distancia valida: ");
		scanf("%d", &(*p)[i].distance);
	}

	printMeasurement();
	printf("Unidade de Medida: ");
	scanf("%d", &(*p)[i].uniMed);
	while ((*p)[i].uniMed < m || (*p)[i].uniMed > mn) {
		printf("Indique uma unidade de medida valida: ");
		scanf("%d", &(*p)[i].uniMed);
	}

	while ((getchar()) != '\n');
}


// Adicionar Plano de Treino
void addTrainingPlan(trainingPlan** t, pratData** c) {
	int i = 0;

	while ((*t)[i].partNum != 0) {
		i++;
	}


	printf("Indique o seu numero de praticante: ");
	scanf("%d", &(*t)[i].partNum);
	while (validarNum(&c, (*t)[i].partNum) == 0) {
		printf("Introduza um numero valido: ");
		scanf("%d", &(*t)[i].partNum);
	}
	printf("Indique a data de inicio: AA/MM/DD\n");
	printf("ano:");
	scanf("%d", &(*t)[i].initDate.ano);
	printf("mes:");
	scanf("%d", &(*t)[i].initDate.mes);
	while ((*t)[i].initDate.mes < 1 || (*t)[i].initDate.mes > 12) {
		printf("Introduza um mes valido: ");
		scanf("%d", &(*t)[i].initDate.mes);
	}
	printf("dia:");
	scanf("%d", &(*t)[i].initDate.dia);
	while ((*t)[i].initDate.dia < 1 || (*t)[i].initDate.dia > MAX_DAYS[(*t)[i].initDate.mes - 1]) {
		printf("Introduza um dia valido: ");
		scanf("%d", &(*t)[i].initDate.dia);
	}

	printf("Indique a hora de inicio: HH:MM\n");
	printf("Hora: ");
	scanf("%d", &(*t)[i].inittime.hora);
	while ((*t)[i].inittime.hora < 0 || (*t)[i].inittime.hora > 23) {
		printf("Indique uma hora valida: ");
		scanf("%d", &(*t)[i].inittime.hora);
	}
	printf("Minutos: ");
	scanf("%d", &(*t)[i].inittime.minuto);
	while ((*t)[i].inittime.minuto < 0 || (*t)[i].inittime.minuto > 59) {
		printf("Indique um valor de minutos valido: ");
		scanf("%d", &(*t)[i].inittime.minuto);
	}

	printf("Indique a data de fim: AA/MM/DD\n");
	printf("ano:");
	scanf("%d", &(*t)[i].endDate.ano);
	printf("mes:");
	scanf("%d", &(*t)[i].endDate.mes);
	while ((*t)[i].endDate.mes < 1 || (*t)[i].endDate.mes > 12) {
		printf("Introduza um mes valido: ");
		scanf("%d", &(*t)[i].endDate.mes);
	}
	printf("dia:");
	scanf("%d", &(*t)[i].endDate.dia);
	while ((*t)[i].endDate.dia < 1 || (*t)[i].endDate.dia > MAX_DAYS[(*t)[i].endDate.mes - 1]) {
		printf("Introduza um dia valido: ");
		scanf("%d", &(*t)[i].endDate.dia);
	}

	printf("Indique a hora de fim: HH:MM\n");
	printf("Hora: ");
	scanf("%d", &(*t)[i].endtime.hora);
	while ((*t)[i].endtime.hora < 0 || (*t)[i].endtime.hora > 23) {
		printf("Indique uma hora valida: ");
		scanf("%d", &(*t)[i].endtime.hora);
	}
	printf("Minutos: ");
	scanf("%d", &(*t)[i].endtime.minuto);
	while ((*t)[i].endtime.minuto < 0 || (*t)[i].endtime.minuto > 59) {
		printf("Indique um valor de minutos valido: ");
		scanf("%d", &(*t)[i].endtime.minuto);
	}

	printSportType();
	printf("Atividade: ");
	scanf("%d", &(*t)[i].sport);
	while ((*t)[i].sport < marcha || (*t)[i].sport > swimming) {
		printf("Indique uma Atividade valida: ");
		scanf("%d", &(*t)[i].sport);
	}

	printf("Indique a distancia pecurrida: ");
	scanf("%d", &(*t)[i].distance);
	while ((*t)[i].distance < 1) {
		printf("Indique uma distancia valida: ");
		scanf("%d", &(*t)[i].distance);
	}


	printMeasurement();
	printf("Unidade de Medida: ");
	scanf("%d", &(*t)[i].uniMed);
	while ((*t)[i].uniMed < m || (*t)[i].uniMed > mn) {
		printf("Indique uma unidade de medida valida: ");
		scanf("%d", &(*t)[i].uniMed);
	}
	while ((getchar()) != '\n');
}




int main() {


	pratData c[MAX_PART];
	trainingType p[MAX_PART], z[MAX_PART];
	trainingPlan t[MAX_PART], a[MAX_PART];

	return 0;
}