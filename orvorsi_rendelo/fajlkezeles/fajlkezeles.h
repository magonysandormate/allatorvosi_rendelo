#ifndef FAJLKEZELES_H
#define FAJLKEZELES_H

typedef struct Tulajdonos{
    int id;
    char nev[50];
    char tel[20];
    char email[50];

    struct Haziallat **allatok;
    int allat_db;

    struct Tulajdonos *kov;
} Tulajdonos;

typedef struct Haziallat{
    int id;
    char nev[50];
    char faj[30];
    char szul[11];
    char oltas[11];
    Tulajdonos *tulaj;

    struct Vizsgalat **vizsgalatok;
    int vizsgalat_db;

    struct Haziallat *kov;
} Haziallat;

typedef struct Vizsgalat{
    int id;
    char datum[11];
    char megjegyzes[150];
    Haziallat *allat;
    struct Vizsgalat *kov;
} Vizsgalat;

bool email_valid(const char *email);
bool tel_valid(const char *tel);
bool datum_valid(const char *datum);

int kov_id_tulaj(Tulajdonos *eleje);
int kov_id_allat(Haziallat *eleje);
int kov_id_vizsgalat(Vizsgalat *eleje);

Tulajdonos *tulaj_betolt(const char *fajlnev);
Haziallat *allat_betolt(const char *fajlnev, Tulajdonos *tulajok);
Vizsgalat *vizsgalat_betolt(const char *fajlnev, Haziallat *allatok);
void tulaj_mentes(const char *fajlnev, Tulajdonos *eleje);
void allat_mentes(const char *fajlnev, Haziallat *eleje);
void vizsgalat_mentes(const char *fajlnev, Vizsgalat *eleje);

#endif