#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro_font.h>
#include <allegro_ttf.h>
#include <string.h>
#include <allegro_primitives.h>
#include <allegro_image.h>
#include "struct_pionek.h"
#include "game.h"
void begin_computer(int color_gracza, ALLEGRO_BITMAP *szachownica, ALLEGRO_BITMAP *kursor, int wczytana, int ruszajcy, struct pionek *w_pionki)
{
    int kolor_komputera = !color_gracza;
    int aktualnie_ruszajacy = 0;
    ALLEGRO_FONT *title = al_load_ttf_font("fonts/Jelly Crazies.ttf", 60, 0);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 32 , 0);
    ALLEGRO_FONT *info_font = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 25 , 0);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    ALLEGRO_COLOR color_napisu, color_prostokata;
    int wybrany = 0, x_wybrany = NULL, y_wybrany = NULL, wyk_bicie_x = NULL, wyk_bicie_y = NULL, ruchy_damka = 0, ruchy, esc_1 = 0;;
    struct pionek tab_pion[24];
    int i, j, tab[] = {1, 0, 3, 0, 5, 0, 7, 0,
                0, 1, 2, 1, 4, 1, 6, 1,
                1, 2, 3, 2, 5, 2, 7, 2,

                0, 7, 2, 7, 4, 7, 6, 7,
                  1, 6, 3, 6, 5, 6, 7, 6,
                  0, 5, 2, 5, 4, 5, 6, 5};
    for (i = 0, j = 0; i < 24; i++, j += 2)
    {
        if(i < 12)
        {
            tab_pion[i].color = 0;
        }
        else
        {
            tab_pion[i].color = 1;
        }
        tab_pion[i].x = tab[j];
        tab_pion[i].y = tab[j+1];
        tab_pion[i].zbity = 0;
        tab_pion[i].damka = 0;
    }
    if(wczytana)
    {
       aktualnie_ruszajacy = ruszajcy;
        for(int iteracja  = 0; iteracja < 24; iteracja ++)
        {
            tab_pion[iteracja].x = w_pionki[iteracja].x;
            tab_pion[iteracja].y = w_pionki[iteracja].y;
            tab_pion[iteracja].color = w_pionki[iteracja].color;
            tab_pion[iteracja].damka = w_pionki[iteracja].damka;
            tab_pion[iteracja].zbity = w_pionki[iteracja].zbity;
        }
        al_draw_bitmap(szachownica, 24, 24, NULL);
        rysuj_pionki(tab_pion);
        al_draw_text(menu_text, white, 900, 640, ALLEGRO_ALIGN_CENTER, "Zapisz (\"Z\")");
        al_draw_text(menu_text, white, 900, 690, ALLEGRO_ALIGN_CENTER, "Powrot (\"ESC\")");
         if(!aktualnie_ruszajacy)
        {
            color_napisu = red;
            color_prostokata = white;
        }
        else
        {
            color_napisu = white;
            color_prostokata = red;
        }
        al_draw_filled_rectangle(749, 150, 1019, 200, color_prostokata);
        al_draw_textf(info_font, color_napisu, 884, 150, ALLEGRO_ALIGN_CENTER, "Ruch gracza");
        al_flip_display();
    }
    int game = 1, bicie = 0, temp_i = 3, temp_kierunku = 0;
    int x = 0, y = 0, b_color;
    int bicia[48], kierunek[48];
    ALLEGRO_EVENT_QUEUE *event_queue_game = al_create_event_queue();
    al_register_event_source(event_queue_game, al_get_keyboard_event_source());
    while(game)
    {
        if(!aktualnie_ruszajacy)
        {
            b_color = 0;
            color_napisu = red;
            color_prostokata = white;
        }
        else
        {
            b_color = 1;
            color_napisu = white;
            color_prostokata = red;
        }
        int j = 0;
        j = znajdz_bica(bicia, kierunek, tab_pion, b_color, wyk_bicie_x, wyk_bicie_y);
        /*int test = 0;
        while (test < j && bicia[test] != 9)
        {
            fprintf(stderr, "Bicie [%d] =%d %d \n Kierynek %d, %d\n\n",((test + 1) /2), bicia[test], bicia[test + 1], kierunek[test], kierunek[test + 1]);
            test += 2;
        }*/
         if(!aktualnie_ruszajacy)
        {
            b_color = 0;
            color_napisu = red;
            color_prostokata = white;
        }
        else
        {
            b_color = 1;
            color_napisu = white;
            color_prostokata = red;
        }
        if (b_color == color_gracza)
        {
            al_draw_filled_rectangle(749, 150, 1019, 200, color_prostokata);
            al_draw_textf(info_font, color_napisu, 884, 150, ALLEGRO_ALIGN_CENTER, "Ruch gracza");
            al_draw_bitmap(szachownica, 24, 24, NULL);
            ALLEGRO_EVENT ev_game;
            al_wait_for_event(event_queue_game, &ev_game);
            if (ev_game.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if(ev_game.keyboard.keycode == ALLEGRO_KEY_Z)
                {
                    zapisz(tab_pion, aktualnie_ruszajacy, 1, color_gracza);
                }
                if(ev_game.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                {
                    if(x + 1 <= 8)
                    {
                        x++;
                    }
                }
                if(ev_game.keyboard.keycode == ALLEGRO_KEY_LEFT)
                {
                    if(x - 1 >= 0)
                    {
                        x--;
                    }
                }
                if(ev_game.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {
                    if( x!= 8)
                    {
                        if(y + 1 <= 7)
                        {
                            y++;
                        }
                    }
                    else
                    {
                        y = !y;
                    }
                }
                if(ev_game.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                    if(x!= 8)
                    {
                        if(y - 1 >= 0)
                        {
                            y--;
                        }
                    }
                    else
                    {
                        y = !y;
                    }
                }
                if(ev_game.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    al_draw_filled_rectangle(749, 275, 1019, 350, color_prostokata);
                    if (x == 8)
                    {
                        if(y % 2 == 0)
                        {
                            game = 0;
                        }
                        else
                        {
                            zapisz(tab_pion, aktualnie_ruszajacy, 1, color_gracza);
                        }
                    }
                    else if(wybrany)
                    {
                        {
                            if(bicia[0] == 9)
                            {
                                if(ruch_dozwolony(x_wybrany, y_wybrany, x, y, b_color, tab_pion))
                                {
                                    for(int iter = 0; iter < 24; iter++)
                                    {
                                        if(tab_pion[iter].x == x_wybrany && tab_pion[iter].y == y_wybrany && !tab_pion[iter].zbity && tab_pion[iter].color == b_color && tab_pion[iter].damka)
                                        {
                                            ruchy_damka++;
                                        }
                                        else if(tab_pion[iter].x == x_wybrany && tab_pion[iter].y == y_wybrany && !tab_pion[iter].zbity && tab_pion[iter].color == b_color && !tab_pion[iter].damka)
                                        {
                                            ruchy_damka = 0;
                                        }
                                    }
                                    rusz(x_wybrany, y_wybrany, x, y, b_color, tab_pion);
                                    wybrany = 0;
                                    x_wybrany = NULL;
                                    y_wybrany = NULL;
                                    wyk_bicie_x = NULL;
                                    wyk_bicie_y = NULL;
                                    aktualnie_ruszajacy = !aktualnie_ruszajacy;
                                }
                                else
                                {
                                    al_draw_filled_rectangle(749, 275, 1019, 350, color_prostokata);
                                    al_draw_text(info_font, color_napisu, 884, 275, ALLEGRO_ALIGN_CENTER, "Ruch nie dozwolony!");
                                }
                            }
                            else
                            {
                                int nieprawidlowe = 0;
                                struct pionek aktalny_pionek;
                                for(int iter = 0; iter < 24; iter++)
                                {
                                    if(tab_pion[iter].x == x_wybrany && tab_pion[iter].y == y_wybrany && !tab_pion[iter].zbity && tab_pion[iter].color == b_color)
                                    {
                                        aktalny_pionek = tab_pion[iter];
                                    }
                                }
                                for (int iter = 0; iter < j; iter += 2)
                                {
                                    if(!aktalny_pionek.damka)
                                    {
                                        if(x_wybrany + 2 * kierunek[iter] == x && y_wybrany + 2 * kierunek [iter + 1] == y)
                                        {
                                            bij(x_wybrany, y_wybrany, x, y, kierunek[iter], kierunek[iter + 1], b_color, tab_pion);
                                            wybrany = 0;
                                            x_wybrany = NULL;
                                            y_wybrany = NULL;
                                            wyk_bicie_x = x;
                                            wyk_bicie_y = y;
                                            ruchy_damka = 0;
                                            if((aktalny_pionek.color == 0 && y == 7)|| (aktalny_pionek.color == 1 && y == 0))
                                            {
                                                wybrany = 0;
                                                x_wybrany = NULL;
                                                y_wybrany = NULL;
                                                wyk_bicie_x = NULL;
                                                wyk_bicie_y = NULL;
                                                aktualnie_ruszajacy = !aktualnie_ruszajacy;
                                            }
                                            else
                                            {
                                                j = znajdz_bica(bicia, kierunek, tab_pion, b_color, wyk_bicie_x, wyk_bicie_y);
                                                if(j == 0)
                                                {
                                                    wyk_bicie_x = NULL;
                                                    wyk_bicie_y = NULL;
                                                    aktualnie_ruszajacy = !aktualnie_ruszajacy;
                                                }
                                            }

                                        }
                                        else
                                        {
                                            nieprawidlowe +=2;

                                        }
                                    }
                                    else
                                    {
                                        if(sprawdz_xy(x_wybrany, y_wybrany, x, y))
                                        {
                                            int il_pionkow_miedzy = 0, mozliwosc = 1, temp_i = -1, temp_color = -1, ilosc_swoich = 0;
                                            if (kierunek[iter] == 1 && kierunek[iter + 1] == 1 && x_wybrany < x && y_wybrany < y)
                                            {
                                                for(int i = 1; x_wybrany + i < x && y_wybrany + i < y && ilosc_swoich == 0; i++)
                                                {
                                                    for (int j = 0; j < 24; j++)
                                                    {
                                                        if(tab_pion[j].x == x_wybrany + i && tab_pion[j].y == y_wybrany + i && !tab_pion[j].zbity && tab_pion[j].color != aktalny_pionek.color)
                                                        {
                                                            temp_i = i;
                                                            il_pionkow_miedzy++;
                                                        }
                                                        if(tab_pion[j].x == x_wybrany + i && tab_pion[j].y == y_wybrany + i && !tab_pion[j].zbity && tab_pion[j].color == aktalny_pionek.color)
                                                        {
                                                            temp_i = -1;
                                                            ilosc_swoich++;
                                                        }
                                                    }
                                                }
                                            }
                                            else if (kierunek[iter] == 1 && kierunek[iter + 1] == -1 && x_wybrany < x && y_wybrany > y)
                                            {
                                                for(int i = 1; x_wybrany + i < x && y_wybrany - i > y && ilosc_swoich == 0; i++)
                                                {
                                                    for (int j = 0; j < 24; j++)
                                                    {
                                                        if(tab_pion[j].x == x_wybrany + i && tab_pion[j].y == y_wybrany - i && !tab_pion[j].zbity && tab_pion[j].color != aktalny_pionek.color)
                                                        {
                                                            temp_i = i;
                                                            il_pionkow_miedzy++;
                                                        }
                                                        if(tab_pion[j].x == x_wybrany + i && tab_pion[j].y == y_wybrany - i && !tab_pion[j].zbity && tab_pion[j].color == aktalny_pionek.color)
                                                        {
                                                            temp_i = -1;
                                                            ilosc_swoich++;
                                                        }
                                                    }
                                                }
                                            }
                                            else if (kierunek[iter] == -1 && kierunek[iter + 1] == 1 && x_wybrany > x && y_wybrany < y)
                                            {
                                                for(int i = 1; x_wybrany - i > x && y_wybrany + i < y && ilosc_swoich == 0; i++)
                                                {
                                                    for (int j = 0; j < 24; j++)
                                                    {
                                                        if(tab_pion[j].x == x_wybrany - i && tab_pion[j].y == y_wybrany + i && !tab_pion[j].zbity && tab_pion[j].color != aktalny_pionek.color)
                                                        {
                                                            temp_i = i;
                                                            il_pionkow_miedzy++;
                                                        }
                                                        if(tab_pion[j].x == x_wybrany - i && tab_pion[j].y == y_wybrany + i && !tab_pion[j].zbity && tab_pion[j].color == aktalny_pionek.color)
                                                        {
                                                            temp_i = -1;
                                                            ilosc_swoich++;
                                                        }
                                                    }
                                                }
                                            }
                                            else if (kierunek[iter] == -1 && kierunek[iter + 1] == -1 && x_wybrany > x && y_wybrany > y)
                                            {
                                                for(int i = 1; x_wybrany - i > x && y_wybrany - i > y; i++)
                                                {
                                                    for (int j = 0; j < 24; j++)
                                                    {
                                                        if(tab_pion[j].x == x_wybrany - i && tab_pion[j].y == y_wybrany - i && !tab_pion[j].zbity && tab_pion[j].color != aktalny_pionek.color)
                                                        {
                                                            temp_i = i;
                                                            il_pionkow_miedzy++;
                                                        }
                                                        if(tab_pion[j].x == x_wybrany - i && tab_pion[j].y == y_wybrany - i && !tab_pion[j].zbity && tab_pion[j].color == aktalny_pionek.color)
                                                        {
                                                            temp_i = -1;
                                                            ilosc_swoich++;
                                                        }
                                                    }
                                                }
                                            }
                                            if(il_pionkow_miedzy == 1)
                                            {
                                                mozliwosc = 1;
                                            }
                                            if(ilosc_swoich != 0)
                                            {
                                                mozliwosc = 0;
                                            }
                                            for(int i = 0; i < 24; i++)
                                            {
                                                if(x == tab_pion[i].x && y == tab_pion[i].y && !tab_pion[i].zbity)
                                                {
                                                    mozliwosc = 0;
                                                }
                                            }
                                            if (mozliwosc && temp_i != -1)
                                            {
                                                bij_damka(x_wybrany, y_wybrany, x, y, kierunek[iter], kierunek[iter + 1], b_color, tab_pion, temp_i);
                                                wybrany = 0;
                                                x_wybrany = NULL;
                                                y_wybrany = NULL;
                                                wyk_bicie_x = x;
                                                wyk_bicie_y = y;
                                                ruchy_damka = 0;
                                                j = znajdz_bica(bicia, kierunek, tab_pion, b_color, wyk_bicie_x, wyk_bicie_y);
                                                if(j == 0)
                                                {
                                                    wyk_bicie_x = NULL;
                                                    wyk_bicie_y = NULL;
                                                    aktualnie_ruszajacy = !aktualnie_ruszajacy;
                                                }
                                            }
                                            else
                                            {
                                                nieprawidlowe +=2;
                                            }
                                        }
                                        else
                                        {
                                            nieprawidlowe = j;
                                        }

                                    }
                                }
                                if(nieprawidlowe == j)
                                {
                                    al_draw_filled_rectangle(749, 275, 1019, 350, color_prostokata);
                                    al_draw_text(info_font, color_napisu, 884, 275, ALLEGRO_ALIGN_CENTER, "Masz obowizkowe bicie!");
                                }
                            }
                        }
                    }
                    else
                    {
                        {
                            wybrany = wybierz_pionek(x, y, tab_pion, b_color);
                            int il_nieprawidlowych = 0;
                            if(bicia[0] != 9)
                            {
                                for (int iter = 0; iter < j; iter += 2)
                                {
                                    if(x != bicia[iter] || y != bicia[iter + 1])
                                    {
                                        il_nieprawidlowych += 2;
                                    }
                                }
                                if(il_nieprawidlowych == j)
                                {
                                    wybrany = 0;
                                    al_draw_filled_rectangle(749, 275, 1019, 350, color_prostokata);
                                    al_draw_text(info_font, color_napisu, 884, 275, ALLEGRO_ALIGN_CENTER, "Masz obowizkowe bicie!");
                                }
                            }
                            else
                            {
                                if(!mozliwosc_ruchu(x, y, tab_pion, b_color))
                                {
                                    wybrany = 0;
                                    al_draw_filled_rectangle(749, 275, 1019, 350, color_prostokata);
                                    al_draw_text(info_font, color_napisu, 884, 275, ALLEGRO_ALIGN_CENTER, "Brak mozliwosci ruchu!");
                                }
                            }

                        }
                        if(wybrany)
                        {
                            x_wybrany = x;
                            y_wybrany = y;
                        }
                        else
                        {
                            x_wybrany = NULL;
                            y_wybrany = NULL;
                        }
                    }
                }
                if(ev_game.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    if(wybrany)
                    {
                        wybrany = !wybrany;
                        x_wybrany = NULL;
                        y_wybrany = NULL;
                    }
                    else
                    {
                        if(esc_1)
                        {
                            game = 0;
                            x = 8;
                        }
                        else
                        {
                            al_draw_filled_rectangle(749, 400, 1019, 500, color_prostokata);
                            al_draw_text(menu_text, color_napisu, 884, 400, ALLEGRO_ALIGN_CENTER, "Chcesz wyjsc?");
                            al_draw_text(menu_text, color_napisu, 884, 440, ALLEGRO_ALIGN_CENTER, "Nacisnij ESC");
                            esc_1 = 1;
                        }
                    }
                }
                else
                {
                    esc_1 = 0;
                    al_draw_filled_rectangle(749, 400, 1019, 500, al_map_rgb(30, 115, 70));
                }
            }
            if( x < 8 && y < 8)
            {
                if(wybrany)
                {
                    al_draw_bitmap(kursor, 29 + 90 * x_wybrany, 29 + 90 * y_wybrany, NULL);
                }
                al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                rysuj_pionki(tab_pion);
                al_draw_text(menu_text, white, 900, 640, ALLEGRO_ALIGN_CENTER, "Zapisz (\"Z\")");
                al_draw_text(menu_text, white, 900, 690, ALLEGRO_ALIGN_CENTER, "Powrot (\"ESC\")");
            }
            else
            {
                if(y % 2 == 0)
                {
                    al_draw_text(menu_text, white, 900, 640, ALLEGRO_ALIGN_CENTER, "Zapisz (\"Z\")");
                    al_draw_text(menu_text, yellow, 900, 690, ALLEGRO_ALIGN_CENTER, "Powrot (\"ESC\")");
                    rysuj_pionki(tab_pion);
                }
                else
                {
                    al_draw_text(menu_text, yellow, 900, 640, ALLEGRO_ALIGN_CENTER, "Zapisz (\"Z\")");
                    al_draw_text(menu_text, white, 900, 690, ALLEGRO_ALIGN_CENTER, "Powrot (\"ESC\")");
                    rysuj_pionki(tab_pion);
                }
            }

        }
        else if(b_color == kolor_komputera)
        {
            ALLEGRO_BITMAP *szachownica = al_load_bitmap("szachownica.png");
            al_draw_filled_rectangle(749, 150, 1019, 200, color_prostokata);
            al_draw_textf(info_font, color_napisu, 886, 150, ALLEGRO_ALIGN_CENTER, "Ruch komputera");
            al_draw_text(menu_text, white, 900, 640, ALLEGRO_ALIGN_CENTER, "Zapisz (\"Z\")");
            al_draw_text(menu_text, white, 900, 690, ALLEGRO_ALIGN_CENTER, "Powrot (\"ESC\")");
            al_draw_filled_rectangle(749, 275, 1019, 350, al_map_rgb(30, 115, 70));
            if(bicia[0] != 9)
            {
                ruchy_damka = 0;
                struct pionek aktualny_pionek;
                for(int i = 0; i < 24; i++)
                {
                    if(tab_pion[i].x == bicia[0] && tab_pion[i].y == bicia[1] && !tab_pion[i].zbity && tab_pion[i].color == b_color)
                    {
                        aktualny_pionek = tab_pion[i];
                    }
                }
                if(aktualny_pionek.damka == 1)
                {
                    int znaleziony = 0, i = 1;
                    while(!znaleziony)
                    {
                        for(int iter = 0; iter < 24; iter++)
                        {
                            if(tab_pion[iter].x == aktualny_pionek.x + kierunek[0] * i && tab_pion[iter].y == aktualny_pionek.y + kierunek[1] * i && !tab_pion[iter].zbity && tab_pion[iter].color != b_color)
                            {
                                znaleziony = 1;
                            }
                        }
                        i ++;
                    }
                    x = aktualny_pionek.x + kierunek[0] * i ;
                    y = aktualny_pionek.y + kierunek[1] * i;
                    al_draw_bitmap(szachownica, 24, 24, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                    rysuj_pionki(tab_pion);
                    al_flip_display();
                    al_rest(1);
                    al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                    al_flip_display();
                    al_rest(1);
                    al_draw_bitmap(szachownica, 24, 24, NULL);
                    bij_damka(aktualny_pionek.x, aktualny_pionek.y, x, y, kierunek[0], kierunek[1], b_color, tab_pion, i - 1);
                    al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                    rysuj_pionki(tab_pion);
                    al_flip_display();
                    wyk_bicie_x = x;
                    wyk_bicie_y = y;
                    j = znajdz_bica(bicia, kierunek, tab_pion, b_color, wyk_bicie_x, wyk_bicie_y);
                    if(j == 0)
                    {
                        wyk_bicie_x = NULL;
                        wyk_bicie_y = NULL;
                        aktualnie_ruszajacy = !aktualnie_ruszajacy;
                    }
                }
                else if(aktualny_pionek.damka == 0)
                {
                    al_draw_bitmap(szachownica, 24, 24, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                    rysuj_pionki(tab_pion);
                    x = aktualny_pionek.x + 2 * kierunek[0];
                    y = aktualny_pionek.y + 2 * kierunek[1];
                    al_flip_display();
                    al_rest(1);
                    al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                    al_flip_display();
                    al_rest(1);
                    al_draw_bitmap(szachownica, 24, 24, NULL);
                    bij(aktualny_pionek.x, aktualny_pionek.y, x, y,
                     kierunek[0], kierunek[1], b_color, tab_pion);
                    rysuj_pionki(tab_pion);
                    al_flip_display();
                    al_rest(1);
                    al_flip_display();
                    wyk_bicie_x = x;
                    wyk_bicie_y = y;
                    if((aktualny_pionek.color == 0 && y == 7)|| (aktualny_pionek.color == 1 && y == 0))
                    {
                        bicie = 0;
                        aktualnie_ruszajacy = !aktualnie_ruszajacy;
                        wyk_bicie_x = NULL;
                        wyk_bicie_y = NULL;
                    }
                    else
                    {
                        j = znajdz_bica(bicia, kierunek, tab_pion, b_color, wyk_bicie_x, wyk_bicie_y);
                        if(j == 0)
                        {
                            wyk_bicie_x = NULL;
                            wyk_bicie_y = NULL;
                            aktualnie_ruszajacy = !aktualnie_ruszajacy;
                        }
                    }
                }
            }
            else
            {
                int kierunki_ruchow[] = {1, 1,
                                         1, -1,
                                         -1, 1,
                                         -1, -1};
                struct pionek aktualny_pionek;
                aktualny_pionek.x = 9;
                for(int i = temp_i; i < 24; i++)
                {
                    if(tab_pion[i].color == b_color && mozliwosc_ruchu(tab_pion[i].x, tab_pion[i].y, tab_pion, b_color) && aktualny_pionek.x == 9 && !tab_pion[i].zbity)
                    {
                        aktualny_pionek = tab_pion[i];
                        temp_i = i + 4;
                    }
                }
                for(int i = 0; i < 24; i++)
                {
                    if(tab_pion[i].color == b_color && mozliwosc_ruchu(tab_pion[i].x, tab_pion[i].y, tab_pion, b_color) && !tab_pion[i].damka && !tab_pion[i].zbity)
                    {
                        if(b_color == 0 && tab_pion[i].y >= 6)
                        {
                            aktualny_pionek = tab_pion[i];
                        }
                        if(b_color == 1 && tab_pion[i].y <= 2)
                        {
                            aktualny_pionek = tab_pion [i];
                        }
                    }
                }
                if(aktualny_pionek.x == 9)
                {
                    for(int i = 0; i < 24; i++)
                    {
                        if(tab_pion[i].color == b_color && mozliwosc_ruchu(tab_pion[i].x, tab_pion[i].y, tab_pion, b_color) && aktualny_pionek.x == 9 && !tab_pion[i].zbity)
                        {
                            aktualny_pionek = tab_pion[i];
                            temp_i = i + 3;
                        }
                    }
                }
                if(aktualny_pionek.damka)
                {
                    int i = 0, ruszony = 0, il_pol = 0, ostatnie_i, Maks = 0;
                    for(i  = 0; i < 8; i +=2)
                    {
                        int PRAWDA = 1, il_pol = 1;
                        while(PRAWDA)
                        {
                            int x_while = aktualny_pionek.x + kierunki_ruchow[i] * il_pol;
                            int y_while = aktualny_pionek.y + kierunki_ruchow[i + 1] * il_pol;
                            if(ruch_dozwolony(aktualny_pionek.x, aktualny_pionek.y, x_while, y_while, b_color, tab_pion) && x_while < 7 && x_while >=0 && y_while < 7 && y_while >=0)
                            {
                                il_pol ++;
                            }
                            else
                            {
                                PRAWDA = 0;
                            }

                        }
                        if(il_pol > Maks)
                        {
                            Maks = il_pol;
                            ostatnie_i = i;
                            temp_kierunku = i + 2;
                        }
                    }
                    ruchy_damka ++;
                    temp_i++;
                    x = aktualny_pionek.x + (Maks - 1) * kierunki_ruchow[ostatnie_i];
                    y = aktualny_pionek.y + (Maks - 1) * kierunki_ruchow[ostatnie_i + 1];
                    al_draw_bitmap(szachownica, 24, 24, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                    rysuj_pionki(tab_pion);
                    al_flip_display();
                    al_rest(1);
                    al_draw_bitmap(szachownica, 24, 24, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                    rysuj_pionki(tab_pion);
                    al_flip_display();
                    al_rest(1);
                    al_draw_bitmap(szachownica, 24, 24, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                    al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                    rusz(aktualny_pionek.x, aktualny_pionek.y, x, y, b_color, tab_pion);
                    rysuj_pionki(tab_pion);
                    al_flip_display();
                    aktualnie_ruszajacy = !aktualnie_ruszajacy;

                }
                else
                {
                    ruchy_damka = 0;
                    int ruszony = 0;
                    for (int i = temp_kierunku; i < 8 && !ruszony; i += 2)
                    {
                        if(ruch_dozwolony(aktualny_pionek.x, aktualny_pionek.y, aktualny_pionek.x + kierunki_ruchow[i],
                         aktualny_pionek.y + kierunki_ruchow[i + 1], b_color, tab_pion))
                         {
                            x = aktualny_pionek.x + kierunki_ruchow[i];
                            y = aktualny_pionek.y + kierunki_ruchow [i + 1];
                            al_draw_bitmap(szachownica, 24, 24, NULL);
                            al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                            rysuj_pionki(tab_pion);
                            al_flip_display();
                            al_rest(1);
                            al_draw_bitmap(szachownica, 24, 24, NULL);
                            al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                            al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                            rysuj_pionki(tab_pion);
                            al_flip_display();
                            al_rest(1);
                            al_draw_bitmap(szachownica, 24, 24, NULL);
                            al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                            al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                            rusz(aktualny_pionek.x, aktualny_pionek.y, aktualny_pionek.x + kierunki_ruchow[i],
                                aktualny_pionek.y + kierunki_ruchow[i + 1], b_color, tab_pion);
                            rysuj_pionki(tab_pion);
                            al_flip_display();
                            ruszony = 1;
                            temp_kierunku = i + 1;
                         }

                    }
                    if(!ruszony)
                    {
                        for (int i = 0; i < 8 && !ruszony; i += 2)
                        {
                            if(ruch_dozwolony(aktualny_pionek.x, aktualny_pionek.y, aktualny_pionek.x + kierunki_ruchow[i],
                             aktualny_pionek.y + kierunki_ruchow[i + 1], b_color, tab_pion))
                             {
                                x = aktualny_pionek.x + kierunki_ruchow[i];
                                y = aktualny_pionek.y + kierunki_ruchow [i + 1];
                                al_draw_bitmap(szachownica, 24, 24, NULL);
                                al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                                rysuj_pionki(tab_pion);
                                al_flip_display();
                                al_rest(2);
                                al_draw_bitmap(szachownica, 24, 24, NULL);
                                al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                                al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                                rysuj_pionki(tab_pion);
                                al_flip_display();
                                al_rest(2);
                                rusz(aktualny_pionek.x, aktualny_pionek.y, aktualny_pionek.x + kierunki_ruchow[i],
                                    aktualny_pionek.y + kierunki_ruchow[i + 1], b_color, tab_pion);
                                al_draw_bitmap(szachownica, 24, 24, NULL);
                                al_draw_bitmap(kursor, 29 + 90 * aktualny_pionek.x, 29 + 90 * aktualny_pionek.y, NULL);
                                al_draw_bitmap(kursor, 29 + 90 * x, 29 + 90 * y, NULL);
                                rysuj_pionki(tab_pion);
                                al_flip_display();
                                al_flip_display();
                                aktualny_pionek.y + kierunki_ruchow[i + 1];
                                ruszony = 1;
                                temp_kierunku = i + 1;
                             }

                        }
                    }
                    temp_i++;
                    aktualnie_ruszajacy = !aktualnie_ruszajacy;
                    al_destroy_bitmap(szachownica);
                }
            }

        }
        if(wszystkie_zbite(tab_pion))
        {
            game = 0;
            x = wszystkie_zbite(tab_pion);
        }
        else if(brak_ruchow(tab_pion) && bicia[0] == 9)
        {
            if(brak_ruchow(tab_pion) == 11 && aktualnie_ruszajacy == 0)
            {
                game = 0;
                x = 10;
            }
            if(brak_ruchow(tab_pion) == 10 && aktualnie_ruszajacy == 1)
            {
                game = 0;
                x = 11;
            }
        }
        else if(ruchy_damka == 30)
        {
            game = 0;
            x = 9;
        }
        al_flip_display();
    }
    al_destroy_event_queue(event_queue_game);
    al_destroy_bitmap(szachownica);
    if(x == 9)
    {
        al_clear_to_color(al_map_rgb(30, 115, 70));
        al_draw_text(title, white, 512, 300, ALLEGRO_ALIGN_CENTER, "REMIS");
        al_flip_display();
        al_rest(5);
        main_menu();

    }
    if (x == 8)
    {
        main_menu();
    }
    if(x == 11)
    {
        al_clear_to_color(white);
        al_draw_text(title, yellow, 512, 200, ALLEGRO_ALIGN_CENTER, "WYGRALY");
        al_draw_text(title, yellow, 512, 350, ALLEGRO_ALIGN_CENTER, "BIALE");
        al_flip_display();
        al_rest(5);
        main_menu();
    }
    if(x == 10)
    {
        al_clear_to_color(red);
        al_draw_text(title, yellow, 512, 200, ALLEGRO_ALIGN_CENTER, "WYGRALY");
        al_draw_text(title, yellow, 512, 350, ALLEGRO_ALIGN_CENTER, "CZERWONE");
        al_flip_display();
        al_rest(5);
        main_menu();
    }
}
