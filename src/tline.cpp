#include "TCanvas.h" // include class TCanvas from RootClass library
#include "TGraph.h" // graf
#include "TMultiGraph.h"
#include "TH1D.h"
#include "TH2F.h"           // histogram 2D
#include "TF1.h"
#include "TF2.h"

#include "TFitResultPtr.h"
#include "TFitResult.h"

#include "TMath.h"
#include "TRandom3.h"
#include "TAxis.h"
#include "THStack.h"
#include "TLine.h"

#include "TRootCanvas.h"
#include "TApplication.h"

#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

int main(){

	TApplication app("app", NULL, NULL);

	TCanvas *c = new TCanvas("c", "canvas", 1200, 600);

    TLine *line = new TLine(0.2,0.2,0.8,0.3); // (min x, min y value, max x, max y);
    line->SetLineWidth(5);
    line->SetLineColor(kRed);
    line->Draw();
    
	TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
	
	return 0;
}