/*******************************************************************************************

* Programmer: Guangbei Yi                                                                        *

* Class: CptS 121, Spring 2021; Programming Assignment 4                                            *

* Programming Assignment: A Game of Chance "Craps"               *

* Date: March 10, 2021                                                                           *

* Description: This program Write a program that play the game dice using sdl
*
* File Description: This profile give the function prototype.

* https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA4.htm

*******************************************************************************************/


#ifndef PAIVFUNCTIONS_H
#define PAIVFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define CRAPS_STATE_MAIN_MENU 1
#define CRAPS_STATE_IN_GAME 2
#define CRAPS_STATE_IN_GAME_BALANCE 11
#define CRAPS_STATE_IN_GAME_WAGER 12
#define CRAPS_STATE_IN_GAME_CHECK_AMOUNT 13
#define CRAPS_STATE_IN_GAME_ROLL_DICE 14
#define CRAPS_STATE_IN_GAME_CHECK_RESULT 15
	
#define SCROLL_SPEED 300     // speed in pixels/second influenced by fps

#include <stdio.h>
#include <math.h>
#include <stdlib.h> // rand (), srand ()
#include <time.h> // time ()
#include <windows.h>
#include <stdbool.h>
#include <string.h>

#include "include/SDL.h"
#include "include/SDL_timer.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"

#pragma comment(lib ,"lib/x64/SDL2.lib")
#pragma comment(lib ,"lib/x64/SDL2main.lib")
#pragma comment(lib ,"lib/x64/SDL2_image.lib")
	
/*Prints out the rules of the game of "craps".*/
void print_game_rules(void);

/*Prompts the player for an initial bank balance from which wagering will be added or subtracted. The player entered bank balance (in dollars, i.e. $100.00) is returned.*/
double get_bank_balance(void);

/*Prompts the player for a wager on a particular roll. The wager is returned.*/
double get_wager_amount(void);

/*Checks to see if the wager is within the limits of the player's available balance. If the wager exceeds the player's allowable balance, then 0 is returned; otherwise 1 is returned.*/
int check_wager_amount(double wager, double balance);

/*Rolls one die. This function should randomly generate a value between 1 and 6, inclusively. Returns the value of the die.*/
int roll_die(void);

/*Sums together the values of the two dice and returns the result. Note: this result may become the player's point in future rolls.*/
int calculate_sum_dice(int die1_value, int die2_value);

/*Determines the result of the first dice roll. If the sum is 7 or 11 on the roll, the player wins and 1 is returned. If the sum is 2, 3, or 12 on the first throw (called "craps"), the player loses (i.e. the "house" wins) and 0 is returned. If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's "point" and -1 is returned.*/
int is_win_loss_or_point(int sum_dice);

/*Determines the result of any successive roll after the first roll. If the sum of the roll is the point_value, then 1 is returned. If the sum of the roll is a 7, then 0 is returned. Otherwise, -1 is returned.*/
int is_point_loss_or_neither(int sum_dice, int point_value);

/*If add_or_subtract is 1, then the wager amount is added to the bank_balance. If add_or_subtract is 0, then the wager amount is subtracted from the bank_balance. Otherwise, the bank_balance remains the same. The bank_balance result is returned.*/
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);

/*Prints an appropriate message dependent on the number of rolls taken so far by the player, the current balance, and whether or not the player just won his roll. The parameter win_loss_neither indicates the result of the previous roll.*/
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);

/*custon functions*/
//read files
FILE* open_file(char* filename, char* file_access);

//SDL functions	
//init sdl
int sdl_init();

//init sdl ttf
int sdl_ttf_init();

//create window
SDL_Window* sdl_create_window();
	
//create render
SDL_Renderer* sdl_create_render(SDL_Window* win, Uint32 sdl_current_render_flags);

//init game main window
void vCrapsInitGameMainWindow(SDL_Window* win, SDL_Renderer* rend);

//display background picture
void vCrapsDisplayBackgroundPicture(SDL_Renderer* craps_main_window_renderer, SDL_Texture* tex_background);

//load init resource
void vCrapsLoadInitResource(SDL_Texture* tex_background, SDL_Renderer* craps_main_window_renderer);
	
//create surface load image into memory
SDL_Surface* sdl_create_surface(char *location_pic);

//load image data into VRAM
SDL_Texture* sdl_create_texture_from_surface(SDL_Renderer* render, SDL_Surface* surface);
	
//load the dice
SDL_Texture* sdl_load_picture_into_texture(const char* name_dice, SDL_Renderer* render, SDL_Rect* rect_dice);
	
const char* sdl_pick_up_dice(int numbers);
	
#ifdef __cplusplus
}
#endif
#endif
