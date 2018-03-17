#include "struct_pionek.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

int znajdz_bica(int *bicia, int *kierunek, struct pionek *tab_pion, int b_color, int wyk_bicie_x, int wyk_bicie_y)
{
    int j = 0;
    for(int i = 0; i < 48; i++)
            {
                bicia[i] = 9;
                kierunek[i] = 0;
            }
    for(int i = 0; i < 24; i ++)
    {
        if(tab_pion[i].color == b_color && !tab_pion[i].zbity)
        {
            if(!tab_pion[i].damka)
            {
                for(int a = 0; a < 24; a++)
                {
                    int tab_bic[]={1, 1,
                                    -1, -1,
                                    -1, 1,
                                    1, -1};
                    for(int c = 0; c < 8; c += 2)
                    {
                        if(tab_pion[i].x + tab_bic[c] == tab_pion[a].x && tab_pion[i].y + tab_bic[c + 1] == tab_pion[a].y &&
                            tab_pion[i].color != tab_pion[a].color && !tab_pion[a].zbity)
                        {
                            if((tab_pion[i].x + 2 * tab_bic[c]) < 8 && (tab_pion[i].y + 2 * tab_bic[c + 1]) < 8
                                && (tab_pion[i].x + 2 * tab_bic[c]) >= 0 && (tab_pion[i].y + 2 * tab_bic[c + 1]) >= 0)
                            {
                                int b, o = 0;
                                for (b = 0; b < 24; b ++)
                                {
                                    if(tab_pion[i].x + 2 * tab_bic[c] == tab_pion[b].x && tab_pion[i].y + 2 * tab_bic[c + 1] == tab_pion [b].y && !tab_pion[b].zbity)
                                    {
                                        o++;
                                    }
                                }
                                if(o == 0)
                                {
                                    if (wyk_bicie_x == NULL && wyk_bicie_y == NULL)
                                    {
                                        bicia[j] = tab_pion[i].x;
                                        bicia[j + 1] = tab_pion[i].y;
                                        kierunek[j] = tab_bic[c];
                                        kierunek[j + 1] = tab_bic[c + 1];
                                        j += 2;
                                    }
                                    else
                                    {
                                        if(wyk_bicie_x == tab_pion[i].x && wyk_bicie_y == tab_pion[i].y)
                                        {
                                            bicia[j] = tab_pion[i].x;
                                            bicia[j + 1] = tab_pion[i].y;
                                            kierunek[j] = tab_bic[c];
                                            kierunek[j + 1] = tab_bic[c + 1];
                                            j += 2;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                ///Bicie1 1 1
                int c = 1, il_miedzy = 0, temp_c = -1, mozliwosc_bicia = 1;
                while (tab_pion[i].x + c < 8 && tab_pion[i].y + c < 8 && mozliwosc_bicia)
                {
                    for(int a = 0; a < 24; a++)
                    {
                        if(tab_pion[a].x == tab_pion[i].x + c && tab_pion[i].y + c == tab_pion[a].y && !tab_pion[a].zbity
                        && tab_pion[i].color != tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            temp_c = c;
                            il_miedzy++;
                        }
                        if(tab_pion[a].x == tab_pion[i].x + c && tab_pion[i].y + c == tab_pion[a].y
                        && !tab_pion[a].zbity && tab_pion[i].color == tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    c++;
                }
                if (il_miedzy != 1)
                {
                    mozliwosc_bicia = 0;
                }
                if(il_miedzy == 1 && mozliwosc_bicia)
                {
                    for(int b = 0; b < 24 && mozliwosc_bicia; b++)
                    {
                        if(tab_pion[i].x + temp_c + 1 < 8 && tab_pion[i].x + temp_c + 1 == tab_pion[b].x
                        && tab_pion[i].y + temp_c + 1 < 8 && tab_pion[i].y + temp_c + 1 == tab_pion[b].y
                        && !tab_pion[b].zbity)
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    if(tab_pion[i].x + temp_c + 1 > 7 || tab_pion[i].y + temp_c + 1 > 7)
                    {
                        mozliwosc_bicia = 0;
                    }
                }
                if(mozliwosc_bicia && il_miedzy == 1)
                {
                    if (wyk_bicie_x == NULL && wyk_bicie_y == NULL)
                    {
                        bicia[j] = tab_pion[i].x;
                        bicia[j + 1] = tab_pion[i].y;
                        kierunek[j] = 1;
                        kierunek[j + 1] = 1;
                        j += 2;
                    }
                    else
                    {
                        if(wyk_bicie_x == tab_pion[i].x && wyk_bicie_y == tab_pion[i].y)
                        {
                            bicia[j] = tab_pion[i].x;
                            bicia[j + 1] = tab_pion[i].y;
                            kierunek[j] = 1;
                            kierunek[j + 1] = 1;
                            j += 2;
                        }
                    }
                }
                ///Bicie2 1 -1
                c = 1, il_miedzy = 0, temp_c = -1, mozliwosc_bicia = 1;
                while (tab_pion[i].x + c < 8 && tab_pion[i].y - c >= 0 && mozliwosc_bicia)
                {
                    for(int a = 0; a < 24; a++)
                    {
                        if(tab_pion[a].x == tab_pion[i].x + c && tab_pion[i].y - c == tab_pion[a].y && !tab_pion[a].zbity
                        && tab_pion[i].color != tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            temp_c = c;
                            il_miedzy++;
                        }
                        if(tab_pion[a].x == tab_pion[i].x + c && tab_pion[i].y - c == tab_pion[a].y
                        && !tab_pion[a].zbity && tab_pion[i].color == tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    c++;
                }
                if (il_miedzy != 1)
                {
                    mozliwosc_bicia = 0;
                }
                if(il_miedzy == 1 && mozliwosc_bicia)
                {
                    for(int b = 0; b < 24 && mozliwosc_bicia; b++)
                    {
                        if(tab_pion[i].x + temp_c + 1 < 8 && tab_pion[i].x + temp_c + 1 == tab_pion[b].x
                        && tab_pion[i].y - temp_c - 1 >= 0 && tab_pion[i].y - temp_c - 1 == tab_pion[b].y
                        && !tab_pion[b].zbity)
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    if(tab_pion[i].x + temp_c + 1 > 7 || tab_pion[i].y - temp_c - 1 < 0)
                    {
                        mozliwosc_bicia = 0;
                    }
                }
                if(mozliwosc_bicia && il_miedzy == 1)
                {
                    if (wyk_bicie_x == NULL && wyk_bicie_y == NULL)
                    {
                        bicia[j] = tab_pion[i].x;
                        bicia[j + 1] = tab_pion[i].y;
                        kierunek[j] = 1;
                        kierunek[j + 1] = -1;
                        j += 2;
                    }
                    else
                    {
                        if(wyk_bicie_x == tab_pion[i].x && wyk_bicie_y == tab_pion[i].y)
                        {
                            bicia[j] = tab_pion[i].x;
                            bicia[j + 1] = tab_pion[i].y;
                            kierunek[j] = 1;
                            kierunek[j + 1] = -1;
                            j += 2;
                        }
                    }
                }
                ///Bicie3 -1 1
                c = 1, il_miedzy = 0, temp_c = -1, mozliwosc_bicia = 1;
                while (tab_pion[i].x - c >= 0 && tab_pion[i].y + c < 8 && mozliwosc_bicia)
                {
                    for(int a = 0; a < 24; a++)
                    {
                        if(tab_pion[a].x == tab_pion[i].x - c && tab_pion[i].y + c == tab_pion[a].y && !tab_pion[a].zbity
                        && tab_pion[i].color != tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            temp_c = c;
                            il_miedzy++;
                        }
                        if(tab_pion[a].x == tab_pion[i].x - c && tab_pion[i].y + c == tab_pion[a].y
                        && !tab_pion[a].zbity && tab_pion[i].color == tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    c++;
                }
                if (il_miedzy != 1)
                {
                    mozliwosc_bicia = 0;
                }
                if(il_miedzy == 1 && mozliwosc_bicia)
                {
                    for(int b = 0; b < 24 && mozliwosc_bicia; b++)
                    {
                        if(tab_pion[i].x - temp_c - 1 >= 0 && tab_pion[i].x - temp_c - 1 == tab_pion[b].x
                        && tab_pion[i].y + temp_c + 1 < 8 && tab_pion[i].y + temp_c + 1 == tab_pion[b].y
                        && !tab_pion[b].zbity)
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    if(tab_pion[i].x - temp_c - 1 < 0 || tab_pion[i].y + temp_c + 1 > 7)
                    {
                        mozliwosc_bicia = 0;
                    }
                }
                if(mozliwosc_bicia && il_miedzy == 1)
                {
                    if (wyk_bicie_x == NULL && wyk_bicie_y == NULL)
                    {
                        bicia[j] = tab_pion[i].x;
                        bicia[j + 1] = tab_pion[i].y;
                        kierunek[j] = -1;
                        kierunek[j + 1] = 1;
                        j += 2;
                    }
                    else
                    {
                        if(wyk_bicie_x == tab_pion[i].x && wyk_bicie_y == tab_pion[i].y)
                        {
                            bicia[j] = tab_pion[i].x;
                            bicia[j + 1] = tab_pion[i].y;
                            kierunek[j] = -1;
                            kierunek[j + 1] = 1;
                            j += 2;
                        }
                    }
                }
                ///Bicie4 -1 -1
                c = 1, il_miedzy = 0, temp_c = -1, mozliwosc_bicia = 1;
                while (tab_pion[i].x - c >= 0 && tab_pion[i].y - c >= 0 && mozliwosc_bicia)
                {
                    for(int a = 0; a < 24; a++)
                    {
                        if(tab_pion[a].x == tab_pion[i].x - c && tab_pion[i].y - c == tab_pion[a].y && !tab_pion[a].zbity
                        && tab_pion[i].color != tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            temp_c = c;
                            il_miedzy++;
                        }
                        if(tab_pion[a].x == tab_pion[i].x - c && tab_pion[i].y - c == tab_pion[a].y
                        && !tab_pion[a].zbity && tab_pion[i].color == tab_pion[a].color && (temp_c == -1 || temp_c + 1 == c))
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    c++;
                }
                if (il_miedzy != 1)
                {
                    mozliwosc_bicia = 0;
                }
                if(il_miedzy == 1 && mozliwosc_bicia)
                {
                    for(int b = 0; b < 24 && mozliwosc_bicia; b++)
                    {
                        if(tab_pion[i].x - temp_c - 1 >= 0 && tab_pion[i].x - temp_c - 1 == tab_pion[b].x
                        && tab_pion[i].y - temp_c - 1 >= 0 && tab_pion[i].y - temp_c - 1 == tab_pion[b].y
                        && !tab_pion[b].zbity)
                        {
                            mozliwosc_bicia = 0;
                        }
                    }
                    if(tab_pion[i].x - temp_c - 1 < 0 || tab_pion[i].y - temp_c - 1 < 0)
                    {
                        mozliwosc_bicia = 0;
                    }
                }
                if(mozliwosc_bicia && il_miedzy == 1)
                {
                    if (wyk_bicie_x == NULL && wyk_bicie_y == NULL)
                    {
                        bicia[j] = tab_pion[i].x;
                        bicia[j + 1] = tab_pion[i].y;
                        kierunek[j] = -1;
                        kierunek[j + 1] = -1;
                        j += 2;
                    }
                    else
                    {
                        if(wyk_bicie_x == tab_pion[i].x && wyk_bicie_y == tab_pion[i].y)
                        {
                            bicia[j] = tab_pion[i].x;
                            bicia[j + 1] = tab_pion[i].y;
                            kierunek[j] = -1;
                            kierunek[j + 1] = -1;
                            j += 2;
                        }
                    }
                }
            }
        }
    }
    return j;
}
