#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


using namespace std;

class Mouse {
private:        
    int mx, my, x, y;
public:

    void update() {
		mx = mousex();
        my = mousey();

    }
    void chrosshair() {
        setcolor(WHITE);
        line(mx - 10, my, mx + 10, my);
        line(mx, my - 10, mx, my + 10);
    }

};

class Shape{
    protected: int x,y,color,speed,dx,dy,clickCount;
    public:
    virtual void draw()  = 0;
    virtual bool clicked(int mx, int my) = 0;
    virtual void increaseStats() = 0;

    void move(){
        x = x + speed * dx;
        y = y + speed * dy;

        
        if (x > 1280) x = 0;
        if (x < 0) x = 1280;
        if (y > 720) y = 0;
        if (y < 0) y = 720;
    }
    void direction() {
        do {
            dx = (rand() % 3) - 1;
            dy = (rand() % 3) - 1;
        } while (dx == 0 && dy == 0);
    }

};

class Circle : public Shape{
    private: int radius;
    public:
    Circle() {
        radius = 25;
        clickCount = 0;
        speed = 1; 
		color = (rand() % 15) + 1; //ngerandom color
       

        x = rand() % (1280 - radius * 2) + radius;
        y = rand() % (720 - radius * 2) + radius;

        direction();
    }

     void draw() override {
       setfillstyle(SOLID_FILL, color);
        setcolor(WHITE);
        fillellipse(x, y, radius, radius);
    }
    bool clicked(int mx, int my) override {
        if (mx >= (x - radius) && mx <= (x + radius) &&
            my >= (y - radius) && my <= (y + radius)) {
                PlaySound(TEXT("D:/Code/ProlanVScode/Home/media/faaah.wav"), NULL, SND_FILENAME | SND_ASYNC);

            return true;
        }
        return false;
    }
    void increaseStats() override {
        clickCount++;
        speed++;
        x = rand() % (1280 - radius * 2) + radius;
        y = rand() % (720 - radius * 2) + radius;
		direction();
    }

};

class Photo: public Shape{
    private: int size;
    public:
    Photo() {
        size = (rand() % 20) + 50;
        clickCount = 0;
        speed = 1; 
		color = (rand() % 15) + 1; //ngerandom color
       

        x = rand() % (1280 - size * 2) + size;
        y = rand() % (720 - size * 2) + size;

        direction();
    }

     void draw() override {
       setfillstyle(SOLID_FILL, color);
        bar(x - size, y - size, x + size, y + size);
        readimagefile("D:/Code/ProlanVScode/Home/media/mm.bmp", x - size, y - size, x + size, y + size);
    }
    bool clicked(int mx, int my) override {
        if (mx >= (x - size) && mx <= (x + size) &&
            my >= (y - size) && my <= (y + size)) {
                PlaySound(TEXT("D:/Code/ProlanVScode/Home/media/faaah.wav"), NULL, SND_FILENAME | SND_ASYNC);

            return true;
        }
        return false;
    }
    void increaseStats() override {
        clickCount++;
        speed++;
        x = rand() % (1280 - size * 2) + size;
        y = rand() % (720 - size * 2) + size;
		direction();
    }



};




int main() {
 
    initwindow(1280, 720, "5024251066");
    srand(time(0));

    
    vector<Shape*> target;
    target.push_back(new Photo());
    target.push_back(new Circle());
	Mouse mouse;

    int totalClicks = 0;
    int page = 0;
 
    while (!kbhit()) {
        setactivepage(page);
        cleardevice();

        mouse.update();

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            bool hit = false;

            for (int i = 0; i < target.size(); i++) {
                if (target[i]->clicked(mx, my)) {
                    target[i]->increaseStats();
                    totalClicks++;
                    
                    hit = true;
                    break; 
                }
            }

            if (hit) {
                target.push_back(new Circle());
                target.push_back(new Photo());
            }
        }

        
        for (int i = 0; i < target.size(); i++) {
            target[i]->move();
            target[i]->draw();
        }

		mouse.chrosshair();

        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        char scoreText[50];
        sprintf(scoreText, "score: %d", totalClicks);
        outtextxy(10, 10, scoreText);

        setvisualpage(page);
        page = 1 - page;


        delay(10);
    }

    getch();
    return 0;
}