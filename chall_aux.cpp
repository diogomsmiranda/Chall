#include "chall_structs.hpp"

string get_origin(flight_t *flight) { return flight->origin; }
string get_destiny(flight_t *flight) { return flight->destiny; }
string get_start_date(flight_t *flight) { return flight->start_date; }
string get_passengers(flight_t *flight) { return flight->passengers; }
string get_start_time(flight_t *flight) { return flight->start_time; }
string get_end_time(flight_t *flight) { return flight->end_time; }
string get_duration(flight_t *flight) { return flight->duration; }
string get_flight_number(flight_t *flight) { return flight->flight_number; }
string get_cost(flight_t *flight) { return flight->cost; }

void print_flight(flight_t *flight) { 
    printf("%s | %s | %s | %s | %s | %s | %s | %s | %s\n", flight->origin.c_str(), 
    flight->destiny.c_str(), flight->start_date.c_str(), flight->passengers.c_str(), 
    flight->start_time.c_str(), flight->end_time.c_str(), flight->duration.c_str(), 
    flight->flight_number.c_str(), flight->cost.c_str());
}

flight_t create_flight(string chunk) {
    flight_t current;
    current.origin = strtok((char*)chunk.c_str(), " ");
    current.destiny = strtok(NULL, " ");
    current.start_date = strtok(NULL, " ");
    current.passengers = strtok(NULL, " ");
    current.start_time = strtok(NULL, " ");
    current.end_time = strtok(NULL, " ");
    current.duration = strtok(NULL, " ");
    current.flight_number = strtok(NULL, " ");
    current.cost = strtok(NULL, " ");
    current.airplane_n = strtok(NULL, " ");
    return current;
}

client_t create_client(string chunk) {
    client_t current;
    current.name = strtok((char*)chunk.c_str(), " ");
    current.mail = strtok(NULL, " ");
    current.contact = strtok(NULL, " ");
    current.address = strtok(NULL, " ");
    current.credit = strtok(NULL, " ");
    current.lastflight = strtok(NULL, " ");
    return current;
}

ticket_t create_ticket(client_t client, flight_t flight) {
    ticket_t current;
    current.flight_number = flight.flight_number;
    current.client_name = client.name;
    current.client_mail = client.mail;
    current.client_contact = client.contact;
    current.client_address = client.address;
    current.client_credit = client.credit;
    current.client_password = client.password;
    current.client_lastflight = client.lastflight;
    current.flight_origin = flight.origin;
    current.flight_destiny = flight.destiny;
    current.flight_start_date = flight.start_date;
    current.flight_start_time = flight.start_time;
    current.flight_end_time = flight.end_time;
    current.flight_duration = flight.duration;
    current.flight_cost = flight.cost;
    current.flight_airplane_n = flight.airplane_n;
    current.client_bag = client.bag;
    return current;
}

ticket_t create_ticket_string(string chunk) {
    ticket_t current;
    current.flight_number = strtok((char*)chunk.c_str(), " ");
    current.client_name = strtok(NULL, " ");
    current.client_mail = strtok(NULL, " ");
    current.client_contact = strtok(NULL, " ");
    current.client_address = strtok(NULL, " ");
    current.client_credit = strtok(NULL, " ");
    current.client_password = strtok(NULL, " ");
    current.client_lastflight = strtok(NULL, " ");
    current.flight_origin = strtok(NULL, " ");
    current.flight_destiny = strtok(NULL, " ");
    current.flight_start_date = strtok(NULL, " ");
    current.flight_start_time = strtok(NULL, " ");
    current.flight_end_time = strtok(NULL, " ");
    current.flight_duration = strtok(NULL, " ");
    current.flight_cost = strtok(NULL, " ");
    current.flight_airplane_n = strtok(NULL, " ");
    current.client_bag = strtok(NULL, " ");
    return current;
}

string ticket_to_str(ticket_t ticket) { return ticket.flight_number + " " + ticket.client_name + " " + ticket.client_mail + " " + ticket.client_contact + " " + ticket.client_address + " " + ticket.client_credit + " " + ticket.client_password + " " + ticket.client_lastflight + " " + ticket.flight_origin + " " + ticket.flight_destiny + " " + ticket.flight_start_date + " " + ticket.flight_start_time + " " + ticket.flight_end_time + " " + ticket.flight_duration + " " + ticket.flight_cost + " " + ticket.flight_airplane_n; }

string client_to_str(client_t client) { return client.name + " " + client.mail + " " + client.contact + " " + client.address + " " + client.credit + " " + client.password + " " + client.lastflight; }

void sort_start(vector <flight_t> &flights) {
    sort(flights.begin(), flights.end(), [](flight_t a, flight_t b) {
        int a_hour = stoi(a.start_time.substr(0, 2));
        int a_min = stoi(a.start_time.substr(3, 2));
        int b_hour = stoi(b.start_time.substr(0, 2));
        int b_min = stoi(b.start_time.substr(3, 2));
        if (a_hour == b_hour) {
            return a_min < b_min;
        } else {
            return a_hour < b_hour;
        }
    });
}

void sort_end(vector <flight_t> &flights) {
    sort(flights.begin(), flights.end(), [](flight_t a, flight_t b) {
        int a_hour = stoi(a.end_time.substr(0, 2));
        int a_min = stoi(a.end_time.substr(3, 2));
        int b_hour = stoi(b.end_time.substr(0, 2));
        int b_min = stoi(b.end_time.substr(3, 2));
        if (a_hour == b_hour) {
            return a_min < b_min;
        } else {
            return a_hour < b_hour;
        }
    });
}

void sort_dur(vector <flight_t> &flights) {
    sort(flights.begin(), flights.end(), [](flight_t a, flight_t b) {
        int a_hour = stoi(a.duration.substr(0, 2));
        int a_min = stoi(a.duration.substr(3, 2));
        int b_hour = stoi(b.duration.substr(0, 2));
        int b_min = stoi(b.duration.substr(3, 2));
        if (a_hour == b_hour) {
            return a_min < b_min;
        } else {
            return a_hour < b_hour;
        }
    });
}

void sort_price(vector <flight_t> &flights) {
    sort(flights.begin(), flights.end(), [](flight_t a, flight_t b) {
        return stoi(a.cost) < stoi(b.cost);
    });
}


bool verify_airport(string word) {
    return (word.length() == 3 && all_of(word.begin(), word.end(), [](unsigned char c){ return isupper(c); }));
}
bool verify_date(string word) {
    for (int i = 0; i < (int)word.length(); i++) {
        if (i == 2 || i == 5) {
            if (word[i] != '/') return false;
        } else {
            if (!isdigit(word[i])) return false;
        }
    }
    return (word.length() == 8);
}
bool verify_number(string word) {
    return (all_of(word.begin(), word.end(), [](unsigned int c){ return isdigit(c); }));
}
bool verify_time(string word) {
    for (int i = 0; i < (int)word.length(); i++) {
        if (i == 2) {
            if (word[i] != ':') return false;
        } else {
            if (!isdigit(word[i])) return false;
        }
    }
    return (word.length() == 5);
}
bool verify_phone(string word) {
    return (verify_number(word) && word.length() == 9);
}
bool verify_credit(string word) {
    return (verify_number(word) && word.length() == 16);
}
bool verify_name(string word) {
    return (all_of(word.begin(), word.end(), [](unsigned char c){ return isalpha(c); }));
}

