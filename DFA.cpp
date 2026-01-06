#include <iostream>
#include <string>
#include <map>
using namespace std;

bool isAccepted(string input) {

    enum State {
        S0, S1, S2, S3, S4, S5, S6, S7, DEAD
    };

    map<pair<State, char>, State> dtran;

    dtran[{S0, 'b'}] = S1;
    dtran[{S1, 'a'}] = S0;
    dtran[{S1, 'b'}] = S1;
    dtran[{S0, 'a'}] = S2;
    dtran[{S2, 'a'}] = S2;
    dtran[{S2, 'b'}] = S3;
    dtran[{S3, 'a'}] = S4;
    dtran[{S4, 'a'}] = S2;
    dtran[{S4, 'b'}] = S2;

    State currentState = S0;

    for (char c : input) {
        if (dtran.count({currentState, c})) {
            currentState = dtran[{currentState, c}];
        } else {
            currentState = DEAD;
            break;
        }
    }


    return (currentState == S2);
}

int main() {
    string str;
    cout << "Enter string: ";
    cin >> str;

    if (isAccepted(str)) {
        cout << "Result: ACCEPTED" << endl;
    } else {
        cout << "Result: REJECTED" << endl;
    }

    return 0;
}
