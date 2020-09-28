#include<iostream>
#include<cmath>
#include<cstring>
#include"vrijeme.cc"
using namespace std;
int netrokuti = 0;
class ctrokut{
	private:
		float s;
		cvrijeme vrijeme;
	public:
		bool trokut;
		float vrijeme_elem;
		static int brojac;
		char naziv[20];
		float a, b, c;
		void unos(){
			float pom;
			vrijeme.pocetak();
			cout << "Naziv trokuta: " ;
			cin.ignore();
			cin.getline(naziv, 20);
			cout << "a: ";
			cin >> a;
			cout << "b: ";
			cin >> b;
			cout << "c: " ;
			cin >> c;
			vrijeme.kraj();
			pom = (int)(vrijeme.proteklo() / 10);
			vrijeme_elem = (float)(pom / 100);
			trokut = false;
			if ((a + b > c) && (a + c > b) && (b + c > a)) trokut = true;
			if (!trokut) netrokuti++;	
		}
		float povrsina(){
			s = (a + b+ c) / 2;
			return sqrt(s*(s - a) * (s - b) * (s - c));
			
		}
		void ispis(){
			cout << "Naziv trokuta: " << naziv << endl;
			cout << "a: " << a << endl;
			cout << "b: " << b << endl;
			cout << "c: " << c << endl;
			if (trokut) cout << "Povrsina: " << povrsina() << endl;
			else cout << "Nije trokut" << endl;
			cout << "Vrijeme unosa: " << vrijeme_elem << " sec" << endl;
			cout << "........................................" << endl;
		}
};

ctrokut *polje = new ctrokut[50];
ctrokut pom;


int ctrokut::brojac = 0;
int main(){
	int i, x;
	
	do{
		cout << "1: Unos podataka o trokutima u polje trokuta" << endl;
		cout << "2: Ispis podataka o unesenim trokutima" << endl;
		cout << "3: Statistika" << endl;
		cout << "4: Prepoznavanje odredenih vrsta trokuta" << endl;
		cout << "9: Izlaz iz programa" << endl;
		cout << "Odabir: " ;
		cin >> i;
		if (i == 9) break;
		switch(i){
			case 1:
				x = ctrokut::brojac;
				polje[x].unos();
				ctrokut::brojac++;
				break;
			case 2:
				for (int i=0; i<ctrokut::brojac; i++){
					polje[i].ispis();
				}
				break;
			case 3:
				cout << "Ukupni broj trokuta: " << ctrokut::brojac << endl;
				cout << "Broj netrokuta: " << netrokuti << endl;
				break;
			case 4:
				for (int i=0; i < ctrokut::brojac-1; i++){
					memcpy(&pom, &polje[i], sizeof(ctrokut));
					for (int j = i+1; j < ctrokut::brojac; j++){
						if (pom.povrsina() == polje[j].povrsina()){
							if ((pom.a == polje[j].a) && (pom.b == polje[j].b) && (pom.c == polje[j].c)){
								cout << "Naziv trokuta: " << pom.naziv << endl;
								cout << "a: " << pom.a << endl;
								cout << "b: " << pom.b << endl;
								cout << "c: " << pom.c << endl;
								if (pom.trokut) cout << "Povrsina: " << pom.povrsina() << endl;
								else cout << "Nije trokut" << endl;
								cout << "-----------------------------------------" << endl;
							}
						}
					}
				}
				break;
		}
	}while(true);
	system("pause");
	return 0;
}
