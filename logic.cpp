#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cout << "ERROR: unable to open: " << fileName << endl;
        return nullptr;                                             
    }
    //input info of the player
    ifs >> maxRow;
    ifs >> maxCol;
    ifs >> player.row;
    ifs >> player.col;

    if (ifs.fail() || maxRow < 1 || maxCol < 1 || maxRow > (INT32_MAX / maxRow) || player.row < 0 || player.row >= maxRow ||
        player.col < 0 || player.col >= maxCol || maxCol > (INT32_MAX / maxCol)) {
            return nullptr;
}
 char** dungeon = createMap(maxRow, maxCol);
    char current_tile = '\0';
    bool exit = false;
    int count = 0;
    int grid = maxRow * maxCol;
    int i = 0;
    int j = 0;

    for (i = 0; i < maxRow; ++i) {
        for (j = 0; j < maxCol; ++j) {
            ifs >> current_tile;

            if (ifs.eof()) {
                if (count < grid) {
                    deleteMap(dungeon, maxRow);
                    return nullptr;
                }
            }
            ++count;

            if (current_tile == TILE_DOOR) {
                dungeon[i][j] = current_tile;
                exit = true;
            } else if (current_tile == TILE_EXIT) {
                dungeon[i][j] = current_tile;
                exit = true;
            } else if (current_tile == TILE_OPEN) {
                dungeon[i][j] = current_tile;
            } else if (current_tile == TILE_PLAYER) {
                dungeon[i][j] = current_tile;
            } else if (current_tile == TILE_TREASURE) {
                dungeon[i][j] = current_tile;
            } else if (current_tile == TILE_AMULET) {
                dungeon[i][j] = current_tile;
            } else if (current_tile == TILE_MONSTER) {
                dungeon[i][j] = current_tile;
            } else if (current_tile == TILE_PILLAR) {
                dungeon[i][j] = current_tile;
            } else {
                deleteMap(dungeon, maxRow);
                return nullptr;
            }
        }
    }

    
   if(ifs >> current_tile){
    deleteMap(dungeon, maxRow);
        return nullptr;
   }
   if (ifs.peek() != EOF) {
        deleteMap(dungeon, maxRow);
        return nullptr;
    }

    if (!exit) {
        deleteMap(dungeon, maxRow);
        return nullptr;
    }

    dungeon[player.row][player.col] = TILE_PLAYER;

    return dungeon;
}


/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
     if (input == MOVE_RIGHT) {
        ++nextCol;
    }
    else if (input == MOVE_LEFT) {
        --nextCol;
    }
    else if (input == MOVE_UP) {
        --nextRow;
    }
    else if (input == MOVE_DOWN) {
        ++nextRow;
    }
    else {
        nextRow = nextRow;
        nextCol = nextCol;
    }
    
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char** current_tile = new char*[maxRow];
    char* curr;
    int i = 0;
    int j = 0;

    for (i = 0; i < maxRow; ++i) {
        curr = new char[maxCol];
        for (j = 0; j < maxCol; ++j) {
            curr[j] = TILE_OPEN; 
        }
        current_tile[i] = curr;
    }
    return current_tile;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    int i = 0;
                                        
    if (map) {
        for (i = 0; i < maxRow; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }

    map = nullptr;                         
    maxRow = 0; 
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
      int current_row;
    int current_col;
    int a = 0;
    int b = 0;

    if (map == nullptr || maxCol < 1 || maxRow < 1) {
        return nullptr;                                 
    }  

    int temp_row = 2 * maxRow;                    
    int temp_col = 2 * maxCol;

    char** temp_map = new char*[temp_row];
    char* current;

    int i = 0;
    for (i = 0; i < temp_row; ++i) {              
        current = new char[temp_col];
        temp_map[i] = current;
    }
    for (a = 0; a < maxRow; ++a) {
        for (b = 0; b < maxCol; ++b) {
            if (map[a][b] == 'o') {
                current_col = b;
                current_row = a;
            }
        }
    }
    map[current_row][current_col] = TILE_OPEN;

    for (a = 0; a < temp_row; ++a) {
        for (b = 0; b < temp_col; ++b) {
            temp_map[a][b] = map[a % maxRow][b % maxCol];
        }
    }

    temp_map[current_row][current_col] = 'o';

    deleteMap(map, maxRow);              
                                 
    maxRow = temp_row;            
    maxCol = temp_col;

    return temp_map;          
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
 if (nextCol >= maxCol || nextCol < 0) {
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    } else if (nextRow >= maxRow || nextRow < 0) {
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    } else if (map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER) {
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    } else if (map[nextRow][nextCol] == TILE_TREASURE) {
        player.treasure++;
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return 2;
    } else if (map[nextRow][nextCol] == TILE_AMULET) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return 3;
    } else if (map[nextRow][nextCol] == TILE_DOOR) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return 4;
    } else if (map[nextRow][nextCol] == TILE_EXIT) { 
        if(player.treasure >= 1){
            map[player.row][player.col] = TILE_OPEN;
            map[nextRow][nextCol] = TILE_PLAYER;
            player.row = nextRow;
            player.col = nextCol;
            return 5;
        }
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }
    
    map[player.row][player.col] = TILE_OPEN;
    map[nextRow][nextCol] = TILE_PLAYER;
    player.row = nextRow;
    player.col = nextCol;

    return 1;
    }

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    int i = 0;
    bool lifebar = false;
    
    for (i = player.row - 1; i >= 0; --i) {
        if (map[i][player.col] == TILE_MONSTER) {
            if (map[i + 1][player.col] == TILE_PLAYER) {
                map[i + 1][player.col] = TILE_MONSTER;
                map[i][player.col] = TILE_OPEN;
                lifebar = true;
            }
            map[i + 1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        } else if(map[i][player.col] == TILE_PILLAR) {
            break;
        }
    }

    for (i = player.row + 1; i < maxRow; ++i) {
        if (map[i][player.col] == TILE_MONSTER) {
            if (map[i - 1][player.col] == TILE_PLAYER) {
                map[i - 1][player.col] = TILE_MONSTER;
                map[i][player.col] = TILE_OPEN;
                lifebar = true;
            }
            map[i - 1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        } else if(map[i][player.col] == TILE_PILLAR) {
            break;
        }
    }
   
    for (i = player.col - 1; i >= 0; --i) {
        if (map[player.row][i] == TILE_MONSTER) {
            if (map[player.row][i + 1] == TILE_PLAYER) {
                map[player.row][i + 1] = TILE_MONSTER;
                map[player.row][i] = TILE_OPEN;
                lifebar = true;
            }
            map[player.row][i + 1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        } else if (map[player.row][i] == TILE_PILLAR) {
            break;
        }
    }
    
    for (i = player.col + 1; i < maxCol; ++i) {
        if (map[player.row][i] == TILE_MONSTER) {
            if(map[player.row][i - 1] == TILE_PLAYER) {
                map[player.row][i - 1] = TILE_MONSTER;
                map[player.row][i] = TILE_OPEN;
                lifebar = true;
            }
            map[player.row][i - 1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        } else if (map[player.row][i] == TILE_PILLAR) {
            break;
        }
    }
    return lifebar;
}
