#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>

#include "menu/allatok/allatok.h"
#include "menu/kereses/kereses.h"
#include "menu/tulajok/tulajok.h"
#include "menu/vizsgalatok/vizsgalatok.h"
#include "menu/menuvalaszto/menuvalaszto.h"
#include "fajlkezeles/fajlkezeles.h"
#include "debugmalloc.h"

//Fájlnevek
const char *tulajf = "adatok/tulajok.txt";
const char *allatf = "adatok/allatok.txt";
const char *vizsgalatf = "adatok/vizsgalatok.txt";

//Fájlok létrehozása ha nem léteznek
void fajl_inic(){
    FILE *f;

    f = fopen(tulajf, "r");
    if(!f){
        f = fopen(tulajf, "w");
        if(f){
            fclose(f);
            printf("Fajl letrehozva: %s\n", tulajf);
        }
    } else{
        fclose(f);
    }

    f = fopen(allatf, "r");
    if(!f){
        f = fopen(allatf, "w");
        if(f){
            fclose(f);
            printf("Fajl letrehozva: %s\n", allatf);
        }
    } else{
        fclose(f);
    }

    f = fopen(vizsgalatf, "r");
    if(!f){
        f = fopen(vizsgalatf, "w");
        if(f){
            fclose(f);
            printf("Fajl letrehozva: %s\n", vizsgalatf);
        }
    } else{
        fclose(f);
    }
}

//Adatok mentése
void adat_ment(Tulajdonos *tulajdonosok, Haziallat *allatok, Vizsgalat *vizsgalatok){
    printf("\nAdatok mentese...\n");
    tulaj_mentes(tulajf, tulajdonosok);
    allat_mentes(allatf, allatok);
    vizsgalat_mentes(vizsgalatf, vizsgalatok);
    printf("Adatok sikeresen mentve!\n");
}

//Memória felszabadítása
void felszabaditas(Tulajdonos **tulajdonosok, Haziallat **allatok, Vizsgalat **vizsgalatok){
    while(*vizsgalatok){
        Vizsgalat *temp = *vizsgalatok;
        *vizsgalatok = (*vizsgalatok)->kov;
        free(temp);
    }

    while(*allatok){
        Haziallat *temp = *allatok;
        *allatok = (*allatok)->kov;
        free(temp->vizsgalatok);
        free(temp);
    }

    while(*tulajdonosok){
        Tulajdonos *temp = *tulajdonosok;
        *tulajdonosok = (*tulajdonosok)->kov;
        free(temp->allatok);
        free(temp);
    }
}

static Tulajdonos **tulajok_ptr = NULL;
static Haziallat **allatok_ptr = NULL;
static Vizsgalat **vizsgalatok_ptr = NULL;

void ctrlc_kezeles(int signum){
    konzol_torol();
    adat_ment(*tulajok_ptr, *allatok_ptr, *vizsgalatok_ptr);
    felszabaditas(tulajok_ptr, allatok_ptr, vizsgalatok_ptr);

    exit(0);
}

//Főmenü
void fomenu(Tulajdonos **tulajdonosok, Haziallat **allatok, Vizsgalat **vizsgalatok){
    char *menupontok[] = {
        "Tulajdonosok kezelese",
        "Allatok kezelese",
        "Vizsgalatok kezelese",
        "Kereses es listazas",
        "Kilepes"
    };
    int valasztas;

    while(true){
        valasztas = menu_valasztas("Fomenu", menupontok, 5);

        switch (valasztas){
            case 1:
                tulaj_kezeles(tulajdonosok, allatok);
                break;
            case 2:
                allat_kezeles(tulajdonosok, allatok);
                break;
            case 3:
                vizsgalat_kezeles(allatok, vizsgalatok);
                break;
            case 4:
                kereses_listazas(*tulajdonosok, *allatok);
                break;
            case 5:
                return;
        }
    }
}

int main(){
    Tulajdonos *tulajdonosok = NULL;
    Haziallat *allatok = NULL;
    Vizsgalat *vizsgalatok = NULL;

    tulajok_ptr = &tulajdonosok;
    allatok_ptr = &allatok;
    vizsgalatok_ptr = &vizsgalatok;
    signal(SIGINT, ctrlc_kezeles);

    fejlec();
    fajl_inic();

    //Adatok betöltése
    printf("Adatok betoltese...\n");
    tulajdonosok = tulaj_betolt(tulajf);
    allatok = allat_betolt(allatf, tulajdonosok);
    vizsgalatok = vizsgalat_betolt(vizsgalatf, allatok);
    printf("Adatok betoltve!");

    printf("\nNyomj egy ENTER-t a folytatashoz...");
    getchar();

    fomenu(&tulajdonosok, &allatok, &vizsgalatok);

    konzol_torol();
    adat_ment(tulajdonosok, allatok, vizsgalatok);
    felszabaditas(&tulajdonosok, &allatok, &vizsgalatok);
}