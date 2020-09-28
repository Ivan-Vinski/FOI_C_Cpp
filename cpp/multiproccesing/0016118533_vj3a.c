#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define LIJEVA_O 0
#define DESNA_O 1
#define MISIONARI 0
#define LJUDOZDERI 1

int broj[2][2], br_putnika = 0, cun_ljudozder = 0, cun_misionar = 0, cun_obala = 1, iskrc = 0;



sem_t kriticni_odsjecak, ukrcavanje, iskrcavanje, s[2][2], cun;
pthread_t dretva, cun_dretva;

void *misionar(void *x)
{
        sem_wait(&kriticni_odsjecak);
        int obala = rand() % 2;
        int usao_u_cun = 0;
        broj[obala][MISIONARI] = broj[obala][MISIONARI] + 1;

        while (!usao_u_cun) {
                if (!iskrc && (obala == cun_obala) && (br_putnika < 7)) {
                        usao_u_cun = 1;
                        broj[obala][MISIONARI] = broj[obala][MISIONARI] - 1;
                        cun_misionar = cun_misionar + 1;
                        br_putnika = br_putnika + 1;

                        if (br_putnika == 3)
                                sem_post(&ukrcavanje);

                        if ((br_putnika >= 3) && (br_putnika < 7) && (broj[obala][LJUDOZDERI] > 0))
                                sem_post(&s[obala][LJUDOZDERI]);
                }

                else {
                        sem_post(&kriticni_odsjecak);
                        sem_wait(&s[obala][MISIONARI]);
                        sem_wait(&kriticni_odsjecak);
                }
        }

        sem_post(&kriticni_odsjecak);
        sem_wait(&cun);
        sem_wait(&kriticni_odsjecak);

        if (obala) printf("Misionar s desne obale iskrcan je na lijevu obalu\n");
        else printf("Misionar s lijeve obale iskrcane je na desnu obalu\n");

        cun_misionar = cun_misionar - 1;
        br_putnika = br_putnika - 1;
        br_putnika = br_putnika - 1;

        if (!br_putnika) sem_post(&iskrcavanje);
        sem_post(&kriticni_odsjecak);
}

void *ljudozder(void *x)
{
        sem_wait(&kriticni_odsjecak);
        int obala = rand() % 2;
        int usao_u_cun = 0;
        broj[obala][LJUDOZDERI] = broj[obala][LJUDOZDERI] + 1;

        while (!usao_u_cun) {
                if (!iskrc && (obala == cun_obala) && (br_putnika < 7) && (cun_ljudozder < cun_misionar)) {
                        usao_u_cun = 1;
                        broj[obala][LJUDOZDERI] = broj[obala][LJUDOZDERI] + 1;
                        cun_ljudozder = cun_ljudozder + 1;
                        br_putnika = br_putnika + 1;

                        if (br_putnika == 3)
                                sem_post(&ukrcavanje);

                        if ((br_putnika >= 3) && (br_putnika < 7) && (broj[obala][MISIONARI] > 0))
                                sem_post(&s[obala][MISIONARI]);
                }

                else {
                        sem_post(&kriticni_odsjecak);
                        sem_wait(&s[obala][LJUDOZDERI]);
                        sem_wait(&kriticni_odsjecak);
                }
                        sem_wait(&kriticni_odsjecak);
                }
        }

        sem_post(&kriticni_odsjecak);
        sem_wait(&cun);
        sem_wait(&kriticni_odsjecak);

        if (obala) printf("Ljudozder s desne obale iskrcan je na lijevu obalu\n");
        else printf("Ljudozder s lijeve obale iskrcan je na desnu obalu\n");

        cun_ljudozder = cun_ljudozder - 1;
        br_putnika = br_putnika - 1;

        if (!br_putnika) sem_post(&iskrcavanje);
        sem_post(&kriticni_odsjecak);
}

void *dretva_cun(void *x)
{
        int i;
        while (1)
        {

                sem_wait(&ukrcavanje);

                sleep(1);

                printf("Camac je krenuo\n");
                if (cun_obala) printf("DESNA");
                else printf("LIJEVA");
				
                printf("->");

                if (cun_obala) printf("LIJEVA\n");
                else printf("DESNA\n");

                sleep(1);
                printf("Camac je presao rijeku\n");
                iskrc = 1;
                for (i = 0; i < br_putnika; i++) sem_post(&cun);


                sem_wait(&iskrcavanje);
                iskrc = 0;
                cun_obala = 1 - cun_obala;

                for (i = 0; i < broj[cun_obala][MISIONARI]; i++)
                        sem_post(&s[cun_obala][MISIONARI]);

                for (i = 0; i < broj[cun_obala][LJUDOZDERI]; i++)
                        sem_post(&s[cun_obala][LJUDOZDERI]);

        }
}

void unistiSemafore()
{
        sem_destroy(&kriticni_odsjecak);
        sem_destroy(&ukrcavanje);
        sem_destroy(&iskrcavanje);
        sem_destroy(&s[0][0]);
		        sem_destroy(&s[1][0]);
        sem_destroy(&s[0][1]);
        sem_destroy(&s[1][1]);
        sem_destroy(&cun);
}

void izlaz(int sig)
{
        unistiSemafore();
        kill(getpid(), SIGKILL);
}

void suma()
{
        while (1)
        {
                pthread_create(&dretva, NULL, ljudozder, NULL);
                sleep(1);
                pthread_create(&dretva, NULL, misionar, NULL);
                pthread_create(&dretva, NULL, ljudozder, NULL);
                sleep(1);
        }
}

int main()
{

        broj[0][0] = 0;
        broj[0][1] = 0;
        broj[1][0] = 0;
		broj[1][1] = 0;

        srand(time(0));

        sem_init(&kriticni_odsjecak, 0, 1);
        sem_init(&ukrcavanje, 0, 0);
        sem_init(&iskrcavanje, 0, 0);
        sem_init(&s[0][0], 0, 0);
        sem_init(&s[1][0], 0, 0);
        sem_init(&s[0][1], 0, 0);
        sem_init(&s[1][1], 0, 0);
        sem_init(&cun, 0, 0);

        sigset(SIGINT, izlaz);

        pthread_create(&cun_dretva, NULL, &dretva_cun, NULL);

        suma();

        return 0;
}
