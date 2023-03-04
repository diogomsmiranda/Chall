#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;


// Structs
typedef struct flight {
    string origin;
    string destiny;
    string start_date;
    string passengers;
    string start_time;
    string end_time;
    string duration;
    string flight_number;
    string cost;
    string airplane_n;
}flight_t;

typedef struct client {
    string name;
    string mail;
    string contact;
    string address;
    string credit;
    string password;
    vector<flight_t> flights;
    string lastflight;
    bool bag;
}client_t;

typedef struct ticket {
    string flight_number;
    string client_name;
    string client_mail;
    string client_contact;
    string client_address;
    string client_credit;
    string client_password;
    string client_lastflight;
    string flight_origin;
    string flight_destiny;
    string flight_start_date;
    string flight_start_time;
    string flight_end_time;
    string flight_duration;
    string flight_cost;
    string flight_airplane_n;
    bool client_bag;
}ticket_t;


// Functions squeletons
string get_origin(flight_t *flight);
string get_destiny(flight_t *flight);
string get_start_date(flight_t *flight);
string get_passengers(flight_t *flight);
string get_start_time(flight_t *flight);
string get_end_time(flight_t *flight);
string get_duration(flight_t *flight);
string get_flight_number(flight_t *flight);
string get_cost(flight_t *flight);
vector <client_t> get_clients(flight_t *flight);
flight_t create_flight(string chunk);
client_t create_client(string chunk);
ticket_t create_ticket(client_t client, flight_t flight);
ticket_t create_ticket_string(string chunk);
string ticket_to_str(ticket_t ticket);
string client_to_str(client_t client);
void print_flight(flight_t *flight);
void sort_start(vector <flight_t> &flights);
void sort_end(vector <flight_t> &flights);
void sort_dur(vector <flight_t> &flights);
void sort_price(vector <flight_t> &flights);
bool verify_airport(string word);
bool verify_date(string word);
bool verify_time(string word);
bool verify_number(string word);
bool verify_credit(string word);
bool verify_phone(string word);
bool verify_name(string word);
void mmenu_prompt();