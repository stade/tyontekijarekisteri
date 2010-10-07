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
    struct tyontekija* k;
    struct tyontekija* y;

    //Luodaan työntekijät testaamista varten.
    t=malloc(sizeof(struct tyontekija));
    k=malloc(sizeof(struct tyontekija));
    y=malloc(sizeof(struct tyontekija));


    //Annetaan työntekijöille tiedot.
    char taula[20]="Matti";
    char taulub[30]="Kemppainen";
    strcpy(t->etunimi, taula);
    strcpy(t->sukunimi, taulub);
    t->aloitusvuosi = 2008;
    t->palkka = 1500;

    char tauluc[20]="Mikko";
    char taulud[30]="Alatalo";
    strcpy(k->etunimi, tauluc);
    strcpy(k->sukunimi, taulud);
    k->aloitusvuosi = 2009;
    k->palkka = 2000;

    
    char taulue[20]="Paavo";
    char tauluf[30]="Väyrynen";
    strcpy(y->etunimi, taulue);
    strcpy(y->sukunimi, tauluf);
    y->aloitusvuosi = 2010;
    y->palkka = 3000;


    // Luodaan lista. Ohjelman suoritus loppuu, jos listan luominen ei
    // onnistunut.
     if ((l = luoLista()) == NULL) {
         
         printf("Listan luominen epäonnistui.\n");
         return (EXIT_FAILURE);
         
     }
     else {
          printf("Listan luonti onnistui\n");
     }
    
     
     /*if ((s = luoSolmu(t)) == NULL) {
         
         printf("Ei näin2\n");
         return (EXIT_FAILURE);
         
         
     }*/
    
     // Lisätään listaan työtekijät. Ilmoitetaan jos ei onnistunu.

     if ((i = lisaaListaanLoppuun(l,t)) == 0) {

         printf("1. listaan lisääminen epäonnistui\n");
     }

     //printf("1. %d\n" , i);

     if ((i = lisaaListaanLoppuun(l,k)) == 0) {

         printf("2. listaan lisääminen epäonnistui\n");
     }
     //printf("2. %d\n" , i);

     if ((i = lisaaListaanLoppuun(l,y)) == 0) {
         printf("3. listaan lisääminen epäonnistui");
     }


     //printf("kolmas työntekijä:  %d\n", i);

     // Luodaan työntekijä etsinnän testaamista varten.
     struct tyontekija* testityontekija = malloc(sizeof(struct tyontekija));
     //printf("ennen etsintää\n");
     testityontekija = etsiListasta(l, "Matti", "Kemppainen");
     //printf("etsinnän jälkeen\n");
     
     if (testityontekija == NULL)  {
         printf("etsintä epäonnistui\n");
     }

     //Tulostetaan etsityn työntekijän tiedot.
     printf("NIMI: %s SUKUNIMI: %s\n", testityontekija->etunimi, testityontekija->sukunimi);


     //Poistetaan listasta 1. työntekijä.
     if  (poistaListasta(l, "Paavo", "Väyrynen") == 0) {

        printf("1. käyttäjän poisto ei onnistunut\n");


     }

     if ((testityontekija = etsiListasta(l, "Paavo", "Väyrynen")) == 0) {

          printf("1. poisto onnistui\n");

     }
       //Poistetaan listasta 2. työntekijä.
     if  (poistaListasta(l, "Matti ", "Kemppainen") == 0) {

        printf("2. käyttäjän poisto ei onnistunut\n");


     }

     if ((testityontekija = etsiListasta(l, "Matti", "Kemppainen")) == 0) {

          printf("2. poisto onnistui\n");

     }
     /*
       //Poistetaan listasta 3. työntekijä.
     if  (poistaListasta(l, "Mikko", "Alatalo") == 0) {

        printf("3. käyttäjän poisto ei onnistunut\n");


     }

     if ((testityontekija = etsiListasta(l, "Mikko", "Alatalo")) == 0) {

          printf("3. poisto onnistui\n");

     }
     */


     // Vapautetaan käytetty muisti.
     free(testityontekija);
     free(l);

    return (EXIT_SUCCESS);
}



