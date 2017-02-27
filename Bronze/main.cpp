#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_map>

using namespace std;


class Node{
    //int id;
    int production;
    int owner;
    int content;
    int strike;
    vector <pair<int,int>> neighbors;
    
    Node(int p, int o, int c, int s){
    	production=p;
    	owner=o;
    	content=c;
    	strike=s;
    }
};
/*struct Link{
    int f1;
    int f2;
    int d;
};*/

class Troop{
	//int id; 
    int owner;
    int origin;
    int destination;
    int content;
    int tour_arrivee;
    
    Troop(int own, int ori, int de, int c, int ta){
    	owner=own;
    	origin=ori;
    	destination=de;
    	content=c;
    	tour_arrivee=ta;
    }
};
struct Bomb{
	//int id
    int owner;
    int origin;
    int destination;
    int tour_arrivee;
    Bomb(int own, int ori, int de, int ta){
		owner=own;
		origin=ori;
		destination=de;
		tour_arrivee=ta;
    }
};
/*int find_closest(int origin, unordered_multimap<int,pair<int,int>> &neighbors, list<Factory> &factorys){
	pair<unordered_multimap<int,pair<int,int>>::iterator,unordered_multimap<int,pair<int,int>>::iterator>  range = neighbors.equal_range(origin);
	vector<pair<int,int>> tneighbors;
	int result;
	int result_owner;
	for(unordered_multimap<int,pair<int,int>>::iterator it = range.first; it!=range.second; it++){
		tneighbors.push_back(it->second);
	}
	sort(tneighbors.begin(),tneighbors.end());
	auto it=tneighbors.begin();
	do {
		result = it->second; //the id of node with least d ...
		it++;
		for (Factory fac : factorys){
			if (fac.name==result) {
				result_owner=fac.owner;
				break;
			}
		}		
	}while(result_owner==1 && it!=tneighbors.end());//closest is friend
	cerr << "dist : " << it->first <<endl;
	return result; 
}*/
int main()
{
    int factoryCount; // the number of factories
    cin >> factoryCount; cin.ignore();
    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();
    list<Link> links;
    //unordered_multimap<int,pair<int,int>> neighbors; //node1,pair<distance,node2>
    map<int,Noeud> factorys;
    vector<pair<int,int>> myFactorys;
    map<int,Troop> troops;
    map<int,Bomb> bombs;
    //Link link;
    Noeud factory;
    Troop troop;
    Bomb bomb;
    int done=0;
    int count[3]={0,0,0};
    
    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> link.f1 >> link.f2 >> link.d; cin.ignore();
        links.push_back(link);
        if (factorys.find(link.f1) == factorys.end()){
        	factorys.insert(make_pair(link.f1,Noeud(0,0,0,0)));
        }
        factorys[f1].neighbors.push_back(make_pair(link.d,link.f2));
        if (factorys.find(link.f2) == factorys.end()){
            factorys.insert(make_pair(link.f2,Noeud(0,0,0,0)));
        }
        factorys[f2].neighbors.push_back(make_pair(link.d,link.f1));
        neighbors.insert(make_pair(link.f1,make_pair(link.d,link.f2)));
        neighbors.insert(make_pair(link.f2,make_pair(link.d,link.f1)));
    }
    int tour=0;
    // game loop
    while (1) {
        tour++;
        myFactorys.clear();
        //troops.clear();
        //bombs.clear();
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
                factorys[entityId].owner=arg1;
                factorys[entityId].content=arg2;
                factorys[entityId].production=arg3;
                factorys[entityId].strike=arg4;
                if (arg1==1){
                    myFactorys.push_back(std::make_pair(factory.content,factory.name));                    
                }
            }
            else if (entityType=="TROOP"){
            	int id = arg1*(arg2*10000+arg3*100+tour+arg5);
            	if (troops.find(id) == troops.end()){
            		troops.insert(make_pair(id,Troop(arg1,arg2,arg3,arg4, arg5+tour)));
            	}
            	else {
            		troops[id].owner=arg1;
					troops[id].origin=arg2;
					troops[id].destination=arg3;
					troops[id].content=arg4;
					troops[id].tour_arrivee=arg5+tour;
            	}
            }
            else if (entityType=="BOMB"){
            	int id=arg1*count[arg1+1];
            	count[arg1+1]++;
            	if (bombs.find(id) == bombs.end()){
            		bombs.insert(make_pair(id,Bomb(arg1,arg2,arg3,arg4+tour)));
            	}
            	else {
                bombs[id].owner=arg1;
                bombs[id].origin=arg2;
                bombs[id].destination=arg3;
                bombs[id].tour_arrivee=arg4+tour;
            	}
            }
        }
        cout << "WAIT" ;
        done=0;
        for (auto &itF:factorys){    
            if (itF.owner==1 && itF.content>2){
            	int obj=find_closest(itF.name,neighbors,factorys);
            	
            	cout << ";MOVE " << itF.name << " " << obj <<" " << floor(itF.content*0.7) ;
            	done=1;            	
            }
            /*if (itF.owner==0 && !myFactorys.empty()){
            	int cont=0;
            	sort(myFactorys.begin(),myFactorys.end());
                pair<int,int> fab=*std::prev(myFactorys.end());
            	cout << ";MOVE " << fab.second << " " << itF.name <<" 100" ;
            	myFactorys.pop_back();
            	done=1;            	
            }*/
        }
        /*if (done!=1) {
            for (auto &itF:factorys){
                
                if (itF.owner==-1 && !myFactorys.empty()){
                	int cont=0;
                	sort(myFactorys.begin(),myFactorys.end());
                    pair<int,int> fab=*std::prev(myFactorys.end());
                	cout << ";MOVE " << fab.second << " " << itF.name <<" 100";
                	done=1;
                	break;
                }
            }
        }*/
        //if (done!=1) cout << "WAIT" << endl;
        cout << endl;
    }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
       
  
}