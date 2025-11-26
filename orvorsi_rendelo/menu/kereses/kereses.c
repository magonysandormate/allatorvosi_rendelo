#include <stdbool.h>
#include "kereses.h"
#include "../menuvalaszto/menuvalaszto.h"

//A "Keresés és listázás" menüpont és annak almenüi
void kereses_listazas(){
    char *menupontok[] = {
        "Tulajdonos keresese es adatainak listazasa",
        "Egy tulajdonoshoz tartozo haziallatok adatainak kilistazasa",
        "Haziallat keresese es adatainak listazasa",
        "1 evnel regebben beoltott haziallatok kilistazasa",
        "Vissza a fomenube"
    };
    int valasztas;

    while(true){
        valasztas = menu_valasztas("Kereses es listazas", menupontok, 5);

        switch (valasztas){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                return;
        }
    }
}