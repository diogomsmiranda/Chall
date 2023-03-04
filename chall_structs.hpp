#include <iostream>


using namespace std;


typedef struct flight {
    string origin;
    string destiny;
    string start_date;
    string pass_number;
    string start_time;
    string end_time;
    string flight_number;
    string cost;
}flight_t ;

string get_origin(flight_t *flight);
string get_destiny(flight_t *flight);
string get_start_date(flight_t *flight);
string get_pass_number(flight_t *flight);
string get_start_time(flight_t *flight);
string get_end_time(flight_t *flight);
string get_flight_number(flight_t *flight);
string get_cost(flight_t *flight);
flight_t create_flight(string chunk);

