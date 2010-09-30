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
     char *etunimi;
     char *sukunimi;
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
    char etun[20];
    char sukun[30];
    int p=0;
    int aloitusv=0;
    struct tyontekija temp;

    if ((tiedosto = fopen("/fs-3/0/tatutahv/Oma/c-ohjelmointi/ht/testi", "r" )) == NULL){
        fprintf(stderr, "Tiedoston avaaminen epäonnistu\n");
        return (EXIT_FAILURE);
    }

    if (tiedosto != NULL) {

       printf(":E\n");

    }

    printf("JEE\n");

    while (feof(tiedosto) == 0) {

        //printf("jee1\n");



        fscanf(tiedosto, "%s %s %d%d\n", etun, sukun, &p, &aloitusv);
        printf("%s %s\n", etun, sukun);
            //fprintf(stderr, "tiedosto kusee\n");
        temp.etunimi = *etun;
        temp.sukunimi = *sukun;
        temp.palkka = p;
        temp.aloitusvuosi = aloitusv;
        //LASKE HAJAUTUSFUNKTIOLLA JA SIJOITA HAJAUTUSTAULUUN
        //ETTEI KADOTETA TÄTÄ TYÖNTEKIJÄÄ -> hajauta(sukun);
        //#ifdef DEB

        printf("etunimi: %s sukunimi: %s palkka %d aloitusv: %d\n", &temp.etunimi, &temp.sukunimi, temp.palkka, temp.aloitusvuosi);

        //printf("jee2\n");
        //#endif
    }

    if(fclose(tiedosto) == EOF) {
        fprintf(stderr, "Tiedoston sulkeminen epäonnistui");
        return EXIT_FAILURE;

    }


    return EXIT_SUCCESS;
}