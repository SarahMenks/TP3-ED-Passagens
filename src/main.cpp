#include <iostream>
#include <ctime>
#include <fstream>
#include "AVL.hpp"
#include "Flight.hpp"

using namespace std;

void parse_args(int argc,char *argv[]){
    //argc deve receber o nome do arquivo xcvs
    if(argc < 2){
        cout << "Faltam argumentos" << endl;
        exit(1);
    }
    if(argc > 2){
        cout << "Argumentos a mais" << endl;
        exit(1);
    }
}

double StringToSeconds(string const &time_str){
    //retorna o tempo, em segundos, de uma string no formato "YYYY-MM-DDTHH:MM:SS"
    char *ptr;
    double ano = strtod(time_str.c_str(), &ptr);
    double mes = strtod(ptr+1, &ptr);
    double dia = strtod(ptr+1, &ptr);
    double hora = strtod(ptr+1, &ptr);
    double min = strtod(ptr+1, &ptr);
    double seg = strtod(ptr+1, &ptr);

    return (ano*31536000) + (mes*2592000) + (dia*86400) + (hora*3600) + (min*60) + seg;
}

int main(int argc, char *argv[]){

    parse_args(argc, argv);

    int num_flights;
    Flight *flights;

    //cria as arvores dos criterios de ordenacao
    Node *org = nullptr, *dst = nullptr, *prc = nullptr;
    Node *sea = nullptr, *dep = nullptr, *arr = nullptr;
    Node *sto = nullptr, *dur = nullptr;

    ifstream file(argv[1]);

    if( !file.is_open() ){
        cout << "Impossivel abrir o arquivo!" << endl;
        exit(1);
    }

    //coleta os dados dos voos
    try{
        file >> num_flights;
        flights = new Flight[num_flights];

        for(int index = 0; index < num_flights; index++){
            //recebe os dados dos voos
            file >> flights[index].origin >> flights[index].destination >> flights[index].price >> flights[index].seats >> flights[index].departure_time >> flights[index].arrival_time >> flights[index].number_stops;
            flights[index].departure_time_seconds = StringToSeconds(flights[index].departure_time); //calcula o horario de partida em segundos
            flights[index].arrival_time_seconds = StringToSeconds(flights[index].arrival_time); //calcula o horario de chegada em segundos
            flights[index].duration = to_string(flights[index].arrival_time_seconds - flights[index].departure_time_seconds); //calcula duração do voo

            //insere os dados nas arvores
            org = FindAndInsert(org, flights[index].origin, index);
            dst = FindAndInsert(dst, flights[index].destination, index);
            prc = FindAndInsert(prc, flights[index].price, index);
            sea = FindAndInsert(sea, flights[index].seats, index);
            dep = FindAndInsert(dep, flights[index].departure_time, index);
            arr = FindAndInsert(arr, flights[index].arrival_time, index);
            sto = FindAndInsert(sto, flights[index].number_stops, index);
            dur = FindAndInsert(dur, flights[index].duration, index);
            
            cout << flights[index].origin << " " << flights[index].destination << " " << flights[index].price << " " << flights[index].seats << " " << flights[index].departure_time << " " << flights[index].arrival_time << " " << flights[index].number_stops << " " << flights[index].departure_time_seconds << " " << flights[index].arrival_time_seconds << " " << flights[index].duration << endl;
        }
    } catch (exception &e){
        cout << "Erro ao coletar os dados dos voos!" << endl;
        cerr << e.what() << endl;
        exit(1);
    }

    PostOrder(org);

    file.close();

    delete [] flights;
    delete org;
    delete dst;
    delete prc;
    delete sea;
    delete dep;
    delete arr;
    delete sto;
    delete dur;

    return 0;
}