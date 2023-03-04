#include "chall_structs.h"
#include <iostream>

string get_origin(flight_t *flight) return flight->origin;
string get_destiny(flight_t *flight) return flight->destiny;
string get_start_date(flight_t *flight) return flight->start_date;
string get_pass_number(flight_t *flight) return flight->pass_number;
string get_start_time(flight_t *flight) return flight->start_time;
string get_end_time(flight_t *flight) return flight->end_time;
string get_flight_number(flight_t *flight) return flight->flight_number;
string get_cost(flight_t *flight) return flight->cost;

flight_t create_flight(string chunk) {
    flight_t current;
    current.origin = chunk.substr(0, chunk.find(" "));
    current.destiny = chunk.substr(0, chunk.find(" "));
    current.start_date = chunk.substr(0, chunk.find(" "));
    current.pass_number = chunk.substr(0, chunk.find(" "));
    current.start_time = chunk.substr(0, chunk.find(" "));
    current.end_time = chunk.substr(0, chunk.find(" "));
    current.flight_number = chunk.substr(0, chunk.find(" "));
    current.cost = chunk.substr(0, chunk.find(" "));
    return current;
}