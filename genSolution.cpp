#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <stdio.h>
using namespace std;

bool visualization(vector<vector<int> > sol_mat) {
	int i,j;
	int size = sol_mat.size();
	FILE *svgfp = fopen("solution.svg","w");
	if (svgfp == NULL) {
		printf("Error when opening svgfile\n");
		return 0;
	}
	// draw the svg
	fprintf(svgfp,"<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fprintf(svgfp,"<svg width=\"10000\" height=\"10000\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");

	//parameters for visualization
	int len = 25;	//length for the square
	int bias = 50;	//bias for the graph
	int sobias = 2 * bias + len * size;
	//Visualization
	int gridx,gridy,textx,texty;
	for (i = 0;i < size;i++) {
		for (j = 0;j < size;j++) {
			gridx = j * len + bias;
			gridy = i * len + bias;
			fprintf(svgfp,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:white;stroke:black;stroke-width:3;\"/>\n",gridx,gridy,len,len);
			if (sol_mat[i][j] != 0)
				fprintf(svgfp,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:black;stroke:grey;stroke-width:3;\"/>\n",gridx + sobias,gridy,len,len);
			else
				fprintf(svgfp,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:white;stroke:grey;stroke-width:3;\"/>\n",gridx + sobias,gridy,len,len);
			
			if (sol_mat[i][j] != 0)
				fprintf(svgfp,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:black;stroke:grey;stroke-width:3;\"/>\n",gridx + 2 * sobias,gridy,len,len);
			else
				fprintf(svgfp,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:white;stroke:grey;stroke-width:3;\"/>\n",gridx + 2 * sobias,gridy,len,len);

			if (input[i][j] != -1) {
				textx = (int)(gridx + len / 2);
				texty = (int)(gridy + len * 0.85);
				fprintf(svgfp,"<text x=\"%d\" y=\"%d\" font-size=\"%d\" fill=\"black\" text-anchor=\"middle\">\n",textx,texty,(int)(len));
				fprintf(svgfp,"%d\n",input[i][j]);
				fprintf(svgfp,"</text>\n");
				fprintf(svgfp,"<text x=\"%d\" y=\"%d\" font-size=\"%d\" fill=\"grey\" text-anchor=\"middle\">\n",textx + sobias,texty,(int)(len));
				fprintf(svgfp,"%d\n",input[i][j]);
				fprintf(svgfp,"</text>\n");
			}
		}
	}
	fprintf(svgfp,"</svg>\n");
	fclose(svgfp);
	return true;
}

int main(void) {
	string fileName = "cnf.txt";
	string solutionName = "solution.txt";
	ifstream cnf_file;
	ifstream solution_file;
	string tmp;
	cnf_file.open(fileName);
	unordered_map<int, int> map;
	int count = 0;
	int size = 0;
	int variable, grid;
	int i,j;
	int space[] = {0,0};
	string subTmp;
	while (getline(cnf_file, tmp)) {
		if (tmp[0] == 'p') {
			//cout<<tmp<<endl;
			break;
		}
		j = 0;
		for (i = 0; i < tmp.length(); i++) {
			if (tmp[i] == ' ') {
				space[j++] = i;
			}
		}
		for (j = space[0] + 1; j < space[1]; j++)
			subTmp.push_back(tmp[j]);
		variable = atoi(subTmp.c_str());
		subTmp.clear();
		for (j = space[1] + 1; j < tmp.length(); j++)
			subTmp.push_back(tmp[j]);
		grid = atoi(subTmp.c_str());
		subTmp.clear();
		//cout<<variable<<" "<<grid<<endl;
		map.insert(make_pair(variable, grid));
		size++;
		//cout<<size<<endl;
	}
	size = sqrt(size);
	//cout<<size<<endl;
	cnf_file.close();

	int value;
	int index_i, index_j;
	int solution[size][size];
	memset(solution, 0, sizeof(solution));
	solution_file.open(solutionName);
	while (getline(solution_file, tmp)) {
		if (tmp[0] != 'v')
			continue;
		tmp = tmp.substr(2);
		subTmp.clear();
		for (i = 0; i < tmp.length(); i++) {
			if (tmp[i] == ' ') {
				variable = atoi(subTmp.c_str());
				value = (variable > 0)? 1 : 0;
				variable = (variable > 0)? variable : (-variable);
				subTmp.clear();
				unordered_map<int, int>::const_iterator got = map.find(variable);
				if (got != map.end()) {
					grid = got->second;
					index_i = grid / size;
					index_j = grid % size;
					solution[index_i][index_j] = value;
				}
			}
			else
				subTmp.push_back(tmp[i]);
		}
		variable = atoi(subTmp.c_str());
		if (variable == 0) {
			break;
		}
		value = (variable > 0)? 1 : 0;
		variable = (variable > 0)? variable : (-variable);
		subTmp.clear();
		unordered_map<int, int>::const_iterator got = map.find(variable);
		if (got != map.end()) {
			grid = got->second;
			index_i = grid / size;
			index_j = grid % size;
			solution[index_i][index_j] = value;
		}

	}
	vector<vector<int> > sol_mat;
	vector<int> sol_line;
	ofstream out_visual;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			cout<<solution[i][j]<<"";

			sol_line.push_back(solution[i][j]);
		}
		sol_mat.push_back(sol_line);
		sol_line.clear();
		cout<<endl;
	}
	visualization(sol_mat);
	return 0;
}
