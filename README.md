# Digital Image Processing

There are some basic operations for BMP file.

## K-means methods

#### Origin picture

![image-20211004122211828](C:\Users\Tianhe Wu\AppData\Roaming\Typora\typora-user-images\image-20211004122211828.png)

#### K-means compress picture

It can compress 256 color picture.

![image-20211004122244279](C:\Users\Tianhe Wu\AppData\Roaming\Typora\typora-user-images\image-20211004122244279.png)

### Color histogram equalization

Open the 24-bit bmp file exp_24.bmp and convert the rgb space to yuv space. Perform histogram equalization on the y-space. Then convert from yuv space to rgb space.

#### Origin picture

![image-20211004122706215](C:\Users\Tianhe Wu\AppData\Roaming\Typora\typora-user-images\image-20211004122706215.png)

#### Histogram equalization

![image-20211004122739791](C:\Users\Tianhe Wu\AppData\Roaming\Typora\typora-user-images\image-20211004122739791.png)

#### Parameters

Probability non-zero gray level, the ratio of the maximum probability, minimum probability, and maximum minimum probability in the probability non-zero gray level; the number of gray levels with probability greater than the average probability in the image; the average and variance of the non-zero probability are shown in the following figure:

![image-20211004122814638](C:\Users\Tianhe Wu\AppData\Roaming\Typora\typora-user-images\image-20211004122814638.png)
