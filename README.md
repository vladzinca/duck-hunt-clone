# Duck Hunt Clone

## What is it?

This project is a recreation of the Nintendo classic 2D video game Duck Hunt, made using an OpenGL framework called GFX, available [here](https://github.com/UPB-Graphics/gfx-framework).

I coded it during the first half of November 2022 and had a lot of fun with it.

## How to run it?

1.  Clone this repository.
2.  Make the build files using CMake, as described [here](https://github.com/UPB-Graphics/gfx-framework).
3.  Open the project using the `GFXFramework.sln` file and run it.
4.  Enjoy!

## What does it do?

It lets you shoot ducks.

Pretty barbaric, but keep in mind it's just a video game.

Just in the old Duck Hunt, the game will spawn one duck at a time that will bounce off the screen, in a desperate attempt to escape. After a few moments, it will succeed. That is where ***you*** come in.

By aiming and shooting the duck with LeftMouseButton, you will make it fall to the ground and accumulate some score. The goal is to make the score bar full.

But be careful, as you only have 3 bullets for each duck, and if 3 ducks escape, it's game over.

## How did I do it?

As you can see, the game mechanics are pretty simple in this day and age, but I learned a ton of things from coding it.

First off, making the ducks achieve the wanted motion by only using matrix multiplications is nothing but challenging at first. You have to take into consideration that all walls can be hit from two directions, so there are 8 cases total. This, coupled with the fact that I wanted the point of collision with the margins to be my duck's head, meant I had to do quite a bit of trigonometry in order to get it done.

Secondly, checking that the mouse position is touching the duck meant I had to create a hitbox for the poor bird, as well as to translate and rotate the axes for mouse coordinates so that both have the same origin and angle.

## Did you know?

If you are more curious to observe the background computations of these processes, pressing T on the keyboard while the game is running reveals what I termed a Debug Mode, that freezes the game state and enables the hitbox, as well as several points of interest.

In Debug Mode, the duck cannot escape anymore, and you can spend your time watching it bounce off the window's edges, as well as killing it when you get bored. How wonderful!
