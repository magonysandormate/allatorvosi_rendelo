#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "menuvalaszto.h"
#include "../../fajlkezeles/fajlkezeles.h"

//Az ismétlés elkerülése és a helytakarékosság érdekében ez a függvény hozza létre a menüpontokat
int menu_valasztas(char *menu_nev, char **menupontok, int be_meret){
    char valasztas[32];
    int visszateres;
    while (true){
        konzol_torol();
        fejlec();

        printf("%s\n\n", menu_nev);
        for (int i = 0; i < be_meret; i++){
            printf("%d. %s\n", i + 1, menupontok[i]);
        }
        printf("Valassz menupontot (1-%d): ", be_meret);

        if(fgets(valasztas, sizeof(valasztas), stdin) == NULL){
            printf("Beolvasasi hiba, probalja ujra\n");
            continue;
        }

        if (sscanf(valasztas, "%d", &visszateres) == 1){
            if(visszateres > 0 && visszateres <= be_meret){
                return visszateres;
            }
        }
        printf("Hibas bevitel, kerem egy 1 es %d kozotti szamot adjon meg\n", be_meret);
        getchar();
    }
}