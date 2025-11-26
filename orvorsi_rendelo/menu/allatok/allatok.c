#include <stdbool.h>
#include <stdio.h>
#include "allatok.h"
#include "../menuvalaszto/menuvalaszto.h"
#include "../../allatmuveletek/allatmuveletek.h"
#include "../../fajlkezeles/fajlkezeles.h"

extern Tulajdonos *tulajdonosok;
extern Haziallat *allatok;

//Az "Állatok kezelése" menüpont és annak almenüi
void allat_kezeles(){
    char *menupontok[] = {
        "Uj haziallat felvetele",
        "Haziallat adatainak modositasa",
        "Haziallat torlese",
        "Vissza a fomenube"
    };
    int valasztas;

    while(true){
        valasztas = menu_valasztas("Haziallatok kezelese", menupontok, 4);

        switch (valasztas){
            case 1:
                uj_allat(&allatok, tulajdonosok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 2:
                allat_modosit(allatok, tulajdonosok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 3:
                allat_torol(&allatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 4:
                return;
        }
    }
}