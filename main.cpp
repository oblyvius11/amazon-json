/**
 * file: proj4-main.cpp
 * author: Prof. Aars
 * course: CSI 1440
 * assignment: project 4
 * due date: 2/27/2023
 *
 * date modified:  2/27/2023
 *    - file created
 *
 * This file is the main file.
 */

#include <iostream>
#include "proj4-ItemInfo.hpp"
#include <fstream>

using namespace std;

void itemResize(ItemInfo*& a, int &size) {
    size *= 2;

    ItemInfo* newItem = new ItemInfo[size];

    for (int i = 0; i < size/2; i++) {
        newItem[i] = a[i];
    }

    delete[] a;

    a = nullptr;

    a = newItem;
}

char* strToCstr(string a) {
    int size = a.size();
    char* b = new char[size + 1];

    for (int i = 0; i < size; i++) {
        b[i] = a[i];
    }
    b[size] = '\0';

    return b;
    delete[] b;
}


int main()
{
    ifstream file;
    int i = 0;
    string val;
    const char* id;
    const char* desc;
    const char* manuCost;
    const char* price;
    ItemInfo* item = new ItemInfo [2];
    int size = 2;

    file.open("proj4-productServices.csv");

    while (getline(file, val, ',')) {
        id = strToCstr(val);
        getline(file, val, ',');
        desc = strToCstr(val);
        getline(file, val, ',');
        manuCost = strToCstr(val);
        getline(file, val);
        price = strToCstr(val);



        item[i].setItemId(id);
        item[i].setDescription(desc);
        item[i].setManCost(manuCost);
        item[i].setSellPrice(price);

        i++;

        if (i >= size) {
            itemResize(item, size);
        }

        delete[] id;
        delete[] desc;
        delete[] manuCost;
        delete[] price;
    }

    cout << "NORMAT FORMAT: " << endl << endl;

    for (int j = 0; j < i; j++) {
        item[j].displayItemInfo(cout);
    }
    cout << endl;

    cout << "SORTING ARRAY OF ITEMS BY PROFIT" << endl << endl;


    for (int j = 0; j < i - 1; j++) {
        for (int k = 0; k < i - j - 1; k++) {
            if (item[k].calcProfit() < item[k + 1].calcProfit()) {
                ItemInfo temp = item[k];
                item[k] = item[k + 1];
                item[k + 1] = temp;
            }
        }
    }

    string position[5];

    position[0] = "firstItem";
    position[1] = "secondItem";
    position[2] = "thirdItem";
    position[3] = "fourthItem";
    position[4] = "fifthItem";

    cout << "AMAZON FORMAT: " << endl << endl;

    cout << "\"Aiden's Store\": [" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "\t\t\"" << position[i] << "\": {" << endl;
        item[i].toAmazonJSON(cout);
        cout << "\t\t}," << endl;
    }
    cout << "]" << endl;

    file.close();

    delete[] item;

    return 0;
}


