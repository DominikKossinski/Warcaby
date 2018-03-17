#include "struct_pionek.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

///Sprawdza czy mozna wybrac dany pionek
int wybierz_pionek(int x, int y, struct pionek *tab_pion, int color)
{
    for (int i = 0; i < 24; i++)
    {
        if(x == tab_pion[i].x && y == tab_pion[i].y && color == tab_pion[i].color && !tab_pion[i].zbity)
        {
            return 1;
        }
    }
    return 0;
}

///Rusza z pozycji aktualnej pionka na x, y na ktorym jest kursor
void rusz(int x_wybrany, int y_wybrany, int x, int y, int color, struct pionek *tab_pion)
{
    int aktualny = -1;
    for (int i = 0; i < 24; i++)
    {
        if(x_wybrany == tab_pion[i].x && tab_pion[i].y == y_wybrany && !tab_pion[i].zbity && tab_pion[i].color == color)
        {
            aktualny = i;

        }
    }
    if(aktualny != -1)
    {
        tab_pion[aktualny].x = x;
        tab_pion[aktualny].y = y;
        if(!color)
        {
            if (y == 7)
            {
                tab_pion[aktualny].damka = 1;
            }
        }
        else
        {
            if(y == 0)
            {
                tab_pion[aktualny].damka = 1;
            }
        }
    }
}

///Sprawdza czy dany pionek ma mozliosc ruchy (nie uwzglednia bic)
int mozliwosc_ruchu(int x, int y, struct pionek *tab_pion, int color)
{
    int znalezione = 0;
    struct pionek aktualny_pionek;
    aktualny_pionek.x = 9;
    aktualny_pionek.y = 9;
    aktualny_pionek.color = 9;
    aktualny_pionek.damka = 9;
    aktualny_pionek.zbity = 9;
    for (int i = 0; i < 24; i++)
    {
        if(x == tab_pion[i].x && tab_pion[i].y == y && !tab_pion[i].zbity && tab_pion[i].color == color)
        {
            aktualny_pionek = tab_pion[i];
        }
    }
    if(aktualny_pionek.x == 9)
    {
        return 0;
    }
    else
    {
        int kolidujace = 0;
        for (int i = 0; i < 24; i++)
        {
            if(!aktualny_pionek.damka)
            {
                if(!color)
                {
                    if(x - 1 == tab_pion[i].x && y + 1 == tab_pion[i].y && !tab_pion[i].zbity)
                    {
                        kolidujace++;
                    }
                    if(x + 1 == tab_pion[i].x && y + 1 == tab_pion[i].y && !tab_pion[i].zbity)
                    {
                        kolidujace++;
                    }

                }
                else
                {
                    if(x - 1 == tab_pion[i].x && y - 1 == tab_pion[i].y && !tab_pion[i].zbity)
                    {
                        kolidujace++;
                    }
                    if(x + 1 == tab_pion[i].x && y - 1 == tab_pion[i].y && !tab_pion[i].zbity)
                    {
                        kolidujace++;
                    }
                }
                if((aktualny_pionek.x == 0 || aktualny_pionek.x == 7) && kolidujace == 1)
                {
                    return 0;
                }
                if(kolidujace == 2)
                {
                    return 0;
                }
            }
            else
            {
                if(x - 1 == tab_pion[i].x && y + 1 == tab_pion[i].y && !tab_pion[i].zbity)
                {
                    kolidujace++;
                }
                if(x + 1 == tab_pion[i].x && y + 1 == tab_pion[i].y && !tab_pion[i].zbity)
                {
                    kolidujace++;
                }
                if(x - 1 == tab_pion[i].x && y - 1 == tab_pion[i].y && !tab_pion[i].zbity)
                {
                    kolidujace++;
                }
                if(x + 1 == tab_pion[i].x && y - 1 == tab_pion[i].y && !tab_pion[i].zbity)
                {
                    kolidujace++;
                }
                if(kolidujace == 4)
                {
                    return 0;
                }
            }
        }
        return 1;
    }
}

///Sprawza czy ruch, ktory gracz probuje wykonac jest dozwolony
int ruch_dozwolony(int x_wybrany, int y_wybrany, int x, int y, int color, struct pionek *tab_pion)
{
    if(x > 7 || x < 0 || y > 7 || y < 0)
    {
        return 0;
    }
    int aktualny = -1;
    for (int i = 0; i < 24; i++)
    {
        if(x_wybrany == tab_pion[i].x && tab_pion[i].y == y_wybrany && !tab_pion[i].zbity && tab_pion[i].color == color)
        {
            aktualny = i;

        }
    }
    if(aktualny == -1)
    {
        return 0;
    }
    else
    {
        if(!tab_pion[aktualny].damka)
        {
            if(!color)
            {
                if((x_wybrany + 1 == x && x < 8 && y_wybrany + 1 == y) || (x_wybrany - 1 == x && y_wybrany + 1 == y))
                {
                    for(int i = 0; i < 24; i++)
                    {
                        if(tab_pion[i].x == x && tab_pion[i].y == y && !tab_pion[i].zbity)
                        {
                            return 0;
                        }
                    }
                }
                else
                {
                        return 0;
                }
            }
            else
            {
                if((x_wybrany + 1 == x || x_wybrany - 1 == x) && x < 8 && y_wybrany - 1 == y)
                {
                    for(int i = 0; i < 24; i++)
                    {
                        if(tab_pion[i].x == x && tab_pion[i].y == y && !tab_pion[i].zbity)
                        {
                            return 0;
                        }
                    }
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            if(x_wybrany == x || y_wybrany == y)
            {
                return 0;
            }
            int ok = 0;
            if(x_wybrany < x && y_wybrany < y)
            {
                for(int i = 1; x_wybrany + i <= x && y_wybrany + i <= y; i++)
                {
                    for (int p = 0; p < 24; p++)
                    {
                        if(tab_pion[p].x == x_wybrany + i && tab_pion[p].y == y_wybrany + i && !tab_pion[p].zbity)
                        {
                            return 0;
                        }
                    }
                    if(x_wybrany + i == x && y_wybrany + i == y)
                    {
                        ok = 1;
                    }
                }
            }
            if(x_wybrany < x && y_wybrany > y)
            {
                for(int i = 1; x_wybrany + i <= x && y_wybrany - i >= y; i++)
                {
                    for (int p = 0; p < 24; p++)
                    {
                        if(tab_pion[p].x == x_wybrany + i && tab_pion[p].y == y_wybrany - i && !tab_pion[p].zbity)
                        {
                            return 0;
                        }
                    }
                    if(x_wybrany + i == x && y_wybrany - i == y)
                    {
                        ok =1;
                    }
                }
            }
            if(x_wybrany > x && y_wybrany < y)
            {
                for(int i = 1; x_wybrany - i >= x && y_wybrany + i <= y; i++)
                {
                    for (int p = 0; p < 24; p++)
                    {
                        if(tab_pion[p].x == x_wybrany - i && tab_pion[p].y == y_wybrany + i && !tab_pion[p].zbity)
                        {
                            return 0;
                        }
                    }
                    if (x_wybrany - i == x && y_wybrany + i == y)
                    {
                        ok = 1;
                    }
                }
            }
            if(x_wybrany > x && y_wybrany > y)
            {
                for(int i = 1; x_wybrany - i >= x && y_wybrany - i >= y; i++)
                {
                    for (int p = 0; p < 24; p++)
                    {
                        if(tab_pion[p].x == x_wybrany - i && tab_pion[p].y == y_wybrany - i && !tab_pion[p].zbity)
                        {
                            return 0;
                        }
                    }
                    if (x_wybrany - i == x && y_wybrany - i == y)
                    {
                        ok = 1;
                    }

                }
            }
            if(!ok)
            {
                return 0;
            }
        }
    }
    return 1;
}

///Realizuje bicie pionkiem
void bij(int x_wybrany, int y_wybrany, int x, int y, int kierunek_x, int kierunek_y, int color, struct pionek *tab_pion)
{
    for (int i = 0; i < 24; i++)
    {
        if(tab_pion[i].x == x_wybrany && tab_pion[i].y == y_wybrany)
        {
            rusz(x_wybrany, y_wybrany, x, y, color, tab_pion);
        }
        if(tab_pion[i].x == x_wybrany + kierunek_x && tab_pion[i].y == y_wybrany + kierunek_y && !tab_pion[i].zbity && tab_pion[i].color != color)
        {
            tab_pion[i].zbity = 1;
        }
    }
}

///Realizuje bicie damka
void bij_damka(int x_wybrany, int y_wybrany, int x, int y, int kierunek_x, int kierunek_y, int color, struct pionek *tab_pion, int temp_i)
{
    for (int i = 0; i < 24; i ++)
    {
        if(tab_pion[i].x == x_wybrany && tab_pion[i].y == y_wybrany)
        {
            rusz(x_wybrany, y_wybrany, x, y, color, tab_pion);
        }
        if(tab_pion[i].x == x_wybrany + kierunek_x * temp_i && tab_pion[i].y == y_wybrany + kierunek_y * temp_i && !tab_pion[i].zbity && tab_pion[i].color != color)
        {
            tab_pion[i].zbity = 1;
        }

    }
}

///Sprawdza czy poszczegolny gracz ma chociaz jeden nie zbity pionek
int wszystkie_zbite(struct pionek *tab_pion)
{
    int liczba_b = 0, liczba_c = 0;
    for(int i = 0; i < 24; i++)
    {
        if(tab_pion[i].zbity && tab_pion[i].color == 0)
        {
            liczba_b ++;
        }
        if(tab_pion[i].zbity && tab_pion[i].color == 1)
        {
            liczba_c ++;
        }

    }
    if(liczba_b == 12 && liczba_c == 12)
    {
        return 9;
    }
    else
    {
        if(liczba_b == 12)
        {
            return 10;
        }
        if(liczba_c == 12)
        {
            return 11;
        }
    }
    return 0;
}

///Sprawdza przy ruchu damka czy x oraz y leza po skosie od pozycji damki
int sprawdz_xy(int x_wybrany, int y_wybrany, int x, int y)
{
    int ok = 0;
    if(x_wybrany < x && y_wybrany < y)
    {
        for(int i = 1; x_wybrany + i <= x && y_wybrany + i <= y; i++)
        {
            if(x_wybrany + i == x && y_wybrany + i == y)
            {
                ok = 1;
            }
        }
    }
    if(x_wybrany < x && y_wybrany > y)
    {
        for(int i = 1; x_wybrany + i <= x && y_wybrany - i >= y; i++)
        {
            if(x_wybrany + i == x && y_wybrany - i == y)
            {
                ok =1;
            }
        }
    }
    if(x_wybrany > x && y_wybrany < y)
    {
        for(int i = 1; x_wybrany - i >= x && y_wybrany + i <= y; i++)
        {
            if (x_wybrany - i == x && y_wybrany + i == y)
            {
                ok = 1;
            }
        }
    }
    if(x_wybrany > x && y_wybrany > y)
    {
        for(int i = 1; x_wybrany - i >= x && y_wybrany - i >= y; i++)
        {
            if (x_wybrany - i == x && y_wybrany - i == y)
            {
                ok = 1;
            }

        }
    }
    return ok;
}

///Sprawdza czy gracz ma jaki kolwie ruch (nie uwzglednia bic)
int brak_ruchow(struct pionek *tab_pionek)
{
    int liczba_zablokowanych_b = 0, liczba_zablokowanych_c = 0;
    for (int i = 0; i < 24; i++)
    {
        if(!mozliwosc_ruchu(tab_pionek[i].x, tab_pionek[i].y, tab_pionek, tab_pionek[i].color) && tab_pionek[i].color == 0)
        {
            liczba_zablokowanych_b ++;
        }
        if(!mozliwosc_ruchu(tab_pionek[i].x, tab_pionek[i].y, tab_pionek, tab_pionek[i].color) && tab_pionek[i].color == 1)
        {
            liczba_zablokowanych_c ++;
        }
    }
    if(liczba_zablokowanych_b == 12 && liczba_zablokowanych_c == 12)
    {
        return 9; ///Remis
    }
    if(liczba_zablokowanych_b  == 12)
    {
        return 10; ///Czerwony wygral
    }
    if(liczba_zablokowanych_c == 12)
    {
        return 11; ///Bialy wygral
    }
    return 0;
}
