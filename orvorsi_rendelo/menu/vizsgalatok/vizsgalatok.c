#include <stdbool.h>
#include "vizsgalatok.h"
#include "../menuvalaszto/menuvalaszto.h"

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
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                return;
        }
    }
}