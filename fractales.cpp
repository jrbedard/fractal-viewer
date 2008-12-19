////////////////////////////////////////////////////////////////////////////////
// Name		: Fractales.cpp
// To		: Draw fractales with parameters control on a form created by windows 32api
// Author	: Jean-Rene Bedard (jrbedard@gmail.com)
// Date		: November 2000
// Known bugs: none
// Note     : You can freely use this code, change it and redistribute it
//           
////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "complex.h"
#include "resource.h"


void reset(HWND hwndDlg);
void fractals_preset();
void draw_fractal(HWND hwndDlg);



char Step_text[8];
char param_text[8];
char zoom_text[8];
char color_text[8];
char move_text[8];

int StepX;
int StepY;

double paramA;
double paramB;

float zoom;


double red_color;
double green_color;

float mod_x;
float mod_y;



// Draw a fractal
void DrawFractal(HDC hDC) 
	{
	// Fractal limits
	float x1=mod_x-1.0f*zoom;
	float x2=mod_x+1.0f*zoom;
	float y1=mod_y-1.0f*zoom;
	float y2=mod_y+1.0f*zoom;
	
	

	// Form properties
	int Xfrm=10; int Yfrm=10;
	int Width=600; int Height=600;
	
	
	
	// Drawing vars
	RECT r;
	HBRUSH brush;

	// Init
	//Complex C ((double)-0.0519, (double)0.688); default
	Complex C ((double)-paramA, (double)+paramB);
	Complex Z, Z0, Zt;
	int i;
	bool Fini;

	// Draw Fractal
	for (int x=0; x<Width; x+=StepX) 
	{
		for (int y=0; y<Height; y+=StepY) 
		{
			// Init Z to position (x,y) in space z([x1,y1],[x2,y2])
			Z=Z0=Complex((double)(x*(x2-x1)/Width+x1), (double)(y*(y2-y1)/Height+y1));
			Fini=false;

			// Find ecart
			for (i=0; i<100 && (!Fini); i++) 
			{
				Z=Z*Z+C;
				Zt=Z-Z0;				
				if (Zt.modulus()>4.0) Fini=true;
			}

			// Draw pixel or rectangle
			if (StepX==1 && StepY==1)
				SetPixel(hDC, x+Xfrm, y+Yfrm, RGB(sin(i*red_color/100)*255, sin(i*green_color/100)*200,255-i*2));
			else 
			{				
				brush=CreateSolidBrush(RGB(sin(i*red_color/100)*255, sin(i*green_color/100)*200,255-i*2));
				r.left=x+Xfrm; r.top=y+Yfrm;
				
				r.right=r.left+StepX; r.bottom=r.top+StepY;
				FillRect(hDC, &r, brush);
				DeleteObject(brush);
			}
		}
	}
} // DrawFractal



// Dialog box callback
BOOL CALLBACK DialogProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg)
	{	
		case WM_PAINT :
			RECT r;
			PAINTSTRUCT ps;

			// Redraw the fractal
			//DrawFractal(GetDC(hwndDlg));

			// Search minimal rect size wich contain the zone to be updated 
			if (GetUpdateRect(hwndDlg, &r, FALSE))
			{
				BeginPaint(hwndDlg, &ps);		// Update
				EndPaint(hwndDlg, &ps);
			}
			return FALSE;

		case WM_INITDIALOG:    
			
			reset(hwndDlg);
			return TRUE;
    
		case WM_COMMAND:   
			if(wParam==IDOK || wParam==IDCANCEL)
			EndDialog(hwndDlg,0);      
			
			
			if(wParam== IDC_LEFT)
			{
				GetDlgItemText(hwndDlg, IDC_MOVE, move_text,8);; 
				mod_x = mod_x - atof(move_text);
				wParam=IDDRAW;
			}
			
			
			if(wParam== IDC_RIGHT)
			{
				GetDlgItemText(hwndDlg, IDC_MOVE, move_text,8);; 
				mod_x = mod_x + atof(move_text);
				wParam=IDDRAW;
			}
			
			
			if(wParam== IDC_UP)
			{
				GetDlgItemText(hwndDlg, IDC_MOVE, move_text,8);; 
				mod_y = mod_y - atof(move_text);
				wParam=IDDRAW;
			}
			
			
			if(wParam== IDC_DOWN)
			{
				GetDlgItemText(hwndDlg, IDC_MOVE, move_text,8);; 
				mod_y = mod_y + atof(move_text);
				wParam=IDDRAW;
			}
			
			
			if(wParam== IDC_RESET)   // call for reseting parameters to default
			{
			reset(hwndDlg);
			}
			
			
			
			
			if(wParam==IDDRAW)
			{
			draw_fractal(hwndDlg);		
			}
		return TRUE;
	}
	return FALSE;
} 
 



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DLG_FRACTALS), HWND_DESKTOP, (DLGPROC)DialogProc, 0l); 
	return 0;
} // WinMain
 





void draw_fractal(HWND hwndDlg)
{

			//Step MOD
			GetDlgItemText(hwndDlg, IDCX, Step_text,8);
			StepX = atoi(Step_text);
			GetDlgItemText(hwndDlg, IDCY, Step_text,8);
			StepY = atoi(Step_text);
				
			//param MOD
			GetDlgItemText(hwndDlg, IDCPA, param_text,8);
			paramA = atof(param_text);
			GetDlgItemText(hwndDlg, IDCPB, param_text,8);
			paramB = atof(param_text);	
				
				
			GetDlgItemText(hwndDlg, IDCZOOMA, zoom_text,8);
			zoom = atof(zoom_text);
			zoom = 1/zoom;
				
			//colors
			GetDlgItemText(hwndDlg, IDCRED, color_text,8);
			red_color = atof(color_text);
			GetDlgItemText(hwndDlg, IDCGREEN, color_text,8);
			green_color = atof(color_text);	
				
			//draw fractal fractales 
			DrawFractal(GetDC(hwndDlg));

}









void reset(HWND hwndDlg) // Parameters by default
{

	SetDlgItemText(hwndDlg, IDCX, "1"); 
	SetDlgItemText(hwndDlg, IDCY, "1"); 
	SetDlgItemText(hwndDlg, IDCPA, "0.0519"); 
	SetDlgItemText(hwndDlg, IDCPB, "0.688"); 
	SetDlgItemText(hwndDlg, IDCZOOMA, "1"); 
	SetDlgItemText(hwndDlg, IDCRED, "3.1415"); 
	SetDlgItemText(hwndDlg, IDCGREEN, "3.1415"); 
	SetDlgItemText(hwndDlg, IDC_MOVE, "0.5"); 

}


void fractals_preset()
{
	





}