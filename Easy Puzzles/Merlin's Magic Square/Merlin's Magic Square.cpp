// very very optimized version at the cost of it being unreadable

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int board{}, i{}, press;
    std::vector<int> toggles = {~0, 432, 448, 216, 292, 186, 73, 54, 7, 27};

    for (;i<9;++i) {
        board = board << 1 | !(getchar()>>6);
        getchar();
    }

    for (press = getchar(); ~press; press = getchar())
        board ^= toggles[press-'0'];

    auto addr = std::find(toggles.begin(), toggles.end(), board ^ 495);
    std::cout << addr-toggles.begin();
}
