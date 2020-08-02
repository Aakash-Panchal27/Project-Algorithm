class matrix{
public:
	
	int row, col;
	std::vector<std::vector<lld>> num;
	
	matrix(int row, int col, int defaultValue = 0){
		this->num = std::vector<std::vector<lld>>(row, std::vector<lld>(col, defaultValue));
		this->row = row, this->col = col;
	}
	matrix(std::vector<std::vector<lld>> num){
		this->num = num;
		this->row = this->num.size();
		this->col = this->num[0].size();
	}
	
	matrix operator *(matrix &another){
		if(this->col != another.row){
			printf("Wrong size: %d*%d X %d*%d\n", this->row, this->col, another.row, another.col);
			throw "Wrong size";
		}
		matrix newone(this->row, another.col);
		for(int r=0; r<newone.row; r++) for(int c=0; c<newone.col; c++){
			for(int k=0; k<this->col; k++){	
				newone.num[r][c] += this->num[r][k] * another.num[k][c];
				newone.num[r][c] %= matrixRemainder;
			}
		} return newone;
	}	
	
	matrix operator ^(lld x){
		if(x==0){
			printf("Not implemented yet.\n");
			throw "Not implemented";
		}
		else if(x==1) return *this;
		else{
			matrix halfpower = (*this) ^ (x/2);
			if(x%2 == 0) return halfpower * halfpower;
			else return halfpower * halfpower * (*this);
		}
	}
};
