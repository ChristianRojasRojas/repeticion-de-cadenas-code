//
// Created by pc on 14/06/2020.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class City{
private:
    string Longitude;
    string Latitude;
public:
    string city;
    City(){}
    void setLongitude(string Longitude){
        this->Longitude = Longitude;
    }
    void setLatitude(string Latitude){
        this->Latitude = Latitude;
    }
};

City *createCity(vector<string> data){

    auto ciudad = new City();
    int i = 1;

    for (auto element: data){
        switch (i){
            case 1:{
                ciudad->city = element;
                break;
            }
            case 2:{
                ciudad->setLatitude(element);
                break;
            }
            case 3:{
                ciudad->setLongitude(element);
                break;
            }
        }
        i++;
    }

    return ciudad;
}


vector<City*> read_json_cities(string file) {
    ifstream archivo;
    string linea;
    vector<City*> jsonCities;
    vector<string> data;

    archivo.open(file, ios::in);
    int contadorTemporal = 0;
    int contadorData = 0;
    bool anexar = false;
    string palabraTemporal = "";
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {

            // aqui realiza el push de data
            for (auto i: linea) {
                if (i == ':') {
                    contadorTemporal = 0;
                }
                if (anexar && i == '"') {
                    ++contadorData;
                    anexar = false;
                    data.push_back(palabraTemporal);
                    palabraTemporal = "";
                    if (contadorData == 3) {
                        City* newCity = createCity(data);
                        data.clear();
                        contadorData = 0;
                        jsonCities.push_back(newCity);
                    }
                }
                if (anexar) {
                    palabraTemporal += i;
                }
                if (contadorTemporal == 2 && i == '"') {
                    anexar = true;
                }
                ++contadorTemporal;
            }
        }
        archivo.close();
    }
    return jsonCities;
}