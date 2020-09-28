#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int *pokBrojevi, *pokTrazim, *pokBrojDretvi, zadnjiBroj = 0;
pthread_t *pokDretveID;


void udiUKO(int i)
{
        pokTrazim[i] = 1;
        int brojac;

		pokBrojevi[i] = zadnjiBroj + 1;
		zadnjiBroj = pokBrojevi[i];

        pokTrazim[i] = 0;

        for (brojac = 0; brojac < *pokBrojDretvi; brojac++)
        {
                while (pokTrazim[brojac] != 0)
                {
                        //radno cekaj;
                }
                while ((pokBrojevi[brojac] != 0)  &&  ((pokBrojevi[brojac] < pokB$
                         || (pokBrojevi[brojac] == pokBrojevi[i] && brojac < i))){
                        //radno cekaj;
                }
        }
}

void izadiIzKO(int i)
{
        pokBrojevi[i] = 0;
}

void *funkcija(void *x)
{
        int k, m, i = *((int*)x);
        for (k = 1; k <= 5; k++)
        {;
                udiUKO(i);
                for (m = 1; m <= 5; m++)
                {
                        printf("Dretva = %d ; k.o.br. = %d (%d/5)\n", i+1, k, m);
                        usleep(100);
                }
                izadiIzKO(i);
        }
}

int main(int argc, char *argv[]){
        int brojDretvi;
        brojDretvi = atoi(argv[1]);

        int poljeBrojevi[brojDretvi], poljeTrazim[brojDretvi];
        pthread_t threadID[brojDretvi];

        pokBrojDretvi = &brojDretvi;
        pokBrojevi = poljeBrojevi;
        pokTrazim = poljeTrazim;
        pokDretveID = threadID;

        int brojDretve[brojDretvi];
        int k;
        for (k = 0; k < brojDretvi; k++)
        {
                brojDretve[k] = k;
        }


        int i;
        int pom;
        for (i = 0; i < brojDretvi; i++)
        {
                if (pthread_create(&threadID[i], NULL, funkcija, &brojDretve[i]) != 0)
                {
                        printf("Greska pri stvaranju dretve\n");
                        exit(1);
                }
        }

        for (i = 0; i < brojDretvi; i++)
        {
                pthread_join(pokDretveID[i], NULL);
  	}
        return 0;
}


