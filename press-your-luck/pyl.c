/**
 * @file pyl.c
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "pyl.h"
#include "io-lcd.h"
#include "pyl_images.h"

static inline void pyl_images_randomize_remaining(image_t *images);
static inline void pyl_images_randomize_spins(image_t *images, uint8_t num_spins);
static inline void pyl_images_randomize_whammies(image_t *images, uint8_t num_whammies);

/******************************************************************************
 * STAFF SUPPLIED FUNCTIONS - DO NOT EDIT                                     *
 ******************************************************************************/

/**
 * @brief 
 * Returns a random image that includes a dollar amount plus a spin
 * @return image_type_t 
 */
static inline image_type_t pyl_images_get_random_spin(void)
{
  uint8_t rand_num;

  rand_num = cyhal_trng_generate(&trng_obj) % 3;

  if (rand_num == 0)
  {
    return IMG_TYPE_1000_PLUS_SPIN;
  }
  else if (rand_num == 1)
  {
    return IMG_TYPE_2500_PLUS_SPIN;
  }
  else
  {
    return IMG_TYPE_5000_PLUS_SPIN;
  }
}

/**
 * @brief 
 * Sets all of the fields in the array of images to 0
 * @param images 
 */
static inline void pyl_images_reset(image_t *images)
{
  for (int i = 0; i < NUM_SQUARES; i++)
  {
    memset(&images[i], 0, sizeof(image_t));
    images[i].image_type = IMG_TYPE_INVALID;
  }
}

/**
 * @brief 
 *  Prints out a single decimal number at the specified coordinates.  
 * @param num 
 *      Number to Print
 * @param x
 *      X coordinate 
 * @param y 
 *      Y coordinate
 * @param fcolor 
 *      Foreground color
 * @param bcolor 
 *      Background color
 */
static void pyl_print_number(uint8_t num, uint16_t x, uint16_t y, uint16_t fcolor, uint16_t bcolor)
{
    uint32_t bitmap_addr = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    /* Verify num is a number from 0-9 OR the ASCII character ':' */
    if( ((num >= 0) && ( num <= 9)) || (num == 58) )
    {
        /* If num is a ':', then we need to change the index into the LUT to be 10*/
        if(num == 58)
        {
            num = 10;
        }

        /* Get the height of the bitmap from the Font Look Up Table */
        height = FONT_DESC[num].h_px;

        /* Get the width of the bitmap from the Font Look Up Table */
        width = FONT_DESC[num].w_px;

        /* Get the address of the bitmap from the Font Look Up Table */
        bitmap_addr = (uint32_t)(&FONT_BITMAPS[FONT_DESC[num].index]);

        lcd_draw_image(x, y, width, height, (const uint8_t *)bitmap_addr, fcolor, bcolor);
    }
}

/**
 * @brief 
 * Prints out a 2-digit number based on the value in num
 * @param num
 * number to print
 * @param x
 * X coordinate to print the image 
 * @param y 
 * Y coordinate to print the image 
 * @param fcolor 
 * Foreground color
 * @param bcolor
 * Background color 
 */
void pyl_print_digits_2(uint32_t num, uint16_t x, uint16_t y, uint16_t fcolor, uint16_t bcolor)
{
    char num_string[3];

    if( num > 99)
    {
        return;
    }

    /*format the number as a 2-digit string*/
    sprintf(num_string,"%02d",(int)num);

    /* Print out the numbers 1-digit at a time*/
    for(int i = 0; i < 2; i++)
    {
        pyl_print_number(num_string[i]-0x30, x, y, fcolor, bcolor);
        x = x + 15;
    }


}

/**
 * @brief 
 * Prints out a 6-digit number based on the value in num
 * @param num
 * number to print
 * @param x
 * X coordinate to print the image 
 * @param y 
 * Y coordinate to print the image 
 * @param fcolor 
 * Foreground color
 * @param bcolor
 * Background color 
 */
void pyl_print_digits_6(uint32_t num, uint16_t x, uint16_t y, uint16_t fcolor, uint16_t bcolor)
{
    char num_string[7];

    if( num > 999999)
    {
        return;
    }

    /*format the number as a 6-digit string*/
    sprintf(num_string,"%06d",(int)num);

    /* Print out the numbers 1-digit at a time*/
    for(int i = 0; i < 6; i++)
    {
        pyl_print_number(num_string[i]-0x30, x, y, fcolor, bcolor);
        x = x + 15;
    }
}

/**
 * @brief 
 * Randomizes the images at each of the 14 locations on the game board.
 *
 * A minimum of 3 locations contain whammies.  
 * A maximum of 3 locations contain a dollar amount an a spin 
 *
 * @param images 
 */
void pyl_images_randomize(image_t *images)
{
    /* Clear all of the images*/
    pyl_images_reset(images);

    /* Set a minimum of 3 locations to Whammies*/
    pyl_images_randomize_whammies(images,3);

    /* Set a minimum of 3 locations to a dollar amount that 
     * includes a spin
     */
    pyl_images_randomize_spins(images,3);

    /* Randomize the remaining squares to include only
     * dollar amounts WITHOUT spins or a whammy
     */
    pyl_images_randomize_remaining(images); 
}


/******************************************************************************
 * STUDENT DEFINED FUNCTIONS                                                  *
 ******************************************************************************/

/**
 * @brief 
 * Draws an empty square at the location defined by the square_id.  
 *
 * The squares will be generated by drawing two squares centered at the same
 * X and Y coordinates.  The outer square will use IMG_SQUARE_OUTER_HEIGHT and
 * IMG_SQUARE_OUTER_WIDTH to determine the dimensions of the square.
 *
 * The inner square will use IMG_SQUARE_INNER_HEIGHT and IMG_SQUARE_INNER_WIDTH
 * to determine the dimensions of the square.
 *
 * Use square_id as an index into the IMG_COORD_LUT[] look up table to determine 
 * the X and Y coordinates for a given square. 
 *
 * Example of how to determine the coordinates of square 5 
 * 
 *   coordinates_t coordinates = IMG_COORD_LUT[5];
 *
 * Use void lcd_draw_rectangle_centered() from io-lcd.c to draw the squares on
 * the LCD. 
 *
 * @param square_id 
 */
void pyl_draw_square(uint8_t square_id) 
{

  coordinates_t coordinates = IMG_COORD_LUT[square_id];
  int x = coordinates.pos_x;
  int y = coordinates.pos_y;

  
  //draw outer square
  lcd_draw_rectangle_centered(x,y,IMG_SQUARE_OUTER_HEIGHT,IMG_SQUARE_OUTER_WIDTH,LCD_COLOR_RED);
  lcd_draw_rectangle_centered(x,y,IMG_SQUARE_INNER_HEIGHT,IMG_SQUARE_INNER_WIDTH,LCD_COLOR_BLACK);

}


/**
 * @brief 
 * Draws the image on the game board.
 *
 * You will first draw an inner square using IMG_SQUARE_INNER_HEIGHT and 
 * IMG_SQUARE_INNER_WIDTH to determine the dimensions of the square.
 * 
 * Next, you will draw the image specified by the image_t pointer passed into the
 * function.
 *
 * Use void lcd_draw_image() from io-lcd.c to draw the image.  Use the fields
 * provided by the image_t pointer to determine the the address of the bitmap, 
 * image width, image height, foreground color, and background color. You should
 * assume that all of the fields of the struct have been set to valid values.  
 *
 * If the invert_colors field of the image_t pointer is set to true, swap the 
 * foreground and background colors prior to drawing the square and the image.
 *
 * Use image->square_id as an index into the IMG_COORD_LUT[] look up table to 
 * determine the X and Y coordinates for the square and the image. 
 *
 * Example of how to determine the coordinates of square 
 *
 *  coordinates_t coordinates = IMG_COORD_LUT[image->square_id];
 *
 * @param image 
 */

void pyl_draw_image(image_t *image) 
{

  //redraw draw inner square from image->square_id
  coordinates_t coordinates = IMG_COORD_LUT[image->square_id];
  int x = coordinates.pos_x;
  int y = coordinates.pos_y;

  //base square
  pyl_draw_square(image->square_id);

  //if invert_colors is true, draw image with inverted colors
  if(image->invert_colors == true) {
    lcd_draw_image(x,y,image->width,image->height,image->bitmap,image->bcolor,image->fcolor);
  }

  //if invert_colors is false, draw image with normal colors
  else {
    lcd_draw_image(x,y,image->width,image->height,image->bitmap,image->fcolor,image->bcolor);
  }
  
}


/**
 * @brief 
 * Examine all 14 squares in the image_t array.  Any square that has a type 
 * of IMG_TYPE_INVALID will be randomly set to one of the following image 
 * types: 
 *
 *    IMG_TYPE_WHAMMY
 *    IMG_TYPE_0100
 *    IMG_TYPE_0250
 *    IMG_TYPE_0500
 *    IMG_TYPE_1000
 *    IMG_TYPE_2500
 *    IMG_TYPE_5000
 *
 * Below are examples of how you can initialize an image in an 
 * array of image_t structs.
 * 
 *      image[0] = IMG_INFO_LUT[IMG_TYPE_0100];  // Set Square 0 to $100
 *
 *      rand_image_type = cyhal_trng_generate(&trng_obj) % 7;
 *      image[i] = IMG_INFO_LUT[rand_image_type];
 * 
 * @param images 
 * Address of the image_t array
 */

static inline void pyl_images_randomize_remaining(image_t *images)
{

  // Out of remaining squares, set them to random image type
  for(int i = 0; i < NUM_SQUARES; i++) {
    if(images[i].image_type == IMG_TYPE_INVALID) {

      image_type_t type = cyhal_trng_generate(&trng_obj) % 7;
      images[i] = IMG_INFO_LUT[type];
    }
  }
}

/**
 * @brief 
 * Initializes an array of image_t structs to contains a configurable number
 * of dollar amounts that include an additional spin. The location of each
 * dollar amount plus a spin is randomly assigned.
 * 
 * Only squares that have a type of IMG_TYPE_INVALID can be set to one of the 
 * following image types: 
 *
 *  IMG_TYPE_1000_PLUS_SPIN
 *  IMG_TYPE_2500_PLUS_SPIN
 *  IMG_TYPE_5000_PLUS_SPIN
 *
 * Below is an example of how you can initialize an image in an 
 * array of image_t structs.
 *
 *      image_type_t img_type = pyl_images_get_random_spin();
 *      image[i] = IMG_INFO_LUT[img_type];
 *
 * @param images 
 * Address of the image_t array
 * @param num_spins 
 * Number of squares that MUST contains a dollar amount plus a spin
 */
static inline void pyl_images_randomize_spins(image_t *images, uint8_t num_spins)
{

  //generate at least random amount of indexes to a number with extra spin
  
  while(num_spins>0) {
      int index = cyhal_trng_generate(&trng_obj) % NUM_SQUARES;
      
      if(images[index].image_type == IMG_TYPE_INVALID) {
        image_type_t type = pyl_images_get_random_spin();
        images[index] = IMG_INFO_LUT[type];
        num_spins--;
      }

  }  
}

/**
 * @brief 
 * Initializes an array of image_t structs to contains a configurable number
 * of whammies in random squares. The location of each whammy is assigned
 * randomly.
 *
 * Only squares that have a type of IMG_TYPE_INVALID can be set to one of the 
 * following image types: 
 *
 *  IMG_TYPE_WHAMMY
 *
 * @param images
 * Address of the image_t array
 * @param num_whammies 
 * Number of squares that MUST contains a whammy
 */

static inline void pyl_images_randomize_whammies(image_t *images, uint8_t num_whammies)
{

  //generate at least 3 indexes of images array to whammy

  while(num_whammies>0) {
      int index = (cyhal_trng_generate(&trng_obj) % NUM_SQUARES);
      
      if(images[index].image_type == IMG_TYPE_INVALID) {
        images[index] = IMG_INFO_LUT[IMG_TYPE_WHAMMY];
        num_whammies--;
      }

    }
}


/******************************************************************************
 * END STUDENT DEFINED FUNCTIONS 
 ******************************************************************************/

