#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "allatmuveletek.h"
#include "../fajlkezeles/fajlkezeles.h"
#include "../tulajmuveletek/tulajmuveletek.h"
#include "../debugmalloc.h"

//Háziállat keresése Id alapján
Haziallat *allat_keres_id(Haziallat *eleje, int id){
    while(eleje){
        if(eleje->id == id)
            return eleje;
        eleje = eleje->kov;
    }
    return NULL;
}

//Új háziállat felvétele
void uj_allat(Haziallat **eleje, Tulajdonos *tulajok){
    konzol_torol();
    fejlec();
    
    Haziallat *uj = (Haziallat*)malloc(sizeof(Haziallat));
    uj->vizsgalatok = NULL;
    uj->vizsgalat_db = 0;
    uj->kov = NULL;
    uj->tulaj = NULL;

    printf("Uj haziallat felvetele\n\n");

    printf("Nev: ");
    fgets(uj->nev, sizeof(uj->nev), stdin);
    uj->nev[strcspn(uj->nev, "\n")] = 0;

    printf("Faj: ");
    fgets(uj->faj, sizeof(uj->faj), stdin);
    uj->faj[strcspn(uj->faj, "\n")] = 0;

    do{
        printf("Szuletesi datum (EEEE-HH-NN): ");
        fgets(uj->szul, sizeof(uj->szul), stdin);
        uj->szul[strcspn(uj->szul, "\n")] = 0;
        if(!datum_valid(uj->szul))
            printf("Hibas datum formatum!\n");
    } while(!datum_valid(uj->szul));

    do{
        printf("Utolso oltas datuma (EEEE-HH-NN): ");
        fgets(uj->oltas, sizeof(uj->oltas), stdin);
        uj->oltas[strcspn(uj->oltas, "\n")] = 0;
        if(!datum_valid(uj->oltas))
            printf("Hibas datum formatum!\n");
    } while(!datum_valid(uj->oltas));

    int tulaj_id;
    char buffer[32];
    printf("Tulajdonos Id-ja: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &tulaj_id);

    Tulajdonos *t = tulaj_keres_id(tulajok, tulaj_id);
    if(!t){
        printf("Nem talalhato tulajdonos ezzel az Id-val.\n");
        free(uj);
        return;
    }

    uj->tulaj = t;
    t->allat_db++;
    t->allatok = (Haziallat**)realloc(t->allatok, t->allat_db * sizeof(Haziallat*));
    t->allatok[t->allat_db - 1] = uj;

    uj->id = kov_id_allat(*eleje);

    if(!*eleje){
        *eleje = uj;
    } else{
        Haziallat *temp = *eleje;
        while(temp->kov)
            temp = temp->kov;
        temp->kov = uj;
    }

    printf("\nSikeresen felvetted az allatot! (Id: %d)\n", uj->id);
}

void allat_modosit(Haziallat *eleje, Tulajdonos *tulajok){
    konzol_torol();
    fejlec();
    
    printf("Allat adatainak modositasa\n\n");
    
    char nev[50];
    printf("Modositando allat neve: ");
    fgets(nev, sizeof(nev), stdin);
    nev[strcspn(nev, "\n")] = 0;

    Haziallat *talalatok[100];
    int talalat_db = 0;

    Haziallat *temp = eleje;
    while(temp && talalat_db < 100){
        if(strstr(temp->nev, nev))
            talalatok[talalat_db++] = temp;
        temp = temp->kov;
    }

    if(talalat_db == 0){
        printf("Nem talalhato haziallat ilyen neven.\n");
        return;
    }

    Haziallat *h = NULL;

    if(talalat_db > 1){
        printf("\nTalalatok:\n");
        for(int i = 0; i < talalat_db; i++)
           printf("%d. [Id: %d] %s - %s\n", i+1, talalatok[i]->id, talalatok[i]->nev, talalatok[i]->szul);
        
        int valasztas;
        char buffer[32];
        do{
            printf("\nMelyiket szeretned modositani (1-%d)? ", talalat_db);
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &valasztas);
            if(valasztas < 1 || valasztas > talalat_db)
                printf("Ervenytelen valasztas!\n");
        }while(valasztas < 1 || valasztas > talalat_db);

        h = talalatok[valasztas - 1];
    } else{
        h = talalatok[0];
        printf("Talalat: [Id: %d] %s\n", h->id, h->nev);
    }

    printf("\nJelenlegi adatok\n\n");
    printf("1. Nev: %s\n", h->nev);
    printf("2. Faj: %s\n", h->faj);
    printf("3. Szuletesi datum: %s\n", h->szul);
    printf("4. Utolso oltas datuma: %s\n", h->oltas);

    int valasztas;
    char buffer[32];
    do{
        printf("\nMelyik adatot szeretned modositani (1-4)? ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &valasztas);

        if(valasztas < 1 || valasztas > 4){
            printf("Ervenytelen valasztas!\n");
            continue;
        }

        getchar();
        switch(valasztas){
            case 1:
                printf("Uj nev: ");
                fgets(h->nev, sizeof(h->nev), stdin);
                h->nev[strcspn(h->nev, "\n")] = 0;
                break;
            case 2:
                printf("Uj faj: ");
                fgets(h->faj, sizeof(h->faj), stdin);
                h->faj[strcspn(h->faj, "\n")] = 0;
                break;
            case 3:
                do{
                    printf("Uj szuletesi datum: ");
                    fgets(h->szul, sizeof(h->szul), stdin);
                    h->szul[strcspn(h->szul, "\n")] = 0;
                    if(!datum_valid(h->szul))
                        printf("Hibas formatum!\n");
                } while(!datum_valid(h->szul));
                break;
            case 4:
                do{
                    printf("Uj utolso oltas datuma: ");
                    fgets(h->oltas, sizeof(h->oltas), stdin);
                    h->oltas[strcspn(h->oltas, "\n")] = 0;
                    if(!datum_valid(h->oltas))
                        printf("Hibas formatum!\n");
                } while(!datum_valid(h->oltas));
                break;
        }

        printf("Sikeres modositas!\n");
        break;
    } while(true);
}

//Háziállat törlése
void allat_torol(Haziallat **eleje){
    konzol_torol();
    fejlec();
    
    printf("Haziallat torlese\n\n");

    char nev[50];
    printf("Torlendo haziallat neve: ");
    fgets(nev, sizeof(nev), stdin);
    nev[strcspn(nev, "\n")] = 0;

    Haziallat *talalatok[100];
    int talalat_db = 0;

    Haziallat *temp = *eleje;
    while(temp && talalat_db < 100){
        if(strstr(temp->nev, nev))
            talalatok[talalat_db++] = temp;
        temp = temp->kov;
    }

    if(talalat_db == 0){
        printf("Nem talalhato haziallat ilyen neven.\n");
        return;
    }

    Haziallat *h = NULL;

    if(talalat_db > 1){
        printf("\nTalalatok:\n");
        for(int i = 0; i < talalat_db; i++)
           printf("%d. [Id: %d] %s - %s\n", i+1, talalatok[i]->id, talalatok[i]->nev, talalatok[i]->szul);
        
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

        h = talalatok[valasztas - 1];
    } else{
        h = talalatok[0];
    }

    printf("Allat adatai:\n\n");
    printf("Nev: %s\n", h->nev);
    printf("Szuletesi datum: %s\n", h->szul);

    char megerosit[10];
    printf("\nBiztosan torolni szeretned (i/n)? ");
    fgets(megerosit, sizeof(megerosit), stdin);

    if(megerosit[0] == 'i' || megerosit[0] == 'I'){
        //Tulajdonos állat-listájából törlés
        if(h->tulaj){
            Tulajdonos *t = h->tulaj;
            for(int i = 0; i < t->allat_db; i++){
                if(t->allatok[i]->id == h->id){
                    for(int j = i; j < t->allat_db-1; j++)
                        t->allatok[j] = t->allatok[j+1];
                    t->allat_db--;
                    t->allatok = (Haziallat**)realloc(t->allatok, t->allat_db * sizeof(Haziallat*));
                    break;
                }
            }
            
        }

        Haziallat *elozo = NULL;
        temp = *eleje;

        while(temp && temp != h){
            elozo = temp;
            temp = temp->kov;
        }

        if(!elozo)
            *eleje = h->kov;
        else
            elozo->kov = h->kov;

        free(h->vizsgalatok);
        free(h);

        printf("Allat torolve.\n");
    } else{
        printf("Torles megszakitva.\n");
    }
}

//Háziállat keresése név alapján
void allat_keres(Haziallat *eleje){
    konzol_torol();
    fejlec();
    
    printf("Haziallat keresese\n\n");

    char nev[50];
    printf("Keresett haziallat neve: ");
    fgets(nev, sizeof(nev), stdin);
    nev[strcspn(nev, "\n")] = 0;

    int talalat = 0;
    printf("Talalatok:\n\n");
    while(eleje){
        if(strstr(eleje->nev, nev)){
            printf("Id: %d\n", eleje->id);
            printf("Nev: %s\n", eleje->nev);
            printf("Faj: %s\n", eleje->faj);
            printf("Szuletesi datum: %s\n", eleje->szul);
            printf("Utolso oltas: %s\n", eleje->oltas);
            printf("Tulajdonos: %s\n", eleje->tulaj ? eleje->tulaj->nev : "Ismeretlen");
            talalat++;
            printf("\n");
        }
        eleje = eleje->kov;
    }

    if(talalat == 0)
        printf("Nem talalhato ilyen nevu allat");
}

//1 évnél régebbi oltású háziállatok listázása
void regi_oltas(Haziallat *eleje){
    konzol_torol();
    fejlec();
    
    time_t most = time(NULL);

    printf("1 evnel regebbi oltasu allatok\n\n");
    int talalat = 0;

    while(eleje){
        struct tm tm_oltas = {0};

        int ell = sscanf(eleje->oltas, "%d-%d-%d", &tm_oltas.tm_year, &tm_oltas.tm_mon, &tm_oltas.tm_mday);

        if(ell == 3){
            tm_oltas.tm_year -= 1900;
            tm_oltas.tm_mon -= 1;

            time_t oltas_ido = mktime(&tm_oltas);

            if(oltas_ido != (time_t) - 1){
                double kulonbseg = difftime(most, oltas_ido) / (60 * 60 * 24);
                int eltelt_nap = (int)kulonbseg;

                if(eltelt_nap >= 365){
                    printf("Id: %d\n", eleje->id);
                    printf("Nev: %s\n", eleje->nev);
                    printf("Faj: %s\n", eleje->faj);
                    printf("Szuletesi datum: %s\n", eleje->szul);
                    printf("Utolso oltas: %s\n", eleje->oltas);
                    printf("Tulajdonos: %s\n", eleje->tulaj ? eleje->tulaj->nev : "Ismeretlen");
                    printf("Telefonszama: %s\n", eleje->tulaj ? eleje->tulaj->tel : "Ismeretlen");
                    talalat++;
                    printf("\n");
                }
            }
        }

        eleje = eleje->kov;
    }

    if(talalat == 0)
        printf("Nincs 1 evnel regebbi oltasu haziallat.\n");
}