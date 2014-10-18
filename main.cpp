#include <allegro.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

void init();
void deinit();
void fullscreen(bool b);
void game();
void update();
int random(int min, int max, int seed);
void move();
bool hittest(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h );
void moretime();
void sgame();
void egame();
void pgame();
void resume_game();
void to_main_menu();
void game_over();
void credits();

int screenwidth;
int screenheight;
bool end;
float charx;
float chary;
float movementspeed;
int sampvol;
int midivol;
int score;
bool newpos = true;
int golex;
int goley;
int minalive;
int red;
int blue;
bool gameon;
bool menu;
int arrowpos;
int menupos;
int arrowy;
bool arowm;
bool fs;
bool gin;
bool pausemenu;
bool _pause;
int snake_bitmap_frame;
int snake_bitmap_x;
bool enter_key_in;
int randx;
int randy;
bool tree_touch;
bool trees_on;
bool soundfx;
bool bgmusic;
bool game_over_screen;
int arrowx;
bool con;
float creditscroll;

volatile long arrowcounter;
volatile long secalive;
volatile long timeremaining;
volatile long counter = 0;
volatile long dubl;


void ticker(){counter++;}
void rticker(){
    if(_pause == false){
        timeremaining--;
    }
}
void aliveticker(){
    if(pause == false){
        secalive++;
    }
}
void dubler(){dubl++;}
void arrowticker(){arrowcounter++;}
void tree_ticker(){tree_touch = false;}

using namespace std;

int main(){
    init();
    game();

}
END_OF_MAIN();

void init(){
    //sets variables
    end = false;
    screenwidth = 640;
    screenheight = 480;
    sampvol = 150;
    midivol = 150;
    bgmusic = true;
    soundfx = true;

    gameon = false;
    menu = true;
    menupos = 1;
    arowm = true;
    fs = false;
    game_over_screen = false;

    //initalize color depth and full screen
    allegro_init();
    set_color_depth(32);
    fullscreen(false);

    install_timer();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);

    LOCK_VARIABLE(counter);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(90));
	install_int_ex(arrowticker, BPS_TO_TIMER(10));

}

void deinit(){
    clear_keybuf();
}

void fullscreen(bool b){
    if(b == true){
        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screenwidth, screenheight, 0, 0);
    }
    if(b == false){
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenwidth, screenheight, 0, 0);
    }
}


void game(){
    //variables
    string music;
    string sound;

    //bitmaps
    BITMAP *buffer = create_bitmap(screenwidth, screenheight);
    BITMAP *snake = load_bitmap("images/cati.bmp", NULL);
    BITMAP *gole = load_bitmap("images/plnt.bmp", NULL);
    BITMAP *arrow = load_bitmap("images/arrow.bmp", NULL);
    BITMAP *splashscreen = load_bitmap("images/snake_bite.bmp", NULL);
    BITMAP *tree = load_bitmap("images/tree.bmp", NULL);

    //fonts
    //FONT* comic = load_font("bc.otf", NULL, NULL);

    //samples
    SAMPLE *pswd = load_sample("audio/password.wav");
    SAMPLE *menumove = load_sample("audio/mouseClick.wav");
    SAMPLE *gole_sound_fx = load_sample("audio/dinga.wav");

    //midis
	MIDI *menu_bg_midi = load_midi("audio/menu.mid");

	play_midi(menu_bg_midi, true);

    while(end == false){
        while(counter > 0){
            if(timeremaining < 0 && gameon == true){
                game_over();
            }
            set_volume((soundfx)?150:0, (bgmusic)?150:0);

            if(gameon == true && gin == true){

                if(snake_bitmap_frame == 1){
                    snake_bitmap_x = 0;
                }
                if(snake_bitmap_frame == 8){
                    snake_bitmap_x = 62;
                }
                if(snake_bitmap_frame == 16){
                    snake_bitmap_x = 124;
                }
                 if(snake_bitmap_frame == 24){
                    snake_bitmap_x = 186;
                }
                if(snake_bitmap_frame > 24){
                    snake_bitmap_frame = 1;
                }

                if(key[KEY_ESC]){
                pgame();
                }
                if(tree_touch == false){

            if(key[KEY_UP] && key[KEY_RIGHT] && charx < screenwidth - 60 && chary > 20){
                charx += movementspeed / 2;
                chary -= movementspeed / 2;
                snake_bitmap_frame++;
            }
            else if(key[KEY_UP] && key[KEY_LEFT] && charx > 0 && chary > 20){
                charx -= movementspeed / 2;
                chary -= movementspeed / 2;
                snake_bitmap_frame++;
            }
            else if(key[KEY_DOWN] && key[KEY_RIGHT] && charx < screenwidth - 64 && chary < screenheight - 64){
                charx += movementspeed / 2;
                chary += movementspeed / 2;
                snake_bitmap_frame++;
            }
            else if(key[KEY_DOWN] && key[KEY_LEFT] && charx > 0 && chary < screenheight - 64){
                charx -= movementspeed / 2;
                chary += movementspeed / 2;
                snake_bitmap_frame++;
            }
            //movement input
            else if(key[KEY_UP] && chary > 20 && !key[KEY_DOWN]){
                chary -= movementspeed;
                snake_bitmap_frame++;
            }
            else if(key[KEY_DOWN] && chary < screenheight - 65  && !key[KEY_UP]){
                chary += movementspeed;
                snake_bitmap_frame++;
            }
            else if(key[KEY_RIGHT] && charx < screenwidth - 64 && !key[KEY_LEFT]){
                charx += movementspeed;
                snake_bitmap_frame++;
            }
            else if(key[KEY_LEFT] && charx > 0 && !key[KEY_RIGHT]){
                charx -= movementspeed;
                snake_bitmap_frame++;
            }

            if(hittest(charx, chary, 64, 32, golex, goley, 18, 11) == true && dubl > 1){
                move();
                score++;
                moretime();
                dubl = 0;
                play_sample(gole_sound_fx, 150, 128, 1000, false);
            }

            if(timeremaining > 630){
                timeremaining = 630;
            }
            if(secalive >= 60){
                secalive = 0;
                minalive++;
            }

            if(timeremaining < 150 &&  red < 255){
                red++;
                blue--;

            }
            }
            }


            if(arrowcounter > 4){
                arrowcounter = 1;
            }

            if(arrowcounter == 1){
                arrowpos = 0;
            }
            if(arrowcounter == 2){
                arrowpos = 20;
            }
            if(arrowcounter == 3){
                arrowpos = 40;
            }
            if(arrowcounter == 4){
                arrowpos = 60;
            }

            if(menu == true){
                if(!key[KEY_ENTER]){
                    enter_key_in = true;
                }
                if(!key[KEY_UP] && !key[KEY_DOWN]){
                    arowm = true;
                }
                if(key[KEY_ENTER]){
                    if(menupos == 1 && enter_key_in == true){
                        sgame();
                    }
                    if(menupos == 2){
                        if(fs == false){
                            fullscreen(true);
                            fs = true;
                        }
                        else{
                            fullscreen(false);
                            fs = false;
                        }
                    }
                    if(menupos == 3 && enter_key_in == true){
                        enter_key_in = false;
                        if(trees_on == false){
                            trees_on = true;
                        }
                        else{
                            trees_on = false;
                        }

                    }
                    if(menupos == 4){
                        credits();
                    }
                    if(menupos == 5){
                        end = true;
                    }
                }


                if(menupos > 5){
                    menupos = 1;
                }
                if(menupos < 1){
                    menupos = 4;
                }

                if(menupos == 1){
                    arrowy = 103;
                }
                if(menupos == 2){
                    arrowy = 143;
                }
                if(menupos == 3){
                    arrowy = 183;
                }
                if(menupos == 4){
                    arrowy = 223;
                }
                if(menupos == 5){
                    arrowy = 263;
                }
                if(key[KEY_UP] && arowm == true){
                    menupos--;
                    play_sample(menumove, 150, 128, 1000, false);
                    arowm = false;
                }
                if(key[KEY_DOWN] && arowm == true){
                    menupos++;
                    play_sample(menumove, 150, 128, 1000, false);
                    arowm = false;
                }
            }

            if(pausemenu == true){
                if(!key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_ENTER]){
                    enter_key_in = true;
                    arowm = true;
                }

                if(menupos == 1){
                    arrowy = 120;
                }
                if(menupos == 2){
                    arrowy = 160;
                }
                if(menupos == 3){
                    arrowy = 200;
                }
                if(menupos == 4){
                    arrowy = 240;
                }

                if(key[KEY_UP] && arowm == true){
                    menupos--;
                    play_sample(menumove, 150, 128, 1000, false);
                    arowm = false;
                }
                if(key[KEY_DOWN] && arowm == true){
                    menupos += 1;
                    play_sample(menumove, 150, 128, 1000, false);
                    arowm = false;
                }

                if(menupos > 4){
                    menupos = 1;
                }
                if(menupos < 1){
                    menupos = 4;
                }

                if(key[KEY_ENTER] && arowm == true && enter_key_in == true){
                    if(menupos == 1){
                        resume_game();
                    }
                    if(menupos == 2){
                        to_main_menu();
                        enter_key_in = false;
                    }
                    if(menupos == 3){
                        enter_key_in = false;
                        if(soundfx == true){
                            soundfx = false;
                        }

                        else{
                            soundfx = true;
                        }
                    }
                    if(menupos == 4){
                        enter_key_in = false;
                        if(bgmusic == true){
                            bgmusic = false;
                        }

                        else{
                            bgmusic = true;
                        }
                    }
                }
            }

             if(game_over_screen == true){
                 if(!key[KEY_RIGHT] && !key[KEY_LEFT] && !key[KEY_ENTER]){
                     enter_key_in = true;
                 }
                 if(key[KEY_RIGHT] && enter_key_in == true){
                     enter_key_in = false;
                     menupos++;
                 }
                 if(key[KEY_LEFT] && enter_key_in == true){
                     enter_key_in = false;
                     menupos--;
                 }
                 if(menupos > 2){
                     menupos = 1;
                 }
                 if(menupos < 1){
                     menupos = 2;
                 }

                 if(key[KEY_ENTER] && enter_key_in == true){
                     if(menupos == 1){
                         sgame();
                     }
                     if(menupos == 2){
                         to_main_menu();

                     }
                 }
                 if(menupos == 1){
                     arrowx = 230;
                 }
                 if(menupos == 2){
                     arrowx = 330;
                 }

             }
          counter--;
        }

        rectfill(buffer, 0, 0, screenwidth, screenheight, makecol(0, 219, 0));

        if(gameon == true){

            masked_blit(snake, buffer, snake_bitmap_x, 0, charx, chary, 64, 32);

            masked_blit(gole, buffer, 102, 21, golex, goley, 18, 11);

            if(trees_on == true){
            for(int i = 0; i < 10; i++){
                masked_blit(tree, buffer, 0, 0, (randx * i + 74904)&  450, (randy * i + 734)& 320, 65, 82);
                if(hittest(((randx * i + 74904)&  450) + 11, ((randy * i + 734)& 320) + 68, 40, 15, charx, chary, 64, 32)){
                    cout << "tree touch - ";
                }
            }
            }
            rectfill(buffer, 0, screenheight - 30, screenwidth, screenheight, makecol(0, 200, 0));

            if(timeremaining > 10){
                rectfill(buffer, 10, screenheight - 20, timeremaining, screenheight - 10, makecol(red, 0, blue));
            }
            if(timeremaining > 100){
                textprintf_centre_ex(buffer, font, timeremaining / 2, screenheight - 19, makecol(255, 255, 255), -1, "time: %i", timeremaining / 30);
            }

            rectfill(buffer, 0, 0, screenwidth, 30, makecol(0, 200, 0));
            textprintf_ex(buffer, font, screenwidth - 600, 10, makecol(255, 255, 255), -1, "time: %i:%i", minalive, secalive);
            textprintf_ex(buffer, font, screenwidth - 215, 10, makecol(255, 255, 255), -1, "score: %i", score);

        }

        if(menu == true){
            blit(splashscreen, buffer, 0, 0, 0, 0, 640, 480);

            (buffer, 0, 0, 100, 100, makecol(200, 0, 0));
            textprintf_ex(buffer, font, 70, 110, makecol(255, 255, 255), -1, "Play!!!");
            textprintf_ex(buffer, font, 70, 150, makecol(255, 255, 255), -1, "Togle fullscreen");
            textprintf_ex(buffer, font, 70, 190, makecol(255, 255, 255), -1, "trees are %s - not done yet",(trees_on)?"on":"off");
            textprintf_ex(buffer, font, 70, 230, makecol(255, 255, 255), -1, "Credits");
            textprintf_ex(buffer, font, 70, 270, makecol(255, 255, 255), -1, "Quit");
            masked_blit(arrow, buffer, arrowpos, 0, 45, arrowy, 19, 20);
        }

        if(game_over_screen == true){

            rectfill(buffer, (screenwidth / 2) - 150, 60, (screenwidth / 2) + 150, 200, makecol(0, 180, 0));
            textprintf_ex(buffer, font, (screenwidth / 2) - 50, 70, makecol(255, 255, 255), -1, "GAME OVER :<");

            textprintf_ex(buffer, font, 250, 125, makecol(255, 255, 255), -1, "total score: %i", (score * (minalive + 1) + (secalive / 10) - 1 ));
            textprintf_ex(buffer, font, 250, 165, makecol(255, 255, 255), -1, "retry");
            textprintf_ex(buffer, font, 350, 165, makecol(255, 255, 255), -1, "main menu");

            masked_blit(arrow, buffer, arrowpos, 0, arrowx, 160, 19, 20);
        }

        if(pausemenu == true){
            rectfill(buffer, (screenwidth / 2) - 150, 60, (screenwidth / 2) + 150, 430, makecol(0, 180, 0));

            textprintf_ex(buffer, font, (screenwidth / 2) - 50, 70, makecol(255, 255, 255), -1, "GAME PAUSED");

            textprintf_ex(buffer, font, 250, 125, makecol(255, 255, 255), -1, "resume");
            textprintf_ex(buffer, font, 250, 165, makecol(255, 255, 255), -1, "main menu");
            textprintf_ex(buffer, font, 250, 205, makecol(255, 255, 255), -1, "sound fx: %s", (soundfx)?"on":"off");
            textprintf_ex(buffer, font, 250, 245, makecol(255, 255, 255), -1, "background music: %s", (bgmusic)?"on":"off");


            masked_blit(arrow, buffer, arrowpos, 0, 225, arrowy, 19, 20);
        }

        if(con == true){
            rectfill(buffer, 0, 0, screenwidth, screenheight, makecol(0, 0, 0));
            creditscroll -= .01;
            textprintf_centre_ex(buffer, font, screenwidth / 2, creditscroll + 150, makecol(255, 255, 255), -1, "CREDITS - sorry they aren't here yet");
            textprintf_centre_ex(buffer, font, screenwidth / 2, creditscroll + 170, makecol(255, 255, 255), -1, "this is soooooo long and i don't want to type it");
            textprintf_centre_ex(buffer, font, screenwidth / 2, creditscroll + 190, makecol(255, 255, 255), -1, "too bad there is no way to get back to the game");
            textprintf_centre_ex(buffer, font, screenwidth / 2, creditscroll + 210, makecol(255, 255, 255), -1, "so you better restart the game and NEVER select credist again");
            textprintf_centre_ex(buffer, font, screenwidth / 2, creditscroll + 230, makecol(255, 255, 255), -1, "alco check you all sorts of stuff at www.adaywithian.com - there are two things");




        }

        blit(buffer, screen, 0, 0, 0, 0, screenwidth, screenheight);
        clear_bitmap(buffer);
    }
}


void update(){

}

int random(int min, int max, int seed){
    srand(seed * 500);
    return((rand()%max) + min);
}

void move(){
    golex = random(0, screenwidth - 18, time(0));
    goley = random(30, screenheight - 100, time(0));
}

bool hittest( int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h ){
    if ( ( b1_x > b2_x + b2_w - 1 )  ||
                ( b1_y > b2_y + b2_h - 1 )       ||
                ( b2_x > b1_x + b1_w - 1 )       ||
                ( b2_y > b1_y + b1_h - 1 ) )
    {
        // no collision
        return (0);
    }

    // collision
    return (1);
}

void moretime(){
    timeremaining += 50;
}

void sgame(){

    MIDI *bg = load_midi("audio/huh.mid");
    gameon = true;
    menu = false;

    install_int_ex(rticker, BPS_TO_TIMER(40));
	install_int_ex(aliveticker, BPS_TO_TIMER(1));
	install_int_ex(dubler, BPS_TO_TIMER(10));

	 chary = screenheight / 2;
    charx = screenwidth / 2;
    movementspeed = 7;
    timeremaining = 640 - 10;
    move();
    secalive = 0;
    minalive = 0;
    red = 0;
    blue = 255;
    dubl = 0;
    gin = true;
    _pause = false;
    snake_bitmap_frame = 1;
    snake_bitmap_x = 0;
    game_over_screen = false;

    randy = random(40, 500, time(NULL));
    randx = random(40, 500, time(NULL));

    play_midi(bg, true);
}

void egame(){
    gameon = false;
    menu = true;
}

void pgame(){
    gin = false;
    _pause = true;
    arrowy = 120;
    menupos = 1;
    pausemenu = true;
}

void resume_game(){
    gin = true;
    _pause = false;
    pausemenu = false;
}

void to_main_menu(){
    MIDI *menu_bg_midi = load_midi("menu.mid");
    gameon = false;
    menupos = 1;
    _pause = false;
    pausemenu = false;
    menu = true;
    enter_key_in = false;
    game_over_screen = false;
    play_midi(menu_bg_midi, true);
}

void game_over(){
    game_over_screen = true;
    gin = false;
    arrowy = 163;
    arrowx = 230;
    menupos = 1;
    _pause = true;
    timeremaining = 1;
}

void credits(){
    con = true;
}
