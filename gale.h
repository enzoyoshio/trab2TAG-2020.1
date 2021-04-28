#ifndef GALE_H
#define GALE_H

// declaração das funções e essas coisas
#include<vector>
#include<map>

using namespace std;

struct Professor {
    int hab=4, id, id_par=0;
    vector<int> preferencias;
    Professor(int idx, int h, vector<int> p);
};

struct Escola {
    int cap=0, id;
    vector<int> preferencias;
    vector<int> id_pares;
    Escola(int idx, int c, vector<int> p);
};

map<int, vector<int>> gale_shapley(vector<Professor>& p, vector<Escola>& e);

#endif