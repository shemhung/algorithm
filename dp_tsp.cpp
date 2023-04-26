#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<bitset>
using namespace std;
void calculation(vector<vector<int>> &p,vector<vector<double>> &d);
int findindex(vector<double> &distance_temp,double min);
int main(int argc,char *argv[]){
    fstream fs;
    int id,x,y;
    vector<vector<int>> p;              //p[num][0]=x,p[num][1]=y ;c[][num] for all city 
    vector<int> city;
    vector<double> d_temp;
    vector<vector<double>> d;                   //all city's distance city x city   1 2 3 4 5 6
    fs.open(argv[1],ios::in);                   //                                 1 
    while(fs>>id>>x>>y){                        //                                 2
        vector<int> temp;                       //                                 3
        city.push_back(id-1);                   //                                 4
        temp.push_back(x);                      //                                 5
        temp.push_back(y);                      //                                 6
        p.push_back(temp);
    }
    fs.close();
    calculation(p,d);
    const int bit_digit=24;
    // for(int i=0;i<p.size();i++){
    //     for(int j=0;j<p.size();j++){
    //         cout<<d[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    vector<bitset<bit_digit>> bs,bs_copy;           //2^14 xxxx(14個位元)
    bitset<bit_digit> b;                    //14個位元
    vector<vector<double>> distance(city.size(),vector<double>(pow(2,bit_digit),0));
    vector<double> distance_temp;
    vector<vector<int>> city_route(city.size(),vector<int>(pow(2,bit_digit),0));
    vector<int> city_route_temp;
    int bs_num;
    double sum=0,min;
    for(int i=0;i<pow(2,bit_digit);i++){
        bitset<bit_digit> b(i);
        bs.push_back(b);
        //cout<<bs[i]<<" ";
    }
    bs_copy=bs;
    for(int i=0;i<city.size();i++){
        distance[i][0]=d[i][0];
    }
    //cout<<city.size()<<endl;
    for(int i=1;i<bs.size();i++){            //縱軸2^15-1
        for(int j=0;j<city.size();j++){       //橫軸 15城市
            if(j!=0 && bs[i][j-1]==1){        //城市對應的bit是1->0
                continue;
            }
            for(int k=0;k<b.size();k++){
                if(bs[i][k]==1 ){              //每個bit是不是1，是->改0
                    sum+=d[j][k+1];            //加第一個式子
                    bs[i][k]=0;

                    city_route_temp.push_back(k+2);
                }
                else    
                    continue;
                bs_num=bs[i].to_ulong( );      //轉十進位，
                sum+=distance[k+1][bs_num];   //加第二個式子;


                distance_temp.push_back(sum);
                sum=0;
                bs[i]=bs_copy[i];
            }
            min=(*min_element(distance_temp.begin(),distance_temp.end()));

            city_route[j][i]=city_route_temp[findindex(distance_temp,min)];
            city_route_temp.clear();
            distance[j][i]=min;
            distance_temp.clear();
        }
    }

    vector<int> ans;
    ans.push_back(1);
    ans.push_back(city_route[0][pow(2,bit_digit)-1]);
    int start=1;
    while(bs_copy[pow(2,bit_digit)-1] !=bs_copy[0]){
        bs_copy[bs_copy.size()-1][ans[start]-2]=0;
        bs_num=bs_copy[pow(2,bit_digit)-1].to_ulong( );
        ans.push_back(city_route[ans[start]-1][bs_num]);
        start++;
    }
    ans.pop_back();
    // cout<<"route ";
    // for(int i=0;i<ans.size();i++){
    //     cout<<ans[i]<<" ";
    // }
    // cout<<endl;
    
    // for(int i=0;i<city.size();i++){
    //     for(int j=0;j<bs.size();j++){
    //         cout<<distance[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    //cout<<distance[0][bs.size()-1]<<" ";
 



   

   
    fs.open(argv[2],ios::out);
    fs<<"distance: "<<distance[0][bs.size()-1]<<endl;
    for(int i=0;i<city_route.size();i++){
            fs<<ans[i]<<endl;
    }
}

void calculation(vector<vector<int>> &p,vector<vector<double>> &d){         //d[0][0] for 1-1,d[1][1] for 2-2,
    vector<double> temp_dis;
    for(int i=0;i<p.size();i++){
        for(int j=0;j<p.size();j++){
            temp_dis.push_back(sqrt(pow(p[i][0]-p[j][0],2)+pow(p[i][1]-p[j][1],2))); //x^2+y^2開根
        }
        d.push_back(temp_dis);
        temp_dis.clear();  
    }   
}
int findindex(vector<double> &distance_temp,double min){
    for(int i=0;i<distance_temp.size();i++){
        if(distance_temp[i]==min)
            return i;
    }
}