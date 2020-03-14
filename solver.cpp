#include<bits/stdc++.h>
#define ll long long int
#define pii pair<int,int>
#define mod 1000000007
#define eps 0.000000001
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()
#define sz(x) ((int)x.size())
#define ln(x) ((int)x.length())
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const double PI = acos(-1.0);
using namespace std;

class CubeState
{
    //Slots are ordered anticlockwise
    //top 0 1 2 3, starting UBL
    //bottom layer 4 5 6 7, starting DFL
    int cornerSlot[8];

    //Slots are ordered anticlockwise
    //top 0 1 2 3, starting UL
    //middle 4 5 6 7, starting FL
    //bottom 8 9 10 11, starting DL
    int edgeSlot[12];

    // 0 is solved
    // 1 is twisted anticlockwise
    // 2 is twisted clockwise
    int cornerTwist[8];

    // 0 is correct
    // 1 in flipped
    int edgeTwist[12];
public:
    CubeState()
    {
        for(int i = 0; i < 8; i++)
            cornerSlot[i] = i, cornerTwist[i] = 0;
        for(int i = 0; i < 12; i++)
            edgeSlot[i] = i, edgeTwist[i] = 0;
    }
    CubeState(CubeState const &x)
    {
        for(int i = 0; i < 8; i++)
            cornerSlot[i] = x.cornerSlot[i], cornerTwist[i] = x.cornerTwist[i];
        for(int i = 0; i < 12; i++)
            edgeSlot[i] = x.edgeSlot[i], edgeTwist[i] = x.edgeTwist[i];
    }
    bool operator<(const CubeState &x) const
    {
        int s1 = 0, s2 = 0;
        for(int i = 0; i < 8; i++)
        {
            if(cornerSlot[i] == i)
                s1++;
            if(cornerTwist[i] == 0)
                s1++;
            if(x.cornerSlot[i] == i)
                s2++;
            if(x.cornerTwist[i] == 0)
                s2++;
        }
        for(int i = 0; i < 12; i++)
        {
            if(edgeSlot[i] == i)
                s1++;
            if(edgeTwist[i] == 0)
                s1++;
            if(x.edgeSlot[i] == i)
                s2++;
            if(x.edgeTwist[i] == 0)
                s2++;
        }
        return s1 < s2;
    }
    void halfTurn(vector<int> cs, vector<int> es)
    {
        // 4 corner cycle
        // cs[0]->cs[3]->cs[2]->cs[1]->cs[0]
        int s = cornerSlot[cs[0]];
        cornerSlot[cs[0]] = cornerSlot[cs[1]];
        cornerSlot[cs[1]] = cornerSlot[cs[2]];
        cornerSlot[cs[2]] = cornerSlot[cs[3]];
        cornerSlot[cs[3]] = s;
        s = cornerTwist[cs[0]];
        cornerTwist[cs[0]] = cornerTwist[cs[1]];
        cornerTwist[cs[1]] = cornerTwist[cs[2]];
        cornerTwist[cs[2]] = cornerTwist[cs[3]];
        cornerTwist[cs[3]] = s;

        //4 edge cycle
        //es[0]->es[3]->es[2]->es[1]->es[0]
        s = edgeSlot[es[0]];
        edgeSlot[es[0]] = edgeSlot[es[1]];
        edgeSlot[es[1]] = edgeSlot[es[2]];
        edgeSlot[es[2]] = edgeSlot[es[3]];
        edgeSlot[es[3]] = s;
        s = edgeTwist[es[0]];
        edgeTwist[es[0]] = edgeTwist[es[1]];
        edgeTwist[es[1]] = edgeTwist[es[2]];
        edgeTwist[es[2]] = edgeTwist[es[3]];
        edgeTwist[es[3]] = s;
    }
    void doubleTurn(vector<int> cs, vector<int> es)
    {
        // 2 swaps
        // cs[0] <-> cs[2]
        // cs[1] <-> cs[3]
        int s = cornerSlot[cs[0]];
        cornerSlot[cs[0]] = cornerSlot[cs[2]];
        cornerSlot[cs[2]] = s;
        s = cornerSlot[cs[1]];
        cornerSlot[cs[1]] = cornerSlot[cs[3]];
        cornerSlot[cs[3]] = s;
        s = cornerTwist[cs[0]];
        cornerTwist[cs[0]] = cornerTwist[cs[2]];
        cornerTwist[cs[2]] = s;
        s = cornerTwist[cs[1]];
        cornerTwist[cs[1]] = cornerTwist[cs[3]];
        cornerTwist[cs[3]] = s;

        // 2 swaps
        // es[0] <-> es[2]
        // es[1] <-> es[3]
        s = edgeSlot[es[0]];
        edgeSlot[es[0]] = edgeSlot[es[2]];
        edgeSlot[es[2]] = s;
        s = edgeSlot[es[1]];
        edgeSlot[es[1]] = edgeSlot[es[3]];
        edgeSlot[es[3]] = s;
        s = edgeTwist[es[0]];
        edgeTwist[es[0]] = edgeTwist[es[2]];
        edgeTwist[es[2]] = s;
        s = edgeTwist[es[1]];
        edgeTwist[es[1]] = edgeTwist[es[3]];
        edgeTwist[es[3]] = s;

    }
    void changeCornerOrientation(vector<int> slot)
    {
        vector<int> add = {1, -1, 1, -1};
        for(int i = 0; i < sz(slot); i++)
        {
            cornerTwist[slot[i]] = (cornerTwist[slot[i]] + add[i] + 3) % 3;
        }
    }
    void changeEdgeOrientation(vector<int> slot)
    {
        vector<int> add = {1, 1, 1, 1};
        for(int i = 0; i < sz(slot); i++)
        {
            edgeTwist[slot[i]] = (edgeTwist[slot[i]] + add[i]) % 2;
        }
    }
    void moveU()
    {
        //3->2->1->0->3
        //3->2->1->0->3
        this->halfTurn({0, 1, 2, 3}, {0, 1, 2, 3});
        //no change in twist
    }
    void moveUi()
    {
        //0->1->2->3->0
        //0->1->2->3->0
        this->halfTurn({3, 2, 1, 0}, {3, 2, 1, 0});
        //no change in twist
    }

    void moveU2()
    {
        //0<->2
        //1<->3
        //0<->2
        //1<->3
        this->doubleTurn({0, 1, 2, 3}, {0, 1, 2, 3});
        //no change in twist
    }
    void moveD()
    {
        //7->6->5->4->7
        //11->10->9->8->11
        this->halfTurn({4, 5, 6, 7}, {8, 9, 10, 11});
        //no change in twist
    }
    void moveDi()
    {
        //4->5->6->7->4
        //8->9->10->11->8
        this->halfTurn({7, 6, 5, 4}, {11, 10, 9, 8});
        //no change in twist
    }

    void moveD2()
    {
        //4<->6
        //5<->7
        //8 <-> 10
        //9 <-> 11
        this->doubleTurn({4, 5, 6, 7}, {8, 9, 10, 11});
        //no change in twist
    }
    void moveR()
    {
        //2->3->6->7->2
        //2->6->10->5->2
        this->halfTurn({7, 6, 3, 2}, {5, 10, 6, 2});
        this->changeCornerOrientation({2, 3, 6, 7});
    }
    void moveRi()
    {
        //3->2->7->6->3
        //6->2->5->10->6
        this->halfTurn({6, 7, 2, 3}, {2, 6, 10, 5});
        this->changeCornerOrientation({2, 3, 6, 7});
    }

    void moveR2()
    {
        //2<->6
        //3<->7
        //2<->10
        //5<->6
        this->doubleTurn({2, 3, 6, 7}, {5, 10, 6, 2});
        //no change in twist
    }

    void moveL()
    {
        //0->1->4->5->0
        //0->4->8->7->0
        this->halfTurn({5, 4, 1, 0}, {7, 8, 4, 0});
        this->changeCornerOrientation({0, 1, 4, 5});
    }
    void moveLi()
    {
        //1->0->5->4->1
        //4->0->7->8->4
        this->halfTurn({4, 5, 0, 1}, {0, 4, 8, 7});
        this->changeCornerOrientation({0, 1, 4, 5});
    }

    void moveL2()
    {
        //0<->4
        //1<->5
        //0<->8
        //4<->7
        this->doubleTurn({0, 1, 4, 5}, {7, 8, 4, 0});
        //no change in twist
    }

    void moveF()
    {
        //1->2->7->4->1
        //1->5->11->4->1
        this->halfTurn({4, 7, 2, 1}, {4, 11, 5, 1});
        this->changeCornerOrientation({1, 2, 7, 4});
        this->changeEdgeOrientation({4, 11, 5, 1});
    }
    void moveFi()
    {
        //2->1->4->7->2
        //5->1->4->11->5
        this->halfTurn({7, 4, 1, 2}, {1, 5, 11, 4});
        this->changeCornerOrientation({1, 2, 7, 4});
        this->changeEdgeOrientation({4, 11, 5, 1});
    }

    void moveF2()
    {
        //1<->7
        //2<->4
        //4<->5
        //1<->11
        this->doubleTurn({1, 2, 7, 4}, {4, 11, 5, 1});
        //no change in twist
    }

    void moveB()
    {
        //3->0->5->6->0
        //3->7->9->6->3
        this->halfTurn({6, 5, 0, 3}, {6, 9, 7, 3});
        this->changeCornerOrientation({3, 0, 5, 6});
        this->changeEdgeOrientation({3, 7, 9, 6});
    }
    void moveBi()
    {
        //6->5->0->3->6
        //7->3->6->9->7
        this->halfTurn({3, 0, 5, 6}, {3, 7, 9, 6});
        this->changeCornerOrientation({3, 0, 5, 6});
        this->changeEdgeOrientation({3, 7, 9, 6});
    }

    void moveB2()
    {
        //3<->5
        //0<->6
        //3<->9
        //7<->6
        this->doubleTurn({3, 0, 5, 6}, {6, 9, 7, 3});
        //no change in twist
    }
    vector<int> getCornerSlot()
    {
        return vector<int>(cornerSlot, cornerSlot + 8);
    }

    vector<int> getCornerTwist()
    {
        return vector<int>(cornerTwist, cornerTwist + 8);

    }
    void setCornerSlot(vector<int> v)
    {
        for(int i = 0; i < 8; i++)
            cornerSlot[i] = v[i];
    }

    void setCornerTwist(vector<int> v)
    {
        for(int i = 0; i < 8; i++)
            cornerTwist[i] = v[i];
    }
    vector<int> getEdgeSlot()
    {
        return vector<int>(edgeSlot, edgeSlot + 12);
    }

    vector<int> getEdgeTwist()
    {
        return vector<int>(edgeTwist, edgeTwist + 12);

    }
    void setEdgeSlot(vector<int> v)
    {
        for(int i = 0; i < 12; i++)
            edgeSlot[i] = v[i];
    }

    void setEdgeTwist(vector<int> v)
    {
        for(int i = 0; i < 12; i++)
            edgeTwist[i] = v[i];
    }
    vector<int> getStateForG1()
    {
        //Return array of EO
        return this->getEdgeTwist();
    }
    void setStateForG1(vector<int> v)
    {
        for(int i = 0; i < 12; i++)
            edgeTwist[i] = v[i];
    }
    vector<int> endStateForG1()
    {
        //Return array of EO
        return vector<int> (12, 0);
    }
    vector<int> getStateForG2()
    {
        //CO + middle layer
        vector<int> v;
        for(int i = 0; i < 8; i++)
            v.pb(cornerTwist[i]);
        for(int i = 4; i < 8; i++)
        {
            for(int j = 0; j < 12; j++)
            {
                if(edgeSlot[j] == i)
                    v.pb(j);
            }

        }
        return v;
    }
    void setStateForG2(vector<int> v)
    {
        for(int i = 0; i < 8; i++)
            cornerTwist[i] = v[i];
        vector<pii> rem;
        int c = 4, sw = 0;
        vector<int> vis;
        for(int i = 0; i < 12; i++)
            edgeSlot[i] = -1;
        for(int i = 8; i < 12; i++)
        {
            edgeSlot[v[i]] = c++;
        }
    }
    vector<int> endStateForG2()
    {
        //CO + middle layer
        vector<int> v(12, 0);
        for(int i = 8; i < 12; i++)
            v[i] = i - 4;
        return v;
    }
    void setStateForG3(vector<int> v)
    {
        for(int i = 0; i < 8; i++)
        {
            cornerSlot[i] = v[i];
        }
        for(int i = 8; i < 12; i++)
        {
            edgeSlot[i - 8] = v[i];
        }
        for(int i = 12; i < 16; i++)
        {
            edgeSlot[i - 4] = v[i];
        }
    }
    vector<int> endStateForG3()
    {
        //CP + EP
        vector<int> v(16);
        for(int i = 0; i < 20; i++)
            v[i] = i % 2;

        return v;
    }
    vector<int> getStateForG3()
    {
        //CP + EP relative
        vector<int> v;
        for(int i = 0; i < 8; i++)
            v.pb(cornerSlot[i] % 2);
        for(int i = 0; i < 4; i++)
            v.pb(edgeSlot[i] % 2);
        for(int i = 8; i < 12; i++)
            v.pb(edgeSlot[i] % 2);
        return v;
    }
    void setStateForG4(vector<int> v)
    {
        for(int i = 0; i < 8; i++)
        {
            cornerSlot[i] = v[i];
        }
        for(int i = 8; i < 20; i++)
        {
            edgeSlot[i - 8] = v[i];
        }
    }
    vector<int> endStateForG4()
    {
        //Solved corner and edges
        vector<int> v;
        for(int i = 0; i < 8; i++)
            v.pb(i);
        for(int i = 8; i < 20; i++)
            v.pb(i - 8);
        return v;
    }
    vector<int> getStateForG4()
    {
        vector<int> v;
        for(int i = 0; i < 8; i++)
            v.pb(cornerSlot[i]);
        for(int i = 0; i < 12; i++)
            v.pb(edgeSlot[i]);
        return v;
    }

    bool equal(CubeState *state)
    {
        bool f = true;
        for(int i = 0; i < 8; i++)
        {
            if(cornerSlot[i] != i || cornerTwist[i])
                f = false;
        }
        for(int i = 0; i < 12; i++)
        {
            if(edgeSlot[i] != i || edgeTwist[i])
                f = false;
        }
        return f;
    }
    void scramble(vector<string> &seq)
    {
        for(string x : seq)
        {
            if(x == "U")
                this->moveU();
            else if(x == "U'")
                this->moveUi();
            else if(x == "U2")
                this->moveU2();
            else if(x == "D")
                this->moveD();
            else if(x == "D'")
                this->moveDi();
            else if(x == "D2")
                this->moveD2();
            else if(x == "R")
                this->moveR();
            else if(x == "R'")
                this->moveRi();
            else if(x == "R2")
                this->moveR2();
            else if(x == "L")
                this->moveL();
            else if(x == "L'")
                this->moveLi();
            else if(x == "L2")
                this->moveL2();
            else if(x == "F")
                this->moveF();
            else if(x == "F'")
                this->moveFi();
            else if(x == "F2")
                this->moveF2();
            else if(x == "B")
                this->moveB();
            else if(x == "B'")
                this->moveBi();
            else if(x == "B2")
                this->moveB2();
        }
    }
};

typedef void (CubeState::*mov)();
typedef vector<int> (CubeState::*getStateParams)();
typedef void (CubeState::*setStateParams)(vector<int>);

vector<pair<mov, string>> moves(18);
vector<vector<int>> restrictedMove(5);
vector<getStateParams> getGState(5), endGState(5);
vector<setStateParams> setGState(5);
vector<vector<string>> s(5, vector<string>());

void init()
{
    moves[0]  = mp(&CubeState::moveU, "U");
    moves[1]  = mp(&CubeState::moveUi, "U'");
    moves[2]  = mp(&CubeState::moveU2, "U2");
    moves[3]  = mp(&CubeState::moveD, "D");
    moves[4]  = mp(&CubeState::moveDi, "D'");
    moves[5]  = mp(&CubeState::moveD2, "D2");
    moves[6]  = mp(&CubeState::moveR, "R");
    moves[7]  = mp(&CubeState::moveRi, "R'");
    moves[8]  = mp(&CubeState::moveR2, "R2");
    moves[9]  = mp(&CubeState::moveL, "L");
    moves[10] = mp(&CubeState::moveLi, "L'");
    moves[11] = mp(&CubeState::moveL2, "L2");
    moves[12] = mp(&CubeState::moveF, "F");
    moves[13] = mp(&CubeState::moveFi, "F'");
    moves[14] = mp(&CubeState::moveF2, "F2");
    moves[15] = mp(&CubeState::moveB, "B");
    moves[16] = mp(&CubeState::moveBi, "B'");
    moves[17] = mp(&CubeState::moveB2, "B2");

    getGState[0] = &CubeState::getStateForG1;
    endGState[0] = &CubeState::endStateForG1;
    setGState[0] = &CubeState::setStateForG1;
    restrictedMove[0] = vector<int>();

    getGState[1] = &CubeState::getStateForG2;
    endGState[1] = &CubeState::endStateForG2;
    setGState[1] = &CubeState::setStateForG2;
    restrictedMove[1] = {12, 13, 15, 16};

    getGState[2] = &CubeState::getStateForG3;
    endGState[2] = &CubeState::endStateForG3;
    setGState[2] = &CubeState::setStateForG3;
    restrictedMove[2] = {6, 7, 9, 10, 12, 13, 15, 16};

    getGState[3] = &CubeState::getStateForG4;
    endGState[3] = &CubeState::endStateForG4;
    setGState[3] = &CubeState::setStateForG4;
    restrictedMove[3] = {6, 7, 9, 10, 12, 13, 15, 16};

    // getGState[4] = &CubeState::getStateForG5;
    // endGState[4] = &CubeState::endStateForG5;
    // setGState[4] = &CubeState::setStateForG5;
    // restrictedMove[4] = {0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16};
}
int inverse(int move)
{
    int type = move % 3;
    if(type == 0)
        return move + 1;
    else if(type == 1)
        return move - 1;
    else
        return move;
}
map<vector<int>, bool> forw, backw;
map<vector<int>, vector<int>> forwMove, backwMove;

void bfs(CubeState *state, int phase)
{
    s[phase].clear();
    forw.clear();
    backw.clear();
    forwMove.clear(), backwMove.clear();
    queue<pair<vector<int>, int>> q;
    CubeState *end = new CubeState;
    // cout << "here";
    q.push(mp((*state.*getGState[phase])(), 1));
    q.push(mp((*end.*endGState[phase])(), 2));

    forw[(*state.*getGState[phase])()] = true;
    backw[(*end.*endGState[phase])()] = true;
    forwMove[(*state.*getGState[phase])()] = vector<int> ();
    backwMove[(*end.*endGState[phase])()] = vector<int> ();
    cout << "PHASE " << phase << " ";
    delete end;
    while(!q.empty())
    {
        // cout<<q.size()<<" ";
        pair<vector<int>, int> u = q.front();
        int dir = u.second;
        vector<int> soFar = (dir == 1 ? forwMove[u.first] : backwMove[u.first]);
        q.pop();
        for(int i = 0; i < sz(moves); i++)
        {
            if((sz(soFar) && ((soFar.back() / 6) == i / 6)) || binary_search(all(restrictedMove[phase]), i))
                continue;
            CubeState *cur = new CubeState;
            (*cur.*setGState[phase])(u.first);
            (*cur.*moves[i].first)();
            vector<int> v = (*cur.*getGState[phase])();
            delete cur;
            if(!forw[v] && !backw[v])
            {
                q.push(mp(v, dir));
                soFar.pb(i);
                if(dir == 1)
                {
                    forw[v] = true;
                    forwMove[v] = soFar;
                }
                else
                {
                    backw[v] = true;
                    backwMove[v] = soFar;
                }
                soFar.pop_back();
            }
            else if(forw[v] && dir == 2)
            {
                vector<int> mv1 = forwMove[v];
                cout << mv1.size() + soFar.size() + 1 << " moves" << endl;
                for(int x : mv1)
                    s[phase].pb(moves[x].second);
                s[phase].pb(moves[inverse(i)].second);
                for(int x = sz(soFar) - 1; x >= 0; x--)
                    s[phase].pb(moves[inverse(soFar[x])].second);
                queue<pair<vector<int>, int>> emp;
                swap(q, emp);
                break;
            }
            else if(backw[v] && dir == 1)
            {
                vector<int> mv2 = backwMove[v];
                cout << soFar.size() + 1 + mv2.size() << " moves" << endl;
                for(int x : soFar)
                    s[phase].pb(moves[x].second);
                s[phase].pb(moves[i].second);
                for(int x = sz(mv2) - 1; x >= 0; x--)
                    s[phase].pb(moves[inverse(mv2[x])].second);
                queue<pair<vector<int>, int>> emp;
                swap(q, emp);
                break;
            }
        }
    }
}

vector<string> solve(CubeState *state)
{
    vector<string> sol;
    int phase = 0;
    while(phase <= 3)
    {
        bfs(state, phase);
        for(string x : s[phase])
            sol.pb(x);
        state->scramble(s[phase]);
        phase++;
    }
    return sol;
}
int main()
{
    init();
    char str[200];
    // freopen("in", "r", stdin);
    // freopen("out", "w", stdout);
    gets(str);
    vector<string> scrambleSequence;
    string scrambleString(str);
    string temp;
    for(int i = 0; i < ln(scrambleString); i++)
    {
        if(scrambleString[i] == ' ')
            scrambleSequence.pb(temp), temp = "";
        else
            temp += scrambleString[i];
    }
    if(ln(temp))
        scrambleSequence.pb(temp);
    CubeState *state = new CubeState;
    state->scramble(scrambleSequence);
    for(string x : scrambleSequence)
        cout << x << " ";
    cout << endl;

    vector<string> sol = solve(state);
    CubeState *fin = new CubeState;
    if(state->equal(fin))
    {
        cout << "SOLVED: " << sz(sol) << " moves" << endl;
    }
    else
    {
        cout << "NOT SOLVED" << endl;
    }
    for(vector<string> x : s)
    {
        for(string xx : x)
            cout << xx << " ";
        cout << endl;
    }
    cout << endl;
    delete state;
    delete fin;
    return 0;
}