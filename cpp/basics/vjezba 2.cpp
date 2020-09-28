#include<iostream>
#include<cstring>
#include<ctime>

using namespace std;
//OSNOVNA STRUKTURA
struct autori{
	char prezime[15], ime[15], naslov_rada[20];
	int sifra;
	double vrijeme;
	autori *sljedeci;
};
//FUNKCIJA ZA UNOS STAVAKA NA LISTU
void unos (autori *lista){
	double vrijeme;
	bool sifra_nadena = false;
	autori *tekuci, *zadnji, *pompok;
	clock_t pocetak = clock();
	
	zadnji = lista;
	while (zadnji->sljedeci){
		zadnji = zadnji->sljedeci;
	}
	
	tekuci = new autori;
	zadnji->sljedeci = tekuci;
	tekuci->sljedeci = NULL;
	
	cout << "Sifra: ";
	cin>>tekuci->sifra;
/*moramo proci kroz listu i usporediti sve sifre s tekucom sifrom
kroz listu prolazimo isto kao i kod ispisa, ali ne koristimo pokazivac
"lista" jer on mora ostati netaknut pa imamo pomocni pokazivac "pompok"
*/
	pompok = lista;
	while (pompok != tekuci){ //pompok ide dok ne dode do tekuceg
		if (pompok->sifra == tekuci->sifra) sifra_nadena = true;
		pompok = pompok->sljedeci;
	}
/*Svi uvjeti za sifru su tu na jednom mjestu kao i izlaz iz funkcije
ako je sifra kriva. treba izbrisati koristeni pokazivac "tekuci", a
pokazivac "zadnji->sljedeci" mora se staviti na null za nadolazece unose
*/
	if ((tekuci->sifra<100) || (tekuci->sifra>999) || (sifra_nadena)){
		cout << "Pogresna sifra" << endl;
		cout << "----------------------------------------"<<endl;
		delete [] tekuci;
/*zadnji->sljedeci je stavljen da pokazuje na tekuci, pa ga moramo
vratiti da pokazuje na NULL da znamo gdje je kraj liste
*/
		zadnji->sljedeci = NULL;
		return;	
	}
	
	cout<< "Ime: ";
	cin.ignore();
	cin.getline(tekuci->ime,15);
	cout<< "Prezime: ";
	cin.getline(tekuci->prezime, 15);
	cout << "Naslov rada: ";
	cin.getline(tekuci->naslov_rada, 20);
	
	clock_t kraj = clock();
	vrijeme = (int)(kraj-pocetak)/10;
	tekuci->vrijeme = (double)vrijeme/100;
	cout << "----------------------------------------"<< endl;
}

//FUNKCIJA ZA ISPIS STAVAKA LISTE
void ispis (autori *lista){
	int br_elem = 0;
	double zbroj_vremena=0;
	autori *tekuci;
	tekuci = lista->sljedeci;
	while (tekuci){
		cout << tekuci->ime <<endl;
		cout << tekuci->prezime << endl;
		cout << tekuci->naslov_rada << endl;
		cout << tekuci->sifra << endl;
		zbroj_vremena += tekuci->vrijeme;
		cout << "Vrijeme potrebno za upis: "<< tekuci->vrijeme
		<< endl;
		cout << "---------------------------------------" << endl;
		
		tekuci = tekuci->sljedeci;
		br_elem++;
	}
//Ispis i pretvorbe u potrebne oblike (jedna ili 2 decimale)
	cout << "Broj elemenata u listi: "<< br_elem << endl; 
	zbroj_vremena = (int)(zbroj_vremena*10);
	cout << "Zbroj vremena upisa: " << (float)zbroj_vremena/10 << endl;
	cout << "----------------------------------------"<<endl;
}


int main(){
	autori *lista;
	bool alocirano = false;
	int i;
	//GENERIRANJE IZBORNIKA
	bool jos;
	do{
		jos = true;
		cout << "0: alokacija glave vezane liste" << endl;
		cout << "1: unos novog elementa u vezanu listu" << endl;
		cout << "2: ispis sadrzaja vezane liste" << endl;
		cout << "9: izlaz" << endl;
		cout << "----------------------------------------" << endl;
		do{
			cout << "Odaberite opciju: ";
			cin>>i;
			cout << "----------------------------------------"<< endl;
		}while ((i<0) || ((i>2) && i!=9));
		
	//ODABIR OPCIJA
		switch (i){	
			case 0:
				if (alocirano) {
					cout << "Memorija je vec alocirana" << endl;
					cout << "----------------------------------------" << endl;
					continue;
				}
				else if (!alocirano){
					lista = new autori;
					lista->sljedeci = NULL;
					alocirano = true;
					cout << "Memorija uspjesno alocirana." << endl;
					cout << "----------------------------------------" << endl;
				}
				break;
			case 1:
				if (!alocirano){	
					 cout << "Memorija nije alocirana, odaberite "<<endl;
					cout << "opciju 0 u glavnom izborniku." << endl;
					cout << "----------------------------------------" << endl;
					 continue;
				}
				else if (alocirano){
					unos(lista);
					break;
				}
			case 2:
				if (!alocirano){
					cout << "Memorija nije alocirana, odaberite "<<endl;
					cout << "opciju 0 u glavnom izborniku." << endl;
					cout << "----------------------------------------" << endl;
					continue;
				}
				else if (alocirano){
					ispis(lista);
					cout << "----------------------------------------" << endl;
					break;
				}
			case 9:
				cout<< "Kraj programa" << endl;
				jos = false;
				break;				
		}
	}while (jos);
	system("pause");
	return 0;
}
