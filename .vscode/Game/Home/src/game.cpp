#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

//tombol
class Click{
    private: int x1,y1,x2,y2;
             int gotoscene;
    public:
    //zona click
     Click(int ax,int ay,int bx,int by,int goscene){
        x1 = ax;
        y1 = ay;
        x2 = bx;
        y2 = by;
        gotoscene = goscene;
     }
     //check
     bool isClicked(int mouseX, int mouseY) {
        return (mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2);
    }
     //ngambil gotoscene
    int getScene() { return gotoscene; };

    void drawbox(){
        setcolor(RED);
        rectangle(x1,y1,x2,y2);
    }
};


class Scene{
    private: 
    bool haschoice;
    string imageFile;
    vector<Click> choices;
    int nextscene;
    public:
    //gak ada pilihan dialog
        Scene(string filename,int next){
        imageFile = filename;
        nextscene =  next;
        haschoice = false;
        }

    //ada
        Scene(string filename){
        imageFile = filename;
        haschoice = true;
        nextscene = -1;
        }

        void areaChoice(int ax,int ay,int bx,int by,int goscene){
            choices.push_back(Click(ax,ay,bx,by,goscene));
        }

        void draw(){
            readimagefile(imageFile.c_str(),0,0,800,600);
            for(int i=0;i<choices.size();i++){
                choices[i].drawbox();
            }
        }

        int input(){
            while (true){
                if(ismouseclick(WM_LBUTTONDOWN)){
                    int mouseX, mouseY;
                    getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(!haschoice){
                        return nextscene;

                    }else{
                        for(int i=0;i<choices.size();i++){
                            if(choices[i].isClicked(mouseX, mouseY)){
                                return choices[i].getScene();
                            }
                        }
                    }
                }
                delay(50);
            }
            
        }





    };










int main(){

    int gd = DETECT, gm;
    initwindow(800,600,"dialog");

    Scene dia_1("../media/dia_1.bmp",2);
    Scene resp_1("../media/resp_1.bmp");

    //lu siapa mpruy
    resp_1.areaChoice(124, 312, 443, 394, 3);

    //ini lab ..
    resp_1.areaChoice(124, 461, 441, 543, 4);

    Scene dia_resp_1_a("../media/dia_resp_1_a.bmp",00);///end ulang lagi
    Scene dia_resp_1_b("../media/dia_resp_1_b.bmp",5);

    int currentScene = 1;
    bool playing = true;

    while(playing){
        cleardevice();
        switch(currentScene){
            case 1:
                dia_1.draw();
                currentScene = dia_1.input();
                break;
            case 2:
                resp_1.draw();
                currentScene = resp_1.input();
                break;
            case 3:
                dia_resp_1_a.draw();
                currentScene = dia_resp_1_a.input();
                break;
            case 4:
                dia_resp_1_b.draw();
                currentScene = dia_resp_1_b.input();
                break;
            case 00:
                playing = false;
                break;
            
        }
    }

    closegraph();
    return 0;





}