#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro_font.h>
#include <allegro_ttf.h>
#include <string.h>
#include <allegro_primitives.h>
#include <allegro_image.h>
#include <time.h>
#include "struct_pionek.h"
void zapisz(struct pionek *tab_pion, int ruszajacy,int rozgrywka, int kolorgracza)
{
    ALLEGRO_COLOR white  = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR green = al_map_rgb(0, 255, 50);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 48 , 0);
    ALLEGRO_FONT *text_zapisu = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 40 , 0);
    if (!menu_text)
    {
        fprintf(stderr, "Could not load 'Maritime_Tropical_Neue.ttf'\n.");
    }
    rysuj_pionki(tab_pion);
    time_t czas;
    struct tm * ptr;
    time( & czas );
    ptr = localtime( & czas );
    char * data = asctime( ptr );
    int i = 0, z = 0;
    char nazwa_pliku[] = "Zapisy/                       ";
    int j = 7;
    while(data[i] != '\n')
    {
        if(data[i] == ' ')
        {
            i++;
        }
        else
        {
            nazwa_pliku[j + z] = data [i];
            i++;
            z ++;
        }
    }
    nazwa_pliku[j + z] = '.';
    nazwa_pliku[j + z + 1] = 't';
    nazwa_pliku[j + z + 2] = 'x';
    nazwa_pliku[j + z + 3] = 't';
    nazwa_pliku[j + z + 4] = '\0';
    FILE *dozapisu, *zapisy;
    dozapisu = fopen(nazwa_pliku, "wr");
    fprintf(dozapisu, "%d %d %d\n", rozgrywka, kolorgracza, ruszajacy);
    for (int i = 0; i < 24; i++)
    {
        fprintf(dozapisu, "%d %d %d %d %d\n", tab_pion[i].x, tab_pion[i].y, tab_pion[i].color, tab_pion[i].damka, tab_pion[i].zbity);
    }
    zapisy = fopen("Zapisy/Zapisy.txt", "a");
    fprintf(zapisy, "%s", data);
    fclose(dozapisu);
    fclose(zapisy);
    for (int iter = 0; iter < 100; iter++)
    {
        al_draw_filled_rectangle(279, 300, 744, 525, green);
        al_draw_textf(menu_text, white, 512, 300, ALLEGRO_ALIGN_CENTER, "Zapisywanie gry");
        al_draw_rectangle(309, 397, 710, 502, al_map_rgb(0, 0, 0), 5);
        al_draw_filled_rectangle(312, 400, (312 + (iter + 1) * 4), 500, al_map_rgb(255, 2 * iter, 5));
        al_draw_textf(menu_text, white, 512, 400, ALLEGRO_ALIGN_CENTER, "%d %%", iter + 1);
        al_rest(0.05);
        al_flip_display();
    }
    al_draw_filled_rectangle(279, 300, 744, 525, green);
    al_draw_textf(menu_text, white, 512, 300, ALLEGRO_ALIGN_CENTER, "Nazwa zapisu :");
    int l = 0;
    while(data[l]  != '\n')
    {
        l++;
    }
    data[l] = '\0';
    al_draw_textf(text_zapisu, white, 512, 370, ALLEGRO_ALIGN_CENTER, "%s", data);
    al_flip_display();
    al_rest(5);
}
void open_game()
{
    ALLEGRO_BITMAP *szachownica = al_load_bitmap("szachownica.png");
    ALLEGRO_BITMAP *kursor = al_load_bitmap("kursor.png");
    ALLEGRO_COLOR background =al_map_rgb(30, 115, 70);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR white  = al_map_rgb(255, 255, 255);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 48 , 0);
    al_clear_to_color(background);
    if (!menu_text)
    {
        fprintf(stderr, "Could not load 'Maritime_Tropical_Neue.ttf'\n.");
    }
    al_draw_text(menu_text, white, 30, 0, ALLEGRO_ALIGN_LEFT, "Dostepne zapisy :");
    int i = 0, aktualnie_podswietlony = 0, stop = 0;
    char wlacz[]= "                                      ";
    ALLEGRO_EVENT_QUEUE *ev_queue_wczytaj = al_create_event_queue();
    al_register_event_source(ev_queue_wczytaj, al_get_keyboard_event_source());
    while(!stop)
    {
        FILE *zapisy = fopen("Zapisy/Zapisy.txt", "r");
        i = 0;
        if(zapisy == NULL)
        {
            al_draw_text(menu_text, white, 120, 55, ALLEGRO_ALIGN_LEFT, "Brak dostepnych zapisow");
            stop = 1;
            al_flip_display();
            aktualnie_podswietlony = i + 2;
            al_rest(5);
        }
        else
        {
            char pisz[101];
            while (fgets(pisz, 100, zapisy) != NULL && i < 10)
            {
                int j = 0;
                char wypisz[101];
                while (pisz[j] != '\n')
                {
                    wypisz[j] = pisz[j];
                    j++;
                }
                for (j; j<=100; j++)
                {
                    wypisz[j] = '\0';
                }
                if(i == aktualnie_podswietlony)
                {
                    al_draw_textf(menu_text, yellow, 30, 55 + 55 * i, ALLEGRO_ALIGN_LEFT, "%d. %s", i+1, wypisz);
                    int j = 0, z = 0;
                    while(wypisz[j] != '\n')
                    {
                        if(wypisz[j] != ' ')
                        {
                            wlacz[z] = wypisz[j];
                            z++;
                        }
                        j ++;
                    }
                    wlacz[j + 1] = '\0';
                }
                else
                {
                    al_draw_textf(menu_text, white, 30, 55 + 55 * i, ALLEGRO_ALIGN_LEFT, "%d. %s", i+1, wypisz);
                }
                i++;
            }
            if(aktualnie_podswietlony == i + 2)
            {
                al_draw_text(menu_text, yellow, 120, 55 + 55 * (i + 1), ALLEGRO_ALIGN_CENTER, "Powrot");
            }
            else
            {
                al_draw_text(menu_text, white, 120, 55 + 55 * (i + 1), ALLEGRO_ALIGN_CENTER, "Powrot");
            }
            fclose(zapisy);
        }
        al_flip_display();
        ALLEGRO_EVENT ev_wczytaj;
        al_wait_for_event(ev_queue_wczytaj, &ev_wczytaj);
        if (ev_wczytaj.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev_wczytaj.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                if(aktualnie_podswietlony == i - 1)
                {
                    aktualnie_podswietlony += 3;
                }
                else
                {
                    aktualnie_podswietlony ++;
                }
                if(aktualnie_podswietlony > i + 2)
                {
                    aktualnie_podswietlony = 0;
                }
            }
            if(ev_wczytaj.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                if(aktualnie_podswietlony == i + 2)
                {
                    aktualnie_podswietlony -= 3;
                }
                else
                {
                    aktualnie_podswietlony --;
                }
                if(aktualnie_podswietlony < 0)
                {
                    aktualnie_podswietlony = i + 2;
                }
            }
            if(ev_wczytaj.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                stop = 1;
                aktualnie_podswietlony = i + 2;
            }
            if(ev_wczytaj.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                stop = 1;
            }
        }
    }
    al_destroy_event_queue(ev_queue_wczytaj);
    if(aktualnie_podswietlony == i + 2)
    {
        main_menu();
    }
    else
    {
        for (int iter = 0; iter < 100; iter++)
        {
            al_clear_to_color(background);
            al_draw_textf(menu_text, white, 512, 300, ALLEGRO_ALIGN_CENTER, "Ladowanie gry");
            al_draw_rectangle(309, 397, 710, 502, al_map_rgb(0, 0, 0), 5);
            al_draw_filled_rectangle(312, 400, (312 + (iter + 1) * 4), 500, al_map_rgb(255, 2 * iter, 5));
            al_draw_textf(menu_text, white, 512, 400, ALLEGRO_ALIGN_CENTER, "%d %%", iter + 1);
            al_rest(0.05);
            al_flip_display();
        }
        char nazwa_pliku[] = "Zapisy/                       ";
        i = 0;
        int j = 7, z = 0;
        while(wlacz[i] != '\n' && wlacz[i] != '\0')
        {
            if(wlacz[i] == ' ')
            {
                i++;
            }
            else
            {
                nazwa_pliku[j] = wlacz[i];
                i++;
                j++;
            }
        }
        nazwa_pliku[j] = '.';
        nazwa_pliku[j + 1] = 't';
        nazwa_pliku[j + 2] = 'x';
        nazwa_pliku[j + 3] = 't';
        nazwa_pliku[j + 4] = '\0';
        al_clear_to_color(al_map_rgb(30, 115, 70));
        ALLEGRO_COLOR white  = al_map_rgb(255, 255, 255);
        al_flip_display();
        FILE *otwierany_zapis = fopen(nazwa_pliku, "r");
        int rozgrywka, ruszajacy, kolor_gracza1;
        struct pionek tab_pionek[24];
        char linijka[10];
        i = 0, j = 0;
        if(otwierany_zapis != NULL && i < 25)
        {
            while(fgets(linijka, 9, otwierany_zapis) != NULL)
            {
                    //fprintf(stderr, "%s \n", linijka);
                    if(i == 0)
                    {
                        ///linijka [x]  x: 0 - rozgrywka, 2 - kolor gracza, 2 - ruszajacy
                        rozgrywka = (int) linijka[0] - 48;
                        kolor_gracza1 = (int) linijka[2] -48;
                        ruszajacy = (int) linijka[4] - 48;
                        i++;
                    }
                    else
                    {
                        ///x, y, color, damka, zbity
                        if(!j)
                        {
                            tab_pionek[i - 1].x = (int) linijka[0] - 48;
                            tab_pionek[i - 1].y = (int) linijka[2] - 48;
                            tab_pionek[i - 1].color = (int) linijka[4] - 48;
                            tab_pionek[i - 1].damka = (int) linijka[6] - 48;
                            j=!j;

                        }
                        else
                        {
                            j=!j;
                            tab_pionek[i - 1].zbity = (int) linijka[0] - 48;
                            i++;
                        }

                    }
            }
            fclose(otwierany_zapis);
            if(rozgrywka)
            {
                begin_computer(kolor_gracza1, szachownica, kursor, 1, ruszajacy, tab_pionek);
            }
            else
            {
                begin_2_players(kolor_gracza1, szachownica, kursor, 1, ruszajacy, tab_pionek);
            }
        }
        else
        {
            al_rest(3);
            main_menu();
        }

    }
}



