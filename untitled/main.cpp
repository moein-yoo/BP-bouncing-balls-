#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

SDL_Window *m_window;
SDL_Renderer *m_renderer;
SDL_Event* e = new SDL_Event();
SDL_Texture *img = NULL;
SDL_Texture *bimg = NULL;

double w=800;
double h=450;

int r=10;

int x_cannon = w / 2-25;
int y_cannon = h - 100;

double x, y;
double dx, dy=-1;
double x_0, y_0;
double x_col, y_col;

int rang0 = 0xffff9000; int rang1 = 0xff0090ff; int rang2 = 0xff9000ff; int rang3 = 0xff90ff00;int rang4 = 0xff00ff90;


struct ball{
    int x;
    int y;
};vector<ball> toop(50);


void start(){
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    SDL_Init(SDL_flags);
    SDL_CreateWindowAndRenderer(w, h, WND_flags, &m_window, &m_renderer);
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    //SDL_GetCurrentDisplayMode(0, &DM);
    //SDL_RenderClear(m_renderer);
}

void fill_ball(vector<ball> &toop){
    for (int i = 0; i < toop.size() ; ++i) {
        toop[i].x=(i+1)*20;
        toop[i].y=100;
    }
}

void draw_ball(SDL_Renderer *Renderer, vector<ball> toop){
    for (int i = 0; i < toop.size(); ++i) {
        filledCircleColor(Renderer,toop[i].x, toop[i].y, 10, 0xff0022ff);
        SDL_RenderPresent(m_renderer);
        SDL_RenderClear(m_renderer);
    }
}

double cannon_angle(double x, double y) {
    double angle = atan((h-y)/ (x - w/2));
    if (angle<0) angle+=M_PI;
    angle*=180;
    angle/=M_PI;
    angle=-angle;
    angle+=90;
    return angle;
}


void help(){
    for (int i = 1; 1 ; ++i) {
        filledCircleColor(m_renderer, x_0+i*dx, y_0+i, 0.5, rang0);
        i++;
        filledCircleColor(m_renderer, x_0+i*dx, y_0+i, 0.2, rang1);
    }

}
//void hit(vector<ball> &toop, bool clicked=true,double xplus, double yplus){
//    for (int i = 0; i < toop.size(); ++i) {
//        if (pow((x_0-toop[i].x),2)+pow((y_0-toop[i].y),2)<=pow(r,2)){
//            x_c
//            toop.push_back(shot);
//        }
//    }
//}




int main(int argc, char* argv[]) {
    srand(time(0));


    start();
    int img_w, img_h;

    int rang=rand()%5;




    switch (rang){
        case 0:
            rang = rang0;
            break;
        case 1:
            rang = rang1;
            break;
        case 2:
            rang = rang2;
            break;
        case 3:
            rang = rang3;
            break;
        case 4:
            rang = rang4;
        default:
            break;
    }


    fill_ball(toop);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);


    bool clicked = false;
    while (true) {
        x_0=w/2; y_0=h/2;

        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_renderer);

        while (!clicked) {

//            SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
//            SDL_RenderClear(m_renderer);
            //            SDL_Texture* bimg = IMG_LoadTexture(m_renderer, "bimg.png");
//            SDL_QueryTexture(bimg, NULL, NULL, &img_w, &img_h);
//            SDL_Rect bimg_rect;
//            bimg_rect.x = x_cannon;
//            bimg_rect.y = y_cannon;
//            bimg_rect.w = 500;
//            bimg_rect.h = h;
//            SDL_RenderCopy(m_renderer, bimg, NULL, &bimg_rect);
//

            draw_ball(m_renderer, toop);

            x = e->button.x;
            y = e->button.y;
            dx = (x - w / 2) * -5 / (y - h);

            img = IMG_LoadTexture(m_renderer, "cannon.png");
            SDL_QueryTexture(img, NULL, NULL, &img_w, &img_h);
            SDL_Rect img_rect;
            img_rect.x = x_cannon;
            img_rect.y = y_cannon;
            img_rect.w = 50;
            img_rect.h = 100;
            SDL_Point center = {img_rect.w / 2, img_rect.h};
            SDL_RenderCopyEx(m_renderer, img, NULL, &img_rect, cannon_angle(x, y), &center, SDL_FLIP_NONE);

            filledCircleColor(m_renderer, x_0, y_0, r, rang);
            SDL_RenderPresent(m_renderer);
            SDL_RenderClear(m_renderer);

            while (SDL_PollEvent(e)) {
                if (e->type == SDL_MOUSEBUTTONDOWN) clicked = true;
                if (e->type == SDL_QUIT) {
                    SDL_DestroyWindow(m_window);
                    SDL_DestroyRenderer(m_renderer);
                    SDL_Quit();
                    return 0;
                }
                SDL_RenderPresent(m_renderer);
                SDL_Delay(16);
                SDL_RenderClear(m_renderer);
            }


            while (clicked) {

                //                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
//                SDL_RenderClear(m_renderer);
//                SDL_Texture* bimg = IMG_LoadTexture(m_renderer, "bimg.png");
//                SDL_QueryTexture(bimg, NULL, NULL, &img_w, &img_h);
//                SDL_Rect bimg_rect;
//                bimg_rect.x = x_cannon;
//                bimg_rect.y = y_cannon;
//                bimg_rect.w = 500;
//                bimg_rect.h = h;
//                SDL_RenderCopy(m_renderer, bimg, NULL, &bimg_rect);

                draw_ball(m_renderer, toop);

                img = IMG_LoadTexture(m_renderer, "cannon.png");
                SDL_QueryTexture(img, NULL, NULL, &img_w, &img_h);
                SDL_Rect img_rect;
                img_rect.x = x_cannon;
                img_rect.y = y_cannon;
                img_rect.w = 50;
                img_rect.h = 100;
                SDL_Point center = {img_rect.w / 2, img_rect.h};
                SDL_RenderCopyEx(m_renderer, img, NULL, &img_rect, cannon_angle(x, y), &center, SDL_FLIP_NONE);

                x_0 += dx;
                y_0 += dy;

                filledCircleColor(m_renderer, x_0, y_0, r, 0xff0000ff);
                SDL_RenderPresent(m_renderer);
                SDL_RenderClear(m_renderer);
                //hit(toop, clicked);

                while (SDL_PollEvent(e)) {
                    if (e->type == SDL_QUIT) {
                        SDL_DestroyWindow(m_window);
                        SDL_DestroyRenderer(m_renderer);
                        SDL_Quit();
                        return 0;
                    }
                }
                SDL_RenderPresent(m_renderer);
                SDL_Delay(1);
                SDL_RenderClear(m_renderer);
            }
        }
    }
}