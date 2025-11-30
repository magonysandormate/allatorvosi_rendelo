#ifndef TULAJMUVELETEK_H
#define TULAJMUVELETEK_H

#include "../fajlkezeles/fajlkezeles.h"

void uj_tulaj(Tulajdonos **eleje);
void tulaj_keres(Tulajdonos *eleje);
void tulaj_modosit(Tulajdonos *eleje);
void tulaj_torol(Tulajdonos **eleje, Haziallat **allatok, Vizsgalat **vizsgalatok);
Tulajdonos *tulaj_keres_id(Tulajdonos *eleje, int id);
void tulaj_allatai(Haziallat *allatok);

#endif