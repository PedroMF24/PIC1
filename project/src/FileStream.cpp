#include "FileStream.h"

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
        file << found_key->second[i] << "\t"; 
    // setprecision(n) to limit significant digits of number to n digits
    // file << setprecision(5) << found_key->second[i] << "\t"; 
}

void WriteMapToFile(const string &filename, map<string, vector<double>> &ParMap, Parameters &Pars) {
    cout << "Writting Parameter Map to .dat file...\n";

    ofstream file;
    file.open(filename);

    if (!file.is_open()) {
        fprintf(stderr, "**Can not open .dat file to write\n");
        exit(0);
    }

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
		file << endl;
    }
    file.close();
    cout << "Parameter Map written to " << filename << "\n";
}

void ReadDAT(const string &filename, map<string, vector<double>> &ParMap) {
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
	while (getline(ss, col, '\t')) {
		header.push_back(col);
	}
    
	// Read values
	while (getline(input, line)) {
		stringstream ss(line);
		int i = 0;
		while (getline(ss, col, '\t')) {
			ParMap[header[i]].push_back(stod(col));
            cout << "header " << header[i] << " Value " << ParMap[header[i]][i] << endl; 
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
        file << it->first << "\t\t";
    file << endl;
    
    // Write each element in a column
    for (int i = 0; i < maxSize; i++) {
        for (it = ParMap.begin(); it != ParMap.end(); ++it) {
        if (i < it->second.size())
            file << it->second[i] << "\t\t";
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
		while (getline(ss, col, ',')) {
			header.push_back(col);
		}

		// Read values
		while (getline(input, line)) {
			stringstream ss(line);
			int i = 0;
			while (getline(ss, col, ',')) {
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