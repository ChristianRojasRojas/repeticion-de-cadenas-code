#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> z_function(string const& s) { //parte lógica
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i + z[i] < n && s[z[i]] == s[i+z[i]]) // encuentra si los valores son iguales ejemplo "a#a" daria true cuando i = 2 y lo guarda en z[i]
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int get_z(vector<int> const& z, int i) { // retorna la posicion del valor repetido (en el caso que sea 1 esa nposicion es repetido)
    if (0 <= i && i < (int)z.size()) // retorna 0 si no es repetido y 1 si es repetido
        return z[i]; // ejemplo entro vector (0,0,1) i = 2 entonces retorna el 1 que dice que hay un valor repetido
    else
        return 0;
}

vector<pair<int, int>> repetitions;

void convert_to_repetitions(int shift, bool left, int cntr, int l, int k1, int k2) { //setea los valores repetidos en el pair repetitions
    for (int l1 = max(1, l - k2); l1 <= min(l, k1); l1++) { // l1 minimo vale 1
        if (left && l1 == l) break;
        int l2 = l - l1;
        int pos = shift + (left ? cntr - l1 : cntr - l - l1 + 1);
        repetitions.emplace_back(pos, pos + 2*l - 1);
    }
}

void find_repetitions(string s, int shift = 0) {
    int n = s.size();
    if (n == 1)
        return;

    int nu = n / 2;
    int nv = n - nu;
    string u = s.substr(0, nu); // obtiene la primera mitad del string
    string v = s.substr(nu); // obtiene la segunda mitad del string
    string ru(u.rbegin(), u.rend()); // invierte los valores de la primera mitad
    string rv(v.rbegin(), v.rend()); // invierte los valores de la segunda mitad

    find_repetitions(u, shift); // shift es la posicion de un array ejemplo 'a'
    find_repetitions(v, shift + nu);

    // ejemplo en "ab"  -- los vectors van guardando las posiciones en que se van tomando los valores
    vector<int> z1 = z_function(ru); // analiza "a"
    vector<int> z2 = z_function(v + '#' + u); // analiza "b#a"
    vector<int> z3 = z_function(ru + '#' + rv); // analiza "a#b"
    vector<int> z4 = z_function(v); // analiza "b"

    for (int cntr = 0; cntr < n; cntr++) { // logica de Main Lorent< ejemplo (a#b)
        int l, k1, k2;
        if (cntr < nu) { // iteracion de la primera parte ->  ejemplo a
            l = nu - cntr;
            k1 = get_z(z1, nu - cntr);
            k2 = get_z(z2, nv + 1 + cntr);
        } else { // iteracion de la segunda parte -> ejemplo b
            l = cntr - nu + 1;
            k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
            k2 = get_z(z4, (cntr - nu) + 1);;
        }
        if (k1 + k2 >= l)
            convert_to_repetitions(shift, cntr < nu, cntr, l, k1, k2);
    }
}

int main() {
    vector<string> results;
    string palabra, palabraTemporal;
    cin >> palabra;
    find_repetitions(palabra);
    for (auto i: repetitions){
        palabraTemporal ="";
        for (int x=i.first;x<=i.second;++x){
            palabraTemporal += palabra[x];
        }
        results.push_back(palabraTemporal);
    }

    string mitadPalabra;
    int cantidadRepeticiones;
    vector<int> cantidadRepeteciones;
    map<string,int> finalResults;
    int contadorTemporal;

    for (auto element1: results){
        contadorTemporal = 0;
        for (auto element2: results){
            if (element1 == element2){
                ++contadorTemporal;
            }
        }
        finalResults.insert(pair<string,int>(element1,contadorTemporal));
    }

    for (auto element: finalResults){
        mitadPalabra = "";
        for (int i=0; i<element.first.size()/2; ++i){
            mitadPalabra += element.first[i];
        }
        if (element.second == 1)
            cout << "La subcadena \"" << mitadPalabra <<"\" se repite " << element.second << " vez" << endl;
        else
            cout << "La subcadena \"" << mitadPalabra <<"\" se repite " << element.second << " veces" << endl;
    }
}
