#include <iostream>
#include<fstream>
#include <stdlib.h>  
#include<time.h>
#include<Windows.h>
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

class player {
	int money;
	int loc;//loction
	int owned_houses;
	int owned_hotels;
	bool get_out_of_jail;
	bool bankrupt;
	bool skip_turns;
	int skip = 0;
	int index = 0;
	int oland[28];
	bool end;
	bool getoutjail;
	

	int ID;
public:
	int osize;
	void set_oooland(int prix) {
		int temp;
		for (int i = 0; i < 28; i++) {
			if (i == prix) {
				oland[i] = 0;
		}
			for (int i = 0; i < 28; i++) {
				for (int j = 0; j < 28; j++) {
					if (oland[i] < oland[j])
					{
						temp = oland[i];
						oland[i] = oland[j];
						oland[j] = temp;
                     }
					
				}
			}
		}
		osize--;
	}
	
	player()
	{
		end = false;
		bankrupt = false;
		money = 5000;
		loc = 1;
		owned_houses = 0;
		owned_hotels = 0;
		skip_turns = false;
		get_out_of_jail = true;
		for (int i = 0; i < 28; i++)
		{
			oland[i] = 0;
		}
		osize = 0;
	}
	int *get_oland()
	{
		osize = osize + 1;
		return &oland[osize - 1];
	}
	void setid(int id) {
		ID = id;
	}
	int getid(int id) {
		return ID;
	}
	void setend() {
		end = true;
	}
	bool getend() {
		return end;
	}
	void incplpro(int ix) {
		oland[index] = ix;
		index++;
	}
	////////////////motrgage needs to be done	
	void decmoney(int mon) {
		money = money - mon;
	}
	void incmoney(int mone) {
		
		set_money(money+mone);
	}
	void set_money(int m)
	{
		money = m;
	}
	int get_money()
	{
		return money;
	}
	void set_location(int l)
	{
		loc = l;
	}
	int get_location() const
	{
		return loc;
	}
	void set_owned_house(int h)
	{
		owned_houses = h;
	}
	int get_owned_house()
	{
		return owned_houses;
	}
	void set_owned_hotel(int h)
	{
		owned_hotels = h;
	}
	int get_owned_hotel()
	{
		return owned_hotels;
	}
	void setskip(bool skipt) {
		skip_turns = skipt;
		if (skip_turns == true)
			skip++;
	}
	bool getskipturns() {
		return skip_turns;
	}
	int getskip() {
		return skip;
	}
	int incskip() {
		if (skip == 2) {
			skip = 0;
			skip_turns = false;
		}
		else {
			skip++;
		}
		return skip;
	}
	bool getjailcard() {
		return getoutjail;
	}
	void setjailcard(bool option) {
		getoutjail = option;
	}


	bool check_whteher_card_is_communitychest_or_chance()
	{


		if (loc >= 33 && loc <= 35)
		{
			return true;
		}

		if (loc >= 36 && loc <= 38)
		{
			return false;
		}

	}

	int pick_up_special_card()
	{
		int temp;
		srand(time(NULL));

		bool b = check_whteher_card_is_communitychest_or_chance();

		if (b == true)
		{

			ifstream fin("CommunityChest.txt");
			int i = 0;
			if (!fin)
			{
				cout << "error" << endl;
			}
			else
			{
				i = 14;
			}
			int a = rand() % i + 0;
			temp = show_card(a, b);
			//if coomunity chest
			return temp;
		}

		else if (b == false)
		{

			ifstream fin("Chance.txt");
			int i = 0;
			if (!fin)
			{
				cout << "error" << endl;
			}
			else
			{
				i = 14;
			}


			fin.close();
			int a = rand() % i + 0;
			show_card(a, b);
		}
	}
	bool checkbankrupt() {
		bool below;
		if (money < 0) {
			bankrupt = true;
		}
		return bankrupt;
	}
	int show_card(int no, bool sc)

	{
		int i = 0;
		int ret = 0;
		char str[170][170];
		bool var = true;
		if (sc == true)
		{
			ifstream fin("CommunityChest.txt");

			while (i <= no && var == true)
			{
				fin.getline(str[i], 150);

				if (i == no)
				{
					cout << endl << str[i] << endl;
					var = false;
				}
				if (i != no)
				{
					i++;

				}

			}
			cout << i;
			if (i == 0)
			{
				loc = 1;//advance to go
				money = money + 300;
				cout << "Player advances to location: " << loc << endl;
				cout << "Total money: " << money << endl;
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 1)
			{
				money = money + 200;//bank will pay
				cout << "Player's total money increased by 200." << endl;
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 2)
			{
				cout << "Player's total money decreased by 200 duu to paying doctor's fee." << endl;
				money = money - 200;//pay doctor fee
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 3)
			{
				cout << "Player has earned Rs.50 from sale." << endl;
				money = money + 50;//money get from sale
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 4)
			{
				char ch;
				skip_turns = false;
				get_out_of_jail = true;
				cout << "do you want to keep the card until needed? Enter y if you want to or if you want to sold it for 500 enter n" << endl;
				cin >> ch;
				if (ch == 'n') {
					money = money + 500;
					get_out_of_jail = false;
				}
				else {
					system("Pause");
				}
				//Get out of Jail.May be kept until needed or sold for 500 PKR.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 5)
			{
				cout << "Player has collected Rs.150 due to income tax refund." << endl;
				money = money + 150;
				//Income Tax refund collect 150 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 6)
			{
				cout << "Player's health insureance has matured, and he has earned Rs.200 ." << endl;
				money = money + 200;
				//Your health insurance matures collect 200 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 7)
			{
				cout << "Player has donated Rs.100 to hospital." << endl;
				money = money - 100;
				//Pay donation to Hospital 100 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 8)
			{
				cout << "Player's tatal money has decreased by Rs.200 due to student tax" << endl;
				money = money - 200;
				//Pay Student tax of 200 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 9)
			{
				cout << "Player has earned Rs.50 for his outstanding services." << endl;
				money = money + 50;
				//Collect 50 PKR for your services.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 10)
			{
				int total = 0;
				total = get_owned_house() * 50 + get_owned_hotel() * 125;
				decmoney(total);
				cout << "Total money of player as decreased due to street repair." << endl;
				//	Pay Street repair charges 50 PKR per House 125 PKR per Hotel.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 11)
			{
				cout << "Player has won rs.300 from prize money." << endl;
				money = money + 300;
				//You won prize money of 300 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 12)
			{
				cout << "Player is paying water bill of Rs.50." << endl;
				money = money - 50;
				//Pay water bill of 50 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 13)
			{
				cout << "Player is paying electricity bill of Rs80." << endl;
				money = money - 80;
				//Pay electricity bill of 80 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 14)
			{
				cout << "Player is paying internet bill of Rs.50" << endl;
				money = money - 50;
				//Pay internet bill 50 PKR
				cout << endl << endl << endl << endl;
				output();
			}

			fin.close();
		}
		else
		{
			ifstream fin("Chance.txt");

			while (i <= no&&var == true)
			{
				fin.getline(str[i], 150);
				if (i == no)
				{
					cout << str[i] << endl;
					var = false;
				}
				else if (i != no)
				{
					i++;
				}
			}
			cout << i;
			if (i == 0)
			{
				cout << "Player has advanced to go and collected Rs.300" << endl;
				loc = 0;//advance to go
				money = money + 300;
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 1)
			{
				cout << "Player has advanced to DHA Phase I." << endl;
				set_location(15);//Advance to DHA Phase 1.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 2)
			{
				cout << "Player has advanced to the nearest utility.If the utility is owned, he will pay 5 times the amount shown on dice." << endl;
				set_location(32);
				ret = 2;
				//Advance token to nearest utility. If unowned by from Bank. If owned, pay to owner 5X the amount shown on dice.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 3)
			{
				cout << "Player has advanced to the nearest station. If the utility is owned, he will twice the pruchase price of property." << endl;

				set_location(27);
				ret = 3;
				//Advance token to nearest Station. If unowned buy from Bank. If owned, pay to owner the double amount
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 4)
			{
				cout << "Player has advanced to the nearest station. If the utility is owned, he will twice the pruchase price of property." << endl;
				set_location(27);
				ret = 3;
				//	Advance token to nearest Station.If unowned by from Bank.If owned, pay to owner the double amount.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 5)
			{
				loc = 9;
				cout << "Player has advanced to Model Town I and collected Rs.300." << endl;
				money = money + 300;

				//Advance to Model Town 1. If you pass Go collect 300 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 6)
			{
				cout << "Player has been given Rs.100." << endl;
				money = money + 100;//Bank pay you 100 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 7)
			{
				char ch;
				skip_turns = false;
				get_out_of_jail = true;
				cout << "do you want to keep the card until needed? Enter y if you want to or if you want to sold it for 500 enter n" << endl;
				cin >> ch;
				if (ch == 'n') {
					money = money + 500;
					get_out_of_jail = false;
				}
				else {
					system("Pause");
				}
				//Get out of Jail.May be kept until needed or sold for 500 PKR.}
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 8)
			{
				if (loc - 4 >= 0)
				{
					loc = loc - 4;
				}
				else
				{
					int loca = loc - 4;
					loc = 40 + loca;
					//Go back 4 blocks.
					cout << "Player has gone back 4 blocks." << endl;
					cout << endl << endl << endl << endl;
					output();
				}
			}
			if (i == 9)
			{
				//Make repair on your property. For each house pay 50 PKR For each hotel pay 100 PKR
				int total = 0;
				total = get_owned_house() * 50 + get_owned_hotel() * 125;
				decmoney(total);
				cout << "Player has to pay repair costs for his properties." << endl;
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 10)
			{
				cout << "Player has to pay a small tax of Rs.25" << endl;
				money = money - 25;
				//Pay small Tax of 25 PKR
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 11)
			{
				ret = 11;
				//that will take
				cout << "Player has been elected to be the chairperson, he now has to give each other players Rs.25." << endl;
				//	You have been elected as chairperson.Pay 25 PKR to each player.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 12)
			{
				cout << "Player has collected Rs.150." << endl;
				money = money + 150;
				//Collect 150 PKR from the Bank.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 13)
			{
				cout << "There is no property concerning the airport." << endl;
				//Advance to Airport and not pay any Tax there.
				cout << endl << endl << endl << endl;
				output();
			}
			if (i == 14)
			{
				cout << "Player has advanced to Metro Station." << endl;
				set_location(24);
				//Advance token to Metro Station.
				cout << endl << endl << endl << endl;
				output();
			}


		}
		return ret;
	}
	void output()
	{
		cout << "player money is " << money << " on location " << loc << " has owned houses " << owned_houses << " and hotels " << owned_hotels << endl;
		cout << "player have following property IDs : ";
		for (int i = 0; i < osize; i++) {
			cout << oland[i] << " ";
		}


		cout << endl;
	}

};
class bank {
	int bank_owned_properties;
	int bank_houses;
	int bank_shops;
	int bank_hotels;
	int bank_owned_location_size;
	int bank_mortgaged_location_size;
	int bank_sold_location_size;
	int bank_owned_locations[28];
	int bank_mortgaged_locations[28];
	int bank_sold_locations[28];
	int bank_mortgaged_properties;
	int bank_sold_properties;
public:
	bank() {
		bank_owned_properties = 28;
		bank_houses = 100;
		bank_shops = 100;
		bank_owned_location_size = 28;
		int i = 0, k = 0;
		k = i;
		for (i = 0; i<bank_owned_location_size; i++) {
			if (i == 0) {
				k = k + 2;
				bank_owned_locations[i] = k;
				k = k + 1;
			}
			else if (i == 9 || i == 18 || i == 27) {
				//		cout<<"i%10 = "<<i<<endl;
				//		system("pause");
				k = k + 1;
				//	cout<<"k%10 = "<<k<<endl;
				//		system("pause");
				bank_owned_locations[i] = k;
				k = k + 1;
			}
			else {
				//	cout<<"i   = "<<i<<endl;
				//		system("pause");
				//	cout<<"k   = "<<k<<endl;
				//		system("pause");
				bank_owned_locations[i] = k;
				k = k + 1;
			}
		}
		bank_mortgaged_location_size = 28;
		for (int i = 0; i< bank_mortgaged_location_size; i++) {
			bank_mortgaged_locations[i] = 0;
		}
		bank_sold_location_size = 28;
		for (int i = 0; i< bank_sold_location_size; i++) {
			bank_sold_locations[i] = 0;
		}
		bank_mortgaged_properties = 0;
		bank_sold_properties = 0;
	}
	void sell_location(int location) {
		bool check = true;
		for (int i = 0; i< bank_mortgaged_location_size && check == true; i++) {
			if (bank_mortgaged_locations[i] == location) {
				check = false;
			}
		}
		if (check == false) {
			cout << "This property is mortgaged already by bank you cannot //buy it . " << endl << endl;
		}
		else {
			bool check1 = true;
			for (int i = 0; i<bank_sold_location_size && check1 == true; i++)
			{
				if (bank_sold_locations[i] == location) {
					check1 = false;
				}
			}
			if (check1 == false) {
				cout << "The property you want to //buy is already bought by someone . You better try nextime. " << endl << endl;
			}
			else {
				int temp = 0;
				bool check3 = true;
				for (int i = 0; i<bank_owned_location_size && check3 == true; i++) {
					if (bank_owned_locations[i] == location) {
						check3 = false;
						for (int k = i; i<(bank_owned_location_size - 1); k++) {
							temp = bank_owned_locations[k];
							bank_owned_locations[k] = bank_owned_locations[k + 1];
							bank_owned_locations[k + 1] = temp;
						}
						bank_owned_location_size = bank_owned_location_size - 1;
					}
				}
			}
		}
	}
	int get_bank_owned_properties() {
		return bank_owned_properties;
	}
	int get_bank_houses() {
		return bank_houses;
	}                                                              	//	int bank_owned_properties;
	int get_bank_shops() {
		return bank_houses;
	}
	int get_bank_hotels() {
		return bank_hotels;
	}	                                                                                //int bank_houses;	int get_bank_owned_locations_size() {		return bank_owned_location_size;
																						//  int bank_shops;
	int get_bank_mortgaged_locations_size() {
		return bank_mortgaged_location_size;
	}	                                                                             //   int bank_hotels;
	int get_bank_sold_locations_size() {
		return bank_sold_location_size;
	}                                                              //      int bank_owned_location_size;
	int get_bank_mortgaged_properties() {
		return bank_mortgaged_properties;
	}
	int get_bank_sold_properties() {
		return bank_sold_properties;
	}				                                                              //   int bank_mortgaged_location_size;
	int * get_bank_owned_locations() {
		return bank_owned_locations;
	}
	int * get_bank_mortgaged_locations() {
		return bank_mortgaged_locations;
	}				                                                                   // int bank_sold_location_size;
	int * get_bank_sold_locations() {
		return bank_sold_locations;
	}                                                              //            int bank_owned_location[28];
																   //																   //  int bank_mortgaged_locations[28];
																   //																   //int bank_sold_locations[28];
																   //																   //int bank_mortgaged_properties;
																   //																   // int banK_sold_properties;
};
class property{
private:
	int oid;//owner od
	int pid;//property id
	int gid;//group id
	int purchaseprice;
	int rent;
	int nhouses;//number of houses
	int nhotels;//number of hotels
	int nshops;//number of shops

	bool upgradable = false;
	bool buy = true;		   //bool ////upgradable;
							   //bool //buy;//can be baught or not?
							   //bool //property_type;
	bool mortgage;
	bool owned;
public:
	property() {
	}
	property(int i) {
		oid = -1;
		pid = i;
		if (i > 1 && i < 5) {
			gid = 1;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			if (i == 2) {
				purchaseprice = 250;
				rent = 60;
			}
			else if (i == 3) {
				purchaseprice = 200;
				rent = 70;
			}
			else if (i == 4) {
				purchaseprice = 400;
				rent = 100;
			}
		}
		else if (i > 4 && i < 7) {
			gid = 2;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			if (i == 5) {
				purchaseprice = 200;
				rent = 80;
			}
			else if (i == 6) {
				purchaseprice = 250;
				rent = 90;
			}
		}
		else if (i > 6 && i < 10) {
			gid = 3;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			if (i == 7) {
				purchaseprice = 300;
				rent = 100;
			}
			else if (i == 8) {
				purchaseprice = 400;
				rent = 130;
			}
			else if (i == 9) {
				purchaseprice = 400;
				rent = 130;
			}
		}
		else if (i == 10) {
			gid = 4;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			purchaseprice = 800;
			rent = 200;;
		}
		else if (i > 11 && i < 14) {
			gid = 4;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			if (i == 12) {
				purchaseprice = 850;
				rent = rent = 250;
			}if (i == 13) {
				purchaseprice = 2000;
				rent = 500;
			}
		}
		else if (i > 13 && i < 17) {
			gid = 5;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			if (i == 14) {
				purchaseprice = 1000;
				rent = 300;
			}
			else if (i == 15) {
				purchaseprice = 1200;
				rent = 350;
			}
			else if (i == 16) {
				purchaseprice = 2500;
				rent = 600;
			}
		}
		else if (i > 16 && i < 20) {
			gid = 6;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			if (i == 17) {
				purchaseprice = 2000;
				rent = 500;
			}
			else if (i == 18) {
				purchaseprice = 2000;
				rent = 500;
			}
			else if (i == 19) {
				purchaseprice = 2500;
				rent = 1000;
			}
		}
		else if (i == 20) {
			gid = 7;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			//buy = true;//can be baught
			////upgradable = true;
			purchaseprice = 2500;
			rent = 800;
		}
		else if (i > 21 && i < 24) {
			gid = 7;
			nhouses = 0; nshops = 0; nhotels = 0;
			//property_type = false;
			owned = false;
			if (i == 22) {
				purchaseprice = 3000;
				rent = 900;
			}
			else if (i == 23) {
				purchaseprice = 3000;
				rent = 1000;
			}
		}

	}
	virtual void bought(bool b, int o, property p) {//b is if player //buying it or not,p is property id
		int pi = p.getp();
		if (pi != 1 && pi != 11 && pi != 21 && pi != 31) {
			if (pi < 33) {
				owned = true;
				oid = o;
				cout << "Property number: " << pi << " is baught by player: " << o << endl;
			}
		}
	}

	virtual int getpp()const {
		return purchaseprice;
	}
	virtual int getr()const {
		return rent;
	}
	virtual int geto()const {
		return oid;
	}
	virtual int getp()const {
		return pid;
	}
	virtual int getg()const {
		return gid;
	}
	virtual bool getm()const {
		return mortgage;
	}
	virtual void prt() {
		cout << "Property ID: " << pid << endl;
		if (owned != true) {
			cout << "Purchase Price: " << purchaseprice << endl;
		}
		else {
			cout << "Owner ID: " << oid << endl;
			cout << "Rent: " << rent << endl;
			cout << "Number of houses: " << nhouses << endl;
			cout << "Number of hotels: " << nhotels << endl;
			cout << "Number of shops: " << nshops << endl;

		}
	}

	virtual bool getbuy()const {
		return buy;
	}
	virtual bool getupgrade() {
		return upgradable;
	}
	virtual bool getown()const {
		return owned;
	}
	virtual void setm() {
		mortgage = true;
	}
	virtual void setn(int condition) {
		if (condition == 1) {
			nhouses++;
		}
		else if (condition == 2) {
			nhotels++;
		}
		else if (condition == 3) {
			nshops++;
		}
	}
	virtual void setoid(int id) {
		oid = id;
	}
	virtual void setown(bool own) {
		owned = own;
	}
};

class unupgrade :public property{
	int oid;//owner od
	int pid;//property id
	int gid;//group id
	int purchaseprice;
	int rent;
	bool mortgage;
	bool buy = true;
	bool upgradable = false;
	bool owned;
public:
	unupgrade(int i) {
		pid = i;
		if (i > 23 && i < 28) {
			gid = 8;
			//property_type = true;
			owned = false;
			buy = true;//can be baught
					   //upgradable = false;
			if (i == 24 || i == 25) {
				purchaseprice = 2000;
				rent = 200;
			}
			else if (i == 26 || i == 27) {
				purchaseprice = 2500;
				rent = 350;
			}
		}
		else if (i > 27 && i < 31) {
			gid = 9;
			//property_type = true;
			owned = false;
			buy = true;//can be baught
					   //upgradable = false;
			if (i == 28) {
				purchaseprice = 4000;
				rent = 400;
			}
			else if (i == 29) {
				purchaseprice = 5000;
				rent = 450;
			}
			else if (i == 30) {
				purchaseprice = 8000;
				rent = 500;
			}
		}
		else if (i == 32) {
			gid = 9;
			//property_type = true;
			owned = false;
			buy = true;//can be baught
					   ////upgradable = false;
			purchaseprice = 2500;
			rent = 350;
		}
	}
	virtual void prt() {
		if (owned != true) {
			cout << "Purchase Price: " << purchaseprice << endl;
			cout << "Property ID: " << pid << endl;

		}
		else {
			cout << "Owner ID: " << oid << endl;
			cout << "Property ID: " << pid << endl;
			cout << "Group ID: " << gid << endl;
			cout << "Rent: " << rent << endl;
		}
	}
	virtual bool getupgrade() {
		return upgradable;
	}
	bool getbuy()const {
		return buy;
	}
	virtual int getpp()const {
		return purchaseprice;
	}
	int getr()const {
		return rent;
	}
	virtual int geto()const {
		return oid;
	}
	virtual int getp()const {
		return pid;
	}
	virtual int getg()const {
		return gid;
	}
	virtual bool getm()const {
		return mortgage;
	}
	virtual bool getown()const {
		return owned;
	}
	virtual void setm() {
		mortgage = true;
	}

};



class unbuy :public property{
	int pid;//property id
	bool buy = false;//can be baught or not?
public:
	unbuy(int i) {
		pid = i;
		if (i == 1 || i == 11 || i == 21 || i == 31 || i>32) {
			buy = false;//cannot be baught
		}
	}
	virtual void prt() {
		cout << "Property ID: " << pid << endl;
	}
	virtual int getp()const {
		return pid;
	}
	bool getbuy()const {
		return buy;
	}
};




///////////////////////GAME/////////////////////
class game {
	property **board;
	player **p;
public:
	game() {}
	int psize;
	int temp;
	game(int pnum) {
		int j;
		board = new property*[41];
		for (int i = 1; i < 41; i++) {
			j = i;
			if (j == 1 || j == 11 || j == 21 || j == 31 || j > 32) {
				board[i] = new unbuy(j);
			}
			else if (j > 23 && j < 31) {
				board[i] = new unupgrade(j);
			}
			else if (j == 32) {
				board[i] = new unupgrade(j);

			}
			else {
				board[i] = new property(j);
			}
		}
		psize = pnum;
		p = new player*[psize];
		for (int i = 0; i < psize; i++) {
			p[i] = new player();
		}
	}
	int *get_olannd(int pID)
	{
		return p[pID]->get_oland();

	}
	int loop(int prix, int dice, int pix) {
		int ret = prix + dice;
		if (ret > 40) {
			ret = ret - 40;
			p[pix]->incmoney(500);
		}
		return ret;
	}

	void setplayerlocation(int ix, int pID) {
		p[pID]->set_location(ix);
	}
	int getplayerlocation(int ix)const {
		//	cout<<"at player index = "<<ix<<endl<<endl;
		//	cout<<"  p[ix]->get_location() = "<<p[ix]->get_location()<<endl<<endl;
		//	system("pause");
		return p[ix]->get_location();
	}
	bool checkown(int ix) {
		return board[ix]->getown();
	}
	bool buyable(int ix) {
		return board[ix]->getbuy();
	}
	bool getupgrade(int ix) {
		return board[ix]->getupgrade();
	}
	int auction(int prix, int &large) {
		int val;
		int max = 0, larp = 0;
		for (int i = 0; i < psize; i++) {
			cout << "Player " << i + 1 << ",enter the amount you want to bid for the location" << endl;
			cin >> val;
			if (val > max) {
				max = val; larp = i;
			}
		}
		large = larp;
		return max;
	}
	void sell_to_bank(int pix, int pid)
	{
		char ch;
		cout << "do you want to sell your property " << endl;
		cout << "enter  y else n" << endl;
		cin >> ch;
		if (ch == 'y')
		{

			int price = board[pid]->getpp();
			p[pix]->incmoney(price);
			board[pid]->setoid(0);
			board[pid]->setown(false);
			p[pix]->set_oooland(pid);
		}

	}
	/*void upgrade(int pID) {
	int *pd=get_olannd(pID);
	for (int i = 0; i <p[pID]->osize; i++)
	{

	}
	}*/
	void action(int pix, int prix, int dice) {
		bool buy = buyable(prix);
		bool upgrade;
		bool on;
		int mon;
		int id, price;
		int loop;
		int choice;
		bool jailcard;

		if (buy == false) {
			if (prix == 11) {
				system("cls");
				cout << ": you are in jail:" << endl;
				p[pix]->set_location(prix);
				bool skip = p[pix]->getskipturns();
				if (skip == true) {
					int turns = p[pix]->getskip();
					if (turns < 2) {
						p[pix]->incskip();
					}
					else {
						p[pix]->setskip(false);
					}
				}

			}
			else if (prix == 21) {
				system("cls");
				cout << ": Parking: " << endl << endl;
				p[pix]->set_location(prix);
				p[pix]->decmoney(10);
			}
			else if (prix == 31) {
				system("cls");
				cout << "no go area" << endl << endl;
				p[pix]->set_location(11);
				jailcard = p[pix]->getjailcard();
				if (jailcard == true) {
					cout << "Would you like to use your get out of jail card?Press 1 to agree, 0 to decline." << endl;
					cin >> choice;
					if (choice == 1) {
						p[pix]->setjailcard(false);
					}
					else {
						cout << "Would you like to pay Rs.400 to get out of jail?Press 1 to do so, 0 to decline." << endl;
						cin >> choice;
						if (choice == 1) {
							p[pix]->decmoney(400);
						}
						else
						{
							p[pix]->setskip(true);
							p[pix]->set_location(11);
							bool skip = p[pix]->getskipturns();
							if (skip == true) {
								int turns = p[pix]->getskip();
								if (turns < 2) {
									p[pix]->incskip();
								}
								else {
									p[pix]->setskip(false);
								}
							}
						}
					}
				}
				else {
					system("cls");
					cout << "Would you like to pay Rs.400 to get out of jail?Press 1 to do so, 0 to decline." << endl;
					cin >> choice;
					if (choice == 1) {
						p[pix]->decmoney(400);
					}
					else
					{
						p[pix]->setskip(true);
						p[pix]->set_location(11);
						bool skip = p[pix]->getskipturns();
						if (skip == true) {
							int turns = p[pix]->getskip();
							if (turns < 2) {
								p[pix]->incskip();
							}
							else {
								p[pix]->setskip(false);
							}

						}
					}
				}
			}
			else if (prix > 32 && prix<39) {
				temp = p[pix]->pick_up_special_card();
				if (temp == 2) {
					on = board[32]->getown();
					if (on == true) {
						p[pix]->decmoney(dice * 5);
						id = board[32]->geto();
						p[id]->incmoney(dice * 5);
					}


				}
				else if (temp == 3) {
					on = board[27]->getown();
					if (on == true) {
						id = board[27]->geto();
						price = board[32]->getpp();
						p[pix]->decmoney(price * 2);
						p[id]->incmoney(price * 2);

					}
				}
				else if (temp == 11) {
					for (int i = 0; i < psize; i++) {
						if (getoid(pix) != i + 1) {
							p[i]->incmoney(25);
						}
					}
				}
				/////
			}
		}
		else {
			system("cls");
			upgrade = getupgrade(prix);
			if (!upgrade) {
				on = checkown(prix);
				if (!on) {
					board[prix]->prt();
					cout << "Do you want to buy this property?" << endl;
					int ans;
					cin >> ans;
					if (ans == 1) {
						int * var = p[pix]->get_oland();
						*var = prix;
						p[pix]->incplpro(prix);
						mon = board[prix]->getpp();
						p[pix]->decmoney(mon);
						board[prix]->setoid(pix + 1);
						board[prix]->setown(true);
						system("cls");
						board[prix]->prt();
						p[pix]->output();
						system("pause");
					}
					else {
						mon = auction(prix, id);
						p[id]->decmoney(mon);
						p[id]->incplpro(prix);
						board[prix]->setoid(id);
						board[prix]->setown(true);
					}
				}
				else {


					board[prix]->prt();
					mon = board[prix]->getr();
					p[pix]->decmoney(mon);
					id = board[prix]->geto();
				
					if (id != pix+1)
					{
						p[id]->incmoney(mon);///////////////////////////////////////////////////////////////////////////
						cout << "Rent collected: " << mon << endl;
					}
					if (id == pix+1)
					{
						sell_to_bank(pix, id);
					}
					system("Pause");
				}
			}
			else {
				on = checkown(prix);
				if (on == false) {
					board[prix]->prt();
					cout << "Do you want to buy this property?" << endl;
					int ans;
					cin >> ans;
					if (ans == 1) {
						p[pix]->incplpro(prix);
						mon = board[prix]->getpp();
						p[pix]->decmoney(mon);
						board[prix]->setoid(pix + 1);
						board[prix]->setown(true);
						system("cls");
						board[prix]->prt();
						p[pix]->output();
						system("pause");
					}
					else {
						mon = auction(prix, id);
						p[id]->decmoney(mon);
						p[id]->incplpro(prix);
						board[prix]->setoid(id);
						board[prix]->setown(true);
					}
				}
				else {
					board[prix]->prt();
					mon = board[prix]->getr();
					p[pix]->decmoney(mon);
					id = board[prix]->geto();
					p[id]->set_money(mon);
					cout << "Rent collected: " << mon << endl;
					system("Pause");
				}
			}
			
		}
		system("cls");

	}
	void setend(int ix) {
		p[ix]->setend();
	}

	bool getend(int ix) {
		return p[ix]->getend();
	}
	int getpid(int ix) {
		return board[ix]->getp();
	}
	bool getskip(int ix) {
		return p[ix]->getskipturns();
	}
	int getoid(int ix) {
		return p[ix]->getid(ix);
	}
	void setoid(int ix) {
		p[ix]->setid(ix);
	}
	int get_money(int ix)
	{
		return p[ix]->get_money();
	}
};

int roll() {
	srand(time(NULL));
	int j = rand() % 6 + 1;
	return j;
}

void printboard( int id) {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	char **property_name = new char*[40];
	for (int i = 0; i<40; i++) {
		property_name[i] = new char[40];
	}
	strcpy(property_name[0], "GO");
	strcpy(property_name[1], "Iqbal A");
	strcpy(property_name[2], "Iqbal B");
	strcpy(property_name[3], "Iqbal C");
	strcpy(property_name[4], "Johar A");
	strcpy(property_name[5], "Johar B");
	strcpy(property_name[6], "Fasial A");
	strcpy(property_name[7], "Fasial B");
	strcpy(property_name[8], "Fasial C");
	strcpy(property_name[9], "Model A");
	strcpy(property_name[10], "  Jail");
	strcpy(property_name[11], "Model B");
	strcpy(property_name[12], "Model C ");

	strcpy(property_name[13], "Gulberg 2A");
	strcpy(property_name[14], "Gulberg 2B");
	strcpy(property_name[15], "Gulberg 2C");
	strcpy(property_name[16], "Dha A");
	strcpy(property_name[17], "Dha B");
	strcpy(property_name[18], "Dha y");
	strcpy(property_name[19], "Bahiria A");
	strcpy(property_name[20], "Bahiria B");
	strcpy(property_name[21], "Park");
	strcpy(property_name[22], "Bahiria C");
	strcpy(property_name[23], "Metro Station");
	strcpy(property_name[24], "Bus Station");
	strcpy(property_name[25], "Railway Station");
	strcpy(property_name[26], "Orange Train");
	strcpy(property_name[27], "WASA");
	strcpy(property_name[28], "LESCO");
	strcpy(property_name[29], "PTCL");
	strcpy(property_name[30], "|| NO GO Area");
	strcpy(property_name[31], "SUI");
	strcpy(property_name[32], "Communitychest");
	strcpy(property_name[33], "Communitychest");
	strcpy(property_name[34], "Communitychest");
	strcpy(property_name[35], "Chance");
	strcpy(property_name[36], "Chance");
	strcpy(property_name[37], "Chance");
	strcpy(property_name[38], "Land Tax");
	strcpy(property_name[39], "Property Tax");
	cout << endl << endl << endl;
	cout << "_____________________________________________________________________________________________________________________________________________________________________" << endl << "||";
	for (int i = 0; i<11; i++) {
		if (id == i) {
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		}
		if (i == 0)
		{


			cout << "     " << property_name[i];
		}
		else if (i == 10)
			cout << "        " << property_name[i] << "  ||";
		else
			cout << "        " << property_name[i];

		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	}
	cout << endl << "_____________________________________________________________________________________________________________________________________________________________________" << endl;
	if (id == 39) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[39]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                                                                                                             ";
	if (id == 12) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[12] << "||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	if (id == 38) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[38]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                                                                                                               ";
	if (id == 13) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[13] << "||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	if (id == 37) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[37]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                                                                                                                 ";
	if (id == 14) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[14] << "||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	if (id == 36) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[36]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                           MONOPOLY GAME                                                                         ";
	if (id == 15) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[15] << "||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	if (id == 35) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[35]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                                                                                                                   ";
	if (id == 16) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[16] << "   ||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	if (id == 34) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[34]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                                                                                                           ";
	if (id == 17) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[17] << "   ||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	if (id == 33) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[33]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                                                                                                           ";
	if (id == 18) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[18] << "   ||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	if (id == 32) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << "||" << property_name[32]; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "                                                                                                                                          ";
	if (id == 19) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	cout << property_name[19] << "||"; SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << endl;

	for (int i = 30; i>20; i--)
	{
		if (id == i) { SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE); }

		if (i == 21)
		{
			cout << property_name[i] << " ||";
		}
		else
			cout << property_name[i] << "        ";
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	}
	cout << endl << "_____________________________________________________________________________________________________________________________________________________________________";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE);


}

int main() {
	int pnum;
	int bc;
	static int var = 0;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE);

	cout << "Enter number of players" << endl;
	cin >> pnum;
	game monopoly(pnum);
	int dice = 0, clocation=0;
	system("cls");
	int vari = 0;
	int end = 0, choice = 0, playingplayers = 0;
	bool cond, cond2;
	int location;
	for (int i = 0; i < pnum; i++) {
		monopoly.setoid(i);
	}
	int c = 0;
	while (end != -1) {
	
		for (int i = 0; i < pnum && end != -1; i++) {
			if (vari==i) {
				clocation = 0; 
				printboard(clocation);
				vari++;
			}
			else
			{
				clocation = monopoly.getplayerlocation(i);
				printboard(clocation);
			
			}
			c++;
			cout << endl << "player" << i + 1 << endl;
			cond = monopoly.getend(i);
			if (!cond) {
				cout << "Would you like to exit?Press 1 to exit, 0 to continue." << endl;
				cin >> choice;
				if (choice == 0) {
					cond2 = monopoly.getskip(i);
					if (cond2 == false) {
						dice = roll();
						clocation = monopoly.getplayerlocation(i);
						location = monopoly.loop(clocation, dice, i);/////////////////
						monopoly.setplayerlocation(location, i);
						monopoly.action(i, location, dice);
					}
					else {
						clocation = monopoly.getplayerlocation(i);
						monopoly.action(i, clocation, dice);
					}
					bc = monopoly.get_money(i);
					if (bc < 0) {
						monopoly.setend(i);
						cout << "player " << i + 1 << " is bankrupt . " << endl << endl;
						playingplayers = 0;
						for (int j = 0; j < pnum; j++) {
							if (monopoly.getend(j) == false) {
								playingplayers++;
							}
						}
						if (playingplayers < 2) {
							end = -1;
						}
					}
				}

				else {
					monopoly.setend(i);
					playingplayers = 0;
					for (int j = 0; j < pnum; j++) {
						if (monopoly.getend(j) == false) {
							playingplayers++;
						}
					}

					if (playingplayers < 2) {
						end = -1;
					}
				}
			}

		}
	}
	return 0;
}

