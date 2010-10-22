/*
 * File:   main.c
 * Author: Tatu Tahvanainen, Jarkko Nyman, Aleksi Aalto
 *
 * Created on 29. syyskuuta 2010, 13:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "hajautus.h"
#include "linkitettylista.h"



int lueTiedostosta(FILE*, lista* hajautustaulu[]);
void kirjoitaTiedostoon(lista* hajautustaulu[], FILE* tiedosto);
int hajauta(struct tyontekija *duunari);
tyontekija* luoTyontekija(char *nimi, char *sukun, int aloitusv, int palkka);
void luoHajautusTaulu(lista* taulu[72]);
void lueSolmu(solmu *solmu, FILE *tiedosto);
int sijoitaHajautusTauluun(lista* taulu[], tyontekija* t);
void poistaTyontekija(lista* taulu[], char* etunimi, char* sukunimi);
int tarkistaOnkoJo(lista* taulu[], char* etunimi, char* sukunimi);
int aloitusRuutu(lista* taulu[], FILE* tiedosto);
void lisaysRuutu(lista* taulu[]);
void poistoRuutu(lista* taulu[]);
void etsintaRuutu(lista* taulu[]);
void tallennusRuutu(lista* taulu[], FILE* tiedosto);


int main(void) {


    FILE* tiedosto1;
    FILE* tiedosto2;
    char lukutiednimi[100];
    char talltiednimi[100];
    lista* hajautustaulu[71];
    int jatkuu = 1;


    luoHajautusTaulu(hajautustaulu);
    if ((hajautustaulu[71]->paa) != NULL) {
        printf("ERROR\n");
    }
/*
    sijoitaHajautusTauluun(hajautustaulu, p);
int tarkistaOnkoJo(lista* taulu[], char* etunimi, char* sukunimi);
    etsiListasta(hajautustaulu[10], "Esa", "Keskinen");

    */
    printf("Anna luettavan tiedoston nimi\n");

    if (scanf("%99s", lukutiednimi) != 1) {
       fprintf(stderr, "Tiedostonimen lukeminen käyttäjältä epäonnistui!\n");
       return (EXIT_FAILURE);
    }
    printf("Anna tallennettavan tiedoston nimi\n");

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

    // Käyttöliittymän käynnistys.
    while (jatkuu == 1){
        jatkuu = aloitusRuutu(hajautustaulu, tiedosto2);
    }
    //poistaDuunari(hajautustaulu, "kelopaa", "paskis"); //<-- poiston testausta
    //poistaDuunari(hajautustaulu, "bul", "lul");
    //poistaListasta(hajautustaulu[0], "Jarkko", "Nyman");
    
    
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
        temp = luoTyontekija(tempnimi, tempsukunimi, tempaloitusv, temppalkka);
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

void kirjoitaTiedostoon(lista* hajautustaulu[], FILE* tiedosto) {

    for (int i=0; i<71; i++){
        printf("i = %d\n", i);
        if (hajautustaulu[i] != NULL){
            if (hajautustaulu[i]->paa != NULL){
                lueSolmu(hajautustaulu[i]->paa, tiedosto);
               
            }
       }
       free(hajautustaulu[i]);
    }
}

void lueSolmu(solmu *solmuP, FILE *tiedosto) {
    solmu* edell=NULL;
    while (solmuP != NULL){
        printf("HALLOOO\n");
        fprintf(tiedosto, "%s %s %d %d\n", solmuP->duunari->etunimi,
        solmuP->duunari->sukunimi, solmuP->duunari->aloitusvuosi,
        solmuP->duunari->palkka);
        edell = solmuP;
        solmuP = solmuP->seur;
        vapautaSolmunVaraamaMuisti(edell);

    }
}

int hajauta(struct tyontekija *duunari){
    int summa = 0;
    int stringPituus;
    int i;
    printf("NYMANIN Sällin nimi on [%s%s]\n", duunari->etunimi, duunari->sukunimi);
    stringPituus = strlen(duunari->etunimi);
    for (i = 0; i < stringPituus; i++){
        summa = summa + duunari->etunimi[i];
    }
    stringPituus = strlen(duunari->sukunimi);
    for (i = 0; i < stringPituus; i++){
        summa = summa + duunari->sukunimi[i];
    }
    printf("Nimen kirjaimien summa on = %d\n", summa);

    summa = summa%71;

    printf("Modulo taas on = %d\n", summa);
    return summa;
}
int hajautaNimesta(char* etun, char* sukun) { //TODO tutki josko olisi helppo poistaa tämä funkkari kokonaan hevonvittuun.
    int stringPituus, i = 0, summa=0;
    stringPituus = strlen(etun);
    printf("PITUUS ON %d\n", stringPituus);
    for (i = 0; i < stringPituus; i++)
        summa = summa + etun[i];
    stringPituus = strlen(sukun);
    for (i = 0; i < stringPituus; i++)
        summa = summa + sukun[i];
    printf("Sällin nimi on [%s%s]\n", etun, sukun);
    printf("SUMMA ON %d\n", summa);
    summa = summa%71;
    return summa;
}

 tyontekija* luoTyontekija(char *nimi, char *sukun, int aloitusv, int palkka) {

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
     for (int i=0; i<72; i++) {
         taulu[i] = luoLista();
         if (taulu[i] == NULL)
             printf("taulu on null\n");
     }
 }
// TODO Ei toimi testattava.
void poistaTyontekija(lista* taulu[], char* etunimi, char* sukunimi) {
    int indeksi;
    printf("poiston alku\n");
    indeksi = hajautaNimesta(etunimi, sukunimi);
    printf("INDEKSI ON %d\n", indeksi);
    if (taulu[indeksi] != NULL) {
        if (poistaListasta(taulu[indeksi], etunimi, sukunimi) == 0) {
            printf("Poistoa ei suoritettu koska työntekijää ei löydy\n");
        }
    }
    printf("poiston loppu\n");

}

// Palauttaa 0, jos samanniminen työntekijä hajautustaulussa, muuten 1.
int tarkistaOnkoJo(lista* taulu[], char* etunimi, char* sukunimi) {

    int indeksi = hajautaNimesta(etunimi,sukunimi);

    if (taulu[indeksi] != NULL) {
        if(taulu[indeksi] != NULL) {
        
            if (etsiListasta(taulu[indeksi], etunimi, sukunimi) == NULL) {
                return 1;
            }
            else {
              
                return 0;
            }
        }
    }
    return 1;

}

int aloitusRuutu(lista* taulu[],FILE* tiedosto) {

    int valinta;

    printf("Tyontekijarekisteri\n\n");
    printf("Valitse:\n\n"),
    printf("1. Lisää Työntekijä\n\n");
    printf("2. Poista työntekiä\n\n");
    printf("3. Etsi Työntekijä\n\n");
    printf("4. Tallenna rekisteri\n\n");
    printf("0. Lopeta\n\n");

    while (scanf("%1d",&valinta) != 1);

    if (valinta == 1) {

        lisaysRuutu(taulu);
    }
    if (valinta == 2) {

        poistoRuutu(taulu);
    }
    if (valinta == 3) {

        etsintaRuutu(taulu);
    }
    if (valinta == 4) {

        tallennusRuutu(taulu, tiedosto);
    }
    if (valinta == 0) {

        tallennusRuutu(taulu, tiedosto);

        return 0;
    }

    return 1;

}

void lisaysRuutu(lista* taulu[]) {

    char etunimi[20];
    char sukunimi[30];
    int aloitusvuosi;
    int palkka;
    tyontekija* t;


    printf("Anna lisättävän työntekijän etunimi:\n");
    while (scanf("%19s",etunimi) == 0);

    printf("Anna lisättävän työntekijän sukunimi:\n");
    while (scanf("%29s",sukunimi) == 0);

    printf("Anna lisättävän työntekijän aloitusvuosi esim. 1989:\n");
    while (scanf("%4d",&aloitusvuosi) != 1);

    printf("Anna lisättävän työntekijän palkka:\n");
    while (scanf("%d",&palkka) != 1);

    if (tarkistaOnkoJo(taulu, etunimi, sukunimi) != 0) {

        t = luoTyontekija(etunimi, sukunimi,aloitusvuosi,palkka);
        sijoitaHajautusTauluun(taulu, t);
    }
    else {
        printf("Samanniminen työntekijä jo rekisterissä.\n");
        printf("Lisäystä ei suoritettu!\n");
    }



}


void poistoRuutu(lista* taulu[]) {

    char etunimi[20];
    char sukunimi[30];

    printf("Anna poistettavan työntekijän etunimi\n");
    while (scanf("%19s",etunimi) == 0);

    printf("Anna poistettavan työntekijän sukunimi\n");
    while (scanf("%29s",sukunimi) == 0);

    poistaTyontekija(taulu, etunimi, sukunimi);


}

void etsintaRuutu(lista* taulu[]) {
    char etunimi[20];
    char sukunimi[30];
    int aloitusvuosi;
    int palkka;
    tyontekija* t;

    printf("Anna etsittävän työntekijän etunimi\n");
    while (scanf("%19s",etunimi) == 0);

    printf("Anna etsittävän työntekijän sukunimi\n");
    while (scanf("%29s",sukunimi) == 0);

    int indeksi = hajautaNimesta(etunimi, sukunimi);
        if ((t = (etsiListasta(taulu[indeksi], etunimi, sukunimi))) != NULL){
            aloitusvuosi = t->aloitusvuosi;
            palkka = t->palkka;
            printf("Henkilön %s %s: Aloitusvuosi %d ja palkka %d\n", etunimi, sukunimi, aloitusvuosi, palkka);
    }
    else{
        printf("Työntekijää %s %s ei löytynyt rekisteristä\n", etunimi, sukunimi);
    }

}


void tallennusRuutu(lista* taulu[], FILE* tiedosto) {
    char valinta;

    printf("Haluatko tallentaa rekisterin\n");
    printf("Kyllä (k) | EI (e)\n");
    //TODO scanffi kusee korjattava..
    while (scanf("%1c", &valinta) == 0) {

        printf("fail koska %c", valinta);
    }

    if (valinta == ('k' || 'K')) {
        kirjoitaTiedostoon(taulu, tiedosto);
        printf("Rekisteri tallenntu tiedostoon");

    }
   
}
