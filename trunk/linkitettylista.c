#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct lista{
    struct solmu *paa;

}lista;
typedef struct solmu{
    struct tyontekija *duunari;
    struct solmu *seur;
    struct solmu *edell;
}solmu;
lista* luoLista() {
     lista *p;
     p = ((lista *)malloc(sizeof(lista)));

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
     s->edell = NULL;
     return s;


}
/*void lisaaListaanLoppuun(lista *listap, struct tyontekija *duunaaja) { //TODO työntekijöiden nimien vertaus
    solmu* uusi = luoSolmu(duunaaja);
    solmu* seuraava;
    
    if (listap.paa == NULL) {
        lista.paa = uusi;
    }
    else {
        seuraava = lista.paa.seur;
        while (seuraava != NULL) {
            seuraava = seuraava.seur;
        }
        seuraava.seur = uusi;
        uusi.edell = seuraava;
    }
}
tyontekija* etsiListasta(lista l, char* etun, char* sukun) {
    if (l == NULL) {
        return NULL;
    }
    solmu seuraava = l.paa;
    while (seuraava != NULL) {

        if (strcmp(seuraava.duunari.etunimi, etun) == 0 &&
            strcmp(seuraava.duunari.sukunimi, sukun) == 0) {
            return seuraava.duunari;
        } else seuraava = seuraava.seur;
    }
    return NULL;
}
int poistaListasta(lista l, char* etun, char* sukun) { //return 0 if fail
        if (l == NULL) {
        return NULL;
    }
    solmu seuraava = l.paa;
    solmu poistettava;
    while (seuraava != NULL) {

        if (strcmp(seuraava.seur.duunari.etunimi, etun) == 0 &&
            strcmp(seuraava.seur.duunari.sukunimi, sukun) == 0) {
                poistettava = seuraava.seur;
                seuraava.seur=poistettava.seur;
                poistettava.seur=NULL;
                vapautaSolmunVaraamaMuisti(poistettava);
                return 1;
        } else seuraava = seuraava.seur;
    }
    return 0;


}
void vapautaSolmunVaraamaMuisti(solmu s) {
    free(s);
    s=NULL;
}*/