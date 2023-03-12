void multigraph() {

    /*
     * HOW TO USE
     *  
     * To get graph output run $root scripts/graph.cpp
     * To print data, print = 1;
     * To save graph, save = 1;
     * To fit to data, fit = 1;
    */

    string path = "data/MOOC/isocronocidade.csv";  // input file path
    string name = "Planck's Constant";       // Graph title
    string titleX = "#nu [Hz]";          // X axis title
    string titleY = "V_{s} [V]";        // Y axis title
    string dir = "bin/";            // output file folder
    string fitfunction = "[0]*x+[1]";      // Fit function
    int print = 0;
    int save = 1;
    int fit = 0;
    int fit_bit = 0; // Chooses which graoh to fit, fit_bit < N ALWAYS

    // Vector to store the CSV data
    vector<vector<double>> data; 

    // Open file
    ifstream file(path);
    if (!file.is_open()) {
        fprintf(stderr, "**Failed to open file %s", path.c_str());
        exit(0);
    }

    // Discard and/or write title
    string s;
    int N = 0;
    for (int i=0; i<1; i++) {
        getline(file,s);
        stringstream titles(s);
        string title;
        while (getline(titles, title, ';')) {
            cout << title << '\t';
            N++; // N columns
        }
        cout << endl;
    }

    if (N%2 != 0) {
        fprintf(stderr, "**Odd number of columns, exit\n");
        exit(0);
    }

    // Initializes the data storage
    vector<vector<double>> vec;
    for(int i = 0; i < N; i++){
        vector<double> vec;
        data.push_back(vec);
    }

    // Reads csv data
    while (getline(file,s)) { // true is returned if values are read
        int jj = 0;
        stringstream line(s); // turns string into sstream
        string word;
        while (getline(line, word, ';')) {
            data[jj].push_back(stod(word));
            jj++;
        }
    }
    file.close();

    // Print out data if print flag = 1
    if (print) {
        for (auto row : data)
        {
            for (auto cell : row)
                cout << cell << "\t";
            cout << endl;
        }
    }

    // Make graph
    TCanvas *c = new TCanvas();
    vector<TGraph *> grvec;
    TMultiGraph *mg = new TMultigraph();
    N *= 0.5; // Create a graoh for each pair of columns
    for (int i = 0; i < N; i+=2) {
        TGraph *gr = new TGraph(data[i+1].size(), &(data[i][0]), &(data[i+1][0]));
        grvec[i].push_back(gr);
        grvec[i]->SetMarkerColor(i+1);
        grvec[i]->SetMarkerStyle(20); // 20
        // grvec[i]->SetLineColor(kBlue);
        mg->Add(grvec[i]);
    }
    
    if (fit && fit_bit < N) {
        TF1* func = new TF1("func", fitfunction.c_str());
        cout << "Making fit...\n";
        func->SetLineColor(kRed);
        func->SetLineWidth(2);
        grvec[fit_bit]->Fit("func");
        // gr->SetMarkerColor(0);
        // gr->SetMarkerStyle(9);
        // gr->SetMarkerSize(0.1);
        func->Draw("SAME");
    }

    mg->GetXaxis()->CenterTitle();
    mg->SetTitle(name.c_str());
    mg->GetXaxis()->SetTitle(titleX.c_str());
    mg->GetYaxis()->SetTitle(titleY.c_str());

    // gr->SetLineWidth(2);
    mg->Draw("AP");

    // Save graph in bin dir
    if (save) {
        dir.append(name);
        dir.append("2.png");
        c->Update();
        c->SaveAs(dir.c_str());
    }
}