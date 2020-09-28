#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

int *brDretvi;
int broj = 0;

pthread_mutex_t monitor;
pthread_cond_t uvjet;
sem_t binSemUnos;

void *barijera(void *brDretve)
{
        int unos;
        pthread_mutex_lock(&monitor);

        printf("Broj dretve: %d | Unesite broj: ", *((int*)brDretve));
        scanf("%d", &unos);

        broj = broj + 1;

        if (broj < *brDretvi)
        {
                pthread_cond_wait(&uvjet, &monitor);
        }
        else
        {
                pthread_cond_broadcast(&uvjet);
                printf("\n");
        }

        pthread_mutex_unlock(&monitor);
        printf("Broj dretve: %d | Unesen broj: %d\n", *((int*)brDretve), unos);
}

void monDestroy()
{
        pthread_mutex_destroy(&monitor);
        pthread_cond_destroy(&uvjet);
}

int main(int argc, char*argv[])
{

        int n = atoi(argv[1]);
        pthread_t threadID[n];
        brDretvi = &n;
        int pomPolje[n], i;

        pthread_mutex_init(&monitor, NULL);
        pthread_cond_init(&uvjet, NULL);

        for(i = 0; i < n;i++)
        {
        	pomPolje[i] = i;
        }
        for (i = 0; i < n; i++)
        {
                pthread_create(&threadID[i], NULL, barijera, &pomPolje[i]);
                sleep(1);
        }


        for (i = 0; i < n; i++)
        {
                pthread_join(threadID[i], NULL);
        }
        monDestroy();
        return 0;
}
