#include <iostream>
#include "CImg.h"
#include <math.h>

using namespace std;
using namespace cimg_library;

int main(){
	
	char answer;
	long double step;
	long int i, j; //only for loops
	const double exp_r_f = 1.2; //the exposure rate factor of the image
	const int exp_r = 10; //the exposure rate of the image
	const int mmc = 80; //max misses counted
	const int nos = 1000; //num_of_stabilities
	const int iss = 1000; //num_of_initial_stabilization_steps
	int print_x, print_y; //only for printing
	int size_x=1920, size_y=1020; // the size of the display
	int temp_x_int; //the x value of the display currently being investigated
	long double temp_x; //the physical x value currently being investigated
	long double min_y, max_y; // the min and max physical values of y that will fit on screen
	long double scale = 200; //the scaling between temp_x and tamp_x_int, scale * temp_x (unit) = temp_x_int (unit)
	long double cntr_x=1, cntr_y=0.55; //the physical centre of the display area
	long double stabilities[nos]; //physical values of the stabilities for a given temp_x
	long double z; //physical value currently being stabilized
	
	const unsigned char white[] = { 255 };
	const unsigned char black[] = { 0 };	
	unsigned char temp_color[1];
	CImg<unsigned char> bg(size_x,size_y,1,1,255);
	bg.draw_rectangle(0,0,size_x,size_y,black);
	CImgDisplay dsp(size_x,size_y,"Graph Display",0);
	
	render: //starts rendering the graph with the current scale, cntr_x and cntr_y
	CImg<unsigned char> img(bg); //sets the background as the current image
	for(temp_x_int=0; temp_x_int<size_x; temp_x_int++){ //scans the display on the x-axis (repeats 1920 times)
		temp_x = (temp_x_int-size_x/2)/scale+cntr_x;
		min_y = cntr_y - size_y/(2*scale);
		max_y = cntr_y + size_y/(2*scale);
		z=0.5;
		for(i=0; i<iss; i++) z=z*temp_x*(1-z);		//initialy steps iss times
		i=0;
		j=0;				//resets i to zero to start counting the new stabilities
		while(i<nos){
			z=z*temp_x*(1-z);	//finds the next stability
			if(min_y<z && z<max_y){
				stabilities[i] = z;
				i++;
				j=0;
			}else if(j>mmc){
				stabilities[i] = z;
				i++;
				j=0;
			}else j++;
		}
		for(i=0; i<nos; i++){
			if(min_y<stabilities[i] && stabilities[i]<max_y){
				print_x = temp_x_int;
				print_y = (size_y/2)-(int)((stabilities[i]-cntr_y)*scale);
				
	            temp_color[0] = (int)img(print_x,print_y,0,0)*exp_r_f+exp_r;
	            if(temp_color[j]>255) temp_color[0] = 255;
				
				img.draw_point(print_x,print_y,temp_color);
			}
		}
		
	}
	img.normalize(0, 255);
	dsp.display(img);//updates the image displayed to the finished result
	img.save("image_product.bmp");
	cin >> answer;
	step=size_x/(10*scale);
	switch(answer){
		case '1':
			cntr_x=cntr_x-step;
			cntr_y=cntr_y-step;
		break;	
		case '2':
			cntr_y=cntr_y-step;
		break;	
		case '3':
			cntr_x=cntr_x+step;
			cntr_y=cntr_y-step;
		break;	
		case '4':
			cntr_x=cntr_x-step;
		break;	
		case '6':
			cntr_x=cntr_x+step;
		break;	
		case '7':
			cntr_x=cntr_x-step;
			cntr_y=cntr_y+step;
		break;	
		case '8':
			cntr_y=cntr_y+step;
		break;	
		case '9':
			cntr_x=cntr_x+step;
			cntr_y=cntr_y+step;
		break;	
		case '+':
			scale=scale*1.3;
		break;	
		case '-':
			scale=scale/1.3;
		break;
		case 'e':
			return 0;
		break;
	}
	goto render;
	
	
}
