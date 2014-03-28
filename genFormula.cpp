#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
using namespace std;

vector<vector<int> > selection;
int comb[9];
void combination(int m, int n, int total) {
    int i, j;
    for (i = m; i >= n; i--) {
    	comb[n] = i;        /* select first number */
    	if (n > 1) {
    	/* recursive */
    		combination(i - 1, n - 1, total);
    	}
    	else {
    	/* reach target count */
    		vector<int> tmp(total);
    		for (j = comb[0]; j > 0; j--){
    			//printf("%c", comb[j] + 64);
    			//cout<<comb[j];
    			tmp[comb[j] - 1] = 1;
    		}
    		selection.push_back(tmp);
    		//printf(" ");
    	}
    }
    return;
}

vector<vector<int> > input;

bool readInput(string fileName) {
	FILE *in_file = fopen(fileName.c_str(),"r");
	if (in_file == NULL) {
		cerr<<"open failed!"<<endl;
		return false;
	}
	vector<int> line;
	int size;
	char tmpc;
	fscanf(in_file,"%d",&size);
	tmpc = fgetc(in_file);
	for (int i = 0; i < size; i++) {
		line.clear();
		for (int j = 0; j < size; j++) {
			tmpc = fgetc(in_file);
			if (tmpc == '*')
				line.push_back(-1);
			else
				line.push_back(tmpc - '0');
		}
		tmpc = fgetc(in_file);
		input.push_back(line);
	}
	fclose(in_file);
	return true;
}

int main(void) {
	string fileName = "in.txt";
	string outFileName = "formula.txt";
	ofstream out_file;
	out_file.open(outFileName);
	readInput(fileName);
	int size = input.size();
	int variable;
	int totalGridNum;
	int count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j  < size; j++) {
			if (input[i][j] >= 0) {
				count ++;
				variable = i * size + j;
				if (count > 1)
					out_file<<"\t| ~(";
				else
					out_file<<"\t~(";
				
				if (i == 0 && j == 0) {//up-left corner
					totalGridNum = 4;
					int move[] = {0, 1, size, size + 1};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				else if (i == 0 && j == size - 1) {//up-right corner
					totalGridNum = 4;
					int move[] = {-1, 0, size - 1, size};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<") |";
					}
				}
				else if (i == size - 1 && j == 0) {//down-left corner
					totalGridNum = 4;
					int move[] = {-size, -size + 1, 0, 1};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				else if (i == size - 1 && j == size - 1) {//down-right corner
					totalGridNum = 4;
					int move[] = {-size - 1, -size, -1, 0};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				else if (i == 0) {//up edge
					totalGridNum = 6;
					int move[] = {-1, 0, 1, size - 1, size, size + 1};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				else if (j == size - 1) {//right edge
					totalGridNum = 6;
					int move[] = {-size - 1, -size, -1, 0, size - 1, size};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				else if (i == size - 1) {//down edge
					totalGridNum = 6;
					int move[] = {-size - 1, -size, -size + 1, -1, 0, 1};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				else if (j == 0) {//left edge
					totalGridNum = 6;
					int move[] = {-size, -size + 1, 0, 1, size, size + 1};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				else {//inner grid
					totalGridNum = 9;
					int move[] = {-size - 1, -size, -size + 1, -1, 0, 1, size - 1, size, size + 1};
					if (input[i][j] == 0) {
						for (int n = 0; n < totalGridNum; n++) {
							if (n > 0)
								out_file<<"&";
							out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")"<<endl;
						continue;
					}
					selection.clear();
					comb[0] = input[i][j];
					combination(totalGridNum, comb[0], totalGridNum);
					for (int m = 0; m < selection.size(); m++) {
						if (m > 0)
							out_file<<" |";
						out_file<<" (";
						for (int n = 0; n < selection[m].size(); n++) {
							if (n > 0)
								out_file<<"&";
							if (selection[m][n] > 0)
								out_file<<(variable + move[n]);
							else
								out_file<<"~"<<(variable + move[n]);
						}
						out_file<<")";
					}
				}
				out_file<<" )"<<endl;
			}
		}
	}
	out_file.close();

	return 0;
}
