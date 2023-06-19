#include <bits/stdc++.h>
#include <fstream>

using namespace std;

#define pb push_back
#define vc vector
#define FOR(i,m,n) for(int i = m; i < n; i++)

//general varriables
string t[3][3] = {"**", "**","**", "**","**", "**","**", "**","**"};
string p1Beads = "1B2B3B1B2B3B", p2Beads = "1R2R3R1R2R3R";
string p1,p2;
int finished = 0 , turn = 1, flag1 = 0;

//void for showing live table
void table(string a[3][3]){
  if(flag1) system("CLS");
  flag1++;
  cout << "Current table : " << endl << char(201);
  FOR(i,0,14) cout << char(205);
  cout << char(187) << endl << char(186);
  FOR(j,0,3){
    FOR(i,0,3) cout << " " << t[j][i][0] << t[j][i][1] << " " << char(186);
    if(j != 2)cout << endl << char(186);
    else cout << endl << char(200);
    if(j != 2)FOR(i,0,14) cout << char(205);
    else{ FOR(i,0,14) cout << char(205); cout << char(188) << endl;}
    if(j != 2)cout << char(186);
    if(j!=2)cout << endl << char(186);
  }
  cout << "player " << p1 << "'s beads :";
  for(int i =0 ; i < p1Beads.size(); i+=2){
    FOR(j,i,i+2) cout << p1Beads[j]; cout << " ";
  }
  cout << endl << "player " << p2 << "'s beads :";
    for(int i =0 ; i < p2Beads.size(); i+=2){
    FOR(j,i,i+2) cout << p2Beads[j]; cout << " ";
  }
  cout << endl << endl;
}
//exit check
void choke(string a){ if(a == "exit") exit (EXIT_FAILURE); }

//win check(checks if the game is ended) (inputs : table)
bool check(string t[3][3]){
  FOR(i,0,3) if(t[i][0][1] == t[i][1][1] and t[i][0][1] == t[i][2][1] and t[i][0][0] != '*') return 1;
  FOR(i,0,3) if(t[0][i][1] == t[1][i][1] and t[0][i][1] == t[2][i][1] and t[0][i][0] != '*' and t[1][i][0] != '*') return 1;
  if((t[0][0][1] == t[1][1][1] and t[0][0][1] == t[2][2][1] and t[2][2][1] != '*') or (t[1][1][1] == t[0][2][1] and t[0][2][1] == t[2][0][1] and t[1][1][1] != '*')) return 1;
  return 0;
}
//undo option (coordinates)
void shoke(int a, int b){
  if(t[a][b][1] == 'B'){
    p1Beads += t[a][b][0];
    p1Beads += t[a][b][1];
  }
  else {
    p2Beads += t[a][b][0];
    p2Beads += t[a][b][1];
  }
  t[a][b][0] = t[a][b][2];
  t[a][b][1] = t[a][b][3];
  t[a][b][2] = t[a][b][4];
  t[a][b][3] = t[a][b][5];
  t[a][b][4] = '*';
  t[a][b][5] = '*';
}

//file control (inputs : usernames, flag)
void file(string n, string m,int aa){
  int emt1,emt2, c = 0;
  fstream File;
  string a,b;
  File.open("data.txt", ios::in);
  while(File >> a) b += a;
  vc<string> r;
  FOR(i,0,b.size()){
    string q;
    if(b[i] == ':' and isdigit(b[i+1])){
      if(c == 0) FOR(j,c,i) q +=b[j];
      else FOR(j,c+1,i) q +=b[j];
      r.pb(q);
      c = i+2;
    } //exporting file's content
  }
  File.close();
    File.open("data.txt", ios::out);
    File << b; //importing file's content
    if((!count(r.begin(), r.end(), n) or !count(r.begin(), r.end(), m)) and aa){ // adding new usernames
      if(turn%2 ==1) File << "\n" << n << ":" << 1 << ":" << m << ":" << 0 << ":";
      else File << "\n" << n << ":" << 0 << ":" << m << ":" << 1 << ":";
      File.close();
    }
    else if(!aa and count(r.begin(), r.end(), n) and count(r.begin(), r.end(), m)){ // exporting players match history
    FOR(i,0,b.size()){
      FOR(j,0,n.size()){
        if(b[j+i] != n[j]) break;
        else if(j == n.size() - 1){
          emt1 = b[i+j+2] -'0';
        }
      }
    }
    string qqq;
    FOR(i,0,b.size()){
      FOR(j,0,m.size()){
        if(b[j+i] != m[j]) break;
        else if(j == m.size() - 1){
          emt2 = b[i+j+2] -'0';
          }
      }
    }
    cout << "These players have already played together" << endl << n << " : " << emt1 << endl << m << " : " << emt2 << endl;
    if(emt2 > emt1){ turn++; cout << "since player " << m << " has more wins, he starts the game!" << endl;}
    else if(emt1 == emt2) cout << "player " << n << "and player " << m << "are equal in winning history, so player " << n << " starts the game" << endl;
    else cout << "since player " << n << " has more wins, he starts the game!" << endl << endl;
    }
    else if(aa and count(r.begin(), r.end(), n) and count(r.begin(), r.end(), m)){
      File.close();
      string last,h;
      File.open("data.txt", ios::in);
      while(File >> last){
        h += last;
      }
      File.close();
      File.open("data.txt", ios::out);
      if(turn % 2){  // updating scores
        FOR(i,0,h.size()){
          FOR(j,0,n.size()){
            if(h[j+i] != n[j]) break;
            else if(j == n.size() - 1){
              int yy = h[i+j+2] -'0' + 1;
              h[i+j+2] = to_string(yy)[0];
              File << h;
              File.close();
            }
          }
        }
      }
      else{
        FOR(i,0,h.size()){  // updating scores
          FOR(j,0,m.size()){
            if(h[j+i] != m[j]) break;
            else if(j == m.size() - 1){
              int yy = h[i+j+2] -'0' + 1;
              h[i+j+2] = to_string(yy)[0];
              File << h;
              File.close();
            }
          }
        }
      }
    }
  }

// showing the winner (inputs : usernames)
void win(string n, string m){
  string a;
  a = (turn % 2) ? n : m;
  table(t);
  FOR(i,0,22- 1 + a.size()) cout << char(178);
  cout << endl << char(178);
   FOR(i,0,20 - 1 + a.size()) cout << char(177);
   cout << char(178) << endl << " " << char(178);
   cout << a << " is the Winner!!!" << char(178) << endl;
  cout << char(178);
  FOR(i,0,20- 1 + a.size()) cout << char(177); cout << char(178) << endl;
    FOR(i,0,22- 1 + a.size()) cout << char(178);
    cout << endl << endl << char(204) << "\033[1;31m Writed By Mahdi Porheydari && Rozhan Alvandi :>> \033[0m" << char(185) << endl;
  file(n,m,1);
  finished = 12;
}
// void for adding a bead into a empty spot (inputs : current bead's coordinate, it's new spot coordinate, bead name, usernames)
void change(int a, int b, string c, string q, string qq){
  t[a][b] = c[0];
  t[a][b] += c[1];
  if(check(t)) win(q,qq);
}

// void for moving a bead on board to another spot (inputs : current bead's coordinate, it's new spot coordinate, bead name, usernames)
void add1(int a, int b, int c, int d, string e, string f){
  reverse(t[c][d].begin(), t[c][d].end());
  t[c][d] += t[a][b][1];
  t[c][d] += t[a][b][0];
  if(t[a][b].size() == 4 or (t[a][b].size() == 6 and t[a][b][4] == '*')){
  t[a][b][0] = t[a][b][2];
  t[a][b][1] = t[a][b][3];
  t[a][b][2] = '*';
  t[a][b][3] = '*';
  }
  else if(t[a][b].size() > 3){
  t[a][b][0] = t[a][b][2];
  t[a][b][1] = t[a][b][3];
  t[a][b][2] = t[a][b][4];
  t[a][b][3] = t[a][b][5];
  t[a][b][4] = '*';
  t[a][b][5] = '*';
  }
  else if(t[a][b].size() == 2) {
  t[a][b] = "**";
  }
  reverse(t[c][d].begin(), t[c][d].end());
  turn += 1;
  table(t);
  if(check(t)) win(e,f);
}
// void for putting a bead on another bead (inputs : destination coordinates, bead name, usernames)
void add(int a,int b, string s, string q, string qq){
  reverse(t[a][b].begin(), t[a][b].end());
  t[a][b] += s[1];
  t[a][b] += s[0];
  reverse(t[a][b].begin(), t[a][b].end());
    if(check(t)) win(q,qq);
}

// void for player movements (inputs : usernames)
void mp(string n,string m){
  if(turn == 1) cout << "player " << n << " starts with a blue bead and player " << m << " starts with a red bead" << endl;
  if(turn % 2) cout << "Player "<< n << ",It's your turn make your move : ";
  else cout << "Player "<< m << ", It's your turn make your move : " << endl;
  string s;
  getline(cin,s);
  if(s == "skip"){ turn++; return; }
  if(s[0] == 'u' and s[1] == 'n' and s[2] == 'd' and s[3] == 'o' and isdigit(s[5]) and isdigit(s[7])){
      if(t[s[5] - '0' - 1][s[7] - '0' - 1] == "**"){ cout << "this spot is empty!" << endl; return;}
      else{ shoke(s[5] - '0' - 1,s[7] - '0' - 1); turn -= 1 ;table(t);return;}
  }
  else if(s == "exit") choke(s);
  else if(s[0] == 'f' and s[1] == 'r' and s[2] == 'o' and s[3] == 'm' and s[9] == 't' and s[10] == 'o' and s[5] - '0' < 4 and s[7] - '0' < 4 and s[12] - '0' < 4 and s[14] - '0' < 4){
    if(turn % 2 and t[s[5] - '0' -1][s[7] - '0' -1][1] != 'B'){ cout << "It's not your turn to make move." << endl; return;}
    else if(!(turn % 2) and t[s[5] - '0' -1][s[7] - '0' -1][1] != 'R'){ cout << "It's not your turn to make move." << endl; return;}
    else if(t[s[5] - '0' -1][s[7] - '0' -1][0] > t[s[12] - '0' -1][s[14]-'0' -1 ][0]){
    add1(s[5] - '0' -1, s[7] - '0' -1, s[12] - '0' -1, s[14] - '0' -1, n, m);
    return;
    }
    else{ cout << "you can't move your bead to this spot, please trry again : " << endl;
    return; }
  }
  if(turn % 2){
    if(s.size() != 6){cout << "Your movement format is wrong. here is an example for right format of movement : (1R 1 1)/ (from 1 1 to 1 2) " << endl; return;}
    if(count(p1Beads.begin(), p1Beads.end(), s[0]) == 0 or count(p1Beads.begin(), p1Beads.end(), s[1]) == 0){
      cout << "You don't have such a bead. please try again : " << endl;
      return;
    }
    else if(s.size() != 6){
      cout << "Your movement format is wrong. here is an example for right format of movement : (1B 1 1)/ (from 1 1 to 1 2) " << endl;
      return;
    }
    else if(count(p1Beads.begin(), p1Beads.end(), s[1]) >= 1 and count(p1Beads.begin(), p1Beads.end(), s[0]) >= 1 and s[3] - '0' < 4 and s[5] - '0' < 4 ){
      string tr;
      tr += s[0];
      tr += s[1];
        if(t[s[3] - '0' -1][s[5] - '0'-1] != "**" and t[s[3] - '0' -1][s[5]  - '0' -1][0] - '0' >= s[0] - '0'){
          cout << "This spot is already full and unchangable! Try again : " << endl;
          return;
        }
        else if(t[s[3]  - '0' -1][s[5]  - '0' -1][0] - '0' < s[0] - '0') {
          add(s[3]  - '0' -1 , s[5]  - '0' -1 , tr, n,m);
          FOR(i,0,12) if(p1Beads[i] == tr[0] and p1Beads[i+1] == tr[1]) { p1Beads[i] = ' '; p1Beads[i+1] = ' '; break;}
          if(!finished)table(t);
          turn += 1;
        }
        else{
          change(s[3] - '0' -1, s[5] - '0' -1, tr, n,m);
          FOR(i,0,12) if(p1Beads[i] == tr[0] and p1Beads[i+1] == tr[1]) { p1Beads[i] = ' '; p1Beads[i+1] = ' '; break;}
          if(!finished)table(t);
          turn += 1;
        }
    }
    else if(s[3] -'0' > 3 or s[5] -'0' > 3) cout << "the maximum column number is 3!" << endl;
    }
  else{
    if(s.size() != 6){cout << "Your movement format is wrong. here is an example for right format of movement : (1R 1 1)/ (from 1 1 to 1 2) " << endl; return;}
    if(count(p2Beads.begin(), p2Beads.end(), s[0]) == 0 or count(p2Beads.begin(), p2Beads.end(), s[1]) == 0){
      cout << "You don't have such a bead. please try again : " << endl;
      return;
    }
    else if(s.size() != 6){
      cout << "Your movement format is wrong. here is an example for right format of movement : (1B 1 1)/ (from 1 1 to 1 2) " << endl;
      return;
    }
    else if(count(p2Beads.begin(), p2Beads.end(), s[1]) >= 1 and count(p2Beads.begin(), p2Beads.end(), s[0]) >= 1 and s[3] - '0' < 4 and s[5] - '0' < 4 ){
      string tr;
      tr += s[0];
      tr += s[1];
        if(t[s[3] - '0' -1][s[5] - '0'-1] != "**" and t[s[3] - '0' -1][s[5]  - '0' -1][0] - '0' >= s[0] - '0'){
          cout << "This spot is already full and unchangable! Try again : " << endl;
          return;
        }
        else if(t[s[3]  - '0' -1][s[5]  - '0' -1][0] - '0' < s[0] - '0') {
          add(s[3]  - '0' -1 , s[5]  - '0' -1 , tr, n,m);
          FOR(i,0,12) if(p2Beads[i] == tr[0] and p2Beads[i+1] == tr[1]) { p2Beads[i] = ' '; p2Beads[i+1] = ' '; break;}
          if(!finished)table(t);
          turn += 1;
        }
        else{
          change(s[3] - '0' -1, s[5] - '0' -1, tr, n,m);
          FOR(i,0,12) if(p2Beads[i] == tr[0] and p2Beads[i+1] == tr[1]) { p2Beads[i] = ' '; p2Beads[i+1] = ' '; break;}
          if(!finished)table(t);
          turn += 1;
        }
    }
    else if(s[3] -'0' > 3 or s[5] -'0' > 3) cout << "the maximum column number is 3!" << endl;
  }

}

int main(){
  cout << "Welcome to an advanced XO game, here you can challenge yourselves by playing this game : " << endl;
  cout << "if you need to check this game's rules and tutorial enter 'help' otherwise you can start the game by entering 'start' : " << endl;
  string gg;
  getline(cin,gg);
  choke(gg);
  if(gg == "help"){
    cout << endl << "this game is almost the same game as the famous XO game, but here every player has 3 types of beads (2 of each) which they can choose to play with." << endl;
    cout << "you shall enter your move in this format : 'bead size''bead type' 'x' 'y' which x and y are a 3*3 matrix numbers." << endl;
    cout << "bead names are B and R which you can choose which to start with, thus an example of a correct move would be '1R 1 1' " << endl;
    cout << "after every move you can undo your move by entering 'undo'' 'x' 'y' which x and y should point the spot you want to clear" << endl;
    cout << "in every turn a player can skip their move by entering 'skip' " << endl;
    cout << "(except if the move is the last move before someone wins)." << endl;
    cout << "for moving a bead which has already been played, you shall enter your movement in this format : 'from' 'x' 'y' 'to' 'p' 'z' " << endl;
    cout << "which in, x and y are matrix numbers of the bead you wish to move and p and z are the new numbers for the bead you're going to move" << endl;
    cout << "be aware that you only can move a bead to another place only if it's empty or there's a lower bead in the mentioned spot" << endl;
    cout << "turns changes after every move and 2 players keep playing until one of them is the winner." << endl;
    cout << "in every part of the game you can end the game and close it by entering 'exit'. " << endl;
  }
  gg = "start";
  if(gg == "start"){
    cout << endl << "Please enter your usernames below :" << endl << "Player No.1 : ";
    getline(cin,p1);
    choke(p1);
    system("CLS");
    cout << "Player No.2 : ";
    getline(cin,p2);
    while(p2 == p1){ cout << "This username has already been taken, please try another : "; getline(cin,p2); }
    system("cls");
    file(p1,p2,0);
    choke(p2);
    table(t);
    while(1){
      if(finished == 12) return 0;
      mp(p1,p2);
      if(finished == 12) return 0;
    }
  }
}