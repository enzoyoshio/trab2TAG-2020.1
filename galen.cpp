#include"galen.h"
#include<algorithm>
#include<vector>
#include<map>
#include<iostream>

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
        if(h <= p.hab && h > 0) {
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
        if(prof.hab >= mini){
            mini = prof.hab;
            par = prof.id;
        }
    }
    return par;
}

void arruma(Escola& e, Professor p) {
    for(auto& a: e.preferencias) {
        if(abs(a) <= p.id) {
            a = abs(a);
            return;
        }
    }
}

int procura_outra(int hab, vector<Escola> e, map<int,vector<int>> M) {
    for(int i = 0; i < e.size(); i++) {
        if(M[e[i].id].size() < e[i].cap && (e[i].preferencias[0] <= hab || (e[i].preferencias.size() == 2 &&e[i].preferencias[1] <= hab))) return i;
    }
    return -1;
}

map<int, vector<int>> galen_shapley_estavel(vector<Professor>& p, vector<Escola>& e) {
    map<int, vector<int>> M;
    int idx_professor = 0, contador = 0;
    
    // laço "infinito" para o algoritmo rodar o suficiente para encontrar a melhor resposta
    // ele para quando todos professores forem alocados ou as vagas das escolas acabarem (?)
    while(idx_professor < 1000) { 
        // escolhe o professor para aplicar       
        // & faz salvar o valor no vetor tambem
        Professor& p1 = p[(idx_professor++)%50];
        if(p1.id_par != -1) continue;
        cout << "TESTE\n";
        cout << temProf(p)-1 << '\n';
        cout << "FIM TESTE\n";
        // encontra a escola que o professor quer
        int idx_escola;
        if(p1.preferencias.empty()) {
            idx_escola = procura_outra(p1.hab, e, M);
        }else {
            idx_escola = (*p1.preferencias.begin())-1;
        }
        if(idx_escola == -1) {
            p1.id = 19;
            //if(p1.preferencias.size()) p1.preferencias.erase(p1.preferencias.begin());
            continue;
        } 
        Escola& e1 = e[idx_escola];

        // verifica se o professor tem habilitação para a escola desejada
        if(!escola_quer_prof(e1, p1)) {
            if(p1.preferencias.size()) p1.preferencias.erase(p1.preferencias.begin());
            continue;
        } 

        // cout << "TESTE ESCOLA >>>>>>>>>>>>>>>>>\n";
        // for(auto [l, k] : e1.preferencias) cout << l << ' ' << k << '\n';
        // cout << "FIM TESTE >>>>>>>>>>>>>>>>>>.\n";
 
        // professor aplicando para a escola
        M[e1.id].push_back(p1.id);
        p1.id_par = e1.id;
        if(p1.preferencias.size()) p1.preferencias.erase(p1.preferencias.begin());
        e1.id_pares.push_back(p1.id);
    
        // se tiverem mais professores do que a escola pode receber, temos que retirar algum
        if(e1.cap < M[e1.id].size()) {
            int apaga = escolhe_pior(M[e1.id], p);
            p[apaga-1].id_par = -1;
            M[e1.id].erase(find(M[e1.id].begin(), M[e1.id].end(), apaga));
            e1.id_pares.erase(find(e1.id_pares.begin(), e1.id_pares.end(), apaga));
            arruma(e1, p[apaga-1]);
        }
    }

    return M;
}

int tem_escola(vector<Escola> e, map<int, vector<int>>& M) {
    for(int i = 0; i < e.size(); i++) {
        if(M[e[i].id].size() <= e[i].cap) return i+1;
    }
    return 0;
}

map<int, vector<int>> gale_shapley_escola(vector<Professor>& p, vector<Escola>& e) {
    map<int, vector<int>> M;

    int idx = -1;
    while((idx = tem_escola(e, M))) {
        Escola& e1 = e[idx-1];
        // int prof_idx = procura_professor(e1.id, p);
    }
    return M;
}

map<int, vector<int>> galen_shapley_maximo_estavel(vector<Professor> p, vector<Escola> e) {
    return {{1, {1, 2}}};
}