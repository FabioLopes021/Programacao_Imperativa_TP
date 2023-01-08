// incluir Bibliotecas
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Source.h"
#include "Source.c"
#include <windows.h>


// Definiçao de funçoes
void wEnter();
void SetColor(int ForgC);
void startup(pratData** c, trainingType** p, trainingPlan** t);
void startupTrainingPlan(trainingPlan** t);
void startupTrainingType(trainingType** p);
void startupSeguidores(seguidores** s);
void startupCalcMed(calcMed* t);
void printSportType();
void printMeasurement();
void printPartData(pratData** c);
void printTrainingType(trainingType** p);
void printTrainingPlan(trainingPlan** t);
void printNumSeg(seguidores** s);
void addPratData(pratData** c);
int validarNum(pratData*** c, int num);
void addTrainingType(trainingType** p, pratData** c);
void addTrainingPlan(trainingPlan** t, pratData** c);
int encontraNumero(seguidores*** s, int num);
int verificarsegue(seguidores*** s, int num, int seg);
void addNumSeguidores(seguidores** s);
void corrigeseguidores(seguidores*** s, int num, int num1);
void rmvNumSeguidores(seguidores** s);
void atualizarseguidores(seguidores** s, pratData** c);
void savePartData(pratData** c);
void readPartData(pratData** c);
void saveTrainingType(trainingType** p);
void readTrainingType(trainingType** p);
void saveTrainingPlan(trainingPlan** t);
void readTrainingPlan(trainingPlan** t);
int numberNumSeguidores(seguidores*** s, int z);
int numberNumSeguir(seguidores*** s, int z);
void saveSeguidores(seguidores** s);
void readSeguidores(seguidores** s);
void dateRangeTrainingType(trainingType** p, trainingType** r);
void dateRangeTrainingPlan(trainingPlan** p, trainingPlan** r);
void pergunta4(trainingType** p);
void pergunta5(trainingType** p);
void pergunta6(pratData** c, trainingPlan** a);
void pergunta7(trainingType** p);
void auxpergunta8(trainingPlan*** t, trainingType*** p, int* savetp, int* save, int x);
void pergunta8(trainingType** p, trainingPlan** t, pratData** c);
void pergunta10(pratData** c, seguidores** s, trainingType** p);
void pergunta11(pratData** c, seguidores** s, trainingType** p);
char menu();
int menuAdicionar();
int menuFuncoes();
void generico();


// Funçao para esperar pelo enter para continuar
void wEnter() {
	printf("\nPrima ENTER para continuar..."); getchar();
}

/*
Função para alterar a cor da consola
https://stackoverflow.com/questions/29574849/how-to-change-text-color-and-console-color-in-codeblocks
Name         | Value
			 |
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15
*/
void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}


// funçao para inicializar as variáveis das estrutura (pratData, trainingType e trainingPlan)
void startup(pratData** c, trainingType** p, trainingPlan** t) {
	int i;

	for (i = 0; i < MAX_PART; i++) {

		// iniciar partData

		(*c)[i].partNum = 0;
		strcpy((*c)[i].name, "");
		(*c)[i].tel = 0;
		(*c)[i].age = 0;

		//iniciar trainingType
		(*p)[i].partNum = 0;
		(*p)[i].data.ano = 0; (*p)[i].data.mes = 0; (*p)[i].data.dia = 0;
		(*p)[i].hora.hora = 0; (*p)[i].hora.minuto = 0;
		(*p)[i].duration = 0;
		(*p)[i].distance = 0;

		// iniciar trainingPlan
		(*t)[i].partNum = 0;
		(*t)[i].initDate.dia = 0; (*t)[i].initDate.mes = 0; (*t)[i].initDate.ano = 0;
		(*t)[i].inittime.hora = 0; (*t)[i].inittime.minuto = 0;
		(*t)[i].endDate.dia = 0; (*t)[i].endDate.mes = 0; (*t)[i].endDate.ano = 0;
		(*t)[i].endtime.hora = 0; (*t)[i].endtime.minuto = 0;
		(*t)[i].distance = 0;
	}
}

// Funçao para inicializar variável auxiliar
void startupTrainingPlan(trainingPlan** t) {
	int i;

	for (i = 0; i < MAX_PART; i++) {

		// iniciar trainingPlan
		(*t)[i].partNum = 0;
		(*t)[i].initDate.dia = 0; (*t)[i].initDate.mes = 0; (*t)[i].initDate.ano = 0;
		(*t)[i].inittime.hora = 0; (*t)[i].inittime.minuto = 0;
		(*t)[i].endDate.dia = 0; (*t)[i].endDate.mes = 0; (*t)[i].endDate.ano = 0;
		(*t)[i].endtime.hora = 0; (*t)[i].endtime.minuto = 0;
		(*t)[i].distance = 0;
	}
}


// Funçao para inicializar variável da estrutura (trainingType)
void startupTrainingType(trainingType** p) {
	int i;

	for (i = 0; i < MAX_PART; i++) {

		//iniciar trainingType
		(*p)[i].partNum = 0;
		(*p)[i].data.ano = 0; (*p)[i].data.mes = 0; (*p)[i].data.dia = 0;
		(*p)[i].hora.hora = 0; (*p)[i].hora.minuto = 0;
		(*p)[i].duration = 0;
		(*p)[i].distance = 0;
	}
}

// Funçao para inicializar a variavel da estrutura (Seguidores)
void startupSeguidores(seguidores** s) {
	int i, j;

	for (i = 0; i < MAX_PART; i++) {

		//iniciar Seguidores
		(*s)[i].partNum = 0;
		for (j = 0; j < MAX_PART; j++) {
			(*s)[i].numSeguidores[j] = 0;
		}
		for (j = 0; j < MAX_PART; j++) {
			(*s)[i].numSeguir[j] = 0;
		}
	}
}

// Funçao para inicializar variável da estrutura (calcMed)
void startupCalcMed(calcMed* t) {
	for (int i = 0; i < MAX_PART; i++) {
		t[i].iteracoes = 0;
		t[i].med = 0;
		t[i].partNum = 0;
		t[i].totalTime = 0;
	}
}

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


// Funçao para validar o numero de praticante (retorna 1 se existir e 0 se nao existir)
int encontraNumero(seguidores*** s, int num) {
	int ver = 0, i = 0;

	while ((**s)[i].partNum != 0) {
		if ((**s)[i].partNum == num)
			ver = 1;
		i++;
	}
	return ver;
}


// Funçao para verificar se um praticante segue outro (retorna 1 se seguir e 0 se nao seguir)
int verificarsegue(seguidores*** s, int num, int seg) {
	int ver = 0, i = 0;

	while ((**s)[seg - 1].numSeguidores[i] != 0) {
		if ((**s)[seg - 1].numSeguidores[i] == num) {
			ver = 1;
		}
		i++;
	}

	return ver;
}


// Funçao seguir outro praticante
void addNumSeguidores(seguidores** s) {
	int i = 0, j = 0, aux, num;

	printf("Indique o seu numero de praticante: ");
	scanf("%d", &num);

	if (encontraNumero(&s, num) == 1) {
		printf("Indique o numero do praticante que deseja seguir: ");
		scanf("%d", &aux);
		if (verificarsegue(&s, num, aux) == 0 && num != aux) {
			while ((*s)[num - 1].numSeguir[j] != 0) {
				j++;
			}
			(*s)[num - 1].numSeguir[j] = aux;
			j = 0;
			while ((*s)[aux - 1].numSeguidores[j] != 0) {
				j++;
			}
			(*s)[aux - 1].numSeguidores[j] = num;
		}
		else {
			if (num == aux) {
				printf("Nao e possivel um utilizador seguir-se a si mesmo");
			}
			else {
				printf("Ja esta a seguir esse utilizador\n");
			}
		}
	}
	else {
		printf("Nao existe nenhum praticante com esse numero");
	}

	while ((getchar()) != '\n');		//limpar buffer
}


// Funçao para corrigir os arrays que guardam o numero de seguires e a seguir 
void corrigeseguidores(seguidores*** s, int num, int num1) {
	int i = 0, j, counter = 0;

	while (i < MAX_PART) {
		if ((**s)[num].numSeguidores[i] != 0)
			counter++;
		i++;
	}

	for (i = 0, j = 1; j <= counter; i++, j++) {
		if ((**s)[num].numSeguidores[i] == 0) {
			(**s)[num].numSeguidores[i] = (**s)[num].numSeguidores[j];
			(**s)[num].numSeguidores[j] = 0;
		}
	}

	i = 0;
	counter = 0;

	while (i < MAX_PART) {
		if ((**s)[num1].numSeguir[i] != 0)
			counter++;
		i++;
	}

	for (i = 0, j = 1; j <= counter; i++, j++) {
		if ((**s)[num1].numSeguir[i] == 0) {
			(**s)[num1].numSeguir[i] = (**s)[num1].numSeguir[j];
			(**s)[num1].numSeguir[j] = 0;
		}
	}
}


// Funçao para deixar de seguir praticante
void rmvNumSeguidores(seguidores** s) {
	int i = 0, j = 0, aux, num;

	printf("Indique o seu numero de praticante: ");
	scanf("%d", &num);

	if (encontraNumero(&s, num) == 1) {
		printf("Indique o numero do praticante que deseja parar de seguir: ");
		scanf("%d", &aux);
		if (verificarsegue(&s, num, aux) == 1) {
			while ((*s)[num - 1].numSeguir[j] != aux) {
				j++;
			}
			(*s)[num - 1].numSeguir[j] = 0;
			j = 0;
			while ((*s)[aux - 1].numSeguidores[j] != num) {
				j++;
			}
			(*s)[aux - 1].numSeguidores[j] = 0;
			corrigeseguidores(&s, aux - 1, num - 1);
		}
		else {
			printf("Ja nao estava a seguir este utilizador\n");
		}
	}
	else {
		printf("Nao existe nenhum praticante com esse numero");
	}

	while ((getchar()) != '\n');		//limpar buffer
}


// Funçao para atribuir a identificaçao dos praticantes na estrutura Seguidores
void atualizarseguidores(seguidores** s, pratData** c) {
	int i = 0;

	while ((*c)[i].partNum != 0) {
		if ((*s)[i].partNum == 0) {
			(*s)[i].partNum = (*c)[i].partNum;
		}
		i++;
	}
}


// Guardar dados da variavel c (partData) no ficheiro "pratData.txt"
void savePartData(pratData** c) {
	FILE* fp;
	int i = 0;

	fp = fopen("pratData.txt", "w");

	if (fp != NULL) {
		while ((*c)[i].age != 0) {
			fprintf(fp, "%.4d;%s;%d;%d\n", (*c)[i].partNum, (*c)[i].name, (*c)[i].tel, (*c)[i].age);
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Lê dados do ficheiro "pratData.txt" para a variavel c (partData)
void readPartData(pratData** c) {
	FILE* fp;
	char line[1024];
	char* campo1, * campo2, * campo3, * campo4;
	int i = 0;

	fp = fopen("pratData.txt", "r");


	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");

			(*c)[i].partNum = atoi(campo1);
			strcpy((*c)[i].name, campo2);
			(*c)[i].tel = atoi(campo3);
			(*c)[i].age = atoi(campo4);

			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Guardar dados da variavel p (trainingType) no ficheiro "trainingType.txt"
void saveTrainingType(trainingType** p) {
	FILE* fp;
	int i = 0;
	fp = fopen("trainingType.txt", "w");

	if (fp != NULL) {
		while ((*p)[i].partNum != 0) {
			fprintf(fp, "%.4d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n", (*p)[i].partNum, (*p)[i].data.dia, (*p)[i].data.mes, (*p)[i].data.ano, (*p)[i].hora.hora, (*p)[i].hora.minuto, (*p)[i].sport, (*p)[i].duration, (*p)[i].distance, (*p)[i].uniMed);
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Lê dados do ficheiro "trainingType.txt" para a variavel p (trainingType)
void readTrainingType(trainingType** p) {
	FILE* fp;
	char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5, * campo6, * campo7, * campo8, * campo9, * campo10;
	int i = 0;
	fp = fopen("trainingType.txt", "r");


	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");
			campo7 = strtok(NULL, ";");
			campo8 = strtok(NULL, ";");
			campo9 = strtok(NULL, ";");
			campo10 = strtok(NULL, ";");

			(*p)[i].partNum = atoi(campo1);
			(*p)[i].data.dia = atoi(campo2);
			(*p)[i].data.mes = atoi(campo3);
			(*p)[i].data.ano = atoi(campo4);
			(*p)[i].hora.hora = atoi(campo5);
			(*p)[i].hora.minuto = atoi(campo6);
			(*p)[i].sport = atoi(campo7);
			(*p)[i].duration = atoi(campo8);
			(*p)[i].distance = atoi(campo9);
			(*p)[i].uniMed = atoi(campo10);
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Guardar dados da variavel t (trainingPlan) no ficheiro "trainingPlan.txt"
void saveTrainingPlan(trainingPlan** t) {
	FILE* fp;
	int i = 0;

	fp = fopen("trainingPlan.txt", "w");

	if (fp != NULL) {
		while ((*t)[i].partNum != 0) {
			fprintf(fp, "%.4d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n", (*t)[i].partNum, (*t)[i].initDate.dia, (*t)[i].initDate.mes, (*t)[i].initDate.ano, (*t)[i].inittime.hora, (*t)[i].inittime.minuto, (*t)[i].endDate.dia, (*t)[i].endDate.mes, (*t)[i].endDate.ano, (*t)[i].endtime.hora, (*t)[i].endtime.minuto, (*t)[i].sport, (*t)[i].distance, (*t)[i].uniMed);
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Lê dados do ficheiro "trainingPlan.txt" para a variavel t (trainingType)
void readTrainingPlan(trainingPlan** t) {
	FILE* fp;
	char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5, * campo6, * campo7, * campo8, * campo9, * campo10, * campo11, * campo12, * campo13, * campo14;
	int i = 0;

	fp = fopen("trainingPlan.txt", "r");


	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");
			campo7 = strtok(NULL, ";");
			campo8 = strtok(NULL, ";");
			campo9 = strtok(NULL, ";");
			campo10 = strtok(NULL, ";");
			campo11 = strtok(NULL, ";");
			campo12 = strtok(NULL, ";");
			campo13 = strtok(NULL, ";");
			campo14 = strtok(NULL, ";");


			(*t)[i].partNum = atoi(campo1);
			(*t)[i].initDate.dia = atoi(campo2);
			(*t)[i].initDate.mes = atoi(campo3);
			(*t)[i].initDate.ano = atoi(campo4);
			(*t)[i].inittime.hora = atoi(campo5);
			(*t)[i].inittime.minuto = atoi(campo6);
			(*t)[i].endDate.dia = atoi(campo7);
			(*t)[i].endDate.mes = atoi(campo8);
			(*t)[i].endDate.ano = atoi(campo9);
			(*t)[i].endtime.hora = atoi(campo10);
			(*t)[i].endtime.minuto = atoi(campo11);
			(*t)[i].sport = atoi(campo12);
			(*t)[i].distance = atoi(campo13);
			(*t)[i].uniMed = atoi(campo14);
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Retorna o numero de seguidores de um Participante
int numberNumSeguidores(seguidores*** s, int z) {
	int i = 0;

	while ((**s)[z].numSeguidores[i] != 0) {
		i++;
	}

	return i - 1;
}


// Retorna o numero de participante que um participante segue
int numberNumSeguir(seguidores*** s, int z) {
	int i = 0;

	while ((**s)[z].numSeguir[i] != 0)
		i++;

	return i - 1;
}


// Guardar dados da variavel s (seguidores) no ficheiro "seguidores.txt"
void saveSeguidores(seguidores** s) {
	FILE* fp;
	int i = 0, j, aux = 0;

	fp = fopen("Seguidores.txt", "w");

	if (fp != NULL) {
		while ((*s)[i].partNum != 0) {
			j = 0;
			fprintf(fp, "%.4d;", (*s)[i].partNum);
			while (j < numberNumSeguidores(&s, i)) {
				fprintf(fp, "%d,", (*s)[i].numSeguidores[j]);
				j++;
			}
			fprintf(fp, "%d;", (*s)[i].numSeguidores[j]);
			j = 0;
			while (j < numberNumSeguir(&s, i)) {
				fprintf(fp, "%d,", (*s)[i].numSeguir[j]);
				j++;
			}
			fprintf(fp, "%d\n", (*s)[i].numSeguir[j]);
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Lê dados do ficheiro "seguidores.txt" para a variavel s (seguidores)
void readSeguidores(seguidores** s) {
	FILE* fp;
	char line[1024];
	char* campo1, * campo2, * campo3, * token;
	int i = 0, j = 0;

	fp = fopen("Seguidores.txt", "r");


	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");

			(*s)[i].partNum = atoi(campo1);

			token = campo2;
			campo2 = strtok(token, ",");
			j = 0;
			while (campo2 != NULL) {
				(*s)[i].numSeguidores[j] = atoi(campo2);
				campo2 = strtok(NULL, ",");
				j++;
			}

			token = campo3;
			campo3 = strtok(token, ",");
			j = 0;
			while (campo3 != NULL) {
				(*s)[i].numSeguir[j] = atoi(campo3);
				campo3 = strtok(NULL, ",");
				j++;
			}
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


// Copia para a variável z (trainingType) os dados da variável p (trainingType) filtrados por data
void dateRangeTrainingType(trainingType** p, trainingType** r) {
	int i, count = 0;
	Date a, z;


	printf("Introduza o periodo de tempo que deseja seguir esta atividade (AA/MM/DD) \n");
	printf("Inicio \n");
	printf("Ano: ");
	scanf("%d", &a.ano);
	printf("Mes: ");
	scanf("%d", &a.mes);
	while (a.mes < 1 || a.mes > 12) {
		printf("Introduza um mes valido: ");
		scanf("%d", &a.mes);
	}
	printf("Dia: ");
	scanf("%d", &a.dia);
	while (a.dia < 1 || a.dia > MAX_DAYS[a.mes - 1]) {
		printf("Introduza um dia valido: ");
		scanf("%d", &a.dia);
	}

	printf("Fim \n");
	printf("Ano: ");
	scanf("%d", &z.ano);
	printf("Mes: ");
	scanf("%d", &z.mes);
	while (z.mes < 1 || z.mes > 12) {
		printf("Introduza um mes valido: ");
		scanf("%d", &z.mes);
	}
	printf("Dia: ");
	scanf("%d", &z.dia);
	while (z.dia < 1 || z.dia > MAX_DAYS[z.mes - 1]) {
		printf("Introduza um dia valido: ");
		scanf("%d", &z.dia);
	}


	for (i = 0; (*p)[i].partNum != 0; i++) {
		if (((*p)[i].data.ano >= a.ano) && ((*p)[i].data.ano <= z.ano)) {
			if (((*p)[i].data.ano > a.ano) && ((*p)[i].data.ano < z.ano)) {
				(*r)[count].partNum = (*p)[i].partNum;
				(*r)[count].data.ano = (*p)[i].data.ano; (*r)[count].data.mes = (*p)[i].data.mes; (*r)[count].data.dia = (*p)[i].data.dia;
				(*r)[count].hora.hora = (*p)[i].hora.hora; (*r)[count].hora.minuto = (*p)[i].hora.minuto;
				(*r)[count].duration = (*p)[i].duration;
				(*r)[count].distance = (*p)[i].distance;
				(*r)[count].sport = (*p)[i].sport;
				(*r)[count].uniMed = (*p)[i].uniMed;
				count++;
			}
			else if ((*p)[i].data.ano == a.ano) {
				if ((*p)[i].data.mes > a.mes) {
					(*r)[count].partNum = (*p)[i].partNum;
					(*r)[count].data.ano = (*p)[i].data.ano; (*r)[count].data.mes = (*p)[i].data.mes; (*r)[count].data.dia = (*p)[i].data.dia;
					(*r)[count].hora.hora = (*p)[i].hora.hora; (*r)[count].hora.minuto = (*p)[i].hora.minuto;
					(*r)[count].duration = (*p)[i].duration;
					(*r)[count].distance = (*p)[i].distance;
					(*r)[count].sport = (*p)[i].sport;
					(*r)[count].uniMed = (*p)[i].uniMed;
					count++;
				}
				else if ((*p)[i].data.mes == a.mes && (*p)[i].data.dia >= a.dia) {
					(*r)[count].partNum = (*p)[i].partNum;
					(*r)[count].data.ano = (*p)[i].data.ano; (*r)[count].data.mes = (*p)[i].data.mes; (*r)[count].data.dia = (*p)[i].data.dia;
					(*r)[count].hora.hora = (*p)[i].hora.hora; (*r)[count].hora.minuto = (*p)[i].hora.minuto;
					(*r)[count].duration = (*p)[i].duration;
					(*r)[count].distance = (*p)[i].distance;
					(*r)[count].sport = (*p)[i].sport;
					(*r)[count].uniMed = (*p)[i].uniMed;
					count++;
				}
			}
			else if ((*p)[i].data.ano == z.ano) {
				if ((*p)[i].data.mes < z.mes) {
					(*r)[count].partNum = (*p)[i].partNum;
					(*r)[count].data.ano = (*p)[i].data.ano; (*r)[count].data.mes = (*p)[i].data.mes; (*r)[count].data.dia = (*p)[i].data.dia;
					(*r)[count].hora.hora = (*p)[i].hora.hora; (*r)[count].hora.minuto = (*p)[i].hora.minuto;
					(*r)[count].duration = (*p)[i].duration;
					(*r)[count].distance = (*p)[i].distance;
					(*r)[count].sport = (*p)[i].sport;
					(*r)[count].uniMed = (*p)[i].uniMed;
					count++;
				}
				else if ((*p)[i].data.mes == z.mes && (*p)[i].data.dia <= z.dia) {
					(*r)[count].partNum = (*p)[i].partNum;
					(*r)[count].data.ano = (*p)[i].data.ano; (*r)[count].data.mes = (*p)[i].data.mes; (*r)[count].data.dia = (*p)[i].data.dia;
					(*r)[count].hora.hora = (*p)[i].hora.hora; (*r)[count].hora.minuto = (*p)[i].hora.minuto;
					(*r)[count].duration = (*p)[i].duration;
					(*r)[count].distance = (*p)[i].distance;
					(*r)[count].sport = (*p)[i].sport;
					(*r)[count].uniMed = (*p)[i].uniMed;
					count++;
				}
			}
		}
	}
}


// Copia para a variável r (trainingPlan) os dados da variável p (trainingPlan) filtrados por data
void dateRangeTrainingPlan(trainingPlan** p, trainingPlan** r) {
	int i, count, pos = 0;
	Date a, z;

	printf("Introduza o periodo de tempo que deseja seguir esta atividade (AA/MM/DD) \n");
	printf("Inicio \n");
	printf("Ano: ");
	scanf("%d", &a.ano);
	printf("Mes: ");
	scanf("%d", &a.mes);
	while (a.mes < 1 || a.mes > 12) {
		printf("Introduza um mes valido: ");
		scanf("%d", &a.mes);
	}
	printf("Dia: ");
	scanf("%d", &a.dia);
	while (a.dia < 1 || a.dia > MAX_DAYS[a.mes - 1]) {
		printf("Introduza um dia valido: ");
		scanf("%d", &a.dia);
	}

	printf("Fim \n");
	printf("Ano: ");
	scanf("%d", &z.ano);
	printf("Mes: ");
	scanf("%d", &z.mes);
	while (z.mes < 1 || z.mes > 12) {
		printf("Introduza um mes valido: ");
		scanf("%d", &z.mes);
	}
	printf("Dia: ");
	scanf("%d", &z.dia);
	while (z.dia < 1 || z.dia > MAX_DAYS[z.mes - 1]) {
		printf("Introduza um dia valido: ");
		scanf("%d", &z.dia);
	}


	for (i = 0; (*p)[i].partNum != 0; i++) {
		count = 0;
		if (((*p)[i].initDate.ano >= a.ano) && ((*p)[i].initDate.ano <= z.ano)) {
			if (((*p)[i].initDate.ano > a.ano) && ((*p)[i].initDate.ano < z.ano)) {
				count++;
			}
			else if ((*p)[i].initDate.ano == a.ano) {
				if ((*p)[i].initDate.mes > a.mes) {
					count++;
				}
				else if ((*p)[i].initDate.mes == a.mes && (*p)[i].initDate.dia >= a.dia) {
					count++;
				}
			}
			else if ((*p)[i].initDate.ano == z.ano) {
				if ((*p)[i].initDate.mes < z.mes) {
					count++;
				}
				else if ((*p)[i].initDate.mes == z.mes && (*p)[i].initDate.dia <= z.dia) {
					count++;
				}
			}
		}

		if (((*p)[i].endDate.ano >= a.ano) && ((*p)[i].endDate.ano <= z.ano)) {
			if (((*p)[i].endDate.ano > a.ano) && ((*p)[i].endDate.ano < z.ano)) {
				count++;
			}
			else if ((*p)[i].endDate.ano == a.ano) {
				if ((*p)[i].endDate.mes > a.mes) {
					count++;
				}
				else if ((*p)[i].endDate.mes == a.mes && (*p)[i].endDate.mes >= a.dia) {
					count++;
				}
			}
			else if ((*p)[i].endDate.ano == z.ano) {
				if ((*p)[i].endDate.mes < z.mes) {
					count++;
				}
				else if ((*p)[i].endDate.mes == z.mes && (*p)[i].endDate.dia <= z.dia) {
					count++;
				}
			}
		}

		if (count == 2) {
			(*r)[pos].partNum = (*p)[i].partNum;
			(*r)[pos].initDate.dia = (*p)[i].initDate.dia; (*r)[pos].initDate.mes = (*p)[i].initDate.mes; (*r)[pos].initDate.ano = (*p)[i].initDate.ano;
			(*r)[pos].inittime.hora = (*p)[i].inittime.hora; (*r)[pos].inittime.minuto = (*p)[i].inittime.minuto;
			(*r)[pos].endDate.dia = (*p)[i].endDate.dia; (*r)[pos].endDate.mes = (*p)[i].endDate.mes; (*r)[pos].endDate.ano = (*p)[i].endDate.ano;
			(*r)[pos].endtime.hora = (*p)[i].endtime.hora; (*r)[pos].endtime.minuto = (*p)[i].endtime.minuto;
			(*r)[pos].distance = (*p)[i].distance;
			(*r)[pos].sport = (*p)[i].sport;
			(*r)[pos].uniMed = (*p)[i].uniMed;
			pos++;
		}
	}
}


// A funçao "pergunta4" apresenta o numero de praticantes que realizaram uma atividade num determinado periodo de tempo
void pergunta4(trainingType** p) {
	int i, cont = 0;

	SportType x;


	printSportType();
	printf("Escolha a atividade que deseja seguir: ");
	scanf("%d", &x);
	while (x < marcha || x > swimming) {
		printf("Indique uma Atividade valida: ");
		scanf("%d", &x);
	}

	for (i = 0; (*p)[i].partNum != 0; i++) {
		if ((*p)[i].sport == x)
			cont++;
	}

	printf(" Durante o periodo de tempo indicado %d pessoas praticaram a atividade %s\n", cont, SPORT_NAME[x]);
}


// A funçao "pergunta5" lista os praticantes que realizaram alguma atividade num determinado periodo de tempo
void pergunta5(trainingType** p) {
	int i = 0, b = 1, j;
	trainingType aux;

	while ((*p)[i].partNum != 0) {
		i++;
	}
	i--;

	if (i < 0) {
		printf("Nenhum praticante realizou qualquer atividade desportiva no intervalo de tempo indicado\n");
	}
	else {
		while (b) {
			b = 0;
			for (j = 0; j < i; j++) {
				if ((*p)[j].partNum > (*p)[j + 1].partNum) {
					aux.partNum = (*p)[j].partNum;
					aux.data.ano = (*p)[j].data.ano; aux.data.mes = (*p)[j].data.mes; aux.data.dia = (*p)[j].data.dia;
					aux.hora.hora = (*p)[j].hora.hora; aux.hora.minuto = (*p)[j].hora.minuto;
					aux.sport = (*p)[j].sport;
					aux.duration = (*p)[j].duration;
					aux.distance = (*p)[j].distance;
					aux.uniMed = (*p)[j].uniMed;

					(*p)[j].partNum = (*p)[j + 1].partNum;
					(*p)[j].data.ano = (*p)[j + 1].data.ano;  (*p)[j].data.mes = (*p)[j + 1].data.mes; (*p)[j].data.dia = (*p)[j + 1].data.dia;
					(*p)[j].hora.hora = (*p)[j + 1].hora.hora; (*p)[j].hora.minuto = (*p)[j + 1].hora.minuto;
					(*p)[j].sport = (*p)[j + 1].sport;
					(*p)[j].duration = (*p)[j + 1].duration;
					(*p)[j].distance = (*p)[j + 1].distance;
					(*p)[j].uniMed = (*p)[j + 1].uniMed;

					(*p)[j + 1].partNum = aux.partNum;
					(*p)[j + 1].data.ano = aux.data.ano;  (*p)[j + 1].data.mes = aux.data.mes; (*p)[j + 1].data.dia = aux.data.dia;
					(*p)[j + 1].hora.hora = aux.hora.hora; (*p)[j + 1].hora.minuto = aux.hora.minuto;
					(*p)[j + 1].sport = aux.sport;
					(*p)[j + 1].duration = aux.duration;
					(*p)[j + 1].distance = aux.distance;
					(*p)[j + 1].uniMed = aux.uniMed;

					b = 1;
				}

			}
		}



		while (i >= 0) {
			printf("-----------------------------------\n");
			printf("Numero Participante: %.4d \n", (*p)[i].partNum);
			printf("Data: %d/%d/%d \n", (*p)[i].data.dia, (*p)[i].data.mes, (*p)[i].data.ano);
			printf("Hora: %.2d:%.2d \n", (*p)[i].hora.hora, (*p)[i].hora.minuto);
			printf("Tipo de atividade: %s \n", SPORT_NAME[(*p)[i].sport]);
			printf("tempo de duraçao (min): %d \n", (*p)[i].duration);
			printf("Distancia: %d \n", (*p)[i].distance);
			printf("Unidade de medida: %s \n", UNI_MED[(*p)[i].uniMed]);
			printf("-----------------------------------\n");
			i--;
		}
	}
}


// A funçao "pergunta6" lista os planos de atividades de um praticante para um determinado periodo de tempo
void pergunta6(pratData** c, trainingPlan** a) {
	SportType x;
	int num, i, count = 0;

	printSportType();
	printf("Escolha a atividade que deseja seguir: ");
	scanf("%d", &x);
	while (x < marcha || x > swimming) {
		printf("Indique uma Atividade valida: ");
		scanf("%d", &x);
	}

	printf("Digite o numero do praticante que deseja listar o plano de atividades: ");
	scanf("%d", &num);
	while (validarNum(&c, num) == 0) {
		printf("Indique um numero de praticante valido: ");
		scanf("%d", &num);
	}

	for (i = 0; (*a)[i].partNum != 0; i++) {
		if (((*a)[i].partNum == num) && ((*a)[i].sport == x)) {
			printf("-----------------------------------\n");
			printf("Numero Participante: %.4d \n", (*a)[i].partNum);
			printf("Data Inicio: %d/%d/%d \n", (*a)[i].initDate.dia, (*a)[i].initDate.mes, (*a)[i].initDate.ano);
			printf("Hora inicio: %.2d:%.2d \n", (*a)[i].inittime.hora, (*a)[i].inittime.minuto);
			printf("Data fim: %d/%d/%d \n", (*a)[i].endDate.dia, (*a)[i].endDate.mes, (*a)[i].endDate.ano);
			printf("Hora fim: %.2d:%.2d \n", (*a)[i].endtime.hora, (*a)[i].endtime.minuto);
			printf("Atividade: %s\n", SPORT_NAME[(*a)[i].sport]);
			printf("Distancia: %d\n", (*a)[i].distance);
			printf("Unidade de medida: %s \n", UNI_MED[(*a)[i].uniMed]);
			printf("-----------------------------------\n");
			count++;
		}
	}

	if (count == 0)
		printf("Nao existe nenhum plano que correspondas as suas condicoes");
}


// A funçao "pergunta7" calcula os tempos totais e médias por atividade em que cada praticante esteve envolvido num determinado período introduzido pelo utilizador
void pergunta7(trainingType** p) {
	int i, j, savenum;
	calcMed y[MAX_PART];

	startupCalcMed(&y);
	//Calcular tempo total de cada atividade
	for (i = 0; (*p)[i].partNum != 0; i++) {
		j = 0;
		savenum = -1;
		while (y[j].partNum != 0) {
			if (((*p)[i].partNum == y[j].partNum) && ((*p)[i].sport == y[j].sport)) {
				savenum = j;
				break;
			}
			j++;
		}
		if (savenum >= 0) {
			y[savenum].iteracoes += 1;
			y[savenum].totalTime += (*p)[i].duration;
			y[savenum].med = y[savenum].totalTime / y[savenum].iteracoes;
		}
		else {
			y[j].partNum = (*p)[i].partNum;
			y[j].sport = (*p)[i].sport;
			y[j].iteracoes += 1;
			y[j].totalTime += (*p)[i].duration;
			y[j].med = y[j].totalTime / y[j].iteracoes;
		}
	}


	for (i = 0; y[i].partNum != 0; i++) {
		printf("\n\n-----------------------\n");
		printf("Numero de praticante: %.4d\n", y[i].partNum);
		printf("Desporto praticado: %s\n", SPORT_NAME[y[i].sport]);
		printf("Tempo total (min): %d\n", y[i].totalTime);
		printf("Tempo medio (min): %.2f\n", y[i].med);
		printf("-----------------------\n\n");
	}
}


// A funçao "auxpergunta8" serve de auxilio a funçao "Pergunta8", a mesma edita os dados de dois arrays com os indices necessarios para imprimir a informaçao correta
void auxpergunta8(trainingPlan*** t, trainingType*** p, int* savetp, int* save, int x) {
	int i, j;

	for (i = 0; i < 30; i++) {
		savetp[i] = -1;
		save[i] = -1;
	}

	for (i = 0, j = 0; (**t)[i].partNum != 0; i++) {
		if ((**t)[i].partNum == x) {
			savetp[j] = i;
			j++;
		}
	}

	for (i = 0, j = 0; (**p)[i].partNum != 0; i++) {
		if ((**p)[i].partNum == x) {
			save[j] = i;
			j++;
		}
	}
}

// A funçao "pergunta8" Gera uma tabela das atividades planeadas e realizadas para todos os praticantes
void pergunta8(trainingType** p, trainingPlan** t, pratData** c) {
	int i, z, j = 0, d, savetp[30], save[30], auxd, auxz;

	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|Num. Prat | Nome\t\t | Ativ. Planeada | Medida | Valor da medida | Data de Inicio\t | Data de Fim\t | Ativ. realizada | Data de Inicio | Duracao | Medida | Valor da medida|\n");
	for (i = 0; (*c)[i].partNum != 0; i++) {
		z = 0;
		d = 0;
		auxpergunta8(&t, &p, &savetp, &save, (*c)[i].partNum);
		while (savetp[z] != -1)
			z++;
		while (save[d] != -1)
			d++;
		z--;
		d--;
		while (z > d) {
			auxz = savetp[z];
			// imprime a tabela so com o training plan ate poder igualar
			printf("| %-8.4d | %-19s | %-15s| %-7s| %-15d |", (*c)[i].partNum, (*c)[i].name, SPORT_NAME[(*t)[auxz].sport], UNI_MED[(*t)[auxz].uniMed], (*t)[auxz].distance);
			printf(" %.2d/%.2d/%-11.4d | %.2d/%.2d/%-7.4d |", (*t)[auxz].initDate.dia, (*t)[auxz].initDate.mes, (*t)[auxz].initDate.ano, (*t)[auxz].endDate.dia, (*t)[auxz].endDate.mes, (*t)[auxz].endDate.ano);
			printf(" --------------- | -------------- |");
			printf(" ------- | ------ | -------------- |\n");
			z--;
		}
		while (z < d) {
			auxd = save[d];
			// imprime a tabela so com o training type ate poder igualar
			printf("| %-8.4d | %-19s | -------------- | ------ | --------------- |", (*c)[i].partNum, (*c)[i].name);
			printf(" ----------------- | ------------- |");
			printf(" %-15s | %.2d/%.2d/%-8.4d |", SPORT_NAME[(*p)[auxd].sport], (*p)[auxd].data.dia, (*p)[auxd].data.mes, (*p)[auxd].data.ano);
			printf(" %-7d | %-6s | %-14d |\n", (*p)[auxd].duration, UNI_MED[(*p)[auxd].uniMed], (*p)[auxd].distance);
			d--;
		}
		while (z == d && z >= 0) {
			// imprime a tabela com a linha completas
			auxz = savetp[z];
			auxd = save[d];
			printf("| %-8.4d | %-19s | %-15s| %-7s| %-15d |", (*c)[i].partNum, (*c)[i].name, SPORT_NAME[(*t)[auxz].sport], UNI_MED[(*t)[auxz].uniMed], (*t)[auxz].distance);
			printf(" %.2d/%.2d/%-11.4d | %.2d/%.2d/%-7.4d |", (*t)[auxz].initDate.dia, (*t)[auxz].initDate.mes, (*t)[auxz].initDate.ano, (*t)[auxz].endDate.dia, (*t)[auxz].endDate.mes, (*t)[auxz].endDate.ano);
			printf(" %-15s | %.2d/%.2d/%-8.4d |", SPORT_NAME[(*p)[auxd].sport], (*p)[auxd].data.dia, (*p)[auxd].data.mes, (*p)[auxd].data.ano);
			printf(" %-7d | %-6s | %-14d |\n", (*p)[auxd].duration, UNI_MED[(*p)[auxd].uniMed], (*p)[auxd].distance);
			z--;
			d--;
		}
	}
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}


// A funçao "pergunta10" apresenta uma listagem por atividade com o praticante com o maior tempo de prática dessa atividade, e o respetivo tempo, de entre os seguidores de um praticante definido pelo utilizador
void pergunta10(pratData** c, seguidores** s, trainingType** p) {
	int i, j, num, time, bestTime = 0, savenum = 0;
	int save[100] = { 0 };

	SportType x;

	printf("Indique o Numero do praticante: ");
	scanf("%d", &num);
	while (validarNum(&c, num) == 0) {
		printf("Indique um numero de praticante valido: ");
		scanf("%d", &num);
	}

	num -= 1;

	for (i = 0; (*s)[num].numSeguidores[i] != 0; i++) {
		save[i] = (*s)[num].numSeguidores[i];
	}

	for (x = 0; x < 4; x++) {
		bestTime = 0;
		for (i = 0; save[i] != 0; i++) {
			time = 0;
			for (j = 0; (*p)[j].partNum != 0; j++) {
				if ((save[i] == (*p)[j].partNum) && ((*p)[j].sport == x)) {
					time += (*p)[j].duration;
				}
			}
			if (time > bestTime) {
				bestTime = time;
				savenum = save[i];
			}
		}
		if (bestTime != 0) {
			printf("\n-------------------------------------\n");
			printf("Dos seguidores do praticante N %d \n", (*p)[num].partNum);
			printf("O praticante N %d e o que aprensenta mais tempo praticado com %d minutos de %s", savenum, bestTime, SPORT_NAME[x]);
			printf("\n-------------------------------------\n");
		}
		else {
			printf("\n-------------------------------------\n");
			printf("Dos praticantes a seguir o praticante N %d nenhum praticou a atividade %s", (*p)[num].partNum, SPORT_NAME[x]);
			printf("\n-------------------------------------\n");
		}
	}
}



// A funçao "pergunta11" Apresenta uma listagem por atividade com o praticante com o maior tempo de prática dessa atividade, e o respetivo tempo, de entre os praticantes seguidos por um determinado praticantedefinido pelo utilizador
void pergunta11(pratData** c, seguidores** s, trainingType** p) {
	int i, j, num, time, bestTime, savenum = 0;
	int save[100] = { 0 };

	SportType x;


	printf("Indique o Numero do praticante: ");
	scanf("%d", &num);
	while (validarNum(&c, num) == 0) {
		printf("Indique um numero de praticante valido: ");
		scanf("%d", &num);
	}

	num -= 1;

	for (i = 0; (*s)[num].numSeguir[i] != 0; i++) {
		save[i] = (*s)[num].numSeguir[i];
	}

	for (x = 0; x < 4; x++) {
		bestTime = 0;
		for (i = 0; save[i] != 0; i++) {
			time = 0;
			for (j = 0; (*p)[j].partNum != 0; j++) {
				if ((save[i] == (*p)[j].partNum) && ((*p)[j].sport == x)) {
					time += (*p)[j].duration;
				}
			}
			if (time > bestTime) {
				bestTime = time;
				savenum = save[i];
			}
		}
		if (bestTime != 0) {
			printf("\n-------------------------------------\n");
			printf("Dos praticante seguidos pelo N %d \n", (*p)[num].partNum);
			printf("O praticante N %d e o que apresenta mais tempo praticado com %d minutos de %s", savenum, bestTime, SPORT_NAME[x]);
			printf("\n-------------------------------------\n");
		}
		else {
			printf("\n-------------------------------------\n");
			printf("Dos praticantes seguidos pelo N %d nenhum praticou a atividade %s", (*p)[num].partNum, SPORT_NAME[x]);
			printf("\n-------------------------------------\n");
		}
	}
}


int main() {

	pratData c[MAX_PART];
	trainingType p[MAX_PART], z[MAX_PART];
	trainingPlan t[MAX_PART], a[MAX_PART];
	seguidores s[MAX_PART];

	return 0;
}