#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class cstavka{
	private:
		cstavka *sljedeci;
	public:
		int sifra, kolicina;
		char naziv[30];
		double cijena;
	cstavka (){
		sljedeci = NULL;
		cout << "Alociran element liste" << endl;
	}
	~cstavka(){
		cout << "Dealocirana stavka " << naziv << endl;
	}
	void Unos(){
		cstavka *zadnji, *tekuci;
		zadnji = this;
		while (zadnji->sljedeci){
			zadnji = zadnji->sljedeci;
		}
		tekuci = new cstavka;
		zadnji->sljedeci = tekuci;
		tekuci->sljedeci = NULL;
		
		cout << "Naziv stavke: ";
		cin.ignore();
		cin.getline(tekuci->naziv, 30);
		cout << "Cijena: ";
		cin >> tekuci->cijena;
		cout << "Kolicina: ";
		cin >> tekuci->kolicina;
		cout << "Sifra: " ;
		cin >> tekuci->sifra;
	}
	void Ispis(){
		cstavka *tekuci;
		tekuci = this->sljedeci;
		while(tekuci){
			cout << "Naziv stavke: " << tekuci->naziv << endl;
			cout << "Cijena: " << tekuci->cijena << endl;
			cout << "Kolicina: " << tekuci->kolicina << endl;
			cout << "Sifra: " << tekuci->sifra << endl;
			cout << "-------------------------------------------------------------------------------------------------------" << endl;
			tekuci = tekuci->sljedeci;
		}
	}
	void Iznos(){
		cstavka *tekuci;
		tekuci = this->sljedeci;
		double iznos;
		while(tekuci){
			iznos = tekuci->cijena*tekuci->kolicina;
			cout << "Iznos stavke "<< tekuci->naziv << ": " << iznos << endl;
			tekuci = tekuci->sljedeci;
		}
	}
	cstavka* dealokacija(){
		cstavka *tekuci, *prethodni;
		prethodni = this->sljedeci;
		tekuci = prethodni->sljedeci;
		while (tekuci){
			delete prethodni;
			prethodni = tekuci;
			tekuci = tekuci->sljedeci;
		}
		delete prethodni;
		return NULL;
	}
};



int main(){
	int i, broj_vez_listi, broj;
	bool jos, polje_alocirano = false;
	cstavka *polje;
	cstavka *lista;
	do{
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		cout << "1: Alokacija glave pojedine vezane liste,unos pojedinog elementa liste, ispis svih elemenata liste" << endl;
		cout << "2: Iznos** svih elemenata liste, dealokacija vezane liste (glava ostaje)" << endl;
		cout << "3: Alokacija polja vezanih listi/unos podataka u zadanu vezanu listu***/Ispis pojedine vezane liste" << endl;
		cout << "4: Dealokacija svih vezanih listi i polja" << endl;
		cout << "9: Izlaz iz programa " << endl;
		cout << "-------------------------------------------------------------------------------------------------------"<< endl;
		cout << "Izbor: ";
		cin >> i;
		if (i == 9) break;
		switch(i){
			case 1:
				lista = new cstavka;
				jos = true;
				while (jos){
					lista->Unos();
					cout << "Nastaviti? (0/1)" ;
					cin >> jos;
				}
				lista->Ispis();
				break;
			case 2:
				lista->Iznos();
				lista->dealokacija();
				break;
			case 3:
				if (!polje_alocirano){
					cout << "Broj vezanih listi: ";
					cin >> broj_vez_listi;
					polje = new cstavka[broj_vez_listi];
					cout << "Alokacija polja" << endl;
					polje_alocirano = true;
				}
				else {
					cout << "Polje vec postoji" << endl;
				}
				cout << "-------------------------------------------------------------------------------------------------------" << endl;
				do{
					cout << "Broj liste u koju zelite upisivati: ";
					cin >> broj;
				}while(broj < 0 || broj > broj_vez_listi-1);
				cout << "Upis u listu broj " << broj << endl;
				jos = true;
				while (jos){
					polje[broj].Unos();
					cout << "Nastaviti unos? (0/1): " ;
					cin >> jos;
				}
				do{
					cout << "Broj liste koju treba ispisati: ";
					cin >> broj;
				}while (broj < 0 || broj > broj_vez_listi-1);
				cout << "-------------------------------------------------------------------------------------------------------" << endl;
				polje[broj].Ispis();
				break;
			case 4:
				for (int i = 0; i < broj_vez_listi; i++){
					polje[i].dealokacija();
				}
				delete [] polje;
				polje_alocirano = false;
				break;		
		}
	}while(true);
}
