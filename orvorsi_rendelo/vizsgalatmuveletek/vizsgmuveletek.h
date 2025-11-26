#ifndef VIZSGMUVELETEK_H
#define VIZSGMUVELETEK_H

Vizsgalat *vizsgalat_keres_id(Vizsgalat *eleje, int id);
void uj_vizsgalat(Vizsgalat **eleje, Haziallat *allatok);
void vizsgalat_modosit(Vizsgalat *eleje);
void vizsgalat_torol(Vizsgalat **eleje);

#endif