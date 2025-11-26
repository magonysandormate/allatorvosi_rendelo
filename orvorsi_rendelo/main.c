#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "menu/allatok/allatok.h"
#include "menu/kereses/kereses.h"
#include "menu/tulajok/tulajok.h"
#include "menu/vizsgalatok/vizsgalatok.h"
#include "menu/menuvalaszto/menuvalaszto.h"

//Főmenü
void fomenu(){
    char *menupontok[] = {
        "Tulajdonosok kezelese",
        "Allatok kezelese",
        "Vizsgalatok kezelese",
        "Kereses es listazas",
        "Kilepes"
    };
    int valasztas;

    while(true){
        valasztas = menu_valasztas("Fomenu", menupontok, 5);

        switch (valasztas){
            case 1:
                tulaj_kezeles();
                break;
            case 2:
                allat_kezeles();
                break;
            case 3:
                vizsgalat_kezeles();
                break;
            case 4:
                kereses_listazas();
                break;
            case 5:
                return;
        }
    }
}

int main(){
    printf("Allatorvosi rendelo\n");
    fomenu();

    return 0;
}