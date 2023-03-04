#include "chall_structs.hpp"

string get_origin(flight_t *flight) return flight->origin;
string get_destiny(flight_t *flight) return flight->destiny;
string get_start_date(flight_t *flight) return flight->start_date;
string get_client_number(flight_t *flight) return flight->client_number;
string get_start_time(flight_t *flight) return flight->start_time;
string get_end_time(flight_t *flight) return flight->end_time;
string get_duration(flight_t *flight) return flight->duration;
string get_flight_number(flight_t *flight) return flight->flight_number;
string get_cost(flight_t *flight) return flight->cost;
vector<flight_t> get_clients(flight_t *flight) return flight->clients;