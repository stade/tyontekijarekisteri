/* 
 * File:   testimain.c
 * Author: Aleksi Aalto, Jarkko Nyman, Tatu Tahvanainen
 *
 * Created on 5. lokakuuta 2010, 17:57
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */

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

int main(void) {

    lista* l;
    solmu* s;
    int i;
    struct tyontekija* t;
    t=malloc(sizeof(struct tyontekija));
    struct tyontekija* k;
    struct tyontekija* y;
    k=malloc(sizeof(struct tyontekija));
    char taulu[20]="matti";
    char tauluk[30]="kemppainen";
    strcpy(t->etunimi, taulu);
    strcpy(t->sukunimi, tauluk);
    t->aloitusvuosi = 2008;
    t->palkka = 1000;

    char taulua[20]="tissi";
    char taulub[30]="poski";
    strcpy(k->etunimi, taulua);
    strcpy(k->sukunimi, taulub);
    k->aloitusvuosi = 2009;
    k->palkka = 1050;

    y=malloc(sizeof(struct tyontekija));
    char taulug[20]="jeesus";
    char tauluh[30]="poski";
    strcpy(y->etunimi, taulug);
    strcpy(y->sukunimi, tauluh);
    y->aloitusvuosi = 2009;
    y->palkka = 1050;
    
     if ((l = luoLista()) == NULL) {
         
         printf("Ei näin\n");
         return (EXIT_FAILURE);
         
     }
     printf("näin\n");
     
     /*if ((s = luoSolmu(t)) == NULL) {
         
         printf("Ei näin2\n");
         return (EXIT_FAILURE);
         
         
     }*/
     printf("näin2\n");

     if ((i = lisaaListaanLoppuun(l,t)) == 0) {

         printf("Ei näin3 \n");





     }

     printf("1. %d\n" , i);

     if ((i = lisaaListaanLoppuun(l,k)) == 0) {

         printf("Ei näin4 \n");





     }

     printf("2. %d\n" , i);

     if ((i = lisaaListaanLoppuun(l,y)) == 0) {
         printf("fail");
     }
     printf("kolmas työntekijä:  %d\n", i);

     struct tyontekija* testityontekija = malloc(sizeof(struct tyontekija));
     printf("ennen etsintää\n");
     testityontekija = etsiListasta(l, "matti", "kemppainen");
     printf("etsinnän jälkeen\n");
     if (testityontekija == NULL)
         printf("VITTUSAATANA\n");
     printf("NIMI: %s SUKUNIMI: %s\n", testityontekija->etunimi, testityontekija->sukunimi);

     if  (poistaListasta(l, "jeesus", "poski") == 0) {

        printf("poisto kusi");


     }
     if ((testityontekija = etsiListasta(l, "jeesus", "poski")) == 0) {

         printf("Poisto onnistui\n");

     }



     free(t);
     free(k);
     free(l);


     
     






    return (EXIT_SUCCESS);
}



