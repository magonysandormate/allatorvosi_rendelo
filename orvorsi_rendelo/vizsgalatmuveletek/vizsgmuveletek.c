#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vizsgmuveletek.h"
#include "../fajlkezeles/fajlkezeles.h"
#include "../allatmuveletek/allatmuveletek.h"

//Vizsgálat keresése Id alapján
Vizsgalat *vizsgalat_keres_id(Vizsgalat *eleje, int id){
    while(eleje){
        if(eleje->id == id)
            return eleje;
        eleje = eleje->kov;
    }
    return NULL;
}

//Új vizsgálat felvétele
void uj_vizsgalat(Vizsgalat **eleje, Haziallat *allatok){
    Vizsgalat *uj = (Vizsgalat*)malloc(sizeof(Vizsgalat));
    uj->kov = NULL;
    uj->allat = NULL;

    printf("Uj vizsgalat felvetele\n\n");

    do{
        printf("Datum (EEEE-HH-NN): ");
        fgets(uj->datum, sizeof(uj->datum), stdin);
        uj->datum[strcspn(uj->datum, "\n")] = 0;
        if(!datum_valid(uj->datum)){
            printf("Hibas datum formatum!\n");
        }
    } while(!datum_valid(uj->datum));

    printf("Megjegyzes: ");
    fgets(uj->megjegyzes, sizeof(uj->megjegyzes), stdin);
    uj->megjegyzes[strcspn(uj->megjegyzes, "\n")] = 0;

    int allat_id;
    char buffer[32];
    printf("Haziallat Id-ja: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &allat_id);

    Haziallat *h = allat_keres_id(allatok, allat_id);
    if(!h){
        printf("Nem talalhato haziallat ezzel az Id-val.\n");
        free(uj);
        return;
    }

    uj->allat = h;
    h->vizsgalat_db++;
    h->vizsgalatok = (Vizsgalat**)realloc(h->vizsgalatok, h->vizsgalat_db * sizeof(Vizsgalat*));
    h->vizsgalatok[h->vizsgalat_db - 1] = uj;

    uj->id = kov_id_vizsgalat(*eleje);

    if(!*eleje){
        *eleje = uj;
    } else{
        Vizsgalat *temp = *eleje;
        while(temp->kov)
            temp = temp->kov;
        temp->kov = uj;
    }

    printf("\nSikeresen felvetted a vizsgalatot (Id: %d)!\n", uj->id);
}

//Vizsgálat módosítása
void vizsgalat_modosit(Vizsgalat *eleje){
    printf("Vizsgalat modositasa\n\n");
    char datum[50];
    while(true){
        printf("Modositando vizsgalat datuma (EEEE-HH-NN): ");
        fgets(datum, sizeof(datum), stdin);
        datum[strcspn(datum, "\n")] = 0;

        if(datum_valid(datum))
            break;

        printf("Ervenytelen formatum! Pelda: 2025-11-10\n");
    }

    Vizsgalat *talalatok[100];
    int talalat_db = 0;

    Vizsgalat *temp = eleje;
    while(temp && talalat_db < 100){
        if(strstr(temp->datum, datum))
            talalatok[talalat_db++] = temp;
        temp = temp->kov;
    }

    if(talalat_db == 0){
        printf("Nem talalhato vizsgalat ezen a napon.\n");
        return;
    }

    Vizsgalat *v = NULL;
    if(talalat_db > 1){
        printf("\nTalalatok:\n");
        for(int i = 0; i < talalat_db; i++)
           printf("%d. [Id: %d] %s - %s\n", i+1, talalatok[i]->id, talalatok[i]->datum, talalatok[i]->megjegyzes);
        
        int valasztas;
        char buffer[32];
        do{
            printf("\nMelyiket szeretned modositani (1-%d, 0=MEGSE)? ", talalat_db);
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &valasztas);
            if(valasztas == 0){
                printf("Torles megszakitva.\n");
                return;
            }
            if(valasztas < 1 || valasztas > talalat_db)
                printf("Ervenytelen valasztas!\n");
        }while(valasztas < 1 || valasztas > talalat_db);

        v = talalatok[valasztas - 1];
    } else{
        v = talalatok[0];
    }

    printf("Jelenlegi adatok\n\n");
    printf("1. Datum: %s\n", v->datum);
    printf("2. Megjegyzes: %s\n", v->megjegyzes);

    int valasztas;
    char buffer[32];
    do{
        printf("\nMelyik adatot szeretned modositani (1-2)? ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &valasztas);

        if(valasztas < 1 || valasztas > 2){
            printf("Ervenytelen valasztas!\n");
            continue;
        }

        getchar();
        switch(valasztas){
            case 1:
                do{
                    printf("Uj datum (EEEE-HH-NN): ");
                    fgets(v->datum, sizeof(v->datum), stdin);
                    v->datum[strcspn(v->datum, "\n")] = 0;
                    if(!datum_valid(v->datum))
                        printf("Hibas formatum!\n");
                } while(!datum_valid(v->datum));
                break;
            case 2:
                printf("Uj megjegyzes: ");
                fgets(v->megjegyzes, sizeof(v->megjegyzes), stdin);
                v->megjegyzes[strcspn(v->megjegyzes, "\n")] = 0;
                break;
        }

        printf("\nSikeres modositas!\n");
        break;
    } while(true);
}

//Vizsgálat törlése
void vizsgalat_torol(Vizsgalat **eleje){
    printf("Vizsgalat torlese\n\n");

    char datum[50];
    while(true){
        printf("Torlendo vizsgalat datuma (EEEE-HH-NN): ");
        fgets(datum, sizeof(datum), stdin);
        datum[strcspn(datum, "\n")] = 0;

        if(datum_valid(datum))
            break;

        printf("Ervenytelen formatum! Pelda: 2025-11-10\n");
    }

    Vizsgalat *talalatok[100];
    int talalat_db = 0;

    Vizsgalat *temp = *eleje;
    while(temp && talalat_db < 100){
        if(strstr(temp->datum, datum))
            talalatok[talalat_db++] = temp;
        temp = temp->kov;
    }

    if(talalat_db == 0){
        printf("Nem talalhato vizsgalat ezen a napon.\n");
        return;
    }

    Vizsgalat *v = NULL;
    if(talalat_db > 1){
        printf("\nTalalatok:\n");
        for(int i = 0; i < talalat_db; i++)
           printf("%d. [Id: %d] %s - %s - Allat: %s\n", i+1, talalatok[i]->id, talalatok[i]->datum, talalatok[i]->megjegyzes, talalatok[i]->allat ? talalatok[i]->allat->nev : "Ismeretlen");
        
        int valasztas;
        char buffer[32];
        do{
            printf("\nMelyiket szeretned torolni (1-%d, 0=MEGSE)? ", talalat_db);
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &valasztas);
            if(valasztas == 0){
                printf("Torles megszakitva.\n");
                return;
            }
            if(valasztas < 1 || valasztas > talalat_db)
                printf("Ervenytelen valasztas!\n");
        }while(valasztas < 1 || valasztas > talalat_db);

        v = talalatok[valasztas - 1];
    } else{
        v = talalatok[0];
    }

    printf("Torlendo vizsgalat:\n\n");
    printf("Datum: %s\n", v->datum);
    printf("Megjegyzes: %s\n", v->megjegyzes);
    if(v->allat)
        printf("Allat: %s (Id: %d)\n", v->allat->nev, v->allat->id);

    char megerosit[10];
    printf("\nBiztosan torolni szeretned? (i/n)");
    fgets(megerosit, sizeof(megerosit), stdin);

    if(megerosit[0] == 'i' || megerosit[0] == 'I'){
        if(v->allat){
            Haziallat *h = v->allat;
            for(int i = 0; i < h->vizsgalat_db; i++){
                if(h->vizsgalatok[i] == v){
                    for(int j = i; j < h->vizsgalat_db - 1; j++)
                        h->vizsgalatok[j] = h->vizsgalatok[j + 1];
                    h->vizsgalat_db--;
                    h->vizsgalatok = (Vizsgalat**)realloc(h->vizsgalatok, h->vizsgalat_db * sizeof(Vizsgalat*));
                    break;
                }
            }
        }

        Vizsgalat *elozo = NULL, *aktualis = *eleje;

        while(aktualis && aktualis != v){
            elozo = aktualis;
            aktualis = aktualis->kov;
        }

        if(aktualis){
            if(elozo){
                elozo->kov = aktualis->kov;
            } else{
                *eleje = aktualis->kov;
            }
            free(aktualis);
        }
        printf("Vizsgalat torolve.\n");
    } else{
        printf("Torles megszakitva.\n");
    }
}