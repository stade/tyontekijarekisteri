#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tyontekija {
     char etunimi[20];
     char sukunimi[30];
     int palkka;
     int aloitusvuosi;
     

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
     if (p == NULL) { //Kokeillaan onko tila saatu varattua mallocilla.

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
//TODO työntekijöiden nimien vertaus
int lisaaListaanLoppuun(lista *listap, struct tyontekija *duunaaja) { 
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
    struct solmu* seuraava = l->paa;
    while (seuraava != NULL) {
        tempetu = seuraava->duunari->etunimi;
        tempsuku = seuraava->duunari->sukunimi;
        if (strcmp(tempetu, etun) == 0 &&
            strcmp(tempsuku, sukun) == 0) {

            printf("Etsitty on löytynyt\n");

            return seuraava->duunari;
        } else seuraava = seuraava->seur;
    }
    return NULL;
}

void vapautaSolmunVaraamaMuisti(solmu *s) { 

    free(s->duunari);
    free(s);
    s=NULL;
}



int poistaListasta(lista *l, char* etun, char* sukun) { //return 0 if fail
    if (l == NULL) {
        return 0;
    }
    if (l->paa == NULL) {
        return 0;
    }
    solmu* nykyinen = l->paa;
    solmu* edellinen = l->paa;
    if (strcmp(nykyinen->duunari->etunimi, etun) == 0 && //jos poistettava oli ensimmäinen solmu
            strcmp(nykyinen->duunari->sukunimi, sukun) == 0) {
        l->paa = nykyinen->seur;
        vapautaSolmunVaraamaMuisti(nykyinen);
        return 1;
    }
    else nykyinen = nykyinen->seur;
    while (nykyinen != NULL) {

        if (strcmp(nykyinen->duunari->etunimi, etun) == 0 &&
            strcmp(nykyinen->duunari->sukunimi, sukun) == 0) {
                if (nykyinen->seur != NULL) {
                    edellinen->seur=nykyinen->seur;
                }
                else edellinen->seur=NULL;
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
