/**************************************************************
*                                                                         *
* ���� : ���� ũ�� ���ϱ�                                        *
*                                                                        *
***************************************************************/

#include <iostream>
#include <string>
using namespace std;

void searchFloorPlan();
int  searchRoom(int y, int x, int count);
void bubbleSort(int *data, int size);

int main(void)
{
        searchFloorPlan();
}

#define MAX_SIZE (100+1)
#define MAX_ROOMS 100

#define EMPTY    -1
#define WALL     -2

int     floorPlan[MAX_SIZE][MAX_SIZE];

/* ��鵵���� �� ���� ũ�⸦ ���ϴ� �Լ� */
void searchFloorPlan()
{
    int  i, j;
    int  width, height;
    int  roomCount;
    int  roomSize[MAX_ROOMS];

    cin >> width >> height;

    for (i=0; i<height; i++)
    {
        char line[MAX_SIZE];

        cin >> line;

        for(j=0; line[j]; j++)
            if (line[j] == '+')
                floorPlan[i][j] = WALL;
            else
                floorPlan[i][j] = EMPTY;
    }

    roomCount = 0;
    for (i=0; i<height; i++)
        for (j=0; j<width; j++)
        {
            if (floorPlan[i][j] == EMPTY)
            {
                roomSize[roomCount] = searchRoom(i, j, roomCount);
                roomCount++;
            }
        }

    bubbleSort(roomSize, roomCount);

    cout << roomCount << endl;
    for(i=0; i<roomCount; i++)
        cout << roomSize[i] << ' ';
    cout << endl;
}

/*
 * ���� ���� �Ϻ��� ��ġ (x, y)���� ������ �Ǻθ����� �˻��ϸ鼭
 * ��ü ���� ũ�⸦ ����ϴ� �Լ�
 */
int searchRoom(int y, int x, int count)
{
    int left, right, up, down;

    if (floorPlan[y][x] != EMPTY)
        return 0;

    floorPlan[y][x] = count;

    left  = searchRoom(y,   x-1, count);
    right = searchRoom(y,   x+1, count);
    up    = searchRoom(y+1, x,   count);
    down  = searchRoom(y-1, x,   count);

    return left + right + up + down + 1;
}

/* ���� ũ������� �����ϴ� ���� ���� �Լ� */
void bubbleSort(int *data, int size)
{
    int i, j;

    for(i=0; i<size-1; i++)
        for(j=0; j<size-1-i; j++)
        {
            if (data[j+1] > data[j])
            {
                int tmp;

                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
}

