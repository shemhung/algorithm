#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cmath>
#include<cstdlib>
using namespace std;
int min_distance(vector<vector<int>> &p,vector<int> &city_choose,int start);
double calcultion(vector<vector<int>> &p,vector<int> &city_route);
int main(int argc,char *argv[]){
    fstream fs;
    int id,x,y;
    vector<vector<int>> p;              //p[num][0]=x,p[num][1]=y ;c[][num] for all city 
    vector<int> city;
    vector<double> d;                   //all city's distance
    fs.open(argv[1],ios::in);
    while(fs>>id>>x>>y){
        vector<int> temp;
        city.push_back(id-1);
        temp.push_back(x);
        temp.push_back(y);
        p.push_back(temp);
    }
    vector<int> city_choose(city.size()),city_route;    //city_choose(city.size())=[0,0,0,0,0,0,0,0]被選了就變為1
    vector<int> c;
    fs.close();

    int start=0;
    city_choose[start]=1;
    city_route.push_back(start);                        //被選了就丟到city_route
    for(int i=0;i<city_choose.size()-1;i++){
        start=min_distance(p,city_choose,start);        //找出最小的就丟到city_route
        city_route.push_back(start);
    }
    fs.open(argv[2],ios::out);
    fs<<"distance: "<<calcultion(p,city_route)<<endl;
    for(int i=0;i<city_route.size();i++){
            fs<<city_route[i]+1<<endl;
    }
}
int min_distance(vector<vector<int>> &p,vector<int> &city_choose,int start){
    vector<double> dis;
    for(int i=0;i<city_choose.size();i++){              //算出離start的距離
        if(city_choose[i]==1)   
            continue;
        else{
            dis.push_back(sqrt(pow(p[start][0]-p[i][0],2)+pow(p[start][1]-p[i][1],2)));
        }
    }
    double min_city=*min_element(dis.begin(),dis.end());//找出最小的距離
    int count=0;
    int zero_index;
    for(int i=0;i<dis.size();i++){                      //找出在0裡面最小距離的index
        if(dis[i]==min_city){
            zero_index=i+1;
            break;
        }  
    }
    for(int i=0;i<city_choose.size();i++){              //在0裡面的index,當zero_index==count,找到最小值
        if(city_choose[i]==0)
            count++;
        if(zero_index==count){
            city_choose[i]=1;
            return i;
        }
    }
}
double calcultion(vector<vector<int>> &p,vector<int> &city_route){
    double sum=0;
    for(int i=1;i<city_route.size();i++){
        sum+=sqrt(pow(p[city_route[i]][0]-p[city_route[i-1]][0],2)+pow(p[city_route[i]][1]-p[city_route[i-1]][1],2)); //x^2+y^2開根
    }
    sum+=sqrt(pow(p[city_route.back()][0]-p[city_route[0]][0],2)+pow(p[city_route.back()][1]-p[city_route[0]][1],2));
    return sum;
}