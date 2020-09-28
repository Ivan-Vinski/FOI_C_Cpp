#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<ctime>
using namespace std;

struct autori {
	char prez_ime[30], naslov[20];
	int sifra;
};

fstream dat;
autori autor;
char naziv_datoteke[30];

void unos_dat(){
	char jos;
	jos = 'd';
/*"out" jer u nju upisujemo, "app" da otvori postojecu datoteku i ne brise sadrzaj,
 "binary" jer radimo s dat s fiksnom duljinom zapisa
*/
	dat.open(naziv_datoteke, ios::out   | ios::app |  ios::binary);
	while(jos== 'd'){
		cout << "Ime i prezime: ";
		cin.ignore();
		cin.getline(autor.prez_ime, 30);
		cout << "Naslov rada: ";
		cin.getline(autor.naslov, 20);
		cout << "Sifra: ";
		cin >> autor.sifra;
		dat.write((char*) &autor, sizeof(autori)); //podaci se pisu iz objekta autor strukture autori u datoteku
		cout << "Jos ? ";
		cin >> jos;
	}
	dat.close();
	dat.clear();	
	
}

void ispis_dat(){
//"in" sluzi za citanje/ispis iz datoteke, "binary" uvijek kad je datoteka fiksne velicine zapisa
	dat.open(naziv_datoteke, ios::in | ios::binary);
	int brojac;
	brojac = 0;
	while (true){
		dat.read((char*)&autor, sizeof(autori));
		/*
		"read" ucita podatak duljine "autori" na adresi "autor" u datoteku
		te prebacuje datotecni pokazivac na sljedeci element "autori" u datoteci
		 */
		if (dat.eof()) break; //ako je kraj datoteke, break;
		cout << autor.prez_ime << endl;
		cout << autor.naslov << endl;
		cout << autor.sifra << endl;
		cout << "-------------------------------------"<<endl;
		brojac++;
	}
	cout << "Ukupni broj autora: "<< brojac<< endl;
	dat.close();
	dat.clear();
	return;
}

void pretrazivanje_dat(){
	int sifra;
	cout << "Sifra trazenog autora: ";
	cin >> sifra;
	dat.open(naziv_datoteke, ios::binary | ios::in);
	while (true){
		dat.read((char*)&autor, sizeof(autori));
		if (dat.eof()) break;
		if (autor.sifra == sifra){
			cout << autor.prez_ime << endl;
			cout << autor.naslov << endl;
			cout << autor.sifra << endl;
			cout << "-------------------------------------"<<endl;
			dat.close();
			dat.clear();
			return;
		}
	}
	cout << "Nije naden autor s unesenom sifrom." << endl;
	cout << "-------------------------------------"<<endl;
	dat.close();
	dat.clear();
}

void unos_provjera(){
/*ovdje zapravo ide funckija "pretrazivanje_dat" koja je malo 
modificirana da umjesto ispisa poruke upise podatke u datoteku

najsigurnije je napraviti prvo otvaranje u modu "in" za citanje,
pa tako vrsiti pretrazivanje (prethodnu funkciju prakticki) i to 
staviti u pomocnu varijablu.
*/
	dat.open(naziv_datoteke, ios::in  | ios::binary);
	
	char jos;
	jos = 'd';
	
	autori pom;

	cout << "Ime i prezime: ";
	cin.ignore();
	cin.getline(pom.prez_ime, 30);
	cout << "Naslov: ";
	cin >> pom.naslov;
	cout << "Sifra: ";
	cin >> pom.sifra;
	while (true){
		dat.read((char*)&autor, sizeof(autori));
		if (dat.eof()) break;
		if (pom.sifra == autor.sifra){
			cout << "Sifra vec postoji" << endl;
			dat.close();
			dat.clear();
			return;
		}
	}
/*zatim cemo zatvoriti dat i otvoriti u novom modu
za upis koji mora imati i ovaj "app" da se ne obrisu
podaci od prije u toj datoteci
*/
	dat.close();
	dat.clear();
	dat.open(naziv_datoteke, ios::out | ios::app | ios::binary);
	dat.write((char*)&pom, sizeof(autori));
	dat.close();
	dat.clear();
}

int main(){
	int i;
	do{
		cout << "-------------------------------------"<<endl;
		cout << "1: Unos podataka u datoteku" << endl;
		cout << "2: Ispis sadrzaja cijele datoteke" << endl;
		cout << "3: Pretrazivanje datoteke" << endl;
		cout << "4: Unos podataka u datoteku uz provjeru kljuca" << endl;
		cout << "9: Izlaz iz programa"<< endl;
		cout << "-------------------------------------"<<endl;
		cout << "Izbor: ";
		cin >> i;
		cout << "-------------------------------------"<<endl;
		
//Korisnik unosi naziv datoteke te se provjerava je li vec stvorena na disku
		if (i>0 && i<5){
			cout << "Naziv datoteke: ";
			cin >> naziv_datoteke;
//mod "in"(za citanje) otvara samo postojece datoteke, ne stvara nove
			dat.open(naziv_datoteke, ios::in | ios::binary);
			if (!dat){	//citaj: ako datoteka nije otvorena ilitiga ako datoteka ne postoji jos na disku
				dat.open(naziv_datoteke, ios::out | ios::binary);
				//ako ne postoji, otvaramo ju u modu out koji stvara novu datoteku
				dat.close();// i obvezno zatvaramo tu datoteku
				dat.clear();
			}
			else {//ako mod "in" uspije otvoriti datoteku, znaci da postoji vec pa se ispisuje poruka
				cout << "Datoteka " << naziv_datoteke << " vec postoji na disku." << endl;
				dat.close();//i obvezno zatvarmo taj "in" mod
				dat.clear();
			}
		}
		
		switch (i){
			case 1:
				unos_dat();
				break;
			case 2:
				ispis_dat();
				break;
			case 3:
				pretrazivanje_dat();
				break;
			case 4:
				unos_provjera();
				break;
		}
	}while(i != 9);
}
