#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro_font.h>
#include <allegro_ttf.h>
#include <allegro_primitives.h>
#include <allegro_image.h>
#include <string.h>
#include "new_game.h"
#include "zapis.h"
char nazwa[] = "WARCABY";
char powrot[] = "Powrot";
char napisy[6][20] = {"Nowa gra", "Wczytaj gre", "Zasady","Informacje o grze", "Zakoncz"};
///Glowna aktywnosc menu
void main_menu()
{
    ALLEGRO_COLOR backgroundc = al_map_rgb(30, 115, 70);

    ALLEGRO_FONT *title = al_load_ttf_font("fonts/Jelly Crazies.ttf", 72 , 0);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 48 , 0);
    if (!title)
    {
        fprintf(stderr, "Could not load 'Jelly Crazies.ttf'\n");
    }
    if (!menu_text)
    {
        fprintf(stderr, "Could not load 'Maritime_Tropical_Neue.ttf'\n.");
    }
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    int stop_game = 0, actual_menu_item = 0;
    menu_create(title, menu_text, 0);
    while (!stop_game)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    actual_menu_item = 4;
                    break;
                }

            if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                    actual_menu_item --;
                    if(actual_menu_item < 0)
                    {
                        actual_menu_item = 4;
                    }
                    menu_create(title, menu_text, actual_menu_item);
                }

            if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {
                    actual_menu_item ++;
                    if (actual_menu_item > 4)
                    {
                        actual_menu_item = 0;
                    }
                    menu_create(title, menu_text, actual_menu_item);
                }
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    //fprintf(stderr,"Wlaczono %d menu\n", actual_menu_item);
                    break;

                }
        }
    }
    al_destroy_event_queue(event_queue);
    if(actual_menu_item != 4)
    {
        open_menu(actual_menu_item);
    }


}

///Tworzy grafike menu glowngo
void menu_create(ALLEGRO_FONT *title_font, ALLEGRO_FONT *menu_font, int podswietlone)
{
    ALLEGRO_COLOR backgroundc = al_map_rgb(30, 115, 70);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR  white = al_map_rgb(255, 255, 255);
    al_clear_to_color(backgroundc);
    al_draw_text(title_font, white, 512, 0, ALLEGRO_ALIGN_CENTER, nazwa);
    for (int i = 0; i <=5; i++)
    {
        if (podswietlone == i)
        {
            al_draw_text(menu_font, yellow, 512, 200 + 75 * i, ALLEGRO_ALIGN_CENTER, napisy[i]);
        }
        else
        {
            al_draw_text(menu_font, white, 512, 200 + 75 * i, ALLEGRO_ALIGN_CENTER, napisy[i]);
        }
    }
    al_flip_display();
}

///Otwiera aktywnosc wybrana przez uzytkownika
void open_menu (int menu_number)
{
    if (menu_number == 0)
    {
        new_game(); ///Otwarcie menu wyboru gry new_game.c
    }
    if (menu_number == 1)
    {
        open_game();///Otwarcie menu wyboru zapisu zapis.c
    }
    if (menu_number == 2)
    {
        open_rules();///Otwarcie menu z regulami (tutaj)
    }
    if (menu_number == 3)
    {
        open_description();///Otwarcie menu z opisem gry (tutaj)
    }
}

///Otwiera opis gry z pliku info.txt
void open_description()
{
    ALLEGRO_COLOR backgroundc = al_map_rgb(30, 115, 70);
    al_clear_to_color(backgroundc);
    ALLEGRO_FONT *title = al_load_ttf_font("fonts/Jelly Crazies.ttf", 72 , 0);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 48 , 0);
    if (!title)
    {
        fprintf(stderr, "Could not load 'Jelly Crazies.ttf'\n");
    }
    if (!menu_text)
    {
        fprintf(stderr, "Could not load 'Maritime_Tropical_Neue.ttf'\n.");
    }
    ALLEGRO_COLOR  white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    al_draw_text(title, white, 512, 0, ALLEGRO_ALIGN_CENTER, nazwa);
    FILE *info = fopen("info.txt", "r");
    char pisz[101];
    if ( info == NULL)
    {
        fprintf(stderr, "Blad ladowania 'info.txt'\n");
        al_clear_to_color(backgroundc);
        al_draw_text(title, white, 512, 0, ALLEGRO_ALIGN_CENTER, nazwa);
        al_draw_text(menu_text, white, 512, 384, ALLEGRO_ALIGN_CENTER, "Nie mozna zaladowac informacji. Przepraszamy!");
        al_flip_display();
        al_rest(3);
        main_menu();
    }
    else
    {
        int i = 0;
        while (fgets(pisz, 100, info) != NULL)
        {
            int j = 0;
            char wypisz[101];
             ///Usuwanie niepotrzebnych znakow na koncu wypisz
            while (pisz[j] != '\n')
            {
                wypisz[j] = pisz[j];
                j++;
            }
            for (j; j<=100; j++)
            {
                wypisz[j] = '\0';
            }
            al_draw_text(menu_text, white, 512, 200 + 55 * i, ALLEGRO_ALIGN_CENTER, wypisz);
            i++;
        }
        fclose(info);
        al_draw_text(menu_text, white, 512, 690, ALLEGRO_ALIGN_CENTER, powrot);
        ALLEGRO_EVENT_QUEUE *event_queue_desc = al_create_event_queue();
        al_register_event_source(event_queue_desc, al_get_keyboard_event_source());
        al_flip_display();
        int desc_stop = 0;
        int pod = 0;
        while(!desc_stop)
        {
            ALLEGRO_EVENT ev_desc;
            al_wait_for_event(event_queue_desc, &ev_desc);
            if (ev_desc.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (ev_desc.keyboard.keycode == ALLEGRO_KEY_DOWN || ev_desc.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                    if (!pod)
                    {
                        pod = 1;
                        al_draw_text(menu_text, yellow, 512, 690, ALLEGRO_ALIGN_CENTER, powrot);
                    }
                    else
                    {
                        pod = 0;
                        al_draw_text(menu_text, white, 512, 690, ALLEGRO_ALIGN_CENTER, powrot);
                    }
                    al_flip_display();
                }
                if (ev_desc.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    al_destroy_event_queue(event_queue_desc);
                    break;

                }
                if (ev_desc.keyboard.keycode == ALLEGRO_KEY_ENTER && pod)
                {
                    al_destroy_event_queue(event_queue_desc);
                    break;
                }
            }
        }
        main_menu();
    }
}

///Otwiera zasady gry z pliku rules.txt
void open_rules()
{
    ALLEGRO_COLOR backgroundc = al_map_rgb(30, 115, 70);
    al_clear_to_color(backgroundc);
    ALLEGRO_FONT *title = al_load_ttf_font("fonts/Jelly Crazies.ttf", 72 , 0);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 28 , 0);
    if (!title)
    {
        fprintf(stderr, "Could not load 'Jelly Crazies.ttf'\n");
    }
    if (!menu_text)
    {
        fprintf(stderr, "Could not load 'Maritime_Tropical_Neue.ttf'\n.");
    }
    ALLEGRO_COLOR  white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    al_draw_text(title, white, 512, 0, ALLEGRO_ALIGN_CENTER, nazwa);
    FILE *info = fopen("rules.txt", "r");
    char pisz[101];
    if ( info == NULL)
    {
        fprintf(stderr, "Blad ladowania rules.txt'\n");
        al_clear_to_color(backgroundc);
        al_draw_text(title, white, 512, 0, ALLEGRO_ALIGN_CENTER, nazwa);
        al_draw_text(menu_text, white, 512, 384, ALLEGRO_ALIGN_CENTER, "Nie mozna zaladowac zasad gry. Przepraszamy!");
        al_flip_display();
        al_rest(3);
        main_menu();
    }
    else
    {
        int i = 0;
        while (fgets(pisz, 100, info) != NULL)
        {
            int j = 0;
            char wypisz[101];
            ///Usuwanie niepotrzebnych znakow na koncu wypisz
            while (pisz[j] != '\n')
            {
                wypisz[j] = pisz[j];
                j++;
            }
            for (j; j<=100; j++)
            {
                wypisz[j] = '\0';
            }
            al_draw_text(menu_text, white, 20, 100 + 40 * i, ALLEGRO_ALIGN_LEFT, wypisz);
            i++;
        }
        al_draw_text(menu_text, white, 512, 690, ALLEGRO_ALIGN_CENTER, powrot);
        ALLEGRO_EVENT_QUEUE *event_queue_desc = al_create_event_queue();
        al_register_event_source(event_queue_desc, al_get_keyboard_event_source());
        al_flip_display();
        int desc_stop = 0;
        int pod = 0;
        while(!desc_stop)
        {
            ALLEGRO_EVENT ev_desc;
            al_wait_for_event(event_queue_desc, &ev_desc);
            if (ev_desc.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (ev_desc.keyboard.keycode == ALLEGRO_KEY_DOWN || ev_desc.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                    if (!pod)
                    {
                        pod = 1;
                        al_draw_text(menu_text, yellow, 512, 690, ALLEGRO_ALIGN_CENTER, powrot);
                    }
                    else
                    {
                        pod = 0;
                        al_draw_text(menu_text, white, 512, 690, ALLEGRO_ALIGN_CENTER, powrot);
                    }
                    al_flip_display();
                }
                if (ev_desc.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    al_destroy_event_queue(event_queue_desc);
                    break;

                }
                if (ev_desc.keyboard.keycode == ALLEGRO_KEY_ENTER && pod)
                {
                    al_destroy_event_queue(event_queue_desc);
                    break;
                }
            }
        }
        fclose(info);
        main_menu();
    }
}

