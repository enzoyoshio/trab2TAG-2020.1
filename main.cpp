/**
 * Universidade de Brasília - UnB
 *
 * Nome : Enzo Yoshio Niho
 * Matrícula : 19/0027304
 * Matéria : Teoria e Aplicação de Grafos (TAG)
 *
 */

#include<vector>
#include<map>
#include<iostream>
#include"gale.h"

// using namespace or wirte std everytime ?
using namespace std;

// função para ler a entrada do arquivo
void le_entrada(vector<Professor>& p, vector<Escola>& esc) {
	string str;
	while(getline(cin, str)) {
        if(str[0] == '/' || str == "") continue;
        int a=0, b=0, c=0, d=0, e=0, f=0;

        if(str[1] == 'P') { // caso seja um professor
            sscanf(str.c_str(), "(P%d, %d): (E%d, E%d, E%d, E%d)", &a, &b, &c, &d, &e, &f);
			vector<int> aux = {c, d, e, f};
			while(aux.back() == 0) aux.pop_back();
			for(int i = 1; i <= 50; i++) aux.push_back(i);
			p.push_back(Professor(a, b, aux));
		}else { // caso seja uma escola
            sscanf(str.c_str(), "(E%d):(%d):(%d)", &a, &b, &c);
			if(c == 0) 
				esc.push_back(Escola(a, 1, {b}));
			else 
				esc.push_back(Escola(a, 2, {b, c}));
		} 
    }
}

int main() {
	
	// funções para ler e escrever em outros arquivos como saída padrão
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	// criando os vértices do grafo
	vector<Professor> professores;
	vector<Escola> escolas;

	// lendo a entrada
	le_entrada(professores, escolas);

	int cont = 0, conta_escola = 0;
	vector<int> v(3, 0), tot(3, 0), saco(3, 0);
	for(auto p: professores) tot[p.hab-1]++;
	for(auto e: escolas) for(auto p: e.preferencias) saco[abs(p)-1]++;

	// colocando a resposta no conjunto resposta
	map<int, vector<int>> resposta = gale_shapley(professores, escolas);
	cout << "Um conjunto máximo estável para esse problema é:\n\n";
	for(auto [esc, profs]: resposta) {
		cont += profs.size();
		conta_escola++;
		cout << "ESCOLA " << esc << " :\n";
		for(auto p: profs) cout << "Professor " << p << " possui habilitacao -> " << professores[p-1].hab << " ocupou a vaga para habilitaçao " << professores[p-1].id_par << '\n', v[professores[p-1].hab -1]++;
		cout << "\n";
	}

	cout << "O total de professores alocados foi " << cont << '\n';
	cout << "O total de escolas alocadas foi " << conta_escola << "\n";

	return 0;
}
