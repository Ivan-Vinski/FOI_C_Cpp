#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int broj, N, oznaka_reda = 0;


void unos_a(){
        printf("\n");
        if (oznaka_reda == 1){
                printf("Igracu A, varalica ste, na redu je bio igrac B!\n");
                oznaka_reda = 0;
                return;
        }
        do{
                printf("Igrac A, unesite broj zigica:");
                scanf("%d",&broj);
        }while (broj < 1 || broj > 3 || N < broj);
        N = N - broj;
        printf("Igrac A oduzeo je sa stola %d zigica \n", broj);

}
void unos_b(){
        printf("\n");
        if (oznaka_reda == 0){
                printf("Igracu B, varalica ste, na redu je bio igrac A!\n");
                oznaka_reda = 1;
                return;
        }
        do{
                printf("Igrac B, unesite broj zigica: ");
                scanf("%d", &broj);
        }while (broj < 1 || broj > 3 || N < broj);
        N = N - broj;
        printf("Igrac B oduzeo je sa stola %d zigica \n", broj);
}

int main (int argc, char *argv[]){
        int pom;
        pom = atoi(argv[1]);
        N = pom;
        const int M = 3;
        sigset(SIGINT, unos_a);
        sigset(SIGQUIT, unos_b);
        if (N < M){
                printf("Netocan unos \n");
                return 0;
        }
        else {
                printf("M = 3 ; N = %d \n", N);
                printf("Na stolu su %d zigica, a odjednom ih mozes uzeti najvise 3. Let the game beggin! \n", N);
        }
        while (N > 0 && oznaka_reda != 2){
                if (oznaka_reda == 0){
                        printf("Zigica na stolu: %d ; Na redu igrac A \n", N);
                }
                else if (oznaka_reda == 1){
                        printf("Zigica na stolu: %d ; Na redu igrac B \n", N);
                }
                pause();
                if (oznaka_reda == 0) oznaka_reda = 1;
                else if (oznaka_reda == 1) oznaka_reda = 0;
        }
        if (oznaka_reda == 0) printf("Igrac A je pobjednik, cestitke!\n");
        if (oznaka_reda == 1) printf("Igrac B je pobjednik, cestitke!\n");
        printf("\n");
        return 0;
}
