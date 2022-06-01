#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>


#define MAX_N 11
#define MAX_M 11

using namespace std;

struct Wezel
{
    int coord_1;
	int	coord_2;
	bool visited;
	
    Wezel *syn, *ojciec, *P_brat, *L_brat, *G_brat, *D_brat, *poprzedni;
    
    Wezel()
    {
		coord_1;
		coord_2;
    	syn = NULL;
    	ojciec = NULL;
    	L_brat = NULL;
    	P_brat = NULL;
    	G_brat = NULL;
		D_brat = NULL;
		poprzedni = NULL;
    	visited = false;
	}
    
};



string sprawdzeniePlanszyRed(int tablicaPlanszy[MAX_N][MAX_M], bool tablicaPlanszy_bool[MAX_N][MAX_M], int board_size, string type_of_test, int r_pawns, int b_pawns)
{
	int wskaznik1;
	int wskaznik2;
	
	int coord_1_pawn1 = 0;
	int coord_2_pawn1 = 0;
	int coord_1_pawn2 = 0;
	int coord_2_pawn2 = 0;
	
	int empty_pawn_slots = 0;
	int no_pawns_num = 0;
			
	bool is_board_possible_bool = false;
	bool is_game_over_bool = false;
		
	bool red_win_1_move_naive = false;
	bool blue_win_1_move_naive = false;
	bool red_win_2_moves_naive = false;
	bool blue_win_2_moves_naive = false;
	
	bool pick_no_winning_position = false;
	
	bool found_possible_way = false;
	
	bool red_win = false;
	bool is_board_possible = false;	
	bool removed_pawn_bool = false;
	bool start_removing = false;
	bool added_pawn_bool = false;	
	bool added_another_pawn_bool = false;
	bool start_adding = false;
	bool block_one_pawn = false;
	bool last_pawn_placed = false;
	
	bool stopLooping = false;
	
	bool possible_move = false;
	bool temp_block = false;
	
	string answer = "";				
	Wezel *temp;
	int counter = 0;
	
	
	if(type_of_test == "is_board_possible_bool")
	{
		is_board_possible_bool = true;
		removed_pawn_bool = true;
	}
	else if(type_of_test == "is_game_over_bool")
	{
		is_game_over_bool = true;
		removed_pawn_bool = true;	
	}
	else if(type_of_test == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
	{
		//cout << "JEST" << endl;
		red_win_1_move_naive = true;
		added_pawn_bool = true;
		
	}
	else if(type_of_test == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
	{
		//cout << "JEST" << endl;
		blue_win_1_move_naive = true;
		added_pawn_bool = true;
	}	
	else if(type_of_test == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")
	{
		red_win_2_moves_naive = true;
		added_pawn_bool = true;
	
	}
	else if(type_of_test == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")
	{						
		blue_win_2_moves_naive = true;
		added_pawn_bool = true;
	}
	else if(type_of_test == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT_CHECK_NO_WIN")
	{						
		red_win_1_move_naive = true;
		pick_no_winning_position = true;
		added_pawn_bool = true;
	}
	else if(type_of_test == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT_CHECK_NO_WIN")
	{						
		blue_win_1_move_naive = true;
		pick_no_winning_position = true;
		added_pawn_bool = true;
	}
	
	
	
	
	
	//cout << type_of_test << "TUTAJ" << endl;
	empty_pawn_slots = (board_size*board_size)-b_pawns-r_pawns;
	//cout << empty_pawn_slots << "TUUUUUTAJ" << endl;
	
	do
	{
		counter++;
		if(counter == 100)
		{
			//break;
		}
		
		if(is_board_possible_bool == true && start_removing == true && tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] == 1)
		{
			//cout << "USUWA PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
			tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
			//cout << tablicaPlanszy[coord_1_pawn1][coord_2_pawn1];
			removed_pawn_bool = true;
			red_win = false;
		}
		
		if((red_win_1_move_naive == true || red_win_2_moves_naive == true) && start_adding == true)
		{
			if(red_win_1_move_naive == true || block_one_pawn == false)
			{
				if(tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] == 0)
				{	
					//cout << "DODAJE RED 1-PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
					no_pawns_num++;
					added_pawn_bool = true;
					block_one_pawn = true;	
					
					//removed_pawn = tablicaPlanszy[coord_1_pawn1][coord_2_pawn1];
					tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 1;
					//cout << tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] << endl;	
				}	
			}				

			if(red_win_2_moves_naive == true && start_adding == true && block_one_pawn == true)
			{
				if(tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] == 0)
				{	
					//cout << "DODAJE RED ANOTHER-PIONKA" << coord_1_pawn2 << "--" << coord_2_pawn2 << endl;
					added_another_pawn_bool = true;
					added_pawn_bool = false;
					//removed_pawn = tablicaPlanszy[coord_1_pawn2][coord_2_pawn2];
					tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] = 1;
					//cout << tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] << endl;	
				}	
			}
		}
			
		if(removed_pawn_bool == true || added_pawn_bool == true || added_another_pawn_bool == true)
		{
			
			for(int k = 0; k < board_size; k++)
			{	
				if(tablicaPlanszy[k][0] == 1)
				{
					wskaznik1 = k;
					wskaznik2 = 0;
					Wezel *korzen_red = new Wezel();
					temp = korzen_red;
					temp->coord_1 = wskaznik1;
					temp->coord_2 = 0;
					tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
					//cout << "POCZATEK" << endl;
					found_possible_way = true;
					
					do
					{		
						possible_move = true;
							
						if(temp->coord_2 == board_size - 1)
						{
							if(red_win_1_move_naive == true || is_board_possible_bool == true || is_game_over_bool == true)
								{
									//if(pick_no_winning_position == false)
									//{
										red_win = true;	
										answer = "YES RED";
										//cout << "RED WIN TUTAJJ" << endl;	
								//	}
											
									//break;
								}
								else if(red_win_2_moves_naive == true && added_another_pawn_bool == true)
								{
									red_win = true;	
									answer = "YES RED";
									//cout << "RED WIN" << endl;		
									//break;
								}
								else if(red_win_2_moves_naive == true && start_adding == false)
								{
									red_win = true;
									answer = "YES RED";
									//cout << "YES RED TUTAJ2" << endl;
								}	
						}
							
						//cout << temp->coord_1 << " ";
						//cout << temp->coord_2 << " RED" << endl;
		
						if(temp->coord_1 > 0 && temp_block == false && temp->P_brat == NULL)
						{
							if(tablicaPlanszy[temp->coord_1-1][temp->coord_2] == 1 && tablicaPlanszy_bool[temp->coord_1-1][temp->coord_2] == false)
							{
								//cout << "GORA" << endl;
			
								wskaznik1 = wskaznik1 - 1;
										
								Wezel *nowy = new Wezel();
								temp->P_brat = nowy;
								nowy->poprzedni = temp;
								nowy->L_brat = temp;
									//temp->visited = true;
								temp = nowy;
								temp->coord_1 = wskaznik1;
								temp->coord_2 = wskaznik2;
											
								//cout << temp->coord_1 << " ";
								//cout << temp->coord_2 << " E" << endl;
											
								possible_move = false;
								temp_block = true;
							}
						}
									
						if(temp->coord_2 < board_size - 1 && temp_block == false)
						{		
							if(tablicaPlanszy[temp->coord_1][temp->coord_2+1] == 1 && tablicaPlanszy_bool[temp->coord_1][temp->coord_2+1] == false)
							{	
								//cout << "PRAWO" << endl;
											
								wskaznik2 = wskaznik2 + 1;
											
								Wezel *nowy = new Wezel();
								temp->syn = nowy;
								nowy->poprzedni = temp;
								nowy->ojciec = temp;
								//temp->visited = true;
								temp = nowy;
								temp->coord_1 = wskaznik1;
								temp->coord_2 = wskaznik2;
											
								//cout << temp->coord_1 << " ";
								//cout << temp->coord_2 << " B" << endl;
											
								possible_move = false;
								temp_block = true;
							}
									
						}	
										
						if(temp->coord_1 < board_size - 1 && temp_block == false && temp->L_brat == NULL)
						{
							if(tablicaPlanszy[temp->coord_1+1][temp->coord_2] == 1 && tablicaPlanszy_bool[temp->coord_1+1][temp->coord_2] == false)
							{		
								//cout << "DOL" << endl;					
								tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
											
								wskaznik1 = wskaznik1 + 1;
											
								Wezel *nowy = new Wezel();
								temp->L_brat = nowy;
								nowy->poprzedni = temp;
								nowy->P_brat = temp;
								//nowy->ojciec = temp->ojciec;
								//temp->visited = true;
								temp = nowy;
								temp->coord_1 = wskaznik1;
								temp->coord_2 = wskaznik2;
			
								//cout << temp->coord_1 << " ";
								//cout << temp->coord_2 << " C" << endl;
																
								possible_move = false;
								temp_block = true;
							}
						}	
								
						if(temp->coord_2 < board_size - 1 && temp_block == false && temp->G_brat == NULL)
						{	
							//cout << tablicaPlanszy[temp->coord_1-1][temp->coord_2-1] << endl;	
							//cout << temp->coord_1-1 << endl;
							//cout << temp->coord_2-1 << endl;
							if(tablicaPlanszy[temp->coord_1-1][temp->coord_2-1] == 1 && tablicaPlanszy_bool[temp->coord_1-1][temp->coord_2-1] == false)
							{		
								if(wskaznik1 - 1 >= 0 && wskaznik2 - 1 >= 0)
								{
									//cout << "SKOS GORA" << endl;
											
									wskaznik1 = wskaznik1 - 1;
									wskaznik2 = wskaznik2 - 1;
			
									tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
											
									Wezel *nowy = new Wezel();
									temp->G_brat = nowy;
									nowy->poprzedni = temp;
									nowy->D_brat = temp;
									temp = nowy;
									temp->coord_1 = wskaznik1;
									temp->coord_2 = wskaznik2;
											
									//cout << temp->coord_1 << " ";
									//cout << temp->coord_2 << " B" << endl;
											
									possible_move = false;
									temp_block = true;	
								}		
							}			
						}
											
						if(temp->coord_1 < board_size - 1 && temp->coord_2 < board_size - 1 && temp_block == false && temp->D_brat == NULL)
						{
							if(tablicaPlanszy[temp->coord_1+1][temp->coord_2+1] == 1 && tablicaPlanszy_bool[temp->coord_1+1][temp->coord_2+1] == false)
							{
								//cout << "SKOS DOL" << endl;
								tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
											
								wskaznik1 = wskaznik1 + 1;
								wskaznik2 = wskaznik2 + 1;
											
								Wezel *nowy = new Wezel();
								temp->D_brat = nowy;
								nowy->poprzedni = temp;
								nowy->G_brat = temp;
								//temp->visited = true;
								temp = nowy;
								temp->coord_1 = wskaznik1;
								temp->coord_2 = wskaznik2;
											
								//cout << temp->coord_1 << " ";
								//cout << temp->coord_2 << " D" << endl;
										
								temp_block = true;	
								possible_move = false;
							}
						}
								
						if(temp->coord_2 > 0 && temp_block == false && temp->ojciec == NULL)
						{		
							//cout << tablicaPlanszy[temp->coord_1][temp->coord_2-1] << endl;
							if(tablicaPlanszy[temp->coord_1][temp->coord_2-1] == 1 && tablicaPlanszy_bool[temp->coord_1][temp->coord_2-1] == false)
							{	
								//cout << "LEWO" << endl;
										
								wskaznik2 = wskaznik2 - 1;	
										
								tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
										
								Wezel *nowy = new Wezel();
								temp->G_brat = nowy;
								nowy->poprzedni = temp;
								nowy->D_brat = temp;
								//nowy->ojciec = temp->ojciec;
								//temp->visited = true;
								temp = nowy;
								temp->coord_1 = wskaznik1;
								temp->coord_2 = wskaznik2;
											
								//cout << temp->coord_1 << " ";
								//cout << temp->coord_2 << " B" << endl;
											
								possible_move = false;
								temp_block = true;
							}			
						}
						
						if(possible_move == true && temp_block == false)
						{
							//cout << "COFKA" << endl;
							tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
								
							if(temp->poprzedni != NULL)
							{	
								temp = temp->poprzedni;
								wskaznik1 = temp->coord_1;
								wskaznik2 = temp->coord_2;
							}
						} 
						
						temp_block = false;
								
					} while(temp->poprzedni != NULL);		
				}
				else
				{
					found_possible_way = false;
				}	
			}	
			
			if(found_possible_way == true)
			{
				for(int l = 0; l < board_size; l++)
				{
					for(int m = 0; m < board_size; m++)
					{
						tablicaPlanszy_bool[l][m] = false;
					}	
				}
			}
			
			if(is_board_possible_bool == true)
			{
				if(red_win == false && start_removing == false)
				{
					//cout << "TUTAJ3" << endl;
					removed_pawn_bool = false;
					break;		
				}
				else if(red_win == true && start_removing == false)
				{	
					//cout << "YES RED4" << endl;
					removed_pawn_bool = false;
					answer = "YES RED";		
				}
				else if(red_win == false && start_removing == true)
				{
					//cout << "TUTAJ5" << endl;
					break;
				}		
			}
			else if(red_win_1_move_naive == true)
			{
				if(red_win == false && start_adding == false)
				{
					added_pawn_bool = false;
				}
				else if(red_win == true && start_adding == false)
				{	
					added_pawn_bool = false;
					
					if(pick_no_winning_position == true)
					{
						answer = "YES RED";		
					}
					else
					{
						answer = "NO";		
					}
					
					//cout << "ALREADY WON" << endl;	
					break;	
				}
				else if(red_win == true && start_adding == true)
				{
					if(pick_no_winning_position == true)
					{
						red_win = false;
						answer = "";
						//cout << "WINNING PLACE" << endl;	
						//break;	
					}		
				}
				else if(red_win == false && start_adding == true && pick_no_winning_position == true)
				{
					added_pawn_bool = false;
					answer = "NO";
					//cout << "NIE WYGRYWAJACE MIEJSCE" << endl;
				}	
			}	
			else if(red_win_2_moves_naive == true)
			{
				if(red_win == false && start_adding == false)
				{
					added_pawn_bool = false;
				}
				else if(red_win == true && start_adding == false)
				{
					added_pawn_bool = false;
					answer = "NO";	
					//cout << "NAAH" << endl;
					break;
				}
				else if(red_win == true && start_adding == true && added_another_pawn_bool == false)
				{
					added_pawn_bool = false;
					answer = "NO";	
					//cout << "ALREADY WON" << endl;
					//break;
				}
				else if(red_win == true && start_adding == true && added_another_pawn_bool == true)
				{
					added_pawn_bool = false;
					answer = "YES RED";	
					//cout << "WIN" << endl;
					//break;
				}	
			}	
		}

		if(removed_pawn_bool == true || added_pawn_bool == true || added_another_pawn_bool == true)
		{
			if(removed_pawn_bool == true && is_board_possible_bool == true)
			{
				//cout << "ZWRACA SWOJEGO RED PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
				tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 1;
				removed_pawn_bool = false;	
			}
			else if((added_pawn_bool == true && red_win_1_move_naive == true) || (block_one_pawn == false && red_win_2_moves_naive == true))
			{
				//cout << "1-ZWRACA USUNIETEGO PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
				tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
				added_pawn_bool = false;
				last_pawn_placed = false;			
			}
			else if(added_another_pawn_bool == true && red_win_2_moves_naive == true)
			{
				//cout << "1-ZWRACA USUNIETEGO ANOTHER PIONKA" << coord_1_pawn2 << "--" << coord_2_pawn2 << endl;
				tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] = 0;
				added_another_pawn_bool = false;
			}	
		}
		
		if(red_win_1_move_naive == true || red_win_2_moves_naive == true)
		{
			if(answer == "YES RED" || answer == "NO")
			{
				if(block_one_pawn == true)
				{
					tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
					//cout << "XD 1-ZWRACA RED PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
					break;
				}
			}	
		}
			
			
			
		if((start_removing == true && is_board_possible_bool == true) || (start_adding == true && red_win_1_move_naive == true) || (start_adding == true && red_win_2_moves_naive == true))
		{
			if((start_removing == true && is_board_possible_bool == true) || (start_adding == true && red_win_1_move_naive == true) || (start_adding == true && red_win_2_moves_naive == true && block_one_pawn == false))
			{
				if(coord_1_pawn1 <= board_size - 1 && coord_2_pawn1 <= board_size - 1)
				{
					//cout << coord_1_pawn1 << "--" << coord_2_pawn1 << "--PIERWSZY--" << endl;
					if((coord_1_pawn1 < board_size - 1) && (coord_2_pawn1 == board_size - 1))
					{
						coord_1_pawn1++;
						coord_2_pawn1 = 0;
					}
					else if(coord_2_pawn1 < board_size - 1)
					{
						coord_2_pawn1++;	
					}
					
					//cout << coord_1_pawn1 << "--" << coord_2_pawn1 << "--PIERWSZY--" << endl;
				}
				
				if(red_win_1_move_naive == true)
				{
					if(coord_1_pawn1 == board_size - 1 && coord_2_pawn1 == board_size - 1)
					{
						//cout << coord_1_pawn1 << "--" << coord_2_pawn1 << "--PIERWSZY--" << endl;
						last_pawn_placed = true;	
					}	
					
					//cout << empty_pawn_slots << " " << no_pawns_num << endl;
					if(empty_pawn_slots == no_pawns_num)
					{
						last_pawn_placed = false;
						
						if(pick_no_winning_position == true)
						{
							answer = "YES RED";	
							break;
						}
					}		 
				}	
			}
				
			
				
				
				
			if(start_adding == true && red_win_2_moves_naive == true && block_one_pawn == true)
			{	
				//cout << "NIE WCHODZI" << endl;
				if(coord_1_pawn2 <= board_size - 1 && coord_2_pawn2 <= board_size - 1)
				{
					//cout << coord_1_pawn2 << "--" << coord_2_pawn2 << "--DRUGI--" << endl;
					if(coord_2_pawn2 == 0)
					{
						if(coord_1_pawn2 == 0)
						{
							//cout << "1-ZWRACA USUNIETEGO PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
							
							if(blue_win_2_moves_naive == true)
							{
								stopLooping = true;	
							}
							
							tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
							block_one_pawn = false;
							coord_1_pawn2 = board_size - 1;
							coord_2_pawn2 = board_size - 1;	
							
							if(coord_2_pawn1 == board_size - 1)
							{	
								coord_1_pawn1++;
								coord_2_pawn1 = 0;
							}
							else
							{
								coord_2_pawn1++;	
							}	
						}
						else
						{
							coord_1_pawn2--;
							coord_2_pawn2 = board_size - 1;	
						}	
					}
					else
					{
						coord_2_pawn2--;	
					}
				}		
			}
		}				
					
		if(is_board_possible_bool == true && start_removing == false)
		{
			//cout << "TUTAJ1" << endl;
			start_removing = true;	
		}
		else if(is_board_possible_bool == true && start_removing == true)
		{
			if(coord_1_pawn1 == board_size - 1 && coord_2_pawn1 == board_size - 1)
			{
				//cout << "TUTAJ2" << endl;
				start_removing = false;	
			}	
		}
		
		if((red_win_1_move_naive == true && start_adding == false) || (red_win_2_moves_naive == true && start_adding == false))
		{
			//cout << "TUTAJ1 XDD" << endl;
			start_adding = true;	
		}
		else if((red_win_1_move_naive == true && start_adding == true) || (red_win_2_moves_naive == true && start_adding == true))
		{
			//cout << "WCHODZI KURWA XDD" << endl;
			if(coord_1_pawn1 == board_size - 1 && coord_2_pawn1 == board_size - 1)
			{
				
				if(red_win_1_move_naive == true && last_pawn_placed == false)
				{
					//cout << "TUTAJ2 XDD" << endl;
					start_adding = false;	
				}
				if(red_win_2_moves_naive == true)
				{
					if(coord_1_pawn2 == board_size - 1 && coord_2_pawn2 == board_size - 1)
					{
						//cout << "TUTAJ3 XDD" << endl;
						//cout << "1-ZWRACA USUNIETEGO PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
						tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
						start_adding = false;	
					}
					else
					{
						start_adding = false;		
					}		
				}
			}	
		}
		else if(red_win_2_moves_naive == true && start_adding == true)
		{
			if(coord_1_pawn2 == board_size - 1 && coord_2_pawn2 == board_size - 1)
			{
				//cout << "TUTAJ25" << endl;
				if(red_win_2_moves_naive == true)
				{
					block_one_pawn = false;
				}	
			}	
		}
								
	} while(start_removing == true || start_adding == true);
	

	if(is_game_over_bool == true)
	{
		if(answer == "YES RED")
		{
			answer = "YES RED";
		}		
	}
	else if(is_board_possible_bool == true)
	{	
		if(answer == "YES RED" && r_pawns == b_pawns)
		{
				answer = "NO";	
		}
		else if(red_win == true)
		{
				answer = "NO";
		}
		else
		{
				answer = "YES";	
		}	
	}
	else if(red_win_1_move_naive == true)
	{
		if(answer == "YES RED")
		{
			answer = "YES";
			//cout << answer << endl << endl << endl;
		}
		else
		{
			answer = "NO";	
		}
	}
	else if(red_win_2_moves_naive == true)
	{
		if(answer == "YES RED")
		{
			answer = "YES";
			//cout << answer << endl << endl << endl;
		}
		else
		{
			answer = "NO";	
			//cout << "NAH" << endl;
		}
	}
	
	return answer;		
}

string sprawdzeniePlanszyBlue(int tablicaPlanszy[MAX_N][MAX_M], bool tablicaPlanszy_bool[MAX_N][MAX_M], int board_size, string type_of_test, int r_pawns, int b_pawns)
{
	int wskaznik1;
	int wskaznik2;
	
	int coord_1_pawn1 = 0;
	int coord_2_pawn1 = 0;
	int coord_1_pawn2 = board_size - 1;
	int coord_2_pawn2 = board_size - 1;
	
	int empty_pawn_slots = 0;
	int no_pawns_num = 0;
		
	bool is_board_possible_bool = false;
	bool is_game_over_bool = false;
		
	bool red_win_1_move_naive = false;
	bool blue_win_1_move_naive = false;
	bool red_win_2_moves_naive = false;
	bool blue_win_2_moves_naive = false;
	
	bool pick_no_winning_position = false;

	bool blue_win = false;
	bool is_board_possible = false;	
	bool removed_pawn_bool = false;
	bool start_removing = false;
	bool added_pawn_bool = false;
	bool added_another_pawn_bool = false;	
	bool start_adding = false;
	bool block_one_pawn = false;
	bool last_pawn_placed = false;
	
	bool stopLooping = false;
		
	bool possible_move = false;
	bool temp_block = false;
	
	string answer = "";				
	Wezel *temp;
	int counter = 0;
	
	
	if(type_of_test == "is_board_possible_bool")
	{
		is_board_possible_bool = true;
		removed_pawn_bool = true;
	}
	else if(type_of_test == "is_game_over_bool")
	{
		is_game_over_bool = true;
		removed_pawn_bool = true;	
	}
	else if(type_of_test == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
	{
		red_win_1_move_naive = true;
		added_pawn_bool = true;
		
	}
	else if(type_of_test == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
	{
		blue_win_1_move_naive = true;
		added_pawn_bool = true;
	}	
	else if(type_of_test == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")
	{
		red_win_2_moves_naive = true;
		added_pawn_bool = true;
	
	}
	else if(type_of_test == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")
	{
		blue_win_2_moves_naive = true;
		added_pawn_bool = true;
	}
	else if(type_of_test == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT CHECK NO WIN")
	{						
		red_win_1_move_naive = true;
		pick_no_winning_position = true;
		added_pawn_bool = true;
	}
	else if(type_of_test == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT CHECK NO WIN")
	{						
		blue_win_1_move_naive = true;
		pick_no_winning_position = true;
		added_pawn_bool = true;
	}
	
	empty_pawn_slots = (board_size*board_size)-b_pawns-r_pawns;
	//cout << empty_pawn_slots << endl;	
	
	do
	{
		counter++;
		if(counter == 200)
		{
			//break;
		}
		
		if(is_board_possible_bool == true && start_removing == true && tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] == 2)
		{
			//cout << "USUWA PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
			tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
			//cout << tablicaPlanszy[coord_1_pawn1][coord_2_pawn1];
			removed_pawn_bool = true;
			blue_win = false;
		}
		
		if((blue_win_1_move_naive == true || blue_win_2_moves_naive == true) && start_adding == true)
		{
			if(blue_win_1_move_naive == true || block_one_pawn == false)
			{
				if(tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] == 0)
				{	
					//cout << "DODAJE blue 1-PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
					no_pawns_num++;
					added_pawn_bool = true;
					block_one_pawn = true;	
					
					if(blue_win_2_moves_naive == true)
					{
						stopLooping = true;	
					}
					
					//removed_pawn = tablicaPlanszy[coord_1_pawn1][coord_2_pawn1];
					tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 2;
					//cout << tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] << endl;	
				}
			}				

			if(blue_win_2_moves_naive == true && start_adding == true && block_one_pawn == true)
			{
				if(tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] == 0)
				{	
					//cout << "DODAJE blue ANOTHER-PIONKA" << coord_1_pawn2 << "--" << coord_2_pawn2 << endl;
					added_another_pawn_bool = true;
					added_pawn_bool = false;
					
					if(blue_win_2_moves_naive == true)
					{
						stopLooping = false;	
					}
					
					//removed_pawn = tablicaPlanszy[coord_1_pawn2][coord_2_pawn2];
					tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] = 2;
					//cout << tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] << endl;	
				}	
			}
		}
		
		
			
		if(removed_pawn_bool == true || added_pawn_bool == true || block_one_pawn == true)
		{
			if(stopLooping == false)
			{			
				for(int k = 0; k < board_size; k++)
				{	
					if(tablicaPlanszy[0][k] == 2)
					{
						wskaznik1 = 0;
						wskaznik2 = k;
						Wezel *korzen_blue = new Wezel();
						temp = korzen_blue;
						temp->coord_1 = 0;
						temp->coord_2 = wskaznik2;
						tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
						//cout << "POCZATEK" << endl;
							
						do
						{		
								possible_move = true;
								
								if(temp->coord_1 == board_size - 1)
								{
									if(blue_win_1_move_naive == true && pick_no_winning_position == false || is_board_possible_bool == true || is_game_over_bool == true)
									{
										
										blue_win = true;
										answer = "YES BLUE";
										//cout << "YES BLUE1111" << endl;
									}
									else if(blue_win_1_move_naive == true && pick_no_winning_position == true)
									{
										
									}
									else if(blue_win_2_moves_naive == true && added_another_pawn_bool == true)
									{
										blue_win = true;
										answer = "YES BLUE";
										//cout << "YES BLUE TUTAJ" << endl;
									}
									else if(blue_win_2_moves_naive == true && start_adding == false)
									{
										blue_win = true;
										answer = "YES BLUE";
										//cout << "YES BLUE TUTAJ2" << endl;
									}
								}
								
								//cout << temp->coord_1 << " ";
								//cout << temp->coord_2 << " BLUE" << endl;
								
									if(temp->coord_1 < board_size - 1 && temp_block == false && temp->L_brat == NULL)
									{
										if(tablicaPlanszy[temp->coord_1+1][temp->coord_2] == 2 && tablicaPlanszy_bool[temp->coord_1+1][temp->coord_2] == false)
										{		
											//cout << "DOL" << endl;					
						
											wskaznik1 = wskaznik1 + 1;
												
											Wezel *nowy = new Wezel();
											temp->L_brat = nowy;
											nowy->poprzedni = temp;
											nowy->P_brat = temp;
											nowy->ojciec = temp->ojciec;
											temp = nowy;
											temp->coord_1 = wskaznik1;
											temp->coord_2 = wskaznik2;
				
											//cout << wskaznik1 << " ";
											//cout << wskaznik2 << " C" << endl;
											//cout << temp->coord_1 << " ";
											//cout << temp->coord_2 << " C" << endl;
											//cout << "SYN";
											possible_move = false;
											temp_block = true;
										}
									}
									
									if(temp->coord_2 > 0 && temp_block == false)
									{		
										//cout << tablicaPlanszy[temp->coord_1][temp->coord_2-1] << endl;
										if(tablicaPlanszy[temp->coord_1][temp->coord_2-1] == 2 && tablicaPlanszy_bool[temp->coord_1][temp->coord_2-1] == false)
										{	
											//cout << "LEWO" << endl;
												
											wskaznik2 = wskaznik2 - 1;
												
											Wezel *nowy = new Wezel();
											temp->G_brat = nowy;
											nowy->poprzedni = temp;
											nowy->D_brat = temp;
											nowy->ojciec = temp->ojciec;
											temp = nowy;
											temp->coord_1 = wskaznik1;
											temp->coord_2 = wskaznik2;
												
											//cout << temp->coord_1 << " ";
											//cout << temp->coord_2 << " B" << endl;
												
											possible_move = false;
											temp_block = true;
										}
										
									}
									
									if(temp->coord_2 < board_size - 1 && temp_block == false && temp->D_brat == NULL && temp->syn == NULL)
									{		
										if(tablicaPlanszy[temp->coord_1][temp->coord_2+1] == 2 && tablicaPlanszy_bool[temp->coord_1][temp->coord_2+1] == false)
										{	
											//cout << "PRAWO" << endl;
											
											tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;	
											wskaznik2 = wskaznik2 + 1;
												
											Wezel *nowy = new Wezel();
											temp->syn = nowy;
											nowy->poprzedni = temp;
											nowy->ojciec = temp;
											temp = nowy;
											temp->coord_1 = wskaznik1;
											temp->coord_2 = wskaznik2;
												
											//cout << temp->coord_1 << " ";
											//cout << temp->coord_2 << " B" << endl;
												
											possible_move = false;
											temp_block = true;
										}
										
									}
									
									if(temp->coord_1 < board_size - 1 && temp->coord_2 < board_size - 1 && temp_block == false && temp->D_brat == NULL)
									{
										if(tablicaPlanszy[temp->coord_1+1][temp->coord_2+1] == 2 && tablicaPlanszy_bool[temp->coord_1+1][temp->coord_2+1] == false)
										{
											//cout << "SKOS DOL" << endl;
													
											wskaznik1 = wskaznik1 + 1;
											wskaznik2 = wskaznik2 + 1;
												
											Wezel *nowy = new Wezel();
											temp->D_brat = nowy;
											nowy->poprzedni = temp;
											nowy->G_brat = temp;
											nowy->ojciec = temp->ojciec;
											temp = nowy;
											temp->coord_1 = wskaznik1;
											temp->coord_2 = wskaznik2;
											
											tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
												
											//cout << temp->coord_1 << " ";
											//cout << temp->coord_2 << " D" << endl;
											//cout << "P_BRAT";
												
											possible_move = false;
											temp_block = true;
										}
									}
																
									if(temp->coord_1 > 0 && temp_block == false && temp->P_brat == NULL)
									{
										if(tablicaPlanszy[temp->coord_1-1][temp->coord_2] == 2 && tablicaPlanszy_bool[temp->coord_1-1][temp->coord_2] == false)
										{
											//cout << "GORA" << endl;
											
											tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
											
											wskaznik1 = wskaznik1 - 1;
												
											Wezel *nowy = new Wezel();
											temp->P_brat = nowy;
											nowy->poprzedni = temp;
											nowy->L_brat = temp;
											nowy->ojciec = temp->ojciec;
											temp = nowy;
											temp->coord_1 = wskaznik1;
											temp->coord_2 = wskaznik2;
					
											//cout << temp->coord_1 << " ";
											//cout << temp->coord_2 << " E" << endl;
												
											possible_move = false;
											temp_block = true;
										}
									}
									
									if(temp->coord_1 > 0 && temp_block == false && temp->G_brat == NULL)
									{
										if(tablicaPlanszy[temp->coord_1-1][temp->coord_2-1] == 2 && tablicaPlanszy_bool[temp->coord_1-1][temp->coord_2-1] == false)
										{
											//tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
											if(wskaznik1 - 1 >= 0 && wskaznik2 - 1 >= 0)
											{
												//cout << "SKOS GORA" << endl;
												wskaznik1 = wskaznik1 - 1;
												wskaznik2 = wskaznik2 - 1;
												
												Wezel *nowy = new Wezel();
												temp->G_brat = nowy;
												nowy->poprzedni = temp;
												nowy->D_brat = temp;
												nowy->ojciec = temp->ojciec;
												temp = nowy;
												temp->coord_1 = wskaznik1;
												temp->coord_2 = wskaznik2;
					
												//cout << temp->coord_1 << " ";
												//cout << temp->coord_2 << " E" << endl;
												
												possible_move = false;
												temp_block = true;
											}
										}
									}
							
								if(possible_move == true && temp_block == false)
								{
									//cout << "COFKA" << endl;
									tablicaPlanszy_bool[temp->coord_1][temp->coord_2] = true;
												
									if(temp->poprzedni != NULL)
									{
										temp = temp->poprzedni;
										wskaznik1 = temp->coord_1;
										wskaznik2 = temp->coord_2;		
									}											
								}
					
								temp_block = false;
						
						} while(temp->poprzedni != NULL);
					}				
				}
				
				for(int l = 0; l < board_size; l++)
				{
					for(int m = 0; m < board_size; m++)
					{
						tablicaPlanszy_bool[l][m] = false;
					}	
				}		
			}
			
			if(is_board_possible_bool == true)
			{
				if(blue_win == false && start_removing == false)
				{
					//cout << "TUTAJ3" << endl;
					removed_pawn_bool = false;
					break;		
				}
				else if(blue_win == true && start_removing == false)
				{	
					//cout << "YES RED4" << endl;
					removed_pawn_bool = false;
					answer = "YES BLUE";		
				}
				else if(blue_win == false && start_removing == true)
				{
					//cout << "TUTAJ5" << endl;
					break;
				}		
			}
			else if(blue_win_1_move_naive == true)
			{
				if(blue_win == false && start_adding == false)
				{
					added_pawn_bool = false;
				}
				if(blue_win == true && start_adding == false)
				{
					added_pawn_bool = false;
					
					if(pick_no_winning_position == true)
					{
						answer = "YES BLUE";		
					}
					else
					{
						answer = "NO";		
					}
					
					//cout << "ALREADY WON" << endl;	
					break;
				}
				else if(blue_win == true && start_adding == true)
				{
					if(pick_no_winning_position == true)
					{
						blue_win = false;
						answer = "";
					}
				}
				else if(blue_win == false && start_adding == true && pick_no_winning_position == true)
				{
					added_pawn_bool = false;
					answer = "NO";
				}	
			}
			else if(blue_win_2_moves_naive == true)
			{
				if(blue_win == false && start_adding == false)
				{
					added_pawn_bool = false;
				}
				else if(blue_win == true && start_adding == false)
				{
					added_pawn_bool = false;
					answer = "NO";	
					//cout << "ALREADY WON" << endl;
					break;
				}
				else if(blue_win == true && start_adding == true && added_another_pawn_bool == false)
				{
					added_pawn_bool = false;
					answer = "NO";	
					//cout << "ALREADY WON" << endl;
					//break;
				}
				else if(blue_win == true && start_adding == true && added_another_pawn_bool == true)
				{
					added_pawn_bool = false;
					answer = "YES BLUE";	
					//cout << "ALREADY WON1" << endl;
					//break;
				}	
			}		
		}

		if(removed_pawn_bool == true || added_pawn_bool == true || added_another_pawn_bool == true)
		{
			if(removed_pawn_bool == true && is_board_possible_bool == true)
			{
				//cout << "ZWRACA SWOJEGO BLUE PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
				tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 2;
				removed_pawn_bool = false;	
			}
			else if((added_pawn_bool == true && blue_win_1_move_naive == true) || (block_one_pawn == false && blue_win_2_moves_naive == true))
			{
				//cout << "1-ZWRACA USUNIETEGO PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
				tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
				added_pawn_bool = false;
				last_pawn_placed = false;
			}
			else if(added_another_pawn_bool == true && blue_win_2_moves_naive == true)
			{
				//cout << "1-ZWRACA USUNIETEGO ANOTHERRYYR BLUE PIONKA" << coord_1_pawn2 << "--" << coord_2_pawn2 << endl;
				tablicaPlanszy[coord_1_pawn2][coord_2_pawn2] = 0;
				
				if(blue_win_2_moves_naive == true)
				{
					stopLooping = true;	
				}
					
				added_another_pawn_bool = false;
			}	
		}
		
		if(blue_win_1_move_naive == true || blue_win_2_moves_naive == true)
		{
			if(answer == "YES BLUE" || answer == "NO")
			{
				//cout << answer << "ASNWER" << endl;
				if(block_one_pawn == true)
				{
					tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
					//cout << "1-ZWRACA BLUE PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
					//cout << "tu" << endl;
					break;
				}		
			}	
		}
		
			
			
		if((start_removing == true && is_board_possible_bool == true) || (start_adding == true && blue_win_1_move_naive == true) || (start_adding == true && blue_win_2_moves_naive == true))
		{
			if((start_removing == true && is_board_possible_bool == true) || (start_adding == true && blue_win_1_move_naive == true) || (start_adding == true && blue_win_2_moves_naive == true && block_one_pawn == false))
			{
				if(coord_1_pawn1 <= board_size - 1 && coord_2_pawn1 <= board_size - 1)
				{
					//cout << coord_1_pawn1 << "--" << coord_2_pawn1 << "--PIERWSZY--" << endl;
					if((coord_1_pawn1 < board_size - 1) && (coord_2_pawn1 == board_size - 1))
					{
						coord_1_pawn1++;
						coord_2_pawn1 = 0;
					}
					else if(coord_2_pawn1 < board_size - 1)
					{
						coord_2_pawn1++;
						//cout << coord_1_pawn1 << "--" << coord_2_pawn1 << "--PIERWSZY--" << endl;	
					}
				}
				
				if(blue_win_1_move_naive == true)
				{
					if(coord_1_pawn1 == board_size - 1 && coord_2_pawn1 == board_size - 1)
					{
						//cout << coord_1_pawn1 << "--" << coord_2_pawn1 << "--PIERWSZY--" << endl;
						last_pawn_placed = true;	
					}	
					
					//cout << empty_pawn_slots << " " << no_pawns_num << endl;
					if(empty_pawn_slots == no_pawns_num)
					{
						last_pawn_placed = false;
						
						if(pick_no_winning_position == true)
						{
							answer = "YES BLUE";	
							break;
						}
					}		
				}
				
			}
				
			if(start_adding == true && blue_win_2_moves_naive == true && block_one_pawn == true)
			{	
				//cout << "WESZLO" << endl;
				if(coord_1_pawn2 <= board_size - 1 && coord_2_pawn2 <= board_size - 1)
				{
					//cout << coord_1_pawn2 << "--" << coord_2_pawn2 << "--DRUGI--" << endl;
					if(coord_2_pawn2 == 0)
					{
						if(coord_1_pawn2 == 0)
						{
							//cout << "1-ZWRACA USUNIETEGO PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
							
							if(blue_win_2_moves_naive == true)
							{
								stopLooping = true;	
							}
							
							tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
							block_one_pawn = false;
							coord_1_pawn2 = board_size - 1;
							coord_2_pawn2 = board_size - 1;	
							
							if(coord_2_pawn1 == board_size - 1)
							{	
								coord_1_pawn1++;
								coord_2_pawn1 = 0;
							}
							else
							{
								coord_2_pawn1++;	
							}	
						}
						else
						{
							coord_1_pawn2--;
							coord_2_pawn2 = board_size - 1;	
						}	
					}
					else
					{
						coord_2_pawn2--;	
					}
				}		
			}
		}				
		
		if(is_board_possible_bool == true && start_removing == false)
		{
			//cout << "TUTAJ1" << endl;
			start_removing = true;	
		}
		else if(is_board_possible_bool == true && start_removing == true)
		{
			if(coord_1_pawn1 == board_size - 1 && coord_2_pawn1 == board_size - 1)
			{
				//cout << "TUTAJ2" << endl;
				start_removing = false;	
			}	
		}
		
		if((blue_win_1_move_naive == true && start_adding == false) || (blue_win_2_moves_naive == true && start_adding == false))
		{
			//cout << "TUTAJ1 XDD" << endl;
			start_adding = true;	
		}		
		else if((blue_win_1_move_naive == true && start_adding == true) || (blue_win_2_moves_naive == true && start_adding == true))
		{
			if(coord_1_pawn1 == board_size - 1 && coord_2_pawn1 == board_size - 1)
			{
				if(blue_win_1_move_naive == true && last_pawn_placed == false)
				{
					//cout << "TUTAJ2 XDD1" << endl;
					start_adding = false;	
				}
				if(blue_win_2_moves_naive == true)
				{
					if(coord_1_pawn2 == board_size - 1 && coord_2_pawn2 == board_size - 1)
					{
						//cout << "TUTAJ2 XDD" << endl;
						//cout << "1-ZWRACA USUNIETEGO PIONKA" << coord_1_pawn1 << "--" << coord_2_pawn1 << endl;
						tablicaPlanszy[coord_1_pawn1][coord_2_pawn1] = 0;
						start_adding = false;	
					}
					else
					{
						start_adding = false;		
					}		
				}
			}	
		}
		else if(blue_win_2_moves_naive == true && start_adding == true)
		{
			if(coord_1_pawn2 == board_size - 1 && coord_2_pawn2 == board_size - 1)
			{
				//cout << "TUTAJ25" << endl;
				if(blue_win_2_moves_naive == true)
				{
					block_one_pawn = false;
				}	
			}	
		}
						
	} while(start_removing == true || start_adding == true);
	
	
	if(is_game_over_bool == true)
	{
		if(blue_win == true)
		{
			answer = "YES BLUE";
		}		
	}
	else if(is_board_possible_bool == true)
	{	
		if(answer == "YES BLUE" && r_pawns > b_pawns)
		{
				answer = "NO";	
		}
		else if(blue_win == true)
		{
				answer = "NO";
		}
		else
		{
				answer = "YES";	
		}	
	}
	else if(blue_win_1_move_naive == true)
	{
		if(answer == "YES BLUE")
		{
			answer = "YES";
		}
		else
		{
			answer = "NO";	
		}
	}
	else if(blue_win_2_moves_naive == true)
	{
		if(answer == "YES BLUE")
		{
			answer = "YES";
		}
		else
		{
			answer = "NO";	
			//cout << "TUTAJ";
		}
	}
	
	return answer;
}


int main() 
{
		
	int tablicaPlanszy[MAX_N][MAX_M];
	bool tablicaPlanszy_bool[MAX_N][MAX_M];
	
	int board_size = 10;
	int red_pawns = 0;
	int blue_pawns = 0;
	int no_pawns = 0;
	
	int counter = 0;
	int counter_wins = 0;

	bool is_board_possible_bool = false;
	bool is_game_over_bool = false;
	
	//bool red_win_1_move_naive = true;
	bool red_win_1_move_naive = false;
	
	bool blue_win_1_move_naive = false;
	//bool blue_win_1_move_naive = true;
	
	//bool red_win_2_moves_naive = true;
	bool red_win_2_moves_naive = false;
	
	bool blue_win_2_moves_naive = true;
	//bool blue_win_2_moves_naive = false;
	
	bool checking_win_1_move = false;
	
	bool red_move = false;
	bool blue_move = false;
	
	string type_of_test;
	string resultRed;
	string resultBlue;
	
	bool possible_move = false;
	bool temp_block = false;
	
	tablicaPlanszy[0][0] = 1; tablicaPlanszy[0][1] = 1; tablicaPlanszy[0][2] = 2; tablicaPlanszy[0][3] = 2; tablicaPlanszy[0][4] = 1; tablicaPlanszy[0][5] = 1; tablicaPlanszy[0][6] = 2; tablicaPlanszy[0][7] = 0; tablicaPlanszy[0][8] = 1; tablicaPlanszy[0][9] = 2; tablicaPlanszy[0][10] = 2;
	tablicaPlanszy[1][0] = 2; tablicaPlanszy[1][1] = 2; tablicaPlanszy[1][2] = 1; tablicaPlanszy[1][3] = 2;	tablicaPlanszy[1][4] = 2; tablicaPlanszy[1][5] = 0; tablicaPlanszy[1][6] = 1; tablicaPlanszy[1][7] = 2; tablicaPlanszy[1][8] = 1; tablicaPlanszy[1][9] = 0; tablicaPlanszy[1][10] = 2;
	tablicaPlanszy[2][0] = 2; tablicaPlanszy[2][1] = 2; tablicaPlanszy[2][2] = 2; tablicaPlanszy[2][3] = 1; tablicaPlanszy[2][4] = 2; tablicaPlanszy[2][5] = 2; tablicaPlanszy[2][6] = 0; tablicaPlanszy[2][7] = 1; tablicaPlanszy[2][8] = 1; tablicaPlanszy[2][9] = 2; tablicaPlanszy[2][10] = 2;
	tablicaPlanszy[3][0] = 1; tablicaPlanszy[3][1] = 1; tablicaPlanszy[3][2] = 2; tablicaPlanszy[3][3] = 1; tablicaPlanszy[3][4] = 1; tablicaPlanszy[3][5] = 2; tablicaPlanszy[3][6] = 2; tablicaPlanszy[3][7] = 2; tablicaPlanszy[3][8] = 0; tablicaPlanszy[3][9] = 0; tablicaPlanszy[3][10] = 1;
	tablicaPlanszy[4][0] = 1; tablicaPlanszy[4][1] = 2; tablicaPlanszy[4][2] = 1; tablicaPlanszy[4][3] = 0; tablicaPlanszy[4][4] = 0; tablicaPlanszy[4][5] = 2; tablicaPlanszy[4][6] = 2; tablicaPlanszy[4][7] = 0; tablicaPlanszy[4][8] = 0; tablicaPlanszy[4][9] = 1; tablicaPlanszy[4][10] = 2;
	tablicaPlanszy[5][0] = 2; tablicaPlanszy[5][1] = 2; tablicaPlanszy[5][2] = 2; tablicaPlanszy[5][3] = 0; tablicaPlanszy[5][4] = 2; tablicaPlanszy[5][5] = 0; tablicaPlanszy[5][6] = 2; tablicaPlanszy[5][7] = 1; tablicaPlanszy[5][8] = 0; tablicaPlanszy[5][9] = 1; tablicaPlanszy[5][10] = 1;
	tablicaPlanszy[6][0] = 1; tablicaPlanszy[6][1] = 1; tablicaPlanszy[6][2] = 1; tablicaPlanszy[6][3] = 1; tablicaPlanszy[6][4] = 1; tablicaPlanszy[6][5] = 2; tablicaPlanszy[6][6] = 1; tablicaPlanszy[6][7] = 2; tablicaPlanszy[6][8] = 1; tablicaPlanszy[6][9] = 1; tablicaPlanszy[6][10] = 1;
	tablicaPlanszy[7][0] = 2; tablicaPlanszy[7][1] = 2; tablicaPlanszy[7][2] = 2; tablicaPlanszy[7][3] = 2; tablicaPlanszy[7][4] = 1; tablicaPlanszy[7][5] = 1; tablicaPlanszy[7][6] = 2; tablicaPlanszy[7][7] = 1; tablicaPlanszy[7][8] = 1; tablicaPlanszy[7][9] = 1; tablicaPlanszy[7][10] = 2;
	tablicaPlanszy[8][0] = 2; tablicaPlanszy[8][1] = 1; tablicaPlanszy[8][2] = 2; tablicaPlanszy[8][3] = 1; tablicaPlanszy[8][4] = 1; tablicaPlanszy[8][5] = 1; tablicaPlanszy[8][6] = 2; tablicaPlanszy[8][7] = 1; tablicaPlanszy[8][8] = 0; tablicaPlanszy[8][9] = 1; tablicaPlanszy[8][10] = 1;
	tablicaPlanszy[9][0] = 2; tablicaPlanszy[9][1] = 2; tablicaPlanszy[9][2] = 2; tablicaPlanszy[9][3] = 0; tablicaPlanszy[9][4] = 1; tablicaPlanszy[9][5] = 2; tablicaPlanszy[9][6] = 0; tablicaPlanszy[9][7] = 1; tablicaPlanszy[9][8] = 2; tablicaPlanszy[9][9] = 1; tablicaPlanszy[9][10] = 2;
	tablicaPlanszy[10][0] = 1; tablicaPlanszy[10][1] = 2; tablicaPlanszy[10][2] = 1; tablicaPlanszy[10][3] = 1; tablicaPlanszy[10][4] = 2; tablicaPlanszy[10][5] = 2; tablicaPlanszy[10][6] = 2; tablicaPlanszy[10][7] = 2; tablicaPlanszy[10][8] = 1; tablicaPlanszy[10][9] = 2; tablicaPlanszy[10][10] = 1;
	
	tablicaPlanszy_bool[0][0] = false; tablicaPlanszy_bool[0][1] = false; tablicaPlanszy_bool[0][2] = false; tablicaPlanszy_bool[0][3] = false; tablicaPlanszy_bool[0][4] = false; tablicaPlanszy_bool[0][5] = false; tablicaPlanszy_bool[0][6] = false; tablicaPlanszy_bool[0][7] = false; tablicaPlanszy_bool[0][8] = false; tablicaPlanszy_bool[0][9] = false; tablicaPlanszy_bool[0][10] = false;
	tablicaPlanszy_bool[1][0] = false; tablicaPlanszy_bool[1][1] = false; tablicaPlanszy_bool[1][2] = false; tablicaPlanszy_bool[1][3] = false;	tablicaPlanszy_bool[1][4] = false; tablicaPlanszy_bool[1][5] = false; tablicaPlanszy_bool[1][6] = false; tablicaPlanszy_bool[1][7] = false; tablicaPlanszy_bool[1][8] = false; tablicaPlanszy_bool[1][9] = false; tablicaPlanszy_bool[1][10] = false;
	tablicaPlanszy_bool[2][0] = false; tablicaPlanszy_bool[2][1] = false; tablicaPlanszy_bool[2][2] = false; tablicaPlanszy_bool[2][3] = false; tablicaPlanszy_bool[2][4] = false; tablicaPlanszy_bool[2][5] = false; tablicaPlanszy_bool[2][6] = false; tablicaPlanszy_bool[2][7] = false; tablicaPlanszy_bool[2][8] = false; tablicaPlanszy_bool[2][9] = false; tablicaPlanszy_bool[2][10] = false;
	tablicaPlanszy_bool[3][0] = false; tablicaPlanszy_bool[3][1] = false; tablicaPlanszy_bool[3][2] = false; tablicaPlanszy_bool[3][3] = false; tablicaPlanszy_bool[3][4] = false; tablicaPlanszy_bool[3][5] = false; tablicaPlanszy_bool[3][6] = false; tablicaPlanszy_bool[3][7] = false; tablicaPlanszy_bool[3][8] = false; tablicaPlanszy_bool[3][9] = false; tablicaPlanszy_bool[3][10] = false;
	tablicaPlanszy_bool[4][0] = false; tablicaPlanszy_bool[4][1] = false; tablicaPlanszy_bool[4][2] = false; tablicaPlanszy_bool[4][3] = false; tablicaPlanszy_bool[4][4] = false; tablicaPlanszy_bool[4][5] = false; tablicaPlanszy_bool[4][6] = false; tablicaPlanszy_bool[4][7] = false; tablicaPlanszy_bool[4][8] = false; tablicaPlanszy_bool[4][9] = false; tablicaPlanszy_bool[4][10] = false;
	tablicaPlanszy_bool[5][0] = false; tablicaPlanszy_bool[5][1] = false; tablicaPlanszy_bool[5][2] = false; tablicaPlanszy_bool[5][3] = false; tablicaPlanszy_bool[5][4] = false; tablicaPlanszy_bool[5][5] = false; tablicaPlanszy_bool[5][6] = false; tablicaPlanszy_bool[5][7] = false; tablicaPlanszy_bool[5][8] = false; tablicaPlanszy_bool[5][9] = false; tablicaPlanszy_bool[5][10] = false;
	tablicaPlanszy_bool[6][0] = false; tablicaPlanszy_bool[6][1] = false; tablicaPlanszy_bool[6][2] = false; tablicaPlanszy_bool[6][3] = false; tablicaPlanszy_bool[6][4] = false; tablicaPlanszy_bool[6][5] = false; tablicaPlanszy_bool[6][6] = false; tablicaPlanszy_bool[6][7] = false; tablicaPlanszy_bool[6][8] = false; tablicaPlanszy_bool[6][9] = false; tablicaPlanszy_bool[6][10] = false;
	tablicaPlanszy_bool[7][0] = false; tablicaPlanszy_bool[7][1] = false; tablicaPlanszy_bool[7][2] = false; tablicaPlanszy_bool[7][3] = false; tablicaPlanszy_bool[7][4] = false; tablicaPlanszy_bool[7][5] = false; tablicaPlanszy_bool[7][6] = false; tablicaPlanszy_bool[7][7] = false; tablicaPlanszy_bool[7][8] = false; tablicaPlanszy_bool[7][9] = false; tablicaPlanszy_bool[7][10] = false;
	tablicaPlanszy_bool[8][0] = false; tablicaPlanszy_bool[8][1] = false; tablicaPlanszy_bool[8][2] = false; tablicaPlanszy_bool[8][3] = false; tablicaPlanszy_bool[8][4] = false; tablicaPlanszy_bool[8][5] = false; tablicaPlanszy_bool[8][6] = false; tablicaPlanszy_bool[8][7] = false; tablicaPlanszy_bool[8][8] = false; tablicaPlanszy_bool[8][9] = false; tablicaPlanszy_bool[8][10] = false;
	tablicaPlanszy_bool[9][0] = false; tablicaPlanszy_bool[9][1] = false; tablicaPlanszy_bool[9][2] = false; tablicaPlanszy_bool[9][3] = false; tablicaPlanszy_bool[9][4] = false; tablicaPlanszy_bool[9][5] = false; tablicaPlanszy_bool[9][6] = false; tablicaPlanszy_bool[9][7] = false; tablicaPlanszy_bool[9][8] = false; tablicaPlanszy_bool[9][9] = false; tablicaPlanszy_bool[9][10] = false;
	tablicaPlanszy_bool[10][0] = false; tablicaPlanszy_bool[10][1] = false; tablicaPlanszy_bool[10][2] = false; tablicaPlanszy_bool[10][3] = false; tablicaPlanszy_bool[10][4] = false; tablicaPlanszy_bool[10][5] = false; tablicaPlanszy_bool[10][6] = false; tablicaPlanszy_bool[10][7] = false; tablicaPlanszy_bool[10][8] = false; tablicaPlanszy_bool[10][9] = false; tablicaPlanszy_bool[10][10] = false;
	
	
	if(is_board_possible_bool == true)
	{
		type_of_test = "is_board_possible_bool";	
	}
	else if(is_game_over_bool == true)
	{
		type_of_test = "is_game_over_bool";
	}
	else if(red_win_1_move_naive == true)
	{
		type_of_test = "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
	}
	else if(blue_win_1_move_naive == true)
	{
		type_of_test = "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
	}
	else if(red_win_2_moves_naive == true)
	{
		type_of_test = "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";
	}
	else if(blue_win_2_moves_naive == true)
	{
		type_of_test = "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";
	}
	
		
	//resultRed = sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);
	//resultBlue = sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);	
	
	for(int i = 0; i < board_size; i++)
	{
		for(int j = 0; j < board_size; j++)
		{
			if(tablicaPlanszy[i][j] == 1)
			{
				red_pawns++;
			}
			else if(tablicaPlanszy[i][j] == 2)
			{
				blue_pawns++;	
			}
			else if(tablicaPlanszy[i][j] == 0)
			{
				no_pawns++;
			}
			
			cout << tablicaPlanszy[i][j] << " ";	
		}
		cout << endl;
	}
	cout << endl << endl;
	
	cout << red_pawns << endl;
	cout << blue_pawns << endl;
	cout << no_pawns << endl;
	
	if(red_pawns > blue_pawns)
	{
		blue_move = true;
	}
	else if(red_pawns == blue_pawns)
	{
		red_move = true;	
	}
	
	if(is_game_over_bool == true)
	{
		resultRed = sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);
		resultBlue = sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);
	
		if(resultRed == "YES RED")
		{
			//cout << resultRed << endl;
			printf("%s", "NO");
		}
		else if(resultBlue == "YES BLUE")
		{
			cout << resultBlue << endl;
		}
		else
		{
			//cout << "NO" << endl;
			printf("%s", "NO");	
		}	
	}
	else if(is_board_possible_bool == true)
	{
		resultRed = sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);
		resultBlue = sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);
	
		if(resultRed == "NO" && resultBlue == "NO")
		{
			//cout << "NO" << endl;
			printf("%s", "NO");	
		}
		else if(resultRed == "YES" && resultBlue == "NO")
		{
			//cout << "NO" << endl;	
			printf("%s", "NO");		
		}
		else if(resultRed == "NO" && resultBlue == "YES")
		{
			//cout << "NO" << endl;
			printf("%s", "YES");		
		}
		else
		{
			//cout << "YES" << endl;
			printf("%s", "YES");
		}	
	}
	else if(red_win_1_move_naive == true)
	{	
		if(no_pawns == 0)
		{
			//cout << "NO" << endl;
			printf("%s", "NO");	
		}
		else
		{
			if(red_move == true)
			{
				cout << sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl;
			}
			else if(blue_move == true)
			{
				if(no_pawns > 1)
				{
					cout << sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl;	
				}
				else
				{
					//cout << "NO" << endl;
					printf("%s", "NO");
				}
			}	
		}	
		
	}	
	else if(blue_win_1_move_naive == true)
	{
		if(no_pawns == 0)
		{
			//cout << "NO" << endl;	
			printf("%s", "NO");
		}
		else
		{
			if(blue_move == true)
			{
				cout << sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl;
			}
			else if(red_move == true)
			{
				if(no_pawns > 1)
				{
					cout << sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl;	
				}
				else
				{
					//cout << "NO" << endl;
					printf("%s", "NO");
				}
			}
		}		
			
	}
	else if(red_win_2_moves_naive == true)
	{
		if(no_pawns == 0)
		{
			//cout << "NO" << endl;
			printf("%s", "NO");	
		}
		else
		{
			type_of_test = "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT_CHECK_NO_WIN";
			resultRed = sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);
			type_of_test = "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";	

			if(red_move == true)
			{
				if(no_pawns > 2)
				{
					if(resultRed == "YES")
					{
						//cout << "NO" << endl;
						printf("%s", "NO");
					}
					else
					{
						cout << sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl;		
						//cout << "XD1" << endl;
					}		
				}
				else
				{
					//cout << "NO" << endl;
					printf("%s", "NO");
				}
				
			}
			else if(blue_move == true)
			{
				if(no_pawns > 3)
				{
					if(resultRed == "YES")
					{
						//cout << "NO" << endl;
						printf("%s", "NO");
					}
					else
					{
						cout << sprawdzeniePlanszyRed(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl;
						//cout << "XD" << endl;		
					}			
				}
				else
				{
					//cout << "NO" << endl;
					printf("%s", "NO");
				}
			}	
		}	
	}
	else if(blue_win_2_moves_naive == true)
	{
		if(no_pawns == 0)
		{
			//cout << "NO" << endl;
			printf("%s", "NO");	
		}
		else
		{
			type_of_test = "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT_CHECK_NO_WIN";
			resultBlue = sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns);
			type_of_test = "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";
					
			if(blue_move == true)
			{
				if(no_pawns > 2)
				{
					if(resultBlue == "YES")
					{
						//cout << "NO" << endl << endl;
						printf("%s", "NO");
					}
					else
					{
						cout << sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl << endl;		
					}	
				}
				else
				{
					//cout << "NO" << endl << endl;
					printf("%s", "NO");
				}
				
			}
			else if(red_move == true)
			{
				if(no_pawns > 3)
				{					
					if(resultBlue == "YES")
					{
						//cout << "NO" << endl << endl;
						printf("%s", "NO");
					}
					else
					{
						//cout << "XD" << endl;
						cout << sprawdzeniePlanszyBlue(tablicaPlanszy, tablicaPlanszy_bool, board_size, type_of_test, red_pawns, blue_pawns) << endl << endl;		
					}	
				}
				else
				{
					//cout << "NO" << endl << endl;
					printf("%s", "NO");
				}
			}	
		}	
	}
	
	cout << endl << endl;
	for(int i = 0; i < board_size; i++)
	{
		for(int j = 0; j < board_size; j++)
		{
			//cout << tablicaPlanszy_bool[i][j] << " ";
			//cout << tablicaPlanszy[i][j] << " ";	
		}
		cout << endl;
	}
	
	
		
	return 0;
}
