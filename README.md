Ryan Baten

OpenGL Roller Coaster

OpenGL version 2
SDL version 1.2

![screenshot 1](https://github.com/RyanBaten/graphics-finalproject/blob/master/project_screenshot1.jpg)
![screenshot 2](https://github.com/RyanBaten/graphics-finalproject/blob/master/project_screenshot2.jpg)

Controls
========

General controls:

| Key        | Action |
| ---------- | ------ |
|1           | switch to Construction mode
|2           | switch to Coaster 3rd person view
|3           | switch to Preset coaster loaded in/ 3rd person view
|4           |  switch to First person follow coaster
|5           |  switch to Debug mode
|Arrow keys  |  rotate view
|b           |  export track to create file yourTrack.track
|w           |  increase velocity
|s           |  decrease velocity

Construction mode specific controls:
| Key        | Action |
| ---------- | ------ |
|w           |  move camera forward
|s           |  move camera backward
|i           |  move cursor forward
|k           |  move cursor back
|j           |  move cursor left 
|l           |  move cursor right
|t           |  move cursor up 
|y           |  move cursor down 
|Enter       |  add point for rollercoaster
|r           |  reset rollercoaster points

How to Use
==========

When the program starts up, it will load in and display a sample track. I would recommend playing with the basic controls (arrow keys and w and s keys) to look around and change the velocity of the coaster on the track. Next, press the 4 key to enter a fun first person mode where you ride the coaster!

The construction mode can be entered by pressing the 1 key. Move the cursor around and press enter a couple times to add points to the rollercoaster, after the third point is selected, the generated track will be desplayed. Add additional sections by pressing enter again. It is helpful to use the w and s keys to move the camera back and forth when trying to get a good view of the scene.

Have fun!

Challenges while making and what I learned:
===========================================
- Automatic calculation of track vertices and normals
  - Using one bezier curve to generate two lines of a track that may not intersect requires various manipulations to be done.

- Getting the coaster to rotate correctly and debugging issues with order in which rotation occurs
  - My calculations for the angle required rotation around the y axis to occur before the rotation involving the pitch of the coaster. At first the coaster model was on an axis that my opengl code would rotate after doing y axis rotation. The fix ended up being rotating and re-exporting the model since I didn't want to mess with the Object::draw function which is also used for drawing the trees.

- Particle generation using point sprites

- Particle behavior and not having the particles fight with eachother
  - Requires disabling z buffer while drawing particles

- Generation of random points for ground and calculating normals
  - Better way to do it would be using a Bezier surface but at the time I implemented it, I didn't know they existed.

- The main loop can slow down considerably while keys are pressed/held if events aren't handled correctly.
  - At first, I handled all key presses and holds with a function containing if statements through the event handling section of the main loop. After testing, I found that it's best to have a separate function for key presses and keys that are meant to be held. Key presses should be handled in the event loop, however held keys can be handled in the idle loop to avoid slowing down execution of the idle loop by flooding the event handler with events.
  - It is important to remove any delay on the idle loop that the event loop may impose on it. When starting the development, I had introduced such a delay to avoid cases where keys would be handled twice in a row.
  - The end result of this was that instead of the coaster pausing while any keys were pressed, the coaster now glides smoothly at all times and the whole application feels smoother.

- Having reference points on the ground (trees) makes camera movement seem less disorienting.


Sources:
--------
This project uses these sounds from freesound:
mark time 1P77b by Setuniman (https://freesound.org/people/Setuniman/sounds/408201/)

Skybox images from:
https://93i.de/p/free-skybox-texture-set/

Grass image:
https://opengameart.org/sites/default/files/forum-attachments/grass20.png

Metal texture:
https://opengameart.org/sites/default/files/oga-textures/metall010-new-tileable.png

SDL print function from CSCI 5229

Object files for coaster and trees and their textures made in Blender and particle images made in Paint.net by me.
