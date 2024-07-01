//main.cpp
#include <iostream>

//function prototypes
void do_first_black_jack_analysis();
float prob_first_card_is_jack(int,int);
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
	return 0;
}

void do_first_black_jack_analysis(){
	//take user input
	int cards = get_user_cards();
	if (cards==-1){return;}
	int jacks = get_user_jacks(cards);
	if (jacks==-1){return;}
	int teams = get_user_teams();
	if (teams==-1){return;}
	//analyze the game
	float teamWinProbs[teams] = {0.0};
	int teamNumber = 0;
	float coefficient = 1.0;
	float prevP = 0.0;//stores value of prob_first_card_is_jack in last for loop travel
	//go through each card and add the probability that it is the first black jack to the win probability to the relavant team
	for (int cardNumber=1;cardNumber<cards+1;cardNumber++){
		//if there is more than one black jack, then the final card cannot be the first black jack.
		if (jacks>cards-(cardNumber-1)){
			break;
		}
		//update teamNumber for this card
		teamNumber = (cardNumber%teams);
		if (teamNumber==0){
			teamNumber=teams;
		}
		//calculate the new coefficient
		coefficient*=1-prevP;
		//calculate newProb;
		float newP = prob_first_card_is_jack(cards-(cardNumber-1),jacks);
		//calculate prob this card is first black jack
		float probFirstJack = coefficient*newP;
		teamWinProbs[teamNumber-1] += probFirstJack;
		//update prevProb
		prevP = newP;
	}
	//print the results
	std::cout << "\nIn the game with "<<cards<<" cards, "<<jacks<<" black jacks, and "<<teams<<" teams, the probability that each team wins is:\n";
	for (int teamNumber=1;teamNumber<teams+1;teamNumber++){
		float winProb = teamWinProbs[teamNumber-1];
		std::cout << "Team "<<teamNumber<<" wins "<<100*winProb<<"% of the time.\n";
	}
	std::cout<<"\n";
}
float prob_first_card_is_jack(int cards,int jacks){
	return ((float)jacks/cards);
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
	//'jacks' and 'black jacks' here means winning cards. AKA, the cards that have the team who turn them up win the game
	//ask user for number of black jacks
	int jacks;
	std::cout << "Enter the number of black jacks in the deck: ";
	std::cin >> jacks;
	if (std::cin.fail()){
		std::cout<<"Error: Your deck must have an integer number of black jacks.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (jacks<1){
		std::cout << "Error: Your deck must have at least 1 black jack.\n\n";
		return -1;
	}
	if (jacks>cards){
		std::cout << "Error: You cannot have more black jacks than total cards in the deck.\n\n";
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
