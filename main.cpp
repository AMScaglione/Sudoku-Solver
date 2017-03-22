#include <iostream>

using namespace std;

class suBoard{
    private:
        int vals [9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0}};
        int presetVals [9][9]; //after the preset values are added, they are copied to here so clear() doesn't clear them as well
        void clear();
    public:
        //prints the grid in an organized fashion
        void print();
        bool addVal(int num, int row, int col);
        bool checkRow(int num, int row);
        bool checkCol(int num, int col);
        bool checkGrid(int num, int row, int col);
        void populate();
        bool solve();


};

int main()
{
    suBoard sudoku;
    sudoku.print();

    char query = 'n';
    do{
        sudoku.populate();
        std::cout << "Is this the board you want? y/n: ";
        std::cin >> query;
        std::cout << std::endl;
    }while(query != 'y');

    sudoku.solve();

    return 0;
}


//prints the grid in an organized fashion
void suBoard::print(){
    for(int i = 0; i < 9; ++i){
        if(i%3 == 0)
            std::cout << "+---------+---------+---------+" << std::endl;
        for(int j = 0; j < 9; ++j){
            if(j%3 == 0)
                std::cout << "|";
            if(vals[i][j] == 0)
                std::cout << "[" << " " << "]";
            else
                std::cout << "[" << vals[i][j] << "]";
            if(j == 8)
                std::cout << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "+---------+---------+---------+" << std::endl;
}
//attempts to add the value to the grid
//takes the value, and the position
//returns true if it was added, otherwise false
bool suBoard::addVal(int num, int row, int col){

    if(!checkRow(num, row) && !checkCol(num, col) && !checkGrid(num, row, col)){
        vals[row][col] = num;
        std::cout << "value added" << std::endl;
        return true;
    }
    std::cout << "value not added" << std::endl;
    return false;
}
//checks if value is already in the row its in
//takes index of row
//returns true if it finds num
bool suBoard::checkRow(int num, int row){
    for(int i = 0; i < 9; ++i){
        if(vals[row][i] == num)
            return true;
    }
    return false;
}
//checks if value is already in the column its in
//takes index of column
//returns true if it finds num
bool suBoard::checkCol(int num, int col){
    for(int i = 0; i < 9; ++i){
        if(vals[i][col] == num)
            return true;
    }
    return false;
}
//checks if value is already in the 3x3 grid its in
//takes the location of the top left value of grid
//returns true if it finds num
bool suBoard::checkGrid(int num, int row, int col){
    row = row - row%3;
    col = col - col%3;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(vals[i+row][j+col] == num)
                return true;
        }
    }
    return false;
}
//asks the user to fill in the already given answers
void suBoard::populate(){
    int tempVal = 0; //temporarily holds the value for input
    std::cout << "Type in the values given in each square one at a time." << std::endl;
    for(int i = 0; i < 81; ++i){
        do{
            std::cout << "Enter the next value, 0 to skip, or -1 to finish: ";
            std::cin >> tempVal;
            std::cout << std::endl;
            if(tempVal == 0) //skips on no input
                break;
            if(tempVal == -1)
                return;
        }while(!addVal(tempVal, i/9, i%9));
        print();
        tempVal = 0;
    }
}
//recursively solves the tree by checking numbers one by one and backtracking
//if it finds a failed space
bool suBoard::solve(){
    int row = 0;
    int col = 0;
    for(int i = 0; i <= 81; ++i){ //searches for an open spot. Could probably do this by
        if(i == 81){              //keeping track of the space, but I'm lazy
            return true; //if it reaches the end, that means the puzzle is solved
            std::cout << "Success!" << std::endl;
        }
        row = i/9;
        col = i%9;
        if(vals[row][col] == 0)
            break;
    }
    for (int i = 1; i <= 9; i++){
        if (!checkRow(i, row) && !checkCol(i, col) && !checkGrid(i, row, col)){
            vals[row][col] = i;
            print();
            if (solve()){ //base case
                return true;
            }
            vals[row][col] = 0;
        }
    }
    return false;
}
