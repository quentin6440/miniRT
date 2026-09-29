*This project has been created as part of the 42 curriculum by qcyril-a, zali.*

## Description

`miniRT` is a small ray tracer written in C as part of the 42 curriculum.

The program reads a `.rt` scene file and renders spheres, planes, and finite cylinders with a camera, ambient lighting, diffuse lighting, and shadows using MiniLibX.

## Instructions

The project requires Linux, `make`, a C compiler, and the X11 development libraries.

From the project directory, compile the project with:

```bash
make
```

Run the program with one `.rt` scene file:

```bash
./miniRT scene.rt
```

The program opens a window displaying the rendered scene. Press `ESC` or close the window to exit.

A scene file contains one element per line:

```text
A ratio R,G,B
C x,y,z nx,ny,nz FOV
L x,y,z ratio R,G,B
sp x,y,z diameter R,G,B
pl x,y,z nx,ny,nz R,G,B
cy x,y,z nx,ny,nz diameter height R,G,B
```

Example:

```text
A 0.2 255,255,255
C 0,0,-5 0,0,1 70
L -2,5,-3 0.7 255,255,255
sp 0,0,0 2 255,0,0
pl 0,-2,0 0,1,0 0,255,100
cy 2,0,1 0,1,0 1.0 2.0 0,100,255
```

`A` defines ambient lighting, `C` the camera, `L` a point light, `sp` a sphere, `pl` a plane, and `cy` a cylinder.

## Resources

- The official 42 `miniRT` subject
- MiniLibX documentation
- C and `math.h` documentation
- References about ray tracing, vectors, intersections, surface normals, and lighting

AI was used to help understand ray-tracing concepts, review parsing and intersection logic, identify possible edge cases. The code and final decisions were implemented manually.
