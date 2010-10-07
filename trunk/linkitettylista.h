/*
 * linkitettylista.h
 */


/*
 * tyontekija-tietueen sisäinen rakenne
 * 
 */
typedef struct tyontekija {
    char etunimi[20];
    char sukunimi[30];
    int palkka;
    int aloitusvuosi;


} tyontekija;


/*
 * Lista-tietue, joka pitää kirjaa linkitettyinä listoina toimivista solmuista.
 * Toiminnaltaan siis "ankkuri" jolla päästään kiinni linkitettyjen solmujen
 * ensimmäiseen solmuun.
 */
typedef struct lista {
    struct solmu *paa;

} lista;


/*
 * Solmu-tietue sisältää pointterin oleellisimpaan tietueeseen eli duunari-
 * tietueeseen, sekä pointterit edelliseen ja seuraavaan solmu-tietueeseen.
 */
typedef struct solmu {
    struct tyontekija *duunari;
    struct solmu *seur;
    struct solmu *edell;
} solmu;


/*
 *luoLista-funktio luo uuden lista-tietueen ja varaa sille tilan mallocilla.
 * Palauttaa luodun listan onnistuessaan ja NULL jos epäonnistuu.
 *
 */
lista* luoLista();


/*
 *luoSolmu-funktio luo uuden solmu-tietueen ja varaa sille tilan mallocilla.
 * Palauttaa luodun solmun onnistuessaan ja NULL jos epäonnistuu.
 *
 * Asettaa muuttujalle duunari parametrina annettun tyontekijanpointterin, sekä
 * muuttujille seur ja edell arvon NULL.
 *
 */
solmu* luoSolmu(struct tyontekija *t);


/*
 * Parametrina saaduun listapointterin perusteella lisätään jo luotuun lista-
 * tietueeseen uuden solmu-tietueen. Solmu-tietue tehdään luoSolmu-funktiolla
 * joka saa lisaaListanLoppuun-funktion kutsussa olevan tyontekija *duunaaja- 
 * parametrin omaksi todelliseksi parametrikseen tyontekija *t
 * 
 * Jos lista on tyhjä, niin luotu solmu lisätään listan ensimmäiseksi tietueeksi.
 * Muuten tutkitaan linkitettyjä solmuja niin pitkään, kunnes solmun seur-arvo
 * on Null
 * 
 */
int lisaaListaanLoppuun(lista *listap, struct tyontekija *duunaaja);


/*
 * Funktio tutkii parametrina annetun listan kaikki solmut läpi. Lopettaa kesken
 * ja palauttaa löydetyn työntekijän* jos se löytyy. Listan ollessa tyhjä tai
 * annettua ei löydettäessä palautetaan NULL. Jos poistettavakasi haluttava tyontekija
 * löytyy, niin
 *
 */
tyontekija* etsiListasta(lista *l, char* etun, char* sukun);


/*
 * poistaListasta-funktio tutkii ensiksi onko parametrina annettuna lista tyhjä
 * vai ei. Jos ei tyhjä, niin käydään läpi listan sisältämät solmut joista tutkitaan
 * muuttujat etunimi ja sukunimi ja verrataan niitä annettuihin parametreihin
 * etun ja sukun. Mikäli Täysin samaniminen tyontekija löytyy solmusta, poistetaan
 * solmu vaihtamalla aikaisemman ja seuraavan solmun viitaukset niin ettei
 * poistettavaan enää osoita seur- tai edell-pointteria. Tämän jälkeen kutsutaan
 * vapautaSolmunVaraamaMuisti-funktiota parametrinaan poistettavan solmun pointteri.
 * Onnistuneen poiston jäljiltä palautetaan onnistumisen merkiksi 1. Poiston epäonnistuminen
 * palauttaa 0.
 */
int poistaListasta(lista *l, char* etun, char* sukun);


/*
 * Vapauttaa parametrina saamansa solmu-tietueen tilan.
 */
void vapautaSolmunVaraamaMuisti(solmu*);