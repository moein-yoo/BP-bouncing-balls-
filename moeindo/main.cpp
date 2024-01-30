#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
#include <ctime>
#include <vector>
#include <string>
#include <conio.h>
#include <chrono>
#include <fstream>

using namespace std;
fstream player_file;vector <int> player_data[2];vector <string> player_name;
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
SDL_Texture *game_over_page = nullptr;  SDL_Texture *win_page = nullptr;
SDL_Texture *infinity_mode = nullptr;   SDL_Texture *timer_mode = nullptr;  SDL_Texture *normal_mode = nullptr;
SDL_Texture *setting_page_scoreboard = nullptr; SDL_Texture *setting_page_change_music = nullptr; SDL_Texture *setting_page_sound_off = nullptr;
SDL_Texture *setting_page_sound_on = nullptr;SDL_Texture *setting_page_volume = nullptr;
SDL_Texture *cannon_img = nullptr;
SDL_Texture *pause_page = nullptr;SDL_Texture *pause_page_resume = nullptr;  SDL_Texture *pause_page_pause = nullptr;

Mix_Music *game_over_music = nullptr;   Mix_Music *win_music = nullptr;
Mix_Music *soundnum0 = nullptr; Mix_Music *soundnum1 = nullptr;
Mix_Music *soundnum2 = nullptr; Mix_Music *soundnum3 = nullptr;

SDL_Event *e = new SDL_Event();
int K = 1;
int W = K*1600, H = K*900;
double radious = 25;
int tedadhazf = 0;double maxY = 25,Miny = 300;
bool sound = true;int soundnum = 3;int volumee = 64;string username;
double dx,dy;double x_m,y_m;int a,b,c;int emtiaz = 0;

struct ball{
    double x,y;
    int rang;
    bool gofl;
    bool flagcheck;
};vector<ball> toop;ball shoot;

struct rang {
    int code;
    int v;
};rang color[6]={{static_cast<int>(0xffff9000),0}, {static_cast<int>(0xff0090ff),0},{static_cast<int>(0xff9000ff), 0},{static_cast<int>(0xff90ff00),0},{static_cast<int>(0xff00ff90),0},{static_cast<int>(0xff63637e),0}};

//font=2 -> Arial rounded bold
//############*************  MOEIN  *************##############

void print_asli();
void print_top();
void search_vec(ball shoot2);
void search_vec_jodaha(ball shoot2);
void bombing(int x,int y);
void main_menu();
void game_render();
void login();
void setting();
void scoreboard_p();
void mode();
void sign_up();
void help_desk();
void chase_mouse_menu(int x,int y);
void chase_mouse_game(int x,int y);
void exit_page(bool x);
void game_over();
void win();
void sound_play();
char check_char();
void pause();
//############*************  MOEIN  *************##############
//############*************  EMAD  *************##############
double cannon_angle(double x,double y);
void hit();
void create_shoot();
void help();
//############*************  EMAD  *************##############
bool bazi = true, running = true, bazi_infinity = false, bazi_normal = true, bazi_timer = false, gameover = false;

int main( int argc, char * argv[] ){
    srand(time(nullptr));
    player_file.open(R"(C:\Users\moein\Desktop\SUT\BP\project\moeindo\cmake-build-debug\player_file.txt)",ios::in);
    while(player_file.good()) {
        string s;int t1;int t2;
        player_file >> s >> t1 >> t2;
        player_data[0].push_back(t1);
        player_data[1].push_back(t2);
        player_name.push_back(s);
        cout << s;
    }
    a = rand()%5;b = rand()%5;
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

    menu_img = IMG_LoadTexture(m_renderer,R"(aks ha\main_menu.jpg)");
    menu_img_login = IMG_LoadTexture(m_renderer,R"(aks ha\login3.png)");
    menu_img_setting = IMG_LoadTexture(m_renderer,R"(aks ha\settings.png)");
    menu_img_sign_up = IMG_LoadTexture(m_renderer,R"(aks ha\sign_up.png)");
    menu_img_start = IMG_LoadTexture(m_renderer,R"(aks ha\start.png)");
    menu_img_help_desk = IMG_LoadTexture(m_renderer,R"(aks ha\help_desk.png)");
    game_page = IMG_LoadTexture(m_renderer,R"(aks ha\G2PTeO.jpg)");
    exit_img = IMG_LoadTexture(m_renderer, R"(aks ha\exit.png)");
    login_page = IMG_LoadTexture(m_renderer, R"(aks ha\login_page.jpg)");
    sign_up_page = IMG_LoadTexture(m_renderer, R"(aks ha\sign_up_page.jpg)");
    setting_page = IMG_LoadTexture(m_renderer, R"(aks ha\setting_page.jpg)");
    mode_page = IMG_LoadTexture(m_renderer, R"(aks ha\mode_page.jpg)");
    game_over_page = IMG_LoadTexture(m_renderer, R"(aks ha\game_over_page.png)");
    win_page = IMG_LoadTexture(m_renderer, R"(aks ha\win_page.png)");
    infinity_mode = IMG_LoadTexture(m_renderer, R"(aks ha\infinity_mode.png)");
    timer_mode = IMG_LoadTexture(m_renderer, R"(aks ha\timer_mode.png)");
    normal_mode = IMG_LoadTexture(m_renderer, R"(aks ha\normal_mode.png)");
    setting_page_volume = IMG_LoadTexture(m_renderer, R"(aks ha\volume.png)");
    setting_page_sound_on = IMG_LoadTexture(m_renderer, R"(aks ha\sound_on.png)");
    setting_page_sound_off = IMG_LoadTexture(m_renderer, R"(aks ha\sound_off.png)");
    setting_page_scoreboard = IMG_LoadTexture(m_renderer, R"(aks ha\scoreboard.png)");
    setting_page_change_music = IMG_LoadTexture(m_renderer, R"(aks ha\change_music.png)");
    cannon_img = IMG_LoadTexture(m_renderer, R"(aks ha\cannon.png)");
    pause_page = IMG_LoadTexture(m_renderer, R"(aks ha\pause_page.jpg)");
    pause_page_pause = IMG_LoadTexture(m_renderer, R"(aks ha\pause_page_pause.png)");
    pause_page_resume = IMG_LoadTexture(m_renderer, R"(aks ha\pause_page_resume.png)");

    game_over_music = Mix_LoadMUS(R"(music ha\game_over_music.mp3)");
    win_music = Mix_LoadMUS(R"(music ha\win_music.mp3)");
    soundnum0 = Mix_LoadMUS(R"(music ha\soundnum0.mp3)");
    soundnum1 = Mix_LoadMUS(R"(music ha\soundnum1.mp3)");
    soundnum2 = Mix_LoadMUS(R"(music ha\soundnum2.mp3)");
    soundnum3 = Mix_LoadMUS(R"(music ha\soundnum3.mp3)");
    sound_play();
    sound = true;

    while(running){
        bazi_infinity=false;bazi_normal = false;bazi_timer = false;bazi = false;
        e->type = 0;
        for (int i = 0; i < player_name.size(); ++i) {
            if(player_name[i] == username) {
                if (emtiaz == 0)
                    emtiaz = player_data[0][i];
                else
                    player_data[0][i] = emtiaz;
            }

        }
        toop.clear();
        print_asli();
        main_menu();
        while(e->type != SDL_MOUSEBUTTONDOWN && e->type != SDL_KEYDOWN) {
            if (sound && !Mix_PlayingMusic()) {
                soundnum = (soundnum + 1) % 4;
                sound_play();
            }
            SDL_PollEvent(e);
        }
        if(e->type == SDL_QUIT)
            break;
        x_m = e->button.x,y_m = e->button.y;
        chase_mouse_menu(x_m,y_m);
        if(!running)
            break;
        if(bazi)game_render();
        while(bazi){
            if(shoot.y != 875)
                create_shoot();
            if (sound && !Mix_PlayingMusic()) {
                soundnum = (soundnum + 1) % 4;
                sound_play();
            }
            e->type = 0;
            while(e->type != SDL_MOUSEBUTTONDOWN) {
                if (sound && !Mix_PlayingMusic()) {
                    soundnum = (soundnum + 1) % 4;
                    sound_play();
                }
                if (e->key.keysym.sym == SDLK_0) {
                    bazi = false;
                    break;
                }
                SDL_PollEvent(e);
                if(e->type == SDL_MOUSEWHEEL){
                    e->type = 0;
                    shoot.rang = color[b].code;
                    swap(a,b);
                }
                print_top();
                x_m = e->button.x;
                y_m = e->button.y;

                if(maxY > 775){
                    break;
                }
            }
            if(maxY > 775){
                game_over();
                break;
            }
            if(!bazi)
                break;
            x_m = e->button.x,y_m = e->button.y;
            if(x_m<300){
                pause();
            }
            if(x_m>300 && x_m<1300){
                dx =  (x_m - W / 2) * -7/ (y_m - H);
                dy = -7.0;
                hit();
                bool run = false;
                e->type = 0;

                search_vec(shoot);
                if(tedadhazf<3){
                    for (auto & i : toop) {
                        i.flagcheck = false;
                    }
                    shoot.flagcheck = false;
                    toop.push_back(shoot);
                    tedadhazf = 0;
                }
                for (int i = 0; i < toop.size(); ++i) {
                    if(toop[i].gofl && toop[i].flagcheck) {
                        toop[i].gofl = false;
                        toop[i].flagcheck = false;
                    }
                    if(toop[i].flagcheck){
                        toop.erase(toop.begin()+i);
                        i--;
                    }
                }
                for (auto & i : toop) {
                    if(i.y==Miny)
                        search_vec_jodaha(i);
                }
                for (int i = 0; i < toop.size(); ++i) {
                    if(!toop[i].flagcheck){
                        toop.erase(toop.begin()+i);
                        i--;
                    }
                }
                for(auto & i : toop) {
                    i.flagcheck = false;
                }
                emtiaz += 10*tedadhazf;
                tedadhazf = 1;
                //bombing(x,y);
                SDL_RenderPresent(m_renderer);
                if(e->key.keysym.sym == SDLK_0)
                    break;
                if(maxY > 775){
                    game_over();
                    break;
                }
                if(toop.empty()){
                    win();
                    break;
                }
            }
        }
    }
    player_file.close();
    player_file.open(R"(C:\Users\moein\Desktop\SUT\BP\project\moeindo\cmake-build-debug\player_file.txt)", ios::out);
    for (int i = 0; i < player_name.size(); ++i) {
        if(player_name[i] == username && !username.empty()){
            player_file << username << '\t' << emtiaz << '\t' << player_data[1][i] << '\n';
            continue;
        }
        string s;int t1;int t2;
        t1 = player_data[0][i];
        t2 = player_data[1][i];
        s = player_name[i];
        if(!s.empty())
            player_file << s << '\t' << t1 << '\t' << t2 << '\n';
    }
    player_file.close();

    SDL_DestroyTexture(menu_img);SDL_DestroyTexture(menu_img_login);SDL_DestroyTexture(menu_img_setting);
    SDL_DestroyTexture(menu_img_sign_up);SDL_DestroyTexture(menu_img_start);SDL_DestroyTexture(menu_img_help_desk);
    SDL_DestroyTexture(exit_img);

    SDL_DestroyTexture(game_page);SDL_DestroyTexture(login_page);SDL_DestroyTexture(sign_up_page);
    SDL_DestroyTexture(setting_page);SDL_DestroyTexture(mode_page);SDL_DestroyTexture(game_over_page);
    SDL_DestroyTexture(setting_page_change_music);SDL_DestroyTexture(setting_page_scoreboard);
    SDL_DestroyTexture(setting_page_sound_off);SDL_DestroyTexture(setting_page_sound_on);
    SDL_DestroyTexture(setting_page_volume);SDL_DestroyTexture(win_page);

    SDL_DestroyTexture(infinity_mode);SDL_DestroyTexture(timer_mode);SDL_DestroyTexture(normal_mode);

    Mix_FreeMusic(game_over_music);Mix_FreeMusic(soundnum0);Mix_FreeMusic(soundnum1);
    Mix_FreeMusic(soundnum2);Mix_FreeMusic(soundnum3);Mix_FreeMusic(win_music);
    Mix_CloseAudio();
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    IMG_Quit();
    SDL_Quit();
    return 0;
}

//############*************  MOEIN  *************##############
void print_asli(){
    int xx = 325,yy = 20;
    int d = 50,k = rand()%3,rang = rand()%5;
    ball jadid{};
    int radif = 0;
    while(radif < K*3) {
        jadid.x = xx;
        jadid.y = yy;
        if(k!=0) {
            k--;
        }
        else{
            k = rand()%3;
            rang = rand()%5;
        }
        jadid.rang = color[rang].code;
        color[rang].v = 1;
        if(xx+d > 1300 || xx+d < 300) {
            d = -d;
            yy += 50;
            radif++;
        }
        else{
            xx += d;
        }
        jadid.flagcheck = false;
        toop.push_back(jadid);
    }
    int golf = rand()%7 + 3;
    k = rand()%toop.size();
    while(golf--){
        if(!toop[k].gofl)
            toop[k].gofl = true;
        k = rand()%toop.size();
    }
    golf = rand()%4+2;
    k = rand()%toop.size();
    while(golf--){
        if(!toop[k].gofl && toop[k].rang != color[5].code && toop[k].y != 20)
            toop[k].rang = color[5].code;
        k = rand()%toop.size();
    }
}

void print_top(){
    SDL_RenderClear(m_renderer);
    game_render();
    //help();
    maxY = 25,Miny = 900;
    color[0].v=0;color[1].v=0;color[2].v=0;color[3].v=0;color[4].v=0;
    for (auto & i : toop) {
        filledCircleColor(m_renderer, i.x, i.y+.1, radious, i.rang);\
        if(i.gofl){
            hlineRGBA(m_renderer,i.x-25,i.x+25,i.y+.1,126,99,99,255);
            vlineRGBA(m_renderer,i.x,i.y-24.9,i.y+25.1,126,99,99,255);
        }
        i.y += 0.1;
        if(i.rang == color[0].code)
            color[0].v = true;
        else if(i.rang == color[1].code)
            color[1].v = true;
        else if(i.rang == color[2].code)
            color[2].v = true;
        else if(i.rang == color[3].code)
            color[3].v = true;
        else if(i.rang == color[4].code)
            color[4].v = true;
        if(Miny  > i.y)
            Miny = i.y;
        if(maxY < i.y)
            maxY = i.y;
    }
    int xx = 325;
    while(Miny==25 && xx<=1300 && bazi_infinity){
        Miny = -25;
        ball jadid;
        int k = rand()%2,rang = rand()%5;
        jadid.x = xx;
        xx+=50;
        jadid.y = -25;
        if(k!=0) {
            k--;
        }
        else{
            k = rand()%3;
            rang = rand()%5;
        }
        jadid.rang = color[rang].code;
        color[rang].v = 1;
        jadid.flagcheck = false;
        toop.push_back(jadid);
    }
    for (int i = 0; i < 5; ++i) {
        while(shoot.rang==color[i].code && !color[i].v){
            shoot.rang = color[b].code;
            a = b;
            b = rand()%5;
        }
    }
    hlineRGBA(m_renderer,300,1300,Miny-26,126,99,99,255);
    hlineRGBA(m_renderer,300,1300,800,126,99,99,255);
    vlineRGBA(m_renderer,300,Miny-26,800,126,99,99,255);
    vlineRGBA(m_renderer,1300,Miny-26,800,126,99,99,255);
    SDL_Delay(10);

    string ss = "Score : "+to_string(emtiaz);
    textRGBA(m_renderer,50,100,ss.c_str(),2,40,150,50,50,255);
    SDL_RenderPresent(m_renderer);
}

void search_vec(ball shoot2){
    for (auto & i : toop) {
        double fasele = sqrt((shoot2.x - i.x)*(shoot2.x - i.x) + (shoot2.y - i.y)*(shoot2.y - i.y));
        if(shoot2.rang==i.rang && !i.flagcheck && fasele<=2*radious+5){
            ball shoot1;
            i.flagcheck = true;
            tedadhazf++;
            shoot1 = i;
            search_vec(shoot1);
        }
    }
}

void search_vec_jodaha(ball shoot2){
    for (auto & i : toop) {
        double fasele = sqrt((shoot2.x - i.x)*(shoot2.x - i.x) + (shoot2.y - i.y)*(shoot2.y - i.y));
        if(!i.flagcheck && fasele<=2*radious+5){
            ball shoot1{};
            i.flagcheck = true;
            shoot1 = i;
            search_vec_jodaha(shoot1);
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
void pause(){
    int w,h;
    SDL_QueryTexture(pause_page,nullptr,nullptr,&w,&h);
    SDL_Rect pause_page_rect; pause_page_rect.x = 0; pause_page_rect.y = 0; pause_page_rect.w = 1600; pause_page_rect.h = 900;
    SDL_RenderCopy(m_renderer,pause_page,nullptr,&pause_page_rect);
    int w_pause_page_resume,h_pause_page_resume;
    SDL_QueryTexture(pause_page_resume,nullptr,nullptr,&w_pause_page_resume,&h_pause_page_resume);
    SDL_Rect pause_page_resume_rect; pause_page_resume_rect.x = 300; pause_page_resume_rect.y = 100; pause_page_resume_rect.w = w_pause_page_resume; pause_page_resume_rect.h = h_pause_page_resume;
    SDL_RenderCopy(m_renderer,pause_page_resume,nullptr,&pause_page_resume_rect);
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
        if(x>300 && x<300+w_pause_page_resume && y>100 && y<100+h_pause_page_resume){
            break;
        }
        else if (x > 600 && x < 600 + w_sound_on && y > 400 && y < 400 + h_sound_on) {
            Mix_ResumeMusic();
        } else if (x > 300 && x < 300 + w_sound_off && y > 400 && y < 400 + h_sound_off) {
            Mix_PauseMusic();

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
            bazi = false;
            break;
        }
    }
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
    SDL_RenderCopy(m_renderer,game_page,nullptr,&game_page_rect);
//    int w_exit,h_exit;
//    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
//    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
//    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    filledCircleColor(m_renderer,shoot.x,shoot.y,radious,shoot.rang);
    int w_pause_page_pause,h_pause_page_pause;
    SDL_QueryTexture(pause_page_pause, nullptr, nullptr, &w_pause_page_pause, &h_pause_page_pause);
    SDL_Rect pause_page_pause_rect; pause_page_pause_rect.x = 100; pause_page_pause_rect.y = 450; pause_page_pause_rect.w = w_pause_page_pause; pause_page_pause_rect.h = h_pause_page_pause;
    SDL_RenderCopy(m_renderer, pause_page_pause, nullptr, &pause_page_pause_rect);
    filledCircleColor(m_renderer,shoot.x,shoot.y,radious,shoot.rang);
    int w_cannon_img,h_cannon_img;
    SDL_QueryTexture(cannon_img, NULL, NULL, &w_cannon_img, &h_cannon_img);
    SDL_Rect img_rect;
    img_rect.x = 725;
    img_rect.y = 775;
    img_rect.w = w_cannon_img;
    img_rect.h = h_cannon_img;
    SDL_Point center = {img_rect.w / 2, img_rect.h};
    SDL_RenderCopyEx(m_renderer, cannon_img, NULL, &img_rect, cannon_angle(x_m, y_m), &center, SDL_FLIP_NONE);
    filledCircleColor(m_renderer,W/2-100,875,radious,color[b].code);
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
void chase_mouse_game(int x,int y){
    if(gameover){
        //SDL_Delay(6500);
        e->type = 0;
        while(e->type != SDL_MOUSEBUTTONDOWN) {
            SDL_PollEvent(e);
        }
        x = e->button.x,y = e->button.y;
        gameover = false;
    }
    if(x>300 && x<400 && y>300 && y<400){
        setting();
    }
    else if(x>300 && x<400 && y>680 && y<780){
        help_desk();
    }
    else if(x>1400 && x<1550 && y>700 && y <850){
        exit_page(true);
    }
    else {
        bazi = false;
    }
}
void login() {
    bool exiting_mode = false;
    int w, h;
    SDL_QueryTexture(login_page, nullptr, nullptr, &w, &h);
    SDL_Rect login_page_rect; login_page_rect.x = 0; login_page_rect.y = 0; login_page_rect.w = 1600; login_page_rect.h = 900;
    int w_exit, h_exit;
    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, login_page, nullptr, &login_page_rect);
    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    SDL_RenderPresent(m_renderer);
    while(true){
        e->type = 0;char c;bool existance = true;
        while (e->type != SDL_KEYDOWN) {
            SDL_PollEvent(e);
            x_m = e->button.x,y_m = e->button.y;
            if (x_m > 1400 && x_m < 1550 && y_m > 700 && y_m < 850 && e->type == SDL_MOUSEBUTTONDOWN) {
                exit_page(false);
                exiting_mode = true;
                break;
            }
        }
        if(exiting_mode)
            break;
        if(e->key.keysym.sym != SDLK_TAB) {
            c = check_char();

            if(c==';') {
                if (!username.empty())
                    username.pop_back();
            }
            else if(c!=':')
                username += c;
        }
        else{
            bool m = false;
            for (int i = 0;i < player_name.size(); ++i) {
                if(player_name[i]==username){
                    SDL_RenderClear(m_renderer);
                    SDL_RenderCopy(m_renderer, login_page, nullptr, &login_page_rect);
                    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
                    textRGBA(m_renderer,600,100,"Logged in successfully!",2,30,150,50,50,255);
                    emtiaz = player_data[0][i];
                    //username.clear();
                    SDL_RenderPresent(m_renderer);
                    m = true;
                    break;
                }
            }
            if(m)
                break;
            else{
                SDL_RenderClear(m_renderer);
                SDL_RenderCopy(m_renderer, login_page, nullptr, &login_page_rect);
                SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
                textRGBA(m_renderer,600,100,"Username does not existðŸ˜’!",2,30,150,50,50,255);
                SDL_RenderPresent(m_renderer);
                existance = false;
            }
        }
        if(existance) {
            SDL_RenderClear(m_renderer);
            SDL_RenderCopy(m_renderer, login_page, nullptr, &login_page_rect);
            SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
            if (!username.empty())
                textRGBA(m_renderer, 600, 100, username.c_str(), 2, 30, 150, 50, 50, 255);
            SDL_RenderPresent(m_renderer);
        }
    }
    while(!exiting_mode){
        e->type = 0;
        while (e->type != SDL_MOUSEBUTTONDOWN)
            SDL_PollEvent(e);
        int x = e->button.x, y = e->button.y;
        if (x > 1400 && x < 1550 && y > 700 && y < 850) {
            exit_page(false);
            exiting_mode = true;
        }
    }
//    do {
//        e->type = 0;
//        while (e->type != SDL_MOUSEBUTTONDOWN)
//        SDL_PollEvent(e);
//        int x = e->button.x, y = e->button.y;
//        if (x > 1400 && x < 1550 && y > 700 && y < 850) {
//            exit_page(false);
//            exiting_mode = true;
//        }
//    }
//    while(!exiting_mode);
}
void setting(){
    while(true) {
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
        e->type = 0;
        while (e->type != SDL_MOUSEBUTTONDOWN)SDL_PollEvent(e);
        int x = e->button.x, y = e->button.y;
        if (x > 300 && x < 300 + w_scoreboard && y > 100 && y < 100 + h_scoreboard) {
            scoreboard_p();
            exit_page(false);

        } else if (x > 600 && x < 600 + w_sound_on && y > 400 && y < 400 + h_sound_on) {
            Mix_ResumeMusic();

        } else if (x > 300 && x < 300 + w_sound_off && y > 400 && y < 400 + h_sound_off) {
            Mix_PauseMusic();

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
void scoreboard_p(){
    SDL_RenderClear(m_renderer);
    int w,h;
    SDL_QueryTexture(setting_page,nullptr,nullptr,&w,&h);
    SDL_Rect setting_page_rect; setting_page_rect.x = 0; setting_page_rect.y = 0; setting_page_rect.w = 1600; setting_page_rect.h = 900;
    SDL_RenderCopy(m_renderer,setting_page,nullptr,&setting_page_rect);
    for (int i = 0; i < player_name.size(); ++i) {
        if(player_name[i].empty())
            continue;
        string tt = player_name[i];
        textRGBA(m_renderer,200,i*50+50,tt.c_str(),2,40,126,99,99,255);
        tt = to_string(player_data[0][i]);
        textRGBA(m_renderer,700,i*50+50,tt.c_str(),2,40,126,99,99,255);
    }
    int w_exit,h_exit;
    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    SDL_RenderPresent(m_renderer);
    while(true) {
        e->type = 0;
        while (e->type != SDL_MOUSEBUTTONDOWN)SDL_PollEvent(e);
        int x = e->button.x, y = e->button.y;
        if (x > 1400 && x < 1550 && y > 700 && y < 850) {
            //exit_page(false);
            break;
        }
    }

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
            bazi = true;
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
    int w_exit,h_exit;
    SDL_QueryTexture(exit_img, nullptr, nullptr, &w_exit, &h_exit);
    SDL_Rect exit_rect; exit_rect.x = 1400; exit_rect.y = 700; exit_rect.w = w_exit; exit_rect.h = h_exit;
    SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
    SDL_RenderPresent(m_renderer);
    bool exiting_mode = false;
    while(true){
        e->type = 0;char c;bool existance = true;
        while (e->type != SDL_KEYDOWN) {
            SDL_PollEvent(e);
            x_m = e->button.x,y_m = e->button.y;
            if (x_m > 1400 && x_m < 1550 && y_m > 700 && y_m < 850 && e->type == SDL_MOUSEBUTTONDOWN) {
                exit_page(false);
                exiting_mode = true;
                break;
            }
        }
        if(exiting_mode)
            break;
        if(e->key.keysym.sym != SDLK_TAB) {
            c = check_char();
            if(c==';') {
                if (!username.empty())
                    username.pop_back();
            }
            else if(c!=':')
                username += c;
        }
        else{
            bool m = false;
            for (const auto & i : player_name) {
                if(i==username && !username.empty()){
                    m = true;
                    break;
                }
            }
            if(m) {
                SDL_RenderClear(m_renderer);
                SDL_RenderCopy(m_renderer, sign_up_page, nullptr, &sign_up_page_rect);
                SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
                textRGBA(m_renderer,600,100,"This username exists, use another one!",2,30,150,50,50,255);
                SDL_RenderPresent(m_renderer);
                break;
            }
            else{
                SDL_RenderClear(m_renderer);
                SDL_RenderCopy(m_renderer, sign_up_page, nullptr, &sign_up_page_rect);
                SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
                textRGBA(m_renderer,600,100,"Username created!",2,30,150,50,50,255);
                if(!username.empty()) {
                    player_name.push_back(username);
                //    username.clear();
                    player_data[0].push_back(0);
                    player_data[1].push_back(0);
                }
                SDL_RenderPresent(m_renderer);
                existance = false;
            }
        }
        if(existance) {
            SDL_RenderClear(m_renderer);
            SDL_RenderCopy(m_renderer, sign_up_page, nullptr, &sign_up_page_rect);
            SDL_RenderCopy(m_renderer, exit_img, nullptr, &exit_rect);
            if (!username.empty())
                textRGBA(m_renderer, 600, 100, username.c_str(), 2, 30, 150, 50, 50, 255);
            SDL_RenderPresent(m_renderer);
        }
    }
    while(!exiting_mode){
        e->type = 0;
        while (e->type != SDL_MOUSEBUTTONDOWN)
            SDL_PollEvent(e);
        int x = e->button.x, y = e->button.y;
        if (x > 1400 && x < 1550 && y > 700 && y < 850) {
            exit_page(false);
            exiting_mode = true;
        }
    }
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
    for (int i = 0; i < player_name.size(); ++i) {
        if(username == player_name[i])
            emtiaz = player_data[0][i];
    };
//    string ss = "Your score is "+to_string(emtiaz);
//    textRGBA(m_renderer,600,100,ss.c_str(),2,40,150,50,50,255);
    SDL_RenderPresent(m_renderer);
    while(Mix_PlayingMusic());
    gameover = true;
}
void win(){
    SDL_RenderClear(m_renderer);
    int w, h;
    SDL_QueryTexture(win_page, nullptr, nullptr, &w, &h);
    SDL_Rect win_page_rect; win_page_rect.x = 0; win_page_rect.y = 0; win_page_rect.w = 1600; win_page_rect.h = 900;
    SDL_RenderCopy(m_renderer, win_page, nullptr, &win_page_rect);
    Mix_PlayMusic(win_music, 0);
    string ss = "Your score is "+to_string(emtiaz);
    textRGBA(m_renderer,600,100,ss.c_str(),2,40,150,50,50,255);

    SDL_RenderPresent(m_renderer);
    while(Mix_PlayingMusic());
    gameover = true;
}
void sound_play(){
    switch (soundnum) {
        case 0:
            Mix_PlayMusic(soundnum0,-1);
            break;
        case 1:
            Mix_PlayMusic(soundnum1,-1);
            break;
        case 2:
            Mix_PlayMusic(soundnum2,-1);
            break;
        case 3:
            Mix_PlayMusic(soundnum3,-1);
            break;
    }
}
char check_char(){
    switch (e->key.keysym.sym) {
        case SDLK_0:
            return '0';
            break;
        case SDLK_1:
            return '1';
            break;
        case SDLK_2:
            return '2';
            break;
        case SDLK_3:
            return '3';
            break;
        case SDLK_4:
            return '4';
            break;
        case SDLK_5:
            return '5';
            break;
        case SDLK_6:
            return '6';
            break;
        case SDLK_7:
            return '7';
            break;
        case SDLK_8:
            return '8';
            break;
        case SDLK_9:
            return '9';
            break;
        case SDLK_BACKSPACE:
            return ';';
            break;
        case SDLK_SPACE:
            return ' ';
            break;
        case SDLK_a:
            return 'a';
            break;
        case SDLK_b:
            return 'b';
            break;
        case SDLK_c:
            return 'c';
            break;
        case SDLK_d:
            return 'd';
            break;
        case SDLK_e:
            return 'e';
            break;
        case SDLK_f:
            return 'f';
            break;
        case SDLK_g:
            return 'g';
            break;
        case SDLK_h:
            return 'h';
            break;
        case SDLK_i:
            return 'i';
            break;
        case SDLK_j:
            return 'j';
            break;
        case SDLK_k:
            return 'k';
            break;
        case SDLK_l:
            return 'l';
            break;
        case SDLK_m:
            return 'm';
            break;
        case SDLK_n:
            return 'n';
            break;
        case SDLK_o:
            return 'o';
            break;
        case SDLK_p:
            return 'p';
            break;
        case SDLK_q:
            return 'q';
            break;
        case SDLK_r:
            return 'r';
            break;
        case SDLK_s:
            return 's';
            break;
        case SDLK_t:
            return 't';
            break;
        case SDLK_u:
            return 'u';
            break;
        case SDLK_v:
            return 'v';
            break;
        case SDLK_w:
            return 'w';
            break;
        case SDLK_x:
            return 'x';
            break;
        case SDLK_y:
            return 'y';
            break;
        case SDLK_z:
            return 'z';
            break;
        case SDLK_COMMA:
            return ',';
            break;
        case SDLK_EQUALS:
            return '=';
            break;
        case SDLK_LSHIFT:
            e->type = 0;
            while(e->type != SDL_KEYDOWN)SDL_PollEvent(e);
            switch (e->key.keysym.sym) {
                case SDLK_MINUS:
                    return '_';
                    break;
                case SDLK_1:
                    return '!';
                    break;
                case SDLK_2:
                    return '@';
                    break;
                case SDLK_3:
                    return '#';
                    break;
                case SDLK_4:
                    return '$';
                    break;
                case SDLK_5:
                    return '%';
                    break;
                case SDLK_6:
                    return '^';
                    break;
                case SDLK_7:
                    return '&';
                    break;
                case SDLK_8:
                    return '*';
                    break;
                case SDLK_9:
                    return '(';
                    break;
                case SDLK_0:
                    return ')';
                    break;
                case SDLK_EQUALS:
                    return '+';
                    break;
            }
            break;
        case SDLK_RSHIFT:
            e->type = 0;
            while(e->type != SDL_KEYDOWN)SDL_PollEvent(e);
            switch (e->key.keysym.sym) {
                case SDLK_MINUS:
                    return '_';
                    break;
                case SDLK_1:
                    return '!';
                    break;
                case SDLK_2:
                    return '@';
                    break;
                case SDLK_3:
                    return '#';
                    break;
                case SDLK_4:
                    return '$';
                    break;
                case SDLK_5:
                    return '%';
                    break;
                case SDLK_6:
                    return '^';
                    break;
                case SDLK_7:
                    return '&';
                    break;
                case SDLK_8:
                    return '*';
                    break;
                case SDLK_9:
                    return '(';
                    break;
                case SDLK_0:
                    return ')';
                    break;
                case SDLK_EQUALS:
                    return '+';
                    break;
            }
            break;
        default:
            return ':';
            break;
    }
}
//############*************  MOEIN  *************##############


//############*************  EMAD  *************##############

double cannon_angle(double x, double y) {
    double angle = atan((H-y)/ (x - W/2));
    if (angle<0) angle+=M_PI;
    angle*=180;
    angle/=M_PI;
    angle=-angle;
    angle+=90;
    return angle;
}

void hit() {
    bool clicked = true;
    while (clicked) {
        for (auto & i : toop) {
            if (pow((shoot.x - i.x), 2) + pow((shoot.y - i.y), 2) <= pow(2 * radious, 2)) {
                clicked=false;
                break;
            }
        }
        if(shoot.y<=Miny) {
            clicked = false;
            shoot.y = Miny;
            shoot.flagcheck = false;
            toop.push_back(shoot);
        }
        if (clicked) {
            if(shoot.x>1300 || shoot.x<300)
                dx *= -1;
            shoot.x += dx;
            shoot.y += dy;
            print_top();
        }
    }
}
void create_shoot(){
    do{
        c=rand()%5;
    }
    while(!color[c].v);
    a=b;
    b=c;
    shoot.x=W/2;
    shoot.y=875;
    shoot.rang=color[a].code;
    shoot.flagcheck=true;
}

void help(){
    for (int i = 1; 1 ; ++i) {
        filledCircleColor(m_renderer, shoot.x+i*dx, shoot.y-i*dy, 0.5, 0xff000000);
        i++;
        filledCircleColor(m_renderer, shoot.x+i*dx, shoot.y-i*dy, 0.2, 0xff000000);
        if(shoot.x+i*dx >= x_m && shoot.y-i*dy<=y_m)
            break;
    }
}
