#include <stdio.h>
#include <stdbool.h>
#include "kereses.h"
#include "../menuvalaszto/menuvalaszto.h"
#include "../../tulajmuveletek/tulajmuveletek.h"
#include "../../allatmuveletek/allatmuveletek.h"
#include "../../fajlkezeles/fajlkezeles.h"

//A "Keresés és listázás" menüpont és annak almenüi
void kereses_listazas(Tulajdonos *tulajdonosok, Haziallat *allatok){
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
                tulaj_keres(tulajdonosok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 2:
                tulaj_allatai(allatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 3:
                allat_keres(allatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 4:
                regi_oltas(allatok);
                printf("\nNyomj egy ENTER-t a folytatashoz...");
                getchar();
                break;
            case 5:
                return;
        }
    }
}