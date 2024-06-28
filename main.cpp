//main.cpp
#include <iostream>
// #include <stdio.h>
// #include <string>
// #include <numeric>

//function prototypes
void do_first_black_jack_analysis();

float prob_first_card_is_jack(int,int);
float prob_card_is_first_jack(int,int,int);
float prob_team_wins(int,int,int,int);

int get_user_cards();
int get_user_jacks(int);
int get_user_teams();

int main(){
	bool keepgoing = true;
	while (keepgoing){
		std::cout << "What would you like to do?\n";
		std::cout << "1) Analyze a 'First Black Jack' Game.\n";
		std::cout << "0) Quit\n";
		std::string response = "0";
		std::cin >> response;

		if (response.compare("0")==0){
			std::cout << "goodbye";
			keepgoing = false;
		}else if (response.compare("1")==0){
			do_first_black_jack_analysis();
		}else{
			std::cout << "Error: You must type the number for one of the options.\n\n";
		}
	}
}

void do_first_black_jack_analysis(){
	//take user input
	int cards = get_user_cards();
	if (cards==-1){return;}
	int jacks = get_user_jacks(cards);
	if (jacks==-1){return;}
	int teams = get_user_teams();
	if (teams==-1){return;}
	//analyze the game and print the results
	std::cout << "\nIn the game with "<<cards<<" cards, "<<jacks<<" jacks, and "<<teams<<" teams, the probability that each team wins is:\n";
	for (int teamNumber=1;teamNumber<teams+1;teamNumber++){
		float winProb = prob_team_wins(cards,jacks,teams,teamNumber);
		std::cout << "Team "<<teamNumber<<" wins "<<100*winProb<<"% of the time.\n";
	}
	std::cout<<"\n";
}

//!!!For efficiency, should save results in a global table
float prob_first_card_is_jack(int cards,int jacks){
	return ((float)jacks/cards);
}
float prob_card_is_first_jack(int cards,int jacks,int cardNumber){//cardNumber>=1
	if (jacks>cards-(cardNumber-1)){
		return 0;
	}
	float coefficient = 1.0;
	if (cardNumber>1){
		for (int index=0;index<cardNumber-1;index++){
			coefficient*=1-prob_first_card_is_jack(cards-index,jacks);
		}
	}
	// std::cout<<"prob for cardNumber "<<cardNumber<<" is: "<<coefficient*prob_first_card_is_jack(cards-(cardNumber-1),jacks)<<"\n";
	return coefficient*prob_first_card_is_jack(cards-(cardNumber-1),jacks);
}
float prob_team_wins(int cards,int jacks,int teams,int teamNumber){//teamNumber>=1
	//find number of cards this team gets in this game
	int cardsForTeam = cards/teams;//!!!Verify this is right
	int remainder = cards%teams;
	if (remainder>=teamNumber){
		cardsForTeam++;
	}
	if (cardsForTeam==0){
		return 0.0;
	}
	//add the probability of any one of their cards being the first black jack
	float totalProb = 0.0;
	for (int index=0;index<cardsForTeam;index++){
		int cardNumber = teamNumber+index*teams;
		totalProb+=prob_card_is_first_jack(cards,jacks,cardNumber);
	}
	return totalProb;
}
//user input functions
int get_user_cards(){
	//ask user for number of cards
	int cards;
	std::cout << "Enter the total number of cards in the deck: ";
	std::cin >> cards;
	if (std::cin.fail()){
		std::cout<<"Error: Your deck must have an integer number of cards.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (cards<1){
		std::cout << "Error: Your deck must have at least 1 card.\n\n";
		return -1;
	}
	return cards;
}
int get_user_jacks(int cards){
	//ask user for number of jacks
	int jacks;
	std::cout << "Enter the number of jacks (winning cards) in the deck: ";
	std::cin >> jacks;
	if (std::cin.fail()){
		std::cout<<"Error: Your deck must have an integer number of winning cards.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (jacks<1){
		std::cout << "Error: Your deck must have at least 1 jack.\n\n";
		return -1;
	}
	if (jacks>cards){
		std::cout << "Error: You cannot have more jacks than cards.\n\n";
		return -1;
	}
	return jacks;
}
int get_user_teams(){
	//ask user for number of teams
	int teams;
	std::cout << "Enter the number of teams: ";
	std::cin >> teams;
	if (std::cin.fail()){
		std::cout<<"Error: You must have an integer number of teams.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (teams<1){
		std::cout << "Error: You must have at least 1 team.\n\n";
		return -1;
	}
	return teams;
}
