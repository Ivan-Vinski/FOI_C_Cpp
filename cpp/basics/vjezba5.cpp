#include<iostream>
#include<cmath>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include"biblioteka_vrijeme.cc"
#include"tel_imenik.cc"
using namespace std;

struct autori{
	char prez_ime[30], naslov[20];
	int sifra;
	double vrijeme;
};
fstream dat;
autori autor;
int velicina_dat;
int prost_broj;

void kreiranje(){
	autor.prez_ime[0] = '\0';
	autor.naslov[0] = '\0';
	autor.sifra = 0;
	autor.vrijeme = 0;
	dat.open("data", ios::out | ios::binary);
	for (int i=0; i<velicina_dat; i++){
		dat.write((char*)&autor, sizeof(autori));
	}
	dat.close();
	dat.clear();
}

void prvi_manji_prost_broj(){
	bool prost;
	for (int i=velicina_dat-1; i>1; i--){
		prost = true;
		for (int j=2; j<=sqrt(i); j++){
			if (i%j==0) {
				prost= false;
				break;
			}
		}
	if (prost) {
		prost_broj = i;
		return;
	} 
	}
}

void upis(){
	autori autor2;
	double pom;
	int rbz;
	bool pom1;
	do{
		pom1 = false;
		vrijeme_pocetak();
		cout << "Ime i prezime autora: ";
		cin.ignore();
		cin.getline(autor.prez_ime, 30);
		cout << "Naslov: ";
		cin.getline(autor.naslov, 20);
		do{
			cout << "Sifra: ";
			cin >> autor.sifra;
		}while(autor.sifra<1);
		vrijeme_kraj();
		pom = (int)(vrijeme_proteklo()/100);
		autor.vrijeme = (double)(pom /10);
		if (autor.vrijeme<5){
			cout << "Unos kraci od 5 sec, probajte opet." << endl;
			pom1 = true;
		}
	}while (pom1);
	rbz = autor.sifra % prost_broj;
	dat.open("data", ios::in | ios::out | ios::binary);
	dat.seekg(rbz * sizeof(autori));
	do{
		dat.read((char*)&autor2, sizeof(autori));
	}while (autor2.sifra>0);
	rbz = (dat.tellg()/sizeof(autori))-1;
	dat.seekp(rbz * sizeof(autori));
	dat.write((char*)&autor, sizeof(autori));
	dat.close();
	dat.clear();
}

void pretrazivanje(){
	int sifra;
	int rbz;
	double vrijeme;
	cout << "Sifra trazenog autora: ";
	cin >> sifra;
	vrijeme_pocetak();
	rbz = sifra % prost_broj;
	dat.open("data", ios::in | ios::binary);
	dat.seekg(rbz * sizeof(autori));
	do{
		dat.read((char*)&autor, sizeof(autori));
		if (dat.eof()){
			cout << "Nije naden zapis" << endl;
			dat.close();
			dat.clear();
			return;
		}
	}while (autor.sifra != sifra);
	cout << "Naden!" << endl;
	cout << autor.prez_ime << endl;
	cout << autor.naslov << endl;
	cout << autor.sifra << endl;
	cout << autor.vrijeme << endl;
	vrijeme_kraj();
	cout << "Vrijeme pretrage i ispisa: " << vrijeme_proteklo()/1000 << " sec" << endl;
	dat.close();
	dat.clear();
}

void statistika(){
	int brojac;
	dat.open("data", ios::in | ios::binary);
	while (true){
		dat.read((char*)&autor, sizeof(autori));
		if (dat.eof()) break;
		if (autor.sifra != 0) brojac++;
	}
	cout << "Broj nepraznih zapisa: " << brojac << endl;
	dat.close();
	dat.clear();
}


int main(){
	int i;
	do{
		cout << "0: Kreiranje prazne datoteke i izracun prostog broja" << endl;
		cout << "1: Unos podataka u relativnu datoteku" << endl;
		cout << "2: Pretrazivanje relativne datoteke" << endl;
		cout << "3: Statistika" << endl;
		cout << "9: Kraj" << endl;
		cout << "Odabir: ";
		cin >> i;
		if (i == 9) break;
		switch(i){
			case 0:
				cout << "Velicina datoteke u zapisima: ";
				cin >> velicina_dat;
				kreiranje();
				prvi_manji_prost_broj();
				cout << "Prost broj: " << prost_broj << endl;
				break;
			case 1:
				upis();
				break;
			case 2:
				pretrazivanje();
				break;
			case 3:
				statistika();
				break;
		}
	}while (true);
}
