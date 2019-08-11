#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>
#include "PlanetWars.h"
#include <fstream>
#include <map>
using namespace std;

//ofstream print;
// The DoTurn function is where your code goes. The PlanetWars object contains
// the state of the game, including information about all planets and fleets
// that currently exist. Inside this function, you issue orders using the
// pw.IssueOrder() function. For example, to send 10 ships from planet 3 to
// planet 8, you would say pw.IssueOrder(3, 8, 10).
//
// There is already a basic strategy in place here. You can use it as a
// starting point, or you can throw it out entirely and replace it with your
// own. Check out the tutorials and articles on the contest website at
// http://www.ai-contest.com/resources.
int Dist(double x1, double y1, double x2, double y2){
   return ceil(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}
bool comparefleetbyturn(const Fleet &F1,const Fleet &F2){
  return F1.TurnsRemaining() < F2.TurnsRemaining();
}
bool comparebyID(const Planet &P1,const Planet &P2){
  return P1.PlanetID()<P2.PlanetID();
}
int dist(Planet P1,Planet P2){
  return Dist(P1.X(),P1.Y(),P2.X(),P2.Y());
}
struct sort_pred {
    bool operator()(const pair<Planet,int> &left, const pair<Planet,int> &right) {
        return left.second < right.second;
    }
};
int fleetrequirednew(const PlanetWars& pw,Planet p){
  //print<<"fleetreqin"<<endl;
  //print<<"PlanetID: "<<p.PlanetID()<<" fdist :"<<fdist<<endl;
  vector<Fleet> fleet = pw.Fleets();
  vector<Fleet> inc_fleet;
  for(int i=0;i<fleet.size();i++){
    if(fleet[i].DestinationPlanet() == p.PlanetID()){
      inc_fleet.push_back(fleet[i]);
    }
  }
 // print<<"inc_fleetsize: "<<inc_fleet.size()<<endl;
  if(inc_fleet.size()==0){
    if(p.Owner()!=1)return p.NumShips();
    else return 0;
  }
  int own = p.Owner();
  sort(inc_fleet.begin(),inc_fleet.end(),comparefleetbyturn);
  int fltreq = 0;
  int current = p.NumShips();
  int turns = 0;
  if(inc_fleet.size()>1){
      if(own==2){current += inc_fleet[0].TurnsRemaining()*p.GrowthRate();}
      if(own==1){current += inc_fleet[0].TurnsRemaining()*p.GrowthRate();}
    for(int i=0;i<inc_fleet.size()-1;i++){
      if(own == 0){
        current = current - inc_fleet[i].NumShips();
        if(current<0){
          current = -1*current;
          own = inc_fleet[i].Owner();
          current += (inc_fleet[i+1].TurnsRemaining()-inc_fleet[i].TurnsRemaining())*p.GrowthRate();
        }
      }
      else if(own == 2){
        if(inc_fleet[i].Owner() == 1){
          current = current - inc_fleet[i].NumShips();
          if(current<0){
            current = -1*current;
            own = 1;
            current += (inc_fleet[i+1].TurnsRemaining()-inc_fleet[i].TurnsRemaining())*p.GrowthRate();
          }
        }
        else{
          current += inc_fleet[i].NumShips();
          current += (inc_fleet[i+1].TurnsRemaining()-inc_fleet[i].TurnsRemaining())*p.GrowthRate();
        }
      }
      else if(own == 1){
        if(inc_fleet[i].Owner() == 2){
          current = current - inc_fleet[i].NumShips();
          if(current<0){
            current = -1*current;
            own = 2;
            current += (inc_fleet[i+1].TurnsRemaining()-inc_fleet[i].TurnsRemaining())*p.GrowthRate();
          }
        }
        else{
          current += inc_fleet[i].NumShips();
          current += (inc_fleet[i+1].TurnsRemaining()-inc_fleet[i].TurnsRemaining())*p.GrowthRate();
        }
      }
    }
    if(own==0){
      current = current - inc_fleet[inc_fleet.size()-1].NumShips();
      if(current<0){
        current = -1*current;
      own = inc_fleet[inc_fleet.size()-1].Owner();
    }
    }
    else if(own == 1){
      if(inc_fleet[inc_fleet.size()-1].Owner() == 1 ){
        current = current + inc_fleet[inc_fleet.size()-1].NumShips();
      }
      else if(inc_fleet[inc_fleet.size()-1].Owner() == 2){
        current = current - inc_fleet[inc_fleet.size()-1].NumShips();
        if(current<0){
          current = -1*current;
          own = 2;
        }
      }
    }
    else if(own == 2){
      if(inc_fleet[inc_fleet.size()-1].Owner() == 2 ){
        current = current + inc_fleet[inc_fleet.size()-1].NumShips();
      }
      else if(inc_fleet[inc_fleet.size()-1].Owner() == 1){
        current = current - inc_fleet[inc_fleet.size()-1].NumShips();
        if(current<0){
          current = -1*current;
          own = 2;
        }
      }
    }
  }
  else{
    if(own==0){
      current = current - inc_fleet[inc_fleet.size()-1].NumShips();
      if(current<0){
        current = -1*current;
      own = inc_fleet[inc_fleet.size()-1].Owner();
    }
      }
      else if(own == 1){
        current += inc_fleet[0].TurnsRemaining()*p.GrowthRate(); 
        if(inc_fleet[inc_fleet.size()-1].Owner() == 1 ){
          current = current + inc_fleet[inc_fleet.size()-1].NumShips();
        }
        else if(inc_fleet[inc_fleet.size()-1].Owner() == 2){
          current = current - inc_fleet[inc_fleet.size()-1].NumShips();
          if(current<0){
            current = -1*current;
            own = 2;
          }
        }
     }
      else if(own == 2){
        current += inc_fleet[0].TurnsRemaining()*p.GrowthRate(); 
        if(inc_fleet[inc_fleet.size()-1].Owner() == 2 ){
          current = current + inc_fleet[inc_fleet.size()-1].NumShips();
        }
        else if(inc_fleet[inc_fleet.size()-1].Owner() == 1){
          current = current - inc_fleet[inc_fleet.size()-1].NumShips();
          if(current<0){
            current = -1*current;
            own = 2;
          }
        }
    }
  }
 if(own == 0)return current;
 else if(own == 2)return current;
 else if(own == 1){
      return 0;
    }
}
int getnearestmyplanet(Planet p,const PlanetWars& pw){
  vector<Planet> my=pw.MyPlanets();
  int min=100000;
    for(int i=0;i<my.size();i++){
      int k=dist(p,my[i]);
      if(k<=min){min=k;
      }
    }
    return min;
}
int np(Planet p,const PlanetWars& pw){
  vector<Planet> my=pw.EnemyPlanets();
    int min=100000,n=-1,gr=0;
    for(int i=0;i<my.size();i++){
      int k=dist(p,my[i]);
      if(k<=min){min=k;n=my[i].NumShips();gr=p.GrowthRate();}}
    if(n-min*gr >0)return n - min*gr;
    else return 0; 
  }
vector<Planet> attack(const PlanetWars& pw,map<int,int> fleet,int n){
  vector<Planet> planets = pw.Planets();
  int g[planets.size()][n+1];
  for(int i=0;i<n+1;i++){
    if(i<fleet[0])g[0][i]=0;
    else g[0][i]=planets[0].GrowthRate();}
  for(int i=1;i<planets.size();i++){
    for(int j=0;j<n+1;j++){
      if(j<fleet[i])g[i][j]=g[i-1][j];
      else {int k1=planets[i].GrowthRate()+g[i-1][j-fleet[i]],k2=g[i-1][j];
        if(k1>k2)g[i][j]=k1;
        else g[i][j]=k2;}}}
  vector<Planet> target;
  int k=n;
  for(int i=planets.size()-1;i>0;i--){
    if(k>=fleet[i]){if(g[i][k]==(g[i-1][k-fleet[i]]+planets[i].GrowthRate())){target.push_back(planets[i]);k-=fleet[i];}}}
  if(k>=0){if(g[0][k]!=0)target.push_back(planets[0]);}
  return target;
  }
int myfleet(const PlanetWars& pw){
  vector<Planet> planets=pw.MyPlanets();
  int tot=0;
  for(int i=0;i<planets.size();i++){
    tot+=planets[i].NumShips();}
  return tot;}

void DoTurn(const PlanetWars& pw) {
  map<int,int> ship;
  vector<Planet> planets=pw.Planets();
  vector<Planet> my=pw.MyPlanets();
  vector<Fleet> fleets=pw.Fleets();
  for(int i=0;i<planets.size();i++){
    ship[planets[i].PlanetID()]=fleetrequirednew(pw,planets[i]);
  }
    /*
  for(int i=0;i<fleets.size();i++){
    Fleet tmp=fleets[i];
    if(tmp.Owner()==1)ship[tmp.DestinationPlanet()]-=tmp.NumShips();
    else ship[tmp.DestinationPlanet()]+=tmp.NumShips();}
  map<int,int>fdist;
  for(int i=0;i<planets.size();i++){
    fdist[planets[i].PlanetID()]=np(planets[i],pw);}
  for(int i=0;i<planets.size();i++){
    Planet p=planets[i];
    if(p.Owner()!=1 && p.Owner()!=0){ship[p.PlanetID()]+=(p.NumShips() + fdist[p.PlanetID()]);}
    if(p.Owner()==0)ship[p.PlanetID()]+=p.NumShips();}
    */
    for (int i = 0; i < planets.size(); ++i)
    { 
      int fdist = np(planets[i],pw);
      if(planets[i].Owner()==2){ship[planets[i].PlanetID()]+=fdist;
        int k = getnearestmyplanet(planets[i],pw);
        ship[planets[i].PlanetID()]+=k*planets[i].GrowthRate();
      }
    }
  map<int,int> check;map<int,int> cons;
  int tot_ships=0;
  for(int i=0;i<my.size();i++){
    check[my[i].PlanetID()]=my[i].NumShips();
    int x=np(my[i],pw)+ship[my[i].PlanetID()];
    //int x = ship[my[i].PlanetID()];
    if(x>=0)cons[my[i].PlanetID()]=x;
    else cons[my[i].PlanetID()]=0;
    int k=check[my[i].PlanetID()]-cons[my[i].PlanetID()];
    if(k>0)tot_ships+=k;
    }
  for(int i=0;i<planets.size();i++){
    ship[planets[i].PlanetID()]*=1.1;
    if(ship[planets[i].PlanetID()]<0)ship[planets[i].PlanetID()]=0;
    if(ship[planets[i].PlanetID()]==0)ship[planets[i].PlanetID()]=0;
    else if(ship[planets[i].PlanetID()]<10)ship[planets[i].PlanetID()]+=1;
  }
  vector<Planet> target;
  //if(turn<=10)target=attack(pw,myinit,ship,tot_ships);
  target=attack(pw,ship,tot_ships);
  vector<vector<pair<Planet,int> > > tgtsrc;
  for(int i=0;i<target.size();i++){
    Planet p=target[i];
    vector<pair<Planet,int> > tmp;
    for(int j=0;j<my.size();j++){
      Planet q=my[j];
      if(p.PlanetID() != q.PlanetID())tmp.push_back(make_pair(q,dist(p,q)));}
    sort(tmp.begin(),tmp.end(),sort_pred());
    tgtsrc.push_back(tmp);
    }
  
  for(int i=0;i<tgtsrc.size();i++){  //set target to max 3
  int ships=ship[target[i].PlanetID()];
    for(int j=0;j<tgtsrc[i].size();j++){     //set source to max 3
      Planet src=tgtsrc[i][j].first;
      if(ships<=check[src.PlanetID()]-cons[src.PlanetID()]){
        if(ships>0){pw.IssueOrder(src.PlanetID(),target[i].PlanetID(),ships);
        check[src.PlanetID()]-=ships;break;
        }
        }
      else{int k=check[src.PlanetID()]-cons[src.PlanetID()];
        if(k>0){pw.IssueOrder(src.PlanetID(),target[i].PlanetID(),k);
          check[src.PlanetID()]-=k;
          ships-=k;}}
      }
  }

}

// This is just the main game loop that takes care of communicating with the
// game engine for you. You don't have to understand or change the code below.
int main(int argc, char *argv[]) {
  std::string current_line;
  std::string map_data;
  //print.open("debugger.txt");
  while (true) {
    int c = std::cin.get();
    current_line += (char)c;
    if (c == '\n') {
      if (current_line.length() >= 2 && current_line.substr(0, 2) == "go") {
        PlanetWars pw(map_data);
        map_data = "";
        DoTurn(pw);
  pw.FinishTurn();
      } else {
        map_data += current_line;
      }
      current_line = "";
    }
  }
  return 0;
}
