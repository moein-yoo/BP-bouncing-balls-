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
SDL_Texture *bkImg = nullptr;
SDL_Texture *menu_img = nullptr;
SDL_Texture *menu_img_login = nullptr;
SDL_Texture *menu_img_setting = nullptr;
SDL_Texture *menu_img_sign_up = nullptr;
SDL_Texture *menu_img_start = nullptr;
SDL_Texture *menu_img_help_desk = nullptr;
SDL_Texture *exit_img = nullptr;

SDL_Texture *game_page = nullptr;
SDL_Texture *login_page = nullptr;     SDL_Texture *sign_up_page = nullptr;
SDL_Texture *setting_page = nullptr;   SDL_Texture *mode_page = nullptr;
SDL_Event *e = new SDL_Event();
int K = 1;
int W = K*1600, H = K*900;
double radious = 25;
int tedadhazf = 0;int maxY = 25;
int rang0 = 0xffff9000; int rang1 = 0xff0090ff; int rang2 = 0xff9000ff; int rang3 = 0xff90ff00;int rang4 = 0xff00ff90;
bool unlimited;
struct ball{
    int x,y;
    int rang;
    bool gofl;
    bool flagcheck;
};vector<ball> toop;


//############*************  MOEIN  *************##############

void print_asli();
void print_top();
void search_vec(ball shoot);
void bombing(int x,int y);
void main_menu();
void game_render();
void login();
void setting();
void mode();
void sign_up();
void help_desk();
void chase_mouse_menu(int x,int y);
void chase_mouse_run(int x,int y);
void exit_page(bool x);

//############*************  MOEIN  *************##############
bool bazi = true;   bool running = true;

int main( int argc, char * argv[] ){
    srand(time(nullptr));
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/;

    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( W, H, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    bkImg = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, W, H);
    SDL_SetRenderDrawColor( m_renderer, 0, 50, 0, 255 );
    SDL_RenderClear( m_renderer );
    stringColor(m_renderer,200,200,"Try another one",0xFFFFFFFF);
    SDL_SetRenderTarget(m_renderer,nullptr);

    menu_img = IMG_LoadTexture(m_renderer,R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\main_menu.jpg)");
    menu_img_login = IMG_LoadTexture(m_renderer,R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\login3.png)");
    menu_img_setting = IMG_LoadTexture(m_renderer,R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\settings.png)");
    menu_img_sign_up = IMG_LoadTexture(m_renderer,R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\sign_up.png)");
    menu_img_start = IMG_LoadTexture(m_renderer,R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\start.png)");
    menu_img_help_desk = IMG_LoadTexture(m_renderer,R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\help_desk.png)");
    game_page = IMG_LoadTexture(m_renderer,R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\G2PTeO.jpg)");
    exit_img = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\exit.png)");

    while(running){
        toop.clear();
        print_asli();
        e->type = 0;
        main_menu();
        while(e->type != SDL_MOUSEBUTTONDOWN && e->type != SDL_KEYDOWN) {
            SDL_PollEvent(e);
        }
        if(e->type == SDL_KEYDOWN)
            break;
        int x,y;
        x = e->button.x,y = e->button.y;
        chase_mouse_menu(x,y);
        if(!running)
            break;
        game_render();
        while(bazi){
            ball shoot{};
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
            x = e->button.x,y = e->button.y;
            bool run = false;
            chase_mouse_run(x,y);
            if(!bazi)
                break;
            for (int i = 0; i < toop.size(); ++i) {
                double fasele = sqrt((x - toop[i].x)*(x - toop[i].x) + (y - toop[i].y)*(y - toop[i].y));
                if(fasele <= radious){
                    x = i;
                    run = true;
                    break;
                }
            }
            if(!run)
                continue;
            e->type = 0;
            shoot.x = toop[x].x,shoot.y = toop[x].y,shoot.rang = toop[x].rang;
            //mouse harekat
            //barkhord function ke x , y toop shoot shode ra bedahad

            //agar rooye pause ha nabashad
            search_vec(shoot);
            if(tedadhazf<3){
                for (auto & i : toop) {
                    i.flagcheck = false;
                }
            }
            for (int i = 0; i < toop.size(); ++i) {
                if(toop[i].flagcheck){
                    toop[i].flagcheck = false;
                    toop.erase(toop.begin()+i);
                    i--;
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
    }

    SDL_DestroyTexture(menu_img);SDL_DestroyTexture(menu_img_login);SDL_DestroyTexture(menu_img_setting);
    SDL_DestroyTexture(menu_img_sign_up);SDL_DestroyTexture(menu_img_start);SDL_DestroyTexture(menu_img_help_desk);
    SDL_DestroyTexture(exit_img);
    SDL_DestroyTexture(game_page);SDL_DestroyTexture(login_page);SDL_DestroyTexture(sign_up_page);
    SDL_DestroyTexture(setting_page);SDL_DestroyTexture(mode_page);
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    IMG_Quit();
    SDL_Quit();
    return 0;
}

//############*************  MOEIN  *************##############
void print_asli(){
    int x = 325,y = -100;
    int d = 50,k = rand()%3,rang = rand()%5;
    ball jadid{};
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
        if(x+d > 1300 || x+d < 300) {
            d = -d;
            y += 50;
            radif++;
        }
        else{
            x += d;
        }
        jadid.flagcheck = false;
        toop.push_back(jadid);
    }
}

void print_top(){
    SDL_RenderClear(m_renderer);
    game_render();
    for (auto & i : toop)
        filledCircleColor(m_renderer,i.x,++i.y,radious,i.rang);
    SDL_Delay(100);
    SDL_RenderPresent(m_renderer);
}

void search_vec(ball shoot){
    for (auto & i : toop) {
        double fasele = sqrt((shoot.x - i.x)*(shoot.x - i.x) + (shoot.y - i.y)*(shoot.y - i.y));
        if(shoot.rang==i.rang && !i.flagcheck && fasele<=2*radious){
            ball shoot1;
            i.flagcheck = true;
            tedadhazf++;
            shoot1 = i;
            search_vec(shoot1);
        }
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
    SDL_SetRenderTarget(m_renderer,nullptr);
    SDL_RenderCopy(m_renderer, bombing1, nullptr, img_rect);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(1000);
//    SDL_RenderCopy(m_renderer,bkImg,NULL,NULL);
    SDL_DestroyTexture(bombing1);
}

void main_menu(){
    int w,h;
    SDL_QueryTexture(menu_img,nullptr,nullptr,&w,&h);
    SDL_Rect menu_img_rect; menu_img_rect.x = 0; menu_img_rect.y = 0; menu_img_rect.w = 1600; menu_img_rect.h = 900;
    SDL_SetRenderTarget(m_renderer,menu_img);
    SDL_RenderCopy(m_renderer,menu_img,nullptr,&menu_img_rect);
    SDL_RenderPresent(m_renderer);
    int w_login,h_login;
    SDL_QueryTexture(menu_img_login,nullptr,nullptr,&w_login,&h_login);
    SDL_Rect menu_img_login_rect; menu_img_login_rect.x = 300; menu_img_login_rect.y = 150; menu_img_login_rect.w = w_login; menu_img_login_rect.h = h_login;
    SDL_RenderCopy(m_renderer,menu_img_login,nullptr,&menu_img_login_rect);
    int w_setting,h_setting;
    SDL_QueryTexture(menu_img_setting,nullptr,nullptr,&w_setting,&h_setting);
    SDL_Rect menu_img_setting_rect; menu_img_setting_rect.x = 300; menu_img_setting_rect.y = 300; menu_img_setting_rect.w = w_setting; menu_img_setting_rect.h = h_setting;
    SDL_RenderCopy(m_renderer,menu_img_setting,nullptr,&menu_img_setting_rect);
    int w_sign_up,h_sign_up;
    SDL_QueryTexture(menu_img_sign_up,nullptr,nullptr,&w_sign_up,&h_sign_up);
    SDL_Rect menu_img_sign_up_rect; menu_img_sign_up_rect.x = 300; menu_img_sign_up_rect.y = 450; menu_img_sign_up_rect.w = w_sign_up; menu_img_sign_up_rect.h = h_sign_up;
    SDL_RenderCopy(m_renderer,menu_img_sign_up,nullptr,&menu_img_sign_up_rect);
    int w_start,h_start;
    SDL_QueryTexture(menu_img_start,nullptr,nullptr,&w_start,&h_start);
    SDL_Rect menu_img_start_rect; menu_img_start_rect.x = 300; menu_img_start_rect.y = 550; menu_img_start_rect.w = w_start; menu_img_start_rect.h = h_start;
    SDL_RenderCopy(m_renderer,menu_img_start,nullptr,&menu_img_start_rect);
    int w_help_desk,h_help_desk;
    SDL_QueryTexture(menu_img_help_desk,nullptr,nullptr,&w_help_desk,&h_help_desk);
    SDL_Rect menu_img_help_desk_rect; menu_img_help_desk_rect.x = 300; menu_img_help_desk_rect.y = 680; menu_img_help_desk_rect.w = w_help_desk; menu_img_help_desk_rect.h = h_help_desk;
    SDL_RenderCopy(m_renderer,menu_img_help_desk,nullptr,&menu_img_help_desk_rect);
    int w_exit,h_exit;
    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    SDL_RenderPresent(m_renderer);
}

void game_render(){
    int w,h;
    SDL_QueryTexture(game_page,nullptr,nullptr,&w,&h);
    SDL_Rect game_page_rect; game_page_rect.x = 0; game_page_rect.y = 0; game_page_rect.w = w*2; game_page_rect.h = h*2;
    //SDL_SetRenderTarget(m_renderer,menu_img);
    SDL_RenderCopy(m_renderer,game_page,nullptr,&game_page_rect);
    int w_exit,h_exit;
    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    //SDL_RenderPresent(m_renderer);

}
void chase_mouse_menu(int x,int y){
    if(x>300 && x<400 && y>150 && y<250){
        login();
    }
    else if(x>300 && x<400 && y>300 && y<400){
        setting();
    }
    else if(x>300 && x<400 && y>450 && y<495){
        sign_up();
    }
    else if(x>300 && x<400 && y>550 && y<640){
        mode();
    }
    else if(x>300 && x<400 && y>680 && y<780){
        help_desk();
    }
    else if(x>1400 && x<1550 && y>700 && y <850){
        exit_page(true);
    }
    else{
        bazi = false;
    }
}
void chase_mouse_run(int x,int y){
    if(x>1400 && x<1550 && y>700 && y <850){
        exit_page(false);
    }
}
void login(){
    bazi = false;
}
void setting(){
    bazi = false;
}
void mode(){
    bazi = true;
}
void sign_up(){
    bazi = false;
}
void help_desk(){
    bazi = false;
}
void exit_page(bool x){
    if(x)
        running = false;
    else
        bazi = false;
}
//############*************  MOEIN  *************##############
