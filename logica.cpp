#include <bits/stdc++.h>
using namespace std;

int main(){
  /*
  printf("Digite o nome do Arquivo de entrada: ");
  string arquivo;
  cin >> arquivo;
  freopen(arquivo.c_str(), "r", stdin);
  /**/
  freopen("Entrada.in", "r", stdin);
  freopen("saida.out", "w", stdout);

  int n;
  string prop;
  cin >> n;
  getline(cin, prop);

  for(int prob = 1; prob <= n; prob++){
    getline(cin, prop);
    bool fnc = true;
    bool horn = true;
    bool sat = true;
    vector<vector<int>> clause;
    int tam = prop.size();

    bool dentro = false;
    int temPos = -1;
    vector<int> temp(9, 0);
    int neg = 0;

    set<int> unitPos;
    vector<int> varToClause[8];

    for(int i = 0; i < tam && fnc; i++){
      switch (prop[i])
      {
      case '(':
        if(dentro)
          fnc = false;
        else{
          dentro = true;
        }
        break;

      case ')':
        if(!dentro)
          fnc = false;
        else{
          dentro = false;
          clause.push_back(temp);
          if(temp[8] == 1 && temPos != -1)
            unitPos.insert(temPos);
          temPos = -1;
          for(int k = 0; k < 9; k++){
            temp[k] = 0;
          }
        }
        break;

      case 'v':
        if(!dentro)
          fnc = false;
        break;

      case '~':
        if(!dentro)
          fnc = false;
        neg = 1 - neg;
        break;

      case '&':
        if(dentro)
          fnc = false;
        break;
        
      case '>':    
      case '<':
        fnc = false;
        break;
      
      case 'P':      
      case 'Q':
      case 'R':
      case 'S':
        if(!dentro)
          fnc = false;
        
        int mapa = (prop[i] - 'P') * 2 + neg;
        if(neg == 0){
          if(temPos != -1)
            horn = false;
          else
            temPos = mapa;
        }
        
        if(temp[mapa] == 0){
          temp[mapa]++;
          temp[8]++;
          varToClause[mapa].push_back(clause.size());
        }
        
        neg = 0;
        break;
      }
    }

    int val[4];
    for(int i = 0; i < 4; i++){
      val[i] = 0;
    }

    if(horn && fnc){
      while(!unitPos.empty() && sat){
        int varAt = *(unitPos.begin());
        unitPos.erase(varAt);
        val[varAt/2] = 1;
        for(int i = 0; i < varToClause[varAt].size(); i++){
          clause[varToClause[varAt][i]][8] = -1;
        }
        for(int i = 0; i < varToClause[varAt+1].size(); i++){
          if(clause[varToClause[varAt+1][i]][8] == -1)
            continue;         
          clause[varToClause[varAt+1][i]][8]--;
          if(clause[varToClause[varAt+1][i]][8] == 0)
            sat = false;
          if(clause[varToClause[varAt+1][i]][8] == 1){
            for(int j = 0; j < 8; j += 2){
              if(clause[varToClause[varAt+1][i]][j] > 0)
                unitPos.insert(j);
            }
          }
        }
      }
    }

    printf("Problema #%d\n", prob);
    if(!fnc){
      printf("Não está na FNC.\n\n");
    }
    else if(!horn){
      printf("Nem todas as cláusulas são de Horn.\n\n");
    }
    else if (sat){
      printf("Sim, é satisfatível.\n\n");
      //printf("Valoração verdade: {v(P) = %d, v(Q) = %d, v(R) = %d, v(S) = %d}\n", val[0], val[1], val[2], val[3]);
    }
    else{
      printf("Não, não é satisfatível.\n\n");
    }
  }
}