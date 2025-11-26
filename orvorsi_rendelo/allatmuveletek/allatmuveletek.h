#ifndef ALLATMUVELETEK_H
#define ALLATMUVELETEK_H

#include "../fajlkezeles/fajlkezeles.h"

Haziallat *allat_keres_id(Haziallat *eleje, int id);
void uj_allat(Haziallat **eleje, Tulajdonos *tulajok);
void allat_modosit(Haziallat *eleje, Tulajdonos *tulajok);
void allat_torol(Haziallat **eleje);
void allat_keres(Haziallat *eleje);
void regi_oltas(Haziallat *eleje);

#endif