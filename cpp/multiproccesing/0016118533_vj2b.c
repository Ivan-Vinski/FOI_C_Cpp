#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<math.h>
#include<signal.h>
#define PI 3.14159265358979
struct mnogokut{
        int brojStranica;
        double duljinaStranice;
};

void izracun(int brojStranica, double duljinaStranice){
        double opseg, povrsina;
        povrsina = (0.25)*brojStranica * duljinaStranice * (duljinaStranice/tan(PI/brojStranica));
        printf("N = %d ; a = %f ; Povrsina: %f\n", brojStranica, duljinaStranice, povrsina);
        sleep(1);
        opseg = brojStranica * duljinaStranice;
        printf("N = %d ; a = %f ; Opseg: %f\n", brojStranica, duljinaStranice, opseg);
};

int main(int argc, char* argv[]){
        int i, argc_pom;
        argc_pom = argc - 1;
        struct mnogokut mnogokutObj[5];
        for (i = 1; i <= argc_pom/2; i++){
                mnogokutObj[i-1].brojStranica = atoi(argv[2*i -1]);
                mnogokutObj[i-1].duljinaStranice = atof(argv[2*i]);
        }
        int j;
        for (j = 0; j < argc_pom/2; j++){
                switch(fork()){
                        case 0:
                                izracun(mnogokutObj[j].brojStranica, mnogokutObj[j].duljinaStranice);
                                exit(0);
                        case -1:
                                printf("Greska u switchu vracen -1\n");
                                return 0;
                }
        }
        while(j--) wait(NULL);
        printf("\n");
        return 0;
}
