using namespace std;
#include <ncurses.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <vector>

void salir();
int menu();
void movimiento();
int kbhit(void);
vector<char> X;

int main(void)
{
    int z;
    while (z != 4)
    {
        erase();
        z = menu();
        /* char fs[] = "dsffd";
        printw("%s", fs);
        refresh();
        usleep(3000000); */
        switch (z)
        {
        case 1:
        {
            move(6, 17);
            printw("Opcion 1");
            refresh();
            usleep(1000000);
            move(7, 0);
            refresh();
            char t[100];
            printw("Ingrese un entero: ");
            echo();
            scanw("%s", t);
            refresh();
            printw("Dato Ingresado: ");
            int entero = atoi(t);
            move(30, 40);
            printw("%i", entero);
            refresh();
            getch();
            break;
        }
        case 2:
        {
            move(6, 17);
            printw("Opcion 2");
            refresh();
            usleep(1000000);
            movimiento();
            break;
        }
        case 3:
        {
            move(6, 17);
            printw("Opcion 3");
            refresh();
            usleep(1000000);
            break;
        }
        case 4:
        {
            salir();
        }
        }
    }
}

int menu()
{
    initscr();
    int x, y;
    getmaxyx(stdscr, y, x);
    move(0, (x / 2 - 18));
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_WHITE);
        attron(COLOR_PAIR(1));
        printw("<< Laboratorio 6  -  Carlos Romero >>");
        attroff(COLOR_PAIR(1));
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        attron(COLOR_PAIR(2));
        move(1, 0);
        printw("Escoja una opción:\n");
        move(2, 1);
        printw("1)  \n");
        move(3, 1);
        printw("2) Intento de Snake \n");
        move(4, 1);
        printw("3)  \n");
        move(5, 1);
        printw("4) Salir \n");
        move(6, 0);
        printw("Opción escogida: ");
        attroff(COLOR_PAIR(2));
    }
    int cx = 0;
    int cy = 2;
    int tecla;
    move(cy, cx);
    refresh();
    while (true)
    {
        noecho();
        tecla = getch();
        if (tecla == 10)
        {
            if (cy == 2)
            {
                return 1;
            }
            if (cy == 3)
            {
                return 2;
            }
            if (cy == 4)
            {
                return 3;
            }
            if (cy == 5)
            {
                return 4;
            }
        }
        else
        {
            //printw("%i",tecla);
            if (tecla == 65 && cy > 2)
            {
                //printw(" arriba");
                cy = cy - 1;
                move(cy, cx);
            }
            else if (tecla == 66 && cy <= 4)
            {
                //printw(" abajo");
                cy = cy + 1;
                move(cy, cx);
            }
            else
            {
                //No hara nada
            }
        }
        refresh();
    }
    echo();
    return 0;
}

void salir()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    erase();
    if (has_colors)
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        move(y / 2, (x / 2 - 6));
        printw("Saliendo");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        refresh();
        usleep(1000000 / 2);
        attroff(COLOR_PAIR(1));
    }
    endwin();
    exit(0);
}

void movimiento()
{
    erase();
    //vector <char> ser={'*','*','*'};
    char ser = (char)79;
    int x, y;
    int cx = 1;
    int cy = 1;
    getmaxyx(stdscr, y, x);
    move(y / 2, x / 2 - 18);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    printw("Presione ENTER para iniciar el juego.");
    refresh();
    attroff(COLOR_PAIR(1));
    int tecla;
    tecla = getch();
    while (tecla != 10)
    {
        tecla = getch();
    }
    int direccion = 3;
    cx = x / 2;
    cy = y / 2;
    erase();
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    keypad(stdscr,TRUE);
    refresh();
    while (true)
    {
        if (kbhit())
        {
            tecla = getch();
            //ARRIBA
            if (tecla==KEY_UP)
            {
                direccion = 1;
            }
            //IZQUIERDA
            if (tecla==KEY_LEFT)
            {
                direccion = 2;
            }
            //DERECHA
            if (tecla==KEY_RIGHT)
            {
                direccion = 3;
            }
            //ABAJO
            if (tecla==KEY_DOWN)
            {
                direccion = 4;
            }
        }
        if ((cx > 0 && cy > 0) && (cx < x && cy < y))
        {
            move(cy, cx);
            printw("%c", ser);
            refresh();
            usleep(1000000 / 5);
            if (direccion == 1)
            {
                cy = cy - 1;
                move(cy + 1, cx);
                printw(" ");
                refresh();
            }
            if (direccion == 2)
            {
                cx = cx - 1;
                move(cy, cx + 1);
                printw(" ");
                refresh();
            }
            if (direccion == 3)
            {
                cx = cx + 1;
                move(cy, cx - 1);
                printw(" ");
                refresh();
            }
            if (direccion == 4)
            {
                cy = cy + 1;
                move(cy - 1, cx);
                printw(" ");
                refresh();
            }
        }
        else
        {
            break;
        }
    }
    attroff(COLOR_PAIR(2));
    keypad(stdscr,FALSE);
    move(y / 2, (x / 2 - 4));
    printw("Perdió!!");
    refresh();
    usleep(1000000 / 2);
    curs_set(1);
}

int kbhit(void)
{
    struct timeval timeout;
    fd_set readfds;
    int how;

    /* look only at stdin (fd = 0) */
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    /* poll: return immediately */
    timeout.tv_sec = 0L;
    timeout.tv_usec = 0L;

    how = select(1, &readfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
    /* Change "&timeout" above to "(struct timeval *)0"       ^^^^^^^^
         * if you want to wait until a key is hit
         */

    if ((how > 0) && FD_ISSET(0, &readfds))
        return 1;
    else
        return 0;
}