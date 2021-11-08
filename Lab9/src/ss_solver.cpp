/* Name:
 * Date:
 * Program:
 * Purpose:
 */

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


class Shifter{
	public:
		bool Read_Grid_And_Shapes(int argc, const char **argv);
		bool Apply_Shape(int index, int r, int c);
		bool Find_Solution(int index);
		void Print_Solution() const;

	protected:
		vector <string> Grid;				//Grid = Vector of 0's and 1's
		vector <vector <string> > Shapes;	//Shapes in the order in which they appear in standard input
		vector <int> Solution_Rows;			//Starting row of shapes when finding solution and done
		vector <int> Solution_Cols;			//Starting col of shapes when finding solution and done
		
//		vector <int> tempR;
//		vector <int> tempC;
};


/* 1. Read_Grid_And_Shapes() initializes the grid from argc/argv
 * 2. Reads from standard input to get the shapes.*/
bool Shifter::Read_Grid_And_Shapes(int argc, const char **argv){
	stringstream ss;
	int r = 0;
	string input;
	string separate;

	if(argc <= 1)
		return false;


	for(int i = 0; i < argc-1; i++){		
		Grid.push_back(argv[i+1]);
	}


	Shapes.resize(10);

	while(getline(cin, input)){
		ss.clear();
		ss << input;
		ss >> separate;

		Shapes[r].push_back(separate);	

		while(ss.peek() == ' '){
			ss.clear();
			ss >> separate;
			Shapes[r].push_back(separate);
		}
		
		r++;
	}
	Shapes.resize(r);
	Solution_Rows.resize(r);
	Solution_Cols.resize(r);

/*	for(unsigned int row = 0; row < Shapes.size(); row++){
		for(unsigned int col = 0; col < Shapes[row].size(); col++){
			cout << Shapes[row][col] << " ";
		}
		cout << endl;
	}*/
	return true;
}


/* 1. Apply_Shape() applies the shape in Shapes[index] to the grid, starting at row r and column c. 
 * 2. If you call Apply_Shape twice with the same arguments, you'll end up with same grid as before the two calls. */
bool Shifter::Apply_Shape(int index, int r, int c){
	(void) index;
	(void) r;
	(void) c;
	bool goodRow = false, goodCol = false;
	
	bool possible = false;

	//cout << "Apply Shape" << endl;
	
	if(r + Shapes[index].size() <= Grid.size())
		goodRow = true;
	if(c + Shapes[index][0].size() <= Grid[0].size())
		goodCol = true; 

	
	if(goodRow && goodCol){
		possible = true;
		
		for(unsigned int i = 0; i < Shapes[index].size(); i++){
			for(unsigned int j = 0; j < Shapes[index][i].size(); j++){
				
				
				if(Shapes[index][i][j] == '1' && Grid[r+i][c+j] == '1')
					Grid[r+i][c+j] = '0';

				else if(Shapes[index][i][j] == '1' && Grid[r+i][c+j] == '0')
					Grid[r+i][c+j] = '1';
//IMPORTANT
//				cout << "Grid (" << r+i << ", " << c+j << ") = " << Grid[r+i][c+j] << endl;
			}
		}
	}

//IMPORTANT	
/*	 for(unsigned int i = 0; i < Grid.size(); i++){
		 for(unsigned int j = 0; j < Grid[0].size(); j++){
			 cout << Grid[i][j] << " ";
		 }
		cout << endl;
	 }
*/
	return possible;
}


/* 1. Find_Solution() is the recursive procedure.  
 * 2. It tries all possible starting positions for Shape[index], 
 *	  and calls Find_Solution() recursively to see if that's a correct way to use Shape[index]. 
 * 3. If a recursive call returns false, then it "undoes" the shape by calling Apply_Shape() again.*/
bool Shifter::Find_Solution(int index){
	(void) index;
	unsigned int num_ones = 0;
	
	for(unsigned int row = 0; row < Grid.size(); row++){
		for(unsigned int col = 0; col < Grid[0].size(); col++){
			
			if(index != (int)Shapes.size())
//IMPORTNAT				
//				cout << "SHAPE = " << index << endl;
			
			if(index < (int)Shapes.size()){	
//				cout << "row: " << row << ", col:" << col << endl;
				if(Apply_Shape(index, row, col) == true){
					//cout << "APPLY_SHAPE IF = " << row << ", " << col << endl;
					Solution_Rows[index] = row;
					Solution_Cols[index] = col;
					
//					cout << "Solution = " << Solution_Rows[index] << " + " << Solution_Cols[index] << endl;
//					cout << "the index is " << index << endl;
					//Solution_Rows.push_back(row);
					//Solution_Cols.push_back(col);
			
					
					index++;
									
					if(!Find_Solution(index)){
//						cout << "\n!Find\n" << endl;
						//tempR.erase(tempR.end()-1);
						//tempC.erase(tempC.end()-1);
						index--;
					}
					else{
//						cout << "ELSE !FIND" << endl;
						
						//cout << Solution_Rows[index] << " - " << Solution_Cols[index] << endl;
						/*
						for(unsigned int a = 0; a < tempR.size(); a++){
							for(unsigned int b = 0; b < tempC.size(); b++){
								cout << tempR[a] << " " << tempC[b] << endl;
							}
						}
						
						Solution_Rows[2] = tempR[0];
						Solution_Cols[2] = tempC[0];
						

						cout << Solution_Rows[2] << " - " << Solution_Cols[2] << endl;

						//Solution_Rows[index] = tempR[index];
						//Solution_Cols[index] = tempC[index];
						*/
						
						num_ones = 0;
						for(unsigned int y = 0; y < Grid.size(); y++){
							for(unsigned int z = 0; z < Grid[0].size(); z++){
								num_ones++;
							}
						}
						
						if(num_ones == (Grid.size() * Grid[0].size())){
							return true;

						}

						//Solution_Rows.push_back(row);
						//Solution_Cols.push_back(col);

						//Solution_Rows[index] = row;
						//Solution_Cols[index] = col;
						
						//return true;
					}
				}		
			}
		}
	}

//	cout << "outside for loop" << endl;
	
	for(unsigned int i = 0; i < Grid.size(); i++){
		for(unsigned int j = 0; j < Grid[0].size(); j++){
			//cout << Grid[i][j] << " ";
			if(Grid[i][j] == '1'){
				num_ones++;
			}
		}
		//cout << endl;
	}

	if(num_ones != (Grid.size() * Grid[0].size())){
//		cout << "NOT ALL 1s" << endl << endl;
		index--;
		Apply_Shape(index, Solution_Rows[index], Solution_Cols[index]);
		return false;
	}
	else{
	
//	cout << "\nbottom true" << endl;
//	cout << "Solution = " << Solution_Rows[index-1] << " * " << Solution_Cols[index-1] << endl;
//	cout << "now the index is " << index-1 << endl;
	//Solution_Rows[index-1] = Solution_Rows[index-1];
	//Solution_Cols[index-1] = Solution_Cols[index-1]+1;
	
	//tempR.push_back(Solution_Rows[index-1]);
	//tempC.push_back(Solution_Cols[index-1]);

	return true;
	}
}


/* 1. This prints the solution on standard output.*/
void Shifter::Print_Solution() const{
//	int correctCol;
//	cout << "I should be printing the solution now" << endl;
	
//	cout << Solution_Rows[2] << " % " << Solution_Cols[2] << endl;

	for(unsigned int row = 0; row < Shapes.size(); row++){
		for(unsigned int col = 0; col < Shapes[row].size(); col++){
			cout << Shapes[row][col] << " ";
		}
		cout << Solution_Rows[row] << " " << Solution_Cols[row] << endl;
	}
}



int main(int argc, const char **argv){
	Shifter shwifty;
	shwifty.Read_Grid_And_Shapes(argc, argv);
	
	//cout << "Time to find some solutions!" << endl;
	
	shwifty.Find_Solution(0);
	shwifty.Print_Solution();
	
	return 0;
}


