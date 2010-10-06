/* 
 * File:   testimain.c
 * Author: Aleksi Aalto, Jarkko Nyman, Tatu Tahvanainen
 *
 * Created on 5. lokakuuta 2010, 17:57
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkitettylista.h"


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

     printf("tyontetekijäkusee\n");
     struct tyontekija* testityontekija = malloc(sizeof(struct tyontekija));
     printf("ennen etsintää\n");
     testityontekija = etsiListasta(l, "matti", "kemppainen");
     printf("etsinnän jälkeen\n");
     if (testityontekija == NULL)
         printf("VITTUSAATANA\n");
     printf("NIMI: %s SUKUNIMI: %s\n", testityontekija->etunimi, testityontekija->sukunimi);

     if  (poistaListasta(l, "jeesus", "poski") == 0) {

        printf("käyttäjän poisto ei onnistunut\n");


     }

      if ((testityontekija = etsiListasta(l, "jeesus", "poski")) == 0) {

          printf("Poisto onnistui\n");

      }

     free(t);
     free(k);
     free(l);

    return (EXIT_SUCCESS);
}



