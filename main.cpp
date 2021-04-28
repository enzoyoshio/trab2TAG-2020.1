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

void le_entrada(vector<Professor>& p, vector<Escola>& esc) {
	string str;
	while(getline(cin, str)) {
        if(str[0] == '/' || str == "") continue;
        int a=0, b=0, c=0, d=0, e=0, f=0;
        if(str[1] == 'P') {
            sscanf(str.c_str(), "(P%d, %d): (E%d, E%d, E%d, E%d)", &a, &b, &c, &d, &e, &f);
			vector<int> aux = {c, d, e, f};
			while(aux.back() == 0) aux.pop_back();
			for(int i = 1; i <= 50; i++) aux.push_back(i);
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

	le_entrada(professores, escolas);

	int cont = 0, conta_escola = 0;
	vector<int> v(3, 0), tot(3, 0), saco(3, 0);
	for(auto p: professores) tot[p.hab-1]++;
	for(auto e: escolas) for(auto p: e.preferencias) saco[abs(p)-1]++;
	map<int, vector<int>> resposta = gale_shapley(professores, escolas);

	cout << "Um conjunto estável para esse problema eh:\n";
	for(auto [esc, profs]: resposta) {
		cont += profs.size();
		conta_escola++;
		cout << "ESCOLA " << esc << " quer professores com ";
		for(auto pre:escolas[esc-1].preferencias) cout << "QUERIA " << abs(pre) << ' ';
		cout <<  "\n";
		for(auto p: profs) cout << "Professor " << p << " possui habilitacao -> " << professores[p-1].hab << " ocupou a vaga para habilitaçao " << professores[p-1].id_par << '\n', v[professores[p-1].hab -1]++;
		cout << "\n\n";
	}

	cout << "O total de professores alocados foi " << cont << '\n';
	cout << "O total de escolas alocadas foi " << conta_escola << "\n\n";

	cout << "As escolas estavam ofertando " << saco[0] << " vagas para habilitacao 1\n";
	cout << "As escolas estavam ofertando " << saco[1] << " vagas para habilitacao 2\n";
	cout << "As escolas estavam ofertando " << saco[2] << " vagas para habilitacao 3\n";
	cout << "O total de vagas era " << saco[0]+saco[1]+saco[2] << "\n\n";

	cout << "No total haviam " << tot[0] << " professores com habilitacao 1 e " << v[0] << " foram alocados\n";
	cout << "No total haviam " << tot[1] << " professores com habilitacao 2 e " << v[1] << " foram alocados\n";
	cout << "No total haviam " << tot[2] << " professores com habilitacao 3 e " << v[2] << " foram alocados\n";
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
