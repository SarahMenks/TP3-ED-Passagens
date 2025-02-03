#ifndef FLIGHT_CPP
#define FLIGHT_CPP

#include <string>
#include <ctime>

typedef struct Flight {
    std::string origin;
    std::string destination;
    std::string price;
    std::string seats;
    std::string departure_time;
    std::string arrival_time; 
    std::string number_stops;
    std::string duration; //em segundos
    double departure_time_seconds; //horario de partida em segundos
    double arrival_time_seconds; //horario de chegada em segundos

    // void SetOrigin(std::string origin);
    // void SetDestination(std::string destination);
    // void SetPrice(double price);
    // void SetAvailableSeats(int seats);
    // void SetDepartureTime(std::string departure_time);
    // void SetArrivalTime(std::string arrival_time);
    // void SetNumberStops(int number_stops);
} Flight;



#endif