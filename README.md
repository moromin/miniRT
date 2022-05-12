# miniRT

## `rt`ファイルについて
このレイトレーシング・プログラムは、`rt`ファイルに基づいてレンダリングする。`rt`ファイルのフォーマットは以下のように定義されている。

```
{identifier} {param1} {param2} ...
```

例
```
A 0.2 255,255,255

C -50,0,20 0,0,0 70
L -40,0,30 0.7 255,255,255

pl 0,0,0 0,1.0 255,0,225
SP 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

各識別子のパラメータは以下のように設定されている。
#### A：自然光 (Ambient)
```
A {ratio} {color}
```
- `ratio` : 自然光の光の強さの比率 `[0.0, 1.0]`
- `color` : 自然光の色 `R,G,B`, `[0.0, 255.0]`

#### C：カメラ (Camera)
```
C {view_point} {orientation_vector} {FOV}
```
- `view_point` : 視点座標 `x,y,z`
- `orientation_vector` :  正規化された方向ベクトル `x,y,z`, `[-1, 1]`
- `FOV` : 水平方向の視野角 `[0, 180]`

#### L：光 (Light)
```
L {point} {ratio} {color}
```
- `point` : 光源の座標 `x,y,z`
- `ratio` : 光源の光の強さの比率 `[0.0, 1.0]`
- `color` : 光源の色 (mandatoryでは未使用) `R,G,B`, `[0.0, 255.0]`

#### sp：球 (Sphere)
```
sp {center} {diameter} {color}.
```
- `center` : 中心座標 `x,y,z`
- `diameter` : 球の直径
- `color` : 色 `R,G,B`, `[0.0, 255.0]`


#### pl：平面 (Plane)
```
pl {center} {orientation_vector} {color}
```
- `center` : 中心座標 `x,y,z`
- `orientation_vector` : 正規化された方向ベクトル  `x,y,z`, `[-1, 1]`
- `color` : 色 `R,G,B`, `[0.0, 255.0]`

#### cy：円柱 (Cylinder)
```
cy {center} {orientation_vector} {diameter} {height} {color}
```
- `center` : 中心座標 `x,y,z`
- `orientation_vector` : 正規化された方向ベクトル  `x,y,z`, `[-1, 1]`
- `diameter` : 円柱の直径
- `height` : 円柱の高さ
- `color` : 色 `R,G,B`, `[0.0, 255.0]`


## 参考サイト
- C言語でレイトレーシングプログラムを作った](https://jun-networks.hatenablog.com/entry/2021/04/02/043216)
- レイトレーシングの教科書@TDU](https://knzw.tech/raytracing/?page_id=1154)
