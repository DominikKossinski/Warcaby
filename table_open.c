#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro_font.h>
#include <allegro_ttf.h>
#include <string.h>
#include <allegro_primitives.h>
void open_table()
{
    fprintf(stderr, "Otworzono tablice wynikow");
    ALLEGRO_COLOR backgroundc = al_map_rgb(30, 115, 70);
    ALLEGRO_FONT *title = al_load_ttf_font("fonts/arial-black.ttf", 72 , 0);
    ALLEGRO_FONT *menu_text = al_load_ttf_font("fonts/Maritime_Tropical_Neue.ttf", 32 , 0);
    if (!title)
    {
        fprintf(stderr, "Could not load 'arial-black.ttf'");
    }
    ALLEGRO_COLOR  white = al_map_rgb(255, 255, 255);
    if (!menu_text)
    {
        fprintf(stderr, "Could not load 'Maritime_Tropical_Neue.ttf'.");
    }
    al_clear_to_color(backgroundc);
    al_draw_text(title, white, 512, 0, ALLEGRO_ALIGN_CENTER, "WARCABY");
    fill_table(menu_text, white);
    draw_table();
    powrot_do_menu(menu_text, white);
    al_flip_display();
    main_menu();

}
void powrot_do_menu(ALLEGRO_FONT *font, ALLEGRO_COLOR white)
{
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    int act_powrot = 0;
    al_draw_text(font, white, 512, 690, ALLEGRO_ALIGN_CENTER, "Powrot");
    al_flip_display();
    ALLEGRO_EVENT_QUEUE *event_queue_table = al_create_event_queue();
    al_register_event_source(event_queue_table, al_get_keyboard_event_source());
    while(1)
    {
        ALLEGRO_EVENT table_ev;
        al_wait_for_event(event_queue_table, &table_ev);
        if(table_ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(table_ev.keyboard.keycode == ALLEGRO_KEY_DOWN ||
                table_ev.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                    act_powrot = !act_powrot;
                    if(act_powrot)
                    {
                        al_draw_text(font, yellow, 512, 690, ALLEGRO_ALIGN_CENTER, "Powrot");
                    }
                    else
                    {
                        al_draw_text(font, white, 512, 690, ALLEGRO_ALIGN_CENTER, "Powrot");
                    }
                    al_flip_display();
                }
            if((table_ev.keyboard.keycode == ALLEGRO_KEY_ENTER && act_powrot)
                || table_ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                break;
            }
        }
    }
    al_destroy_event_queue(event_queue_table);
}

void fill_table(ALLEGRO_FONT *font, ALLEGRO_COLOR color)
{
    FILE *table = fopen("table.txt", "r");
    char pisz[101];
    if ( table == NULL)
    {
        fprintf(stderr, "Blad ladowania rules.txt'");
        al_draw_text(font, color, 512, 384, ALLEGRO_ALIGN_CENTER, "Blad ladowania tabeli.");
    }
    else
    {
        int i = 0;
        char nazwa_gracza[50], il_ruchow[50];
        while (fgets(pisz, 100, table) != NULL)
        {
            int j=0;
            while(pisz[j] != ';')
            {
                nazwa_gracza[j] = pisz[j];
                j++;
            }
            for (int z = j; z < 50; z++)
            {
                nazwa_gracza[z]='\0';
            }
            j++;
            int a = 0;
            while(pisz[j] != '\0')
            {
                il_ruchow[a] = pisz[j];
                j++;
                a++;
            }
            for (int z=a-1; z < 50; z++)
            {
                il_ruchow[z] = '\0';
            }
            al_draw_text(font, color, 350, 150 + i * 50, ALLEGRO_ALIGN_CENTER, nazwa_gracza);
            al_draw_text(font, color, 674, 150 + i * 50, ALLEGRO_ALIGN_CENTER, il_ruchow);
            i++;
        }
    }
    al_flip_display();
}

void draw_table()
{
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    for (int i = 0 ; i <= 10; i++)
    {
        al_draw_line(200, 150 + 50 * i, 824, 150 + 50 * i, black, 5.0);
    }
    for (int i = 0 ; i < 3; i++)
    {
        al_draw_line(200 + i * 312, 150, 200 + i * 312, 650, black, 5.0);
    }
}
