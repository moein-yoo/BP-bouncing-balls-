#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <ctime>
#include <vector>
#include <string>

using namespace std;
SDL_Window * m_window;
SDL_Renderer * m_renderer;
SDL_Texture *bkImg = NULL;
SDL_Event *e = new SDL_Event();
float K = 1;
int W = K*1600, H = K*900;
int radious = 25;
int tedadhazf = 0;int maxY = 25;
int rang0 = 0xffff9000; int rang1 = 0xff0090ff; int rang2 = 0xff9000ff; int rang3 = 0xff90ff00;int rang4 = 0xff00ff90;

struct ball{
    int x,y;
    int rang;
    bool gofl;
    bool flagcheck;
};vector<ball> toop;

struct bal{
    int rang;
    bool flagcheck;
    bool vojood;
};bal top[1355][1055];bal hazfi[1355][1055];

vector<int> hazfii;
void print_asli();
void print_asl();
void print_top();
void search_vec(ball shoot);
void bombing(int x,int y);

int main( int argc, char * argv[] ){
    srand(time(0));
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/;

    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( W, H, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    bkImg = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, W, H);
    SDL_SetRenderDrawColor( m_renderer, 0, 50, 0, 255 );
    SDL_SetRenderTarget(m_renderer,bkImg);
    SDL_RenderClear( m_renderer );
    stringColor(m_renderer,200,200,"Try another one",0xFFFFFFFF);
    SDL_SetRenderTarget(m_renderer,NULL);
    SDL_RenderPresent(m_renderer);
    SDL_RenderCopy(m_renderer,bkImg,NULL,NULL);
    SDL_SetRenderTarget(m_renderer,bkImg);

    while(true){
        //menu asli
        //vared bazi shavim bayad bool zir ok shavad
        bool bazi = true;
        print_asli();
        e->type = 0;
        while(e->type != SDL_KEYDOWN) {
            SDL_PollEvent(e);
        }
        while(bazi){
            ball shoot;
            e->type = 0;
            while(e->type != SDL_MOUSEBUTTONDOWN) {
                if(e->key.keysym.sym == SDLK_0) {
                    bazi = false;
                    break;
                }
                SDL_PollEvent(e);
                print_top();
            }
            if(!bazi)
                break;
            int x,y;
            x = e->button.x,y = e->button.y;
            bool f = false;
            e->type = 0;
            if(top[x][y].vojood)
                f = true;
            for (int i = 0; i <= 50 && !f; ++i) {
                for (int j = 0; j <= 50 && !f; ++j) {
                    if(top[x+i][y+j].vojood){
                        f = true;
                        x += i;
                        y += j;
                    }
                    else if(top[x+i][y].vojood) {
                        f = true;
                        x += i;
                    }
                    else if(top[x-i][y].vojood) {
                        f = true;
                        x -= i;
                    }
                    else if(top[x][y+j].vojood) {
                        f = true;
                        y += j;
                    }
                    else if(top[x][y-j].vojood) {
                        f = true;
                        y -= j;
                    }
                    else if(top[x+i][y-j].vojood){
                        f = true;
                        x += i;
                        y -= j;
                    }
                    else if(top[x-i][y+j].vojood){
                        f = true;
                        x -= i;
                        y += j;
                    }
                    else if(top[x-i][y-j].vojood){
                        f = true;
                        x -= i;
                        y -= j;
                    }
                }
            }
            shoot.x = x;shoot.y = y;
            shoot.rang = top[x][y].rang;
//            shoot.x = toop[50].x;shoot.y = toop[50].y;
//            shoot.rang = toop[50].rang;
            //mouse harekat
            //barkhord function ke x , y toop shoot shode ra bedahad

            //agar rooye pause ha nabashad
            search_vec(shoot);
            bool bale = false;
            if(tedadhazf>2)
                bale = true;
            for (int i = 300; i <= 1300; ++i) {
                for (int j = 0; j < 1000; ++j) {
                    if(hazfi[i][j].vojood){
                        top[i][j].vojood = !bale;top[i][j].flagcheck = false;
                        hazfi[i][j].vojood = false;
                    }
                }
            }
            tedadhazf = 0;
            print_top();
            //bombing(x,y);
            SDL_RenderPresent(m_renderer);
//            while(e->type != SDL_KEYDOWN) {
//                SDL_PollEvent(e);
//            }
            if(e->key.keysym.sym == SDLK_0)
                break;
        }
        e->type = 0;
        while(e->type != SDL_KEYDOWN) {
            SDL_PollEvent(e);
        }
        if(e->type != 0)
            break;
    }
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void print_asl(){
    int x = 0,y = 25;
    int d = 50,k = rand()%3,rang = rand()%5;
    int radif = 0;
    while(radif < K*6) {
        if(k!=0) {
            k--;
        }
        else{
            k = rand()%3;
            rang = rand()%5;
        }
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
        top[x][y].rang = rang;
        cout << "log";
        top[x][y].vojood = true;
        if(x+d > 1000) {
            d = -d;
            y += 50;
            radif++;
        }
        else if(x+d < 0) {
            d = -d;
            y += 50;
            radif++;
        }
        else{
            x += d;
        }
    }
    SDL_SetRenderTarget(m_renderer,NULL);
    for (int i = 0; i < 1000; i+=50) {
        for (int j = 0; j < 1000; j+=50) {
            if(top[i][j].vojood == true)
                filledCircleColor(m_renderer,i+300,j,radious,top[i][j].rang);
            SDL_RenderPresent(m_renderer);
        }
        //SDL_Delay(50);
    }
}

void print_asli(){
    int x = 300,y = 25;
    int d = 50,k = rand()%3,rang = rand()%5;
    ball jadid;
    int radif = 0;
    while(radif < K*6) {
        jadid.x = x;
        jadid.y = y;
        if(k!=0) {
            k--;
        }
        else{
            k = rand()%3;
            rang = rand()%5;
        }
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
        jadid.rang = rang;
        if(x+d > 1300) {
            d = -d;
            y += 50;
            radif++;
        }
        else if(x+d < 300) {
            d = -d;
            y += 50;
            radif++;
        }
        else{
            x += d;
        }
        toop.push_back(jadid);
    }
    SDL_SetRenderTarget(m_renderer,NULL);
    for (int i = toop.size()-1; i >= 0; --i) {
        top[toop[i].x][toop[i].y].rang = toop[i].rang;
        top[toop[i].x][toop[i].y].vojood = true;
        filledCircleColor(m_renderer,toop[i].x,toop[i].y,radious,toop[i].rang);
        SDL_RenderPresent(m_renderer);
        //SDL_Delay(50);
    }
}

void print_top(){
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer,bkImg,NULL,NULL);
    for (int i = 1300; i > 0; i--) {
        for (int j = 1000; j >= 0; j--) {
            if(top[i][j].vojood){
                top[i][j+1].vojood = top[i][j].vojood,top[i][j+1].rang = top[i][j].rang;
                top[i][j].vojood = false;
                filledCircleColor(m_renderer,i,j+1,radious,top[i][j+1
                ].rang);
            }
        }
    }
    SDL_Delay(100);
    SDL_RenderPresent(m_renderer);
}

void search_vec(ball shoot){
    int x = shoot.x,y = shoot.y;
    hazfi[x][y].vojood = true;
    if(top[x-50][y].vojood && top[x-50][y].rang == shoot.rang && !top[x-50][y].flagcheck){
        ball shoot1;
        top[x-50][y].flagcheck = true;
        hazfi[x-50][y].vojood = true;
        tedadhazf++;
        shoot1.x = x-50; shoot1.y = y;shoot1.rang = top[x-50][y].rang;
        search_vec(shoot1);
    }
    if(top[x+50][y].vojood && top[x+50][y].rang == shoot.rang && !top[x+50][y].flagcheck){
        ball shoot1;
        top[x+50][y].flagcheck = true;
        hazfi[x+50][y].vojood = true;
        tedadhazf++;
        shoot1.x = x+50; shoot1.y = y;shoot1.rang = top[x+50][y].rang;
        search_vec(shoot1);
    }
    if(top[x][y-50].vojood && top[x][y-50].rang == shoot.rang && !top[x][y-50].flagcheck){
        ball shoot1;
        top[x][y-50].flagcheck = true;
        hazfi[x][y-50].vojood = true;
        tedadhazf++;
        shoot1.x = x; shoot1.y = y-50;shoot1.rang = top[x][y-50].rang;
        search_vec(shoot1);
    }
    if(top[x][y+50].vojood && top[x][y+50].rang == shoot.rang && !top[x][y+50].flagcheck){
        ball shoot1;
        top[x][y+50].flagcheck = true;
        hazfi[x][y+50].vojood = true;
        tedadhazf++;
        shoot1.x = x; shoot1.y = y+50;shoot1.rang = top[x][y+50].rang;
        search_vec(shoot1);
    }
}

void bombing(int x,int y){
    SDL_Texture *bombing1 = IMG_LoadTexture(m_renderer,"bombing1");
    int img_w,img_h;
    SDL_Rect *img_rect;
    //SDL_QueryTexture(bombing1, NULL, NULL, &img_w, &img_h);
    img_rect->x = x;
    img_rect->y = y;
    img_rect->w = 50;
    img_rect->h = 50;
//    SDL_SetTextureBlendMode(bombing1, SDL_BLENDMODE_BLEND);
//    SDL_SetTextureAlphaMod(bombing1, 100);
    // copy the texture to the rendering context
    SDL_SetRenderTarget(m_renderer,NULL);
    SDL_RenderCopy(m_renderer, bombing1, NULL, img_rect);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(1000);
//    SDL_RenderCopy(m_renderer,bkImg,NULL,NULL);
    SDL_DestroyTexture(bombing1);
}