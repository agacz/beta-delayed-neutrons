#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TF2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TStyle.h"
using namespace std;

Double_t fn_square_hole_1D (Double_t *x, Double_t *a) {
	// a[0] = bin width, mm
	// a[1] = counts/mm
	// a[2] = low edge
	// a[3] = high edge
	if (a[2] < x[0] && x[0] < a[3]) return a[0]*a[1];
	else return 0.0;
}

Double_t fn_hole_1D (Double_t *x, Double_t *a) {
	// a[0] = bin width, mm
	// a[1] = const background, counts/mm^2
	// a[2] = amplitude of peak, counts/mm^2
	// a[3] = hole center, mm
	// a[4] = hole width parameter, mm
	// a[5] = power in the exponent of the "Gaussian"
	
	// Hole FWHM = 2*a[4]*(ln(2))^(1/n) where n is the power in the exponent of the "Gaussian"
	Double_t xPart = TMath::Exp( -TMath::Power((x[0]-a[3])/a[4], a[5]) );
	//Double_t fitval = a[0] * ( a[1] + a[2]*TMath::Exp( -TMath::Power((x[0]-a[3])/a[4], a[5]) ) );
	return a[0] * ( a[1] + a[2]*xPart );
}

Double_t fn_hole_2D (Double_t *x, Double_t *a) {
	// a[0] = bin width, mm -- assumed the same for X and Y bins
	// a[1] = const background, counts/mm^2
	// a[2] = amplitude of peak, counts/mm^2
	// a[3] = hole center in X, mm
	// a[4] = hole center in Y, mm
	// a[5] = hole width parameter in X, mm
	// a[6] = hole width parameter in Y, mm
	// a[7] = power in the exponent of the "Gaussian" -- assumed the same for X and Y bins
	
	// Hole FWHM = 2*a[4]*(ln(2))^(1/n) where n is the power in the exponent of the "Gaussian"
	Double_t xPart = TMath::Exp( -TMath::Power((x[0]-a[3])/a[5], a[7]) );
	Double_t yPart = TMath::Exp( -TMath::Power((x[1]-a[4])/a[5], a[7]) );
	return ( a[1] + a[2]*xPart*yPart ) * a[0] * a[0];
}

Double_t fn_surf (Double_t *x, Double_t *p) {
	Double_t h = 52.5; // distance from trap center to MCP in mm
	// p[0] = bin width mm
	// p[1] = avg MCP hits/mm^2
	// p[2] = peak in X, mm
	// p[3] = peak in Y, mm
	// p[4] = distance from trap center to MCP in mm
	// p[5] = MCP half-width mm
	Double_t s = TMath::Sqrt(TMath::Power(x[0],2.0)+TMath::Power(x[1],2.0));
	return p[1]*0.25*TMath::Power(p[0]/p[4],2.0)/TMath::ATan((p[5]/p[4])/TMath::Sqrt(2.0+TMath::Power(p[4]/p[5],2.0)))/TMath::Power(1+TMath::Power(s/p[4],2.0),1.5);
}

void fit_hole(char *filename, char *directory, char *histname, Int_t dim) {
//void fit_hole() {
	
	gROOT->Reset();
	
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_mask3.root");
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_mask2.root");
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_bothmasks.root");
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_nomask.root");
//	TFile *f = new TFile("~/135-Sb-2/run00155.root");
//	TFile *f = new TFile("~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask.root");
//	TFile *f = new TFile("~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root");
	TFile *f = new TFile(filename);
	f->cd(directory);
	cout << endl;
	cout << "Looking at file : " << filename << endl;
	cout << "Subdirectory    : " << directory << endl;
	cout << "Histogram       : " << histname << endl;
	gStyle->SetOptStat("e");
	
	if (dim==1) { // do fit in 1D
		
//		TH1I *hX	= (TH1I*)gDirectory->Get("h_R_mcpX");
//		TH1I *hX	= (TH1I*)gDirectory->Get("h_R_mcpX_1");
//		TH1I *hY	= (TH1I*)gDirectory->Get("h_T_mcpY_2");
		TH1I *hX	= (TH1I*)gDirectory->Get(histname);
		
//		Int_t rebin = 1;
//		Double_t bin_width = rebin*0.02;
		Double_t bin_width = hX->GetBinWidth(1);
		Double_t xMax = 1.0;
		Double_t yMax = 1.0;
		
		//hX->Rebin(rebin);
		//hX->GetXaxis()->SetRangeUser(-xMax,xMax);
		//hY->Rebin(rebin);
		//hY->GetXaxis()->SetRangeUser(-yMax,yMax);
		
		TCanvas *c_fit_1D = new TCanvas("c_fit_1D","1D fit",500,500);
		
		Double_t xCenter = -21.5;
//		Double_t yCenter = 20.0;
		Double_t power = 8.0;
		Double_t ln2 = 0.69314718;
		
//***** PICK A FUNCTION *****//	
//		TF1 *fX	= new TF1("fX", fn_hole_1D, xCenter-2.0, xCenter+2.0, 6);
//		fX->SetParameters(bin_width, 1000.0, 50000.0, xCenter, 0.15);
//		fX->SetParameters(bin_width, 1000.0, 50000.0, 0.0, 46.0);
//		fX->SetParNames("Bin width", "Constant", "Amplitude", "Centroid", "Width", "Power");
//		fX->FixParameter(0, bin_width);
//		fX->FixParameter(5, power);
		
		TF1 *fX	= new TF1("fX", fn_square_hole_1D, -25.0, 25.0, 4);
		fX->SetParameters(bin_width, 23000.0, -21.6, 22);
		fX->SetParNames("Bin width", "Amplitude", "Low edge", "High edge");
		fX->FixParameter(0, bin_width);
// **************************//
		
//		hX->Fit("fX","");
		
		Double_t fitCenterX = fX->GetParameter(3);
		Double_t fitSigmaX = fX->GetParameter(4);
		Double_t lowerEdgeX = fitCenterX - fitSigmaX*TMath::Power(ln2,1.0/power);
		Double_t upperEdgeX = fitCenterX + fitSigmaX*TMath::Power(ln2,1.0/power);
		
		printf("\nX (lower edge, upper edge): (%f, %f)\n\n", lowerEdgeX, upperEdgeX);
		
		gStyle->SetOptStat(10);
//		hX->GetXaxis()->SetRangeUser(xCenter-2.0,xCenter+2.0);
		hX->Draw();
	}
	
	if (dim==2) { // do 2D fit
		TH2I *h	= (TH2I*)gDirectory->Get(histname);
		
		Int_t rebin = 1;
		Double_t bin_width = rebin * h->GetBinWidth(1);
		cout << endl << "Bin width = " << bin_width << endl << endl;
		
//		Double_t xMax = 25.0;
//		Double_t yMax = 25.0;
		
		h->RebinX(rebin);
		h->RebinY(rebin);
//		h->GetXaxis()->SetRangeUser(-xMax,xMax);
//		hY->Rebin(rebin);
//		hY->GetXaxis()->SetRangeUser(-yMax,yMax);
		
		Int_t doFit = 1;
		Int_t physicalMap = 0;
		
		Double_t amp = 1000000.1;
//		Double_t xCenter = -0.005;// center of peak
//		Double_t yCenter = -0.005;
//		Double_t xCenter = -0.8;// center of peak
//		Double_t yCenter = 0.8;
		Double_t xCenter = -0.36;// center of peak
		Double_t yCenter = 0.775;
		Double_t xWindow = 1.0 * 0.05;//~1mm
		Double_t yWindow = 1.0 * 0.05;//~1mm
		Double_t xHWHM = 0.0112;// half width half max
//		Double_t yHWHM = 0.015;
		Double_t power = 8;// 2 is gaussian, larger means more square-ish
		Double_t ln2 = 0.69314718;
		Double_t xWidth = xHWHM/TMath::Power(ln2,1.0/power);
		Double_t yWidth = xHWHM/TMath::Power(ln2,1.0/power);
		
//		h->GetXaxis()->SetRangeUser(xCenter-xWindow,xCenter+xWindow);
//		h->GetYaxis()->SetRangeUser(yCenter-yWindow,yCenter+yWindow);
		Double_t xMin = bin_width*TMath::Floor((xCenter-xWindow)/bin_width);
		Double_t xMax = bin_width*TMath::Floor((xCenter+xWindow)/bin_width);
		Double_t yMin = bin_width*TMath::Floor((yCenter-yWindow)/bin_width);
		Double_t yMax = bin_width*TMath::Floor((yCenter+yWindow)/bin_width);
//		h->GetXaxis()->SetRangeUser(xMin,xMax);
//		h->GetYaxis()->SetRangeUser(yMin,yMax);
		h->GetXaxis()->SetTitle("x");
		h->GetYaxis()->SetTitle("y");
		
		if (physicalMap) {
			xWindow *= 30;
			yWindow *= 30;
			xCenter *= 30;
			yCenter *= 30;
			xWidth *= 30;
			yWidth *= 30;
		}
		
		TF2 *fn	= new TF2("fn", fn_hole_2D, xCenter-xWindow, xCenter+xWindow, yCenter-yWindow, yCenter+yWindow, 8);
		fn->SetParameters(bin_width, 0, amp, xCenter, yCenter, xWidth, yWidth, power);
		fn->SetParNames("Bin width", "Constant", "Amplitude", "X center", "Y center", "X width ", "Y width ", "Power");
		
		if (doFit) {
			fn->FixParameter(0, bin_width);
//			fn->FixParameter(1, 0);// constant = 0
			fn->FixParameter(6, 0);// yWidth set equal to xWidth (a[5]) in func
			fn->FixParameter(7, power);
			h->Fit("fn","LLEMR");
			
			Double_t fitCenterX = fn->GetParameter(3);
			Double_t fitCenterY = fn->GetParameter(4);
			Double_t fitSigmaX = fn->GetParameter(5);
			Double_t fitSigmaY = fn->GetParameter(5);
//			Double_t fitSigmaY = fn->GetParameter(6);
			Double_t fitCenterXerr = fn->GetParError(3);
			Double_t fitCenterYerr = fn->GetParError(4);
			Double_t fitSigmaXerr = fn->GetParError(5);
			Double_t fitSigmaYerr = fn->GetParError(5);
//			Double_t fitSigmaYerr = fn->GetParError(6);
			
			Double_t lowerEdgeX = fitCenterX - fitSigmaX*TMath::Power(ln2,1.0/power);
			Double_t upperEdgeX = fitCenterX + fitSigmaX*TMath::Power(ln2,1.0/power);
			Double_t lowerEdgeY = fitCenterY - fitSigmaY*TMath::Power(ln2,1.0/power);
			Double_t upperEdgeY = fitCenterY + fitSigmaY*TMath::Power(ln2,1.0/power);
			
			Double_t lowerEdgeXerr = TMath::Sqrt( TMath::Power(fitCenterXerr,2) + TMath::Power(fitSigmaXerr,2) * TMath::Power(ln2,2.0/power) );
			Double_t upperEdgeXerr = TMath::Sqrt( TMath::Power(fitCenterXerr,2) + TMath::Power(fitSigmaXerr,2) * TMath::Power(ln2,2.0/power) );
			Double_t lowerEdgeYerr = TMath::Sqrt( TMath::Power(fitCenterYerr,2) + TMath::Power(fitSigmaYerr,2) * TMath::Power(ln2,2.0/power) );
			Double_t upperEdgeYerr = TMath::Sqrt( TMath::Power(fitCenterYerr,2) + TMath::Power(fitSigmaYerr,2) * TMath::Power(ln2,2.0/power) );
			
			cout << "HWHM = " << fitSigmaX*TMath::Power(ln2,1.0/power) << endl;
			printf("\nX (lower edge, upper edge): (%f, %f). Unc = %f on both", lowerEdgeX, upperEdgeX, lowerEdgeXerr);
			printf("\nY (lower edge, upper edge): (%f, %f). Unc = %f on both\n\n", lowerEdgeY, upperEdgeY, lowerEdgeYerr);
			
			TCanvas *c_fit_2D = new TCanvas("c_fit_2D","2D fit",500,500);
//			gStyle->SetOptStat(10);
//			gStyle->SetOptFit(1110);
			h->Draw();
//			fn->DrawCopy("surf3 same");
//			h->Draw();
//			fn->DrawCopy("cont1 same");
		}
		else {
		//	h->Draw("LEGO");
		//	fn->DrawCopy("surf3 SAME");
//			h->Draw("COLZ");
//			fn->DrawCopy("colz");
//			h->Draw("colz same");
//			fn->Draw("surf1");
			TCanvas *c_hole_2D = new TCanvas("c_hole_2D","2D hole",500,500);
			h->Draw();//"colz");
			gPad->Update();
			TPaveStats *stats_2 = (TPaveStats*)h->FindObject("stats");
			if (1) {
				gStyle->SetOptStat("emr");
				gStyle->SetStatFormat("8.6g");
				stats_2->SetX1NDC(.13);
				stats_2->SetX2NDC(.32);
				stats_2->SetY1NDC(.80);
				stats_2->SetY2NDC(.92);
				gPad->Update();
			}
			else {
				gStyle->SetOptStat("e");
				stats_2->SetX1NDC(0.4);
				stats_2->SetX2NDC(0.6);
				//stats_2->SetY1NDC(0.92);
				//stats_2->SetY2NDC(1.00);
				gPad->Update();
			}
			c_hole_2D->Modified();
		}
		
		Double_t window = 2*xWindow;
		Int_t xBinLo = 1 + TMath::Floor((xCenter-xWindow-(-1.0))/bin_width);
		Int_t xBinHi = 1 + TMath::Floor((xCenter+xWindow-(-1.0))/bin_width);
		Int_t yBinLo = 1 + TMath::Floor((yCenter-yWindow-(-1.0))/bin_width);
		Int_t yBinHi = 1 + TMath::Floor((yCenter+yWindow-(-1.0))/bin_width);
		Int_t i, j;
		Double_t sum=0, wSumX=0, wSumY=0;
		Double_t xVal, yVal, binVal;
		
		// diagnostic
		cout << "xBinLo = " << xBinLo << endl;
		cout << "xBinHi = " << xBinHi << endl;
		cout << "yBinLo = " << yBinLo << endl;
		cout << "yBinHi = " << yBinHi << endl;
		
		Double_t xCOM = 1;
		Double_t yCOM = 1;
//		Double_t xCOM_old = 0;
//		Double_t yCOM_old = 0;
//		
//		while (xCOM!=xCOM_old || yCOM!=yCOM_old) {
			for ( i = xBinLo; i<xBinHi; i++) {
				for ( j = yBinLo; j<yBinHi; j++) {
					xVal = xCenter-xWindow + bin_width*(i-xBinLo);
					yVal = yCenter-yWindow + bin_width*(j-yBinLo);
//					cout << "xVal = " << xVal << ", yVal = " << yVal << endl; // diagnostic
					binVal = h->GetBinContent(i,j);
					wSumX += xVal*binVal;
					wSumY += yVal*binVal;
					sum += binVal;
				}
			}
//			
//			xCOM_old = xCOM;
//			yCOM_old = yCOM;
			xCOM = wSumX/sum;//center of mass in x
			yCOM = wSumY/sum;//center of mass in y
			cout << endl << "Number of counts    = " << sum  << endl;
			cout << "x center of mass = " << xCOM << endl;
			cout << "y center of mass = " << yCOM << endl << endl;
//			sum = 0;
//			Double_t window = 2*xWindow;
//			xCenter = xCOM;
//			yCenter = yCOM;
//			xBinLo = 1 + TMath::Floor((xCenter-xWindow-(-1.0))/bin_width);
//			xBinHi = 1 + TMath::Floor((xCenter+xWindow-(-1.0))/bin_width);
//			yBinLo = 1 + TMath::Floor((yCenter-yWindow-(-1.0))/bin_width);
//			yBinHi = 1 + TMath::Floor((yCenter+yWindow-(-1.0))/bin_width);
//			sum=0;
//			wSumX=0;
//			wSumY=0;
//		} // while
//		
//	// Recenter the plot on found centers of mass
//		xMin = bin_width*TMath::Floor((xCenter-xWindow)/bin_width);
//		xMax = bin_width*TMath::Floor((xCenter+xWindow)/bin_width);
//		yMin = bin_width*TMath::Floor((yCenter-yWindow)/bin_width);
//		yMax = bin_width*TMath::Floor((yCenter+yWindow)/bin_width);
//		TF1 *fXline = new TF1("fXline","[1]+[2]*(x-[0])",xMin,xMax);
//		TF1 *fYline = new TF1("fYline","[1]+[2]*(x-[0])",xMin,xMax);
//		fXline->SetParameters(xCenter,yCenter,0);
//		fYline->SetParameters(xCenter,yCenter,1000000000);
//		h->GetXaxis()->SetRangeUser(xMin,xMax);
//		h->GetYaxis()->SetRangeUser(yMin,yMax);
//		fXline->Draw("same");
//		fYline->Draw("same");
		
		wSumX = 0;
		wSumY = 0;
		sum   = 0;
		for ( i = xBinLo; i<xBinHi; i++) {
			for ( j = yBinLo; j<yBinHi; j++) {
				xVal = xCenter-xWindow + bin_width*(i-xBinLo);
				yVal = yCenter-yWindow + bin_width*(j-yBinLo);
//				cout << "xVal = " << xVal << ", yVal = " << yVal << endl; // diagnostic
				binVal = h->GetBinContent(i,j);
				wSumX += TMath::Power(xVal-xCOM,2.0) * binVal;
				wSumY += TMath::Power(yVal-yCOM,2.0) * binVal;
				
				sum += binVal;
			}
		}
		
		Double_t xRMS = TMath::Power(wSumX/sum,0.5);//center of mass in x
		Double_t yRMS = TMath::Power(wSumY/sum,0.5);//center of mass in y
		cout << "x standard deviation = " << xRMS << endl;
		cout << "y standard deviation = " << yRMS << endl << endl;
		cout << "Number of counts    = " << sum  << endl;
		cout << "x c.o.m. std error   = " << xRMS/TMath::Sqrt(sum) << endl;
		cout << "y c.o.m. std error   = " << yRMS/TMath::Sqrt(sum) << endl << endl;
	}
}

void find_active_area(char *filename, char *histname) {
	
	using namespace TMath;
	using namespace std;
	
	gROOT->Reset();
	TFile *f = new TFile(filename);
//	f->cd("mcp_cal");
	f->cd("mcp_cal_pedSubtract");
	TH2I *h	= (TH2I*)gDirectory->Get(histname);
	TH2I *h_binary	= (TH2I*)gDirectory->Get(histname);
	Double_t bin_width = h->GetBinWidth(1);
	Int_t sum = h->Integral();
	Int_t mySum = 0;
	Int_t nX = h->GetNbinsX();
	Int_t nY = h->GetNbinsY();
	
	if (1) {
		TCanvas *c_map_area = new TCanvas("c_map_area","Map for area calculation",500,500);
		h->Draw("colz");
		gStyle->SetOptStat("e");
	}
	
	cout << "# of entries = " << sum << endl;
	cout << "# bins in x = " << nX << endl;
	cout << "# bins in y = " << nY << endl;
	
	Double_t Y_mean = sum/(Double_t)nX/nY;
	Double_t Y_threshold = 1;//1.5;//0.15 * Y_mean;
	cout << "Mean bin height = " << Y_mean << endl;
	cout << "Bin threshold = " << Y_threshold << endl;
	
	Int_t i, j;
	Double_t dA, area = 0, fiducialArea = 0;
	
	// Little (x,y) is coord in data, range is -1 to 1
	// Big (X,Y) is coord on physical MCP, range is about -25mm to 25mm
	Double_t x, y, X, Y, dx, dy, dX, dY, xR, yR, XR, YR, dxR, dyR, dXR, dYR;
	Double_t x1,y1,X1,Y1,xR1,yR1,XR1,YR1;
	Double_t x2,y2,X2,Y2,xR2,yR2,XR2,YR2;
	Double_t x3,y3,X3,Y3,xR3,yR3,XR3,YR3;
	Double_t d2X, d2Y, d3X, d3Y;
	
	// Model parameters (Right MCP)
//	Double_t a0 = 27.1483;// + 0.2138;//27.276;
//	Double_t a2 = 0.289615;// + 0.255794;//0.0072812;
//	Double_t b0 = 27.0965;// + 0.2129;//27.276;
//	Double_t b2 = .239176;// + 0.252428;//0.0072812;
//	Double_t x0 = -0.007298;// + .001995;//-0.006710;
//	Double_t y0 = -0.010548;// + .001999;//-0.008208;
//	Double_t theta = 0.00487232;// + 0.00257631;
	
	// Model parameters (Top MCP)
//	Double_t a0 = 25.2320;// + 0.4318;
//	Double_t b0 = 25.3495;// + 0.4297;
//	Double_t a2 = 0.881473;// + 0.398064;
//	Double_t b2 = 0.630362;// + 0.390002;
//	Double_t theta = 0.00317114;// + 0.00452762;
//	Double_t x0 = 0.003478;// + 0.003365;
//	Double_t y0 = 0.021504;// + 0.003365;
	Double_t a0 = 25.8458;// + 0.4318;
	Double_t b0 = 25.9646;// + 0.4297;
	Double_t a2 = 0.389363;// + 0.398064;
	Double_t b2 = 0.144626;// + 0.390002;
	Double_t theta = 0.00302517;// + 0.00452762;
	Double_t x0 = 0.004707;// + 0.003365;
	Double_t y0 = 0.021184;// + 0.003365;
	
	for (i=1; i<=nX; i++) {
		for (j=1; j<=nY; j++) {
			
			// In general, area dA can depend on x and y: dA(x,y)
			x = h->GetXaxis()->GetBinCenter(i);// Get x
			y = h->GetYaxis()->GetBinCenter(j);// Get y
//			cout << "Bin center = (" << x << "," << y << ")" << endl;
			
			// Calculate dA(x,y)
//			X = a1*(x-x0)/(Cos(theta)-a2*(x-x0));
//			Y = a1*(y-y0)/(Cos(theta)-a2*(y-y0));
//			dX = dx / ( a1*Cos(theta) / Power( a1 + a2*X , 2.0 ) );
//			dY = dy / ( a1*Cos(theta) / Power( a1 + a2*Y , 2.0 ) );

/*************************************			
// Model quadratic along diagonal
			xR = (x-x0)*Cos(theta+Pi()/4) - (y-y0)*Sin(theta+Pi()/4);
			yR = (x-x0)*Sin(theta+Pi()/4) + (y-y0)*Cos(theta+Pi()/4);
//			XR = (a0 + a2*xR*xR) * xR;
//			YR = (b0 + b2*yR*yR) * yR;
//			X = XR*Cos(-Pi()/4) - YR*Sin(-Pi()/4);
//			Y = XR*Sin(-Pi()/4) + YR*Cos(-Pi()/4);
			dx = bin_width;
			dy = bin_width;
//			dxR = dx*Cos(theta+Pi()/4) - dy*Sin(theta+Pi()/4);
//			dyR = dx*Sin(theta+Pi()/4) + dy*Cos(theta+Pi()/4);
// Rotation preserves area
			dXR = (a0 + 3*a2*xR*xR) * dx;
			dYR = (b0 + 3*b2*yR*yR) * dy;
			dX = dXR*Cos(-Pi()/4) - dYR*Sin(-Pi()/4);
			dY = dXR*Sin(-Pi()/4) + dYR*Cos(-Pi()/4);
// Rotation preserves area
			dA = dXR * dYR;
*/			
///*
// Use this instead to avoid linearization error
//Three initial vectors in (x,y) space
			x1 = x - 0.5*bin_width;
			y1 = y - 0.5*bin_width;
			x2 = x1 + bin_width;
			y2 = y1;
			x3 = x1;
			y3 = y1 + bin_width;
// (x1,y1) is where we are on the surface
// (x2,y2) = (x1+dx,y1)
// (x3,y3) = (x1,y1+dx)
// Transform all three to get (Xi,Yi)
// Determine the area from the relevant cross product

// Transformation (nonlinear!)
			xR1 = (x1-x0)*Cos(theta+Pi()/4) - (y1-y0)*Sin(theta+Pi()/4);
			yR1 = (x1-x0)*Sin(theta+Pi()/4) + (y1-y0)*Cos(theta+Pi()/4);
			xR2 = (x2-x0)*Cos(theta+Pi()/4) - (y2-y0)*Sin(theta+Pi()/4);
			yR2 = (x2-x0)*Sin(theta+Pi()/4) + (y2-y0)*Cos(theta+Pi()/4);
			xR3 = (x3-x0)*Cos(theta+Pi()/4) - (y3-y0)*Sin(theta+Pi()/4);
			yR3 = (x3-x0)*Sin(theta+Pi()/4) + (y3-y0)*Cos(theta+Pi()/4);
			
			XR1 = (a0 + a2*xR1*xR1) * xR1;
			YR1 = (b0 + b2*yR1*yR1) * yR1;
			XR2 = (a0 + a2*xR2*xR2) * xR2;
			YR2 = (b0 + b2*yR2*yR2) * yR2;
			XR3 = (a0 + a2*xR3*xR3) * xR3;
			YR3 = (b0 + b2*yR3*yR3) * yR3;
			
			X1 = XR1*Cos(-Pi()/4) - YR1*Sin(-Pi()/4);
			Y1 = XR1*Sin(-Pi()/4) + YR1*Cos(-Pi()/4);
			X2 = XR2*Cos(-Pi()/4) - YR2*Sin(-Pi()/4);
			Y2 = XR2*Sin(-Pi()/4) + YR2*Cos(-Pi()/4);
			X3 = XR3*Cos(-Pi()/4) - YR3*Sin(-Pi()/4);
			Y3 = XR3*Sin(-Pi()/4) + YR3*Cos(-Pi()/4);

// Need the two differnce vectors after the transform 
			d2X = X2-X1;
			d2Y = Y2-Y1;
			d3X = X3-X1;
			d3Y = Y3-Y1;
// d(Area) is the cross product of these diff vectors
			dA = d2X*d3Y-d3X*d2Y;//(X2-X1) * (Y2-Y1);
//*/			
//			cout << "(x,y)=(" << x << "," << y << "); (dXR,dYR)=(" << dXR << "," << dYR << "); (dX,dY)=(" << dX << "," << dY << "); Area=" << dXR * dYR << endl;
//			cout << "(x,y)=(" << x << "," << y << "); (dXR,dYR)=(" << XR2-XR1 << "," << YR2-YR1 << "); (dX,dY)=(" << X2-X1 << "," << Y2-Y1 << "); Area=" << (X2-X1) * (Y2-Y1) << endl;

			// Add this bit of area
			// If there are enough events in this bin...
			if ( h->GetBinContent(i,j) > Y_threshold ) {
				area += dA;
			}	
			if (-0.888 <= x && x <= 0.865 && -0.852 <= y && y <= 0.866) {// fiducial region for TOP MCP
				fiducialArea += dA;
			}
		}
	}
	
//	Also make a plot showing the prediction of the outer area.

	cout << "Active area = " << area << " mm^2" << endl;
	cout << "Side length of a square with this area = " << TMath::Sqrt(area) << " mm" << endl;
	cout << "Fiducial area = " << fiducialArea << " mm^2" << endl;
	cout << "Side length of a square with this area = " << TMath::Sqrt(fiducialArea) << " mm" << endl;
	cout << endl;
	
}
/* DEPRECATED
void fit_1D() {
	
	gROOT->Reset();
	
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_mask3.root");
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_mask2.root");
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_bothmasks.root");
//	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_nomask.root");
//	TFile *f = new TFile("~/135-Sb-2/run00155.root");
//	TFile *f = new TFile("~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask.root");
	TFile *f = new TFile("~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root");
	
	f->cd("mcp_cal");

	//TH1I *hX	= (TH1I*)gDirectory->Get("h_R_mcpX");
	TH1I *hX	= (TH1I*)gDirectory->Get("h_R_mcpX_1");
	//TH1I *hY	= (TH1I*)gDirectory->Get("h_T_mcpY_2");
	
	Int_t rebin = 1;
	Double_t bin_width = rebin*0.02; // mm
	//Double_t xMax = 25.0;
	//Double_t yMax = 25.0;
	
	//hX->Rebin(rebin);
	//hX->GetXaxis()->SetRangeUser(-xMax,xMax);
	//hY->Rebin(rebin);
	//hY->GetXaxis()->SetRangeUser(-yMax,yMax);
	
	TCanvas *c_fit_1D = new TCanvas("c_fit_1D","1D fit",500,500);
	
	Double_t xCenter = -21.5;
//	Double_t yCenter = 20.0;
	Double_t power = 80.0;
	Double_t ln2 = 0.69314718;

///////// PICK A FUNCTION //////////	
//	TF1 *fX	= new TF1("fX", fn_hole_1D, xCenter-2.0, xCenter+2.0, 6);
//	fX->SetParameters(bin_width, 1000.0, 50000.0, xCenter, 0.15);
//	fX->SetParameters(bin_width, 1000.0, 50000.0, 0.0, 46.0);
//	fX->SetParNames("Bin width", "Constant", "Amplitude", "Centroid", "Width", "Power");
//	fX->FixParameter(0, bin_width);
//	fX->FixParameter(5, power);
	
	TF1 *fX	= new TF1("fX", fn_square_hole_1D, -25.0, 25.0, 4);
	fX->SetParameters(bin_width, 23000.0, -21.6, 22);
	fX->SetParNames("Bin width", "Amplitude", "Low edge", "High edge");
	fX->FixParameter(0, bin_width);
	
//	hX->Fit("fX","");
	
	Double_t fitCenterX = fX->GetParameter(3);
	Double_t fitSigmaX = fX->GetParameter(4);
	Double_t lowerEdgeX = fitCenterX - fitSigmaX*TMath::Power(ln2,1.0/power);
	Double_t upperEdgeX = fitCenterX + fitSigmaX*TMath::Power(ln2,1.0/power);
	
	printf("\nX (lower edge, upper edge): (%f, %f)\n\n", lowerEdgeX, upperEdgeX);
	
	gStyle->SetOptStat(10);
//	hX->GetXaxis()->SetRangeUser(xCenter-2.0,xCenter+2.0);
	hX->Draw();
	
}

void fit_2D() {
	
	gROOT->Reset();
	
	//TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_mask3.root");
	//TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_mask2.root");
	//TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_bothmasks.root");
	//TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_nomask.root");
	TFile *f = new TFile("~/135-Sb-2/run00155.root");
	
	f->cd("mcp_cal");
	
	TH2I *h	= (TH2I*)gDirectory->Get("h_T_mcp_map_2");
	//TH1I *hY	= (TH1I*)gDirectory->Get("h_T_mcpY_2");
	
	Int_t rebin = 2;
	Double_t bin_width = rebin*0.1; // mm
	//Double_t xMax = 25.0;
	//Double_t yMax = 25.0;
	
	h->RebinX(rebin);
	h->RebinY(rebin);
	//h->GetXaxis()->SetRangeUser(-xMax,xMax);
	//hY->Rebin(rebin);
	//hY->GetXaxis()->SetRangeUser(-yMax,yMax);
	
	TCanvas *c_fit_2D = new TCanvas("c_fit_2D","2D fit",500,500);
	
	Double_t xWindow = 1.0;
	Double_t yWindow = 1.0;
	Double_t xCenter = 0.6;
	Double_t yCenter = -0.5;
	Double_t xWidth = 0.5;
	Double_t yWidth = 0.5;
	Double_t power = 4.0;
	Double_t ln2 = 0.69314718;
	
	TF2 *fn	= new TF2("fn", fn_hole_2D, xCenter-xWindow, xCenter+xWindow, yCenter-yWindow, yCenter+yWindow, 8);
	fn->SetParameters(bin_width, 12.0, 800.0, xCenter, yCenter, xWidth, yWidth, power);
	fn->SetParNames("Bin width", "Constant", "Amplitude", "X center", "Y center", "X width ", "Y width ", "Power");
	fn->FixParameter(0, bin_width);
	fn->FixParameter(7, power);
	
	h->Fit("fn","");
	
	Double_t fitCenterX = fn->GetParameter(3);
	Double_t fitCenterY = fn->GetParameter(4);
	Double_t fitSigmaX = fn->GetParameter(5);
	Double_t fitSigmaY = fn->GetParameter(6);
	Double_t lowerEdgeX = fitCenterX - fitSigmaX*TMath::Power(ln2,1.0/power);
	Double_t upperEdgeX = fitCenterX + fitSigmaX*TMath::Power(ln2,1.0/power);
	Double_t lowerEdgeY = fitCenterY - fitSigmaY*TMath::Power(ln2,1.0/power);
	Double_t upperEdgeY = fitCenterY + fitSigmaY*TMath::Power(ln2,1.0/power);
	
	printf("\nX (lower edge, upper edge): (%f, %f)", lowerEdgeX, upperEdgeX);
	printf("\nY (lower edge, upper edge): (%f, %f)\n\n", lowerEdgeY, upperEdgeY);
	
	//gStyle->SetOptStat(10);
	gStyle->SetOptFit(1110);
	h->GetXaxis()->SetRangeUser(xCenter-2.0,xCenter+2.0);
	h->GetYaxis()->SetRangeUser(yCenter-2.0,yCenter+2.0);
	
	fn->Draw("surf3");//"SAME");
	h->Draw("SAME LEGO");
	
}
*/

/* TROUBLE COMPILING
void draw_surf() {
	
	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_nomask.root");
	//TFile *f = new TFile("~/135-Sb-2/run00174.root");
	f->cd("mcp_cal");
	
	TH2I *h	= (TH2I*)gDirectory->Get("h_T_mcp_map_2");
	
	Int_t rebin = 5;
	Double_t bin_width = rebin*0.1; // mm
	Double_t xMax = 20.0;
	Double_t yMax = 20.0;
	
	h->RebinX(rebin);
	h->RebinY(rebin);
	h->GetXaxis()->SetRangeUser(-xMax,xMax);
	h->GetYaxis()->SetRangeUser(-yMax,yMax);
	Double_t zMax = h->GetZaxis()->GetXmax();
	h->GetZaxis()->SetRangeUser(0,zMax);
	
	TCanvas *c_mcp_surf_1 = new TCanvas("c_mcp_surf_1","MCP surface colz",650,650);
	gStyle->SetOptStat(0);
	h->Draw("colz");
	
	TF2 *fn = new TF2("fn", fn_surf, -xMax, xMax, -yMax, yMax, 4);
	fn->SetParameters(bin_width, 500.0, 52.3, 24.0);
	fn->SetParNames("Bin width", "Constant", "MCP dist", "MCP half-width");
	fn->FixParameter(0, bin_width);
	fn->FixParameter(2, 52.3);
	//fn->FixParameter(3, 24.0);
	
	TCanvas *c_mcp_surf_2 = new TCanvas("c_mcp_surf_2","MCP surface lego",650,650);
	h->Fit("fn","RM");
	gStyle->SetOptFit(1110);
	//fn->Draw("surf3");
	h->Draw("LEGO");
	
}

void gain() {
	
	TFile *f = new TFile("~/135-Sb-2/sum_mcp_cal_nomask.root");
	//TFile *f = new TFile("~/135-Sb-2/run00174.root");
	f->cd("mcp_cal");
	
	TH1I *h_qA_mcpA	= (TH1I*)gDirectory->Get("h_T_mcpA_qA_2");
	TH1I *h_qA_mcpB	= (TH1I*)gDirectory->Get("h_T_mcpB_qA_2");
	TH1I *h_qA_mcpC	= (TH1I*)gDirectory->Get("h_T_mcpC_qA_2");
	TH1I *h_qA_mcpD	= (TH1I*)gDirectory->Get("h_T_mcpD_qA_2");
	TH1I *h_qA_mcpS	= (TH1I*)gDirectory->Get("h_T_mcpSum_qA_2");
	TH1I *h_qA_mcpX	= (TH1I*)gDirectory->Get("h_T_mcpX_qA_2");
	TH1I *h_qA_mcpY	= (TH1I*)gDirectory->Get("h_T_mcpY_qA_2");
	
	TH1I *h_qB_mcpA	= (TH1I*)gDirectory->Get("h_T_mcpA_qB_2");
	TH1I *h_qB_mcpB	= (TH1I*)gDirectory->Get("h_T_mcpB_qB_2");
	TH1I *h_qB_mcpC	= (TH1I*)gDirectory->Get("h_T_mcpC_qB_2");
	TH1I *h_qB_mcpD	= (TH1I*)gDirectory->Get("h_T_mcpD_qB_2");
	TH1I *h_qB_mcpS	= (TH1I*)gDirectory->Get("h_T_mcpSum_qB_2");
	TH1I *h_qB_mcpX	= (TH1I*)gDirectory->Get("h_T_mcpX_qB_2");
	TH1I *h_qB_mcpY	= (TH1I*)gDirectory->Get("h_T_mcpY_qB_2");
	
	TH1I *h_qC_mcpA	= (TH1I*)gDirectory->Get("h_T_mcpA_qC_2");
	TH1I *h_qC_mcpB	= (TH1I*)gDirectory->Get("h_T_mcpB_qC_2");
	TH1I *h_qC_mcpC	= (TH1I*)gDirectory->Get("h_T_mcpC_qC_2");
	TH1I *h_qC_mcpD	= (TH1I*)gDirectory->Get("h_T_mcpD_qC_2");
	TH1I *h_qC_mcpS	= (TH1I*)gDirectory->Get("h_T_mcpSum_qC_2");
	TH1I *h_qC_mcpX	= (TH1I*)gDirectory->Get("h_T_mcpX_qC_2");
	TH1I *h_qC_mcpY	= (TH1I*)gDirectory->Get("h_T_mcpY_qC_2");
	
	TH1I *h_qD_mcpA	= (TH1I*)gDirectory->Get("h_T_mcpA_qD_2");
	TH1I *h_qD_mcpB	= (TH1I*)gDirectory->Get("h_T_mcpB_qD_2");
	TH1I *h_qD_mcpC	= (TH1I*)gDirectory->Get("h_T_mcpC_qD_2");
	TH1I *h_qD_mcpD	= (TH1I*)gDirectory->Get("h_T_mcpD_qD_2");
	TH1I *h_qD_mcpS	= (TH1I*)gDirectory->Get("h_T_mcpSum_qD_2");
	TH1I *h_qD_mcpX	= (TH1I*)gDirectory->Get("h_T_mcpX_qD_2");
	TH1I *h_qD_mcpY	= (TH1I*)gDirectory->Get("h_T_mcpY_qD_2");
	
	TH1I *h_qCenter_mcpA	= (TH1I*)gDirectory->Get("h_T_mcpA_qCenter_2");
	TH1I *h_qCenter_mcpB	= (TH1I*)gDirectory->Get("h_T_mcpB_qCenter_2");
	TH1I *h_qCenter_mcpC	= (TH1I*)gDirectory->Get("h_T_mcpC_qCenter_2");
	TH1I *h_qCenter_mcpD	= (TH1I*)gDirectory->Get("h_T_mcpD_qCenter_2");
	TH1I *h_qCenter_mcpS	= (TH1I*)gDirectory->Get("h_T_mcpSum_qCenter_2");
	TH1I *h_qCenter_mcpX	= (TH1I*)gDirectory->Get("h_T_mcpX_qCenter_2");
	TH1I *h_qCenter_mcpY	= (TH1I*)gDirectory->Get("h_T_mcpY_qCenter_2");
	
	Double_t qA_entries = h_qA_mcpS->GetEntries();
	Double_t qB_entries = h_qB_mcpS->GetEntries();
	Double_t qC_entries = h_qC_mcpS->GetEntries();
	Double_t qD_entries = h_qD_mcpS->GetEntries();
	Double_t qCenter_entries = h_qCenter_mcpS->GetEntries();
	
	Double_t qA_mean = h_qA_mcpS->GetMean();
	Double_t qB_mean = h_qB_mcpS->GetMean();
	Double_t qC_mean = h_qC_mcpS->GetMean();
	Double_t qD_mean = h_qD_mcpS->GetMean();
	Double_t qCenter_mean = h_qCenter_mcpS->GetMean();
	
	Double_t qA_sigma = qA_mean/TMath::Sqrt(qA_entries);
	Double_t qB_sigma = qB_mean/TMath::Sqrt(qB_entries);
	Double_t qC_sigma = qC_mean/TMath::Sqrt(qC_entries);
	Double_t qD_sigma = qD_mean/TMath::Sqrt(qD_entries);
	Double_t qCenter_sigma = qCenter_mean/TMath::Sqrt(qCenter_entries);
	
	printf("\nQuadrant A entries = %d\n", (Int_t)qA_entries);
	printf("Quadrant B entries = %d\n", (Int_t)qB_entries);
	printf("Quadrant C entries = %d\n", (Int_t)qC_entries);
	printf("Quadrant D entries = %d\n", (Int_t)qD_entries);
	printf("Cntr Quadt entries = %d\n", (Int_t)qCenter_entries);
	
	printf("\nQuadrant A mean = %f +/- %f\n", qA_mean, qA_sigma);
	printf("Quadrant B mean = %f +/- %f\n", qB_mean, qB_sigma);
	printf("Quadrant C mean = %f +/- %f\n", qC_mean, qC_sigma);
	printf("Quadrant D mean = %f +/- %f\n", qD_mean, qD_sigma);
	printf("Cntr Quadt mean = %f +/- %f\n\n", qCenter_mean, qCenter_sigma);
/*	
	TCanvas *c_qA_phds = new TCanvas("c_qA_phds","PHD's for Quadrant A",800,800);
	c_qA_phds->Divide(2,2);
	c_qA_phds->cd(1); h_qA_mcpA->Draw();
	c_qA_phds->cd(2); h_qA_mcpD->Draw();
	c_qA_phds->cd(3); h_qA_mcpB->Draw();
	c_qA_phds->cd(4); h_qA_mcpC->Draw();
	
	TCanvas *c_qA_sum_phd = new TCanvas("c_qA_sum_phd","Sum PHD for Quadrant A",800,800);
	h_qA_mcpS->Draw();
	
//	TCanvas *c_qB_phds = new TCanvas("c_qB_phds","PHD's for Quadrant B",800,800);
//	c_qB_phds->Divide(2,2);
//	c_qB_phds->cd(1); h_qB_mcpA->Draw();
//	c_qB_phds->cd(2); h_qB_mcpD->Draw();
//	c_qB_phds->cd(3); h_qB_mcpB->Draw();
//	c_qB_phds->cd(4); h_qB_mcpC->Draw();
//	
//	TCanvas *c_qB_sum_phd = new TCanvas("c_qB_sum_phd","Sum PHD for Quadrant B",800,800);
//	h_qB_mcpS->Draw();
//	
//	TCanvas *c_qC_phds = new TCanvas("c_qC_phds","PHD's for Quadrant C",800,800);
//	c_qC_phds->Divide(2,2);
//	c_qC_phds->cd(1); h_qC_mcpA->Draw();
//	c_qC_phds->cd(2); h_qC_mcpD->Draw();
//	c_qC_phds->cd(3); h_qC_mcpB->Draw();
//	c_qC_phds->cd(4); h_qC_mcpC->Draw();
//	
//	TCanvas *c_qC_sum_phd = new TCanvas("c_qC_sum_phd","Sum PHD for Quadrant C",800,800);
//	h_qC_mcpS->Draw();
//	
//	TCanvas *c_qD_phds = new TCanvas("c_qD_phds","PHD's for Quadrant D",800,800);
//	c_qD_phds->Divide(2,2);
//	c_qD_phds->cd(1); h_qD_mcpA->Draw();
//	c_qD_phds->cd(2); h_qD_mcpD->Draw();
//	c_qD_phds->cd(3); h_qD_mcpB->Draw();
//	c_qD_phds->cd(4); h_qD_mcpC->Draw();
//	
//	TCanvas *c_qD_sum_phd = new TCanvas("c_qD_sum_phd","Sum PHD for Quadrant D",800,800);
//	h_qD_mcpS->Draw();
//	
//	TCanvas *c_qCenter_phds = new TCanvas("c_qCenter_phds","PHD's for Center Quadrant",800,800);
//	c_qCenter_phds->Divide(2,2);
//	c_qCenter_phds->cd(1); h_qCenter_mcpA->Draw();
//	c_qCenter_phds->cd(2); h_qCenter_mcpD->Draw();
//	c_qCenter_phds->cd(3); h_qCenter_mcpB->Draw();
//	c_qCenter_phds->cd(4); h_qCenter_mcpC->Draw();
//	
//	TCanvas *c_qCenter_sum_phd = new TCanvas("c_qCenter_sum_phd","Sum PHD for Center Quadrant",800,800);
//	h_qCenter_mcpS->Draw();
//	
//	TCanvas *c_q4_sum_phds = new TCanvas("c_q4_sum_phds","PHD's for Each Quadrant",900,600);
//	c_q4_sum_phds->Divide(2,2);
//	c_q4_sum_phds->cd(1); h_qA_mcpS->GetXaxis()->SetRangeUser(-80,8000); h_qA_mcpS->Draw();
//	c_q4_sum_phds->cd(2); h_qD_mcpS->GetXaxis()->SetRangeUser(-80,8000); h_qD_mcpS->Draw();
//	c_q4_sum_phds->cd(3); h_qB_mcpS->GetXaxis()->SetRangeUser(-80,8000); h_qB_mcpS->Draw();
//	c_q4_sum_phds->cd(4); h_qC_mcpS->GetXaxis()->SetRangeUser(-80,8000); h_qC_mcpS->Draw();
	

	TH1I *h_Q	= (TH1I*)gDirectory->Get("h_T_mcpD_0");
	TF1 *fn = new TF1("fn","gaus", 10.0, 20.0);
	h_Q->GetXaxis()->SetRangeUser(10.0,20.0);
	h_Q->Fit("fn");
	h_Q->Draw();
	fn->Draw("SAME");

	
}
*/


