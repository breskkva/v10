
#include "ResourceAllocation.h"
#include "InterferenceGraph.h"
#include "Constants.h"
#include "Instruction.h"
#include <deque>
#include <iostream>
using namespace std;

bool doResourceAllocation(stack<Variable*>* simplificationStack, InterferenceGraph* ig) {

    int i, j, k;
    bool SMETNJA;
    deque<Regs> REGISTRI;
    deque<Regs>::iterator d_it;
    deque<Variable*> OBOJENI;
    deque<Variable*>::iterator v_it;
    Variable* VRH_STEKA;

    for (k = 0; k < __REG_NUMBER__ + 1; k++)
        REGISTRI.push_back((Regs)k);
    cout << "\nKoristimo registre:";
    for (k = 0; k < __REG_NUMBER__ + 1; k++)
        cout << " reg" << REGISTRI[k];
    cout << "." << endl << endl;

    // __REG_NUMBER__ je 3, ali ste na vezbama rekli da ih ima 4, zato sam gore stavio + 1
    // Znaci korisitmo registre reg0 reg1 i reg2 i reg3, oni i jesu definisani u enumeraciji

    while (!simplificationStack->empty()) {

        REGISTRI.clear();
        for (k = 0; k < __REG_NUMBER__ + 1; k++)
            REGISTRI.push_back((Regs)k);

        SMETNJA = false;
        VRH_STEKA = simplificationStack->top();
        cout << "\nTrenutno na vrhu steka " << VRH_STEKA->name << endl;

        for (v_it = OBOJENI.begin(); v_it != OBOJENI.end(); v_it++) {
            cout << "\nProverava ";
            cout << VRH_STEKA->name << " i ";
            cout << (*v_it)->name;
            cout << endl;
            i = VRH_STEKA->pos;
            j = (*v_it)->pos;
            // i i j su indexi matrice grafa smetnji

            if ((*ig).values[i][j] == __INTERFERENCE__) {
                if ((*v_it)->assigment != __UNDEFINE__)
                {
                    for (d_it = REGISTRI.begin(); d_it != REGISTRI.end(); ) {
                        if ((*d_it) == (*v_it)->assigment) {
                            d_it = REGISTRI.erase(d_it);
                        }
                        else {
                            d_it++;
                        }
                    }
                        
                }
            }
        }

        if (!REGISTRI.empty()) {
            VRH_STEKA->assigment = REGISTRI.front();
        }
        else return false;

        OBOJENI.push_back(VRH_STEKA);
        simplificationStack->pop();
    }
    cout << endl;
    return true;
}

Instructions* removeMove(Instructions* instrs)
{
    // ovo je dodatni zadatak

    Instructions::iterator i_it;

    for (i_it = instrs->begin(); i_it != instrs->end(); i_it++) {
        if ((*i_it)->type == T_MOVE) {
            if ((*i_it)->src1->assigment == (*i_it)->dst->assigment) {
                if ((*i_it)->src2 == NULL) {
                    instrs->remove(*i_it);
                    break;
                }
            }
        }
    }

    return instrs;

}