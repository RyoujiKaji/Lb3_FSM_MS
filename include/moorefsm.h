#ifndef MOOREFSM_H
#define MOOREFSM_H

#include <vector>

class MooreFSM {
public:
    MooreFSM(){}
    MooreFSM(const std::vector<std::vector<int>>& trans,
             const std::vector<int>& outs, int currentState)
        : trans(trans), outs(outs), currentState(currentState) {}

    // Переход на следующее состояние
    void makeStep(int x){
        if(x >= 0 && trans.size() > x) currentState = trans[x][currentState];
    }

    // Геттеры для текущих данных
    int getCurrentState() const {return currentState;}
    int getCurrentOutput() const {return outs[currentState];}

    void reset() { currentState = 0; }

private:
    // Таблица переходов
    std::vector<std::vector<int>> trans = {
        {2, 0, 3, 1},
        {0, 1, 2, 2},
        {0, 3, 1, 3},
        {1, 2, 0, 3},
        {3, 0, 2, 0}
    };

    // Вектор выходов
    std::vector<int> outs = {
        0,
        1,
        1,
        0
    };

    // Текущее состояние
    int currentState = 0;
};


#endif // MOOREFSM_H
