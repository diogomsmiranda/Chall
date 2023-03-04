#include "proj1.h"

struct aux aux;

struct airport airports[N_AER];
struct flight flights[FLIGHTSLEN];
struct flight flights_clone_p[FLIGHTSLEN];
struct flight flights_clone_c[FLIGHTSLEN];

date curdate;

/*contadores para os vectores anteriores*/
int num_airports = 0;
int num_flights = 0;
int num_flights_p = 0;
int num_flights_c = 0;

/*atualiza valor da date para o inicial 1/1/2022*/
void set_date() {

    curdate.day = 1;
    curdate.month = 1;
    curdate.year = 2022;
}

/*verifica se existe uma letra do ID que nao seja maiúscula*/
int error_upper(char ID[4]) {
    int i;

    for(i = 0; i<3;i++) {
        if(!isupper(ID[i])) {
            printf("invalid airport ID\n");
            return True;
        }
    }
    return False;
}

/*verifica se existe um airport com o ID dado no vector de airports*/
int error_duplicate(char ID[4]) {

    int j = 0;

    for(j = 0; j < num_airports; j++) {
        if(strcmp(airports[j].ID,ID) == 0) {
            printf("duplicate airport\n");
            return True;
        }
    }
    return False;
}

/*add airport descrito no comando ao vector de airports*/
int add_airport(airport aer) {  

    strcpy(airports[num_airports].ID,aer.ID);
    strcpy(airports[num_airports].country,aer.country);
    strcpy(airports[num_airports].city,aer.city);

    num_airports++;
    return 0;
}

/*le o airport descrito no comando e add-o ao vector se tiver as
    condicoes descritas no enunciado*/
int add_aer(char command[88]) {

    airport aer;
    
    strtok(command, " ");
    strcpy(aer.ID,strtok(NULL," \t"));
    strcpy(aer.country,strtok(NULL," \t"));
    strcpy(aer.city,strtok(NULL," \t\n"));

    if(error_upper(aer.ID))
        return 0;
    
    if (num_airports == N_AER) {
        printf("too many airports\n");
        return 0;
    }

    if(error_duplicate(aer.ID))
        return 0;

    printf("airport %s\n",aer.ID);

    add_airport(aer);
    return 0;
}


/*oderna o vector de airports segundo o ID*/
void insertionSort_aers() {
    int i,j;
    airport key;

    for (i = 1; i < num_airports; i++) {
        key = airports[i];
        j = i - 1;
        while (j >= 0 && strcmp(airports[j].ID,key.ID)>0) {
            airports[j + 1] = airports[j];
            j = j - 1;
        }
        airports[j + 1] = key;
    }
}

/*imprime o vector de airports como descrito no enunciado*/
void print_aers() {
    int h;

    for(h = 0; h<num_airports;h++) {
        printf("%s %s %s %d\n",airports[h].ID, airports[h].city,
         airports[h].country, airports[h].nflights);
    }
}

/*imprime do vector de airports os airports com o ID dado*/
int print_list_aers(char ID_l[4]) {
    int h,counter = 0;

    for(h = 0; h < num_airports; h++) {
        if(strcmp(ID_l,airports[h].ID) == 0) {
            printf("%s %s %s %d\n",airports[h].ID, 
            airports[h].city, airports[h].country, 
            airports[h].nflights);
            counter++;
            break;
        }
    }
    return counter;
}

/*lista os airports com os IDs dados se for o caso ,
    se nao lista o vector de airports ordenado por ID*/
int list_aers(char command[200]) {

    int counter2 = 0,comlen = strlen(command);
    char ID_l[4];

    if(comlen > 2) {
        strtok(command, " ");
        comlen -= 2;

        while(counter2 < comlen) {
            strcpy(ID_l,strtok(NULL," \n"));

            if (print_list_aers(ID_l) == 0) {
                printf("%s: no such airport ID\n", ID_l);
            }
            counter2 += 4;
        }
        return 0;
    }
    else {
        insertionSort_aers();
        print_aers();
        return 0;
    }
}

/*verifica se o codigo de flight dado é válido*/
int error_invalid(char codflight[CODLEN]) {
    int i;
    int len = strlen(codflight);

    for(i = 0; i<2;i++) {
        if(!isupper(codflight[i])) {
            printf("invalid flight code\n");
            return True;
        }
    }
    for(i=2; i<len-3;i++) {
        if(48>=codflight[i] || 57<codflight[i]) {    /*verifica se 0=<num<10*/
            printf("invalid flight code\n");
            return True;
        }
    }
    if(len-3>i && (48>codflight[i+1] || 57<codflight[i+1])) {
        printf("invalid flight code\n");
        return True;
    }
    return False;
}

/*verifica se a date1 é posterior à date2*/
int datecmp (date *date1,date *date2) {
    if(date1->year - date2->year == 1 && date1->day == date2->day && date1->month == date2->month) {
        return True;
    }
    else if(date1->year == date2->year  && date1->month > date2->month) {
        return True;
    }
    else if(date1->year == date2->year  && date1->month == date2->month 
    && date1->day > date2->day) {
        return True;
    }
    else if(date1->year == date2->year  && date1->month == date2->month 
    && date1->day == date2->day) {
        return 2;
    }
    else {
        return False;
    }
}

/*verifica se existe um flight com o codflight e date de partida dados,
     no vector de flights*/
int error_duplicate_add_list_flight(flight flight_) {

    int j = 0;

    for(j = 0; j < num_flights; j++) {
        if(strcmp(flights[j].codflight,flight_.codflight) == 0 
        && datecmp(&flights[j].pardat,&flight_.pardat) == 2) {
            printf("flight already exists\n");
            return True;
        }
    }
    return False;
}

/*verifica se a duracao dada é válida*/
int error_duration(hour *duration) {

    if(duration->hor>12 || (duration->hor == 12 && duration->min > 0)) {
        printf("invalid duration\n");
        return True;
    }
    return False;
}

/*verifca se a date dada é válida*/
int error_date2(date *date_) {

    if (date_->year == curdate.year && date_->month > curdate.month)
        return False;
    else if (date_->year == curdate.year && date_->month == curdate.month 
    && date_->day > curdate.day)
        return False;
    else if(date_->year == curdate.year && date_->month == curdate.month 
    && date_->day == curdate.day)
        return False;
    return True;
}

/*verifica se o codigo de flight dado é válido*/
int error_date(date *date_) {

    if(date_->year-curdate.year == 1 && curdate.month == date_->month 
    && curdate.day == date_->day)
        return False;
    else if(date_->year-curdate.year == 1 && curdate.month == date_->month 
    && curdate.day > date_->day)
        return False;
    else if(date_->year-curdate.year == 1 && curdate.month > date_->month)
        return False;
    else if(!error_date2(date_))
        return False;
    else {
        printf("invalid date\n");
        return True;
    }
}

/*verifica se a capacity do flight dada é válida*/
int error_capacity(int cap) {

    if(cap<10) {
        printf("invalid capacity\n");
        return True;
    }
    return False;
}

/*add o flight dado ao vector de flights atraves da inicializacao da 
posicao num_flights (vazia) do vector*/
int add_flight(flight flight_) {  

    if (num_flights == 30000) {
        printf("too many flights\n");
        return 0;
    }

    strcpy(flights[num_flights].codflight,flight_.codflight);
    strcpy(flights[num_flights].parID,flight_.parID);
    strcpy(flights[num_flights].cheID,flight_.cheID);
    flights[num_flights].pardat.day = flight_.pardat.day;
    flights[num_flights].pardat.month = flight_.pardat.month;
    flights[num_flights].pardat.year = flight_.pardat.year;
    flights[num_flights].parhor.hor = flight_.parhor.hor;
    flights[num_flights].parhor.min = flight_.parhor.min;
    flights[num_flights].dur.hor = flight_.dur.hor;
    flights[num_flights].dur.min = flight_.dur.min;
    flights[num_flights].cap = flight_.cap;
    flights[num_flights].cap_filled = 0;

    num_flights++;
    return 0;
}

/*verifica se um flight com o ID dado existe no vector e 
    aumenta o nflights desse flight caso existe*/
int error_exists(char ID[4], int checker) {
    int h;

    for(h = 0; h<num_airports; h++) {
        if(strcmp(ID,airports[h].ID) == 0) {
            if(checker == True)
                airports[h].nflights += 1;
            return False;
        }
    }
    return True;
}

/*imprime o vector de flights como descrito no enunciado*/
void print_flights() {
    int h;

    for(h = 0; h<num_flights;h++) {
        if(strlen(flights[h].codflight)>0)
        printf("%s %s %s %02d-%02d-%d %02d:%02d\n",flights[h].codflight,
        flights[h].parID,flights[h].cheID,
        flights[h].pardat.day,flights[h].pardat.month,
        flights[h].pardat.year,flights[h].parhor.hor,
        flights[h].parhor.min);
    }
}

/*rotina que processa todos os erros*/
int errors(flight flight_) {
    if(error_invalid(flight_.codflight) || 
        error_duplicate_add_list_flight(flight_))
        return 0;

    if(!error_exists(flight_.parID, True) 
    && !error_exists(flight_.cheID, False)) {
        if(error_date(&flight_.pardat) || error_duration(&flight_.dur) 
        || error_capacity(flight_.cap))
            return 0;

        add_flight(flight_);
    }
    else if (error_exists(flight_.parID, False)) {
        printf("%s: no such airport ID\n", flight_.parID);
        return 0;
    }
    else if (error_exists(flight_.cheID, False)) {
        printf("%s: no such airport ID\n", flight_.cheID);
        return 0;
    }
    return 0;
}

/*le o flight descrito no comando e add-o ao vector se válido*/
int add_list_flight(char command[200]) {

    int comlen = strlen(command);
    flight flight_;

    if(comlen > 2) {
        strtok(command, " ");

        strcpy(flight_.codflight,strtok(NULL," "));
        strcpy(flight_.parID,strtok(NULL," "));
        strcpy(flight_.cheID,strtok(NULL," "));
        flight_.pardat.day = atoi(strtok(NULL,"-"));
        flight_.pardat.month = atoi(strtok(NULL,"-"));
        flight_.pardat.year = atoi(strtok(NULL," "));
        flight_.parhor.hor = atoi(strtok(NULL,":"));
        flight_.parhor.min = atoi(strtok(NULL," "));
        flight_.dur.hor = atoi(strtok(NULL,":"));
        flight_.dur.min = atoi(strtok(NULL," "));
        flight_.cap = atoi(strtok(NULL,"\n"));
        flight_.cap_filled = 0;

        errors(flight_);
        return 0;
    }
    else {
        print_flights();
        return 0;
    }
}

/*passa para a copia do vector flights p todos os flights do vector inicial 
    que tenham como ID de partida ou chegada o ID dado*/
void copy_flights(char ID[4],int checker) {

    int i;
    if(checker == 1) {
        for(i = 0; i <num_flights;i++) {
            if(strcmp(flights[i].parID,ID) == 0) {
                flights_clone_p[num_flights_p] = flights[i];
                num_flights_p += 1;
            }
        }
    }
    else {
        for(i = 0; i <num_flights;i++) {
            if(strcmp(flights[i].cheID,ID) == 0) {
                flights_clone_c[num_flights_c] = flights[i];
                num_flights_c += 1;
            }
        }  
    }
}

/*verifica se a primeira hour1 e posterior a hour2*/
int horcmp_list_aers_start(hour *hour1, hour *hour2) {
    if(hour1->hor > hour2->hor) {
        return True;
    }
    else if(hour1->hor == hour2->hor && hour1->min > hour2->min) {
        return True;
    }
    else {
        return False;
    }
}

/*oderna o vector copia do vector de flights p segundo a date de partida*/
void insertionSort_flights_list_aers_start() {
    int i,j;
    flight key;

    for (i = 1; i < num_flights_p; i++) {

        key = flights_clone_p[i];
        j = i - 1;

        while (j >= 0 && 
        datecmp(&flights_clone_p[j].pardat,&key.pardat) == 1) {
            flights_clone_p[j + 1] = flights_clone_p[j];
            j = j - 1;
        }

        while (j >= 0 && 
        datecmp(&flights_clone_p[j].pardat,&key.pardat) == 2 
        && horcmp_list_aers_start(&flights_clone_p[j].parhor,&key.parhor)) {
            flights_clone_p[j + 1] = flights_clone_p[j];
            j = j - 1;
        }
        flights_clone_p[j + 1] = key;
    }
}

/*oderna o vector copia do vector de flights c segundo a date de chegada*/
void insertionSort_flights_list_aers_dest() {
    int i,j;
    flight key;

    for (i = 1; i < num_flights_c; i++) {
        key = flights_clone_c[i];
        j = i - 1;
        while (j >= 0 
        && datecmp(&flights_clone_c[j].chedat,&key.chedat) == 1) {
            flights_clone_c[j + 1] = flights_clone_c[j];
            j = j - 1;
        }
        while (j >= 0 
        && datecmp(&flights_clone_c[j].chedat,&key.chedat) == 2 
        && horcmp_list_aers_start(&flights_clone_c[j].chehor,&key.chehor)) {
            flights_clone_c[j + 1] = flights_clone_c[j];
            j = j - 1;
        }
        flights_clone_c[j + 1] = key;
    }
}

/*le o ID de partida dado, verifica se é válido e imprime todos os flights 
        com o ID de partida dado por ordem de date de partida*/
int list_aers_start(char command[88]) {
    char ID[4];
    int h;

    strtok(command, " ");

    strcpy(ID,strtok(NULL," \n"));
    
    if(error_exists(ID, False)) {
        printf("%s: no such airport ID\n",ID);
        return 0;
    }
    copy_flights(ID,True);
    insertionSort_flights_list_aers_start();
    for(h = 0; h<num_flights_p;h++) {
        if(strcmp(flights_clone_p[h].parID,ID) == 0)
            printf("%s %s %02d-%02d-%d %02d:%02d\n",
            flights_clone_p[h].codflight,
            flights_clone_p[h].cheID,
            flights_clone_p[h].pardat.day,flights_clone_p[h].pardat.month,
            flights_clone_p[h].pardat.year,flights_clone_p[h].parhor.hor,
            flights_clone_p[h].parhor.min);
    }
    memset(flights_clone_p,0,sizeof num_flights_p);   /*limpa o vector */
    num_flights_p = 0;                             /*para evitar excecoes*/
    return 0;
}

/*verifica se o month tem 31 days*/
int month_biggest(int month) {
    return (((month+1) % 2 == 0 && month <= 7) 
    || month == 8 || month == 10 
    || month == 12);
}

/*inicializa todos os valores da estrutura aux 
    dependendo dos argumentos dados*/
void apply_vals(int day,int month,int year,int hor,int min) {
    aux.newday = day;
    aux.newmonth = month;
    aux.newyear = year;
    aux.newhor = hor;
    aux.newmin = min;
}

/*determina o numero de hours/days a addr á hour de partida*/
void change_hor() {
    while(aux.newmin >= 60) {
            aux.newmin -= 60;
            aux.newhor += 1;
    }
    while(aux.newhor >= 24) {
        if(aux.newhor == 24) {
            aux.newhor = 0;
            aux.newday +=1;
        }
        else {
            aux.newhor -= 24;
            aux.newday += 1;
        }
    }
}

/*determina os inteiros pertencentes á hour e date de chegada*/
void date_cmp2(int day,int month,int year,int hor,int min) {

    apply_vals(day,month,year,hor,min);
    
    
    change_hor();
    
    if(month_biggest(aux.newmonth)) {
        while(aux.newday > 31) {
            aux.newday -= 31;
            aux.newmonth += 1;
        }   
    }
    else if(aux.newmonth == 2) {
        while(aux.newday > 28) {
            aux.newday -= 28;
            aux.newmonth += 1;
        }   
    }
    else {
        while(aux.newday > 30) {
            aux.newday -= 30;
            aux.newmonth += 1;
        }   }
    while(aux.newmonth > 12) {
        aux.newmonth -= 12;
        aux.newyear += 1;
    }
}

/*iguala todos os valores da estrutura aux a 0*/
void reset_aux() {
    aux.newday = 0;
    aux.newmonth = 0;
    aux.newyear = 0;
    aux.newhor = 0;
    aux.newmin = 0;
}

/*soma a date de partida com a duracao a toddos os flights do vetor inicial,
    determinando assim a date de chegada e a hour de chegada*/
void sum_dur() {
    int i;
    int hor_d,min_d,newhor,newmin,newday,newmonth,newyear;

    for(i= 0; i < num_flights;i++) {

        hor_d = flights[i].dur.hor;
        min_d = flights[i].dur.min;

        newmin = flights[i].parhor.min + min_d;
        newhor = flights[i].parhor.hor+ hor_d;
        newday = flights[i].pardat.day;
        newmonth = flights[i].pardat.month;
        newyear = flights[i].pardat.year;

        date_cmp2(newday,newmonth,newyear,newhor,newmin);

        flights[i].chedat.day = aux.newday;
        flights[i].chedat.month = aux.newmonth;
        flights[i].chedat.year = aux.newyear;
        flights[i].chehor.hor = aux.newhor;
        flights[i].chehor.min = aux.newmin;

        reset_aux();
    }
}

/*le o ID de chegada dado, vê se é válido e de seguida imprime todos os 
flights com o ID de chegada dado por ordem de date de chegada*/
int list_aers_dest(char command[88]) {
    char ID[4];
    int h;

    strtok(command, " ");
    strcpy(ID,strtok(NULL," \n\t"));
    
    if(error_exists(ID, False)) {
        printf("%s: no such airport ID\n",ID);
        return 0;
    }
    sum_dur();
    copy_flights(ID,False);
    insertionSort_flights_list_aers_dest();
    for(h = 0; h<num_flights;h++) {
        if(strcmp(ID,flights_clone_c[h].cheID) == 0)
            printf("%s %s %02d-%02d-%02d %02d:%02d\n",
            flights_clone_c[h].codflight,
            flights_clone_c[h].parID,flights_clone_c[h].chedat.day,
            flights_clone_c[h].chedat.month,
            flights_clone_c[h].chedat.year,flights_clone_c[h].chehor.hor,
            flights_clone_c[h].chehor.min);
    }
    memset(flights_clone_c,0,sizeof num_flights_c);
    num_flights_c = 0;
    return 0;
}

/*le a date dada no comando e substitui a date presente por essa nova date*/
int adv_date(char command[88]) {

    date newdate;

    strtok(command, " ");
    newdate.day = atoi(strtok(NULL,"-"));
    newdate.month = atoi(strtok(NULL,"-"));
    newdate.year = atoi(strtok(NULL,"\t\n"));

    if(!datecmp(&newdate,&curdate)) {
        printf("invalid date\n");
        return 0;
    }

    curdate.day = newdate.day;
    curdate.month = newdate.month;
    curdate.year = newdate.year;

    printf("%02d-%02d-%02d\n",curdate.day,curdate.month,curdate.year);
    return 0;
}
