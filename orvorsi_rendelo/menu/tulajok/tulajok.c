#include <stdbool.h>
#include "tulajok.h"
#include "../menuvalaszto/menuvalaszto.h"

//A "Tulajdonosok kezelése" menüpont és annak almenüi
void tulaj_kezeles(){
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