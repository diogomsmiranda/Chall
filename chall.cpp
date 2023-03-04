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

//prints flight to display to user
void printf_flight(flight_t f) { printf("%s |%s |%s |%d\n", f.origin, f.destiny, f.start_date, f.pass_number); }

void welcome_message() {
    string buffer;
    string message = "Bem-Vindo á nossa flight search engine!\n Aqui podes pesquisar sobre os voos disponiveis e comprar bilhetes.\n\n :: Pequenas Regras sobre a nossa engine ::\n -> Nomes das cidades para simplificação são abreviadas a 3 letras. ex: LIS para Lisboa\n -> Datas são aceites no formate DD/MM/YY\n -> Só os últimos dois digitos do ano são especificados sendo todos os voos passados em 2023.\n\n Para começar a pesquisar podes introduzir o comando ,#.\n Obrigado por utilizares a nossa engine!!\n";

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

    welcome_message();
    search_f = search_prompt();

    search_flights(search_f);
}