#include"galen.h"
#include<bits/stdc++.h>

using namespace std;

// aqui faz a implementação das paradas

Professor::Professor(int idx, int h, vector<int> p) : hab(h), id(idx), preferencias(p) {}

Escola::Escola(int idx, int c, vector<int> p) : cap(c), id(idx), preferencias(p), id_pares(p.size(), -1) {}

int temProf(vector<Professor>& p) {
    for(int i = 0; i < p.size(); i++) {
        if(p[i].id_par == -1) return i+1;
    }
    return 0;
}

bool temPref(int idx, vector<Professor>& p) {
    return p[idx-1].preferencias.size();
}

bool escola_quer_prof(Escola& e, Professor p) {
    for(auto& h: e.preferencias) {
        if(h <= p.hab and h > 0) {
            h = -h;                
            return true;
        } 
    }
    return false;
}

int escolhe_pior(vector<int> a, vector<Professor> p) {
    int mini = 0, par = 0;
    for(int i = 0; i < a.size(); i++) {
        Professor prof = p[a[i]-1];
        if(prof.hab > mini){
            mini = prof.hab;
            par = prof.id;
        }
    }
    return par;
}

void arruma(Escola& e) {
    for(auto& a: e.preferencias) {
        if(a < 0) {
            a = -a;
            return;
        }
    }
}

map<int, vector<int>> galen_shapley_estavel(vector<Professor> p, vector<Escola> e) {
    map<int, vector<int>> M;
    int aff = 0;
    while(temProf(p) && temPref(temProf(p), p)) { 
        // escolhe o professor para aplicar       
        // & faz salvar o valor no vetor tambem
        // assert(temProf(p)-1 < p.size() and temProf(p)-1 >= 0);
        Professor& p1 = p[temProf(p)-1];
        // cout << "TESTE\n";
        // cout << temProf(p)-1 << '\n';
        // cout << "FIM TESTE\n";
        // encontra a escola que o professor quer
        Escola& e1 = e[(*p1.preferencias.begin())-1];

        // verifica se o professor tem habilitação para a escola desejada
        if(!escola_quer_prof(e1, p1)) {
            p1.preferencias.erase(p1.preferencias.begin());
            continue;
        } 

        // professor aplicando para a escola
        M[e1.id].push_back(p1.id);
        p1.id_par = e1.id;
        p1.preferencias.erase(p1.preferencias.begin());
        e1.id_pares.push_back(p1.id);
    
        // se tiverem mais professores do que a escola pode receber, temos que retirar algum
        if(e1.cap < M[e1.id].size()) {
            int apaga = escolhe_pior(M[e1.id], p);
            p[apaga-1].id_par = -1;
            M[e1.id].erase(find(M[e1.id].begin(), M[e1.id].end(), apaga));
            e1.id_pares.erase(find(e1.id_pares.begin(), e1.id_pares.end(), apaga));
            arruma(e1);
        }
    }

    return M;
}

map<int, vector<int>> galen_shapley_maximo_estavel(vector<Professor> p, vector<Escola> e) {
    map<int, vector<int>> M;
    int aff = 0;
    while(temProf(p) && temPref(temProf(p), p)) { 
        // escolhe o professor para aplicar       
        // & faz salvar o valor no vetor tambem
        // assert(temProf(p)-1 < p.size() and temProf(p)-1 >= 0);
        Professor& p1 = p[temProf(p)-1];
        // cout << "TESTE\n";
        // cout << temProf(p)-1 << '\n';
        // cout << "FIM TESTE\n";
        // encontra a escola que o professor quer
        Escola& e1 = e[(*p1.preferencias.begin())-1];

        // verifica se o professor tem habilitação para a escola desejada
        if(!escola_quer_prof(e1, p1)) {
            p1.preferencias.erase(p1.preferencias.begin());
            continue;
        } 

        // professor aplicando para a escola
        M[e1.id].push_back(p1.id);
        p1.id_par = e1.id;
        p1.preferencias.erase(p1.preferencias.begin());
        e1.id_pares.push_back(p1.id);
    
        // se tiverem mais professores do que a escola pode receber, temos que retirar algum
        if(e1.cap < M[e1.id].size()) {
            int apaga = escolhe_pior(M[e1.id], p);
            p[apaga-1].id_par = -1;
            M[e1.id].erase(find(M[e1.id].begin(), M[e1.id].end(), apaga));
            e1.id_pares.erase(find(e1.id_pares.begin(), e1.id_pares.end(), apaga));
            arruma(e1);
        }
    }

    return M;
}