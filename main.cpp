#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

#include "MertzLorentz.h"
#include "Crochemore.h"

int main() {
    string cadena,stop;
    cin >> cadena;
    mertzLorentz(cadena);
    cout << endl << endl;
    Crochemore(cadena);
    cin >> stop;
}
