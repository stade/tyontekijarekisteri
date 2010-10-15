/*
 * File:   main.c
 * Author: Tatu Tahvanainen, Jarkko Nyman, Aleksi Aalto
 *
 * Created on 29. syyskuuta 2010, 13:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hajautus.h"
#include "linkitettylista.h"

/*
 *
 */




int lueTiedostosta(FILE*, lista* hajautustaulu[]);
int kirjoitaTiedostoon(lista* hajautustaulu[], FILE* tiedosto);
int hajauta(struct tyontekija *duunari);
tyontekija* luoDuunari(char *nimi, char *sukun, int aloitusv, int palkka);
void luoHajautusTaulu(lista* taulu[16]);
void lueSolmu(solmu *solmu, FILE *tiedosto);
int sijoitaHajautusTauluun(lista* taulu[], tyontekija* t);
void poistaDuunari(lista* taulu[], char* etunimi, char* sukunimi);

int main(void) {

    FILE* tiedosto1;
    FILE* tiedosto2;
    char lukutiednimi[100];
    char talltiednimi[100];
    lista* hajautustaulu[16];




    /*if ((p = (luoDuunari("Esa", "Keskinen", 2010, 5000))) == NULL) {
        return (EXIT_FAILURE);
    }*/

    //printf("nimi = %s\n", p->etunimi);
    luoHajautusTaulu(hajautustaulu);
    if ((hajautustaulu[15]->paa) != NULL) {
        printf("ERROR\n");
    }/*
    sijoitaHajautusTauluun(hajautustaulu, p);

    etsiListasta(hajautustaulu[10], "Esa", "Keskinen");

    */
    printf("Anna luettavan tiedoston nimi\n");

    if (scanf("%99s", lukutiednimi) != 1) {
       fprintf(stderr, "Tiedostonimen lukeminen käyttäjältä epäonnistui!\n");
       return (EXIT_FAILURE);
    }
    printf("Anna tallenntavan tiedoston nimi\n");

    if (scanf("%99s", talltiednimi) != 1) {
       fprintf(stderr, "Tiedostonimen lukeminen käyttäjältä epäonnistui!\n");
       return (EXIT_FAILURE);
    }

    if ((tiedosto1 = fopen(lukutiednimi, "r" )) == NULL){
        fprintf(stderr, "Tiedoston avaaminen epäonnistu\n");
        return (EXIT_FAILURE);
    }
    if ((tiedosto2 = fopen(talltiednimi, "w" )) == NULL){
        fprintf(stderr, "Tiedoston avaaminen epäonnistu\n");
        return (EXIT_FAILURE);
    }

    lueTiedostosta(tiedosto1, hajautustaulu); // <------- LUE

    //poistaDuunari(hajautustaulu, "kelopaa", "paskis"); <-- poiston testausta
    //poistaDuunari(hajautustaulu, "bul", "lul");

    kirjoitaTiedostoon(hajautustaulu, tiedosto2); // <---- KIRJOITA
    
    if(fclose(tiedosto1) == EOF) {
        fprintf(stderr, "Tiedoston sulkeminen epäonnistui");
        return EXIT_FAILURE;
    }
    if(fclose(tiedosto2) == EOF) {
        fprintf(stderr, "Tiedoston sulkeminen epäonnistui");
        return EXIT_FAILURE;
    }
    
    
    return (EXIT_SUCCESS);
}

int lueTiedostosta(FILE* tiedosto, lista* hajautustaulu[]) {
    printf("nyt luetaan tiedostosta\n");
    //struct tyontekija taulu[20]; //taulukollinen työntekijöitä, jotta meillä pointterit niihin (ennen hajautustaulun implementaatiota)
    int j=0; //apumuuttuja taulun läpikäyntiin
    char tempnimi[20];
    char tempsukunimi[30];
    int tempaloitusv;
    int temppalkka;
    while (feof(tiedosto) == 0) {
        printf("luetaan riviä tiedostosta\n");
        struct tyontekija* temp;
        fscanf(tiedosto, "%19s %29s %d%d\n", tempnimi, tempsukunimi, &tempaloitusv, &temppalkka);
        printf("tiedot skannattu\n");
        temp = luoDuunari(tempnimi, tempsukunimi, tempaloitusv, temppalkka);
        if (temp == NULL)
            printf("duunarin luonti kusi\n");
        printf("luodun duunarin nimi on : %s\n", temp->etunimi);
            //fprintf(stderr, "tiedosto kusee\n");
        sijoitaHajautusTauluun(hajautustaulu, temp);
        printf("sijoitettu tauluun\n");
        //LASKE HAJAUTUSFUNKTIOLLA JA SIJOITA HAJAUTUSTAULUUN (tämänhetkisen taulun sijaan)
        //ETTEI KADOTETA TÄTÄ TYÖNTEKIJÄÄ -> hajauta(temp.sukunimi);


        //printf("etunimi: %s sukunimi: %s palkka %d aloitusv: %d\n", temp.etunimi, temp.sukunimi, temp.palkka, temp.aloitusvuosi);

        //printf("taulukon lokerossa %d on työntekijä: %s %s %d %d\n", j, taulu[j].etunimi, taulu[j].sukunimi, taulu[j].palkka, taulu[j].aloitusvuosi); //testataan toimiiko taulu
        j++;
    }



    return EXIT_SUCCESS;
}
int kirjoitaTiedostoon(lista* hajautustaulu[], FILE* tiedosto) {
    //lista *temp;
    //tyontekija *temp;
    
    for (int i=0; i<15; i++){
        printf("i = %d\n", i);
        if (hajautustaulu[i] != NULL){
            if (hajautustaulu[i]->paa != NULL){
                lueSolmu(hajautustaulu[i]->paa, tiedosto);
            }
       }
    }
    
    return (EXIT_FAILURE);
}
void lueSolmu(solmu *solmuP, FILE *tiedosto) {

    if (solmuP != NULL){
        printf("HALLOOO\n");
        fprintf(tiedosto, "%s %s %d %d\n", solmuP->duunari->etunimi,
        solmuP->duunari->sukunimi, solmuP->duunari->aloitusvuosi,
        solmuP->duunari->palkka);

       lueSolmu(solmuP->seur, tiedosto);

    }


}

int hajauta(struct tyontekija *duunari){
    int summa = 0;
    int i;
    for (i = 0; i < 20; i++){
        summa = summa + duunari->etunimi[i];
    }
    for (i = 0; i < 30; i++){
        summa = summa + duunari->sukunimi[i];
    }


    printf("Nimen kirjaimien summa on = %d\n", summa);

    summa = summa%15;

    printf("Modulo taas on = %d\n", summa);
    return summa;
}
int hajautaNimesta(char* etun, char* sukun) {
    int stringPituus, i = 0, summa=0;
    stringPituus = strlen(etun);
    for (i = 0; i < stringPituus; i++)
        summa += etun[i];
    for (i = 0; i < stringPituus; i++)
        summa += sukun[i];
    summa = summa%15;
    return summa;
}

 tyontekija* luoDuunari(char *nimi, char *sukun, int aloitusv, int palkka) {

    tyontekija *t;

    if ((t = malloc(sizeof(tyontekija))) == NULL) {
        fprintf(stderr, "Muistin varaaminen epäonnistui");
        return NULL;
    }

    strcpy(t->etunimi, nimi);
    strcpy(t->sukunimi, sukun);
    t->aloitusvuosi = aloitusv;
    t->palkka = palkka;

    return t;

}
 int sijoitaHajautusTauluun(lista* taulu[], tyontekija* t) {
     int indeksi = hajauta(t);
     int kk;
     if ((kk = lisaaListaanLoppuun(taulu[indeksi], t)) == 0)
         printf("loppuun lisääminen epäonnistui\n");
     
    return 0;

 }
void luoHajautusTaulu(lista* taulu[]) {
     for (int i=0; i<16; i++) {
         taulu[i] = luoLista();
         if (taulu[i] == NULL)
             printf("taulu on null\n");
     }
 }
void poistaDuunari(lista* taulu[], char* etunimi, char* sukunimi) {
    int indeksi;
    tyontekija* duunari;
    printf("poiston alku\n");
    indeksi = hajautaNimesta(etunimi, sukunimi);
    printf("hajautus tehty\n");
    if (taulu[indeksi]!=NULL)
        if (poistaListasta(taulu[indeksi], etunimi, sukunimi) == 0) {
            printf("Poistoa ei suoritettu koska työtekijää ei löydy\n");
        }
    printf("poiston loppu\n");

}


