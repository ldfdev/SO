#include <iostream>
#include <fstream>
#include <vector>
#include <utility> //pt pair
#include <set>  //ca sa pastram sortate perechile
using namespace std;
int cautareT(vector<int> &tata, int nod)
{
    if(tata[nod]==0)
        return nod;
    tata[nod]=cautareT(tata,tata[nod]);
    return tata[nod];
}
struct comparare
{
bool operator()(const pair<pair<int,int>, int>&i, const pair<pair<int,int>, int>&j)
const{
    if(i.second<j.second)
        return 1;
    else if(i.second==j.second && i.first.second<j.first.second)
        return 1;
    else if(i.second==j.second && i.first.second==j.first.second && i.first.first<j.first.first)
        return 1;
    else
        return 0;
    }
};

multiset<pair< pair<int,int>,int>,comparare> date,apcm;
multiset<pair< pair<int,int>,int> > ::iterator it;
vector<int> culori_componente,tata,index;
vector<int>::iterator v_it;
int main()
{
    int N,M,x,y,z,muchie_cost_minim,sol = 1,cost_apcm=0;
    pair<int,int> temp;
    ifstream f("apm.in");
    ofstream g("apm.out");
    f>>N>>M;
    for(int i=0;i<=N;i++)
    {
        culori_componente.push_back(i);
        tata.push_back(0);
        index.push_back(0);
    }
    for(int i=1;i<=M;i++)
    {
        f>>x>>y>>z;
        temp=make_pair(x,y);
        date.insert(make_pair(temp,z));
    }
  /// for(it=date.begin();it!=date.end();++it)
  ///     cout<<(*it).first.first<<" "<<(*it).first.second<<"\n";
    ///KRUSKAL
    for(it=date.begin();it!=date.end() && sol<N;++it)
    {
        muchie_cost_minim=(*it).second;
        x=(*it).first.first;
        y=(*it).first.second;
        /*
        if(culori_componente[x]!=culori_componente[y])
            {
                for(int i=1;i<=N;i++)
                    {
                    if(culori_componente[i]==culori_componente[y] && i!=y)
                        culori_componente[i]=culori_componente[x];

                    }
                    culori_componente[y]=culori_componente[x];
                apcm.insert(make_pair(make_pair(x,y),muchie_cost_minim));
            }
            */
        int xx=cautareT(tata,x);
        int yy=cautareT(tata,y);
        if(xx!=yy)
        {

            apcm.insert(make_pair(make_pair(x,y),muchie_cost_minim));
            x=xx;
            y=yy;
            if(index[x]<index[y])
                tata[x]=y;
            else
            {   tata[y]=x;
                if(index[x]==index[y])
                index[x]++;
            }
            sol++;
        }
        /*int check=0;
        for(int i=2;i<=N;i++)
            if(culori_componente[i]!=culori_componente[1])
                check=1;
        if(!check)
            break;
            */
    }
    ///AFISARE COST APCM
    int cost_apcm=0,NUMAR_MUCHII_APCM=0;
    for(it=apcm.begin();it!=apcm.end();++it)
        {
            cost_apcm+=(*it).second;
            NUMAR_MUCHII_APCM++;
        }
    g<<cost_apcm<<endl;
    ///MUCHII ARBORE APCM
    g<<NUMAR_MUCHII_APCM<<endl;
    ///LISTARE MUCHII
    for(it=apcm.begin();it!=apcm.end();++it)
        g<<(*it).first.first<<" "<<(*it).first.second<<endl;


    return 0;
}
