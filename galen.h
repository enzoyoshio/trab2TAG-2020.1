#ifndef GALEN_H
#define GALEN_H

// declaração das funções e essas coisas
#include<bits/stdc++.h>
using namespace std;

struct Professor {
    int hab=4, id, id_par=-1;
    vector<int> preferencias;
    Professor(int idx, int h, vector<int> p);
};

struct Escola {
    int cap=0, id;
    vector<int> preferencias;
    vector<int> id_pares;
    Escola(int idx, int c, vector<int> p);
};

map<int, vector<int>> galen_shapley_estavel(vector<Professor> p, vector<Escola> e);

map<int, vector<int>> galen_shapley_maximo_estavel(vector<Professor> p, vector<Escola> e);

#endif
