#include "chall_structs.hpp"

void print_flight(flight_t *flight) { 
    printf("%s | %s | %s | %s | %s | %s | %s | %s | %s\n", flight->origin.c_str(), 
    flight->destiny.c_str(), flight->start_date.c_str(), flight->client_number.c_str(), 
    flight->start_time.c_str(), flight->end_time.c_str(), flight->duration.c_str(), 
    flight->flight_number.c_str(), flight->cost.c_str());
}

flight_t create_flight(string chunk) {
    flight_t current;
    //split the string into all the fields using strtok
    current.origin = strtok((char*)chunk.c_str(), " ");
    current.destiny = strtok(NULL, " ");
    current.start_date = strtok(NULL, " ");
    current.client_number = strtok(NULL, " ");
    current.start_time = strtok(NULL, " ");
    current.end_time = strtok(NULL, " ");
    current.duration = strtok(NULL, " ");
    current.flight_number = strtok(NULL, " ");
    current.cost = strtok(NULL, " ");
    return current;
}

void process_flights() {
    string line;
    ifstream file("flights.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            flight_t current = create_flight(line);
            flights.push_back(current);
        }
        file.close();
    }
    else {
        printf("Unable to open file");
    }
}

flight_t search_prompt() {

    flight_t f;
    printf("Introduza a cidade de origem: ");
    cin >> f.origin;
    printf("Introduza a cidade de destino: ");
    cin >> f.destiny;
    printf("Introduza a data de partida (DD/MM/YY): ");
    cin >> f.start_date;
    printf("Introduza o numero de passageiros: ");
    cin >> f.client_number;


    return f;
}

//asks for user to input his name, mail, phone number, adress, credit card
void process_checkout() {
    string name, mail, phone, adress, credit_card;
    printf("Introduza o seu nome: ");
    cin >> name;
    printf("Introduza o seu email: ");
    cin >> mail;
    printf("Introduza o seu numero de telefone: ");
    cin >> phone;
    printf("Introduza o seu endereco: ");
    cin >> adress;
    printf("Introduza o seu numero de cartao de credito: ");
    cin >> credit_card;

    printf("Obrigada pela sua compra! A fatura será adicionada como um file (fatura.txt) no diretório atual.\n");
}


void checkout_prompt(vector<flight_t> displayed) {
    int index;
    printf("Introduza o numero do voo que pretende comprar: ");
    cin >> index;

    //checks if index is valid
    if (index < 0 || index > (int)flights.size()) {
        printf("Numero invalido, tente novamente.\n");
        checkout_prompt(displayed);
    }
    else {
        printf("A prosseguir para o checkout do voo: ");
        print_flight(&displayed[index]);
        process_checkout();
    }
}

vector<flight_t> search_flights(flight_t f) {
    vector<flight_t> found;

    //searches for flights that match the search criteria
    for(int i = 0; i < (int)flights.size(); i++) {
        //print both flights being compared
        if (f.origin == flights[i].origin && f.destiny == flights[i].destiny && f.start_date == flights[i].start_date) {
            found.push_back(flights[i]);
        }
    }

    return found;
}

void display_flights(vector<flight_t> arg) {
    for(int i = 0; i < arg.size(); i++) {
        printf("%d. ", i);
        print_flight(&arg[i]);
    }
}


void welcome_message() {
    string buffer;
    string message = "Bem-Vindo á nossa flight search engine!\n Aqui podes pesquisar sobre os voos disponiveis e comprar bilhetes.\n\n :: Pequenas Regras sobre a nossa engine ::\n -> Nomes das cidades para simplificação são abreviadas a 3 letras. ex: LIS para Lisboa\n -> Datas são aceites no formate DD/MM/YY\n -> Só os últimos dois digitos do ano são especificados sendo todos os voos passados no séc 21.\n\n Para começar a pesquisar podes introduzir o comando ,#.\n Obrigado por utilizares a nossa engine!!\n";

    printf("%s", message.c_str());

    cin >> buffer;

    if (buffer != "#") {
        printf("Comando invalido, tente novamente.\n");
        welcome_message();
    }
}

int main() {
    // figurative flight that will be used to search for flights
    flight_t search_f;
    vector<flight_t> searched_f;

    process_flights();

    welcome_message();
    search_f = search_prompt();
    searched_f = search_flights(search_f);
    display_flights(searched_f);
    checkout_prompt(searched_f);
}