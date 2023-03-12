void graph() {

    /*
     * HOW TO USE
     *  
     * To get graph output run $root scripts/graph.cpp
     * To print data, print = 1;
     * To save graph, save = 1;
     * To fit to data, fit = 1;
    */

    string path = "data/Espectroscopia/h_planck.csv";  // input file path
    // string path = "data/MOOC/TL_linear.csv";  // input file path

    string name = "MOOC";       // Graph title
    string titleX = "#nu [Hz]";          // X axis title
    string titleY = "V_{s} [V]";        // Y axis title
    string dir = "bin/";            // output file folder
    string fitfunction = "[0]*x+[1]";      // Fit function
    // string name = "MOOC";       // Graph title
    // string titleX = "#\\sqrt{\\frac{L}{g}}  [s]"; // "L [m]"; //  //"#\\sqrt{L/g} [s]";       // X axis title
    // string titleY = "T [s]";        // Y axis title
    // string dir = "bin/";            // output file folder
    // string fitfunction = "[0]*x+[1]";      // Fit function
    // "[0]*x*x + [1]*x + [2]"
    int print = 0;
    int save = 1;
    int fit = 1;

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
    for (int i=0; i<1; i++) {
        getline(file,s);
        stringstream titles(s);
        string title;
        while (getline(titles, title, ';'))
            cout << title << '\t';
        cout << endl;
    }

    // Initializes the data storage
    vector<vector<double>> vec;
    for(int i = 0; i < 4; i++){
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
    TGraphErrors *gr = new TGraphErrors(data[1].size(), &(data[0][0]), &(data[1][0]), &(data[2][0]), &(data[3][0])); // Time vs Channel

    if (fit) {
        TF1* func = new TF1("func", fitfunction.c_str());
        cout << "Making fit...\n";
        func->SetLineColor(kRed);
        func->SetLineWidth(2);
        gr->Fit("func");
        // gr->SetMarkerColor(0);
        // gr->SetMarkerStyle(9);
        // gr->SetMarkerSize(0.1);
        func->Draw("SAME");
    }

    gr->GetXaxis()->CenterTitle();
    gr->SetTitle(name.c_str());
    gr->GetXaxis()->SetTitle(titleX.c_str());
    gr->GetYaxis()->SetTitle(titleY.c_str());
    gr->SetMarkerColor(kBlue);
    gr->SetMarkerStyle(20); // 20
    gr->SetLineColor(kBlue);
    // gr->SetLineWidth(2);
    gr->Draw("AP");

    // Save graph in bin dir
    if (save) {
        dir.append(name);
        dir.append(".png");
        c->Update();
        c->SaveAs(dir.c_str());
    }
}