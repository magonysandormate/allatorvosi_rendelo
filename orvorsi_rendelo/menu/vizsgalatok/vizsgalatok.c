#include <stdbool.h>
#include <stdio.h>
#include "vizsgalatok.h"
#include "../menuvalaszto/menuvalaszto.h"
#include "../../vizsgalatmuveletek/vizsgmuveletek.h"
#include "../../fajlkezeles/fajlkezeles.h"

extern Haziallat *allatok;
extern Vizsgalat *vizsgalatok;

//A "Vizsgálatok kezelése" menüpont és annak almenüi
void vizsgalat_kezeles(){
    char *menupontok[] = {
        "Uj vizsgalat felvetele",
        "Vizsgalat adatainak modositasa",
        "Vizsgalat torlese",
        "Vissza a fomenube"
    };
    int valasztas;

    while(true){
        valasztas = menu_valasztas("Vizsgalatok kezelese", menupontok, 4);

        switch (valasztas){
            case 1:
                uj_vizsgalat(&vizsgalatok, allatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 2:
                vizsgalat_modosit(vizsgalatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 3:
                vizsgalat_torol(&vizsgalatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 4:
                return;
        }
    }
}