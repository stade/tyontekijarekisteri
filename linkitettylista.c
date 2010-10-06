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
    struct solmu *edell;
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
     s->edell = NULL;
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
        uusi->edell = seuraava;
        return 2;
    }
    return 0;
}

tyontekija* etsiListasta(lista *l, char* etun, char* sukun) {
    if (l == NULL) {
        return NULL;
    }
    char *tempetu, *tempsuku;

    printf("seuraavan alustus\n");
    struct solmu* seuraava = l->paa;
    while (seuraava != NULL) {
        printf("etsinnän whilessa\n");
        tempetu = seuraava->duunari->etunimi;
        tempsuku = seuraava->duunari->sukunimi;
        printf("%s\n", tempetu);
        if (strcmp(tempetu, etun) == 0 &&
            strcmp(tempsuku, sukun) == 0) {


            printf("ETSITTY HOMO ON LÖYTYNYT\n");
            return seuraava->duunari;
        } else seuraava = seuraava->seur;
    }
    return NULL;
}
int poistaListasta(lista *l, char* etun, char* sukun) { //return 0 if fail
    if (l == NULL) {
        return 0;
    }
    solmu* seuraava = l->paa;
    solmu* poistettava;
    while (seuraava != NULL) {

        if (strcmp(seuraava->seur->duunari->etunimi, etun) == 0 &&
            strcmp(seuraava->seur->duunari->sukunimi, sukun) == 0) {
                poistettava = seuraava->seur;
                seuraava->seur=poistettava->seur;
                poistettava->seur=NULL;
                //vapautaSolmunVaraamaMuisti(poistettava);
                return 1;
        } else seuraava = seuraava->seur;
    }
    return 0;


}
void vapautaSolmunVaraamaMuisti(solmu* s) {

    free(s);
    s=NULL;
}