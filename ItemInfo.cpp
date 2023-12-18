/**
 * file: proj4-ItemInfo.cpp
 * author: Prof. Aars
 * course: CSI 1440
 * assignment: project 4
 * due date: 9/25/2023
 *
 * This file is the function definitions file.
 */

#include "proj4-ItemInfo.hpp"
#include <cmath>
#include <iomanip>
#include <vector>

void ItemInfo::setItemId(const char *num) {
    int count = 0;
    int temp, pos;

    while (num[count] != '\0') {
        count++;
    }

    pos = count - 1;

    for (int i = 0; i < count; i++) {
        temp = num[i] - 48;
        itemId += temp * pow(10, pos);
        pos --;
    }
}

void ItemInfo::setDescription(const char *cstr) {
    int i = 0;
    while (cstr[i] != '\0') {
        description[i] = cstr[i];
        i++;
    }
    description[i] = '\0';
}

void ItemInfo::setManCost(const char *num) {
    manCost = stuCstrToDbl(num);
}

void ItemInfo::setSellPrice(const char *num) {
    sellPrice = stuCstrToDbl(num);
}

int ItemInfo::getItemId() {
    return itemId;
}

const char * ItemInfo::getDescription() {
    return description;
}

double ItemInfo::getManCost() {
    return manCost;
}

double ItemInfo::getSellPrice() {
    return sellPrice;
}

void ItemInfo::toAmazonJSON(ostream &out) {
    out << "\t\t\t \"itemId\": " << getItemId() << "\n";
    out << "\t\t\t \"description\": " << getDescription() << "\n";
    out << "\t\t\t \"manPrice\": " << getManCost() << "\n";
    out << "\t\t\t \"sellPrice\": " << getSellPrice() << "\n";
}

void ItemInfo::displayItemInfo(ostream &out) {
    char newline = '\n';
    char space = ' ';
    char colon = ':';
    char period = '.';
    char buffer[100]; // Adjust the buffer size as needed

    // Convert itemID to a string
    int itemIdCopy = itemId;
    int itemIdLength = 0;
    do {
        buffer[itemIdLength] = '0' + itemIdCopy % 10;
        itemIdCopy /= 10;
        itemIdLength++;
    } while (itemIdCopy > 0);

    // Output itemID
    out.put(newline);
    out.put('i');
    out.put('t');
    out.put('e');
    out.put('m');
    out.put('I');
    out.put('D');
    out.put(colon);
    out.put(space);
    for (int i = itemIdLength - 1; i >= 0; i--) {
        out.put(buffer[i]);
    }
    out.put(newline);

    // Output description
    out.put('d');
    out.put('e');
    out.put('s');
    out.put('c');
    out.put('r');
    out.put('i');
    out.put('p');
    out.put('t');
    out.put('i');
    out.put('o');
    out.put('n');
    out.put(colon);
    out.put(space);
    for (char c : description) {
        out.put(c);
    }
    out.put(newline);

    // Convert manCost to a string with 2 decimal places
    int manCostInteger = static_cast<int>(manCost);
    int manCostDecimal = static_cast<int>((manCost - manCostInteger) * 100);

    // Output manCost
    out.put('m');
    out.put('a');
    out.put('n');
    out.put('C');
    out.put('o');
    out.put('s');
    out.put('t');
    out.put(colon);
    out.put(space);
    for (int i = 0; i < manCostInteger; i++) {
        buffer[i] = '0' + manCostInteger % 10;
        manCostInteger /= 10;
    }
    for (int i = manCostInteger - 1; i >= 0; i--) {
        out.put(buffer[i]);
    }
    out.put(period);
    for (int i = 0; i < 2; i++) {
        buffer[i] = '0' + manCostDecimal % 10;
        manCostDecimal /= 10;
    }
    for (int i = 1; i >= 0; i--) {
        out.put(buffer[i]);
    }
    out.put(newline);

    // Convert sellPrice to a string
    int sellPriceCopy = static_cast<int>(sellPrice);
    int sellPriceLength = 0;
    do {
        buffer[sellPriceLength] = '0' + sellPriceCopy % 10;
        sellPriceCopy /= 10;
        sellPriceLength++;
    } while (sellPriceCopy > 0);

    // Output sellPrice
    out.put('s');
    out.put('e');
    out.put('l');
    out.put('l');
    out.put('P');
    out.put('r');
    out.put('i');
    out.put('c');
    out.put('e');
    out.put(colon);
    out.put(space);
    for (int i = sellPriceLength - 1; i >= 0; i--) {
        out.put(buffer[i]);
    }
    out.put(newline);

    // Convert calculatedProfit to a string with 2 decimal places
    double profit = calcProfit();
    int profitInteger = static_cast<int>(profit);
    int profitDecimal = static_cast<int>((profit - profitInteger) * 100);

    // Output calculatedProfit
    out.put('c');
    out.put('a');
    out.put('l');
    out.put('c');
    out.put('u');
    out.put('l');
    out.put('a');
    out.put('t');
    out.put('e');
    out.put('d');
    out.put('P');
    out.put('r');
    out.put('o');
    out.put('f');
    out.put('i');
    out.put('t');
    out.put(colon);
    out.put(space);
    for (int i = 0; i < profitInteger; i++) {
        buffer[i] = '0' + profitInteger % 10;
        profitInteger /= 10;
    }
    for (int i = profitInteger - 1; i >= 0; i--) {
        out.put(buffer[i]);
    }
    out.put(period);
    for (int i = 0; i < 2; i++) {
        buffer[i] = '0' + profitDecimal % 10;
        profitDecimal /= 10;
    }
    for (int i = 1; i >= 0; i--) {
        out.put(buffer[i]);
    }
    out.put(newline);
    out.put(newline);
}

double ItemInfo::calcProfit() {
    return sellPrice - manCost;
}

double stuCstrToDbl(const char *num) {
    int count = 0;
    int temp, pos, point;
    double val, result;
    bool negative = false;

    if (num[0] == '-') {
        negative = true;
        count = 1;
    }

    while (num[count] != '\0') {
        if (num[count] == '.') {
            point = count;
        }
        count++;
    }

    int i = 0;

    pos = count;

    if (negative) {
        i++;
        pos--;
    }

    for (i; i < count; i++) {
        temp = num[i] - 48;
        if (i == point) {
            pos = 0;
            temp = 0;
            result /= pow(10, count - point + 1);
        }
        val = static_cast<double>(temp);
        result += val * pow(10, pos);
        pos --;
    }

    if (negative) {
        result = -result;
    }
    return result;
}

void stuDblToCstr(char *cstr, double num) {
    bool negative = false;
    int count = 1, tmp, countA, countB;
    vector<int> digitB, digitA;

    digitB.clear();
    digitA.clear();

    if (num < 0) {
        negative = true;
        num = -num;
        count--;
    }

    int a = static_cast<int>(num);
    int b = num * 100;

    b %= a * 100;

    if (negative) {
        count ++;
    }

    tmp = a;
    while (tmp / 10 != 0) {
        count++;
        tmp /= 10;
    }
    countA = count;

    tmp = b;
    count ++;
    while (tmp / 10 != 0) {
        count ++;
        tmp /= 10;
    }
    countB = count - countA;

    for (int i = 0; i < count; i++) {
        cstr[i] = '0';
    }

    count++;

    while (b != 0) {
        tmp = b % 10;
        digitB.push_back(tmp);
        b -= tmp;
        b /= 10;
    }

    while (a != 0) {
        tmp = a % 10;
        digitA.push_back(tmp);
        a -= tmp;
        a /= 10;
    }


    for (int i = 0; i < countB; i++) {
        cstr[count - 1 - i] = digitB.at(i) + 48;
        if (i == countB - 1) {
            cstr[count - 1 - countB] = '.';
        }
    }

    tmp = countA - 1;
    for (int i = 0; i < countA; i++) {
        cstr[i] = digitA.at(tmp) + 48;
        tmp--;
    }

    cstr[count] = '\0';

    if (negative) {
        for (int i = count - 1; i >= 0; i--) {
            cstr[i+1] = cstr[i];
        }
        cstr[0] = '-';
    }

}

void stuCstrCpy(char *dest, const char *src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

int stuCstrLen(const char *src) {
    int count = 0;
    while (src[count] != '\0') {
        count ++;
    }

    return count;
}

ostream& printCString(ostream &out, const char *src){
    int len = stuCstrLen(src);
    for (int i = 0; i < len; i++) {
        out << src[i];
    }
}





