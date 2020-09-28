#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include"binarno_pretrazivanje.cc"
#include"biblioteka_vrijeme.cc"
using namespace std;

struct studenti{
	char prez_ime[30];
	int mat_br, god_stud;
	double vrijeme;
};

fstream maticna_dat;
fstream indeksna_dat;

void upis(){
	studenti student;
	tindeks indeks;
	maticna_dat.open("dat_v6", ios::in | ios::binary);
	if (!maticna_dat){
		cout << "Stvorena je nova datoteka" << endl;
		maticna_dat.open("dat_v6", ios::out | ios::binary);
		indeksna_dat.open("ind_v6", ios::out  | ios::binary);
	}
	else {
		cout << "Datoteka je na disku" << endl;
		maticna_dat.close();
		maticna_dat.clear();
		maticna_dat.open("dat_v6", ios::in | ios::out | ios::ate | ios::binary);
		indeksna_dat.open("ind_v6", ios::in | ios::out | ios::ate | ios::binary);	
	}
	vrijeme_pocetak();
	cout << "Ime i prezime: ";
	cin.ignore();
	cin.getline(student.prez_ime, 30);
	cout << "Godina studiranja: ";
	cin >> student.god_stud;
	cout << "Maticni broj: ";
	cin >> student.mat_br;
	vrijeme_kraj();
	student.vrijeme = vrijeme_proteklo() / 1000 ;
	maticna_dat.write((char*)&student, sizeof(studenti));
	indeks.kljuc = student.mat_br;
	indeks.adresa = (int)maticna_dat.tellp() - sizeof(studenti);
	indeksna_dat.write((char*)&indeks, sizeof(tindeks));
	maticna_dat.close();
	maticna_dat.clear();
	indeksna_dat.close();
	indeksna_dat.clear();
	preslozi_indeks("ind_v6", indeks);
}

void pretrazivanje(){
	bool naden;
	tindeks indeks;
	studenti student;
	int kljuc, gore, dolje, sredina, broj_zapisa;
	cout << "Maticni broj trazenog studenta: ";
	cin >> kljuc;
	indeksna_dat.open("ind_v6", ios::in | ios::binary);
	if (!indeksna_dat){
		cout << "Datoteka nije kreirana" << endl;
		indeksna_dat.close();
		indeksna_dat.clear();
	}
	else {
		indeksna_dat.seekg(0, ios::end);
		broj_zapisa = ((int)indeksna_dat.tellg() / sizeof(tindeks));
		indeksna_dat.close();
		indeksna_dat.clear();
	}
	indeksna_dat.open("ind_v6", ios::in | ios::binary);
	maticna_dat.open("dat_v6", ios::in | ios::binary);
	dolje = 0;
	gore = broj_zapisa;
	while (true){
		sredina = (dolje + gore)/2;
		indeksna_dat.seekg(sredina * sizeof(tindeks));
		indeksna_dat.read((char*)&indeks, sizeof(tindeks));
		if (kljuc == indeks.kljuc){
			naden = true;
			maticna_dat.seekg(indeks.adresa);
			maticna_dat.read((char*)&student, sizeof(studenti));
			cout << student.prez_ime << endl;
			cout << student.god_stud << endl;
			cout << student.mat_br << endl;
			cout << student.vrijeme << endl;
			break;
		}
		if (kljuc > indeks.kljuc){
			dolje = sredina;
		}
		else {
			gore = sredina;
		}
		if (sredina == (gore+dolje)/2) break;
	}
	maticna_dat.close();maticna_dat.clear();
	indeksna_dat.close();indeksna_dat.clear();
	if (!naden){
		cout << "Zapis nije naden" << endl;
	}
}

void ispis(){
	tindeks indeks;
	studenti ispis;
	indeksna_dat.open("ind_v6", ios::in | ios::binary);
	maticna_dat.open("dat_v6", ios::in | ios::binary);
	while (true){
		indeksna_dat.read((char*)&indeks, sizeof(tindeks));
		if (indeksna_dat.eof()) break;
		maticna_dat.seekg(indeks.adresa);
		maticna_dat.read((char*)&ispis, sizeof(studenti));
		cout << ispis.prez_ime << endl;
		cout << ispis.god_stud << endl;
		cout << ispis.mat_br << endl;
		cout << ispis.vrijeme << endl;
	}
	maticna_dat.close();
	maticna_dat.clear();
	indeksna_dat.close();
	indeksna_dat.clear();
}

void statistika(){
	int zbroj = 0, brojac = 0;
	tindeks indeks;
	indeksna_dat.open("ind_v6", ios::in | ios::binary);
	if (!indeksna_dat){
		cout << "Datoteka nije kreirana" << endl;
		indeksna_dat.close();
		indeksna_dat.clear();
		return;
	}
	while (true){
		indeksna_dat.read((char*)&indeks, sizeof(tindeks));
		if (indeksna_dat.eof()) break;
		zbroj += indeks.kljuc;
		brojac++;
	}
	cout << "Aritmeticka sredina svih kljuceva: " << (double)zbroj/brojac << endl;
	indeksna_dat.close();
	indeksna_dat.clear();
}

int main(){
	int i;
	do{
		cout << "1: Rucni unos podataka u indeksiranu datoteku."<<endl;
		cout << "2: Pretrazivanje indeksne datoteke prema primarnom kljucu." << endl;
		cout << "3: Ispis sadrzaja maticne datoteke u redosljedu primarnog kljuca." << endl;
		cout << "4: Statistika." << endl;
		cout << "9: Izlaz" << endl;
		cout << "Izbor: ";
		cin >> i;
		if (i == 9) break;
		
		switch(i){
			case 1:
				upis();
				break;
			case 2:
				pretrazivanje();
				break;
			case 3:
				ispis();
				break;
			case 4:
				statistika();
				break;
		}
	}while(true);
	system("pause");
	return 0;
}
