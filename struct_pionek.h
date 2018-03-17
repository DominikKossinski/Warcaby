struct pionek{
    int color;
    int x;
    int y;
    int zbity;
    int damka;
};
int wybierz_pionek(int x, int y, struct pionek tab_pion[24], int color);///Sprawdza czy mozna wybrac dany pionek
int mozliwosc_ruchu(int x, int y, struct pionek *tab_pion, int color);///Sprawdza czy dany pionek ma mozliosc ruchy (nie uwzglednia bic)
void rusz(int x_wybrany, int y_wybrany, int x, int y, int color, struct pionek *tab_pion);///Rusza z pozycji aktualnej pionka na x, y na ktorym jest kursor
void bij(int x_wybrany, int y_wybrany, int x, int y, int kierunek_x, int kierunek_y, int color, struct pionek *tab_pion);///Realizuje bicie pionkiem
int wszystkie_zbite(struct pionek *tab_pion);///Sprawdza czy poszczegolny gracz ma chociaz jeden nie zbity pionek
int ruch_dozwolony(int x_wybrany, int y_wybrany, int x, int y, int color, struct pionek *tab_pion);///Sprawza czy ruch, ktory gracz probuje wykonac jest dozwolony
void bij_damka(int x_wybrany, int y_wybrany, int x, int y, int kierunek_x, int kierunek_y, int color, struct pionek *tab_pion, int temp_i);///Realizuje bicie damka
int sprawdz_xy(int x_wybrany, int y_wybrany, int x, int y);///Sprawdza przy ruchu damka czy x oraz y leza po skosie od pozycji damki
int brak_ruchow(struct pionek *tab_pionek);///Sprawdza czy gracz ma jaki kolwie ruch (nie uwzglednia bic)
