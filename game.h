void begin_game(int nr_rozgrywki, int nr_koloru);///Otwiera wybrana przez urzytkownika gre
void begin_2_players(int kolor_gracza1, ALLEGRO_BITMAP *szachownica, ALLEGRO_BITMAP *kursor, int wczytana, int ruszajcy, struct pionek *w_pionki);
///Gra dla 2 osob rozpoczyna kolor wybrany przez gracza nr 1
void rysuj_pionki(struct pionek *pionki);///Funkcja do rysowania pionkow na szachownicy
