#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro_font.h>
#include <allegro_ttf.h>
#include <allegro_primitives.h>
#include <allegro_image.h>
#include <string.h>
#include "menu_lib.h"
#include "table_open.h"

int ROZD_X = 1024;
int ROZD_Y = 768;


int main()
{
    if(!al_init())
    {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }
    //Utworzenie ekranu
    ALLEGRO_DISPLAY *display = al_create_display(ROZD_X,ROZD_Y);
    if (!display)
    {
        fprintf(stderr, "Failed to create display.\n");
        return -1;
    }

    //Instalacja klawiatury
    al_install_keyboard();
    //Zaladowanie fontow
    al_init_font_addon();
    al_init_ttf_addon();

    //Zaladowanie rysowania
    al_init_primitives_addon();

    //Zaladowanie bitmap
    al_init_image_addon();
    main_menu();

    al_destroy_display(display);
    return 0;
}
