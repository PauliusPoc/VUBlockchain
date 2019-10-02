#include <iostream>
#include <string.h>
#include <bitset>
#include <fstream>
#include <random>

std::string s = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-*/!@#$%^&*()_-=[{]}'\"\\/";

std::string rnd_str(std::string str, int len){
    for (int i = 0; i < len; ++i) {
        //rand() % 100 -2
    }
}

void create_strings(){
    std::ofstream outfile ("test.txt");
    outfile << "my text here!" << std::endl;
    outfile.close();
}

const int HASH_LENGTH = 64;

long calcVal(long val) {
    if(val > 9999999) {
        while(val > 9999999) {
            val = val / 7;
        }
        return val;
    }
    if(val < 1000000) {
        while(val < 9999999) {
            val = val * 7;
        }
        return val;
    }
    return val;
}

long getCharsSum(std::string str) {
    long sum = 0;
    for(int i = 0; i < str.length(); i++) {
        sum += int(str[i]) * (i + 1);
    }
    return sum * str.length() ;
}

std::string hash(std::string input) {
    std::bitset<HASH_LENGTH> bs[8];
    for(auto & b : bs) {
        b = std::bitset<HASH_LENGTH>{}.set();
    }

    long test = calcVal(getCharsSum(input));
    for(int i = 0; i < 8; i++) {
        long val = test * (i+2);
        while (val >= 64) {
            int index = val % 64;
            val = val / 1.1 ;
            (bs[i].test(index) == 1) ? bs[i] = bs[i].reset(index) : bs[i].set(index);
            if (index % 3 == 0) {
                bs[i].flip();
            }
        }
    }
    char buffer[64];
    sprintf(buffer, "%08llx%08llx%08llx%08llx%08llx%08llx%08llx%08llx", bs[0].to_ullong(), bs[1].to_ullong(), bs[2].to_ullong(), bs[3].to_ullong(), bs[4].to_ullong(), bs[5].to_ullong(), bs[6].to_ullong(), bs[7].to_ullong());
    std::cout << buffer << '\n';

    for(int i = 0; i < 8; i++) {
        std::cout << i << " " << bs[i] << '\n';
    }

    std::cout << std::endl;
    return input;
}

void testing(){

}



int main() {
    hash("lietuvaa");
    std::cout << s.length();
    return 0;
}