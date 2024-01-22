/*
    plik do sprawdzenie czy implementacja bota jest poprawna,
    sprawdzenie integracji bota z całą grą w pliku test
*/

#include "game_bot.h"
#include "bot_utils.h"
#include "bot_main.h"

FILE *file;
void dodaj(){
    char **plansza = allocate(9);

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            plansza[i][j] = ' ';

    //uzupełnianie randomowe planszy
    int czesc = 4;
    char gracz = 'X';

    // for(int i = 0; i < rand() % 10 + 5; i++){
    //     czesc = bot_9x9_random(plansza, gracz, czesc);
    //     gracz = zmiana_gracza(gracz);
    //     if(czesc == -1){
    //         puts("-1");
    //         exit(EXIT_SUCCESS);
    //     }
    // }

    char **nad_zwyciestwa = allocate(3);
    uzupelnij_nad_zwyciestwa(plansza, nad_zwyciestwa);

    int player[2], idx = 0;
    player[0] = rand() % 4 + 3;
    player[1] = rand() % 4 + 3;
    while(player[1]  == player[0]) player[1] = rand() % 3 + 4;

    //!!!!!!!!!!!!!!!!!!!
    player[0] = 6;
    player[1] = 3;
    //!!!!!!!!!!!!!!!!!!!

    //zabawa botem
    // cout(plansza, 9);
    while(sprawdz_wynik(nad_zwyciestwa) == ' ' && !remis(nad_zwyciestwa)){
        int next_czesc;
        if(player[idx] == 6){
            next_czesc = bot_9x9_random(plansza, gracz, czesc);
        }
        else{
            next_czesc = bot(plansza, gracz, czesc, player[idx]);
        }

        if(next_czesc == -1){
             fprintf(file, "%d;%d;%d\n", player[0], player[1], 2);
            return;
        }

        update_nad_zwyciestwa(plansza, nad_zwyciestwa, czesc);
        czesc = next_czesc;
        gracz = zmiana_gracza(gracz);
        idx ^= 1;

        //debug
        // printf("gracz: %c\n", gracz);
        // cout(plansza, 9);
        // cout(nad_zwyciestwa, 3);
        // putchar('\n');
    }
    //wypisanie wyniku
    if(remis(nad_zwyciestwa)){
        fprintf(file, "%d;%d;%d\n", player[0], player[1], 2);
    }

    int wynik = sprawdz_wynik(nad_zwyciestwa);
    if(wynik == 'X') fprintf(file, "%d;%d;%d\n", player[0], player[1], 0);
    else fprintf(file, "%d;%d;%d\n", player[0], player[1], 1);

    deallocate(plansza, 9);
    deallocate(nad_zwyciestwa, 3);
}

int DIFF = 0, WINS = 2, SELECT = 2;
double SQRT = 0.8;

int main(int argc, char *argv[]){
    file = fopen("dane.csv", "w");
    if(argc == 5){
        DIFF = atoi(argv[1]);
        SQRT = atof(argv[2]);
        WINS = atoi(argv[3]);
        SELECT = atoi(argv[4]);
    }

    //tworzenie planszy
    srand(time(NULL));
    for(int i = 0; i < 50; i++){ //!
        dodaj();
        printf("%d\n", i);
    }
    
    fclose(file);
    return 0;
}

//gcc -pthread -std=c11 *.c -lm