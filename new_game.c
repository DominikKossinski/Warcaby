#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro_font.h>
#include <allegro_ttf.h>
#include <string.h>
#include "game.h"
char opcje[3][30] = {"Gracz_1 vs Gracz_2", "Gracz_1 vs Komputer", "Powrot"};
char kolory[2][8] = {"Bialy" , "Czerwony"};

///Otwiera menu wyboru rodzaju gry oraz koloru pionkow
void new_game()
{
    ALLEGRO_COLOR backgroundc = al_map_rgb(30, 115, 70);
    al_clear_to_color(backgroundc);
    int act_option = 0, act_color = 0;
    game_options(act_option, act_color);
    al_flip_display();
    ALLEGRO_EVENT_QUEUE *event_queue_ng = al_create_event_queue();
    al_register_event_source(event_queue_ng, al_get_keyboard_event_source());
    int game_stop = 0, begin_g = 0;
    while (!game_stop)
    {
        ALLEGRO_EVENT new_geme_ev;
        al_wait_for_event(event_queue_ng, &new_geme_ev);
        if(new_geme_ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(new_geme_ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                break;
            }
            if(new_geme_ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                act_option++;
                if(act_option > 2)
                {
                    act_option = 0;
                }
                game_options(act_option, act_color);
            }
            if(new_geme_ev.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                act_option--;
                if(act_option < 0)
                {
                    act_option = 2;
                }
                game_options(act_option, act_color);
            }
            if(new_geme_ev.keyboard.keycode == ALLEGRO_KEY_LEFT ||
                new_geme_ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            {
                act_color = !act_color;
                game_options(act_option, act_color);
            }
            if(new_geme_ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                if(act_option == 2)
                {
                    break;
                }
                else
                {
                    begin_g = 1;
                    break;
                }
            }

        }
    }
    al_destroy_event_queue(event_queue_ng);
    if (begin_g)
    {
        begin_game(act_option, act_color);
    }
    else
    {
        main_menu();
    }

}

///Rysuje aktualny stan menu new_game na ekrnanie
void game_options(int actual_option, int actual_color)
{
    ALLEGRO_FONT *title = al_load_ttf_font("fonts/Jelly Crazies.ttf", 72 , 0);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 52, 0);
    ALLEGRO_COLOR backgroundc = al_map_rgb(30, 115, 70);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR  white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    if (!title)
    {
        fprintf(stderr, "Could not load 'Jelly Crazies.ttf'");
    }
    if (!menu_text)
    {
        fprintf(stderr, "Could not load 'Maritime_Tropical_Neue.ttf'.");
    }
    al_clear_to_color(backgroundc);
    al_draw_text(title, white, 512, 0, ALLEGRO_ALIGN_CENTER, "WARCABY");
    for (int i = 0; i <= 2; i++)
    {
        if(i != 2)
        {
            if(i != actual_option)
            {
                al_draw_text(menu_text, white, 512, 200 + i * 75, ALLEGRO_ALIGN_CENTER, opcje[i]);
            }
            else
            {
                al_draw_text(menu_text, yellow, 512, 200 + i * 75, ALLEGRO_ALIGN_CENTER, opcje[i]);
            }
        }
        else
        {
            if(i != actual_option)
            {
                al_draw_text(menu_text, white, 512, 690, ALLEGRO_ALIGN_CENTER, opcje[i]);
            }
            else
            {
                al_draw_text(menu_text, yellow, 512, 690, ALLEGRO_ALIGN_CENTER, opcje[i]);
            }
        }

    }
    al_draw_text(menu_text, white, 512, 425, ALLEGRO_ALIGN_CENTER, "Wybierz kolor dla gracza_1");
    if(actual_color == 0)
    {
        al_draw_text(menu_text, yellow, 400, 500, ALLEGRO_ALIGN_CENTER, kolory[0]);
        al_draw_text(menu_text, red, 624, 500, ALLEGRO_ALIGN_CENTER, kolory[1]);
    }
    else
    {
        al_draw_text(menu_text, white, 400, 500, ALLEGRO_ALIGN_CENTER, kolory[0]);
        al_draw_text(menu_text, yellow, 624, 500, ALLEGRO_ALIGN_CENTER, kolory[1]);
    }
    al_flip_display();
}
