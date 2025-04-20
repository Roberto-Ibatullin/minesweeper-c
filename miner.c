#include <stdio.h>
#include <stdlib.h>

int size_x, size_y, mines_count;
int *mines;
char *map;

void place_mines(int x, int y);
void open_cell(int x, int y);
void print_map();
int has_empty_cells();
int no_open_mines();
void init_map();

int main()
{
    printf("Enter the size of the field (x y): ");
    scanf("%d %d", &size_x, &size_y);
    printf("Enter the number of mines: ");
    scanf("%d", &mines_count);

    mines = (int *)malloc(size_x * size_y * sizeof(int));
    map = (char *)malloc(size_x * size_y * sizeof(char));

    init_map();
    int x, y;

    printf("Do your first turn: ");
    scanf("%d %d", &x, &y);
    place_mines(x, y);
    open_cell(x, y);
    print_map();

    while (has_empty_cells() && no_open_mines())
    {
        scanf("%d %d", &x, &y);
        open_cell(x, y);
        print_map();
    }

    if (no_open_mines())
    {
        printf("Congrats, you win!");
    }
    else
    {
        printf("WASTED");
    }

    free(mines);
    free(map);

    return 0;
}

void place_mines(int x, int y)
{
    int mines_count_placed = 0;
    while (mines_count_placed < mines_count)
    {
        int m_x = rand() % size_x;
        int m_y = rand() % size_y;
        if (m_x == x && m_y == y)
        {
            continue;
        }
        if (mines[m_x * size_y + m_y] == 1)
        {
            continue;
        }
        mines[m_x * size_y + m_y] = 1;
        mines_count_placed++;
    }
}

void open_cell(int x, int y)
{
    if (mines[x * size_y + y] == 1)
    {
        map[x * size_y + y] = '*';
        return;
    }
    int mines_count = 0;
    if (x + 1 < size_x && mines[(x + 1) * size_y + y])
    {
        mines_count++;
    }
    if (x + 1 < size_x && y - 1 >= 0 && mines[(x + 1) * size_y + (y - 1)])
    {
        mines_count++;
    }
    if (x + 1 < size_x && y + 1 < size_y && mines[(x + 1) * size_y + (y + 1)])
    {
        mines_count++;
    }

    if (x - 1 >= 0 && mines[(x - 1) * size_y + y])
    {
        mines_count++;
    }
    if (x - 1 >= 0 && y - 1 >= 0 && mines[(x - 1) * size_y + (y - 1)])
    {
        mines_count++;
    }
    if (x - 1 >= 0 && y + 1 < size_y && mines[(x - 1) * size_y + (y + 1)])
    {
        mines_count++;
    }

    if (y - 1 >= 0 && mines[x * size_y + (y - 1)])
    {
        mines_count++;
    }
    if (y + 1 < size_y && mines[x * size_y + (y + 1)])
    {
        mines_count++;
    }
    map[x * size_y + y] = '0' + mines_count;
}

void print_map()
{
    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            printf("%c ", map[j * size_y + i]);
        }
        printf("\n");
    }
}

int has_empty_cells()
{
    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            if (map[j * size_y + i] == '?')
            {
                return 1;
            }
        }
    }
    return 0;
}

int no_open_mines()
{
    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            if (map[j * size_y + i] == '*')
            {
                return 0;
            }
        }
    }
    return 1;
}

void init_map()
{
    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            map[j * size_y + i] = '?';
        }
    }
}