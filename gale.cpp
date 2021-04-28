#include"gale.h"
#include<algorithm>
#include<vector>
#include<map>
#include<iostream>

using namespace std;

// aqui faz a implementação das paradas

Professor::Professor(int idx, int h, vector<int> p) : hab(h), id(idx), preferencias(p) {}

Escola::Escola(int idx, int c, vector<int> p) : cap(c), id(idx), preferencias(p), id_pares(p.size(), -1) {}

bool escola_quer_prof(Escola& e, Professor& p) {
    for(auto& h: e.preferencias) {
        if(h <= p.hab && h > 0) {
            // h = -h;
            p.id_par = h;
            h = 0;
            return true;
        } 
    }
    return false;
}

int escolhe_pior(vector<int> a, vector<Professor> p) {
    int mini = 10, par = 0;
    
    for(int i = 0; i < a.size(); i++) {
        Professor prof = p[a[i]-1];
        if(prof.hab <= mini){
            mini = prof.hab;
            par = prof.id;
        }
    }
    return par;
}

void arruma(Escola& e, Professor p) {
    for(auto& it: e.preferencias) {
        if(it == 0) {
            it = p.id_par;
            return;
        }
    }
}

int procura_outra(int hab, vector<Escola> e) {
    for(int i = 0; i < e.size(); i++) {
        if(((e[i].preferencias[0] == hab && e[i].preferencias[0] > 0) || (e[i].preferencias.size() == 2 &&e[i].preferencias[1] == hab && e[i].preferencias[1] > 0))) return i;
    }
    return -1;
}

map<int, vector<int>> gale_shapley(vector<Professor>& p, vector<Escola>& e) {
    map<int, vector<int>> M;
    int idx_professor = 0, contador = -1;
    
    // laço "infinito" para o algoritmo rodar o suficiente para encontrar a melhor resposta
    // ele para quando todos professores forem alocados ou as vagas das escolas acabarem (?)
    while(contador++ < 1000000) { 

        // escolhe o professor para aplicar       
        // & faz salvar o valor no vetor tambem
        Professor& p1 = p[(contador)%100];
        if(p1.hab != 1 and contador < 10000) continue;
        if(p1.hab == 3 and contador < 20000) continue;
        if(p1.id_par != 0) continue;
        
        // encontra a escola que o professor quer
        int idx_escola;

        // if(p1.preferencias.empty()) {
        //     idx_escola = procura_outra(p1.hab, e);
        // }else {
        // }
        idx_escola = (*p1.preferencias.begin())-1;
        
        if(idx_escola == -1) {
            if(p1.preferencias.size()) p1.preferencias.erase(p1.preferencias.begin());
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
        // p1.id_par = e1.id;
        if(p1.preferencias.size()) p1.preferencias.erase(p1.preferencias.begin());
        e1.id_pares.push_back(p1.id);
    
        // se tiverem mais professores do que a escola pode receber, temos que retirar algum
        if(e1.cap < M[e1.id].size()) {
            int apaga = escolhe_pior(M[e1.id], p);
            // p[apaga-1].id_par = 0;
            M[e1.id].erase(find(M[e1.id].begin(), M[e1.id].end(), apaga));
            e1.id_pares.erase(find(e1.id_pares.begin(), e1.id_pares.end(), apaga));
            arruma(e1, p[apaga-1]);
        }
    }

    return M;
}