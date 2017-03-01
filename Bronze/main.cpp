#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
//#include <unordered_map>
#include <map>

using namespace std;


class Node{
    //int id;
    public: 
    int production;
    int owner;
    int content;
    int strike;
    vector<pair<int,int>> neighbors;
    
    Node(int p, int o, int c, int s);
    Node(const Node &n);
    Node();
};
Node::Node(){
    	production=0;
    	owner=0;
    	content=0;
    	strike=0;
    }
Node::Node(const Node &n){
	production=n.production;
	owner=n.owner;
	content=n.content;
	strike=n.strike;
}
Node::Node(int p, int o, int c, int s){
    	production=p;
    	owner=o;
    	content=c;
    	strike=s;
    }
struct Link{
    int f1;
    int f2;
    int d;
};

class Troop{
    public: 
	//int id; 
    int owner;
    int origin;
    int destination;
    int content;
    int tour_arrivee;
    Troop(int own, int ori, int de, int c, int ta);
    Troop(const Troop &t);
    Troop();
    
};
Troop::Troop(int own, int ori, int de, int c, int ta){
    	owner=own;
    	origin=ori;
    	destination=de;
    	content=c;
    	tour_arrivee=ta;
    }
Troop::Troop(const Troop &t){
    owner=t.owner;
	origin=t.origin;
	destination=t.destination;
	content=t.content;
	tour_arrivee=t.tour_arrivee;
}
Troop::Troop(){
    owner=0;
	origin=-1;
	destination=-1;
	content=-1;
	tour_arrivee=-1;
    }
class Bomb{
    public: 
	//int id
    int owner;
    int origin;
    int destination;
    int tour_arrivee;
    Bomb(int own, int ori, int de, int ta);
    Bomb(const Bomb &bomb);
    Bomb();
};
Bomb::Bomb(){
    owner=0;
    origin=-1;
    destination=-1;
    tour_arrivee=-1;
    }
Bomb::Bomb(const Bomb &bomb){
    owner=bomb.owner;
    origin=bomb.origin;
    destination=bomb.destination;
    tour_arrivee=bomb.tour_arrivee;
    }
Bomb::Bomb(int own, int ori, int de, int ta){
		owner=own;
		origin=ori;
		destination=de;
		tour_arrivee=ta;
    }
//int obj=find_closest(itF->first,neighbors,factorys);
int find_closest(int origin, /*vector<pair<int,int>> &neighbors,*/ map<int,Node> &factorys){
	int result;
	int result_owner;
	sort(factorys[origin].neighbors.begin(),factorys[origin].neighbors.end());
	auto it=factorys[origin].neighbors.begin();
	do {
		result = it->second; //the id of node with least d ...
		it++;	
		result_owner=factorys[result].owner;
	}while(result_owner==1 && it!=factorys[origin].neighbors.end());//closest is friend
	cerr << "dist : " << it->first <<endl;
	return result; 
}
/*********BOARD*****************/

//class Board{
    pair<int,int> sumTroops(const map<int,Troop> &troops, const map<int,Node> &factorys, const int tour){
		int ami=0;
		int enemi=0;
		for (auto it=troops.cbegin(); it!=troops.cend(); it++){
			if (it->second.tour_arrivee > tour){
				if (it->second.owner==1) ami+=it->second.content;
				else enemi+=it->second.content;
			}
		}
		for (auto it=factorys.cbegin(); it!=factorys.cend(); it++){
					if (it->second.owner==1) ami+=it->second.content;
					else if (it->second.owner==-1)enemi+=it->second.content;
				}
				cerr << ami << " " << enemi << endl;
		return make_pair(ami,enemi);
	};
	//int winner(vector<pair<int,int>> &myFactorys, map<int,Troop> &troops, map<int,Node> &factorys, map<int,Bomb> &bombs,int &count[3], int tour){
	int winner(map<int,Troop> &troops, map<int,Node> &factorys, int tour){
		pair<int,int> ami_enemi=sumTroops(troops, factorys, tour);
		if (ami_enemi.first==0) return -1;
		else if (ami_enemi.second==0) return 1;
		else if (tour>399){
			if (ami_enemi.first > ami_enemi.second) return 1;
			else if (ami_enemi.first < ami_enemi.second) return -1;
		}
		else return 0;			
	};
	void solveBattles(map<int,Troop> &troops, map<int,Node> &factorys, int tour){ //plus produce cyborgs in factories
		for (auto it=factorys.begin(); it!=factorys.end(); it++){//produce
			it->second.content+=it->second.production;
		}
		for (auto it=factorys.begin(); it!=factorys.end(); it++){//solve battles // todo: erase dead troops 
			int entries=0; //amis >0 enemis <0
			for (auto jt=troops.cbegin(); jt!=troops.cend(); jt++){
				if(jt->second.tour_arrivee==tour && jt->second.destination==it->first) entries+=(jt->second.owner*jt->second.content); 
			}
			//update content and owners after battle
			if(it->second.owner==0){
			    if(entries <0){
			        if(it->second.content+entries <0) {//enemy will take it
			            it->second.content=-(it->second.content+entries);
			            it->second.owner=-1;
			        }
			        else if(it->second.content+entries >0) {//enemy will not take it
			            it->second.content+=entries;
			        }
			    }
			    else if (entries>0){
				    if(it->second.content<entries) {//I will take it
			            it->second.content=-(it->second.content-entries);
			            it->second.owner=1;
			        }
			        else if(it->second.content+entries >0) {//I will not take it
			            it->second.content-=entries;
			        }
			        
			    }
			}
			else if (abs(entries)>it->second.content){
					it->second.owner=it->second.owner*-1;
					it->second.content=abs(it->second.content-abs(entries));
			}
			else it->second.content+=(it->second.owner*entries);
		    cerr << it->first << " cont=" << it->second.content << endl;
		}		
	}
	
//}
/*
 * One game turn is computed as follows:

    Move existing troops and bombs
    Execute user orders
    Produce new cyborgs in all factories
    Solve battles
    Make the bombs explode
    Check end conditions
 * 
 */

/************************************************************************************/
int main()
{
    int factoryCount; // the number of factories
    cin >> factoryCount; cin.ignore();
    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();
    vector<pair<int,int>> myFactorys;
    map<int,Troop> troops;
    map<int,Node> factorys;
    map<int,Bomb> bombs;
    int count[3]={0,0,0};
    int tour=0;
    
    for (int i = 0; i < linkCount; i++) { 
        int f1;
        int f2;
        int d;
        cin >> f1 >> f2 >> d; cin.ignore();
        if (factorys.find(f1) == factorys.end()){
            Node emptyNode(0,0,0,0);
        	factorys.emplace(f1,emptyNode);
        }
        factorys[f1].neighbors.push_back(make_pair(d,f2));
        if (factorys.find(f2) == factorys.end()){
            Node emptyNode(0,0,0,0);
            factorys.emplace(f2,emptyNode);
        }
        factorys[f2].neighbors.push_back(make_pair(d,f1));        
    }

    // game loop
    while (1) {
        tour++;
        myFactorys.clear();
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
                    myFactorys.push_back(std::make_pair(factorys[entityId].content,entityId));                    
                }
            }
            else if (entityType=="TROOP"){
            	int id = arg1*(arg2*10000+arg3*100+tour+arg5);
            	if (troops.find(id) == troops.end()){
            		troops.emplace(id,Troop(arg1,arg2,arg3,arg4, arg5+tour));
            	}
            	/*else {
            		troops[id].owner=arg1;
					troops[id].origin=arg2;
					troops[id].destination=arg3;
					troops[id].content=arg4;
					troops[id].tour_arrivee=arg5+tour;
            	}*/ //donees statiques
            }
            else if (entityType=="BOMB"){
            	int id=arg1*count[arg1+1];
            	count[arg1+1]++;
            	if (bombs.find(id) == bombs.end()){
            		bombs.emplace(id,Bomb(arg1,arg2,arg3,arg4+tour));
            	}
            	/*else {
                bombs[id].owner=arg1;
                bombs[id].origin=arg2;
                bombs[id].destination=arg3;
                bombs[id].tour_arrivee=arg4+tour;
            	}*/ //donees statiques
            }
        }
        cout << "WAIT" ;
        for (auto itF=factorys.begin(); itF!=factorys.end(); itF++){    
            if (itF->second.owner==1 && itF->second.content>2){
            	int obj=find_closest(itF->first,factorys);
            	cout << ";MOVE " << itF->first << " " << obj <<" " << floor(itF->second.content*0.7) ;
            }
        }
        cout << endl;
        cerr << winner(troops, factorys, tour) << endl;
        solveBattles(troops, factorys, tour);
    }

}
