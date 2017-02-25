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
};
struct Troop{
    int owner;
    int origin;
    int destination;
    int content;
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
    list<int> myFactorys;
    list<Troop> troops;
    Link link;
    Factory factory;
    Troop troop;
    
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
                factorys.push_back(factory);
                if (arg1==1){
                    myFactorys.push_back(factory.name);                    
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
            for (auto &itF:factorys){
                if (itF.production==3 && itF.owner!=1 && !myFactorys.empty())
                    //int origin = myFactorys.front();
                    cout << "MOVE " << myFactorys.front() << " " << itF.name <<" 100" << endl;
                    //myFactorys.pop_front();
                }
            
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
        cout << "WAIT" << endl;
    }
}