/*
Projecto 2 - IAED 2021/22


Trabalho realizado por:                              
Diogo Miranda ist1 102536
*/

#include "proj1.h"


/*adds to the cap_filled of the flight which code is the same as newres the number of n_pass in newres*/
int add_pass(res *newres) {
    int i;
    for(i = 0; i < num_flights;i++) {
        if(strcmp(flights[i].codflight,newres->codflight) == 0 && datecmp(&flights[i].pardat,&newres->rdate) == 2) {
            if(flights[i].cap_filled + newres->n_pass > flights[i].cap) {
                printf("too many reservations\n");
                return False;
            }
            flights[i].cap_filled += newres->n_pass;
            break;
        }
    }
    return True;
}

/*append to the end the structure newres to the linked list head*/
void add_res(res *newres, res **head) {
    res *aux = *head;
    if(aux == NULL || aux->codres == NULL) {
        if(!add_pass(newres) || error_date(&newres->rdate))
            return;
        *head = newres;
    }
    else {
        while(aux->next != NULL) {
            aux = aux->next;
        }
        if(!add_pass(newres))
            return;
        aux->next = newres;
    }
}


/*prints the codres and npass of all the res in linked list which codflight and new date is the same*/
void list_res(res **head, char codflight[CODLEN], date newdate) {  
    res *aux;
    aux = *head;
    while(aux != NULL) {
        if(strcmp(aux->codflight,codflight) == 0 && aux->rdate.day == newdate.day && aux->rdate.month == newdate.month && aux->rdate.year == newdate.year) {
            printf("%s %d\n",aux->codres,aux->n_pass);
        }
        aux = aux->next;
    }
}

res* getMid(res* head) {
    res* midPrev = NULL;
    res* mid = NULL;
    while (head && head->next) {
        midPrev = (midPrev == NULL) ? head : midPrev->next;
        head = head->next->next;
    }
    mid = midPrev->next;
    midPrev->next = NULL;
    return mid;
}

res *merge(res* list1, res* list2) {
    res dummyHead;
    res* ptr = &dummyHead;
    while (list1 && list2) {
        if (strcmp(list1->codres,list2->codres) < 0) {
            ptr->next = list1;
            list1 = list1->next;
        } else {
            ptr->next = list2;
            list2 = list2->next;
        }
        ptr = ptr->next;
    }
    if(list1) ptr->next = list1;
    else ptr->next = list2;
    return dummyHead.next;
}

res *sort_res(res* head) {
    res *mid = NULL;
    res *left = NULL;
    res *right = NULL;
    if (!head || !head->next)
        return head;
    mid = getMid(head);
    left = sort_res(head);
    right = sort_res(mid);
    return merge(left, right);
}

date new_date(char *str) {
    date newdate;
    newdate.day = atoi(strtok(str,"-"));
    newdate.month = atoi(strtok(NULL,"-"));
    newdate.year = atoi(strtok(NULL,"\t\n"));
    return newdate;
}

int error_codflight_exist(char codflight[CODLEN],date date2) {
    int i;
    for(i = 0; i<num_flights;i++) {
        if(strcmp(flights[i].codflight,codflight) == 0 && datecmp(&flights[i].pardat,&date2) == 2)
            return True;
    }
    printf("%s: flight does not exist\n",codflight);
    return False;
}

int error_codres_exist(res *head,char codres[CODLEN]) {
    res *temp;
    temp = head;
    while(temp != NULL) {
        if(strcmp(temp->codres,codres) == 0) {
            printf("%s: flight reservation already used\n",codres);
            return True;
        }
        temp = temp->next;
    }
    return False;
}

int check_res_valid(char * codres) {
    char c;
    int i = 0;
    if(strlen(codres) < 10) {
        printf("invalid reservation code\n");
        return False;
    }
    for(i =0; i<(int)strlen(codres); i++) {
        c = codres[i];
        if(!isupper(c) && !isdigit(c)) {
            printf("invalid reservation code\n");
            return False;
        }
    }
    return True;
}

/*add or list reserves*/
void add_list_res(char command[CMDLEN], res **head) {
    res *newres = malloc(sizeof(res));
    res *aux;
    char *temp = malloc(sizeof(char));
    char ndate[DATELEN],codflight[CODLEN];
    char buffer[CMDLEN];
    date newdate;

    if(strlen(command) <= 19) {
        strtok(command, " ");
        strcpy(codflight,strtok(NULL," \t"));
        newdate = new_date(strtok(NULL," \t"));
        if(!error_codflight_exist(codflight,newdate) || error_date(&newdate)) {
            free(newres);
            free(temp);
            return;
        }
        *head = sort_res(*head);
        list_res(head,codflight,newdate);

    }
    else {
        aux = *head;
        strtok(command, " ");
        strcpy(newres->codflight,strtok(NULL," \t"));
        strcpy(ndate,strtok(NULL," \t"));
        strcpy(buffer,strtok(NULL," \t"));
        newres->codres = malloc(strlen(buffer)+1);
        strcpy(newres->codres,buffer);
        newres->n_pass = atoi(strtok(NULL," \t\n"));
        newdate = new_date(ndate);
        if(!error_codflight_exist(newres->codflight,newdate)) {
            free(newres);
            free(temp);
            return;
        }
        newres->rdate = newdate;
        
        if(!check_res_valid(newres->codres)) {
            free(newres);
            free(temp);
            return;
        }
        else if(aux != NULL && aux->codres != NULL && error_codres_exist(aux,newres->codres)) {
            return;
        }
        if(newres->n_pass <=0 || (int)newres->n_pass != newres->n_pass) {
            printf("invalid passenger number\n");
            return;
        }
        newres->next = NULL;
        add_res(newres,head);
    }
}

void erase_cap_f(res *newres) {
    int i;
    /*iterate through flights and subtract the n_pass of res to the flight cap_filled which codflights coincide*/
    for(i = 0; i<num_flights;i++) {
        if(strcmp(flights[i].codflight,newres->codflight) == 0 && datecmp(&flights[i].pardat,&newres->rdate) == 2) {
            flights[i].cap_filled -= newres->n_pass;
        }
    }
}

/*erase from linked list starting in head every node which strcmp(node->codflight,code) == 0*/
void erase_res(char *code, res **head) {
    res *temp = *head, *prev;
    for(temp = *head, prev = NULL; temp != NULL; prev = temp, temp = temp->next) {
        if(strcmp(temp->codres,code) == 0) {
            if(temp == *head) {
                *head = temp->next;
                erase_cap_f(temp);
                free(temp->codres);
                free(temp);
                return;
            }
            else {
                prev->next = temp->next;
                erase_cap_f(temp);
                free(temp->codres);
                free(temp);
                return;
            }
        }  
    }
}

void erase_res_f(char *code, res **head) {

    res *temp = *head, *prev;

    if (temp != NULL && strcmp(temp->codflight,code) == 0) {
        *head = temp->next;
        return;
    }

    while (temp != NULL && strcmp(temp->codflight,code) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL)
        return;

    prev->next = temp->next;
}


/*erase flights*/
void erase_flight(char *code, res **head) {
    int i=0,j=0;
  while (i < num_flights && num_flights > 0)
  {
    if (strcmp(flights[i].codflight,code) == 0) {
            
        if (i < (num_flights - 1)) {
            for ( j = i; j < (num_flights - 1); j++) {
                erase_res_f(code,head);
                flights[j] = flights[j + 1];
            }
        }
        num_flights--;
    }
    else i++;
  }
}
/*check if res exists*/
int check_res(char *code, res **head) {
    res *temp = *head;
    int counter = 0;
    while(temp != NULL) {
        if(temp->codres != NULL && strcmp(temp->codres,code) == 0) {
            counter = 1;
            break;
        }
        temp = temp->next;
    }
    return counter;
}
/*check if flight exists*/
int checkflight(char *code) {
    int i;
    for(i = 0; i<num_flights;i++) {
        if(strcmp(flights[i].codflight,code) == 0) {
            return True;
        }
    }
    return False;
}

/*erase all the reses and flights*/
void erase_res_flight(char *code, res **head) {

    if(!check_res(code,head) && !checkflight(code)) {
        printf("not found\n");
    }
    else if(check_res(code,head)) {  
        erase_res(code,head);
    }
    else if(checkflight(code)) {
        erase_flight(code,head);
    }
    return;
}
/*le o comando e de seguida redireciona o programa para as suas diferentes 
    rotinas*/
int main() {
    char command[CMDLEN];
    res *head = malloc(sizeof(res));
    head->next = NULL;
    head->codres = NULL;
    set_date();
    while(True) {
        fgets(command, sizeof command, stdin);
        switch(command[0]) {
            case 'q': exit(0);
            break;
            case 'a': add_aer(command);
            break;
            case 'l': list_aers(command);
            break;
            case 'v': add_list_flight(command);
            break;
            case 'p': list_aers_start(command);
            break;
            case 'c': list_aers_dest(command);
            break;
            case 't': adv_date(command);
            break;
            case 'r': add_list_res(command, &head);
            break;
            case 'e': strtok(command," "); 
                erase_res_flight(strtok(NULL," \n\t"),&head);
            break;
        }
    }
    return 0;
}
