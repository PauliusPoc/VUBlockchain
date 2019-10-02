#include <iostream>
#include <string.h>
#include <bitset>
#include <fstream>
#include <random>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <sstream>

std::string s = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-*!@#$%^&*()_-=[{]}'\"\\/";

const int BITSET_LENGTH = 32;

std::string rnd_str(int len){
    srand (time(NULL));
    std::string str{};
    for (int i = 0; i < len; ++i) {
        str = str + s[rand() % s.length()];
    }
    return str;
}

void create_strings(){
    std::ofstream outfile ("testBigString2.txt");
    for (int i = 0; i < 1; ++i) {
        outfile << rnd_str(15000) << std::endl;
        //outfile << rnd_str(5) << " " << rnd_str(5 ) << std::endl;
    }
    outfile.close();
}

void create_diff_strings(){
    std::ofstream outfile ("test100k-pairs-diff.txt");

    for (int i = 0; i < 100000; ++i) {
        std::string a = rnd_str(5);
        std::string b = a;
        while ( a == b){
            b[4] = s[rand() % s.length()];
            if (a != b){
                outfile << a << " " << b << std::endl;
            }
        }
    }
    outfile.close();

}




long getCharsSum(std::string str) {
    long sum = 0;
    for(int i = 0; i < str.length(); i++) {
        sum += abs(int(str[i])) * (i + 8);
    }
    long val = sum * str.length() / 3 ;
    val = val / 2 * (val / 3);
    long randm = val % abs((int(str[0])) + abs(int(str[str.length() - 1])) / 2 );
    for (int j = 1; j < randm; ++j) {
        val = val + sin(int(str[0])) + sin(j) * cos(int(str[str.length() - 1 ])) + ((abs(int(str[0])) + abs(int(str[str.length() - 1 ]))) /2)  - abs(int(str[str.length() % j ]));
    }
    return val / 2;
}

std::string hash(std::string input) {
    std::bitset<BITSET_LENGTH> bs[8];
    for(auto & b : bs) {
        b = std::bitset<BITSET_LENGTH>{}.set();
    }

    long test = getCharsSum(input);

    std::stringstream res;
    std::string tmp_str;

    for(int i = 0; i < 8; i++) {
        int sk = 0;
        long val = std::abs(test * (i+3));

        //std::cout << val << std::endl;
        while (val >= BITSET_LENGTH) {
            int index = val % BITSET_LENGTH;
            val = val / 1.05 - (i*2) - bs[i].count() ;
            bs[i].flip(index);
            bs[i].flip(abs(index -  bs[i].count()));
            if (index % 2 == 0) {
                bs[i].flip();
            }
        }
    }
    std::string hex_str;

    for(int i = 0; i < 8; i++) {
        std::stringstream res;
        std::string tmp_str;
        res << std::hex <<  bs[i].to_ullong();
        res >> tmp_str;
        int diff = 8 - tmp_str.length();
        if(diff < 8){
            for (int j = 0; j < diff; ++j) {
                tmp_str.insert(0, "0");
            }
        }
        hex_str += tmp_str;
    }

    return hex_str;
}

void testing(){
    std::vector<std::string> testfiles = {"test1m-pairs.txt"};

    std::string a,b;
        for(int i = 0; i < testfiles.size() ; i++){
            int t = 0;
            int k = 0;
            std::ifstream infile(testfiles[i]);
            std::cout << testfiles[i] << std::endl;
            while (infile >> a >> b){
                std::string hasha = hash(a);
                std::string hashb = hash(b);

                if(hasha == hashb){
                    t++;
                    std::cout << a  << std::endl  << b  << std::endl;
                }
                else{k++;}
            }
            std::cout << k << " praejo" << std:: endl;
            std::cout << t << " fails" << std:: endl;
        }

    }


std::string HexToBin(std::string hexdec)
{
    long int i = 0;
    std::string binStr = "";

    while (hexdec[i]) {
        switch (hexdec[i]) {
            case '0':
                binStr += "0000";
                break;
            case '1':
                binStr += "0001";
                break;
            case '2':
                binStr += "0010";
                break;
            case '3':
                binStr += "0011";
                break;
            case '4':
                binStr += "0100";
                break;
            case '5':
                binStr += "0101";
                break;
            case '6':
                binStr += "0110";
                break;
            case '7':
                binStr += "0111";
                break;
            case '8':
                binStr += "1000";
                break;
            case '9':
                binStr += "1001";
                break;
            case 'a':
                binStr += "1010";
                break;
            case 'b':
                binStr += "1011";
                break;
            case 'c':
                binStr += "1100";
                break;
            case 'd':
                binStr += "1101";
                break;
            case 'e':
                binStr += "1110";
                break;
            case 'f':
                binStr += "1111";
                break;
            default:
                break;
        }
        i++;
    }
    return binStr;
}

void testingBits(std::string filename){
    std::string a,b;
    double minmatch = 512;
    double maxmatch = 0;
    double match = 0;

    double mincharmatch = 512;
    double maxcharmatch = 0;
    double charmatch = 0;

    double avgmatch = 0;
    double avgcharmatch = 0;
    int t = 0;
    int k = 0;

    std::vector<std::string> testfiles = {filename};
    for(int i = 0; i < testfiles.size() ; i++){
        std::ifstream infile(testfiles[i]);
        std::cout << testfiles[i] << std::endl;
    while (infile >> a >> b){
        std::string hasha = hash(a);
        std::string hashb = hash(b);

        std::string ab = HexToBin(hasha);
        std::string bb = HexToBin(hashb);

        match = 0;
        charmatch = 0;

        for (int j = 0; j < ab.length(); j++) {
            if (ab[j] != bb[j]) match++;
        }
        for (int j = 0; j < hasha.size(); j++) {
            if (hasha[j] != hashb[j]) charmatch++;
        }

        if(hasha == hashb){
            t++;
            std::cout << a << " " << getCharsSum(a) << std::endl  << b << " " << getCharsSum(b) << std::endl;
        }
        else{k++;}

        if(match < minmatch) minmatch = match;
        if(match > maxmatch) maxmatch = match;
        avgmatch = (avgmatch + match) / 2;

        if(charmatch < mincharmatch) mincharmatch = charmatch;
        if(charmatch > maxcharmatch) maxcharmatch = charmatch;
        avgcharmatch = (avgcharmatch + charmatch) / 2;

    }
    std::ofstream outFile;
    outFile.open("outputs/comparison.txt");

    std::cout << k << " praejo \n";
    std::cout << t << " fails" << std:: endl << "Bits Lygmuo "<< std::endl << "Min Diff % " << minmatch/256*100.00 << std::endl
    << "Max Diff % " << maxmatch/256*100.00 << std::endl << "Avg Diff % " << avgmatch/256*100.00 << std::endl;

    std::cout << "Char Lygmuo "<< std::endl << "Min Diff % " << mincharmatch/64*100.00 << std::endl
    << "Max Diff % " << maxcharmatch/64*100.00 << std::endl << "Avg Diff % " << avgcharmatch/64*100.00 << std::endl;

    outFile << k << " praejo " <<std::endl ;
    outFile << t << " fails" << std:: endl << "Bits Lygmuo "<< std::endl << "Min Diff % " << minmatch/256*100.00 << std::endl
            << "Max Diff % " << maxmatch/256*100.00 << std::endl << "Avg Diff % " << avgmatch/256*100.00 << std::endl;
    outFile << "Char Lygmuo "<< std::endl << "Min Diff % " << mincharmatch/64*100.00 << std::endl
            << "Max Diff % " << maxcharmatch/64*100.00 << std::endl << "Avg Diff % " << avgcharmatch/64*100.00 << std::endl;

 }
}


void testFileTime(std::string filename){
    std::ifstream file(filename, std::ios::in);

    std::cout << filename << '\n';
    if(file.good()){
        std::string str;
        clock_t start = {};
        double fulltime = 0;
        double testime = 0;
        for(int i = 0; i < 1000; i++){
            while(getline(file,str)){
                std::istringstream ss(str);
                start =  clock();
                hash(str);
                fulltime += (double)(clock() - start)/CLOCKS_PER_SEC;;
            }
            testime += fulltime;
        }
        std::cout << testime/1000 << " sec." << std::endl;

        std::ofstream outFile;
        outFile.open("outputs/measured.txt");
        outFile << testime/1000 << " sec." << std::endl;
        outFile.close();
    }
}

std::string readFromFile(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);
    std::string input;
    getline(inFile, input);
    inFile.close();
    return hash(input);
}

int main(int argc, const char * argv[]) {
    //create_diff_strings();
    //create_strings();


    if(std::string(argv[1]) == "--files") {
        std::ofstream outFile;
        outFile.open("outputs/files.txt");
        for (int i = 0; i < argc; i++) {
            outFile << argv[i] << ": " << readFromFile(std::string(argv[i])) << std::endl;
        }
        outFile.close();
        std::cout << "Output file: outputs/files.txt" << std::endl;
    }

    else if(std::string(argv[1]) == "--compare") {
        testingBits(std::string(argv[2]));
        std::cout << "Output file: outputs/measured.txt" << std::endl;
    }

    else if(std::string(argv[1]) == "--string") {
        std::ofstream outFile;
        outFile.open("outputs/string.txt");
        outFile << hash(std::string(argv[2]));
        outFile.close();
        std::cout << "Output file: outputs/string.txt" << std::endl;
    }

    else if(std::string(argv[1]) == "--time") {
        testFileTime(std::string(argv[2]));
        std::cout << "Output file: outputs/measured.txt" << std::endl;
    }


    /*
    std::vector<std::string> testfiles = {"oneletter1.txt", "oneletter2.txt", "testBigString1.txt", "testBigString2.txt", "testBigStringDiff1.txt", "testBigStringDiff2.txt"};
    for(int i = 0; i < testfiles.size() ; i++) {
        std::ifstream infile(testfiles[i]);
        std::string s;
        while (infile >> s){
            std::cout <<  testfiles[i] << std::endl;
            std::cout <<  hash(s) << std::endl;
        }

    }
    testFileTime("konstitucija.txt"); // 0.208s
    testingBits("test100k-pairs-diff.txt");
    testing();
    */
    return 0;
}