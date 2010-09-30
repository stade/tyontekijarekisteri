/* 
 * File:   main.c
 * Author: Tatu Tahvanainen, Jarkko Nyman, Aleksi Aalto
 *
 * Created on 29. syyskuuta 2010, 13:15
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


 // TODO charit dynaamisiksi.
struct tyontekija {
     char* etunimi[20];
     char* sukunimi[30];
     int palkka;
     int aloitusvuosi;
     // TODO struct tyontekija seuraava;

};

int lueTiedostosta();
int main(int argc, char** argv) {

   


    /* TODO
    struct taulu {

       struct tyontekijat;


    };



    struct hajautus {

        int koko;
        struct taulu;



    };

    */

    lueTiedostosta();

    return (EXIT_SUCCESS);
}

int lueTiedostosta() {

    FILE *tiedosto;
    char *etun;
    char *sukun;
    int p;
    int aloitusv;


    if ((tiedosto = fopen("/fs-3/0/tatutahv/Oma/c-ohjelmointi/ht/testi", "r" )) == NULL){
        fprintf(stderr, "Tiedoston avaaminen epäonnistu\n");
        return (EXIT_FAILURE);
    }

    if (tiedosto != NULL) {

       printf(":E\n");

    }

    printf("JEE\n");

    while (feof(tiedosto) != 0) {

        printf("jee1");

        if (fscanf(tiedosto, "%*s %*s %d %d", &p, &aloitusv) != 4){
            fprintf(stderr, "Tiedostosta lukeminen epäonnistui\n");
            return (EXIT_FAILURE);
        }
        struct tyontekija temp;
        //temp.etunimi = *etun;
        //temp.sukunimi = sukun;
        temp.palkka = p;
        temp.aloitusvuosi = aloitusv;
        //LASKE HAJAUTUSFUNKTIOLLA JA SIJOITA HAJAUTUSTAULUUN
        //ETTEI KADOTETA TÄTÄ TYÖNTEKIJÄÄ -> hajauta(sukun);
        //#ifdef DEB

        printf("etunimi: %s sukunimi: %s palkka %d aloitusv: %d", temp.etunimi, temp.sukunimi, temp.palkka, temp.palkka);

        printf("jee2\n");
        //#endif
    }

    if(fclose(tiedosto) == EOF) {
        fprintf(stderr, "Tiedoston sulkeminen epäonnistui");
        return EXIT_FAILURE;

    }


    return EXIT_SUCCESS;
}