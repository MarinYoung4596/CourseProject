//CDecperiment.h
//code by marinyoung
//IDE:Visual Studio 2010
//GUI library:OpenGL 3.4
//last modification:October 19th,2012
#ifndef CGEXPERIMENT_H
#define CGEXPERIMENT_H
#include<iostream>
#include<GL/glut.h>
#include<cstdlib>
#include<windows.h>

#define Squre(x) (x)*(x)

const int width=700,high=700;

using namespace std;

class screenPt
{
private:
    GLint x,y;

public:
    screenPt()
    {
        x=y=0;
    }
    void setCoords(GLint xCoordValue,GLint yCoordValue)
    {
        x=xCoordValue;
        y=yCoordValue;
    }
    GLint getX()const
    {
        return x;
    }
    GLint getY()const
    {
        return y;
    }
    void incrementX()
    {
        x++;
    }
    void decrementX()
    {
        x--;
    }
    void incrementY()
    {
        y++;
    }
    void decrementY()
    {
        y--;
    }
};

//draw a point
void setPixel(GLint x,GLint y)
{
    glColor3f (0, 0, 0);
    glBegin(GL_POINTS);
		glVertex2i(x,y);
		Sleep(10);
    glEnd();
    glFlush();
}

//function statement
void ellipse_plot_points(screenPt ,GLint ,GLint );
void circle_plot_points(GLint ,GLint ,screenPt );
void Bresenham(screenPt ,screenPt );

/*=====ellipse algorithm=====*/
void Ellipse(screenPt center,GLint Rx,GLint Ry)
{
    //the first area
    screenPt ellipsePt;
    ellipsePt.setCoords(0,Ry);
    int p=Squre(Ry)-Squre(Rx)*Ry+Squre(Rx)/4;
    while(Squre(Ry)*ellipsePt.getX()<Squre(Rx)*ellipsePt.getY())
    {
		ellipsePt.incrementX();
		if(p<0)
		{
			p=p+2*Squre(Ry)*ellipsePt.getX()+Squre(Ry);
		}
		else
		{
			ellipsePt.decrementY();
			p=p+2*Squre(Ry)*ellipsePt.getX()-2*Squre(Rx)*ellipsePt.getY()+Squre(Ry);
		}
		ellipse_plot_points(center,ellipsePt.getX(),ellipsePt.getY());
    }
    //the second area
	p=Squre(Ry)*Squre(ellipsePt.getX()+1/2)+Squre(Rx)*Squre(ellipsePt.getY()-1)-Squre(Rx)*Squre(Ry);
    while(ellipsePt.getY()>=0)
    {
		ellipsePt.decrementY();
		if(p>0)
		{
			p=p-2*Squre(Rx)*ellipsePt.getY()+Squre(Rx);
		}
		else
		{
			ellipsePt.incrementX();
			p=p+2*Squre(Ry)*ellipsePt.getX()-2*Squre(Rx)*ellipsePt.getY()+Squre(Rx);
		}
		ellipse_plot_points(center,ellipsePt.getX(),ellipsePt.getY());
    }
}
	
void ellipse_plot_points(screenPt center,GLint Rx,GLint Ry)
{
    setPixel(center.getX()+Rx,center.getY()+Ry);
    setPixel(center.getX()-Rx,center.getY()+Ry);
    setPixel(center.getX()+Rx,center.getY()-Ry);
    setPixel(center.getX()-Rx,center.getY()-Ry);
}

void draw_ellipse(void)
{
    GLint center_x,center_y;
    screenPt centerPt;
    GLint Rx,Ry;
    cout<<"input the center of  ellipse:\t";
    cin>>center_x>>center_y;
    centerPt.setCoords(center_x,center_y);
    cout<<"input the radius:\t";
    cin>>Rx>>Ry;
	glClearColor(1.0,1.0,1.0,0.0);
	glClear (GL_COLOR_BUFFER_BIT);
    Ellipse(centerPt,Rx,Ry);
}

/*=====circle algorithm=====*/
void circleMidpoint(GLint Xc,GLint Yc,GLint radius)
{
    screenPt circlePt;
    GLint p=1-radius;
    circlePt.setCoords(0,radius);

    circle_plot_points(Xc,Yc,circlePt);
    while(circlePt.getX()<circlePt.getY())
    {
        circlePt.incrementX();
        if(p<0)
            p+=2*circlePt.getX()+1;
        else
        {
            circlePt.decrementY();
            p+=2*(circlePt.getX()-circlePt.getY())+1;
        }
        circle_plot_points(Xc,Yc,circlePt);
    }
}

void circle_plot_points(GLint Xc,GLint Yc,screenPt circlePt)
{
    setPixel(Xc+circlePt.getX(),Yc+circlePt.getY());
    setPixel(Xc-circlePt.getX(),Yc+circlePt.getY());
    setPixel(Xc+circlePt.getX(),Yc-circlePt.getY());
    setPixel(Xc-circlePt.getX(),Yc-circlePt.getY());

    setPixel(Xc+circlePt.getY(),Yc+circlePt.getX());
    setPixel(Xc-circlePt.getY(),Yc+circlePt.getX());
    setPixel(Xc+circlePt.getY(),Yc-circlePt.getX());
    setPixel(Xc-circlePt.getY(),Yc-circlePt.getX());
}

void draw_circle()
{
    GLint x,y,radius;
    cout<<"input radius:\t";
    cin>>radius;
    cout<<"input center:\t";
    cin>>x>>y;
	glClearColor(1.0,1.0,1.0,0.0);
	glClear (GL_COLOR_BUFFER_BIT);
    circleMidpoint(x,y,radius);
}


/*=====bresenham algorithm=====*/
void swap(GLint *x,GLint *y)
{
    GLint temp=*x;
    *x=*y;
    *y=temp;
}

//initialize and Draw Line
void BresenhamDraw(screenPt startPt,screenPt endPt)
{
    screenPt linePt;
    linePt.setCoords(startPt.getY()<endPt.getY()?startPt.getY():endPt.getY(),
                     startPt.getX()<endPt.getX()?startPt.getX():endPt.getX());
    GLint y_max=startPt.getY()>endPt.getY()?startPt.getY():endPt.getY(),
                x_max=startPt.getX()>endPt.getX()?startPt.getX():endPt.getX();
    GLint x1,y1,x2,y2;
    //if k doesn't exist
    if(startPt.getX()==endPt.getX())
    {
        //the same point
        if(startPt.getY()==endPt.getY())
        {
            std::cout<<"error!"<<endl;
            return;
        }
        //k doesn't exist
        else
        {
            while(linePt.getY()!=y_max)
            {
                linePt.incrementY();
                setPixel(startPt.getX(),linePt.getY());
            }
        }
    }
    //if k=0
    else if(startPt.getY()==endPt.getY())
    {
        while(linePt.getX()!=x_max)
        {
            linePt.incrementX();
            setPixel(linePt.getX(),startPt.getY());
        }
    }
    //swap with each other if startPt.getX()>endPt.getX()
    else if(startPt.getX()>endPt.getX())
    {
        x1=startPt.getX();
        y1=startPt.getY();
        x2=endPt.getX();
        y2=endPt.getY();
        swap(x1,x2);
        swap(y1,y2);
        startPt.setCoords(x1,y1);
        endPt.setCoords(x2,y2);
        Bresenham(startPt,endPt);
    }
    else
        Bresenham(startPt,endPt);
}

//Bresenham Algorithm
void Bresenham(screenPt startPt,screenPt endPt)
{
    GLint dx=endPt.getX()-startPt.getX(),dy=endPt.getY()-startPt.getY();
    GLint p=2*dy-dx;
    bool m=(abs(endPt.getY()-startPt.getY())<=abs(endPt.getX()-startPt.getX()));
    // |k|<1
    if(m)
    {
        //0<k<1
        if(startPt.getY()<=endPt.getY())
        {
            for(int k=0; k<dx; k++)
            {
                setPixel(startPt.getX(),startPt.getY());
                startPt.incrementX();
                if(p<0)
                    p+=2*dy;
                else
                {
                    startPt.incrementY();
                    p+=2*(dy-dx);
                }
            }
        }
        //-1<k<0
        else
        {
            p=dx-2*dy;
            for(int k=0; k<dx; k++)
            {
                setPixel(startPt.getX(),startPt.getY());
                startPt.incrementX();
                if(p<0)
                    p-=2*dy;
                else
                {
                    startPt.decrementY();
                    p-=2*(dx+dy);
                }
            }
        }
    }
    //|k|>1
    else
    {
        //k>1
        if(startPt.getY()<=endPt.getY())
        {
            p=2*dx-dy;
            for(int k=0; k<dy; k++)
            {
                setPixel(startPt.getX(),startPt.getY());
                startPt.incrementY();
                if(p<0)
                    p-=2*dy;
                else
                {
                    startPt.incrementX();
                    p-=2*(dx+dy);
                }
            }
        }
        //k<-1
        else
        {
            setPixel(startPt.getX(),startPt.getY());
            p=2*dx+dy;
            for(int k=0; k<dy; k++)
            {
                startPt.decrementY();
                if(p<0)
                    p+=2*dx;
                else
                {
                    startPt.incrementX();
                    p+=2*(dx+dy);
                }
            }
        }
    }
}

void draw_line(void)
{
    screenPt startPt,endPt;
    GLint x1,y1,x2,y2;
    cout<<"input (x1,y1):\t";
    cin>>x1>>y1;
    startPt.setCoords(x1,y1);
    cout<<"input (x2,y2):\t";
    cin>>x2>>y2;
    endPt.setCoords(x2,y2);
	glClearColor(1.0,1.0,1.0,0.0);
	glClear (GL_COLOR_BUFFER_BIT);
    BresenhamDraw(startPt,endPt);
}

void draw_coordinate()
{
	for(int k=0;k<high;k++)//draw y
	{ 
		glColor3f (0, 0, 0);
		glBegin(GL_POINTS);
			glVertex2i(width/2,k);
		glEnd();
		glFlush();
	}
	for(int k=0;k<width;k++)//draw x
	{ 
		glColor3f (0, 0, 0);
		glBegin(GL_POINTS);
			glVertex2i(k,high/2);
		glEnd();
		glFlush();
	}
}

void menu()
{
    int select=1;
	draw_coordinate();
    while(select)
    {
        cout<<"==================MENU====================="<<endl;
        cout<<"\t 1:draw bresenham line"<<endl;
        cout<<"\t 2:draw circle"<<endl;
        cout<<"\t 3:draw ellipse"<<endl;
		//cout<<"\t 4:clear the screen"<<endl;
        cout<<"\t 0:exit"<<endl;
        cout<<"==========================================="<<endl;
        cout<<"\t your select:\t\t";
        cin>>select;
        switch(select)
        {
        case 0:
            break;
        case 1:
            draw_line();
            break;
        case 2:
            draw_circle();
            break;
        case 3:
            draw_ellipse();
            break;
		 case 4:
			//glClear (GL_COLOR_BUFFER_BIT);
			// break;
        default:
            break;
        }
    }
    return;
}
#endif
