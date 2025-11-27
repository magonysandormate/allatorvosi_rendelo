#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fajlkezeles.h"
#include "../debugmalloc.h"

//-------Segédfüggvények-------

//Email validálás
bool email_valid(const char *email){
    int kukac = 0, pont = 0;
    for (int i = 0; email[i] != 0; i++){
        if (email[i] == '@')
            kukac++;
        if(email[i] == '.')
            pont++;
    }
    return (kukac == 1 && pont >= 1);
}

//Telefonszám validálás
bool tel_valid(const char *tel){
    int len = strlen(tel);
    if(tel[0] == '+' && len > 11 && len < 16)
        return true;
    if(tel[0] == '0' && len > 9 && len < 16)
        return true;
    return false;
}

//Dátum validálás
bool datum_valid(const char *datum){
    if(strlen(datum) != 10)
        return false;
    if(datum[4] != '-' || datum[7] != '-')
        return false;
    return true;
}

//Következő Id-k generálása
int kov_id_tulaj(Tulajdonos *eleje){
    int max_id = 0;
    while (eleje){
        if(eleje->id > max_id)
            max_id = eleje->id;
        eleje = eleje->kov;
    }
    return max_id + 1;
}

int kov_id_allat(Haziallat *eleje){
    int max_id = 0;
    while (eleje){
        if(eleje->id > max_id)
            max_id = eleje->id;
        eleje = eleje->kov;
    }
    return max_id + 1;
}

int kov_id_vizsgalat(Vizsgalat *eleje){
    int max_id = 0;
    while (eleje){
        if(eleje->id > max_id)
            max_id = eleje->id;
        eleje = eleje->kov;
    }
    return max_id + 1;
}

//-----------Fájlkezelés----------------

//Tulajdonosok betöltése
Tulajdonos *tulaj_betolt(const char *fajlnev){
    FILE *f = fopen(fajlnev, "r");
    if(!f){
        printf("A \"%s\" fajl nem talalhato, ures fajl letrehozva", fajlnev);
        return NULL;
    }

    Tulajdonos *eleje = NULL, *vege = NULL;
    char sor[300];

    while(fgets(sor, sizeof(sor), f)){
        Tulajdonos *uj = (Tulajdonos*)malloc(sizeof(Tulajdonos));
        uj->allatok = NULL;
        uj->allat_db = 0;
        uj->kov = NULL;

        char *elem = strtok(sor, ";");
        uj->id = atoi(elem);

        elem = strtok(NULL, ";");
        strcpy(uj->nev, elem);

        elem = strtok(NULL, ";");
        strcpy(uj->tel, elem);

        elem = strtok(NULL, ";\n");
        strcpy(uj->email, elem);

        if(!eleje){
            eleje = uj;
            vege = uj;
        } else{
            vege->kov = uj;
            vege = uj;
        }
    }
    
    fclose(f);
    return eleje;
}

//Háziállatok betöltése
Haziallat *allat_betolt(const char *fajlnev, Tulajdonos *tulajok){
    FILE *f = fopen(fajlnev, "r");
    if(!f){
        printf("A \"%s\" fajl nem talalhato, ures fajl letrehozva", fajlnev);
        return NULL;
    }

    Haziallat *eleje = NULL, *vege = NULL;
    char sor[300];

    while(fgets(sor, sizeof(sor), f)){
        Haziallat *uj = (Haziallat*)malloc(sizeof(Haziallat));
        uj->vizsgalatok = NULL;
        uj->vizsgalat_db = 0;
        uj->kov = NULL;
        uj->tulaj = NULL;

        char *elem = strtok(sor, ";");
        uj->id = atoi(elem);

        elem = strtok(NULL, ";");
        strcpy(uj->nev, elem);

        elem = strtok(NULL, ";");
        strcpy(uj->faj, elem);

        elem = strtok(NULL, ";");
        strcpy(uj->szul, elem);

        elem = strtok(NULL, ";");
        strcpy(uj->oltas, elem);

        elem = strtok(NULL, ";\n");
        int tulaj_id = atoi(elem);

        //Tulajdonos hozzárendelése
        Tulajdonos *t = tulajok;
        while(t){
            if(t->id == tulaj_id){
                uj->tulaj = t;
                t->allat_db++;
                t->allatok = (Haziallat**)realloc(t->allatok, t->allat_db * sizeof(Haziallat*));
                t->allatok[t->allat_db - 1] = uj;
                break;
            }
            t = t->kov;
        }
        
        if(!eleje){
            eleje = uj;
            vege = uj;
        } else{
            vege->kov = uj;
            vege = uj;
        }
    }

    fclose(f);
    return eleje;
}

//Vizsgálatok betöltése
Vizsgalat *vizsgalat_betolt(const char *fajlnev, Haziallat *allatok){
    FILE *f = fopen(fajlnev, "r");
    if(!f){
        printf("A \"%s\" fajl nem talalhato, ures fajl letrehozva", fajlnev);
        return NULL;
    }

    Vizsgalat *eleje = NULL, *vege = NULL;
    char sor[300];

    while(fgets(sor, sizeof(sor), f)){
        Vizsgalat *uj = (Vizsgalat*)malloc(sizeof(Vizsgalat));
        uj->kov = NULL;
        uj->allat = NULL;

        char *elem = strtok(sor, ";");
        uj->id = atoi(elem);

        elem = strtok(NULL, ";");
        strcpy(uj->datum, elem);

        elem = strtok(NULL, ";");
        strcpy(uj->megjegyzes, elem);

        elem = strtok(NULL, ";\n");
        int allat_id = atoi(elem);

        //Tulajdonos hozzárendelése
        Haziallat *a = allatok;
        while(a){
            if(a->id == allat_id){
                uj->allat = a;
                a->vizsgalat_db++;
                a->vizsgalatok = (Vizsgalat**)realloc(a->vizsgalatok, a->vizsgalat_db * sizeof(Vizsgalat*));
                a->vizsgalatok[a->vizsgalat_db - 1] = uj;
                break;
            }
            a = a->kov;
        }
        
        if(!eleje){
            eleje = uj;
            vege = uj;
        } else{
            vege->kov = uj;
            vege = uj;
        }
    }

    fclose(f);
    return eleje;
}

//Tulajdonosok mentése
void tulaj_mentes(const char *fajlnev, Tulajdonos *eleje){
    FILE *f = fopen(fajlnev, "w");
    if(!f){
        printf("Nem sikerult megnyitni a fajlt: %s", fajlnev);
        return;
    }
    
    while(eleje){
        fprintf(f, "%d;%s;%s;%s\n", eleje->id, eleje->nev, eleje->tel, eleje->email);
        eleje = eleje->kov;
    }
    
    fclose(f);
}

//Háziállatok mentése
void allat_mentes(const char *fajlnev, Haziallat *eleje){
    FILE *f = fopen(fajlnev, "w");
    if(!f){
        printf("Nem sikerult megnyitni a fajlt: %s", fajlnev);
        return;
    }
    
    while(eleje){
        fprintf(f, "%d;%s;%s;%s;%s;%d\n", eleje->id, eleje->nev, eleje->faj, eleje->szul, eleje->oltas, eleje->tulaj ? eleje->tulaj->id : 0);
        eleje = eleje->kov;
    }
    
    fclose(f);
}

//Vizsgálatok mentése
void vizsgalat_mentes(const char *fajlnev, Vizsgalat *eleje){
    FILE *f = fopen(fajlnev, "w");
    if(!f){
        printf("Nem sikerult megnyitni a fajlt: %s", fajlnev);
        return;
    }
    
    while(eleje){
        fprintf(f, "%d;%s;%s;%d\n", eleje->id, eleje->datum, eleje->megjegyzes, eleje->allat ? eleje->allat->id : 0);
        eleje = eleje->kov;
    }
    
    fclose(f);
}