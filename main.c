/*
 * File:   main.c
 * Author: Tatu Tahvanainen, Jarkko Nyman, Aleksi Aalto
 *
 * Created on 29. syyskuuta 2010, 13:15
 */

#include <stdio.h>
#include <stdlib.h>
#include "hajautus.h"
#include "linkitettylista.h"
/*
 *
 */


 // TODO charit dynaamisiksi.
typedef struct tyontekija {
     char etunimi[20];
     char sukunimi[30];
     int palkka;
     int aloitusvuosi;
     // TODO struct tyontekija seuraava;

}tyontekija;

int lueTiedostosta(FILE*);
int kirjoitaTiedostoon(struct tyontekija[], FILE*);
int main(int argc, char** argv) {

    FILE* tiedosto;
    char tiedostonimi[100];

    printf("Anna luettavan tiedoston nimi\n");

    if (scanf("%99s", tiedostonimi) != 1) {
       fprintf(stderr, "Tiedostonimen lukeminen käyttäjältä epäonnistui!\n");
       return (EXIT_FAILURE);
    }

    if ((tiedosto = fopen(tiedostonimi, "r" )) == NULL){
        fprintf(stderr, "Tiedoston avaaminen epäonnistu\n");
        return (EXIT_FAILURE);
    }
    
    lueTiedostosta(tiedosto); // <------- LUE
    
    if(fclose(tiedosto) == EOF) {
        fprintf(stderr, "Tiedoston sulkeminen epäonnistui");
        return EXIT_FAILURE;
    }

    kirjoitaTiedostoon(hajautustaulu, tiedosto); // <---- KIRJOITA

    return (EXIT_SUCCESS);
}

int lueTiedostosta(FILE* tiedosto) {

    struct tyontekija taulu[20]; //taulukollinen työntekijöitä, jotta meillä pointterit niihin (ennen hajautustaulun implementaatiota)
    int j=0; //apumuuttuja taulun läpikäyntiin
    
    while (feof(tiedosto) == 0) {

        struct tyontekija temp;
        fscanf(tiedosto, "%20s %30s %d%d\n", temp.etunimi, temp.sukunimi, &temp.palkka, &temp.aloitusvuosi);
        taulu[j]=temp; //asetetaan tämä nimenomainen työntekijä sen omaan lokeroon (j) tauluun

            //fprintf(stderr, "tiedosto kusee\n");

        //LASKE HAJAUTUSFUNKTIOLLA JA SIJOITA HAJAUTUSTAULUUN (tämänhetkisen taulun sijaan)
        //ETTEI KADOTETA TÄTÄ TYÖNTEKIJÄÄ -> hajauta(temp.sukunimi);


        printf("etunimi: %s sukunimi: %s palkka %d aloitusv: %d\n", temp.etunimi, temp.sukunimi, temp.palkka, temp.aloitusvuosi);

        printf("taulukon lokerossa %d on työntekijä: %s %s %d %d\n", j, taulu[j].etunimi, taulu[j].sukunimi, taulu[j].palkka, taulu[j].aloitusvuosi); //testataan toimiiko taulu
        j++;
    }



    return EXIT_SUCCESS;
}
int kirjoitaTiedostoon(struct tyontekija hajautustaulu[], FILE* tiedosto) {
    for (int i=0; i<100; i++)
        if (hajautustaulu[i]!=NULL)
            fprintf(tiedosto, "%s %s %d %d", hajautustaulu[i].etunimi,
                    hajautustaulu[i].sukunimi, hajautustaulu[i].aloitusvuosi,
                    hajautustaulu[i].palkka);
        else return(EXIT_FAILURE);
}