//
//  main.cpp
//  testScore
//
//  Created by 张涛 on 24/11/17.
//  Copyright © 2017 张涛. All rights reserved.
//

#include <iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>       /* sqrt */
#include <iomanip>
#include <algorithm>

using namespace std;
class comp{
public:
    int companyId;
    double score[4];
    double scaleScore[4];
    double sum;
    int rank;
    void scale(double bar[4], double std[4]){
        for(int i=0;i<4;i++){
            scaleScore[i] = (score[i]-bar[i])/std[i];
        }
        sum = scaleScore[0]*0.3 + scaleScore[1]*0.2 + scaleScore[2]*0.15 + scaleScore[3]*0.35;
    }
    
    comp(double a_, double b_, double c_, double d_, int id_){
        score[0] = a_;
        score[1] = b_;
        score[2] = c_;
        score[3] = d_;
        companyId = id_;
    }
    
    void printScore(){
        for(int i=0;i<4;i++){
            cout << setprecision(3) << fixed << score[i] <<  '\t';
        }
        cout << setprecision(3) << fixed << sum;
        cout << endl;
    }
    
    void printScale(){
        for(int i=0;i<4;i++){
            cout << setprecision(3) << fixed << scaleScore[i] <<  '\t';
        }
        cout << setprecision(3) << fixed << sum;
        cout << endl;
    }
    
    bool operator > (const comp& str) const
    {
        return (sum > str.sum);
    }
    
    //case two
    void calCaseTwo(){
        sum = 0;
        for(int i=0;i<4;i++){
            sum += score[i];
        }
    }
};

void calHighestForEach(vector<comp> comps,int highestId[3] ){

    double highestScore[3] = {0,0,0};
    double secondHighestScore[3] = {0,0,0};
    for(int i=0;i<comps.size();i++){
        for(int j=0;j<3;j++){
            if(comps[i].score[j]>highestScore[j]){
                secondHighestScore[j] = highestScore[j];
                highestScore[j] = comps[i].score[j];
                highestId[j] = comps[i].companyId;
            }
        }
    }
    for(int j=0;j<3;j++){
        if(highestScore[j]-secondHighestScore[j]<3){
            highestId[j] = -1;
        }
    }
}

void calBar(vector<comp> comps, double bar[4], double std[4]){
    int sum[4] = {0,0,0,0};
    for(int i=0;i<comps.size();i++){
        for(int j=0;j<4;j++){
            sum[j] += comps[i].score[j];
        }
    }
    for(int j=0;j<4;j++){
        bar[j] = sum[j]/comps.size();
    }
    
    double stdTemp[4] = {0,0,0,0};
    for(int i=0;i<comps.size();i++){
        for(int j=0;j<4;j++){
            stdTemp[j] += (comps[i].score[j]-bar[j]) * (comps[i].score[j]-bar[j]);
        }
    }
    for(int j=0;j<4;j++){
        std[j] = sqrt(stdTemp[j]/comps.size());
    }
}

bool searchQueZi(vector<comp> comps,int highestId){
    for(int i=0;i<6;i++){
        if(comps[i].companyId == highestId){
            return true;
        }
    }
    return false;
}
int main(int argc, const char * argv[]) {
    srand ( time(NULL) );
    vector<comp> comps;
    double bar[4] = {0,0,0,0};
    double std[4] = {0,0,0,0};
    
    for(int i=0;i<15;i++){
        double a = rand() % 11;
        double b = rand() % 11;
        double c = rand() % 11;
        double d = rand() % 3+6;
        comp temp(a,b,c,d,i+1);
        comps.push_back(temp);
    }
    
    calBar(comps, bar, std);
    cout << "company"  << '\t' << '\t';
    cout << "a" << '\t' << '\t';
    cout << "b"  << '\t' << '\t';
    cout << "c"  << '\t' << '\t';
    cout << "d"  << '\t' << '\t';

    cout << "sum"  << '\t' << '\t';
    cout << endl;

    for(int i=0;i<15;i++){
        cout << "company" << comps[i].companyId << '\t';
        comps[i].printScore();
    }
    cout << "after scale" << endl;
    for(int i=0;i<15;i++){
        comps[i].scale(bar,std);
    }
    sort(comps.begin(), comps.end(), greater<comp>());
    for(int i=0;i<15;i++){
        cout << "company" << comps[i].companyId << '\t';
        comps[i].printScale();
    }
    
    //case 2
    for(int i=0;i<15;i++){
        comps[i].calCaseTwo();
    }
    int highestId[3] = {0,0,0};
    calHighestForEach(comps,highestId);
    sort(comps.begin(), comps.end(), greater<comp>());
    cout << "case 2:" << endl;
    cout << "before replacement: " << endl;
    for(int i=0;i<15;i++){
        cout << "company" << comps[i].companyId << '\t';
        comps[i].printScore();
    }
    vector<comp>::iterator it;
    for(int i=0;i<3;i++){
        cout << "quezi shi:" << highestId[i] << endl;
    }
    for(int i=0;i<3;i++){
        for(it = comps.begin(); it != comps.end(); it++)    {
            if(highestId[i] == it->companyId) {
                break;
            }
        }
        if((!searchQueZi(comps, highestId[i])) && (highestId[i]!=-1)){
            cout << "replace company" << (comps.begin()+5-i)->companyId << " to company" << it->companyId << endl;
            iter_swap(comps.begin()+5-i, it);
        }
    }
    cout << "after replacement: " << endl;

    for(int i=0;i<15;i++){
        cout << "company" << comps[i].companyId << '\t';
        comps[i].printScore();
    }
    
    return 0;
}
