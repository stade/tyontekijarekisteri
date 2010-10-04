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
     char etunimi[20];
     char sukunimi[30];
     int palkka;
     int aloitusvuosi;
     // TODO struct tyontekija seuraava;

};

int lueTiedostosta();
int main(int argc, char** argv) {


    lueTiedostosta();
    return (EXIT_SUCCESS);
}

int lueTiedostosta() {

    FILE *tiedosto;
    struct tyontekija taulu[20]; //taulukollinen työntekijöitä, jotta meillä pointterit niihin (ennen hajautustaulun implementaatiota)
    int j=0; //apumuuttuja taulun läpikäyntiin
    char tiedostonimi[100];

    printf("Anna luettavan tiedoston nimi\n");


    // Luetaan tiedostonimi käyttäjän syötteestä raijoitetaan luettavien
    // merkkien määrä, jottei tule muistinylivuotoa.
    if (scanf("%99s", tiedostonimi) != 1) {
       fprintf(stderr, "Tiedostonimen lukeminen käyttäjältä epäonnistui!\n");
       return (EXIT_FAILURE);
    }

    if ((tiedosto = fopen(tiedostonimi, "r" )) == NULL){ //TODO muuta fiksummaksi, nyt muuttuu käyttäjän mukaan
        fprintf(stderr, "Tiedoston avaaminen epäonnistu\n");
        return (EXIT_FAILURE);
    }


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

    if(fclose(tiedosto) == EOF) {
        fprintf(stderr, "Tiedoston sulkeminen epäonnistui");
        return EXIT_FAILURE;

    }


    return EXIT_SUCCESS;
}