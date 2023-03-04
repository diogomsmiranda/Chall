#include "chall_structs.hpp"

flight_t search_prompt() {

    flight_t f;
    printf("Introduza a cidade de origem: ");
    cin >> f.origin;
    printf("Introduza a cidade de destino: ");
    cin >> f.destiny;
    printf("Introduza a data de partida (DD/MM/YY): ");
    cin >> f.start_date;
    printf("Introduza o numero de passageiros: ");
    cin >> f.pass_number;


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
    if (index < 1 || index > flights.size()) {
        printf("Numero invalido, tente novamente.\n");
        checkout_prompt(displayed);
    }
    else {
        printf("A prosseguir para o checkout do voo: ");
        printf_flight(displayed[index-1]);
        process_checkout();
    }
}

vector<flight_t> search_flights(flight_t f) {
    vector<flight_t> flights;

    //searches for flights that match the search criteria
    for (auto it = flights.begin(); it != flights.end(); it++) {
        if (it->origin == f.origin && it->destiny == f.destiny && it->start_date == f.start_date && it->pass_number == f.pass_number) {
            flights.push_back(*it);
        }
    }

    return flights;
}

void display_flights(vector<flight_t> arg) {
    for(int i = 0; i < flights.size(); i++) {
        printf("%d. ", i);
        printf_flight(arg[i]);
    }
}

//prints flight to display to user using | as a separator
void printf_flight(flight_t f) { printf("%s | %s | %s | %s | %s | %s | %s | %s\n", f.origin, f.destiny, f.start_date, f.pass_number, f.start_time, f.end_time, f.flight_number, f.cost); }

void welcome_message() {
    string buffer;
    string message = "Bem-Vindo á nossa flight search engine!\n Aqui podes pesquisar sobre os voos disponiveis e comprar bilhetes.\n\n :: Pequenas Regras sobre a nossa engine ::\n -> Nomes das cidades para simplificação são abreviadas a 3 letras. ex: LIS para Lisboa\n -> Datas são aceites no formate DD/MM/YY\n -> Só os últimos dois digitos do ano são especificados sendo todos os voos passados no séc 21.\n\n Para começar a pesquisar podes introduzir o comando ,#.\n Obrigado por utilizares a nossa engine!!\n";

    printf("%s", message);

    cin >> buffer;

    if (buffer == "#") {
        search_prompt();
    }
    else {
        printf("Comando invalido, tente novamente.\n");
        welcome_message();
    }
}

int main() {
    // figurative flight that will be used to search for flights
    flight_t search_f;
    vector<flight_t> searched_f;

    welcome_message();
    search_f = search_prompt();
    searched_f = search_flights(search_f);
    display_flights(searched_f);
    checkout_prompt(searched_f);
}