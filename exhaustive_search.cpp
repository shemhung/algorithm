#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cmath>
#include<cstdlib>
using namespace std;
double distance(vector<vector<int>> &p,vector<int> &city);
int main(int argc,char *argv[]){
    fstream fs;
    int id,x,y;
    vector<vector<int>> p,c;        //p[num][0]=x,p[num][1]=y ;c[][num] for all city 
    vector<int> city;
    vector<double> d;               //all city's distance
    fs.open(argv[1],ios::in);       //read in file
    while(fs>>id>>x>>y){  
        vector<int> temp;
        city.push_back(id-1);       //city's id
        temp.push_back(x);          //city's x
        temp.push_back(y);          //city's y
        p.push_back(temp);
    }
    fs.close();

    do{
        c.push_back(city);                              //push_back 城市順序
        d.push_back(distance(p,city));                  //calculation
    }while(next_permutation(city.begin(),city.end()));
    double min_city=*min_element(d.begin(),d.end());    //find the smallest's distance in 全部順序
    int min_index;
    for(int i=0;i<d.size();i++){                        //find index of smallest's distance
        if(d[i]==min_city){
            min_index=i;
            break;
        }
    }
    fs.open(argv[2],ios::out);
    fs<<"distance: "<<min_city<<endl;               
    for(int i=0;i<c[min_index].size();i++){
            fs<<c[min_index][i]+1<<endl;
    }
    
}
double distance(vector<vector<int>> &p,vector<int> &city){ //calculate 城市順序的距離
    double sum=0;
    for(int i=1;i<city.size();i++){     
        sum+=sqrt(pow(p[city[i]][0]-p[city[i-1]][0],2)+pow(p[city[i]][1]-p[city[i-1]][1],2)); //x^2+y^2開根
    }
    sum+=sqrt(pow(p[city.back()][0]-p[city[0]][0],2)+pow(p[city.back()][1]-p[city[0]][1],2));
    return sum;
   
}