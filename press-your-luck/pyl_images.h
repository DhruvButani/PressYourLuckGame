/**
 * @file pyl_images.h
 * @author jkrachey@wisc.edu
 * @brief 
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __PYL_IMAGES_H__
#define __PYL_IMAGES_H__

#include <stdint.h>
#include <stdbool.h>

#include "drivers/io-lcd.h"

#define NUM_IMAGES      10
#define NUM_SQUARES     14

/* Define the Y coordinate of each of the 4 rows */
#define IMAGE_COORD_Y_ROW_0        29 
#define IMAGE_COORD_Y_ROW_1        89 
#define IMAGE_COORD_Y_ROW_2        149 
#define IMAGE_COORD_Y_ROW_3        209 

/* Define the X coordinate of each of the 5 columns */
#define IMAGE_COORD_X_COL_0       39
#define IMAGE_COORD_X_COL_1       99 
#define IMAGE_COORD_X_COL_2       159 
#define IMAGE_COORD_X_COL_3       219
#define IMAGE_COORD_X_COL_4       279

/* Define the Center of the Game Over Image */
#define IMAGE_COORD_X_GAME_OVER   160
#define IMAGE_COORD_Y_GAME_OVER   150 

/* Define the size of the Whammy Bitmap */
#define IMG_BITMAP_HEIGHT_WHAMMY    37
#define IMG_BITMAP_WIDTH_WHAMMY     43 

/* Define the size of the Game Over Bitmap */
#define IMG_BITMAP_HEIGHT_GAME_OVER 47
#define IMG_BITMAP_WIDTH_GAME_OVER  91

/* Define the size of non-Whammy squares */
#define IMG_BITMAP_HEIGHT           50
#define IMG_BITMAP_WIDTH            50

/* Define the size of an empty square */
#define IMG_SQUARE_OUTER_HEIGHT     56
#define IMG_SQUARE_OUTER_WIDTH      56
#define IMG_SQUARE_INNER_HEIGHT     50
#define IMG_SQUARE_INNER_WIDTH      50

/* Data structure that holds the width, height, and offset of 
 * each of the font numbers 
 */
typedef struct {
    uint8_t w_px;
    uint8_t h_px;
    uint16_t index;
} Font_LUT;


/******************************************************************************
 * The enumerated types and structs that follow are used to store data
 * used to display images on the LCD.
 *****************************************************************************/ 

/* Define the supported types of images that can be displayed in a square */
typedef enum
{
    IMG_TYPE_WHAMMY = 0,
    IMG_TYPE_0100 = 1,
    IMG_TYPE_0250 = 2,
    IMG_TYPE_0500 = 3,
    IMG_TYPE_1000 = 4,
    IMG_TYPE_2500 = 5,
    IMG_TYPE_5000 = 6,
    IMG_TYPE_1000_PLUS_SPIN = 7,
    IMG_TYPE_2500_PLUS_SPIN = 8,
    IMG_TYPE_5000_PLUS_SPIN = 9,
    IMG_TYPE_INVALID = 10,
} image_type_t;

/* Data structure used to define the coordinates of an image*/
typedef struct coordinates_t
{
    uint16_t pos_x;
    uint16_t pos_y;
} coordinates_t ;

/* Data structure used to store the information about a square in the game board*/
typedef struct  image_t
{
    image_type_t image_type;            /* identifies the image type */
    const uint8_t *bitmap;              /* address of corresponding bitmap */
    uint16_t height;                    /* image height */
    uint16_t width;                     /* image width */
    uint16_t fcolor;                    /* image foreground color */
    uint16_t bcolor;                    /* image background color */
    uint16_t value;                     /* dollar amount added to total when selected */
    uint16_t spins;                     /* number of spins added to earned spins when selected */
    uint8_t square_id;                  /* identifies which game square to render the image */
    bool reset;                         /* if true, draw the bounding box, but erase the image*/
                                        /* if false, draw the bounding box and the iamge */
    bool invert_colors;                 /* if true, invert the foreground/background colors */
} image_t;

extern const uint8_t  IMG_BITMAP_GAME_OVER[];

/******************************************************************************
 * A lookup table that is used to return an image_t the corresponds to the 
 * bit map for a given image type. 
 * 
 * Example of initializing an image_t to contain information used to display a 
 * square with a value of $1000
 * 
 *      image_t image = IMG_INFO_LUT[IMG_TYPE_1000]; 
 *****************************************************************************/ 
extern const image_t IMG_INFO_LUT[];

/******************************************************************************
 * A lookup tabled used to determine the X,Y coordinates of a square.
 * 
 * Example of how to determine the coordinates of square 5 
 * 
 *      coordinate_t coordinates = IMG_COORD_LUT[5]; 
 *****************************************************************************/ 
extern coordinates_t IMG_COORD_LUT[];


/******************************************************************************
 * Bitmap images used to display numbers 0-9
 *****************************************************************************/ 
extern const uint8_t FONT_BITMAPS[];

/******************************************************************************
 * FONT lookup table used to display numbers 0-9 
 *****************************************************************************/ 
extern const Font_LUT FONT_DESC[];

#endif