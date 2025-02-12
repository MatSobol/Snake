## Snake

### How to run

Firstly install raylib: https://www.raylib.com/

Than run (for windows)
```
make && ./main.exe
```

### Key bindings

- `a` -> Turn left
- `d` -> Turn right
- `F11` -> Toggle fullscreen
- `left mouse click` -> restart

### How it looks

![image](https://github.com/user-attachments/assets/f22ecf60-5268-4d79-a75c-4efb39e8f287)

### How it works

The snake's body is composed of multiple circles.

The head of the snake is assigned a speed vector, which can be rotated by pressing `a` or `d`.

Each frame, speed vetor is scaled by the delta time between frames and the resulting vector is used to update curent head position.

The center of the next circle is moved to the nearest point on the edge of the head's circle. This action is reapeted for all circles.

Later program calculates a vector between circle centers (for head a speed vector is used) and 
then computes two vectors of radius lenght at right angle to it one to the left and one to the right.
These vectors are then used to draw the snake's body.

Result looks like below:

![image](https://github.com/user-attachments/assets/72fbed3f-f1e0-4ead-a809-83d839192f25)


