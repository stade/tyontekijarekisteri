/*
 linkitettylista.h
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

lista* luoLista();
solmu* luoSolmu(struct tyontekija *t);
int lisaaListaanLoppuun(lista *listap, struct tyontekija *duunaaja);
tyontekija* etsiListasta(lista *l, char* etun, char* sukun);
int poistaListasta(lista *l, char* etun, char* sukun);
void vapautaSolmunVaraamaMuisti(solmu* s);