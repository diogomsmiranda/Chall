/*valores boolenos*/
#ifndef _mystructs_
#define _mystructs_

#define True 1
#define False 0

/*limitações do comando*/
#define N_AER 40        /*número de airports limite*/
#define IDLEN 4         /*limite de letras no ID = 3 + 1 */
#define COUNTRYLEN 31      /*limite de letras no país = 30 + 1*/
#define CITYLEN 51    /*limite de letras na city = 50 + 1*/

/*limitacoes no flight*/
#define CODLEN 7        /*limtie codigo_flight*/
#define HORLEN 6        /*limtie hour*/
#define DATELEN 11      /*limite date*/
#define CAPLEN 4        /*limite capacity*/
#define FLIGHTSLEN 30000   /*limite de flights*/
#define CMDLEN 65535  /*limite do comando*/
    
/*estrutura para guardar dates*/
typedef struct date {
    int day;
    int month;
    int year;
}date;

/*estrutura para guardar hours*/
typedef struct hour {
    int hor;
    int min;
}hour;

typedef struct res {
    char codflight[CODLEN];
    date rdate;
    char *codres;
    int n_pass;
    struct res *next;
}res;

/*estrutura para guardar airports*/
typedef struct airport {
    char ID[IDLEN];
    char country[COUNTRYLEN];
    char city[CITYLEN];
    int nflights;
}airport;

/*estrutura para guardar flights*/
typedef struct flight {
    char codflight[CODLEN];
    char parID[IDLEN];
    char cheID[IDLEN];
    date pardat;
    hour parhor;
    hour dur;
    int cap;
    date chedat;
    hour chehor;
    int cap_filled;
    res *res;
}flight;

/*estrutura aux mais tarde utilizada para determinar a hour de chegada
     e a date de chegada*/
struct aux {
    int newday;
    int newmonth;
    int newyear;
    int newhor;
    int newmin;
};

extern struct aux aux;

/*vectores de estruturas utilizados para guardar as diferentes 
    estruturas do programa*/
extern struct airport airports[N_AER];
extern struct flight flights[FLIGHTSLEN];
extern struct flight flights_clone_p[FLIGHTSLEN];
extern struct flight flights_clone_c[FLIGHTSLEN];

/*date do programa*/
extern date curdate;

/*contadores para os vectores anteriores*/
extern int num_airports;
extern int num_flights;
extern int num_flights_p;
extern int num_flights_c;

#endif
