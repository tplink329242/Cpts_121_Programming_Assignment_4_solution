/*******************************************************************************************

* Programmer: Guangbei Yi                                                                        *

* Class: CptS 121, Spring 2021; Programming Assignment 4                                            *

* Programming Assignment: A Game of Chance "Craps"               *

* Date: March 10, 2021                                                                           *

* Description: This program Write a program that play the game dice using sdl
*
*
* File Description: This profile include the function defination.

* https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA4.htm

*******************************************************************************************/

#include "PAIV_Funcions.h"

/*Prints out the rules of the game of "craps".*/
void print_game_rules(void)
{
	//printf("Game is balabalabala");
}

/*Prompts the player for an initial bank balance from which wagering will be added or subtracted. The player entered bank balance (in dollars, i.e. $100.00) is returned.*/
double get_bank_balance(void)
{
	/*double res, scanf("%f", &res);*/
	return 0.0;
}

/*Prompts the player for a wager on a particular roll. The wager is returned.*/
double get_wager_amount(void)
{
	/*double res, scanf("%f", &res);*/
	return 0.0;
}

/*Checks to see if the wager is within the limits of the player's available balance. If the wager exceeds the player's allowable balance, then 0 is returned; otherwise 1 is returned.*/
int check_wager_amount(double wager, double balance)
{
	if (wager > balance)
	{
		return 0;
	}
	return 1;
}

/*Rolls one die. This function should randomly generate a value between 1 and 6, inclusively. Returns the value of the die.*/
int roll_die(void)
{
	srand((unsigned)time(NULL));
	return rand() % 6 + 1;
}

/*Sums together the values of the two dice and returns the result. Note: this result may become the player's point in future rolls.*/
int calculate_sum_dice(int die1_value, int die2_value)
{
	return die1_value + die2_value;
}

/*Determines the result of the first dice roll. If the sum is 7 or 11 on the roll, the player wins and 1 is returned. If the sum is 2, 3, or 12 on the first throw (called "craps"), the player loses (i.e. the "house" wins) and 0 is returned. If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's "point" and -1 is returned.*/
int is_win_loss_or_point(int sum_dice)
{
	if (sum_dice==7 || sum_dice == 11)
	{
		return 1;
	}
	if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
	{
		return 0;
	}
	return -1;
}

/*Determines the result of any successive roll after the first roll. If the sum of the roll is the point_value, then 1 is returned. If the sum of the roll is a 7, then 0 is returned. Otherwise, -1 is returned.*/
int is_point_loss_or_neither(int sum_dice, int point_value)
{
	if (sum_dice == point_value)
	{
		return 1;
	}
	if (sum_dice == 7)
	{
		return 0;
	}
	return -1;	
}

/*If add_or_subtract is 1, then the wager amount is added to the bank_balance. If add_or_subtract is 0, then the wager amount is subtracted from the bank_balance. Otherwise, the bank_balance remains the same. The bank_balance result is returned.*/
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	if (add_or_subtract == 1)
	{
		return bank_balance + wager_amount;
	}
	if (add_or_subtract == 0)
	{
		return bank_balance - wager_amount;
	}
	return bank_balance;
}

/*Prints an appropriate message dependent on the number of rolls taken so far by the player, the current balance, and whether or not the player just won his roll. The parameter win_loss_neither indicates the result of the previous roll.*/
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{
}

FILE* open_file(char* filename, char* file_access)
{
	FILE* infile = NULL;
	infile = fopen(filename, file_access);
	if (infile == NULL)
	{
		perror("Error: ");
		return NULL;
	}

	printf("\nOpening success");
	return infile;
}

int sdl_init()
{
	int res = 0;
	res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
	if (res != 0)
	{
		printf_s("Error for init SDL: %s ", SDL_GetError());
		return 1;
	}
	printf_s("init success!\n");
	return 0;
}

int sdl_ttf_init()
{
	if (TTF_Init() == -1)
	{
		return 1;
	}
	return 0;
}

SDL_Window* sdl_create_window()
{
	SDL_Window* win = SDL_CreateWindow("Cpts 121 PAIV 'Craps'",
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WINDOW_WIDTH,
										WINDOW_HEIGHT, 0);
	if (!win)
	{
		printf_s("Error creating SDL window: %s ", SDL_GetError());
		return NULL;
	}
	return win;
}

SDL_Renderer* sdl_create_render(SDL_Window *win, Uint32 sdl_current_render_flags)
{
	SDL_Renderer* render = SDL_CreateRenderer(win, -1, sdl_current_render_flags);
	if (!render)
	{
		printf_s("Error creating SDL render: %s ", SDL_GetError());
		return NULL;
	}
	return render;
}

void vCrapsInitGameMainWindow(SDL_Window* win, SDL_Renderer* rend)
{
	//render flags
	const Uint32 craps_sdl_render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	win = sdl_create_window();
	rend = sdl_create_render(win, craps_sdl_render_flags);	
}

void vCrapsDisplayBackgroundPicture(SDL_Renderer* craps_main_window_renderer, SDL_Texture* tex_background)
{
	SDL_RenderCopy(craps_main_window_renderer, tex_background, NULL, NULL);
}

void vCrapsLoadInitResource(SDL_Texture* tex_background, SDL_Renderer* craps_main_window_renderer)
{
	SDL_Surface* surface_background = sdl_create_surface("res/pic/magnet.PNG");
	tex_background = sdl_create_texture_from_surface(craps_main_window_renderer, surface_background);
	//SDL_FreeSurface(surface_background);
}

SDL_Surface* sdl_create_surface(const char* location_pic)
{
	SDL_Surface* surface = IMG_Load(location_pic);
	if (surface == NULL)
	{
		printf_s("Error creating SDL surface: %s ", SDL_GetError());
		return NULL;
	}
	return surface;
}

SDL_Texture* sdl_create_texture_from_surface(SDL_Renderer* render, SDL_Surface* surface)
{
	SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surface);

	//free surface
	SDL_FreeSurface(surface);
	
	if (!tex)
	{
		printf_s("Error creating SDL texture: %s ", SDL_GetError());
		return NULL;
	}
	return tex;
}

SDL_Texture* sdl_load_picture_into_texture(const char* name_dice, SDL_Renderer* render, SDL_Rect *rect_dice)
{
	SDL_Surface* pic_dice = sdl_create_surface(name_dice);
	SDL_Texture* tex = sdl_create_texture_from_surface(render, pic_dice);
	SDL_QueryTexture(tex, NULL, NULL, &rect_dice->w, &rect_dice->h);
	return tex;
}

const char* sdl_pick_up_dice(int numbers)
{
	switch (numbers)
	{
		case 1:
			return "res/pic/dice_1.PNG";
		case 2:
			return "res/pic/dice_2.PNG";
		case 3:
			return "res/pic/dice_3.PNG";
		case 4:
			return "res/pic/dice_4.PNG";
		case 5:
			return "res/pic/dice_5.PNG";
		case 6:
			return "res/pic/dice_6.PNG";		
	}
	return NULL;
}
