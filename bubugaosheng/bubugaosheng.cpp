#include<graphics.h>
#include<conio.h>
#include <windows.h>

const int WIDTH = 600;
const int HEIGHT = 800;
const int PLAYER_SIZE = 30;
const int PLATFORM_WIDTH = 100;

struct platform {
    int x, y;
};
struct player {
    int x, y;
    float velocity;
};

player person;
platform platforms[10];

void initialize() {
    initgraph(WIDTH,HEIGHT);
   person = { WIDTH / 2,HEIGHT/2 ,0 };
   for (int i = 0; i < 10; i++) {
       platforms[i] = {
           rand() % (WIDTH - 100),
           HEIGHT - i * 80
       };
   }
}

void draw() {
    cleardevice();
    setfillcolor(YELLOW);
    solidcircle(person.x, person.y, PLAYER_SIZE / 2);

    setfillcolor(BLUE);
    for (platform p : platforms) {
        solidrectangle(p.x, p.y, p.x + PLATFORM_WIDTH, p.y + 20);
    }
    Sleep(10);
}

void update() {
    if (GetAsyncKeyState(VK_LEFT))
        person.x -= 5;
    if (GetAsyncKeyState(VK_RIGHT))
        person.x += 5;

    person.velocity += 0.5;
    person.y += person.velocity;

    for (platform& p : platforms) {
        if (person.y + PLAYER_SIZE/2 > p.y &&
            person.y + PLAYER_SIZE / 2 < p.y + 20 &&
            person.x > p.x - PLAYER_SIZE / 2 &&
            person.x < p.x + PLATFORM_WIDTH + PLAYER_SIZE / 2)
        {
            person.velocity = -15;
        }
    }
    if (person.y < HEIGHT / 2)
    {
        person.y = HEIGHT / 2;
        for (platform& p : platforms) {
            p.y += 5;
            if (p.y > HEIGHT)
                p = { rand() % (WIDTH - 100),0 };

        }
    }
    if (person.y > HEIGHT) {
        person = { WIDTH / 2, HEIGHT - 100, 0 }; 
        for (int i = 0; i < 10; i++) {         
            platforms[i] = { rand() % (WIDTH - 100), HEIGHT - i * 80 };
        }
    }
}

int main()
{
    initialize();

    while (!_kbhit()) {
        update();
        draw();
    }
    closegraph();
    return 0;
}
