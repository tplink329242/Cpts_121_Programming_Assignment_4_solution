/*******************************************************************************************

* Programmer: Guangbei Yi                                                                        *

* Class: CptS 121, Spring 2021; Programming Assignment 4                                            *

* Programming Assignment: A Game of Chance "Craps"               *

* Date: March 10, 2021                                                                           *

* Description: This program Write a program that play the game dice using sdl
*
* File Description: This profile include the main entertance.

* https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA4.htm

*******************************************************************************************/

#include "PAIV_Funcions.h"

int main(int argc, char* argv[])
{
	if (sdl_ttf_init() != 0)
	{
		return 1;
	}	
	/*Global SDL settings*/
	srand((unsigned)time(NULL));
	const Uint32 craps_sdl_render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	TTF_Font* font = TTF_OpenFont("res/data/calibri.ttf", 25);
	int craps_num_close_requested = 0;
	SDL_Color textColor = { 255, 255, 255 };
	
	//init sdl
	sdl_init();
	SDL_Event craps_event;

	//init keyboard state
	const Uint8* state;

	//init balance and wager
	int num_craps_game_balance = 0;
	int num_craps_game_wager = 0;

	int num_char_user_input = 0;
	char num_tmp_user_input;
	char num_user_input[20] = "\0";
	int num_tmp_char_count = 0;

	char msg_user_balance[100] = "Your balance is : ";
	char msg_user_amount[100] = "One moment please, we are checking your account!";
	char msg_user_amount_win[100] = "Gerat! You win this round";
	char msg_user_amount_lose[100] = "Ooops You lose this round!";
	char msg_user_amount_continue[100] = "We need re roll it again! ";
	
	//init locations
	SDL_Rect rect_main_screen_fonts;
	SDL_Rect rect_input_balance_fonts;
	SDL_Rect rect_input_wager_fonts;
	SDL_Rect rect_check_amount;
	SDL_Rect rect_roll_dice_1st;
	SDL_Rect rect_roll_dice_2nd;

	SDL_Rect rect_check_amount_win;
	SDL_Rect rect_check_amount_lose;
	SDL_Rect rect_check_amount_continue;
	
	//create window render and background
	SDL_Window* craps_main_window = sdl_create_window();;
	SDL_Renderer* craps_main_window_renderer = sdl_create_render(craps_main_window, craps_sdl_render_flags);
	SDL_Surface* surface_background = sdl_create_surface("res/pic/background.PNG");
	SDL_Texture* tex_background = sdl_create_texture_from_surface(craps_main_window_renderer, surface_background);

	//init main fonts
	SDL_Surface* msg_main_menu = TTF_RenderUTF8_Solid(font, "Welcome to Craps, press S to start the game. A player rolls two dice. Each die has six faces.", textColor);
	SDL_Texture* msg_fonts_mainmenu = sdl_create_texture_from_surface(craps_main_window_renderer, msg_main_menu);

	//init input balance fonts
	SDL_Surface* msg_input_balance = TTF_RenderUTF8_Solid(font, "Please Enter Your Balance! Number end by type d! ", textColor);
	SDL_Texture* msg_fonts_input_balance = sdl_create_texture_from_surface(craps_main_window_renderer, msg_input_balance);

	//init input wager fonts
	SDL_Surface* msg_input_wager = TTF_RenderUTF8_Solid(font, msg_user_balance, textColor);
	SDL_Texture* msg_fonts_input_wager = sdl_create_texture_from_surface(craps_main_window_renderer, msg_input_wager);

	//init check amount
	SDL_Surface* msg_check_amount = TTF_RenderUTF8_Solid(font, msg_user_amount, textColor);
	SDL_Texture* msg_fonts_check_amount = sdl_create_texture_from_surface(craps_main_window_renderer, msg_check_amount);

	//init check amount win
	SDL_Surface* msg_check_amount_win = TTF_RenderUTF8_Solid(font, msg_user_amount_win, textColor);
	SDL_Texture* msg_fonts_check_amount_win = sdl_create_texture_from_surface(craps_main_window_renderer, msg_check_amount_win);

	//init check amount lose
	SDL_Surface* msg_check_amount_lose = TTF_RenderUTF8_Solid(font, msg_user_amount_lose, textColor);
	SDL_Texture* msg_fonts_check_amount_lose = sdl_create_texture_from_surface(craps_main_window_renderer, msg_check_amount_lose);

	//init check amount continue
	SDL_Surface* msg_check_amount_continue = TTF_RenderUTF8_Solid(font, msg_user_amount_continue, textColor);
	SDL_Texture* msg_fonts_check_amount_continue = sdl_create_texture_from_surface(craps_main_window_renderer, msg_check_amount_continue);
	
	//query the text
	SDL_QueryTexture(msg_fonts_mainmenu, NULL, NULL, &rect_main_screen_fonts.w, &rect_main_screen_fonts.h);
	SDL_QueryTexture(msg_fonts_input_balance, NULL, NULL, &rect_input_balance_fonts.w, &rect_input_balance_fonts.h);
	SDL_QueryTexture(msg_fonts_input_wager, NULL, NULL, &rect_input_wager_fonts.w, &rect_input_wager_fonts.h);
	SDL_QueryTexture(msg_fonts_check_amount, NULL, NULL, &rect_check_amount.w, &rect_check_amount.h);

	SDL_QueryTexture(msg_fonts_check_amount_win, NULL, NULL, &rect_check_amount_win.w, &rect_check_amount_win.h);
	SDL_QueryTexture(msg_fonts_check_amount_lose, NULL, NULL, &rect_check_amount_lose.w, &rect_check_amount_lose.h);
	SDL_QueryTexture(msg_fonts_check_amount_continue, NULL, NULL, &rect_check_amount_continue.w, &rect_check_amount_continue.h);
	
	boolean is_wager_fonts_init = false;
	boolean is_wager_greater_than_balance = false;
	boolean is_check_amout_fonts_init = false;
	boolean is_check_dices_already_rolled = false;
	boolean is_the_second_roll = false;

	
	//text locations
	rect_main_screen_fonts.x = 0;
	rect_main_screen_fonts.y = 0;

	rect_input_balance_fonts.x = 0;
	rect_input_balance_fonts.y = 0;

	rect_input_wager_fonts.x = 0;
	rect_input_wager_fonts.y = 0;

	rect_check_amount.x = 0;
	rect_check_amount.y = 0;

	rect_roll_dice_1st.x = 40;
	rect_roll_dice_1st.y = 200;

	rect_roll_dice_2nd.x = 550;
	rect_roll_dice_2nd.y = 200;

	rect_check_amount_win.x = 0;
	rect_check_amount_win.y = 0;
	
	rect_check_amount_lose.x = 0;
	rect_check_amount_lose.y = 0;

	rect_check_amount_continue.x = 0;
	rect_check_amount_continue.y = 0;
	
	//init states
	int craps_num_game_state = CRAPS_STATE_MAIN_MENU;
	int craps_num_in_game_state = 0;
	int craps_time_stay_states = 0;

	//init dice numbers
	int num_dice1 = 0;
	int num_dice2 = 0;
	int num_dice_sum = 0;
	int num_point_value = 0;
	int num_check_win_or_lose = 0;

	SDL_Texture* tex_dice_1 = sdl_load_picture_into_texture(sdl_pick_up_dice(1), craps_main_window_renderer, &rect_roll_dice_1st);
	SDL_Texture* tex_dice_2 = sdl_load_picture_into_texture(sdl_pick_up_dice(2), craps_main_window_renderer, &rect_roll_dice_2nd);


	
	//vCrapsInitGameMainWindow(craps_main_window, craps_main_window_renderer);
	//vCrapsLoadInitResource(tex_background, craps_main_window_renderer);

	//load main window
	while (!craps_num_close_requested)
	{
		while (SDL_PollEvent(&craps_event))
		{			
			if (craps_event.type == SDL_QUIT)
			{
				craps_num_close_requested = 1;
				break;
			}
			if (craps_event.type == SDL_KEYDOWN)
			{
				state = SDL_GetKeyboardState(NULL);
				if (state[SDL_SCANCODE_S])
				{
					craps_num_game_state = CRAPS_STATE_IN_GAME;
					craps_num_in_game_state = CRAPS_STATE_IN_GAME_BALANCE;
					num_craps_game_balance = 0;
					num_craps_game_wager = 0;
					break;
				}
			}
			if (craps_num_game_state == CRAPS_STATE_IN_GAME)
			{
				switch (craps_num_in_game_state)
				{
				case CRAPS_STATE_IN_GAME_BALANCE:
					
					SDL_StartTextInput();
				
					switch (craps_event.type) {
					case SDL_TEXTINPUT:
						{
							if (craps_event.key.state == 'd')
							{
								num_craps_game_balance = atoi(num_user_input);
								num_tmp_char_count = 0;
								SDL_StopTextInput();
								craps_num_in_game_state = CRAPS_STATE_IN_GAME_WAGER;								
								break;
							}
							if ((int)craps_event.key.state >= '0' && (int)craps_event.key.state <= '9')
							{
								num_tmp_char_count++;
								num_char_user_input = craps_event.key.state;
								strcat(num_user_input, &num_char_user_input);
							}														
						}						
					}					
					break;
				case CRAPS_STATE_IN_GAME_WAGER:

					SDL_StartTextInput();
					is_the_second_roll = false;

					//init inout wager fonts
					if (is_wager_fonts_init == false)
					{
						//strcat(msg_user_balance, num_user_input);
						printf_s("The original called banalce is: %d\n", num_craps_game_balance);
						strcat(msg_user_balance, itoa(num_craps_game_balance, num_user_input, 10));
						strcat(msg_user_balance, " Please Enter Your Wager! Number end by type d, press enter to refersh game states! ");
						msg_input_wager = TTF_RenderUTF8_Solid(font, msg_user_balance, textColor);
						msg_fonts_input_wager = sdl_create_texture_from_surface(craps_main_window_renderer, msg_input_wager);
						SDL_QueryTexture(msg_fonts_input_wager, NULL, NULL, &rect_input_wager_fonts.w, &rect_input_wager_fonts.h);

						memset(num_user_input, '\0', sizeof(num_user_input));
						is_wager_fonts_init = true;
					}
					

					switch (craps_event.type) {
					case SDL_TEXTINPUT:
					{
						if (craps_event.key.state == 'd')
						{
							num_craps_game_wager = atoi(num_user_input);
							num_tmp_char_count = 0;
							SDL_StopTextInput();
							craps_num_in_game_state = CRAPS_STATE_IN_GAME_CHECK_AMOUNT;
							memset(num_user_input, '\0', sizeof(num_user_input));

							//def flag
							is_wager_fonts_init == false;
							is_check_amout_fonts_init == false;
							break;
						}
						if ((int)craps_event.key.state >= '0' && (int)craps_event.key.state <= '9')
						{
							num_tmp_char_count++;
							num_char_user_input = craps_event.key.state;
							strcat(num_user_input, &num_char_user_input);
						}
					}
					default:;
					}
					break;

				case CRAPS_STATE_IN_GAME_CHECK_AMOUNT:

					is_wager_greater_than_balance = (boolean)check_wager_amount(num_craps_game_wager, num_craps_game_balance);

					if (is_wager_greater_than_balance == true)
					{
						
						if (is_check_amout_fonts_init == false)
						{
							char msg_user_amount_correct[100] = "Checking complete! You are ready to go!";
							msg_check_amount = TTF_RenderUTF8_Solid(font, msg_user_amount_correct, textColor);
							msg_fonts_check_amount = sdl_create_texture_from_surface(craps_main_window_renderer, msg_check_amount);
							
							SDL_QueryTexture(msg_fonts_check_amount, NULL, NULL, &rect_check_amount.w, &rect_check_amount.h);
							is_check_amout_fonts_init = true;
							craps_time_stay_states = 0;
						}

						//procceed to roll the dice
						craps_num_in_game_state = CRAPS_STATE_IN_GAME_ROLL_DICE;
						craps_time_stay_states = 0;
						is_check_amout_fonts_init = false;
						//SDL_Delay(1000);
						//craps_time_stay_states += 1;
						//if (craps_time_stay_states >= 10)
						//{
						//	//procceed to roll the dice
						//	craps_num_in_game_state = CRAPS_STATE_IN_GAME_ROLL_DICE;
						//	craps_time_stay_states = 0;
						//	is_check_amout_fonts_init = false;
						//}
					}
					else
					{
						if (is_check_amout_fonts_init == false)
						{
							char msg_user_amount_correct[100] = "Checking failed! You will be back to wager selection!";
							msg_check_amount = TTF_RenderUTF8_Solid(font, msg_user_amount_correct, textColor);
							msg_fonts_check_amount = sdl_create_texture_from_surface(craps_main_window_renderer, msg_check_amount);
							
							SDL_QueryTexture(msg_fonts_check_amount, NULL, NULL, &rect_check_amount.w, &rect_check_amount.h);
							is_check_amout_fonts_init = true;
							craps_time_stay_states = 0;
						}
						craps_time_stay_states += 1;
						if (craps_time_stay_states >= 5)
						{
							//procceed to roll the dice
							craps_num_in_game_state = CRAPS_STATE_IN_GAME_WAGER;
							craps_time_stay_states = 0;
							is_check_amout_fonts_init = false;
						}
					}					
					break;				

				case CRAPS_STATE_IN_GAME_ROLL_DICE:

					if (is_check_dices_already_rolled == false)
					{
						//roll the dice
						num_dice1 = roll_die();
						printf_s("The first roll is : %d \n", num_dice1);
						num_dice2 = roll_die();
						printf_s("The second roll is : %d \n", num_dice2);

						tex_dice_1 = sdl_load_picture_into_texture(sdl_pick_up_dice(num_dice1), craps_main_window_renderer, &rect_roll_dice_1st);
						tex_dice_2 = sdl_load_picture_into_texture(sdl_pick_up_dice(num_dice2), craps_main_window_renderer, &rect_roll_dice_2nd);						
						//is_check_dices_already_rolled = true;						
					}
					SDL_Delay(10);
					craps_num_in_game_state = CRAPS_STATE_IN_GAME_CHECK_RESULT;
					break;
					
				case CRAPS_STATE_IN_GAME_CHECK_RESULT:

					num_dice_sum = calculate_sum_dice(num_dice1, num_dice2);
					printf_s("The sum number is %d\n", num_dice_sum);
					
					if (is_the_second_roll == FALSE)
					{
						num_check_win_or_lose = is_win_loss_or_point(num_dice_sum);

						switch (num_check_win_or_lose)
						{
							case 1:
								//player win
								num_craps_game_balance = adjust_bank_balance(num_craps_game_balance, num_craps_game_wager, num_check_win_or_lose);
								craps_num_in_game_state = CRAPS_STATE_IN_GAME_WAGER;
								is_wager_fonts_init = false;
								printf_s("The new balance is %d\n", num_craps_game_balance);
								memset(msg_user_balance, '\0', sizeof(msg_user_balance));
								strcat(msg_user_balance, "Your balance is : ");
								break;
							case 0:
								//player lose
								num_craps_game_balance = adjust_bank_balance(num_craps_game_balance, num_craps_game_wager, num_check_win_or_lose);
								is_wager_fonts_init = false;
								memset(msg_user_balance, '\0', sizeof(msg_user_balance));
								strcat(msg_user_balance, "Your balance is : ");
								if (num_craps_game_balance <= 0)
									{
										//game over
										craps_num_game_state = CRAPS_STATE_MAIN_MENU;
										craps_num_in_game_state = 0;
									}
									craps_num_in_game_state = CRAPS_STATE_IN_GAME_WAGER;
								break;
							case -1:
								//roll again
								num_point_value = num_dice_sum;
								craps_num_in_game_state = CRAPS_STATE_IN_GAME_ROLL_DICE;
								break;
							
							default:;
						}
						is_the_second_roll = true;
					}
					else
					{
						num_check_win_or_lose = is_point_loss_or_neither(num_dice_sum, num_point_value);

						switch (num_check_win_or_lose)
						{
						case 1:
							//player win
							num_craps_game_balance = adjust_bank_balance(num_craps_game_balance, num_craps_game_wager, num_check_win_or_lose);
							craps_num_in_game_state = CRAPS_STATE_IN_GAME_WAGER;
							printf_s("The new balance is %d \n", num_craps_game_balance);
							is_wager_fonts_init = false;
							memset(msg_user_balance, '\0', sizeof(msg_user_balance));
							strcat(msg_user_balance, "Your balance is : ");
							break;
						case 0:
							//player lose
							num_craps_game_balance = adjust_bank_balance(num_craps_game_balance, num_craps_game_wager, num_check_win_or_lose);
							is_wager_fonts_init = false;
							memset(msg_user_balance, '\0', sizeof(msg_user_balance));
							strcat(msg_user_balance, "Your balance is : ");
							if (num_craps_game_balance <= 0)
							{
								//game over
								craps_num_game_state = CRAPS_STATE_MAIN_MENU;
								craps_num_in_game_state = 0;
							}
							craps_num_in_game_state = CRAPS_STATE_IN_GAME_WAGER;
							break;
						case -1:
							//roll again
							craps_num_in_game_state = CRAPS_STATE_IN_GAME_ROLL_DICE;
							break;

						default:;
						}
					}
					break;					
				default:;
				}
			}
		}		
		// clear the window
		SDL_RenderClear(craps_main_window_renderer);

		//display background
		vCrapsDisplayBackgroundPicture(craps_main_window_renderer, tex_background);


		if (craps_num_game_state == CRAPS_STATE_MAIN_MENU)
		{
			SDL_RenderCopy(craps_main_window_renderer, tex_dice_1, NULL, &rect_roll_dice_1st);
			SDL_RenderCopy(craps_main_window_renderer, tex_dice_2, NULL, &rect_roll_dice_2nd);
			SDL_RenderCopy(craps_main_window_renderer, msg_fonts_mainmenu, NULL, &rect_main_screen_fonts);
		}
		if (craps_num_in_game_state == CRAPS_STATE_IN_GAME_BALANCE)
		{
			SDL_RenderCopy(craps_main_window_renderer, msg_fonts_input_balance, NULL, &rect_input_balance_fonts);
		}
		if (craps_num_in_game_state == CRAPS_STATE_IN_GAME_WAGER)
		{
			SDL_RenderCopy(craps_main_window_renderer, msg_fonts_input_wager, NULL, &rect_input_wager_fonts);
		}
		if (craps_num_in_game_state == CRAPS_STATE_IN_GAME_CHECK_AMOUNT)
		{
			SDL_RenderCopy(craps_main_window_renderer, msg_fonts_check_amount, NULL, &rect_check_amount);
		}
		if (craps_num_in_game_state == CRAPS_STATE_IN_GAME_ROLL_DICE)
		{
			SDL_RenderCopy(craps_main_window_renderer, tex_dice_1, NULL, &rect_roll_dice_1st);
			SDL_RenderCopy(craps_main_window_renderer, tex_dice_2, NULL, &rect_roll_dice_2nd);		
		}
		if (craps_num_in_game_state == CRAPS_STATE_IN_GAME_CHECK_RESULT)
		{
			SDL_RenderCopy(craps_main_window_renderer, tex_dice_1, NULL, &rect_roll_dice_1st);
			SDL_RenderCopy(craps_main_window_renderer, tex_dice_2, NULL, &rect_roll_dice_2nd);
			switch (num_check_win_or_lose)
			{
			case 1:
				SDL_RenderCopy(craps_main_window_renderer, msg_fonts_check_amount_win, NULL, &rect_check_amount_win);
				break;
			case -1:
				SDL_RenderCopy(craps_main_window_renderer, msg_fonts_check_amount_continue, NULL, &rect_check_amount_continue);
				break;
			case 0:
				SDL_RenderCopy(craps_main_window_renderer, msg_fonts_check_amount_lose, NULL, &rect_check_amount_lose);				
				break;
			default:;
			}
		}
		
		//show the render
		SDL_RenderPresent(craps_main_window_renderer);
		//Sleep(500);

		// wait 1/60th of a second
		SDL_Delay(1000 / 30);
	}


	//release res
	//release tex
	SDL_DestroyTexture(tex_background);
	SDL_DestroyTexture(msg_fonts_mainmenu);

	//release other
	SDL_DestroyRenderer(craps_main_window_renderer);
	SDL_DestroyWindow(craps_main_window);
	SDL_Quit();
	
	return 0;
}
