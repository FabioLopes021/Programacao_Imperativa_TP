#define MAX_NOME 50
#define MAX_PART 100


// apontador char criado para imprimir valores enums
const char* SPORT_NAME[] = { "marcha","windsurfing","btt", "swimming" };
const char* UNI_MED[] = { "m","km","mn" };

// Array de apoio a verificaçao de dias dos meses
int MAX_DAYS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


// estrutura de dados para tipo de desporto
enum sporttype {
	marcha,
	windsurfing,
	btt,
	swimming
};
typedef enum sporttype SportType;

// Estrutura de dados para unidade de medida utilizada
enum measurement {
	m,
	km,
	mn
};
typedef enum measurement Measurement;

// Estrutura de dados para guardar hora do dia (hora e minutos)
typedef struct {
	int hora, minuto;
}Time;

//Estrutura de dados para guardar a data (dia, mes e ano)
typedef struct {
	int dia, mes, ano;
}Date;


// Estrutura de dados do primeiro ficheiro
typedef struct {
	int partNum, age;
	unsigned int tel;
	char name[MAX_NOME];
}pratData;


// Estrutura de dados do segundo ficheiro
typedef struct {
	int partNum, duration, distance;
	Date data;
	Time hora;
	SportType sport;
	Measurement uniMed;
} trainingType;

// estrutura para o terceiro ficheiro
typedef struct {
	int partNum, distance;
	Date initDate, endDate;
	Time inittime, endtime;
	SportType sport;
	Measurement uniMed;
} trainingPlan;
