#include "chall_structs.hpp"
#include "chall_text.hpp"


vector<flight_t> flights;
vector<client_t> clients;

ticket_t ticket;

int option_of_bag;

void save_client(client_t client,flight_t flight) {
    ofstream file;
    ifstream file1;
    bool empty = false;
    //check if file1 is empty
    file1.open("clients/" + client.name + ".txt");
    if(file1.peek() == std::ifstream::traits_type::eof()) {
        empty = true;
    }
    file1.close();

    file.open("clients/" + client.name + ".txt");
    //if the file is empty write the client info if not jump to last line available an write ticket info
    if (empty) {
        file << client_to_str(client) << endl;
        file << "Tickets:" << endl;
    }
    file << ticket_to_str(create_ticket(client, flight)) << endl;
}

void process_flights() {
    string line;
    ifstream file("flights.txt");
    flight_t current;
    if (file.is_open()) {
        while (getline(file, line)) {
            current = create_flight(line);
            flights.push_back(current);
        }
        file.close();
    }
    else {
        printf("Unable to open file");
    }
}

void process_clients() {
    string line;
    ifstream file("clients.txt");
    client_t current;
    if (file.is_open()) {
        while (getline(file, line)) {
            current = create_client(line);
            clients.push_back(current);
        }
        file.close();
    }
    else {
        printf("Unable to open file");
    }
}

void create_invoice(client_t client, flight_t flight) {
    ofstream file;
    file.open("fatura.txt");
    file << "Nome: " << client.name << endl;
    file << "Email: " << client.mail << endl;
    file << "Contacto: " << client.contact << endl;
    file << "Morada: " << client.address << endl;
    file << "Cartao de credito: " << client.credit << endl;
    file << "Número do Avião: " << flight.airplane_n << endl;
    file << "Número do Voo: " << flight.flight_number << endl;
    file << "Origem: " << flight.origin << endl;
    file << "Destino: " << flight.destiny << endl;
    file << "Data de partida: " << flight.start_date << endl;
    file << "Hora de partida: " << flight.start_time << endl;
    file << "Hora de chegada: " << flight.end_time << endl;
    file << "Duração: " << flight.duration << endl;
    if(option_of_bag == 2) {
        file << "Bagagem: Sim" << endl;
        file << "Preço: " << stoi(flight.cost) + 30 << endl;
    }
    else {
        file << "Bagagem: Não" << endl;
        file << "Preço: " << stoi(flight.cost) << endl;
    }
    file.close();

    ticket = create_ticket(client, flight);
}

vector<flight_t> sort_prompt(vector<flight_t> found) {
    
    int option;
    
    cout << text_sort;
    cin >> option;

    switch (option) {
    case 1:
        sort_end(found);
        break;
    case 2:
        sort_dur(found);
        break;
    case 3:
        sort_price(found);
        break;
    case 0:
        sort_start(found);
        break;
    default:
        cout << error_option;
        sort_prompt(found);
        break;
    }

    return found;
}

flight_t search_prompt() {

    flight_t f;
    string buffer;

    // get origin airport
    while(true) {
        cout << text_origin;
        cin >> buffer;
        if (verify_airport(buffer)) { f.origin = buffer; break; }
        else { cout << error_airport << endl; }
    }
    
    // get destination airport
    while(true) {
        cout << text_destination;
        cin >> buffer;
        if (verify_airport(buffer)) { f.destiny = buffer; break; }
        else { cout << error_airport << endl; }
    }

    // get start date
    while(true) {
        cout << text_date;
        cin >> buffer;
        if (verify_date(buffer)) { f.start_date = buffer; break; }
        else { cout << error_date << endl; }
    }

    // get number of passengers
    while(true) {
        cout << text_passengers;
        cin >> buffer;
        if (verify_number(buffer)) { f.passengers = stoi(buffer); break; }
        else { cout << error_number << endl; }
    }

    return f;
}

//asks for user to input his name, mail, phone number, adress, credit card
client_t process_checkout(flight_t flight) {

    string name, mail, phone, address, credit;

    // get client name
    while(true) {
        cout << text_name;
        cin >> name;
        if(verify_name(name)) { break; }
        else { cout << error_name << endl; }
    }

    // get client mail
    while(true) {
        cout << text_mail;
        cin >> mail;
        break;
    }

    // get client phone number
    while(true) {
        cout << text_phone;
        cin >> phone;
        if(verify_phone(phone)) { break; }
        else { cout << error_phone << endl; }
    }

    // get client address
    while(true) {
        cout << text_address;
        cin >> address;
        break;
    }

    // get credit card
    while(true) {
        cout << text_credit;
        cin >> credit;
        if(verify_credit(credit)) { break; }
        else { cout << error_credit << endl; }
    }
    string client_info = name + " " + mail + " " + phone + " " + address + " " + credit+ " " + flight.airplane_n;

    cout << text_buySuccess;

    return create_client(client_info);
}


flight_t checkout_prompt(vector<flight_t> displayed) {
    int index;

    cout << text_buy;
    cin >> index;
    cout << text_baggage;
    cin >> option_of_bag;

    //checks if index is valid
    if (index < 0 || index > (int)flights.size()) {
        cout << error_buy;
        checkout_prompt(displayed);
    }
    else {
        cout << success_buy;
        print_flight(&displayed[index]);
    }

    return displayed[index];
}

vector<flight_t> search_flights(flight_t f) {
    vector<flight_t> found;

    //searches for flights that match the search criteria
    for(int i = 0; i < (int)flights.size(); i++) {
        //print both flights being compared
        if (((f.origin == flights[i].origin && f.destiny == flights[i].destiny) || (f.origin == flights[i].destiny && f.destiny == flights[i].origin)) && f.start_date == flights[i].start_date) {
            found.push_back(flights[i]);
        }
    }

    return found;
}

void display_flights(vector<flight_t> arg) {
    for(int i = 0; i < (int)arg.size(); i++) {
        printf("%d. ", i);
        print_flight(&arg[i]);
    }
}


int main() {
    flight_t search_f;
    vector<flight_t> searched_f;
    flight_t flight;
    client_t client;

    process_flights();
    process_clients();

    cout << text_welcomeMessage << endl;

    search_f = search_prompt();
    searched_f = search_flights(search_f);
    display_flights(sort_prompt(searched_f));
    flight = checkout_prompt(searched_f);
    client = process_checkout(flight);
    create_invoice(client, flight);
    
    save_client(client,flight);
    return 0;
}