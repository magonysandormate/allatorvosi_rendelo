#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tulajmuveletek.h"
#include "../fajlkezeles/fajlkezeles.h"
#include "../debugmalloc.h"

//Új tulajdonos felvétele
void uj_tulaj(Tulajdonos **eleje){
    konzol_torol();
    fejlec();

    Tulajdonos *uj = (Tulajdonos*)malloc(sizeof(Tulajdonos));
    uj->allatok = NULL;
    uj->allat_db = 0;
    uj->kov = NULL;

    printf("\nUj tulajdonos felvetele\n\n");

    printf("Nev: ");
    fgets(uj->nev, sizeof(uj->nev), stdin);
    uj->nev[strcspn(uj->nev, "\n")] = 0;

    do{
        printf("Telefonszam (+36... vagy 06...): ");
        fgets(uj->tel, sizeof(uj->tel), stdin);
        uj->tel[strcspn(uj->tel, "\n")] = 0;
        if(!tel_valid(uj->tel)){
            printf("Hibas telefonszam formatum!\n");
        }
    } while(!tel_valid(uj->tel));

    do{
        printf("E-mail: ");
        fgets(uj->email, sizeof(uj->email), stdin);
        uj->email[strcspn(uj->email, "\n")] = 0;
        if(!email_valid(uj->email)){
            printf("Hibas e-mail formatum, tartalmaznia kell @ es . karaktert!\n");
        }
    } while(!email_valid(uj->email));

    uj->id = kov_id_tulaj(*eleje);

    if(!*eleje){
        *eleje = uj;
    } else{
        Tulajdonos *temp = *eleje;
        while(temp->kov)
            temp = temp->kov;
        temp->kov = uj;
    }

    printf("\nSikeresen felvetted a tulajdonost (Id: %d)!\n", uj->id);
}

//Tulajdonos adatainak módosítása
void tulaj_modosit(Tulajdonos *eleje){
    konzol_torol();
    fejlec();
    
    printf("Tulajdonos adatainak modositasa\n\n");

    char nev[50];
    printf("Modositando tulajdonos neve: ");
    fgets(nev, sizeof(nev), stdin);
    nev[strcspn(nev, "\n")] = 0;

    //Találatok összegyűjtése
    Tulajdonos *talalatok[100];
    int talalat_db = 0;

    Tulajdonos *temp = eleje;
    while(temp && talalat_db < 100){
        if(strstr(temp->nev, nev))
            talalatok[talalat_db++] = temp;
        temp = temp->kov;
    }

    if(talalat_db == 0){
        printf("Nem talalhato tulajdonos ilyen neven.\n");
        return;
    }

    Tulajdonos *t = NULL;

    //Ha több találat van bekérjük a módosítani kívántat
    if(talalat_db > 1){
        printf("\nTalalatok:\n");
        for(int i = 0; i < talalat_db; i++)
           printf("%d. [Id: %d] %s - %s - %s\n", i+1, talalatok[i]->id, talalatok[i]->nev, talalatok[i]->tel, talalatok[i]->email);
        
        int valasztas;
        char buffer[32];
        do{
            printf("\nMelyiket szeretned modositani (1-%d)? ", talalat_db);
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &valasztas);
            if(valasztas < 1 || valasztas > talalat_db)
                printf("Ervenytelen valasztas!\n");
        }while(valasztas < 1 || valasztas > talalat_db);

        t = talalatok[valasztas - 1];
    } else{
        t = talalatok[0];
        printf("Talalat: [Id: %d] %s\n", t->id, t->nev);
    }

    printf("\nJelenlegi adatok\n\n");
    printf("1. Nev: %s\n", t->nev);
    printf("2. Telefonszam: %s\n", t->tel);
    printf("3. E-mail cim: %s\n", t->email);

    int valasztas;
    char buffer[32];
    do{
        printf("\nMelyik adatot szeretned modositani (1-3)? ");
        fgets(buffer, sizeof(buffer), stdin);
        if(sscanf(buffer, "%d", &valasztas) != 1){
            printf("Ervenytelen valasztas!\n");
            valasztas = -1;
            continue;
        }

        if(valasztas < 1 || valasztas > 3){
            printf("Ervenytelen valasztas!\n");
            continue;
        }

        getchar();
        switch(valasztas){
            case 1:
                printf("Uj nev: ");
                fgets(t->nev, sizeof(t->nev), stdin);
                t->nev[strcspn(t->nev, "\n")] = 0;
                break;
            case 2:
                do{
                    printf("Uj telefonszam: ");
                    fgets(t->tel, sizeof(t->tel), stdin);
                    t->tel[strcspn(t->tel, "\n")] = 0;
                    if(!tel_valid(t->tel))
                        printf("Hibas formatum!\n");
                } while(!tel_valid(t->tel));
                break;
            case 3:
                do{
                    printf("Uj e-mail cim: ");
                    fgets(t->email, sizeof(t->email), stdin);
                    t->email[strcspn(t->email, "\n")] = 0;
                    if(!email_valid(t->email))
                        printf("Hibas formatum!\n");
                } while(!email_valid(t->email));
                break;
            default:
                printf("Ervenytelen valasztas!\n");
                continue;
        }

        printf("Sikeres modositas!\n");
        break;
    } while(true);
}

//Tulajdonos törlése
void tulaj_torol(Tulajdonos **eleje, Haziallat **allatok){
    konzol_torol();
    fejlec();
    
    printf("Tulajdonos torlese\n\n");

    char nev[50];
    printf("Torlendo tulajdonos neve: ");
    fgets(nev, sizeof(nev), stdin);
    nev[strcspn(nev, "\n")] = 0;

    //Találatok összegyűjtése
    Tulajdonos *talalatok[100];
    int talalat_db = 0;

    Tulajdonos *temp = *eleje;
    while(temp && talalat_db < 100){
        if(strstr(temp->nev, nev))
            talalatok[talalat_db++] = temp;
        temp = temp->kov;
    }

    if(talalat_db == 0){
        printf("Nem talalhato tulajdonos ilyen neven.\n");
        return;
    }

    Tulajdonos *t = NULL;

    if(talalat_db > 1){
        printf("\nTalalatok:\n");
        for(int i = 0; i < talalat_db; i++)
           printf("%d. [Id: %d] %s - %s - %s\n", i+1, talalatok[i]->id, talalatok[i]->nev, talalatok[i]->tel, talalatok[i]->email);
        
        int valasztas;
        char buffer[32];
        do{
            printf("\nMelyiket szeretned torolni (1-%d, 0=MEGSE)? ", talalat_db);
            fgets(buffer, sizeof(buffer), stdin);
            if(sscanf(buffer, "%d", &valasztas) != 1){
                printf("Ervenytelen valasztas!\n");
                valasztas = -1;
                continue;
            }
            if(valasztas == 0){
                printf("Torles megszakitva.\n");
                return;
            }
            if(valasztas < 1 || valasztas > talalat_db)
                printf("Ervenytelen valasztas!\n");
        }while(valasztas < 1 || valasztas > talalat_db);

        t = talalatok[valasztas - 1];
    } else{
        t = talalatok[0];
    }

    printf("Torlendo tulajdonos\n\n");
    printf("Nev: %s\n", t->nev);
    printf("Telefonszam: %s\n", t->tel);
    printf("E-mail cim: %s\n", t->email);

    if(t->allat_db > 0){
        printf("\nFigyelem! Ehhez a tulajdonoshoz %d allat tartozik\nA tulajdonos torlesevel annak minden allata es a hozzajuk tartozo vizsgalatok is torlodnek!", t->allat_db);
    }

    char megerosit[10];
    printf("\nBiztosan torolni szeretned (i/n)? ");
    fgets(megerosit, sizeof(megerosit), stdin);

    if(megerosit[0] == 'i' || megerosit[0] == 'I'){
        //Először az állatokat töröljük
        if(t->allat_db > 0){
            for(int i = 0; i < t->allat_db; i++){
                Haziallat *torlendo_allat = t->allatok[i];

                Haziallat *elozo_allat = NULL, *aktualis_allat = *allatok;
                while (aktualis_allat){
                    if(aktualis_allat->id == torlendo_allat->id){
                        if(elozo_allat){
                            elozo_allat->kov = aktualis_allat->kov;
                        } else{
                            *allatok = aktualis_allat->kov;
                        }

                        free(aktualis_allat->vizsgalatok);
                        free(aktualis_allat);
                        break;
                    }
                    elozo_allat = aktualis_allat;
                    aktualis_allat = aktualis_allat->kov;
                }
            }
        }

        //Tulajdonos törlése
        Tulajdonos *elozo = NULL, *aktualis = *eleje;
        while(aktualis && aktualis->id != t->id){
            elozo = aktualis;
            aktualis = aktualis->kov;
        }

        if(aktualis){
            if(elozo){
                elozo->kov = aktualis->kov;
            } else{
                *eleje = aktualis->kov;
            }
            free(aktualis->allatok);
            free(aktualis);
            printf("Tulajdonos torolve.\n");
        }
    } else{
        printf("Torles megszakitva.\n");
    }
}

//Tulajdonos keresése Id alapján
Tulajdonos *tulaj_keres_id(Tulajdonos *eleje, int id){
    while(eleje){
        if(eleje->id == id)
            return eleje;
        eleje = eleje->kov;
    }
    return NULL;
}

//Tulajdonos keresése név alapján
void tulaj_keres(Tulajdonos *eleje){
    konzol_torol();
    fejlec();
    
    char nev[50];
    printf("\nTulajdonos adatainak listazasa\n\n");
    printf("\nKeresett tulajdonos neve: ");
    fgets(nev, sizeof(nev), stdin);
    nev[strcspn(nev, "\n")] = 0;

    int talalat = 0;
    printf("\nTalalatok:\n");
    while(eleje){
        if(strstr(eleje->nev, nev)){
            printf("\nId: %d", eleje->id);
            printf("\nNev: %s", eleje->nev);
            printf("\nTelefonszam: %s", eleje->tel);
            printf("\nE-mail cim: %s", eleje->email);
            printf("\nAllatainak szama: %d\n", eleje->allat_db);
            talalat++;
        }
        eleje = eleje->kov;
    }

    if(talalat == 0)
        printf("Nem talalhato tulajdonos a megadott neven.\n");
}

//Egy tulajdonoshoz tartozó összes állat kilistázása
void tulaj_allatai(Haziallat *allatok){
    konzol_torol();
    fejlec();
    
    printf("Egy tulajdonoshoz tartozo allat(ok) adatai\n\n");
    char nev[50];
    printf("Tulajdonos neve: ");
    fgets(nev, sizeof(nev), stdin);
    nev[strcspn(nev, "\n")] = 0;

    int talalat = 0;
    printf("Allatok:\n\n");
    while(allatok){
        if(allatok->tulaj && strstr(allatok->tulaj->nev, nev)){
            printf("\nId: %d\n", allatok->id);
            printf("Nev: %s\n", allatok->nev);
            printf("Faj: %s\n", allatok->faj);
            printf("Szuletesi datum: %s\n", allatok->szul);
            printf("Utolso oltas datuma: %s\n", allatok->oltas);
            talalat++;
            printf("\n");
        }
        allatok = allatok->kov;
    }

    if(talalat == 0)
        printf("Nem talalhato allat ehhez a tulajdonoshoz.\n");
}