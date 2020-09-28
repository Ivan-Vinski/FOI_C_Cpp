#include<iostream>
#include<cstring>
using namespace std;

struct studenti{
	char prez_ime[30], smjer[20];
	int sifra;
	studenti *sljedeci, *prethodni;
};

struct element{
	int broj;
	element *ljevo, *desno;
};

void unos_bin (element *korijen){
	int broj;
	element *tekuci, *zadnji;
	bool jos = true;
	zadnji = korijen;
	cout << "Broj: ";
	cin>>broj;
	
	do{
		if (broj>zadnji->broj){
			if (zadnji->desno){
				zadnji = zadnji->desno;
			}
			else {
				tekuci = new element;
				zadnji->desno = tekuci;
				tekuci->broj = broj;
				tekuci->desno = NULL;
				tekuci->ljevo = NULL;
				jos = false;
			}
		}
		else{
			if (zadnji->ljevo){
				zadnji = zadnji->ljevo;
			}
			else {
				tekuci = new element;
				zadnji->ljevo = tekuci;
				tekuci->ljevo = NULL;
				tekuci->desno = NULL;
				jos = false;
			}
		}
	}while (jos);
	
}

void ispis (studenti *lista){
	studenti *ispis;
	ispis = lista->sljedeci;
	while (ispis){
		cout << ispis->prez_ime << endl;
		cout << ispis->smjer << endl;
		cout << ispis->sifra << endl;
		cout << "----------------------" << endl;
		ispis = ispis->sljedeci;
	}
}

void brisi(studenti *lista){
	studenti *brisi;
	int sifra;
	cout << "Sifra: ";
	cin>>sifra;
	brisi = lista->sljedeci;
	while (brisi){
		if (brisi->sifra == sifra){
			if (!brisi->sljedeci){
				brisi->prethodni->sljedeci = NULL;
				delete brisi;
				return;
			}
			brisi->sljedeci->prethodni = brisi->prethodni;
			brisi->prethodni->sljedeci = brisi->sljedeci;
			delete brisi;
			return;
		}
		
		
		
		brisi = brisi->sljedeci;
	}
	cout << "nije naden" << endl;
	
	
}

void dodaj_pocetak (studenti *lista){
	studenti *drugi, *tekuci, *ispis;
	drugi = lista->sljedeci;
	tekuci = new studenti;
	lista->sljedeci = tekuci;
	drugi->prethodni = tekuci;
	tekuci->sljedeci = drugi;
	tekuci->prethodni = lista;
	
	
	cout << "Ime i prezime: ";
	cin.ignore();
	cin.getline(tekuci->prez_ime, 30);
	cout << "Smjer: " ;
	cin.getline(tekuci->smjer, 20);
	cout << "ID: ";
	cin>>tekuci->sifra;
	cout << "--------------------" << endl;
}

void dodaj_kraj(studenti *lista){
	studenti *tekuci, *zadnji, *ispis;
	zadnji = lista;
	while (zadnji->sljedeci){
		zadnji = zadnji->sljedeci;
	}
	
	tekuci = new studenti;
	zadnji->sljedeci = tekuci;
	tekuci->sljedeci = NULL;
	tekuci->prethodni = zadnji;
	
	cout << "Ime i prezime: ";
	cin.ignore();
	cin.getline(tekuci->prez_ime, 30);
	cout << "Smjer: ";
	cin.getline(tekuci->smjer, 20);
	cout << "ID: ";
	cin>>tekuci->sifra;
	cout << "-------------------" << endl;
}




int main(){
	int i;
	studenti *lista = new studenti;
	lista->sljedeci = NULL;
	lista->prethodni = NULL;
	
	element *korijen = new element;
	korijen->desno = NULL;
	korijen->ljevo = NULL;
	
	do{
		cout << "1: Upis na kraj i ispis"<<endl;
		cout << "2: Uspis na pocetak i ispis" << endl;
		cout << "3: Brisanje i ispis" << endl;
		cout << "9: Izlaz" << endl;
		cout << "Odabir: ";
		cin >> i;
		cout << "---------------------"<< endl;
		switch (i){
			case 1:
				dodaj_kraj(lista);
				ispis (lista);
				break;
			case 2:
				dodaj_pocetak(lista);
				ispis(lista);
				break;
			case 3:
				brisi(lista);
				ispis(lista);
				break;
			case 4:
				unos_bin(korijen);
				break;
		}
	}while (i!=9);
	
	cout << "Kraj! Bok bok " << endl;
	
	system("pause");
	return 0;
}
