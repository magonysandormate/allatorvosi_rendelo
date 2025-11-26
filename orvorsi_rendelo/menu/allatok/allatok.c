#include <stdbool.h>
#include <stdio.h>
#include "allatok.h"
#include "../menuvalaszto/menuvalaszto.h"

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
                uj_allat();
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

void uj_allat(){
    printf("Uj haziallat felvetele\n\n");
    printf("Neve: ");
    scanf("");
    printf("Fajtaja: ");
    scanf("");
    printf("Szuletesi datuma (EEEE-HH-NN): ");
    scanf("");
    printf("Utolso oltas datuma (EEEE-HH-NN): ");
    scanf("");
    printf("Tulajdonos neve: ");
    scanf("");
}