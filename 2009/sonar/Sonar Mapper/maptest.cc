#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "SonarInterface.h"
#include <stdlib.h>

SonarInterface sdev;
int main(int argc, char *argv[])
{
  IplImage* img = 0; 
  int height,width,step,channels;
  uchar *data;
  int i,j,k;
  CvPoint robotBaseAt=cvPoint(160.5,230);

  // load an image  
  img=cvCreateImage(cvSize(320,240),IPL_DEPTH_8U,3);
  if(!img){
    printf("Could not load image file: %s\n",argv[1]);
    exit(0);
  }

  // get the image data
  height    = img->height;
  width     = img->width;
  step      = img->widthStep;
  channels  = img->nChannels;
  data      = (uchar *)img->imageData;
  printf("Processing a %dx%d image with %d channels\n",height,width,channels); 

  // create a window
  cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
  cvMoveWindow("mainWin", 100, 100);
  //Drawing Tests
	  //Draw a circle test
		  cvCircle(img, cvPoint(width/4,height/3),20,
					 //CV_RGB(rand()%255,rand()%255,rand()%255),
					 CV_RGB(255,0,0),
					 -1);
		  
		  // show the image
		  cvShowImage("mainWin", img );
		  		 
		  // wait for a key
		  cvWaitKey(0);		 

	  //Draw a ellipse sector test
		  cvEllipse( img, 	/*CvPoint center*/ 		robotBaseAt, 
		  					/*CvSize axes*/			cvSize(20,30), 
		  					/*double tiltangle*/	0,
				        	/*double startAngle*/ 	0, 
				        	/*double endAngle*/ 	90,
				        	 						CV_RGB(0,0,255),
				        	/*int thickness*/		-1 );
			 

		  // show the image
		  cvShowImage("mainWin", img );

		  // wait for a key
		  cvWaitKey(0);
	  
	  //Draw a ellipse sector test
		  cvEllipse( img, 	/*CvPoint center*/ 		robotBaseAt, 
		  					/*CvSize axes*/			cvSize(60,30), 
		  					/*double tiltangle*/	0,
				        	/*double startAngle*/ 	-20, 
				        	/*double endAngle*/ 	20,
				        	 						CV_RGB(0,255,0),
				        	/*int thickness*/		-1 );
			 

		  // show the image
		  cvShowImage("mainWin", img );

		  // wait for a key
		  cvWaitKey(0);
	  
	  //Angle test (fails)
		  cvEllipse( img, 	/*CvPoint center*/ 		robotBaseAt, 
		  					/*CvSize axes*/			cvSize(40,30), 
		  					/*double tiltangle*/	0,
				        	/*double startAngle*/ 	-20, 
				        	/*double endAngle*/ 	20,
				        	 						CV_RGB(0,255,255),
				        	/*int thickness*/		-1 );
			 

		  // show the image
		  cvShowImage("mainWin", img );

		  // wait for a key
		  cvWaitKey(0);
  //End Drawing Tests
  //Setup Sonar
  
    	int rawdata[10];
		int dat;
		double dists;	
		printf("\nInitializing Link...\n");

		sdev.initSonDev(11,19,2000,15);
		
		
for(int n=1;n<100;n++){
  //Begin Sonar Capture
	printf("Pinging all sonars, then waiting for data return.\nShould return 11 rvalues (0-10).\n");
	sdev.pingAll();
	while(sdev.updateAll() == -1);
	for(int i=0; i<11; i++){
		while((rawdata[i]=sdev.readIndiv(i,'o'))==-1);
		printf("%d:%d\n",i,rawdata[i]);
	}
  //End Sonar Capture
  //Draw ranges
    cvSet(img, cvScalar(0,0,0));
  	for(int i=0; i<11; i++){
		  cvEllipse( img, 	/*CvPoint center*/ 		robotBaseAt, 
		  					/*CvSize axes*/			cvSize(rawdata[i]/4,rawdata[i]/4), 
		  					/*double tiltangle*/	i*18,
				        	/*double startAngle*/ 	-9, 
				        	/*double endAngle*/ 	9,
				        	 						CV_RGB(0,(char)(20*i),(char)(10*i)),
				        	/*int thickness*/		-1 );
	}
			  // show the image
		  cvShowImage("mainWin", img );
		  		  // wait for a key
		  cvWaitKey(10);


}  


  // release the image
  cvReleaseImage(&img );
  return 0;
}