# CUB3D: game recreation of the raycasting technique

## FULL MOON

How to run:
- git clone the directory
- run make
- it will download and install MLX42 graphics library and compile the game
- ./cub3d
- you can choose a different map for maps/ by passing it as a second parameter

Controls: 
WASD - movement
Enter/LeftMouse - swing sword
Mouse/Left and Right Arrow - rotate camera

![](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExcng0YjRpcnp3ejdzYXkxYTkyMm50dzRxNXZ2b3E4amM1NGtsb2FkZCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/N1b5YxJCEbVDr4lgZz/giphy-downsized-large.gif)

This is a game made from scratch using C and an MLX42 graphics library, in collaboration with Marek Burakowski @hatomoto.

The graphics logic is based on the Wolfenstein 3D’s raycasting technique. It calculates the distances between the player and the objects on the text map and utilizes them to draw the screen. 

The graphics are intentionally made lofi by sampling the textures less amount of times. We also took the photos of Marek’s sword and his hands to create the animation for the main weapon. 

This project uses A* pathfinding to make the enemies move whenever the player gets in the view of the enemy. Enemies also use raycasting to determine whether they see you or not.

This project has some rendering bugs and not adjusted for all systems, but the reason for is that most of the interesting stuff we added later was way out of the original scope of just building a barebones raycaster. 

We had a ton of fun making this game, hope you will have some fun playing it too!

