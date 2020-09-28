#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include"tel_imenik.cc"
#include"biblioteka_vrijeme.cc"
#include"stanje_datoteke.cc"
using namespace std;

fstream dat;

struct autori_dat{
	char prez_ime[30], naslov[30];
	int sifra;
	double vrijeme;
};

struct autori_lista{
	char prez_ime[30], naslov[30];
	int sifra;
	double vrijeme;
	autori_lista *prethodni, *sljedeci;
};

autori_lista* dealokacija_liste(autori_lista *glava_liste){
	autori_lista *tekuci;
	tekuci = glava_liste->sljedeci;
	while(tekuci){
		delete tekuci->prethodni;
		tekuci = tekuci->sljedeci;
	}
	delete tekuci;
	return NULL;
}

void unos_dat(){
	bool nastavak = true;
	autori_dat autor;
	double vrijeme;
	dat.open("datoteka", ios::in | ios::binary);
	if (!dat){
		dat.open("datoteka", ios::out | ios::binary);
		dat.close();
		dat.clear();
		cout << "Stvorena je nova datoteka" << endl;
	}
	else {
		dat.close();
		dat.clear();
		cout << "Datoteka vec postoji na disku" << endl;
	}
	do{
		vrijeme_pocetak();
		cout << "Ime i prezime: ";
		cin.ignore();
		cin.getline(autor.prez_ime, 30);
		cout << "Naslov: ";
		cin.getline(autor.naslov, 30);
		cout << "Sifra: ";
		cin >> autor.sifra;
		vrijeme_kraj();
		vrijeme = (int)(vrijeme_proteklo() / 10);
		autor.vrijeme = (double)vrijeme/100;
		dat.open("datoteka", ios::out | ios::app | ios::binary);
		dat.write((char*)&autor, sizeof(autori_dat));
		dat.close();
		dat.clear();
		if (autor.vrijeme < 5) cout << "Unos kraci od 5 sec, ponovite" << endl;
		else nastavak = false;
	
	}while(nastavak);
}
void ispis(){
	autori_dat autor;
	dat.open("datoteka", ios::in | ios::binary);
	while(true){
		dat.read((char*)&autor, sizeof(autori_dat));
		if (dat.eof()) break;
		cout << autor.prez_ime << endl;
		cout << autor.naslov << endl;
		cout << autor.sifra << endl;
		cout << autor.vrijeme << endl;
	}
	dat.close();
	dat.clear();
}

void kopiranje(autori_lista *glava_liste){
	autori_dat autor;
	autori_lista *tekuci, *zadnji = glava_liste;
	
	dealokacija_liste(glava_liste);
	dat.open("datoteka", ios::in | ios::binary);
	if (!dat){
		cout << "Datoteka nije jos stvorena" << endl;
		dat.close();
		dat.clear();
		return;
	}
	while (true){
		dat.read((char*)&autor, sizeof(autori_dat));
		if (dat.eof()) break;
		cout << autor.sifra << endl;
		tekuci = new autori_lista;
		memcpy(tekuci->prez_ime, autor.prez_ime, 30);
		memcpy(tekuci->naslov, autor.naslov, 30);
		tekuci->sifra = autor.sifra;
		tekuci->vrijeme = autor.vrijeme;
		zadnji->sljedeci = tekuci;
		tekuci->sljedeci = NULL;
		zadnji = tekuci;
		
	}
	dat.close();
	dat.clear();
}


void ispis_liste(autori_lista *glava_liste){
	if (!glava_liste->sljedeci){
		cout << "Lista je prazna" << endl;
		return;
	}
	autori_lista *tekuci;
	tekuci = glava_liste->sljedeci;
	while (tekuci){
		cout << tekuci->prez_ime << endl;
		cout << tekuci->naslov << endl;
		cout << tekuci->sifra << endl;
		cout << tekuci->vrijeme << endl;
		tekuci = tekuci->sljedeci;
	}
}

int main(){
	int broj_zapisa;
	autori_lista *glava_liste = new autori_lista;
	glava_liste->sljedeci = NULL;
	glava_liste->prethodni = NULL;
	int i;
	do{
		cout << "1: Rucni unos zapisa u datoteku" << endl;
		cout << "2: Generiranje zapisa datoteke" << endl;
		cout << "3: Kopiranje sadrzaja datoteke u vezanu listu" << endl;
		cout << "4: Ispis sadrzaja vezane liste" << endl;
		cout << "9: Izlaz" << endl;
		cout << "Izbor: ";
		cin >> i;
		if (i == 9) break;
		switch(i){
			case 1:
				unos_dat();
				cout << "----------------" << endl;
				ispis();
				break;
			case 2:
				cout << "Broj zapisa: ";
				cin >> broj_zapisa;
			case 3:
				kopiranje(glava_liste);
				break;
			case 4:
				ispis_liste(glava_liste);
				break;
		}
	}while(true);
	
	system("pause");
	return 0;
}
