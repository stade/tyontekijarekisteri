#include <stdio.h>
#include <stdlib.h>




tyontekija* teeDuunari(int koko) {
    struct tyontekija *duunari;
    duunari = malloc(sizeof(tyontekija));

}
void pointDestruct(tyontekija *point)
{
  free(point);
}
