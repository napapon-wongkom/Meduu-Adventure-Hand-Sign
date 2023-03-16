#include "buffskill.h"
  
int main(){
	srand(time(0));
	
	string name;	
	cout << "Please input your name: ";
	getline(cin,name);	
	Unit hero("Hero",name);
	
	Equipment buff1(2,2,4);
	Equipment buff2(4,4,8);
    Equipment buff3(8,8,16);
	Equipment buff4(16,16,32);


	
	char eq;	
	cout << " [1] buff1 \n [2] buff2 \n [3] buff3 \n [4] buff4 \n";
	cout << "Please selet your buff: ";
	cin >> eq;
    if(eq == '1') hero.equip(&buff1);
	if(eq == '2') hero.equip(&buff2);
	if(eq == '3') hero.equip(&buff3);
	if(eq == '4') hero.equip(&buff4);
	
	Unit mons("Monster","Kraken");
	
	int turn_count = 1;
	char player_action = '\0',monster_action = '\0';
	int p = 0, m = 0;
	while(true){
		mons.newTurn();	
		hero.newTurn();			
		mons.showStatus();
		drawScene(player_action,p,monster_action,m);
		hero.showStatus();		
		cout << "[A] Attack [H] HEAL [G] Guard [D] Dodge [B] Buff [C] Change Equipment [L] LIFE DRAIN  [E] Exit";
		cout << "\n[Turn " << turn_count << "] Enter your action: ";
		cin >> player_action;
		player_action = toupper(player_action);
		if(player_action == 'E') break; 
		
		int temp = rand()%5;
		if(temp <= 1) monster_action = 'A';
		else if(temp == 2) monster_action = 'G';
		else if(temp == 3) monster_action = 'D';
		else if(temp == 4) monster_action = 'U';
		
		if(player_action == 'G') hero.guard();
		if(monster_action == 'G') mons.guard();
		
		if(player_action == 'D') hero.dodge();
		if(monster_action == 'D') mons.dodge();
		
		if(player_action == 'B') p = hero.buff();
		if(player_action == 'H') p = hero.heal();
		
		
		if(player_action == 'C'){
			char eq;	
			cout << " [1] buff1 \n [2] buff2 \n [3] buff3 \n [4] buff4 \n";
			cout << "Please select your buff: ";
			cin >> eq;
			if(eq == '1') hero.equip(&buff1);
	        if(eq == '2') hero.equip(&buff2);
        	if(eq == '3') hero.equip(&buff3);
        	if(eq == '4') hero.equip(&buff4);
		}
		
		if(player_action == 'A') p = hero.attack(mons);
		if(player_action == 'L') p = hero.life_drain(mons);
		if(monster_action == 'A') m = mons.attack(hero); 
		if(monster_action == 'U') m = mons.ultimateAttack(hero); 
		
		if(hero.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerLose();
			break; 
		}
		
		if(mons.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerWin();
			break; 
		}
		
		turn_count++;
	}
	return 0;
}