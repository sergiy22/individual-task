// XMLtask.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

int countdown(int ltimer) {
	int length, min = 0;
	cout << "Input timer length in seconds or \"0\" to load last timer" << endl;
	cout << "Last timer length - " << ltimer << " sec" << endl;
	cin >> length;
	if (length == 0)
		length = ltimer;
	int res = length;
	if (length >= 60) {
		min = length / 60;
		length = length % 60;
	}
	while (length > 0 && min >= 0) {
		cout << min << ":" << length << " sec" << "\r";
		length--;
		if (length == 1 && min > 0) {
			min--;
			length == 59;
		}
		cout.flush();
		Sleep(970);
	}
	cout << "Time passed" << endl;
	system("pause");
	return res;
}
double stopwatch(double ltimer) {
	cout << "Stopwatch" << endl;
	cout << "Last result - " << ltimer << " sec" << endl;
	char ch;
	int j = 0, i = 0;
	double time = 0;
	bool status = true;
	while (status != false) {
		time += 0.1;
		cout.flush();
		cout << time << " sec" << "\r";
		Sleep(70);
		if (GetKeyState(VK_RETURN) == false)
		{
			status = false;
			cout.flush();
			cout << "Time: " << time << " sec" << "\r";
			cout << endl << endl;
			break;
		}

	}
	return time;
}

int main() {
	ifstream fin("data.xml");
	int ltimer = 0;
	double lstopw = 0;
	string temp;
	double stopw = 0, countd = 0;
	while (!fin.eof()) {
		fin >> temp;
		if (temp == "<stopwatch>") {
			fin >> lstopw;
		}
		if (temp == "<countdown>") {
			fin >> ltimer;
		}
	}
	ofstream fout("data.xml");
	while (true) {
		cout << "1 - countdown" << endl;
		cout << "2 - stopwatch" << endl;
		int userinp;
		cin >> userinp;
		switch (userinp) {
		case 1:
			countd = countdown(ltimer);
			break;
		case 2:
			stopw = stopwatch(lstopw);
			break;
		default:
			fout << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
			fout << "<data>" << endl;
			fout << "<countdown> " << ((countd != 0) ? countd : ltimer) << " </countdown>" << endl;
			fout << "<stopwatch> " << ((stopw != 0) ? stopw : lstopw) << " </stopwatch>" << endl;
			fout << "</data>" << endl;
			return 0;
		}
	}
	return 0;
}