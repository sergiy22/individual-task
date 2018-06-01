#include <iostream>
#include <Windows.h>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <cmath>
#include <io.h>
#include <cstdlib>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

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
			length = 59;
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

	int ltimer = 0;
	double lstopw = 0;
	string temp;
	double stopw = 0, countd = 0;
	
	if (!_access("data.xml", 0)) {
		tinyxml2::XMLDocument doc;
		doc.LoadFile("data.xml");
		XMLNode * rRoot = doc.FirstChild();
		if (rRoot == nullptr) {
			return XML_ERROR_FILE_READ_ERROR;
		}
		XMLElement * cdn = rRoot->FirstChildElement("countdown");
		if (cdn == nullptr) return XML_ERROR_PARSING_ELEMENT;
		cdn->QueryDoubleText(&countd);
		XMLElement * stw = rRoot->FirstChildElement("stopwatch");
		if (cdn == nullptr) return XML_ERROR_PARSING_ELEMENT;
		cdn->QueryDoubleText(&stopw);
	}
	else {
		countd = stopw = 0;
	}
	//countd = stopw = 0;
	while (true) {
		cout << "1 - countdown" << endl;
		cout << "2 - stopwatch" << endl;
		int userinp;
		cin >> userinp;
		switch (userinp) {
		case 1:
			countd = countdown(ltimer);
			ltimer = (countd > 0) ? countd : ltimer;
			break;
		case 2:
			stopw = stopwatch(lstopw);
			lstopw = (stopw > 0) ? stopw : lstopw;
			break;
		default:
			countd = (countd != 0) ? countd : ltimer;
			stopw = (stopw != 0) ? stopw : lstopw;

			tinyxml2::XMLDocument xmlDoc;
			XMLNode * pRoot = xmlDoc.NewElement("data");
			xmlDoc.InsertFirstChild(pRoot);
			XMLElement * pElement = xmlDoc.NewElement("countdown");
			pElement->SetText(countd);
			pRoot->InsertEndChild(pElement);
			XMLElement * pElement1 = xmlDoc.NewElement("stopwatch");
			pElement1->SetText(stopw);
			pRoot->InsertEndChild(pElement1);

			xmlDoc.SaveFile("data.xml");
			return 0;
		}
	}
	return 0;
}