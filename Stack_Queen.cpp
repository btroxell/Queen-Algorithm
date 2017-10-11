#include <iostream>
#include <stack>

/*
runtime analysis,
Best Case: the amount will be an odd number with the exception of 3, it will have very little pops because of the odd one being safe
and only have to go through at O(n^2) with the main while and either the for loop in check column or while loop in check diagonals.

Worst Case: it is an even number where the backtrack function will have to shift and check until each previous queen is safe. While it is still at O(n^2)
as the input gets larger for even numbers the runtime increases. it will max at n^3 because it will either have to check the column and diagonal in the
while loop, but not both.

*/

using namespace std;

class Queen{
private:

  int row;
  int column;

public:

    Queen();
    Queen(int row, int column);
    ~Queen();
    int getRow();
    int getColumn();



};//end queen class


Queen::Queen(){//queens no arg contructor

    Queen::row = 0;//sets the queens default row to 0
    Queen::column = 0;//sets the queens default column to 0

}//end queen no args constructor


Queen::Queen(int row, int column){//queens contructor to take the given row and column

    Queen::row = row; //gives queen whatever row
    Queen::column = column; //gives gueen whatever column

}//end queen contructor

Queen::~Queen(){

}//end queen deconstructor

int Queen::getRow(){

    return row;//allows row to be used elsewhere

}//end get row

int Queen::getColumn(){

    return column;//allows column to be used elsewhere

}//end get column

bool checkColumn(stack<Queen> *q, Queen QnArrParam[], int filled){
    //cout << "in checkColumn, current position of queen on top of stack: " << q->top().getRow() << ", " << q->top().getColumn() << endl;
    filled = filled + 1;//current size of stack when passed through checkcolumn (filled will be 1 less)
    //cout << FAmnt << endl;
    bool conflict = false;//assume that there is no conflict
    for(int i=filled; i>1; i--){//decrements through array starting at the filled + 1, which is the stack size
      //cout << "in checkColumn, current position of the previous queen: " << QnArrParam[i-2].getRow() << ", " << QnArrParam[i-2].getColumn() << endl;
      if(q->top().getColumn() == QnArrParam[i-2].getColumn() && q->top().getRow() != QnArrParam[i-2].getRow()){//if the queen on stack's and queen in array's rows are different and columns are the same
           conflict = true; // then there is a conflict
        }//end if
    }//end for
    //cout << "conflict in column: " << conflict << endl;
    return conflict;//use the boolean for later use
}//end bool check column

bool checkDiagonals(stack<Queen> *q, Queen QnArrParam[], int filled, int N){
    //cout << "in check diagonal" << endl;
    int col = q->top().getColumn();//store the column so it can be incremented
    int row = q->top().getRow();//store the row so it can be incremented
    //cout << "in check diagonal" << endl;
    bool conflict = false;//assume that there is no conflict
    while(col >= 0 && row >= 0){ //while the top queens column and row are greater than or equal to 0

        for(int i=0; i<filled; i++){ //go through the array
            if(col == QnArrParam[i].getColumn() && row == QnArrParam[i].getRow()){//queen on top of the stack has the same column
                    //cout << "in first condition check diag function" << endl;
                    conflict = true; // then there is a conflict
            }//end if
        }//end for loop
	col--; //decrement column for diagonal
	row--; //decrement row for diagonal
    }//end while
    col = q->top().getColumn(); // reset to the current queens column
    row = q->top().getRow(); // reset to the current queen's row
    //cout << "before check right diag: " << row << ", " << col << endl;
    while(col < N && row >= 0){ //go through the right diagonal as long as its on the board
        for(int i=0; i<filled; i++){ // go through filled array
            if(col == QnArrParam[i].getColumn() && row == QnArrParam[i].getRow()){//stacks queen compared to the filled array
                    conflict = true; // if true then there is a conflict
            }//end if
        }//end for
	col++; //increment column to go right
	row--; //decrement row to go down
    }//end while
    //cout << "conflict in diagonals: " << conflict << endl;
    return conflict;
}//end bool check diagonal


bool QnConflict(stack<Queen> *q, Queen QnArrParam[], int filled, int N){//makes comparison easier, it compares the checkcolumn and checkdiagonal in one function
    bool conflict; //create bool variable
    conflict = false; //assume there is no conflict
    if(checkColumn(q, QnArrParam, filled) || checkDiagonals(q, QnArrParam, filled, N)){ //compares using or operator, if either one is only false when both are false and true otherwise
        conflict = true;//there is a conflict
    }
    return conflict;//boolean for later use

}

int shiftCol(stack<Queen> *q, int filled, int col){//shifts the queen


    //cout << "in shift column, filled: " << filled << " column: " << col << endl;
    q->pop();//delete the top queen
    q->push(Queen(filled, col + 1));//replace with a shifted queen
    //cout << "shift " << filled <<", " <<  q->top().getColumn() << endl;


}//end shift queen function

void printQueens(stack<Queen> *q, int filled){//prints the queens out

    cout << "output: " << endl;//output
    for (int i=0; i<filled; i++){//go through stack
        cout << q->top().getRow() << "," << q->top().getColumn() << endl;//output stack queen
        q->pop();//delete the queen
    }//end for
}//end print queens





int main(){

    int N; //amount of queens
    cout << "Enter Amount of Queens" << endl;//starting output
    cin >> N;//use defined amount
    stack<Queen> qs;//creates a stack of type queen
    Queen queenArray[N];//create a queen array of size N
    int column=0;//column variable initialized
    int filled = 0;//filled counter initialized
    qs.push(Queen(0,0));//push first queen on
    queenArray[filled] = qs.top();//save that quuen to the array
    filled = filled + 1;//increase the filled counter
    bool keepgoing = true;//boolean variable for algorithm
    qs.push(Queen(filled, 0));//since first queen will be clear, push next queen on
    while(keepgoing){//queen sorter algoritm
      if(!QnConflict(&qs, queenArray, filled, N)){ //for the case that there is no conflict with the column and diagonals
            //cout << filled << endl;
            filled = filled + 1;//increase the filled counter by 1
            //cout << filled << endl;
            //cout << "stack size in first check " << qs.size() << endl;
            //cout << "row, column of each queen so far " << qs.top().getRow() << "," << qs.top().getColumn() << endl;
            if (filled == N){//if all the queens are on the board
                //cout << "filled = N" << filled << endl;
                keepgoing = false;//we are done
            }//end if
            else{//for the case that all the queens are not on the board
                //cout << "before top becomes saved to array: " << qs.top().getRow() << ", " << qs.top().getColumn() << endl;

                //cout << "after array gets saved in array: " << queenArray[filled].getRow() << ", " << queenArray[filled].getColumn() << endl;
                queenArray[filled - 1] = qs.top();//saves the top of the stack to the previous index of array
                column = 0;//reset the column
                qs.push(Queen(filled, column));//push a new next queen on the stack for later comparison
                queenArray[filled] = qs.top();//the previous queen in the array is the currently the top one
                //cout << "queen array sub[filled - 1] " << &queenArray[*filled] << endl;

            }//end else
        }//end if
        else if(QnConflict(&qs, queenArray, filled, N) && qs.top().getColumn() + 1 < N){//if there is a conflict and there is room to move
            //cout << "filled before shift: " << filled << endl;
            queenArray[filled] = qs.top();//save that to queen array
            shiftCol(&qs, filled, column);//shift the queen
            column ++;//increment column
        //queenArray[filled - 1] = qs.top();

        }//end else if
        else if(QnConflict(&qs, queenArray, filled, N) && qs.top().getColumn() + 1 >= N){//if there is not room to move
            cout << "pop: " << qs.top().getRow() << "," << qs.top().getColumn() << endl;//output what has been popped
            qs.pop();//pop the top element of stack
            //cout << "column in back track: " << column << endl;
            column = qs.top().getColumn();//store the top queens value to column
            //cout << "column in back track: " << column << endl;
            filled = filled - 1;//decrement counter since shifting for the queen under is about to happen

            //shiftCol(&qs, filled, column);
            if(column == N-1){//if the column is about to go off the board
                //cout << "column in back track if column == N: " << column << endl;
                cout << "pop: " << qs.top().getRow() << "," << qs.top().getColumn() << endl;//output what has been popped
                qs.pop();//pop top element
                column = qs.top().getColumn();//save the column of the current top element
                filled = filled -1;//decrement the filled counter
                shiftCol(&qs, filled, column);//shift the queen
            }//end if
            else{//if its not at the end
                //cout << "column in back track else: " << column << endl;
                shiftCol(&qs, filled, column);//shift the queen
            }//end else
            //cout << "filled after backtrack statement " << filled << endl;
        }//end else if
    }//end while
    printQueens(&qs, N);//print the queens
}//end main
