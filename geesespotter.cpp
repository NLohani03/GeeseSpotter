#include "geesespotter_lib.h"

char * createBoard(std::size_t xdim, std::size_t ydim);
char * createBoard(std::size_t xdim, std::size_t ydim) { 
 
  char * new_array{new char [xdim*ydim]{} };

  for (int i{0}; i < xdim*ydim; ++i) { 
      new_array[i] = 0x00; 
  }
  return new_array; 
}

//done 
void hideBoard(char * board, std::size_t xdim, std::size_t ydim);
void hideBoard(char * board, std::size_t xdim, std::size_t ydim) { 
    
    for (int k{0}; k < xdim * ydim; ++k) { 
        board[k] |= hiddenBit();   
    }
}

void cleanBoard(char * board);
void cleanBoard(char * board) { 
   
    delete[] board; 
    board = nullptr;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim);
void printBoard(char * board, std::size_t xdim, std::size_t ydim) { 

    for (int i{0}; i < ydim; ++i) { 
        for (int j{0}; j < xdim; ++j) { 
            if (board[i*xdim + j] & markedBit()) { 
                std::cout<<'M'; 
            } else if ( board[i*xdim + j] & hiddenBit()) { 
                std::cout<<'*'; 
            } else { 
                std::cout<<char(board[i*xdim + j] + 48);
            }
        }
        std::cout<<std::endl;
    }
} 

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) { 
     
    if((board[yloc*xdim + xloc] & hiddenBit()) && ((!(board[yloc*xdim + xloc] & markedBit())))) { //mark
        board[yloc*xdim + xloc] = board[yloc*xdim + xloc] | markedBit(); 
    } else if ((!(board[yloc*xdim + xloc] & hiddenBit())) && ((board[yloc*xdim + xloc] | markedBit()))) { //if revealed 
        return 2; 
    } else if ((board[yloc*xdim + xloc] & hiddenBit()) && (board[yloc*xdim + xloc] & markedBit())) {  //unmark if already marked 
        board[yloc*xdim + xloc] = board[yloc*xdim + xloc] & (~markedBit());  
    } else  { 
        return 0; 
    }
   return 0; 
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){ //not done
   
   int index = yloc*xdim + xloc;
   
   
   if( (board[index] & markedBit()) > 0 ) { //it's marked
        return 1; 
   }else if ((board[index] & 0b0001111) == 0b0001001) {  
       board[index] = board[index] &~ hiddenBit(); 
       return 9; 
    } 

    if ((board[index] & hiddenBit()) == 0 ) { 
        return 2; 
    } else { 
        board[index] = board[index] &~ hiddenBit(); 
    }

    
    if ((board[index]) == 0 ) { 
       for (int i{-1}; i <= 1; ++i) {
            for (int j{-1}; j <= 1; ++j){
                int index_1 = index + xdim*i+ j;
                int xloc = index%xdim; 
                int yloc = index/xdim;
                    if (((xloc + j) >= 0) && ((xloc + j) < xdim)) {
                        if (((yloc + i) >= 0) && ((yloc + i) < ydim)) {
                        if (((board[(index_1)]) != 9)) { 
                            board[index_1] = board[index_1] &~ hiddenBit(); 
                        }  
                    }
                }   
            }
        } 
    } else { 
       board[index] &= valueMask(); 
   }
    return 0;
}


void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim)  { 
   //try to find 9 in the board 
   
    for (int position{}; position < xdim*ydim; ++position) { 
        int xloc = position%xdim; 
        int yloc = position/xdim; 

        int xdim_1 = int(xdim); 
        int ydim_1 = int(ydim);

        if (board[position] == 9) { 
            for (int i{-1}; i <= 1; ++i) { //y
                for (int j{-1}; j <= 1; ++j){ //x  
                    if ((board[position + xdim_1*i + j] & valueMask()) == 0x09 ) { 
                    } else {  
                        if ( ((xloc + j >= 0) && (xloc + j < xdim)) && ((yloc + i >= 0) && (yloc + i < ydim)) ) { 
                            board[position + xdim_1*i + j] += 1;
                        } 
                    }   
                }
            }
        }
    }
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim) { //i think its done 

    for (int i{0}; i < xdim*ydim; ++i) { 
        if ((board[i] & hiddenBit()) && ((board[i] & valueMask()) != 0x09)) { 
            return false; 
        } 
    }
   return true;
}
