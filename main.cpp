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
#include"galen.h"

// using namespace or wirte std everytime ?
using namespace std;

void read_input(vector<Professor>& p, vector<Escola>& esc) {
	string str;
	while(getline(cin, str)) {
        if(str[0] == '/' || str == "") continue;
        int a=0, b=0, c=0, d=0, e=0, f=0;
        if(str[1] == 'P') {
            sscanf(str.c_str(), "(P%d, %d): (E%d, E%d, E%d, E%d)", &a, &b, &c, &d, &e, &f);
			vector<int> aux = {c, d, e, f};
			while(aux.back() == 0) aux.pop_back();
			p.push_back(Professor(a, b, aux));
		}
        else {
            sscanf(str.c_str(), "(E%d):(%d):(%d)", &a, &b, &c);
			if(c == 0) 
				esc.push_back(Escola(a, 1, {b}));
			else 
				esc.push_back(Escola(a, 2, {b, c}));
		} 
        // cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << '\n';
    }
}

int main() {
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<Professor> professores;
	vector<Escola> escolas;

	read_input(professores, escolas);

	// for(auto p: professores) {
	// 	cout << "PROFESSOR LIDO " << p.id << '\n';
	// 	cout << "par " << p.id_par << '\n';
	// 	cout << "habilitacao " << p.hab << '\n';
	// 	cout << "LISTA DE ESCOLAS ";
	// 	for(auto e: p.preferencias) cout << e << ' ';
	// 	cout << '\n';
	// }
	// for(auto e:escolas) {
	// 	cout << "ESCOLA LIDA " << e.id << '\n';
	// 	cout << "CAPACIDADE " << e.cap << '\n'; 
	// 	cout << "LISTA DE PARES ";
	// 	for(auto saco: e.id_pares) cout << saco << ' '; cout << '\n';
	// 	cout << "LISTA DE requerimentos ";
	// 	for(auto a: e.preferencias) cout << a << ' ';
	// 	cout << '\n';
	// }

	map<int, vector<int>> resposta = galen_shapley_estavel(professores, escolas);

	cout << "Um conjunto estável para esse problema eh:\n";
	for(auto [esc, profs]: resposta) {
		cout << "ESCOLA " << esc << " quer professores com ";
		for(auto pre:escolas[esc-1].preferencias) cout << "QUERIA " << pre << ' ';
		cout <<  "\n";
		for(auto p: profs) cout << "Professor " << p << " possui habilitacao -> " << professores[p-1].hab << '\n';
		cout << "\n\n";
	}

	// map<int,vector<int>> resposta = galen_shapley_maximo_estavel(professores, escolas);

	// cout << "Um conjunto maximo estavel para esse problema eh: \n";
	// for(auto [esc, profs]: resposta) {
	// 	cout << "ESCOLA " << esc << " quer professores com ";
	// 	for(auto pre:escolas[esc-1].preferencias) cout << pre << ' ';
	// 	cout <<  "\n";
	// 	for(auto p: profs) cout << "Professor " << p << " possui habilitacao -> " << professores[p-1].hab << '\n';
	// 	cout << "\n\n";
	// }
	return 0;
}
