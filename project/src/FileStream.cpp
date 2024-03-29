#include "include/FileStream.h"

bool FileExists(const string& filename) {
    ifstream file(filename);
    bool exists = file.good();
    file.close();
    return exists;
}


void WriteSTUPars(vector<pair<double,double>> &values, const string &filename) {
    // Open and verify if it was opened correctly
    cout << "Writting STU approved Parameters in file..." << endl;
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        fprintf(stderr, "**Can not open DAT file to write\n");
        exit(0);
    }
    file << "S" << "\t" << "T" << endl;

    // Write each element in a column
    for (auto &pair : values)
    {
        file << pair.first << "\t" << pair.second << endl;
    }
    file.close();
}

vector<pair<double,double>> readProfSTU() {
    cout << "Reading professor STU data...\n";
    ifstream infile("data/STU/check/profSTUdata.dat");
    vector<pair<double,double>> res;
    double s, t;
    while (infile >> s >> t) {
        res.push_back(make_pair(s,t));
    }
    return res;
}

void WriteElementToFile(string key, ofstream &file, int i, map<string, vector<double>> &ParMap) {
    // use the find function to search for the key and get the element at that key if it exists
    // map<string, vector<double>> myMap
    auto found_key = ParMap.find(key);
    if (found_key != ParMap.end())
        file << fixed << setprecision(6) << found_key->second[i] << " "; 
    // setprecision(n) to limit significant digits of number to n digits
    // file << setprecision(5) << found_key->second[i] << "\t"; 
}

void WriteSTU_ToFile(ofstream &file, int i, map<string, vector<double>> &ParMap, Parameters &Pars) {
    TheoCons tc;
    double ImVdagV[4][4];
    complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];
    double m11 = Pars.GetMh();
    double MH = ParMap["MH"][i];
    double MA = ParMap["MA"][i];
    double MC = ParMap["MC"][i];
    double S, T, U;
    // Define common variables
    double mneu[4], mch[2];
    tc.InitSTUVars(mneu, mch, m11, MH, MA, MC);
    // cout << "Depois de init " << mch[1] << " " << mneu[1] << endl;
    // Call Evaluate_Matrices and Calculate_STU functions
    tc.InitSTUMatrices(ImVdagV, UdagU, VdagV, UdagV);
    tc.CalculateSTU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);
    file << S << " " << T << " " << U;
}

void WriteMapToFile(const string &filename, map<string, vector<double>> &ParMap, Parameters &Pars) {
    cout << "Writting Parameter Map to .dat file...\n";
    bool PrintSTU = true;
    ofstream file;
    file.open(filename);

    if (!file.is_open()) {
        fprintf(stderr, "**Can not open .dat file to write\n");
        exit(0);
    }
    file << setprecision(10) << scientific;

    // Get the size of the largest vector
    int maxSize = 0;
    map<string, vector<double>>::iterator it;
    for (it = ParMap.begin(); it != ParMap.end(); ++it)
		maxSize = max(maxSize, (int)it->second.size());

    // Order of variables to be written in .dat file
	// The name must be exactly correct, or the data will not appear in the file
	// double m11Sq = Pars.Getla1()*Pars.Getv()*Pars.Getv(); // m11^2 = la1*v^2
    double mh = Pars.GetMh();
	double la1 = Pars.Getla1();
	// Write the column names
    for (auto &par : Pars.GetParNames())
		file << par << " "; // \t
    if (PrintSTU) {
        file << "S " << "T " << "U"; 
    }
    file << endl;

    // Write each element in a column
    for (int i = 0; i < maxSize; i++) {
      	// file << "1 "; // Write the value for m11squared
		for (auto &par : Pars.GetParNames())
		{
			if (par != "mh" && par != "la1") {
				WriteElementToFile(par, file, i, ParMap);
			} else if (par == "mh") {
				file << mh << " "; // \t
			} else if (par == "la1") {
				file << la1 << " "; // \t
			} else {
				fprintf(stderr, "**Acessed entry while writting that should not exist\n");
				exit(0);
			}
		}
        if (PrintSTU) {
            WriteSTU_ToFile(file, i, ParMap, Pars);
        }
		file << endl;
    }
    file.close();
    cout << "Parameter Map written to " << filename << "\n";
}

void ReadDAT(const string &filename, map<string, vector<double>> &ParMap) {
    ParMap.clear(); printf("Clearing map to read parameters...\n");
    printf("Reading %s into Parameter Map\n", filename.c_str());

    ifstream input(filename);

    if (!input.is_open()) {
        fprintf(stderr, "**Can not open DAT file to read\n");
        exit(0);
    }

	string line, col;
	vector<string> header;

    getline(input, line);
	stringstream ss(line);
	while (getline(ss, col, ' ')) {
		header.push_back(col);
	}
    
	// Read values
	while (getline(input, line)) {
		stringstream ss(line);
		int i = 0;
		while (getline(ss, col, ' ')) { // ; para prof data
			ParMap[header[i]].push_back(stod(col));
            // cout << "header " << header[i] << " Value " << ParMap[header[i]][i] << endl; 
			i++;
		}
	}
}

void WriteDat(const string &filename, map<string, vector<double>> &ParMap) {
    // Open and verify if it was opened correctly
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        fprintf(stderr, "**Can not open DAT file to write\n");
        exit(0);
    }

  // Get the size of the largest vector
    int maxSize = 0;
    map<string, vector<double>>::iterator it;
    for (it = ParMap.begin(); it != ParMap.end(); ++it)
        maxSize = max(maxSize, (int)it->second.size());

    // Write the strings
    for (it = ParMap.begin(); it != ParMap.end(); ++it)
        file << it->first << " "; // \t\t
    file << endl;
    
    // Write each element in a column
    for (int i = 0; i < maxSize; i++) {
        for (it = ParMap.begin(); it != ParMap.end(); ++it) {
        if (i < it->second.size())
            file << it->second[i] << " "; // \t\t
        else
            file << "0 ";
        }
        file << endl;
    }
    file.close();
}

void ReadCSV(const string &filename, map<string, vector<double>> &ParMap) {
    // ClearParMap();
    printf("Reading %s into Parameter Map\n", filename.c_str());

    ifstream input(filename);

    if (!input.is_open()) {
        fprintf(stderr, "**Can not open CSV file to read\n");
        exit(0);
    }

	string line, col;
	vector<string> header;

        getline(input, line);
		stringstream ss(line);
		while (getline(ss, col, ';')) {
			header.push_back(col);
		}

		// Read values
		while (getline(input, line)) {
			stringstream ss(line);
			int i = 0;
			while (getline(ss, col, ';')) {
				ParMap[header[i]].push_back(stod(col));
				i++;
			}
		}
    // Print map after reading
	/*
    for (auto &pair : ParMap) {
		cout << pair.first << ": ";
		for (auto& value : pair.second) {
			cout << value << " ";
		}
		cout << endl;
	}
    */
}

void SavePars(const string &filename, map<string, vector<double>> &ParMap) {
    //Open the output file
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        fprintf(stderr, "**Can not open file to save parameters\n");
        exit(0);
    }
    //Write column headings
	for (auto const &pair : ParMap) 
		outputFile << pair.first << ",";
	outputFile << "\n";
	// write data
	for (int i = 0; i < ParMap.begin()->second.size(); i++) {
		for (auto const &pair : ParMap) 
			outputFile << pair.second[i] << ",";
		outputFile << "\n";
	}
    // Close the file
    outputFile.close();
}

Graph* ReadGraphData(const string& filename, const string &Title, const string& X, const string& Y) {
    Graph* gr = new Graph();
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "**Error: could not open file " << filename << endl;
        exit(0); // return gr;
    }

    gr->SetTitle(Title.c_str());

    string line;
    getline(file, line);
    stringstream ss(line);
    string header;
    vector<string> headers;
    while (ss >> header) {
        headers.push_back(header);
    }

    int x_col = -1, y_col = -1;
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i] == X) {
            x_col = i;
            gr->SetXAxis(headers[i]);
        }
        if (headers[i] == Y) {
            y_col = i;
            gr->SetYAxis(headers[i]);
        }
    }
    if (x_col == -1) {
        cerr << "**Error: could not find column " << X << " in file " << filename << endl;
        exit(0); // return gr;
    }
    if (y_col == -1) {
        cerr << "**Error: could not find column " << Y << " in file " << filename << endl;
        exit(0); // return gr;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string val;
        int col = 0;
        double x, y;
        while (ss >> val) {
            if (col == x_col) {
                x = stod(val);
            }
            if (col == y_col) {
                y = stod(val);
            }
            col++;
        }
        // Struct
        // gr.x.push_back(x);
        // gr.y.push_back(y);
        gr->AddToX(x);
        gr->AddToY(y);
    }
    file.close();

    return gr;
}

void ReadWriteSTU(const string& filename, map<string, vector<double>> &ParMap) {
    ReadDAT("data/PassedTeoCons/PassedTeoCons.dat", ParMap);

    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "**Error: could not open file " << filename << endl;
        exit(0); // return gr;
    }
    outfile << endl;
}

// vector<double>
void ReadMicrOMEGAsOutput(const string &filename) {
printf("Reading %s, MicrOMEGAs output\n", filename.c_str());

    ifstream input(filename);

    if (!input.is_open()) {
        fprintf(stderr, "**Can not open DAT file to read\n");
        exit(0);
    }

	string line, col;
	vector<string> header;

    getline(input, line);
	stringstream ss(line);
	while (getline(ss, col, ' ')) {
		header.push_back(col);
	}
    
	// Read values
	while (getline(input, line)) {
		stringstream ss(line);
		int i = 0;
        string BP;
		while (getline(ss, col, ' ')) { // ; para prof data
            if (header[i] == "BP") BP = col;
			if (header[i] == "Omega") {
                cout << col;
            }
            // cout << "header " << header[i] << " Value " << ParMap[header[i]][i] << endl; 
			i++;
		}
        cout << endl;
	}
}

/*
Graph ReadGraphData(const string& filename, const string& X, const string& Y) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filename);
    }

    // Read header line and find indices of columns for X and Y
    string header;
    getline(file, header);
    istringstream iss(header);
    vector<string> headers{istream_iterator<string>(iss), istream_iterator<string>()};
    auto it1 = find(headers.begin(), headers.end(), X);
    auto it2 = find(headers.begin(), headers.end(), Y);
    if (it1 == headers.end() || it2 == headers.end()) {
        throw runtime_error("Could not find specified column labels in file " + filename);
    }
    int index1 = distance(headers.begin(), it1);
    int index2 = distance(headers.begin(), it2);

    // Read data and populate Graph vectors
    Graph g;
    double value1, value2;
    while (file >> value1) {
        for (int i = 0; i < index2; i++) {
            file.ignore(numeric_limits<streamsize>::max(), ' ');
        }
        file >> value2;
        g.x.push_back(value1);
        g.y.push_back(value2);
        for (int i = index2 + 1; i < index1; i++) {
            file.ignore(numeric_limits<streamsize>::max(), ' ');
            file.ignore(numeric_limits<streamsize>::max(), ' ');
        }
    }

    return g;
}*/