*English README is [here](https://github.com/moromin/miniRT/blob/master/README.en.md)

# miniRT

## 概要

シンプルなRay TracerのC言語実装

## デモ

`scenes/bumpmap.rt`

![bumpmap.jpg](https://github.com/moromin/miniRT/blob/main/demo/bumpmap.jpg?raw=true)

`scenes_bonus/ch_multi.rt`

![ch_multi.jpg](https://github.com/moromin/miniRT/blob/main/demo/ch_multi.jpg?raw=true)

## 環境構築の手順

### 必須

- GNU make (version 3.81)
- GCC (Apple clang version 13.0.0)

これらのバージョンを開発中に使用。

### Mac/Linux

- 描画ライブラリ minilibx (詳しくは[こちら](https://github.com/42Paris/minilibx-linux/)をご覧ください！)

```bash
git clone https://github.com/moromin/miniRT --recursive
cd miniRT
make
./miniRT [RTFILE_PATH]
```

## 機能一覧

- `rt` ファイルから環境やオブジェクトの情報を読み込む
    - 詳しい記述方法については下に記載があります！
- 任意の位置に下記を配置可能
    - 幾何オブジェクト
    - 光源
    - 視点
- 対応した幾何オブジェクト
    - 球
    - 平面
    - 円柱
    - 円錐
- 対応した光源
    - 点光源
    - スポットライト（角度を指定可能）
- その他、考慮する要素
    - 環境光
    - 拡散反射
    - 鏡面反射
    - チェッカー柄（指定された場合）

## 注力した機能や工夫した点

### 単一継承を活用し、C言語でOOPを行った

```c
// include/object.h

typedef struct s_object_vtbl	t_object_vtbl;

typedef struct s_object {
	// 仮想関数テーブル
	t_object_vtbl	*vptr;
	t_vector		center;
	t_material		material;
	t_color			diffuse_reflection_coefficient;
	t_color			specular_reflection_coefficient;
}	t_object;

struct s_object_vtbl {
	double		(*solve_ray_equation)(t_object *const me, t_ray);
	t_color		(*calc_radiance)(t_object * const me, t_vector, t_light, t_vector);
	t_vector	(*calc_normal)(t_object * const me, t_vector　cross_point);
	t_color		(*calc_color)(t_object * const me, t_vector cross_point);
};
```

```c
// include/object.h

typedef struct s_sphere {
	// t_objectを継承
	t_object	super;
	// t_sphereに固有のフィールド
	double		radius;
}	t_sphere;
```

### Goを参考に可変長配列を実装し、シンプルな操作を可能にした

*`s[1:2]` のような機能は今回は必要無かった + メモリ管理が複雑になってしまったので、今回は未実装

```c
// include/slice.h

// 前方宣言でカプセル化
typedef struct s_slice	t_slice;

t_slice	*make(size_t size, size_t len, size_t cap);
void	delete(t_slice *s);
void	append(t_slice *s, void *elem);
void	*get(t_slice *s, int index);
size_t	len(t_slice *s);
```

```c
// src/slice.c

void	append(t_slice *s, void *elem)
{
	t_slice	*new;

	if (s->len < s->cap)
	{
		ft_memcpy(s->org_start + s->len * s->size, elem, s->size);
		s->len++;
	}
	else
	{
		new = x_malloc(s->size * s->cap * 2);
		ft_memcpy(new, s->cur_start, s->size * s->len);
		free(s->org_start);
		s->cap *= 2;
		s->org_start = new;
		s->cur_start = new;
		append(s, elem);
	}
}
```

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

### A：自然光 (Ambient)

```
A {ratio} {color}
```

- `ratio` : 自然光の光の強さの比率 `[0.0, 1.0]`
- `color` : 自然光の色 `R,G,B`, `[0.0, 255.0]`

### C：カメラ (Camera)

```
C {view_point} {orientation_vector} {FOV}

```

- `view_point` : 視点座標 `x,y,z`
- `orientation_vector` : 正規化された方向ベクトル `x,y,z`, `[-1, 1]`
- `FOV` : 水平方向の視野角 `[0, 180]`

### L：光 (Light)

```
L {point} {ratio} {color}
```

- `point` : 光源の座標 `x,y,z`
- `ratio` : 光源の光の強さの比率 `[0.0, 1.0]`
- `color` : 光源の色 (mandatoryでは未使用) `R,G,B`, `[0.0, 255.0]`

### sp：球 (Sphere)

```
sp {center} {diameter} {color}.
```

- `center` : 中心座標 `x,y,z`
- `diameter` : 球の直径
- `color` : 色 `R,G,B`, `[0.0, 255.0]`

### pl：平面 (Plane)

```
pl {center} {orientation_vector} {color}
```

- `center` : 中心座標 `x,y,z`
- `orientation_vector` : 正規化された方向ベクトル `x,y,z`, `[-1, 1]`
- `color` : 色 `R,G,B`, `[0.0, 255.0]`

### cy：円柱 (Cylinder)

```
cy {center} {orientation_vector} {diameter} {height} {color}
```

- `center` : 中心座標 `x,y,z`
- `orientation_vector` : 正規化された方向ベクトル `x,y,z`, `[-1, 1]`
- `diameter` : 円柱の直径
- `height` : 円柱の高さ
- `color` : 色 `R,G,B`, `[0.0, 255.0]`

### co：円錐 (Cone)

```
co {center} {direction} {aperture} {color}
```

- `center` : 頂点座標 `x,y,z`
- `orientation_vector` : 正規化された方向ベクトル `x,y,z`, `[-1, 1]`
- `aperture` : 円錐の開き角
- `color` : 色 `R,G,B`, `[0.0, 255.0]`

### sl：スポットライト

```
sl {point} {orientation_vector} {FOV} {ratio} {color}
```

- `point` : 光源の座標 `x,y,z`
- `orientation_vector` : 正規化された方向ベクトル `x,y,z`, `[-1, 1]`
- `FOV` : 水平方向の視野角 `[0, 360]`
- `ratio` : 光源の光の強さの比率 `[0.0, 1.0]`
- `color` : 光源の色  `R,G,B`, `[0.0, 255.0]`

#### bm：バンプマップ (Bump map)
```
bm {file_path} {vertical_repetition} {horizontal_repetition}
```
- `file_path` : バンプマップ(法線マップ)ファイルパス
- `horizontal_repetition` : 横方向繰り返し数
- `vertical_repetition` : 縦方向繰り返し数

#### tx：テクスチャ (Texture)
```
tx {file_path} {vertical_repetition} {horizontal_repetition}
```
- `file_path` : テクスチャファイルパス
- `horizontal_repetition` : 横方向繰り返し数
- `vertical_repetition` : 縦方向繰り返し数

### ch：チェッカーボード

```c
ch {freq u} {freq v} {color1} {color2}
```

- `freq u` : 横方向への色の数 `[1, INF]`
- `freq v` : 縦方向への色の数 `[1, INF]`
- `color1` : チェッカー柄1色目  `R,G,B`, `[0.0, 255.0]`
- `color2` : チェッカー柄2色目  `R,G,B`, `[0.0, 255.0]`

## 著者

- [moromin](https://github.com/moromin)
- [tacomeet](https://github.com/tacomeet)


## 参考サイト

- [C言語でレイトレーシングプログラムを作った](https://jun-networks.hatenablog.com/entry/2021/04/02/043216)
- [レイトレーシングの教科書@TDU](https://knzw.tech/raytracing/?page_id=1154)
- [Application Note Object-Oriented Programming in C](https://www.state-machine.com/doc/AN_Simple_OOP_in_C.pdf)
- [Texture Mapping](http://www.raytracerchallenge.com/bonus/texture-mapping.html) (from *[The Ray Tracer Challenge](http://www.raytracerchallenge.com/))*
- [kohkubo/minirt_sample](https://github.com/kohkubo/minirt_sample)
- yokawada氏notion
