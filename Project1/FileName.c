#include <stdio.h>
#include <windows.h>
#include <conio.h>

// ================= 색상 =================

#define FONT_WHITE 37
#define FONT_YELLOW 33
#define FONT_CYAN 36
#define FONT_RED 31
#define FONT_GREEN 32
#define FONT_MAGENTA 35

#define BG_BLACK 40
#define BG_YELLOW 43

// ================= 전역 =================

int menu = 1;
int isRunning = 1;

// ================= 기본 함수 =================

void set_color(int code)
{
    printf("\x1b[%dm", code);
}

void move_cursor(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

void hide_cursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;

    info.dwSize = 1;
    info.bVisible = FALSE;

    SetConsoleCursorInfo(consoleHandle, &info);
}

void init_console()
{
    system("mode con cols=120 lines=35");
    system("title LOVE GAME");

    hide_cursor();
}

// ================= 시작 화면 =================

void DrawLogo()
{
    set_color(FONT_MAGENTA);

    set_color(FONT_CYAN);

    move_cursor(54, 8);
    printf(" 무인도 탈출 ");
}

int RenderTitle()
{
    system("cls");

    DrawLogo();

    set_color(FONT_WHITE);

    move_cursor(42, 11);
    printf("┌───────────────────────────────────┐");
    move_cursor(42, 13);
    printf("│    폭풍 속 무인도에서 탈출하라    │");
    move_cursor(42, 15);
    printf("└───────────────────────────────────┘");

    // 게임 시작
    if (menu == 1)
        set_color(BG_YELLOW);

    move_cursor(51, 17);
    printf("   1. 게임 시작   ");

    set_color(BG_BLACK);

    // 게임 설명
    if (menu == 2)
        set_color(BG_YELLOW);

    move_cursor(51, 19);
    printf("   2. 게임 설명   ");

    set_color(BG_BLACK);

    // 만든 사람
    if (menu == 3)
        set_color(BG_YELLOW);

    move_cursor(51, 21);
    printf("   3. 만든 사람   ");

    set_color(BG_BLACK);

    // 종료
    if (menu == 4)
        set_color(BG_YELLOW);

    move_cursor(51, 23);
    printf("   4. 게임 종료   ");

    set_color(BG_BLACK);

    move_cursor(48, 30);

    set_color(FONT_GREEN);

    printf("W / S 이동   ENTER 선택");

    char key = _getch();

    switch (key)
    {
    case 'w':
    case 'W':

        if (menu > 1)
            menu--;

        break;

    case 's':
    case 'S':

        if (menu < 4)
            menu++;

        break;

    case 13:

        return menu;
    }

    return 0;
}

// ================= 게임 시작 화면 =================

void GameStartScreen()
{
    system("cls");

    set_color(FONT_CYAN);

    move_cursor(35, 5);
    printf("################################################");

    move_cursor(35, 6);
    printf("#                                              #");

    move_cursor(35, 7);
    printf("#                GAME START !!                 #");

    move_cursor(35, 8);
    printf("#                                              #");

    move_cursor(35, 9);
    printf("################################################");

    set_color(FONT_WHITE);

    move_cursor(40, 14);
    printf("무인도");

    move_cursor(40, 16);
    printf("무인도");

    move_cursor(40, 22);
    printf("아무 키나 누르면 다음으로 진행");

    _getch();

    // 다음 화면
    system("cls");

    move_cursor(0, 5);

    set_color(FONT_CYAN);
    printf("1.\n\n");

    set_color(FONT_WHITE);
    printf("2.\n\n");

    set_color(FONT_RED);
    printf("3. \n\n");

    set_color(FONT_YELLOW);
    printf("GAME OVER\n\n");

    printf("아무 키나 누르면 돌아갑니다.");

    _getch();
}

// ================= 게임 설명 =================

void GameInfo()
{
    system("cls");


    set_color(FONT_CYAN);

    move_cursor(51, 5);
    printf("#############################");

    move_cursor(51, 6);
    printf("#        게임 설명          #");

    move_cursor(51, 7);
    printf("#############################");

    set_color(FONT_WHITE);

    move_cursor(28, 10);
    printf("▶ 여행 중 폭풍에 휘말린 주인공은");

    move_cursor(28, 11);
    printf("  이름 모를 무인도에 표류하게 된다.");

    move_cursor(28, 14);
    printf("▶ 아무도 없는 섬에서 단서를 찾고");

    move_cursor(28, 15);
    printf("  살아남아 탈출해야 한다.");

    move_cursor(28, 18);
    printf("▶ 선택지와 키워드를 통해");

    move_cursor(28, 19);
    printf("  이야기가 달라진다.");

    move_cursor(28, 22);
    printf("▶ 마지막에는 선택한 단어들이 조합되어");

    move_cursor(28, 23);
    printf("  하나의 엔딩 문장이 완성된다.");

    // 하단
    set_color(FONT_YELLOW);

    set_color(FONT_GREEN);

    move_cursor(48, 33);
    printf("아무 키나 누르면 돌아갑니다.");

    _getch();
}

// ================= 만든 사람 =================

void Credit()
{
    system("cls");

    set_color(FONT_MAGENTA);

    move_cursor(45, 5);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

    move_cursor(45, 6);
    printf("@         만든 사람         @");

    move_cursor(45, 7);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

    set_color(FONT_WHITE);

    move_cursor(52, 12);
    printf("20251268 추연지");

    move_cursor(52, 14);
    printf("202618004 강예빈");

    move_cursor(52, 16);
    printf("202617771 정하현");

    move_cursor(52, 18);
    printf("202619106 김태희");

    move_cursor(46, 25);
    printf("아무 키나 누르면 돌아갑니다");

    _getch();
}

// ================= 메인 =================

int main()
{
    init_console();

    while (isRunning)
    {
        int select = RenderTitle();

        switch (select)
        {
        case 1:
            GameStartScreen();
            break;

        case 2:
            GameInfo();
            break;

        case 3:
            Credit();
            break;

        case 4:
            isRunning = 0;
            break;
        }
    }

    system("cls");

    return 0;
}