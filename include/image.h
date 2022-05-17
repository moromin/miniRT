#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_img {
	void	*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*buffer;
	int		height;
	int		width;
}	t_img;

#endif
