#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

pthread_t threadID;
int klijenataUCekaonici, otvoreno = 0, klijentNaSisanju = 0, brijacSpava;

int *pokMjestaUCekaoni, *pokRadnoVrijeme;

pthread_mutex_t monitor;
pthread_cond_t uvjetSisanje, uvjetSpavanje;
sem_t semCekaonica;


void *klijent(void *x)
{
        int brKlijenta = *((int*)x);
        printf("KLIJENT[%d]: Zelim na brijanje!\n", brKlijenta);
        if (otvoreno && klijenataUCekaonici < *pokMjestaUCekaoni)
        {
                sem_wait(&semCekaonica);

                printf("KLIJENT[%d]: Ulazim u cekaonu (%d)\n", brKlijenta, klijenataUCekaonici+1);
                klijenataUCekaonici = klijenataUCekaonici + 1; // usao u cekaonicu

                sem_post(&semCekaonica);
                pthread_mutex_lock(&monitor);
                while (klijentNaSisanju)
                {
                        pthread_cond_wait(&uvjetSisanje, &monitor);
                }

                printf("KLIJENT[%d]: Juhu, napokon sam docekao brijanje\n", brKlijenta);

                klijentNaSisanju = 1;
                if (brijacSpava)
                {
                        brijacSpava = 0;
                        pthread_cond_signal(&uvjetSpavanje);
                }
                pthread_mutex_unlock(&monitor);

        }
        else
        {
                printf("KLIJENT[%d]: Nema mjesta u cekaonici, doci cu drugi put\n", brKlijenta);
        }

}

void *brijac(void *x)
{
        printf("BRIJAC: Salon je otvoren, radno vrijeme zavrsava za %d sec\n", *pokRadnoVrijeme);
        alarm(*pokRadnoVrijeme);
        otvoreno = 1;

        while (otvoreno)
        {
                pthread_mutex_lock(&monitor);
                while (!klijenataUCekaonici)
                {
                        printf("BRIJAC: Nema nikoga, spavam do daljnjega\n");
                        brijacSpava = 1;
                        pthread_cond_wait(&uvjetSpavanje, &monitor);
                }
                printf("BRIJAC: Krecem brijati\n");
                klijenataUCekaonici = klijenataUCekaonici - 1;
                sleep(5);
                printf("Zavrsio brijanje\n");
                klijentNaSisanju = 0;
                if (klijenataUCekaonici)
                {
                        pthread_cond_signal(&uvjetSisanje);
                }
                 pthread_mutex_unlock(&monitor);
        }


}

void monitorDestroy()
{
        sem_destroy(&semCekaonica);
        pthread_mutex_destroy(&monitor);
        pthread_cond_destroy(&uvjetSisanje);
        pthread_cond_destroy(&uvjetSpavanje);
}


void krajRadnogVremena()
{
        otvoreno = 0;
        printf("Kraj radnog vremena\n");
        monitorDestroy();
        exit(0);
}


int main(int argc, char *argv[])
{
        int mjestaUCekaoni, radnoVrijeme;
        mjestaUCekaoni = atoi(argv[1]);
        radnoVrijeme = atoi(argv[2]);

        pokMjestaUCekaoni = &mjestaUCekaoni;
        pokRadnoVrijeme = &radnoVrijeme;

        sigset(SIGALRM, krajRadnogVremena);

        sem_init(&semCekaonica, 0, 1);
        pthread_mutex_init(&monitor, NULL);
        pthread_cond_init(&uvjetSisanje, NULL);
        pthread_cond_init(&uvjetSpavanje, NULL);


        pthread_create(&threadID, NULL, brijac, NULL);

        sleep(2);
        int i = 0;
        while(1)
        {
                pthread_create(&threadID, NULL, klijent, &i);
                sleep(2);
                i = i + 1;
        }

        return 0;
}
