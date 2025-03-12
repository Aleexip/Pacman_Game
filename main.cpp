#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

char tmp_map[18][32];

char map[18][32] = {
    "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb",
    "\xdb                             \xdb",
    "\xdb                             \xdb",
    "\xdb\xdb\xdb \xdb\xdb\xdb  \xdb\xdb\xdb\xdb\xdb\xdb \xdb\xdb   \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb",
    "\xdb   \xdb                         \xdb",
    "\xdb \xdb \xdb\xdb\xdb\xdb \xdb  \xdb           \xdb     \xdb",
    "\xdb \xdb      \xdb  \xdb \xdb\xdb\xdb\xdb  \xdb   \xdb  \xdb  \xdb",
    "\xdb \xdb \xdb\xdb\xdb\xdb\xdb\xdb  \xdb \xdb      \xdb\xdb \xdb     \xdb",
    "\xdb \xdb           \xdb\xdb\xdb\xdb  \xdb      \xdb  \xdb",
    "\xdb \xdb\xdb\xdb\xdb\xdb\xdb \xdb\xdb\xdb         \xdb\xdb       \xdb",
    "\xdb          \xdb\xdb\xdb\xdb\xdb\xdb  \xdb\xdb\xdb\xdb\xdb\xdb\xdb \xdb\xdb\xdb\xdb",
    "\xdb                             \xdb",
    "\xdb\xdb \xdb\xdb\xdb \xdb\xdb\xdb\xdb      \xdb\xdb\xdb   \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb",
    "\xdb                             \xdb",
    "\xdb                             \xdb",
    "\xdb                             \xdb",
    "\xdb                             \xdb",
    "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb"};

void ShowMap()
{
    for (int i = 0; i < 18; i++)
    {
        printf("%s\n", map[i]);
    }
}

void gotoxy(short x, short y)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};

    SetConsoleCursorPosition(hStdout, position);
}

class entity
{
public:
    entity(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void move_x(int p)
    {
        if (map[y][x + p] == ' ')
            x += p;
    }

    void move_y(int p)
    {
        if (map[y + p][x] == ' ')
            y += p;
    }

    void move(int p, int q)
    {
        x += p;
        y += q;
    }

    int get_x() { return x; }
    int get_y() { return y; }

    void draw(char p)
    {
        map[y][x] = p;
        gotoxy(x, y);
        printf("%c", p);
    }

private:
    int x;
    int y;
};

struct walk
{
    short walk_count;
    short x;
    short y;
    short back;
};

struct target
{
    short x;
    short y;
};

vector<target> walk_queue;

vector<walk> BFSArray;

void AddArray(int x, int y, int wc, int back)
{
    if (tmp_map[y][x] == ' ' || tmp_map[y][x] == '.')
    {
        tmp_map[y][x] = '\xdb';
        walk tmp;
        tmp.x = x;
        tmp.y = y;
        tmp.walk_count = wc;
        tmp.back = back;
        BFSArray.push_back(tmp);
    }
}

void ClearDots()
{
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (map[i][j] == '.')
            {
                map[i][j] = ' ';
                gotoxy(j, i);
                cout << " ";
            }
        }
    }
}

void FindPath(int sx, int sy, int x, int y)
{
    memcpy(tmp_map, map, sizeof(map));
    BFSArray.clear();
    walk tmp;
    tmp.x = sx;
    tmp.y = sy;
    tmp.walk_count = 0;
    tmp.back = -1;
    BFSArray.push_back(tmp);

    int i = 0;
    while (i < BFSArray.size())
    {
        if (BFSArray[i].x == x && BFSArray[i].y == y)
        {
            walk_queue.clear();
            target tmp2;
            while (BFSArray[i].walk_count != 0)
            {
                tmp2.x = BFSArray[i].x;
                tmp2.y = BFSArray[i].y;
                walk_queue.push_back(tmp2);

                i = BFSArray[i].back;
            }

            break;
        }

        AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
        AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
        AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);
        AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);

        i++;
    }

    BFSArray.clear();
}

bool askQuestions()
{
    char aux1;

    gotoxy(31, 5);
    printf("The zero pollution targets for 2030, under the EU law,");
    gotoxy(31, 6);
    printf("Green Deal ambitions and synergy with other initiatives are:");
    gotoxy(31, 7);
    printf("a. Reducing by more than 20%% the health impacts (premature deaths)");
    gotoxy(31, 8);
    printf("   of air pollution;");
    gotoxy(31, 9);
    printf("b. Reducing by 50%% nutrient losses, reducing the use of chemical");
    gotoxy(31, 10);
    printf("   pesticides, and more hazardous antimicrobials reagents for");
    gotoxy(31, 11);
    printf("   farmed animals and aquaculture;");
    gotoxy(31, 12);
    printf("c. Reducing by 50%% of plastic in the sea and by 30%% microplastics");
    gotoxy(31, 13);
    printf("   released into the environment;");
    gotoxy(31, 14);
    printf("d. Reducing the municipal waste generation by 20%%");
    gotoxy(31, 15);
    printf("Pick a, b, c or d:");
    cin >> aux1;
    if (aux1 != 'b')
        return false;

    gotoxy(31, 17);
    printf("\n 2. Current solutions available for reducing water resource pollution are:");
    gotoxy(1, 19);
    printf("a. Treatment of industrial and municipal wastewater before discharging into");
    gotoxy(1, 20);
    printf("natural water resources; avoiding discharge of plastic and microplastic");
    gotoxy(1, 21);
    printf(" into the natural water resources; adopting green agriculture practices,");
    gotoxy(1, 22);
    printf("  introducing the ozon in the end step of the wastewater treatment plant \n");
    gotoxy(1, 23);
    printf("b. Using the large-scale of pesticides and fertilizers obtained by chemical");
    gotoxy(1, 24);
    printf(" synthesis in agriculture \n");
    gotoxy(1, 25);
    printf("c. Discharging of municipal wastewater directly into the natural water resources,");
    gotoxy(1, 26);
    printf(" without treatment \n");
    gotoxy(1, 27);
    printf("d. Discharging the industrial wastewater which contains macronutrients directly into the");
    gotoxy(1, 28);
    printf(" natural surface water \n");
    gotoxy(1, 29);
    printf("Pick a, b, c or d:");
    cin >> aux1;
    if (aux1 != 'a')
        return false;

    gotoxy(1, 29);
    printf("3.\n Current solutions available for reducing air pollution are:");
    gotoxy(1, 30);
    printf("\na. Particulate control from gaseous emission by using clean devices;");
    gotoxy(1, 31);
    printf(" removal of volatile organic compounds ( VOCs), desulfurization, and carbon sequestration from gaseous");
    gotoxy(1, 32);
    printf("  emission before release into");
    gotoxy(1, 33);
    printf("   the atmosphere. ");
    gotoxy(1, 34);
    printf("\nb. Releasing the gaseous emission which contains VOCs directly into the atmosphere ");
    gotoxy(1, 35);
    printf("\nc. Release the gaseous emission from industrial facilities (fossil fuel plants, chemical");
    gotoxy(1, 36);
    printf(" industry) directly into the atmosphere, without use the of adequate facilities");
    gotoxy(1, 37);
    printf("  for pollutant removal \n");
    gotoxy(1, 38);
    printf("Pick a, b or c:");
    cin >> aux1;
    if (aux1 != 'a')
        return false;

    gotoxy(1, 39);
    printf("\n4. Management of soil pollution suppose:");
    gotoxy(1, 40);
    printf("\na. Limiting the pollutants due to anthropological activities.");
    gotoxy(1, 41);
    printf("\nb. Discharge industrial sub-products directly on the soil.");
    gotoxy(1, 42);
    printf("\nc. Using the biochar for soil bioremediation ");
    gotoxy(1, 43);
    printf("\nd. Using phytoremediation for the polluted sites \n");
    gotoxy(1, 44);
    printf("Pick a, b, c or d:");
    cin >> aux1;
    if (aux1 == 'b')
        return false;

    return true;
}
int main()
{
    int alreadyplayed = 0;

    bool running = true;
    int x = 15; // hero x
    int y = 16; // hero y
    int old_x;
    int old_y;

    int ex = 1;
    int ey = 1;

    int pts = 0;

    printf("Instruction:\n1. Arrow Keys to move your hero\n2. Eat the dots produced by the Eater to gain poins\n3. Don't get caught by the Eater\n\n");
    printf("H -> Hard\nN -> Normal\nE -> Easy\n\nInput : ");

    char diffi;
    int speedmod = 3;

    cin >> diffi;
    getchar();

    if (diffi == 'N')
    {
        speedmod = 2;
    }
    else if (diffi == 'H')
    {
        speedmod = 1;
    }

    system("cls");
    ShowMap();

    gotoxy(x, y);
    cout << "\xEA";

    int frame = 0;

    FindPath(ex, ey, x, y);

    while (running)
    {
        gotoxy(x, y);
        cout << " ";

        old_x = x;
        old_y = y;

        if (GetAsyncKeyState(VK_UP))
        {
            if (map[y - 1][x] == '.')
            {
                y--;
                pts++;
            }
            else if (map[y - 1][x] == ' ')
                y--;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            if (map[y + 1][x] == '.')
            {
                y++;
                pts++;
            }
            else if (map[y + 1][x] == ' ')
                y++;
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (map[y][x - 1] == '.')
            {
                x--;
                pts++;
            }
            else if (map[y][x - 1] == ' ')
                x--;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (map[y][x + 1] == '.')
            {
                x++;
                pts++;
            }
            else if (map[y][x + 1] == ' ')
                x++;
        }

        if (old_x != x || old_y != y)
        {
            FindPath(ex, ey, x, y);
        }

        gotoxy(x, y);
        cout << "\xEA";

        map[ey][ex] = '.';
        gotoxy(ex, ey);
        cout << ".";

        if (frame % speedmod == 0 && walk_queue.size() != 0)
        {
            ex = walk_queue.back().x;
            ey = walk_queue.back().y;
            walk_queue.pop_back();
        }

        gotoxy(ex, ey);
        cout << "^";

        if (ex == x && ey == y)
        {
            char aux;
            if (alreadyplayed == 0)
            {
                gotoxy(31, 1);
                ("You lose, you have 1 more chance if you answer correctly to the next questions\n");
                gotoxy(31, 3);
                printf("Do you want to continue? Y/N:");
                cin >> aux;
                if (aux == 'Y')
                {
                    alreadyplayed = 1;
                    if (askQuestions())
                    {
                        x = 15;
                        y = 16;

                        ClearDots();
                        system("cls");
                        ShowMap();
                        gotoxy(x, y);
                        cout << "\xEA";
                        ex = 1;
                        ey = 1;
                        gotoxy(ex, ey);
                        cout << "^";

                        continue;
                    }
                    else
                    {
                        gotoxy(31, 45);
                        printf("\n\nWrong answers, you lose!! :*( --> Your points: %d", pts);

                        gotoxy(31, 47);
                        printf("\nPress any key to exit...");
                        cin.ignore();
                        cin.get();
                    }
                }
                else
                    break;
            }
            else
            {
                system("cls");
                gotoxy(31, 45);
                printf("You lose!! :*( --> Your points: %d", pts);
                gotoxy(31, 46);
                printf("\nPress any key to exit...");
                cin.ignore();
                cin.get();
            }
        }

        gotoxy(1, 18);
        gotoxy(1, 50);
        printf("Points: %d", pts);
        Sleep(100);
        frame++;
    }

    system("cls");
    cin.get();
    cin.get();
    cin.get();
    cin.get();
    cin.get();
    cin.get();
    cin.get();
    cin.get();

    return 0;
}