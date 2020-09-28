#include<iostream>
#include<cstring>
#include<cmath>
#include"vrijeme.cc"
using namespace std;

float zbroj_povrsina = 0;
class ctrokut{
	public:
		static int broj;
		bool jest_trokut, pravokutni_trokut;
		ctrokut *sljedeci, *prethodni, *zadnji;
		float a, b, c, vrijeme;
		char naziv[20];
		float povrsina(){
			s = (a+b+c)/2;
			return sqrt(s*(s-a)*(s-b)*(s-c));
		}
		ctrokut* unos(ctrokut* tekuci){
			float pom;
			vrijeme1.pocetak();
			cout << "Naziv trokuta: " ;
			cin.ignore();
			cin.getline(tekuci->naziv, 10);
			cout << "a: " ;
			cin >> tekuci->a;
			cout << "b: " ;
			cin >> tekuci->b;
			cout << "c: ";
			cin >> tekuci->c;
			vrijeme1.kraj();
			
			tekuci->pravokutni_trokut = false;
			if ((tekuci->a > tekuci->b) && (tekuci->a > tekuci->c)){
				if (pow(tekuci->a, 2) == pow(tekuci->b,2) + pow(tekuci->c, 2))
				tekuci->pravokutni_trokut = true;
			}
			if ((tekuci->b > tekuci->a) && (tekuci->b > tekuci->c)){
				if (pow(tekuci->b, 2) == pow(tekuci->a, 2) + pow(tekuci->c, 2)){
					tekuci->pravokutni_trokut = true;
				}
			}
			if ((tekuci->c > tekuci->b) && (tekuci->c > tekuci->a)){
				if (pow(tekuci->c, 2) == pow(tekuci->a, 2) + pow(tekuci->b, 2)){
					tekuci->pravokutni_trokut = true;
				}
			}
			
			pom = (int)(vrijeme1.proteklo() / 10);
			tekuci->vrijeme = (float)(pom / 100);
			
			if ((a+b > c) && (b+c > a) && (a+c > b)) tekuci->jest_trokut = true;
			else tekuci->jest_trokut = false;
			return tekuci;
		}
		void ispis(ctrokut *glava){
			ctrokut *tekuci = glava->sljedeci;
			while (tekuci){
				cout << tekuci->naziv << endl;
				cout << "a: " <<  tekuci->a << endl;
				cout << "b: " << tekuci->b << endl;
				cout << "c: " << tekuci->c << endl;
				if (tekuci->jest_trokut){
					zbroj_povrsina += tekuci->povrsina();
					cout << "Povrsina: " << tekuci->povrsina() << endl;
				}
				else if (!tekuci->jest_trokut){
					cout << "Nije trokut" << endl;
				}
				cout << "Vrijeme: " << tekuci->vrijeme << endl;
				cout << "---------------------------------------" << endl;
				tekuci = tekuci->sljedeci;
			}
		}
		void ispis2(ctrokut *glava){
			ctrokut *pompok = glava->sljedeci;
			while (pompok){
				if (pompok->pravokutni_trokut){
					cout << pompok->naziv << endl;
					cout << "a: " << pompok->a << endl;
					cout << "b: " << pompok->b << endl;
					cout << "c: " << pompok->c << endl;
					if (pompok->jest_trokut){
						cout << "Povrsina: " << pompok->povrsina() << endl;
					}
					cout << "Vrijeme: " << pompok->vrijeme << endl;
					cout << "Pravokutni trokut" << endl;
				}
				pompok = pompok->sljedeci;
			}
			
			
		}
	private:
		float s;
		cvrijeme vrijeme1;
};
int ctrokut::broj;
int main(){
	int i;
	ctrokut *glava = new ctrokut;
	glava->sljedeci = NULL;
	glava->prethodni = NULL;
	ctrokut *zadnji = glava;
	do{
		cout << "1: Unos podataka o trokutima u polju trokuta" << endl;
		cout << "2: Ispis podataka o unesenim trokutima" << endl;
		cout << "3: Statistika" << endl;
		cout << "4: Prepoznavanje odredenih vrsta trokuta" << endl;
		cout << "Odabir: " ;
		cin >> i;
		if (i == 9) break;
		
		switch(i){
			case 1:
				cout << "Broj trokuta: " ;
				cin >> ctrokut::broj;
				for (int i=0; i < ctrokut::broj; i++){
					ctrokut *tekuci = new ctrokut;
					zadnji->sljedeci = tekuci;
					tekuci->unos(tekuci);
					tekuci->sljedeci = NULL;
					zadnji = tekuci;
				}
				break;
			case 2:
				cout << "Ispis: " << endl;
				glava->ispis(glava);
				break;
			case 3:
				cout << "Broj zapisa: " << ctrokut::broj << endl;
				cout << "Zbroj povrsina trokuta: " << zbroj_povrsina<<endl;
				break;
			case 4:
				glava->ispis2(glava);
				break;
		}
	}while(true);
	
	system("pause");
	return 0;
}
