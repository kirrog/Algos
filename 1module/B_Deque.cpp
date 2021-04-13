
#include <cstdio>
#include <iostream>
#include <stack>
#include <deque>

std::deque<int> readNesting(int *anim, bool *impossible, int *animIn) {
    std::stack<char> stack;
    int animBefore = 0;
    std::deque<int> order;
    char nextChar;
    int innerChars = 0;
    bool situationNesting = false;



    while ((nextChar = std::cin.peek()) != EOF) {
        if(*anim == 32){
            int i = 32;
            i--;
        }
        if (innerChars == 0) {
            stack.push(nextChar);
            if ((int) nextChar > 96) {
                (*anim)++;
            }
            std::cin.get();
            innerChars++;
            continue;
        }
        int compare = ((int) nextChar) - ((int) stack.top());
        if (compare == -32) {//next trap
            order.push_back(*anim - animBefore++);
            stack.pop();
            std::cin.get();
            innerChars--;
            situationNesting = true;
        } else if (compare == 32) {//next anim
            order.push_front(++(*anim));
            animBefore++;
            stack.pop();
            std::cin.get();
            innerChars--;
            situationNesting = true;
        } else {
            if (situationNesting) {
                int inAnim = 0;
                std::deque<int> norder = readNesting(anim, impossible, &inAnim);
                animBefore += inAnim;
                order.insert(order.end(), norder.begin(), norder.end());
            } else {
                stack.push(nextChar);
                if ((int) nextChar > 96) {
                    (*anim)++;
                }
                std::cin.get();
                innerChars++;
            }
        }
        if (innerChars == 0) {
            break;
        }
    }

    if (innerChars > 0) {
        *impossible = true;
    }

    *animIn = animBefore;

    return order;
}

int main() {
    int anim = 0;
    bool impossible = false;

    std::deque<int> order;
    while (std::cin.peek() != EOF) {
        int n = 0;
        std::deque<int> norder = readNesting(&anim, &impossible, &n);
        order.insert(order.end(), norder.begin(), norder.end());
    }

    if (impossible) {
        printf("Impossible");
    } else {
        printf("Possible\n");
        for (int i = 0; i < order.size();) {
            printf("%d ", order[0]);
            order.pop_front();
        }
    }

    return 0;
}