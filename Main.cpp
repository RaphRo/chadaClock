/*
 *	ChadaClock.cpp
 *
 *  Created on: Mar 22, 2020
 *  Author: Raphael Rose
 *	Assignment: 3-1: Project One - Chada Clock
 */

#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <thread>
#include <conio.h>
#define Size 50
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

//Functions defined in this code
void displayTime(time_t tmp);		//a method to display the formatted time
void displayMenu();					//a method to display the menu
time_t addSecond(time_t tmp);		//a method to add seconds
time_t addMinute(time_t tmp);		//a method to add minutes
time_t addHour(time_t tmp);			//a method to add hours
time_t buttonListener(time_t now);	//a method to listen for button presses

int main() {

	//generates local variables for the time clock
	time_t start = time(0);	//The unix time for the current 
	time_t now = time(0);	//The current time
	time_t then = time(0);  //The time when button listener stopped and the menu was opened
	char selection = '0';	//A character to denote the user selection


	while (selection != '4') {
		if (selection == '1') {			//adds one hour
			start = buttonListener(addHour(start));
			//This code snippet adjusts the time for the lag in the user entry
			then = time(0);					
			cin >> selection;
			now = time(0);
			start = start + now - then;
		} else if (selection == '2') {	//adds one minute
			start = buttonListener(addMinute(start));
			//This code snippet adjusts the time for the lag in the user entry
			then = time(0);					
			cin >> selection;
			now = time(0);
			start = start + now - then;
		} else if (selection == '3') {	//adds once second
			start = buttonListener(addSecond(start));
			//This code snippet adjusts the time for the lag in the user entry
			then = time(0);
			cin >> selection;
			now = time(0);
			start = start + now - then;
		} else {
			//This code snippet adjusts the time for the lag in the user entry
			start = buttonListener(start);
			then = time(0);
			cin >> selection;
			now = time(0);
			start = start + now - then;
		}
	}

	return 0;
}
//Display Time - displays the 
void displayTime(time_t tmp) {
	struct tm newtime;		//The structured time object that will be used in this method
	char TIME_12[Size];		//Variable for the 12 hour clock
	char TIME_24[Size];		//Variable for the 24 hour clock

	localtime_s(&newtime, &tmp); //creates a structure time for the current time passed
	
	//formats the two time values
	strftime(TIME_12, sizeof(TIME_12), "%I:%M:%S %p", &newtime);
	strftime(TIME_24, sizeof(TIME_24), "%H:%M:%S", &newtime);

	//outputs the formatted time values
	cout << "**************************      **************************" << endl;
	cout << "*     12-Hour Clock      *      *     24-Hours Clock     *" << endl;
	cout << "*      " << TIME_12 << "       *      *        " << TIME_24 << "        *" << endl;
	cout << "**************************      **************************" << endl;
}
//Display Menu -- creates the display menu
void displayMenu() {
	cout << "**************************" << endl;
	cout << "*  1 - Add One Hour      *" << endl;
	cout << "*  2 - Add One Minute    *" << endl;
	cout << "*  3 - Add One Second    *" << endl;
	cout << "*  4 - Exit the Program  *" << endl;
	cout << "**************************" << endl;
	cout << "Please enter selection, press 4 to exit: ";
}
//Listen for a button press
time_t buttonListener(time_t now) {
	while (!_kbhit()) {
		system("cls");
		displayTime(now);
		sleep_until(system_clock::now() + 1s);
		now = addSecond(now);
	}
	displayMenu();
	return now;
}
//Add Hour Function - pulls in unix timestamp and adds one hour
time_t addHour(time_t tmp) {
	tmp += 3600;
	return tmp;
}
//Add Minute Function - pulls in unix timestamp and adds one minute
time_t addMinute(time_t tmp) {
	tmp += 60;
	return tmp;
}
//Add Second Function - pulls in unix timestamp and adds one second
time_t addSecond(time_t tmp) {
	tmp += 1;
	return tmp;
}