#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
struct Link{
    int f1;
    int f2;
    int d;
};
struct Factory{
    int name;
    int production;
    int owner;
    int content;
    int strike;
};
struct Troop{
    int owner;
    int origin;
    int destination;
    int content;
    int dleft;
};
struct Bomb{
    int owner;
    int origin;
    int destination;
    int dleft;
};
int main()
{
    int factoryCount; // the number of factories
    cin >> factoryCount; cin.ignore();
    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();
    list<Link> links;
    list<Factory> factorys;
    vector<pair<int,int>> myFactorys;
    list<Troop> troops;
    list<Bomb> bombs;
    Link link;
    Factory factory;
    Troop troop;
    Bomb bomb;
    int done=0;
    
    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> link.f1 >> link.f2 >> link.d; cin.ignore();
        links.push_back(link);
    }

    // game loop
    while (1) {
        factorys.clear();
        myFactorys.clear();
        troops.clear();
        bombs.clear();
        int entityCount; // the number of entities (e.g. factories and troops)
        cin >> entityCount; cin.ignore();
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            int arg5;
            cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; cin.ignore();
            if (entityType=="FACTORY"){
                factory.name=entityId;
                factory.owner=arg1;
                factory.content=arg2;
                factory.production=arg3;
                factory.strike=arg4;
                factorys.push_back(factory);
                if (arg1==1){
                    myFactorys.push_back(std::make_pair(factory.content,factory.name));                    
                }
            }
            else if (entityType=="TROOP"){
                troop.owner=arg1;
                troop.origin=arg2;
                troop.destination=arg3;
                troop.content=arg4;
                troop.dleft=arg5;
                troops.push_back(troop);
            }
            else if (entityType=="BOMB"){
                bomb.owner=arg1;
                bomb.origin=arg2;
                bomb.destination=arg3;
                bomb.dleft=arg4;
                bombs.push_back(bomb);
            }
        }
        done=0;
        for (auto &itF:factorys){
            
            if (/*itF.production==3 && */itF.owner==0 && !myFactorys.empty()){
            	int cont=0;
            	sort(myFactorys.begin(),myFactorys.end());
                pair<int,int> fab=*std::prev(myFactorys.end());
            	cout << "MOVE " << fab.second << " " << itF.name <<" 100" << endl;
            	done=1;
            	break;
            }
        }
        if (done!=1) {
            for (auto &itF:factorys){
                
                if (/*itF.production==3 && */itF.owner==-1 && !myFactorys.empty()){
                	int cont=0;
                	sort(myFactorys.begin(),myFactorys.end());
                    pair<int,int> fab=*std::prev(myFactorys.end());
                	cout << "MOVE " << fab.second << " " << itF.name <<" 100" << endl;
                	done=1;
                	break;
                }
            }
        }
        if (done!=1) cout << "WAIT" << endl;
    }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
       
  
}