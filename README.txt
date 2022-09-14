the lines you can change without breaking the program are the following:

13	const double exp_r_f = 1.2;
14	const int exp_r = 10;
15	const int mmc = 80;
16	const int nos = 1000;
17	const int iss = 1000;

19	int size_x=1920, size_y=1020;

23	long double scale = 1000;
24	long double cntr_x=1, cntr_y=0.55;

The program works by scanning every vertical line of the display.
For each of them the z=z*temp_x*(1-z) is run for iss initial times, z is initialy set to 0.5.
After that nos stabilities are calculated to fit inside the display area running the z=z*temp_x*(1-z) equation further.
The mcc constant is the amount of fails required to skip one of the iss stabilities and abort searching if it takes too long.
size_x and size_y are the resolution values of the display.
exp_r and exp_r_f are weight values for the exposure of the image. Idealy 1 to 255 and 1 to 1.5, exp_r is an integer.

Lines 25 and 26 can be changed freely and are not constants, they are only initial values for the camera.
scale is the amount of pixels for every unit on the axis.
cntr_x and cntr_y are the coordinates the camera is initialy aiming at.
NOTE: you have to re-compile the cpp file after making any changes for them to take effect.

The axis are not rendered, keep that in mind. You need to know this specific fractal to know their position.
One "image_product.bmp" file is created and re-writen holding the latest rendered image in raw form.

HOW TO MOVE:
Use the numpad numbers as arrows (8 is up, 6 is right, 1 is down left ect) and + - for zooming.
You need the NumLock enabled on your keyboard for this to work and have to have the console window sellected 
to type the mentioned numbers-symbols and press enter.
Very demanding settings might make the scene take too long to render so for fun exploration use the already set values.
