#ifndef _myfuncs_
#define _myfuncs_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defs_structs.h"


void set_date();
int error_upper(char ID[4]);
int error_duplicate(char ID[4]);
int add_airport(airport aer);
int add_aer(char command[88]);
void insertionSort_aers();
void print_aers();
int print_list_aers(char ID_l[4]);
int list_aers(char command[200]);
int error_invalid(char codflight[CODLEN]);
int datecmp (date *date1,date *date2);
int error_duplicate_add_list_flight(flight flight_);
int error_duration(hour *duration);
int error_date2(date *date_);
int error_date(date *date_);
int error_capacity(int cap);
int add_flight(flight flight_);
int error_exists(char ID[4], int checker);
void print_flights();
int errors(flight flight_);
int add_list_flight(char command[200]);
void copy_flights(char ID[4],int checker);
int horcmp_list_aers_start(hour *hour1, hour *hour2);
void insertionSort_flights_list_aers_start();
void insertionSort_flights_list_aers_dest();
int list_aers_start(char command[88]);
int month_biggest(int month);
void apply_vals(int day,int month,int year,int hor,int min);
void change_hor();
void date_cmp2(int day,int month,int year,int hor,int min);
void reset_aux();
void sum_dur();
int list_aers_dest(char command[88]);
int adv_date(char command[88]);

#endif
