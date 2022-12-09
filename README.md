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
  

<img width="1016" alt="Screen Shot 2022-11-30 at 9 09 32 PM" src="https://user-images.githubusercontent.com/69278312/204899162-1ef6833b-7261-4f4c-ad0c-411c21f1606d.png">
