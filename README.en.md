# miniRT

## Elements
This RayTracing program renders based on `rt` files.The format of the `rt` file is defined as follows:

```
{identifier} {param1} {param2} ...
```

Example
```
A 0.2 255,255,255

C -50,0,20 0,0,0 70
L -40,0,30 0.7 255,255,255

pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

The parameters for each identifier are set as follows:
#### A (Ambient)
```
A {ratio} {color}
```
- `ratio` : ratio in range `[0.0, 1.0]`.
- `color` : color in range `[0.0, 255.0]` for each `R,G,B`.

#### C (Camera)
```
C {view_point} {orientation_vector} {FOV}
```
- `view_point` : coordinates of view point in `x,y,z` format.
- `orientation_vector` : normalized orientation vector in range `[-1, 1]` for each `x,y,z` axis.
- `FOV` : horizontal field of view in degrees in range `[0, 180]`.

#### L (Light)
```
L {point} {ratio} {color}
```
- `point` : coordinates of point in `x,y,z` format.
- `ratio` : ratio in range `[0.0, 1.0]`.
- `color` : color in range `[0.0, 255.0]` for each `R,G,B` (unused in mandatory part).

#### sp (Sphere)
```
sp {center} {diameter} {color}
```
- `center` : coordinates of center in `x,y,z` format.
- `diameter` : diameter of the sphere.
- `color` : color in range `[0.0, 255.0]` for each `R,G,B`.


#### pl (Plane)
```
pl {center} {orientation_vector} {color}
```
- `center` : coordinates of center in `x,y,z` format.
- `orientation_vector` : normalized orientation vector in range `[-1, 1]` for each `x,y,z` axis.
- `color` : color in range `[0.0, 255.0]` for each `R,G,B`.

#### cy (Cylinder)
```
cy {center} {orientation_vector} {diameter} {height} {color}
```
- `center` : coordinates of center in `x,y,z` format.
- `orientation_vector` : normalized orientation vector in range `[-1, 1]` for each `x,y,z` axis.
- `diameter` : diameter of the cylinder.
- `height` : height of the cylinder.
- `color` : color in range `[0.0, 255.0]` for each `R,G,B`.


## References
- [C言語でレイトレーシングプログラムを作った](https://jun-networks.hatenablog.com/entry/2021/04/02/043216)
- [The Textbook of RayTracing @TDU](https://knzw.tech/raytracing/?page_id=1154)
