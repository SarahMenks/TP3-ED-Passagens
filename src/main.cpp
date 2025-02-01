#include <iostream>
#include <ctime>
#include <fstream>
#include "AVL.hpp"
#include "Flight.hpp"

using namespace std;

string TimeToString(tm time){
    char buffer[30];

    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", &time);

    return string(buffer);
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

    int num_flights, num_operations;
    Flight *flights;
    AVL *org, *dst, *prc, *sea, *dep, *arr, *sto, *dur;
    
    ifstream file(argv[1]);

    if( !file.is_open() ){
        cout << "Impossivel abrir o arquivo!" << endl;
        exit(1);
    }

    //coleta os dados dos voos
    file >> num_flights;
    flights = new Flight[num_flights];
    for(int i = 0; i < num_flights; i++){
        file >> flights[i].origin >> flights[i].destination >> flights[i].price >> flights[i].seats >> flights[i].departure_time >> flights[i].arrival_time >> flights[i].number_stops;
        flights[i].departure_time_seconds = StringToSeconds(flights[i].departure_time); //calcula o horario de partida em segundos
        flights[i].arrival_time_seconds = StringToSeconds(flights[i].arrival_time); //calcula o horario de chegada em segundos
        flights[i].duration = (flights[i].arrival_time_seconds - flights[i].departure_time_seconds); //calcula duração do voo

        //cout << flights[i].origin << " " << flights[i].destination << " " << flights[i].price << " " << flights[i].seats << " " << flights[i].departure_time << " " << flights[i].arrival_time << " " << flights[i].number_stops << " " << flights[i].departure_time_seconds << " " << flights[i].arrival_time_seconds << " " << flights[i].duration << endl;
    }
    
    //coleta as operações
    file >> num_operations;
    for(int i = 0; i < num_operations; i++){
        char *ptr;
    }
        /*
        //inicializa variaveis aleatorias que vao ajudar na leitura do arquivo
        int numPessoa = 0;
        string linha, caracteristica;
        long unsigned int i;

        //lê cada linha do arquivo e separa as caracteristicas de cada pessoa
        while(getline(arquivo, linha)) {            
            caracteristica = "";
            for(i=0 ; i < linha.size() ; i++){
                if(linha[i] != ',')
                    caracteristica += linha[i];
                else
                    break;
            }
            p[numPessoa].nome = caracteristica;
        */

    return 0;
}