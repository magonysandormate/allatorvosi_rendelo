#ifndef TULAJMUVELETEK_H
#define TULAJMUVELETEK_H

void uj_tulaj(Tulajdonos **eleje);
void tulaj_keres(Tulajdonos *eleje);
void tulaj_modosit(Tulajdonos *eleje);
void tulaj_torol(Tulajdonos **eleje, Haziallat **allatok);
Tulajdonos *tulaj_keres_id(Tulajdonos *eleje, int id);

#endif