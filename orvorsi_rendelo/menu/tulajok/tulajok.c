#include <stdbool.h>
#include <stdio.h>
#include "tulajok.h"
#include "../menuvalaszto/menuvalaszto.h"
#include "../../tulajmuveletek/tulajmuveletek.h"
#include "../../fajlkezeles/fajlkezeles.h"

//A "Tulajdonosok kezelése" menüpont és annak almenüi
void tulaj_kezeles(Tulajdonos **tulajdonosok, Haziallat **allatok, Vizsgalat **vizsgalatok){
    char *menupontok[] = {
        "Uj tulajdonos felvetele",
        "Tulajdonos adatainak modositasa",
        "Tulajdonos torlese",
        "Vissza a fomenube"
    };
    int valasztas;

    while (true){
        valasztas = menu_valasztas("Tulajdonosok kezelese", menupontok, 4);

        switch (valasztas){
            case 1:
                uj_tulaj(tulajdonosok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 2:
                tulaj_modosit(*tulajdonosok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 3:
                tulaj_torol(tulajdonosok, allatok, vizsgalatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 4:
                return;
        }
    }
}