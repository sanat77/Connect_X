/////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THESE CONSTANTS
const int INVALID_GAME = -1;
const int TIE = 1;
const int MAX_BOARD_SIZE = 1024;
/////////////////////////////////////////////////////////////////////////////


// vertical_check(arr[], width, height, length) checks if elements in the array are equal upto length vertically
//Required: arr[] is defined
//          width, height, length are positive integers
static bool vertical_check(const char arr[], const int width, const int height, const int length) {
	bool return_val = false;
	for (int pos = 0; pos < width*height; ++pos) {
		for (int i = 0; i < length-1; ++i) {
			if (arr[pos + i*width] == arr[pos + (i+1)*width] && arr[pos+(i+1)*width] != 0) {
//        printf("arr at i: %c\n", arr[pos + i*width]);
//        printf("arr at i+1: %c\n", arr[pos + (i+1)*width]);
				return_val = true;
			} else {
				return_val = false;
				break;
			}
		}
		if (return_val) {
//			printf("vertical_check gave true\n");
//      printf("Printing array: %c %c %c %c %c %c %c\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
			return true;
		}
	}
//	printf("vertical_check gave false\n");
	return false;
}


// horizontal_check(arr[], width, height, length) checks if elements in the array are equal upto length horizontally
//Required: arr[] is defined
//          width, height, length are positive integers
static bool horizontal_check(const char arr[], const int width, const int height, const int length) {
	bool return_val = false;
	for (int pos = 0; pos < width*height; ++pos) {
		if (pos%width > width-length) {
			continue;
		}
		for (int i = 0; i < length-1; ++i) {
			if (arr[pos + i] == arr[pos + (i+1)] && arr[pos + i] != 0) {
				return_val = true;
			} else {
				return_val = false;
				break;
			}
		}
		if (return_val) {
//      printf("horizontal_check gave true\n");
//      printf("Printing array: %c %c %c %c %c %c %c\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
			return true;
		}
	}
//	printf("horizontal_check gave false\n");
	return false;
}


// diagonal_check(arr[], width, height, length) checks if elements in the array are equal upto length diagonally
//Required: arr[] is defined
//          width, height, length are positive integers
static bool diagonal_check(const char arr[], const int width, const int height, const int length) {
  bool return_val_left = false;
  bool return_val_right = false;
  const int diag_right = width+1;
  const int diag_left = width-1;
  for (int pos = 0; pos < width*height; ++pos) {
  	if (pos%width > width-length) { //left check
  		for (int i = 0; i < length-1; ++i) {
  			if (arr[pos + i*diag_left] == arr[pos + (i+1)*diag_left] && arr[pos + i*diag_left] != 0) {
//          printf("diagonal left absolute gave true pos: %d\n", pos);
  				return_val_left = true;
  			} else {
  				return_val_left = false;
  				break;
  			}
  		}
  	}
  	else if (pos%width < length-1) { //right check
  		for (int i = 0; i < length-1; ++i) {
  			if (arr[pos + i*diag_right] == arr[pos + (i+1)*diag_right] && arr[pos + i*diag_right] != 0) {
  				return_val_right = true;
//          printf("diagonal right absolute gave true pos: %d\n", pos);
  			} else {
  				return_val_right = false;
//          printf("diagonal right absolute gave false\n");
  				break;
  			}
  		}
  	}
  	else { //both
  		for (int i = 0; i < length-1; ++i) {
  			if (arr[pos + i*diag_left] == arr[pos + (i+1)*diag_left] && arr[pos + i*diag_left] != 0) {
  				return_val_left = true;
//          printf("diagonal left gave true pos: %d\n", pos);
  			} else {
  				return_val_left = false;
  				break;
  			}
  		}
  		for (int i = 0; i < length-1; ++i) {
  			if (arr[pos + i*diag_right] == arr[pos + (i+1)*diag_right] && arr[pos + i*diag_right] != 0) {
  				return_val_right = true;
//          printf("diagonal right gave true pos: %d\n", pos+i*diag_right);
  			} else {
  				return_val_right = false;
  				break;
  			}
  		}
  	}
  	if (return_val_left || return_val_right) {
//  		printf("diagonal_check gave true\n");
//      printf("Printing array: %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c 
//            %c %c %c %c %c %c %c %c %c\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9], arr[10], 
//            arr[11], arr[12], arr[13], arr[14], arr[15], arr[16], arr[17], arr[18], arr[19], arr[20], arr[21], arr[22], arr[23], 
//            arr[24], arr[25], arr[26], arr[27], arr[28], arr[29], arr[30], arr[31], arr[32], arr[33], arr[34], arr[35], arr[36], 
//            arr[37], arr[38], arr[39], arr[40], arr[41]);
  		return true;
  	}
  }
//  printf("diagonal_check gave false\n");
  return false;
}


//check_x(arr[], width, height, length) checks if any of vertical_check(), horizontal_check() or diagonal_check() gives true
//Required: arr[] is defined
//          width, height and length are positive integers
static bool check_x(const char arr[], const int width, const int height, const int length) {
  return (vertical_check(arr, width, height, length) || horizontal_check(arr, width, height, length) || diagonal_check(arr, width, height, length));
}



//connect_analysis(moves, width, height, length) analyzes a game of connect on a board of size (width x height) with the given [column] moves
//   and the player must get length in-a-row to win notes: returns TIE if the result is a tie after (width x height) moves returns INVALID_GAME 
//   if a column overflows or an invalid column (outside the range 0..width-1) occurs in moves before the game is won (elements of moves are 
//   ignored after a win) otherwise, returns the winning move #:
//          +x if player #1 wins on move #x
//          -x if player #2 wins on move #x
//   move #1 is made by player #1 and is stored in moves[0]
// Required: moves is an array of length (width x height) [not asserted]
//           2 < width, height
//           width x height <= MAX_BOARD_SIZE
//           2 < length <= max(width, height)
int connect_analysis(const int moves[], int width, int height, int length) {
  int count = 0;
  int pos = 0;
  int num = 0;
  bool answer = false;
  char new_arr[1024] = {0};  // null array
  for (int i = 0; i < width*height; ++i) {
    num = moves[i];
//    printf("num: %d\n", num);
    if (num < 0) {
//      printf("tying to print num: %d\n", num);
      return INVALID_GAME;
    }
    for (int j = 0; j < i; ++j) {
      if (moves[j] == num) {
        ++count;
      }
    }
    pos = num + count*width;
//    printf("%d\n", pos);
    // invalid position output here
    if (num >= width || pos >= width*height) {
      return INVALID_GAME;
    }
    if (i%2 == 0) {
      new_arr[pos] = 'Y';
//      printf("Y called %d, pos: %d\n", num, pos);
    } else {
      new_arr[pos] = 'R';
//      printf("R called %d, pos: %d\n", num, pos);
    }
//    printf("char array: %c/n", new_arr[pos]);
    count = 0;
    
    answer = check_x(new_arr, width, height, length);
//    printf("Answer is: %d\n", answer);
    
    //answer if not tie at the moment
    if (answer) {
      if (new_arr[pos] == 'Y') {
        return (i+1);
      } else if (new_arr[pos] == 'R') {
        return -(i+1);
      }
    }
  }
  //if tie
  return TIE;
}




int main(void) {

  int player1_wins_move_7[42] = {1, 2, 1, 2, 1, 2, 1};
  int player2_wins_move_8[42] = {0, 1, 0, 1, 0, 1, 3, 1};
  int invalid_game1[42] = {0};
  int invalid_game2[42] = {-1};
  int tie1[42] = {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 6, 6,
                  2, 3, 2, 3, 3, 2, 3, 2, 2, 3, 2, 3, 6, 6,
                  4, 5, 4, 5, 5, 4, 5, 4, 4, 5, 4, 5, 6, 6};

//  printf("%d\n", connect_analysis(player2_wins_move_8, 7, 6, 4));
//  printf("%d\n", connect_analysis(player1_wins_move_7, 7, 6, 4));
//  printf("%d\n", connect_analysis(invalid_game1, 7, 6, 4));
//  printf("%d\n", connect_analysis(invalid_game2, 7, 6, 4));
//  printf("%d\n", connect_analysis(tie1, 7, 6, 4));
//  trace_2d(tie1, 7, 6, 4);
  
//  trace_2d(player1_wins_move_7, 7, 6);
  assert(connect_analysis(player1_wins_move_7, 7, 6, 4) == 7);
  assert(connect_analysis(player2_wins_move_8, 7, 6, 4) == -8);
  assert(connect_analysis(invalid_game1, 7, 6, 4) == INVALID_GAME);
  assert(connect_analysis(invalid_game2, 7, 6, 4) == INVALID_GAME);
  assert(connect_analysis(tie1, 7, 6, 4) == TIE);


  int col1[9] = {0, 1, 2, 1, 0, 2, 0};
  assert(connect_analysis(col1, 3, 3, 3) == 7);
  
  int col2[9] = {0, 1, 2, 1, 0, 1, 0};
  assert(connect_analysis(col2, 3, 3, 3) == -6);
  
  int col3[9] = {0, 2, 0, 2, 1, 2};
  assert(connect_analysis(col3, 3, 3, 3) == -6);
  
  int row1[9] = {0, 0, 1, 1, 2, 2};
  assert(connect_analysis(row1, 3, 3, 3) == 5);
  
  int row2[9] = {0, 1, 2, 0, 0, 1, 1, 2, 2};
  assert(connect_analysis(row2, 3, 3, 3) == -8);
  
  int row3[9] = {1, 0, 0, 1, 0, 2, 1, 2, 2};
  assert(connect_analysis(row3, 3, 3, 3) == 9);
  
  int diag1[9] = {2, 1, 1, 0, 0, 2, 0};
  assert(connect_analysis(diag1, 3, 3, 3) == 7);
  
  int diag2[9] = {1, 1, 2, 0, 2, 2};
  assert(connect_analysis(diag2, 3, 3, 3) == -6);
}
