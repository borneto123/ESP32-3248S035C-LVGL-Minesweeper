#ifndef _HELP_
#define _HELP_

/**
 * This struct is used to wrap x and y cordinates in 1 struct:
 * - `x` x position in grid in cordinates
 * - `y` y position in grid in cordinates
 */
struct cords{
    int x;
    int y;
};

/**
 * @brief Function that convert id from button matrix to cord struct
 * 
 * @param id id from button matrix
 * @param cols number of columns in grid
 * @return cords 
 */
cords help_convert_id_to_cordinates(int id,int cols);
#endif