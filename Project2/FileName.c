#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// ================= 색상 =================

#define FONT_WHITE 37
#define FONT_YELLOW 33
#define FONT_CYAN 36
#define FONT_RED 31
#define FONT_GREEN 32
#define FONT_MAGENTA 35
#define FONT_BLUE 34
#define FONT_BRIGHTMAGENTA 95

#define BG_BLACK 40
#define BG_BLUE 44

// ================= 기준 화면 =================

#define BASE_WIDTH 120
#define BASE_HEIGHT 35

// ================= 전역 =================

int menu = 1;
int isRunning = 1;

int screenWidth;
int screenHeight;

int offsetX;
int offsetY;

// 애니메이션 변수
int waveOffset = 0;
int starToggle = 0;
int menuBlink = 0;
int shipOffset = 0;

// ================= 기본 함수 =================

void set_color(int code)
{
    printf("\x1b[%dm", code);
}

void move_cursor(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

void draw(int x, int y, const char* text)
{
    move_cursor(x + offsetX + 1, y + offsetY + 1);
    printf("%s", text);
}

void hide_cursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;

    info.dwSize = 1;
    info.bVisible = FALSE;

    SetConsoleCursorInfo(consoleHandle, &info);
}

void get_console_size()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &csbi
    );

    screenWidth =
        csbi.srWindow.Right - csbi.srWindow.Left + 1;

    screenHeight =
        csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    offsetX = (screenWidth - BASE_WIDTH) / 2;
    offsetY = (screenHeight - BASE_HEIGHT) / 2;

    if (offsetX < 0)
        offsetX = 0;

    if (offsetY < 0)
        offsetY = 0;
}

void init_console()
{
    system("mode con cols=120 lines=35");
    system("title LOVE GAME");

    hide_cursor();

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwMode = 0;

    GetConsoleMode(hOut, &dwMode);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    SetConsoleMode(hOut, dwMode);

    srand(time(NULL));

    get_console_size();
}

// ================= 배경 =================

void DrawBackground()
{
    // ================= 별 =================

    set_color(FONT_WHITE);

    // ===== 고정 별 =====

    draw(5, 2, ".");
    draw(18, 3, "*");
    draw(42, 2, ".");
    draw(70, 4, "*");
    draw(95, 2, ".");
    draw(112, 3, "*");

    draw(28, 5, ".");
    draw(58, 2, "*");
    draw(84, 4, ".");
    draw(104, 5, "*");

    // ===== 반짝이는 별 =====

    if (waveOffset % 2 == 0)
    {
        draw(12, 2, "*");
        draw(35, 4, ".");
        draw(76, 3, "*");
        draw(120, 2, ".");
    }
    else
    {
        draw(12, 2, ".");
        draw(35, 4, "*");
        draw(76, 3, ".");
        draw(120, 2, "*");
    }

    // ================= 구름 =================

    set_color(FONT_WHITE);

    draw(-18, 4, "       .--.");
    draw(-19, 5, "    .-(    ).");
    draw(-20, 6, "   (___.__)__)");

    draw(8, 3, "      .--.");
    draw(7, 4, "   .-(    ).");
    draw(6, 5, "  (___.__)__)");

    draw(48, 4, "     .--.");
    draw(47, 5, "  .-(    ).");
    draw(46, 6, " (___.__)__)");

    draw(92, 4, "      .--.");
    draw(91, 5, "   .-(    ).");
    draw(90, 6, "  (___.__)__)");

    draw(125, 3, "       .--.");
    draw(124, 4, "    .-(    ).");
    draw(123, 5, "   (___.__)__)");

    // ================= 달 =================

    set_color(FONT_YELLOW);

    draw(96, 2, "   _.._");
    draw(96, 3, " .' .-'");
    draw(96, 4, "/  /");
    draw(96, 5, "|  |");
    draw(96, 6, "\\  \\");

    set_color(FONT_WHITE);

    draw(100, 5, "    ___");
    draw(100, 6, "__(   ' )_");
    draw(94, 7, "(_______________)");

    // ================= 왼쪽 섬 =================

    set_color(FONT_YELLOW);

    draw(-8, 23, "      ____");
    draw(-10, 24, "_____/____\\_____");

    set_color(FONT_GREEN);

    draw(-4, 19, "   \\\\|//");
    draw(-4, 20, " --  *  --");
    draw(-4, 21, "   //|\\\\");
    draw(-2, 22, "    ||");
    draw(-2, 23, "   /||\\\\");

    // ================= 메인 야자수 =================

    set_color(FONT_GREEN);

    draw(3, 13, "      \\\\ | //");
    draw(3, 14, "    --  *  --");
    draw(3, 15, "      // | \\\\");

    set_color(FONT_YELLOW);

    draw(5, 16, "      ||");
    draw(5, 17, "      ||");
    draw(5, 18, "     /||\\\\");

    set_color(FONT_GREEN);

    draw(18, 17, "     \\\\ | //");
    draw(18, 18, "   --  *  --");
    draw(18, 19, "     // | \\\\");

    set_color(FONT_YELLOW);

    draw(19, 20, "      ||");
    draw(19, 21, "      ||");
    draw(19, 22, "     /||\\\\");

    // ================= 코코넛 =================

    set_color(FONT_YELLOW);

    draw(12, 15, "(oo)");
    draw(20, 19, "(oo)");

    // ================= 풀 =================

    set_color(FONT_GREEN);

    draw(5, 24, "vVVv");
    draw(15, 25, "VVv");
    draw(30, 24, "vVv");

    // ================= 돌 =================

    set_color(FONT_WHITE);

    draw(20, 24, "  ___");
    draw(20, 25, " /   \\\\");
    draw(20, 26, "/_____\\\\");

    draw(4, 21, "  ___");
    draw(4, 22, " /___\\\\");

    // ================= 모닥불 =================

    if (waveOffset % 2 == 0)
    {
        set_color(FONT_RED);
        draw(14, 21, " (  ) ");

        set_color(FONT_YELLOW);
        draw(14, 22, " )()( ");

        set_color(FONT_RED);
        draw(14, 23, "(____)");
    }
    else
    {
        set_color(FONT_YELLOW);
        draw(14, 21, " \\()/ ");

        set_color(FONT_RED);
        draw(14, 22, " (  ) ");

        set_color(FONT_YELLOW);
        draw(14, 23, "(_[]_)");
    }

    // ================= 오른쪽 큰 섬 =================

    set_color(FONT_YELLOW);

    draw(118, 22, "         ______");
    draw(116, 23, "   _____/______\\_____");
    draw(114, 24, "__/__________________\\__");

    set_color(FONT_GREEN);

    draw(122, 17, "    \\\\ | //");
    draw(122, 18, "  --  *  --");
    draw(122, 19, "    // | \\\\");

    set_color(FONT_YELLOW);

    draw(124, 20, "      ||");
    draw(124, 21, "      ||");
    draw(124, 22, "     /||\\\\");

    // ================= 해변 =================

    set_color(FONT_YELLOW);

    move_cursor(1, 27 + offsetY);

    for (int i = 0; i < screenWidth; i++)
    {
        printf("=");
    }

    // ================= 바다 =================

    set_color(FONT_CYAN);

    for (int y = 28; y <= 31; y++)
    {
        move_cursor(1, y + offsetY);

        for (int x = 0; x < screenWidth; x++)
        {
            if ((x + waveOffset + y) % 6 == 0)
                printf("~");

            else if ((x + waveOffset + y) % 11 == 0)
                printf("-");

            else
                printf(" ");
        }
    }

    // ================= 배 =================

    set_color(FONT_WHITE);

    draw(82, 22 + shipOffset, "           |\\");
    draw(82, 23 + shipOffset, "          /| \\");
    draw(82, 24 + shipOffset, "         /_|__\\");
    draw(82, 25 + shipOffset, "           |");
    draw(82, 26 + shipOffset, "      ____|____");
    draw(82, 27 + shipOffset, "  ___/_________\\___");
    draw(82, 28 + shipOffset, "  \\_______________/");
}

// ================= 로고 =================

void DrawLogo()
{
    set_color(FONT_BRIGHTMAGENTA);

    draw(46, 9, "=========================");
    draw(46, 10, "=== 무인도를 탈출하자 ===");
    draw(46, 11, "=========================");
}

// ================= 타이틀 =================

int RenderTitle()
{
    system("cls");

    get_console_size();

    DrawBackground();
    DrawLogo();

    set_color(FONT_WHITE);

    if (menu == 1)
    {
        set_color(BG_BLUE);
    }

    draw(49, 15, "   ▶ 게임 시작   ");

    set_color(BG_BLACK);

    if (menu == 2)
    {
        set_color(BG_BLUE);
    }
    draw(49, 17, "   ▶ 게임 설명   ");

    set_color(BG_BLACK);

    if (menu == 3)
    {
        set_color(BG_BLUE);
    }
    draw(49, 19, "   ▶ 만든 사람   ");

    set_color(BG_BLACK);

    if (menu == 4)
    {
        set_color(BG_BLUE);
    }

    draw(49, 21, "   ▶ 게임 종료   ");

    set_color(BG_BLACK);

    set_color(FONT_GREEN);

    draw(42, 33, "W / S 이동      ENTER 선택");

    // 애니메이션 업데이트
    waveOffset++;

    shipOffset = waveOffset % 2;

    Sleep(200);

    if (_kbhit())
    {
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

        case 27:

            isRunning = 0;

            break;
        }
    }

    return 0;
}

// ================= 시작 화면 =================

void GameStartScreen()
{
    system("cls");

    set_color(FONT_CYAN);

    move_cursor(72, 5);
    printf("################################################");

    move_cursor(72, 6);
    printf("#                                              #");

    move_cursor(72, 7);
    printf("#                GAME START !!                 #");

    move_cursor(72, 8);
    printf("#                                              #");

    move_cursor(72, 9);
    printf("################################################");

    set_color(FONT_WHITE);

    move_cursor(80, 14);
    printf("무인도");

    move_cursor(80, 16);
    printf("무인도");

    move_cursor(80, 22);
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

// ================= 설명 =================

void GameInfo()
{
    system("cls");


    set_color(FONT_CYAN);

    move_cursor(80, 5);
    printf("#############################");

    move_cursor(80, 6);
    printf("#        게임 설명          #");

    move_cursor(80, 7);
    printf("#############################");

    set_color(FONT_WHITE);

    move_cursor(65, 15);
    printf("▶ 여행 중 폭풍에 휘말린 주인공은");

    move_cursor(65, 17);
    printf("   이름 모를 무인도에 표류하게 된다.");

    move_cursor(65, 21);
    printf("▶ 아무도 없는 섬에서 단서를 찾고");

    move_cursor(65, 23);
    printf("   살아남아 탈출해야 한다.");

    move_cursor(65, 27);
    printf("▶ 선택지와 키워드를 통해");

    move_cursor(65, 29);
    printf("   이야기가 달라진다.");

    move_cursor(65, 33);
    printf("▶ 마지막에는 선택한 단어들이 조합되어");

    move_cursor(65, 35);
    printf("   하나의 엔딩 문장이 완성된다.");

    // 하단
    set_color(FONT_YELLOW);

    set_color(FONT_GREEN);

    move_cursor(80, 45);
    printf("아무 키나 누르면 돌아갑니다.");

    _getch();
}

// ================= 만든 사람 =================

void Credit()
{
    system("cls");

    set_color(FONT_CYAN);

    move_cursor(80, 5);
    printf("#############################");

    move_cursor(80, 6);
    printf("#         만든 사람         #");

    move_cursor(80, 7);
    printf("#############################");

    set_color(FONT_WHITE);

    move_cursor(85, 20);
    printf("▶ 20251268 추연지");

    move_cursor(85, 24);
    printf("▶ 202618004 강예빈");

    move_cursor(85, 28);
    printf("▶ 202617771 정하현");

    move_cursor(85, 32);
    printf("▶ 202619106 김태희");

    // 하단
    set_color(FONT_YELLOW);

    set_color(FONT_GREEN);

    move_cursor(80, 45);
    printf("아무 키나 누르면 돌아갑니다.");

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

    move_cursor(45, 15);

    set_color(FONT_WHITE);

    printf("게임을 종료합니다.");

    return 0;
}