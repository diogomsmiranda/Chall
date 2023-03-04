#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>

using namespace std;

typedef struct client {
    string name;
    string mail;
    string contact;
    string address;
    string credit;
}client_t;

typedef struct flight {
    string origin;
    string destiny;
    string start_date;
    string client_number;
    string start_time;
    string end_time;
    string duration;
    string flight_number;
    string cost;
    vector <client_t> clients;
}flight_t ;


unordered_set<flight_t> flights;


string get_origin(flight_t *flight);
string get_destiny(flight_t *flight);
string get_start_date(flight_t *flight);
string get_client_number(flight_t *flight);
string get_start_time(flight_t *flight);
string get_end_time(flight_t *flight);
string get_duration(flight_t *flight);
string get_flight_number(flight_t *flight);
string get_cost(flight_t *flight);
vector <client_t> get_clients(flight_t *flight);
flight_t create_flight(string chunk);
void print_flight(flight_t *flight);

