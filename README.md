# cub3D
Cub3D is a recreation of the classic game using the C programming language and the Raycasting technique.

# Features
. 3D environment on a 2D screen
. Movement
. Wall collisions
. Textures
. Minimap
. Rotate the point of view with the mouse

# Installation
1 - Clone or download the repository
2 - Navigate to the project directory
3 - Run 'make' to compile the game

# Usage

To run the game, use the following command:
        
        ./cub3D [map_file]
where map_file is the path to the map file to be used.

# Map Format

The map file should be a plain text file with the following format:

          NO [texture_path]
          SO [texture_path]
          WE [texture_path]
          EA [texture_path]
          S [texture_path]
          F [color]
          C [color]

          [map]

where:

   . NO, SO, WE, EA: North, South, West, East textures (optional)
   . S: Sprite texture (optional)
   . F: Floor color (required)
   . C: Ceiling color (required)
   . map: Map data (required)
   
The map data should be a grid of characters representing the different elements in the game world:

  0: Empty space
  1: Wall
  N,S,W,E : player

# Controls
  . W/A/S/D: Move forward/left/backward/right
  
# Raycasting

raycasting technique to render walls in a 3D environment. The 'cast_hrzntal_rays' and 'cast_vrtcal_rays' functions are responsible for casting the rays and calculating the intersection points with the horizontal and vertical walls, respectively. The 'searchto_wall_hrzntl' and 'searchto_wall_vrtcl' functions then search for the walls along the rays until they reach the end of the map or intersect with a wall. The resulting intersection points are used to determine the visibility and appearance of the walls on the screen
# DDA

the DDA (Digital Differential Analyzer) algorithm to draw a line between two points in a 2D environment. The 'dda' function takes in the 'cub' structure (which contains the necessary information for the program), the starting x and y coordinates, and calculates the distance between the two points. It then determines the number of steps needed to draw the line and calculates the increment in x and y coordinates for each step. Finally, it iterates over the number of steps and draws the line on the screen using the 'my_mlx_pixel_put' function.

<img width="1016" alt="Screen Shot 2022-11-30 at 9 09 32 PM" src="https://user-images.githubusercontent.com/69278312/204899162-1ef6833b-7261-4f4c-ad0c-411c21f1606d.png">
