#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tyontekija {
     char etunimi[20];
     char sukunimi[30];
     int palkka;
     int aloitusvuosi;
     // TODO struct tyontekija seuraava;

}tyontekija;

typedef struct lista{
    struct solmu *paa;

}lista;
typedef struct solmu{
    struct tyontekija *duunari;
    struct solmu *seur;
}solmu;
lista* luoLista() {
     lista *p;
     p = ((lista *)malloc(sizeof(lista)));
     p->paa=NULL;
     if (p == NULL) {

         return NULL;
     }

     return p;

}
solmu* luoSolmu(struct tyontekija *t) {
     solmu *s;
     s = (solmu *)malloc(sizeof(solmu));

     if (s == NULL) {

         return NULL;
     }

     s->duunari = t;
     s->seur = NULL;
     return s;


}
int lisaaListaanLoppuun(lista *listap, struct tyontekija *duunaaja) { //TODO työntekijöiden nimien vertaus
    struct solmu* uusi = luoSolmu(duunaaja);
    struct solmu *seuraava;



    if ((listap->paa) == NULL) {
        listap->paa = uusi;
        return 1;
    }
    else {
        seuraava = listap->paa;

        while ((seuraava->seur) != NULL) {
            seuraava = seuraava->seur;
        }
        seuraava->seur = uusi;
        return 2;
    }
    return 0;
}

tyontekija* etsiListasta(lista *l, char* etun, char* sukun) {
    if (l == NULL) {
        return NULL;
    }
    char *tempetu, *tempsuku;

    //printf("seuraavan alustus\n");
    struct solmu* seuraava = l->paa;
    while (seuraava != NULL) {
        //printf("etsinnän whilessa\n");
        tempetu = seuraava->duunari->etunimi;
        tempsuku = seuraava->duunari->sukunimi;
        //printf("Etsinnässä edetään, nyt menossa: %s\n", tempetu);
        if (strcmp(tempetu, etun) == 0 &&
            strcmp(tempsuku, sukun) == 0) {


            //printf("ETSITTY HOMO ON LÖYTYNYT\n");
            return seuraava->duunari;
        } else seuraava = seuraava->seur;
    }
    return NULL;
}

void vapautaSolmunVaraamaMuisti(solmu *s) { //toimivuus ei taattu

    free(s->duunari);
    free(s);
    //printf("muisti vapautettu\n");
    s=NULL;
}


int poistaListasta(lista *l, char* etun, char* sukun) { //return 0 if fail
    if (l == NULL) {
        return 0;
    }
    solmu* nykyinen = l->paa;
    solmu* edellinen = l->paa;
    //printf("etsitty on %s %s ja paassa on %s %s\n", etun, sukun, nykyinen->duunari->etunimi, nykyinen->duunari->sukunimi);
    if (strcmp(nykyinen->duunari->etunimi, etun) == 0 && //jos poistettava oli ensimmäinen solmu
            strcmp(nykyinen->duunari->sukunimi, sukun) == 0) {
        //printf("iffissä ennen sijoitusta\n");
        l->paa = nykyinen->seur;
        vapautaSolmunVaraamaMuisti(nykyinen);
        return 1;
    }
    else nykyinen = nykyinen->seur;
    while (nykyinen != NULL) {

        if (strcmp(nykyinen->duunari->etunimi, etun) == 0 &&
            strcmp(nykyinen->duunari->sukunimi, sukun) == 0) {
                //printf("nykyinen: %s edellinen: %s\n",nykyinen->duunari->etunimi, edellinen->duunari->etunimi );
                if (nykyinen->seur != NULL) {
                    edellinen->seur=nykyinen->seur;
                }
                else edellinen->seur=NULL;
                //printf("edellinen muutoksen jälkeen: %s\n", edellinen->seur->duunari->etunimi );
                nykyinen->seur=NULL;
                vapautaSolmunVaraamaMuisti(nykyinen);
                return 1;
        } else {
            edellinen = nykyinen;
            nykyinen = nykyinen->seur;
        }
    }
    return 0;


}
