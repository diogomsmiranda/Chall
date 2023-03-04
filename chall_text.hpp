#include <stdio.h>
#include <string>


// Text fields used in the console interface
string text_welcomeMessage = 
    "Bem-Vindo á nossa flight search engine!\n" 
    "Aqui podes pesquisar sobre os voos disponiveis e comprar bilhetes.\n\n"
    ":: Pequenas Regras sobre a nossa engine ::\n"
    "-> Nomes das cidades para simplificação são abreviadas a 3 letras. ex: LIS para Lisboa\n"
    "-> Datas são aceites no formate DD/MM/YY\n"
    "-> Só os últimos dois digitos do ano são especificados sendo todos os voos passados no séc 21.\n\n";

string text_search = 
    "Introduza o numero da opcao que pretende: \n"
    "0. Pesquisar voos\n"
    "1. Mostrar Tickets\n";

string text_login_success =
    "Login efetuado com sucesso!\n";

string text_login_fail =
    "Login falhou. Tente novamente.\n";

string text_login = 
    "Introduza o seu username e password (1 por linha) podes pression 0 para voltar ao menu: ";

string text_mmenu = 
    "0. Login de Cliente (Registo Automático ao fim de 1 uso)\n"
    "1. Pesquisar voos\n"
    "2. Sair\n";

string text_origin = 
    "Introduza a cidade de origem: ";

string text_destination =
    "Introduza a cidade de destino: ";

string text_date =
    "Introduza a data de partida (DD/MM/YY): ";

string text_passengers =
    "Introduza o numero de passageiros: ";

string error_airport = 
    "O nome do aeroporto é composto por 3 letras maiúsculas. Tente novamente.\n";

string error_date =
    "A data deve ser introduzida no formato DD/MM/YY. Tente novamente.\n";

string error_number =
    "Este campo deveria ser preenchido com um número. Tente novamente.\n";

string text_sort = 
    "Introduza o numero da opcao que pretende: \n"
    "0. Ordenar por hora de partida\n"
    "1. Ordenar por hora de chegada\n"
    "2. Ordenar por duracao\n"
    "3. Ordenar por preco\n";

string error_option = 
    "Opcao invalida. Tente novamente\n";

string text_name = 
    "Introduza o seu nome: ";

string text_mail = 
    "Introduza o seu mail: ";

string text_phone =
    "Introduza o seu número de telemóvel: ";

string text_address = 
    "Introduza o seu endereço físico: ";

string text_credit = 
    "Introduza o número do seu cartão de crédito: ";

string text_buySuccess =
    "Obrigada pela sua compra! A fatura será adicionada como um file (fatura.txt) no diretório atual.\n";

string error_name = 
    "Por favor introduza um nome com apenas letras e sem espaços em branco.\n";

string error_phone = 
    "Por favor introduza um número de telemóvel válido (9 algarismos).\n";

string error_credit = 
    "Por favor introduza um número de cartão de crédito válido (16 algarismos).\n";

string text_buy = 
    "Introduza o numero do voo que pretende comprar: ";

string text_baggage =
    "Mala de cabine ou Mala de porao? (1/2): ";

string error_buy =
    "Opção inválida. Tente novamente.\n";

string success_buy =
    "A prosseguir para o checkout do voo:\n"; 