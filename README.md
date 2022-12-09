# cub3D
Cub3D is a recreation of the classic game using the C programming language and the Raycasting technique.

# Features
. 3D environment on a 2D screen
. Movement and shooting
. Wall collisions
. Textures
. Minimap

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

          R [width] [height]
          NO [texture_path]
          SO [texture_path]
          WE [texture_path]
          EA [texture_path]
          S [texture_path]
          F [color]
          C [color]

          [map]

where:

   . R: Resolution (required)
   . NO, SO, WE, EA: North, South, West, East textures (optional)
   . S: Sprite texture (optional)
   . F: Floor color (required)
   . C: Ceiling color (required)
   . map: Map data (required)
   
The map data should be a grid of characters representing the different elements in the game world:

  0: Empty space
  1: Wall
  2: Spawn point

# Controls
  . W/A/S/D: Move forward/left/backward/right
  . Left mouse button: Shoot
  
![big-o-cheat-sheet-poster](https://user-images.githubusercontent.com/69278312/205059606-19b2c005-b6d6-4c2a-9f94-4f124e30a047.png)


<img width="545" alt="Screen Shot 2022-11-19 at 3 20 12 PM" src="https://user-images.githubusercontent.com/69278312/203139979-c80e88ed-b02a-4111-ab78-29d2d484b31b.png">
<img width="689" alt="Screen Shot 2022-11-14 at 11 24 45 PM" src="https://user-images.githubusercontent.com/69278312/203140109-9ddd869d-3a2f-4a34-98cd-2fecc52aebcf.png">
<img width="1020" alt="Screen Shot 2022-11-20 at 11 33 21 AM" src="https://user-images.githubusercontent.com/69278312/203140125-ade7f73e-4ee8-4494-b2a3-176a460bd324.png">
<img width="1025" alt="Screen Shot 2022-11-21 at 7 07 03 PM" src="https://user-images.githubusercontent.com/69278312/203140136-b3b8adf6-1cc9-47ad-ae65-0714913eed3e.png">
<img width="1041" alt="Screen Shot 2022-11-21 at 5 47 59 PM" src="https://user-images.githubusercontent.com/69278312/203140145-2f9b7b9a-ddb9-4b7d-90bb-a336e26cf519.png">
<img width="695" alt="Screen Shot 2022-11-15 at 10 53 57 AM" src="https://user-images.githubusercontent.com/69278312/203140149-8647374d-1d5a-407c-aeac-7848fa00ab9a.png">
<img width="1025" alt="Screen Shot 2022-11-21 at 7 07 03 PM" src="https://user-images.githubusercontent.com/69278312/203394929-c106e890-21b9-4285-9859-4b1031ceb399.png">
<img width="1024" alt="Screen Shot 2022-11-22 at 7 21 08 PM" src="https://user-images.githubusercontent.com/69278312/203394947-ec715026-9c7a-419f-9019-0b5bf1188744.png">
<img width="1010" alt="Screen Shot 2022-11-22 at 7 43 22 PM" src="https://user-images.githubusercontent.com/69278312/203396275-b405e87a-b000-4ddc-8204-2a330303ce17.png">
<img width="1085" alt="Screen Shot 2022-11-24 at 6 43 47 PM" src="https://user-images.githubusercontent.com/69278312/203848733-23bddcf0-73ad-458e-9bee-b0481cba04fa.png">
<img width="1253" alt="Screen Shot 2022-11-24 at 7 20 58 PM" src="https://user-images.githubusercontent.com/69278312/203848737-40db42ef-e272-40de-b876-bba6e0f7ef5e.png">
<img width="699" alt="Screen Shot 2022-11-23 at 6 03 41 PM" src="https://user-images.githubusercontent.com/69278312/203848836-b6466283-c26f-4557-ab6a-b9640f38aa31.png">
<img width="451" alt="Screen Shot 2022-11-23 at 6 06 23 PM" src="https://user-images.githubusercontent.com/69278312/203848844-40131d3a-835b-4cab-9ad1-809e96f32cc6.png">
<img width="1031" alt="Screen Shot 2022-11-26 at 2 29 45 PM" src="https://user-images.githubusercontent.com/69278312/204091718-6ed37801-0e65-43b5-a3ce-902f758d3925.png">
<img width="1016" alt="Screen Shot 2022-11-30 at 9 09 32 PM" src="https://user-images.githubusercontent.com/69278312/204899162-1ef6833b-7261-4f4c-ad0c-411c21f1606d.png">
