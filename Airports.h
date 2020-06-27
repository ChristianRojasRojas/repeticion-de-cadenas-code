//
// Created by pc on 01/06/2020.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Airport{
private:
    string Longitude;
    string Latitude;
public:
    string City;
    string Country;
    string Name;
    int Id;
    vector<int> destinations;
    Airport(){}
    void setLongitude(string Longitude){
        this->Longitude = Longitude;
    }
    void setLatitude(string Latitude){
        this->Latitude = Latitude;
    }
    void addDestination(string destination){
        int temp = stoi(destination);
        destinations.push_back(temp);
    }
};

Airport *createAirport(vector<string> data, vector<string> destinations){

    auto airport = new Airport();
    int i = 1;

    for (auto element: data){
        switch (i){
            case 1:{
                airport->City = element;
                break;
            }
            case 2:{
                airport->Name = element;
                break;
            }
            case 3:{
                airport->Country = element;
                break;
            }
            case 4:{
                airport->setLongitude(element);
                break;
            }
            case 5:{
                airport->setLatitude(element);
                break;
            }
            case 6:{
                int id = stoi(element);
                airport->Id = id;
                break;
            }
        }
        i++;
    }
    for (auto destination: destinations){
        airport->addDestination(destination);
    }

    return airport;
}


vector<Airport*> read_json(string file){
    ifstream archivo;
    string linea;
    vector<Airport*> jsonAirports;
    vector<string> data;
    vector<string> destinations;

    archivo.open(file,ios::in);
    int contadorTemporal = 0;
    bool anexar = false;
    bool anexarCorchetes = false;
    string palabraTemporal = "";
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (anexarCorchetes){ // aqui realiza el push de destinations
                bool parentesis = false;
                for (auto i : linea){
                    if (parentesis && i == '"'){
                        parentesis = false;
                        destinations.push_back(palabraTemporal);
                        palabraTemporal = "";
                    }
                    if (parentesis && i != ','){
                        palabraTemporal += i;
                    }
                    if (i == '"'){
                        parentesis = true;
                    }
                    anexarCorchetes = false;
                    if (i == ','){
                        anexarCorchetes = true;
                    }
                }
                if (!anexarCorchetes){
                    Airport* newAirport= createAirport(data,destinations);
                    data.clear();
                    destinations.clear();
                    jsonAirports.push_back(newAirport);
                }
            }else { // aqui realiza el push de data
                for (auto i: linea) {
                    if (i == ':') {
                        contadorTemporal = 0;
                    }
                    if (anexar && i == '"') {
                        anexar = false;
                        data.push_back(palabraTemporal);
                        palabraTemporal = "";
                    }
                    if (anexar) {
                        palabraTemporal += i;
                    }
                    if (contadorTemporal == 2 && i == '"' ) {
                        anexar = true;
                    }else if (contadorTemporal == 2 && i == '[' ){
                        anexarCorchetes = true;
                    }
                    ++contadorTemporal;
                }
            }
        }

        archivo.close();
    }

    return jsonAirports;
}