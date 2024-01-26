#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
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
SDL_Texture *game_over_page = nullptr;
SDL_Texture *infinity_mode = nullptr;   SDL_Texture *timer_mode = nullptr;  SDL_Texture *normal_mode = nullptr;
SDL_Texture *setting_page_scoreboard = nullptr; SDL_Texture *setting_page_change_music = nullptr; SDL_Texture *setting_page_sound_off = nullptr;
SDL_Texture *setting_page_sound_on = nullptr;SDL_Texture *setting_page_volume = nullptr;

Mix_Music *game_over_music = nullptr;   Mix_Music *soundnum0 = nullptr; Mix_Music *soundnum1 = nullptr;
Mix_Music *soundnum2 = nullptr; Mix_Music *soundnum3 = nullptr;

SDL_Event *e = new SDL_Event();
int K = 1;
int W = K*1600, H = K*900;
double radious = 25;
int tedadhazf = 0;int maxY = 25;
int rang0 = 0xffff9000; int rang1 = 0xff0090ff; int rang2 = 0xff9000ff; int rang3 = 0xff90ff00;int rang4 = 0xff00ff90;
bool sound = true;int soundnum = 0;int volumee = 64;

struct ball{
    int x,y;
    int rang;
    bool gofl;
    bool flagcheck;
};vector<ball> toop;

//font=2 -> Arial rounded bold
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
void game_over();
void sound_play();

//############*************  MOEIN  *************##############
bool bazi = true, running = true, bazi_infinity = false, bazi_normal = true, bazi_timer = false, gameover = false;

int main( int argc, char * argv[] ){
    srand(time(nullptr));
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/;

    SDL_Init( SDL_flags );
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
    Mix_VolumeMusic(volumee);
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
    login_page = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\login_page.jpg)");
    sign_up_page = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\sign_up_page.jpg)");
    setting_page = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\setting_page.jpg)");
    mode_page = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\mode_page.jpg)");
    game_over_page = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\game_over_page.png)");
    infinity_mode = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\infinity_mode.png)");
    timer_mode = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\timer_mode.png)");
    normal_mode = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\normal_mode.png)");
    setting_page_volume = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\volume.png)");
    setting_page_sound_on = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\sound_on.png)");
    setting_page_sound_off = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\sound_off.png)");
    setting_page_scoreboard = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\scoreboard.png)");
    setting_page_change_music = IMG_LoadTexture(m_renderer, R"(C:\Users\moein\Desktop\SUT\BP\project\aks ha\change_music.png)");

    game_over_music = Mix_LoadMUS(R"(C:\Users\moein\Desktop\SUT\BP\project\music ha\game_over_music.mp3)");
    soundnum0 = Mix_LoadMUS(R"(C:\Users\moein\Desktop\SUT\BP\project\music ha\soundnum0.mp3)");
    soundnum1 = Mix_LoadMUS(R"(C:\Users\moein\Desktop\SUT\BP\project\music ha\soundnum1.mp3)");
    soundnum2 = Mix_LoadMUS(R"(C:\Users\moein\Desktop\SUT\BP\project\music ha\soundnum2.mp3)");
    soundnum3 = Mix_LoadMUS(R"(C:\Users\moein\Desktop\SUT\BP\project\music ha\soundnum3.mp3)");
    sound_play();
    sound = true;

    while(running){
        if (sound && !Mix_PlayingMusic()) {
            soundnum = (soundnum + 1) % 4;
            sound_play();
        }
        bazi_infinity=false;bazi_normal = false;bazi_timer = false;bazi = false;
        e->type = 0;
        toop.clear();
        print_asli();
        main_menu();
        while(e->type != SDL_MOUSEBUTTONDOWN && e->type != SDL_KEYDOWN) {
            SDL_PollEvent(e);
        }
        if(e->type == SDL_QUIT)
            break;
        int x,y;
        x = e->button.x,y = e->button.y;
        chase_mouse_menu(x,y);
        if(!running)
            break;
        if(bazi)game_render();
        while(bazi){
            ball shoot{};
            if (sound && !Mix_PlayingMusic()) {
                soundnum = (soundnum + 1) % 4;
                sound_play();
            }
            e->type = 0;
            while(e->type != SDL_MOUSEBUTTONDOWN) {
                if (e->key.keysym.sym == SDLK_0) {
                    bazi = false;
                    break;
                }
                SDL_PollEvent(e);
                print_top();
                if (sound && !Mix_PlayingMusic()) {
                    soundnum = (soundnum + 1) % 4;
                    sound_play();
                }
                if(maxY > 675){
                    break;
                }
            }
            if(maxY > 675){
                game_over();
                break;
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
            if(maxY > 675){
                game_over();
                break;
            }
        }
    }

    SDL_DestroyTexture(menu_img);SDL_DestroyTexture(menu_img_login);SDL_DestroyTexture(menu_img_setting);
    SDL_DestroyTexture(menu_img_sign_up);SDL_DestroyTexture(menu_img_start);SDL_DestroyTexture(menu_img_help_desk);
    SDL_DestroyTexture(exit_img);

    SDL_DestroyTexture(game_page);SDL_DestroyTexture(login_page);SDL_DestroyTexture(sign_up_page);
    SDL_DestroyTexture(setting_page);SDL_DestroyTexture(mode_page);SDL_DestroyTexture(game_over_page);
    SDL_DestroyTexture(setting_page_change_music);SDL_DestroyTexture(setting_page_scoreboard);
    SDL_DestroyTexture(setting_page_sound_off);SDL_DestroyTexture(setting_page_sound_on);
    SDL_DestroyTexture(setting_page_volume);

    SDL_DestroyTexture(infinity_mode);SDL_DestroyTexture(timer_mode);SDL_DestroyTexture(normal_mode);

    Mix_FreeMusic(game_over_music);Mix_FreeMusic(soundnum0);Mix_FreeMusic(soundnum1);
    Mix_FreeMusic(soundnum2);Mix_FreeMusic(soundnum3);
    Mix_CloseAudio();
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    IMG_Quit();
    SDL_Quit();
    return 0;
}

//############*************  MOEIN  *************##############
void print_asli(){
    int x = 325,y = 390;
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
    maxY = 25;
    for (auto & i : toop) {
        filledCircleColor(m_renderer, i.x, ++i.y, radious, i.rang);
        if(maxY < i.y)
            maxY = i.y;
    }
    SDL_Delay(70);
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
    e->type = 0;
    int w,h;
    SDL_QueryTexture(menu_img,nullptr,nullptr,&w,&h);
    SDL_Rect menu_img_rect; menu_img_rect.x = 0; menu_img_rect.y = 0; menu_img_rect.w = 1600; menu_img_rect.h = 900;
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

    string str = "M&E Presents";
    textRGBA(m_renderer,700,200,str.c_str(),2,100,150,40,40,255);

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
    if(gameover){
        //SDL_Delay(6500);
        e->type = 0;
        while(e->type != SDL_MOUSEBUTTONDOWN) {
            SDL_PollEvent(e);
        }
        x = e->button.x,y = e->button.y;
        gameover = false;
    }
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
    SDL_RenderClear(m_renderer);
    int w,h;
    SDL_QueryTexture(login_page,nullptr,nullptr,&w,&h);
    SDL_Rect login_page_rect; login_page_rect.x = 0; login_page_rect.y = 0; login_page_rect.w = 1600; login_page_rect.h = 900;
    SDL_RenderCopy(m_renderer,login_page,nullptr,&login_page_rect);
    SDL_RenderPresent(m_renderer);
    e->type = 0;
    while(e->type != SDL_KEYDOWN)SDL_PollEvent(e);
    bazi = false;
}
void setting(){
    SDL_RenderClear(m_renderer);
    int w,h;
    SDL_QueryTexture(setting_page,nullptr,nullptr,&w,&h);
    SDL_Rect setting_page_rect; setting_page_rect.x = 0; setting_page_rect.y = 0; setting_page_rect.w = 1600; setting_page_rect.h = 900;
    SDL_RenderCopy(m_renderer,setting_page,nullptr,&setting_page_rect);
    int w_scoreboard,h_scoreboard;
    SDL_QueryTexture(setting_page_scoreboard,nullptr,nullptr,&w_scoreboard,&h_scoreboard);
    SDL_Rect setting_page_scoreboard_rect; setting_page_scoreboard_rect.x = 300; setting_page_scoreboard_rect.y = 100; setting_page_scoreboard_rect.w = w_scoreboard; setting_page_scoreboard_rect.h = h_scoreboard;
    SDL_RenderCopy(m_renderer,setting_page_scoreboard,nullptr,&setting_page_scoreboard_rect);
    int w_sound_on,h_sound_on;
    SDL_QueryTexture(setting_page_sound_on,nullptr,nullptr,&w_sound_on,&h_sound_on);
    SDL_Rect setting_page_sound_on_rect; setting_page_sound_on_rect.x = 600; setting_page_sound_on_rect.y = 400; setting_page_sound_on_rect.w = w_sound_on; setting_page_sound_on_rect.h = h_sound_on;
    SDL_RenderCopy(m_renderer,setting_page_sound_on,nullptr,&setting_page_sound_on_rect);
    int w_sound_off,h_sound_off;
    SDL_QueryTexture(setting_page_sound_off,nullptr,nullptr,&w_sound_off,&h_sound_off);
    SDL_Rect setting_page_sound_off_rect; setting_page_sound_off_rect.x = 300; setting_page_sound_off_rect.y = 400; setting_page_sound_off_rect.w = w_sound_off; setting_page_sound_off_rect.h = h_sound_off;
    SDL_RenderCopy(m_renderer,setting_page_sound_off,nullptr,&setting_page_sound_off_rect);
    int w_volume,h_volume;
    SDL_QueryTexture(setting_page_volume,nullptr,nullptr,&w_volume,&h_volume);
    SDL_Rect setting_page_volume_rect; setting_page_volume_rect.x = 450; setting_page_volume_rect.y = 600; setting_page_volume_rect.w = w_volume; setting_page_volume_rect.h = h_volume;
    SDL_RenderCopy(m_renderer,setting_page_volume,nullptr,&setting_page_volume_rect);
    int w_change_music,h_change_music;
    SDL_QueryTexture(setting_page_change_music,nullptr,nullptr,&w_change_music,&h_change_music);
    SDL_Rect setting_page_change_music_rect; setting_page_change_music_rect.x = 600; setting_page_change_music_rect.y = 100; setting_page_change_music_rect.w = w_change_music; setting_page_change_music_rect.h = h_change_music;
    SDL_RenderCopy(m_renderer,setting_page_change_music,nullptr,&setting_page_change_music_rect);
    int w_exit,h_exit;
    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    SDL_RenderPresent(m_renderer);
    while(true) {
        e->type = 0;
        while (e->type != SDL_MOUSEBUTTONDOWN)SDL_PollEvent(e);
        int x = e->button.x, y = e->button.y;
        if (x > 300 && x < 300 + w_scoreboard && y > 100 && y < 100 + h_scoreboard) {
            exit_page(false);

        } else if (x > 600 && x < 600 + w_sound_on && y > 400 && y < 400 + h_sound_on) {
            exit_page(false);

        } else if (x > 300 && x < 300 + w_sound_off && y > 400 && y < 400 + h_sound_off) {
            exit_page(false);

        } else if (x > 450 && x < 450 + w_volume && y > 600 && y < 600 + h_volume) {
            if (x < 450 + w_volume / 2) {
                Mix_VolumeMusic(volumee - 20);
                volumee -= 20;
            }
            else{
                Mix_VolumeMusic(volumee+20);
                volumee +=20;
            }
        } else if (x > 600 && x < 600 + w_change_music && y > 100 && y < 100 + h_change_music) {
            Mix_HaltMusic();
            soundnum = (soundnum+1)%4;
            sound_play();
        } else if (x > 1400 && x < 1550 && y > 700 && y < 850) {
            exit_page(false);
            break;
        }
    }
    bazi = false;
}
void mode() {
    SDL_RenderClear(m_renderer);
    int w, h;
    SDL_QueryTexture(mode_page, nullptr, nullptr, &w, &h);
    SDL_Rect mode_page_rect; mode_page_rect.x = 0; mode_page_rect.y = 0; mode_page_rect.w = 1600; mode_page_rect.h = 900;
    SDL_RenderCopy(m_renderer, mode_page, nullptr, &mode_page_rect);
    int w_infinity, h_infinity;
    SDL_QueryTexture(infinity_mode, nullptr, nullptr, &w_infinity, &h_infinity);
    SDL_Rect infinity_mode_rect;infinity_mode_rect.x = 550;infinity_mode_rect.y = 200;infinity_mode_rect.w = w_infinity;infinity_mode_rect.h = h_infinity;
    SDL_RenderCopy(m_renderer, infinity_mode, nullptr, &infinity_mode_rect);
    int w_timer, h_timer;
    SDL_QueryTexture(timer_mode, nullptr, nullptr, &w_timer, &h_timer);
    SDL_Rect timer_mode_rect; timer_mode_rect.x = 910; timer_mode_rect.y = 170; timer_mode_rect.w = w_timer; timer_mode_rect.h = h_timer;
    SDL_RenderCopy(m_renderer, timer_mode, nullptr, &timer_mode_rect);
    int w_normal, h_normal;
    SDL_QueryTexture(normal_mode, nullptr, nullptr, &w_normal, &h_normal);
    SDL_Rect normal_mode_rect; normal_mode_rect.x = 730; normal_mode_rect.y = 70; normal_mode_rect.w = w_normal; normal_mode_rect.h = h_normal;
    SDL_RenderCopy(m_renderer, normal_mode, nullptr, &normal_mode_rect);
    int w_exit,h_exit;
    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    SDL_RenderPresent(m_renderer);
    bool exiting_mode = false;
    do{
        e->type = 0;
        while (e->type != SDL_MOUSEBUTTONDOWN)SDL_PollEvent(e);
        int x = e->button.x, y = e->button.y;
        if (x > 550 && x < 550 + w_infinity && y > 200 && y < 200 + h_infinity) {
            bazi_infinity = true;
        }
        else if (x > 910 && x < 910 + w_timer && y > 170 && y < 170 + h_timer) {
            bazi_timer = true;
        }
        else if (x > 730 && x < 730 + w_normal && y > 70 && y < 70 + h_normal) {
            bazi_normal = true;
            bazi = true;
        }
        else if(x>1400 && x<1550 && y>700 && y <850){
            exit_page(false);
            exiting_mode = true;
        }
    }while(!bazi && !bazi_timer && !bazi_normal && !bazi_infinity && !exiting_mode);
}
void sign_up(){
    SDL_RenderClear(m_renderer);
    int w,h;
    SDL_QueryTexture(sign_up_page,nullptr,nullptr,&w,&h);
    SDL_Rect sign_up_page_rect; sign_up_page_rect.x = 0; sign_up_page_rect.y = 0; sign_up_page_rect.w = 1600; sign_up_page_rect.h = 900;
    SDL_SetRenderTarget(m_renderer,menu_img);
    SDL_RenderCopy(m_renderer,sign_up_page,nullptr,&sign_up_page_rect);
    SDL_RenderPresent(m_renderer);
    e->type = 0;
    while(e->type != SDL_KEYDOWN)SDL_PollEvent(e);
    bazi = false;
}
void help_desk(){
    bazi = false;
}
void exit_page(bool x) {
    if (x)
        running = false;
    else {
        bazi = false; bazi_infinity = false; bazi_normal = false; bazi_timer = false;
    }
}
void game_over(){
    SDL_RenderClear(m_renderer);
    int w, h;
    SDL_QueryTexture(game_over_page, nullptr, nullptr, &w, &h);
    SDL_Rect game_over_page_rect; game_over_page_rect.x = 0; game_over_page_rect.y = 0; game_over_page_rect.w = 1600; game_over_page_rect.h = 900;
    SDL_RenderCopy(m_renderer, game_over_page, nullptr, &game_over_page_rect);
    Mix_PlayMusic(game_over_music, 0);
    SDL_RenderPresent(m_renderer);
    while(Mix_PlayingMusic());
    gameover = true;
}
void sound_play(){
    switch (soundnum) {
        case 0:
            Mix_PlayMusic(soundnum0,0);
            break;
        case 1:
            Mix_PlayMusic(soundnum1,0);
            break;
        case 2:
            Mix_PlayMusic(soundnum2,0);
            break;
        case 3:
            Mix_PlayMusic(soundnum3,0);
            break;
    }
}

//############*************  MOEIN  *************##############
