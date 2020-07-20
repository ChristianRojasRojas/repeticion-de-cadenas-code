//
// Created by pc on 20/07/2020.
//

#ifndef PROYECT_REPETICION_DE_CADENAS_CROCHEMORE_H

struct Array{
    string subString;
    vector<int> values;

    Array(const string &subString, int position) : subString(subString) {
        values.push_back(position);
    }

    Array(const string &subString, const vector<int> &values) : subString(subString), values(values) {}
};

vector<Array*> findArrays(string cadena, int level){
    unordered_set<string> recorridos;
    vector<Array*> result;
    auto iterator = cadena.begin();
    auto itTemp = iterator;
    string temp = "";
    int contador = 0;
    while (true){
        if (iterator == cadena.end())
            return result;
        temp = *iterator;
        itTemp = iterator;
        for (int i=1;i <level; ++i){
            itTemp++;
            if (itTemp == cadena.end()){
                return result;
            }
            temp += *itTemp;
        }
        if (recorridos.find(temp) == recorridos.end()){ // si es la primera vez que agarramos esta subcadena
            Array* ptrArray = new Array(temp,contador);
            result.push_back(ptrArray);
            recorridos.insert(temp);
        }else{ //ya tenemos registrada esa subcadena entonces tenemos que agregar esa posicion al array
            auto it = result.begin();
            bool find = false;
            while (!find){
                if (temp == (*it)->subString){
                    (*it)->values.push_back(contador);
                    find = true;
                }
                it++;
            }
        }
        iterator++;
        contador++;
    }
}

Array* analizeResult(vector<int> array, string value,int level){
    unordered_set<int> recorridos;
    vector<int> vectResult;
    auto it1 = array.begin();
    auto it2 = array.begin();
    it2++;
    while(it2 != array.end()){
        if ((*it2 - *it1) == level){
            if (recorridos.find(*it1) == recorridos.end()){
                recorridos.insert(*it1);
                vectResult.push_back(*it1);
            }
            if (recorridos.find(*it2) == recorridos.end()){
                recorridos.insert(*it2);
                vectResult.push_back(*it2);
            }
        }
        it1++;
        it2++;
    }
    Array* result = new Array(value,vectResult);
    return result;
}

void Crochemore(string cadena) {
    int level = 1;
    vector<Array*> result;
    while (level <= cadena.size()/2) {
        vector<Array *> arrays = findArrays(cadena, level);
        auto it = arrays.begin();
        while (it != arrays.end()) {
            if ((*it)->values.size() > 1) {
                Array *ptrArray = analizeResult((*it)->values, (*it)->subString, level);
                if ((*ptrArray).values.size() != 0)
                    result.push_back(ptrArray);
                else
                    delete ptrArray;
            }
            it++;
        }
        arrays.clear();
        level++;
    }
    // imprimir resultado
    for (auto element: result){
        cout << "la subcadena \"" << element->subString << "\" se repite " << element->values.size() << " veces" << endl;
    }
    cout << "stop";
}
#define PROYECT_REPETICION_DE_CADENAS_CROCHEMORE_H

#endif //PROYECT_REPETICION_DE_CADENAS_CROCHEMORE_H
