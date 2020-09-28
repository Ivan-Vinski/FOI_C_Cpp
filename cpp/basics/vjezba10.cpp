#include <iostream>
#include <cstdlib>
#include <cstring>
 
using namespace std;
 
class cpredmeti {
    public:
        class cpredmeti_zapis {
            public:
            int sifra;
            char naziv[20];
            char nazivSmjera[20];
       
            void unos() {
                cout << "Unesite sifru predmeta: "; cin >> sifra;
                cout << "Unesite naziv predmeta: "; cin >> naziv;
                cout << "Unesite naziv smjera: "; cin >> nazivSmjera;
            }
           
            void ispis() {
                cout << "Sifra predmeta: " << sifra << " Naziv predmeta: " << naziv << " Naziv smjera: " << nazivSmjera << endl;
            }
        };
       
        cpredmeti *sljedeci = NULL;
        cpredmeti_zapis zapis;
       
        void unos() {
            zapis.unos();
        }
       
        void ispis() {
            zapis.ispis();
        }
       
        bool provjeriSmjer(char smjer[20]) {
            return strcmp(zapis.nazivSmjera, smjer) == 0;
        }
};
 
class cprijave {
    public:
        class cprijave_zapis {
            public:
            int sifra;
            int sifraPredmeta;
            int mat_br;
            int rok;
           
            bool unos(cpredmeti *glavaPredmeta) {
                cout << "Unesite sifru predmeta: "; cin >> sifraPredmeta;
               
                cpredmeti *trenutni = glavaPredmeta->sljedeci;
                bool pronadjen = false;
               
                while(trenutni) {
                    if(trenutni->zapis.sifra == sifraPredmeta) {
                        pronadjen = true;
                        break;
                    }
                   
                    trenutni = trenutni->sljedeci;
                }
               
                if(!pronadjen) return false;
               
                cout << "Unesite sifru prijave: "; cin >> sifra;
                cout << "Unesite maticni broj studenta: "; cin >> mat_br;
                cout << "Unesite rok: "; cin >> rok;
               
                return true;
            }
           
            void ispis() {
                cout << "Sifra prijave: " << sifra << " Sifra predmeta: " << sifraPredmeta << " Maticni broj studenta: " << mat_br << " Rok: " << rok << endl;
            }
        };
       
        cprijave *sljedeci = NULL;
        cprijave_zapis *zapis;
       
        bool unos(cpredmeti *glavaPredmeta) {
            return zapis->unos(glavaPredmeta);
        }
       
    cprijave() {
        zapis = new cprijave_zapis;
        cout << "Konstruktor\n";
    }
   
    ~cprijave() {
        delete zapis;
    }
};
 
 
cpredmeti *predmetiHead = new cpredmeti;
cprijave *prijaveHead = new cprijave;
 
void opcija1() {
    cpredmeti *zadnji = predmetiHead, *novi = new cpredmeti;
    int ukupno = 0;
 
    while(zadnji->sljedeci) {
        zadnji = zadnji->sljedeci;
        ukupno++;
    }
   
    cout << "Ukupno prethodnih upisa: " << ukupno << endl;
 
    zadnji->sljedeci = novi;
    novi->unos();
   
    cpredmeti *trenutni = predmetiHead->sljedeci;
   
    while(trenutni) {
        trenutni->ispis();
        trenutni = trenutni->sljedeci;
    }
}
 
void opcija2() {
    cpredmeti *trenutni = predmetiHead->sljedeci;
    char smjer[20];
   
    cout << "Unesite smjer: "; cin >> smjer;
   
    while(trenutni) {
        if(trenutni->provjeriSmjer(smjer))
            trenutni->ispis();
           
        trenutni = trenutni->sljedeci;
    }
}
 
void opcija3() {
    cprijave *novi = new cprijave;
 
    if(!novi->unos(predmetiHead)) {
        delete novi;
        cout << "Prijava za nepostojeci predmet!\n";
    }
   
    cprijave *zadnji = prijaveHead;
   
    while(zadnji->sljedeci)
        zadnji = zadnji->sljedeci;
   
    zadnji->sljedeci = novi;
}
 
void opcija4() {
    int sifraPredmeta;
   
    cout << "Unesite trazenu sifru predmeta: "; cin >> sifraPredmeta;
   
    cpredmeti *trenutni = predmetiHead->sljedeci, *trazeni;
   
    bool pronadjen = false;
   
    while(trenutni) {
        if(trenutni->zapis.sifra == sifraPredmeta) {
            trazeni = trenutni;
            pronadjen = true;
            break;
        }
       
        trenutni = trenutni->sljedeci;
    }
   
    if(!pronadjen) {
        cout << "Taj predmet ne postoji!\n";
        return;
    }
   
    cout << "Predmet: " << trazeni->zapis.naziv << ", smjer: " << trazeni->zapis.nazivSmjera << endl;
   
    cprijave *trenutniP = prijaveHead->sljedeci;
 
    while(trenutniP) {
        if(trenutniP->zapis->sifraPredmeta == sifraPredmeta) {
            cout << "\tPrijava: " << trenutniP->zapis->sifra << ", maticni broj studenta: " << trenutniP->zapis->mat_br << ", rok: " << trenutniP->zapis->rok << ", sljedeci: " << trenutniP->sljedeci << endl;
        }
       
        trenutniP = trenutniP->sljedeci;
    }
}
 
int main() {
    int opcija;
   
    do {
        cout << "1. Upis predmeta na kraj liste predmeta i ispis cijele liste predmeta\n";
        cout << "2. Popis predmeta zadanog smjera\n";
        cout << "3. Unos prijave na kraj liste prijava\n";
        cout << "4. Ispis liste prijava za zadani predmet\n";
        cout << "9. Izlaz iz programa\n";
        cout << " > "; cin >> opcija;
       
        switch(opcija) {
            case 1:
                opcija1();
                break;
           
            case 2:
                opcija2();
                break;
               
            case 3:
                opcija3();
                break;
           
            case 4:
                opcija4();
                break;
           
            default:
                cout << "Nepoznata opcija!\n";
                break;
        }
    } while(opcija != 9);
   
    return 0;
}
