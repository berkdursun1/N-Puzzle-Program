// Factoriel hesabı //
#include<iostream>
#include<cstdlib>
#include<ctime>
#define empty 0 
using namespace std;
//ptr is board
int move_left(int ptr[][9],int size);
int move_right(int ptr[][9],int size);
int move_up(int ptr[][9],int size);
int move_down(int ptr[][9],int size);
int move_intelligent(int ptr[][9],int size,int goal_ptr[][9],int last_move);
int copy_ptr(int ptr[9][9],int copy[9][9]);
int find_the_same_line(int ptr[9][9],int ptr_2[9][9],int goal_ptr[9][9],int size);
int find_blank_coordinat_x(int ptr[][9]);
int find_blank_coordinat_y(int ptr[][9]);
int find_the_y(int ptr[][9],int y,int size);
int find_the_x(int ptr[][9],int x,int size);
int find_the_difference_between_two_coordinates(int x_1,int x_2,int y_1,int y_2);
int find_the_difference_between_two_ptr(int ptr[][9],int goal_ptr[][9],int size);
void shuffle(int ptr[][9],int size);
void initializion(int ptr[][9],int size);
void display(int ptr[][9],int size);
int main(){
	char selection;
	int size; 
	int goal_ptr[9][9];
	int last_move=4;
	int ptr[9][9];
	int check;
	int count=0 ; 
	// initializions the charts
	cout << "please enter size : " ;
	cin >> size ;
	
	initializion(ptr,size);
	initializion(goal_ptr,size); 
	srand(time(NULL));
	do{
	//	cout<<"output\n";
		display(ptr,size);
		cout <<"\n";
		cout << "Your move : " ;
		// select the selection
		cin >> selection ;
		
		if(selection=='u' || selection=='U'){
			move_up(ptr,size);
		}
		else if(selection=='r' || selection=='R'){
			move_right(ptr,size);
		} 
		else if(selection=='d' || selection=='D'){
			move_down(ptr,size);
		}
		else if(selection=='l' || selection=='L' ){
			move_left(ptr,size);
		}
		else if(selection=='i' || selection=='I'){
		//	cout << "Last move " << last_move ; 
		//	cout << "\n" ; 
			last_move=move_intelligent(ptr,size,goal_ptr,last_move); 
		}
		else if(selection=='s' || selection=='S'){
			shuffle(ptr,size);
		}
		count ++;
	}while(selection!='q' && selection!='Q' && last_move!=-1 && find_the_difference_between_two_ptr(ptr,goal_ptr,size)!=0);
	display(ptr,size);
	cout << "\n";
	cout << "Problem solved !! \n";
	cout << "Total number of moves " << count ; 
	


}
void shuffle(int ptr[][9],int size){
	int blank_coordinat_x;
	int blank_coordinat_y;
	int random;
	int selection;
	int number_of_move;
	int i;
	int last_move=-1;
	number_of_move=size*size;
	for(i=0;i<number_of_move;i++){
	//	display(ptr,size);
	//	cout << "\n" ;
		blank_coordinat_x=find_blank_coordinat_x(ptr);
		blank_coordinat_y=find_blank_coordinat_y(ptr);
		random=rand()%4; // 0=up , 1=left , 2=down , size=right		
		while((random==0 && (blank_coordinat_y==0 || last_move==2)) 
			|| (random==1 && (blank_coordinat_x==0|| last_move==3)) 
			|| (random==2 && (blank_coordinat_y==size-1 || last_move==0)) 
			|| (random==3 && (blank_coordinat_x==size-1 || last_move==1))){
			random=rand()%4;
		}
		// moving the blank tile !
		if(random==0 && last_move!=2){
			move_up(ptr,size);
			last_move=0;
		}
		else if(random==1 && last_move!=3){
			move_left(ptr,size);
			last_move=1;
		}
		else if(random==2 && last_move!=0){
			move_down(ptr,size);
			last_move=2;
		}
		else if(random==size && last_move!=1){
			move_right(ptr,size);
			last_move=3;
		}
		
		
	} 
	 

}
// copy ptr from another ptr
int copy_ptr(int ptr[9][9],int copy[9][9]){
	int i=0;
	int k=0;
	for(i=0;i<9;i++){
		for(k=0;k<9;k++){
			copy[i][k]=ptr[i][k];
		}
	}
}
int find_the_difference_between_two_coordinates(int x_1,int x_2,int y_1,int y_2){
	int result=0;
	if(x_2>x_1){
		result=x_2-x_1;
	}
	else{
		result=x_1-x_2;
	}
	if(y_2>y_1){
		result=result+y_2-y_1;
	}
	else{
		result=result+y_1-y_2;
	}
	return result;
}
int find_the_x(int ptr[][9],int x,int size){
	int final=0;
	int i;
	int k;
	for(i=0;i<size;i++){
		for(k=0;k<size;k++){
			if(ptr[i][k]==x){
				final=i;
			}
		}
	}
	return final;

}
int find_the_y(int ptr[][9],int y,int size){
	int final=0;
	int i;
	int k;
	for(i=0;i<size;i++){
		for(k=0;k<size;k++){
			if(ptr[i][k]==y){
				final=k;
			}
		}
	}
	return final;

}
int find_the_difference_between_two_ptr(int ptr[][9],int goal_ptr[][9],int size){
	int result=0;
	int x_1;
	int y_1;
	int x_2;//goal
	int y_2;//goal
	int i=0;
	int k=0;
	for(i=0;i<size;i++){
		for(k=0;k<size;k++){
			if(ptr[i][k]!=goal_ptr[i][k] && ptr[i][k]!=0){
				x_1=find_the_x(ptr,ptr[i][k],size);
				y_1=find_the_y(ptr,ptr[i][k],size);
				x_2=find_the_x(goal_ptr,ptr[i][k],size);
				y_2=find_the_y(goal_ptr,ptr[i][k],size);
				result= result+find_the_difference_between_two_coordinates(x_1,x_2,y_1,y_2);
			}
		}
	}
	
	return result;
}
int find_the_smallest(int x_1,int x_2,int x_size,int x_4){ // find the smallest number 
	if(x_1<=x_2 && x_1<=x_size && x_1 <= x_4){
		return x_1 ;
	}
	else if(x_2<=x_size && x_2<=x_4 && x_2 <= x_1){
		return x_2 ;
	}
	else if(x_size<=x_4 && x_size<=x_2 && x_size <= x_1){
		return x_size ;
	}
	else if(x_4<=x_2 && x_4<=x_size && x_4<=x_1){
		return x_4 ;
	}
	}
int move_intelligent(int ptr[][9],int size,int goal_ptr[][9],int last_move){
	int blank_coordinat_x;
	int blank_coordinat_y;
	// Beginning those are 99
	int check_up=99;
	int check_left=99;
	int check_down=99;
	int check_right=99;
	int ptr_up[9][9];
	int ptr_left[9][9];
	int ptr_down[9][9];
	int ptr_right[9][9];
	int smallest_one;
	int select=-1;
	// find the blank coordinates
	blank_coordinat_x=find_blank_coordinat_x(ptr);
	blank_coordinat_y=find_blank_coordinat_y(ptr);
	copy_ptr(ptr,ptr_up);
	copy_ptr(ptr,ptr_left);
	copy_ptr(ptr,ptr_down);
	copy_ptr(ptr,ptr_right);
	// check if its over
	if(find_the_difference_between_two_ptr(ptr,goal_ptr,size)==0){
		return -1;
	}
	// find the best possibility 
	else{
		if(blank_coordinat_y>0 && last_move!=2){
		move_up(ptr_up,9);	
		check_up=find_the_difference_between_two_ptr(ptr_up,goal_ptr,size);
	
		}
		if(blank_coordinat_x>0 && last_move!=size){
			move_left(ptr_left,9);	
			check_left=find_the_difference_between_two_ptr(ptr_left,goal_ptr,size);
	
		}
		if(blank_coordinat_y<size-1 && last_move!=0){
			move_down(ptr_down,9);	
			check_down=find_the_difference_between_two_ptr(ptr_down,goal_ptr,size);
	
		}
		if(blank_coordinat_x<size-1 && last_move!=1){
			move_right(ptr_right,9);
			check_right=find_the_difference_between_two_ptr(ptr_right,goal_ptr,size);
		}
		smallest_one=find_the_smallest(check_up,check_left,check_down,check_right);
		if(smallest_one==check_up){
			if(smallest_one == check_left){
				select=find_the_same_line(ptr_up,ptr_left,goal_ptr,size);
				if(select==1){
					copy_ptr(ptr_up,ptr);
					last_move=0;
					cout << "Intelligent choose move U\n";
				}
				else{
					copy_ptr(ptr_left,ptr);
					last_move=1;
					cout << "Intelligent choose move L\n";
				}
			}
			else if(smallest_one == check_down){
				select=find_the_same_line(ptr_up,ptr_down,goal_ptr,size);
				if(select==1){
					copy_ptr(ptr_up,ptr);
					last_move=0;
					cout << "Intelligent choose move U\n";
				}
				else{
					copy_ptr(ptr_down,ptr);
					last_move=2;
					cout << "Intelligent choose move D\n";
				}
			}
			else if(smallest_one == check_right){
				select=find_the_same_line(ptr_up,ptr_right,goal_ptr,size);
				if(select==1){
					copy_ptr(ptr_up,ptr);
					last_move=0;
					cout << "Intelligent choose move U\n";
				}
				else{
					copy_ptr(ptr_right,ptr);
					last_move=3;
					cout << "Intelligent choose move R\n";
				}
			}
			else{
				copy_ptr(ptr_up,ptr);
				last_move=0;
				cout << "Intelligent choose move U\n";	
			}
			
		}
		else if(smallest_one==check_left){
			if(smallest_one == check_down){
				select=find_the_same_line(ptr_left,ptr_down,goal_ptr,size);
				if(select==1){
					copy_ptr(ptr_left,ptr);
					last_move=1;
					cout << "Intelligent choose move L\n";
				}
				else{
					copy_ptr(ptr_down,ptr);
					last_move=2;
					cout << "Intelligent choose move D\n";
				}
			}
			if(smallest_one == check_right){
				select=find_the_same_line(ptr_left,ptr_right,goal_ptr,size);
				if(select==1){
					copy_ptr(ptr_left,ptr);
					last_move=1;
					cout << "Intelligent choose move L\n";
				}
				else{
					copy_ptr(ptr_right,ptr);
					last_move=3;
					cout << "Intelligent choose move R\n";
				}
			}
			else{
				copy_ptr(ptr_left,ptr);
				last_move=1;
				cout << "Intelligent choose move L\n";	
			}
			
		}
		else if(smallest_one==check_down){
			if(smallest_one==check_right){
				select=find_the_same_line(ptr_down,ptr_right,goal_ptr,size);
				if(select==1){
					copy_ptr(ptr_down,ptr);
					last_move=2;
					cout << "Intelligent choose move D\n";			
				}
				else{
					copy_ptr(ptr_right,ptr);
					last_move=3;
					cout << "Intelligent choose move R\n";
				}
			}
			else{
				copy_ptr(ptr_down,ptr);
				last_move=2;
				cout << "Intelligent choose move D\n";	
			}
		}
		else if(smallest_one==check_right){
			copy_ptr(ptr_right,ptr);
			last_move=size;
			cout << "Intelligent choose move R\n";
		}	
	}
	return last_move;
}
int find_blank_coordinat_x(int ptr[][9]){
	int i=0;
	int k=0;
	for(i=0;i<9;i++){
		for(k=0;k<9;k++){
			if(ptr[i][k]==0){
				return k ;
			}
		}
	}
}
int find_blank_coordinat_y(int ptr[][9]){
	int i=0;
	int k=0;
	for(i=0;i<9;i++){
		for(k=0;k<9;k++){
			if(ptr[i][k]==0){
				return i ;
			}
		}
	}
}
void display(int ptr[][9],int size){
	int i; 
	int k;
	for(i=0;i<9;i++){
		for(k=0;k<9;k++){
			if(ptr[i][k]!=99){
				if(ptr[i][k]==0)
					cout << "\t" ;
				else 
					cout << "" << ptr[i][k] << "\t";
			}
			
		}
		if(i<size)
		cout << "\n" ; 
	}
}
int move_left(int ptr[][9],int size){
	int blank_coordinat_x=find_blank_coordinat_x(ptr);
	int blank_coordinat_y=find_blank_coordinat_y(ptr);
	if(blank_coordinat_x==0){
		cout << "Something wrong !! left" ; 
		return 99 ; 
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y][blank_coordinat_x-1];
		ptr[blank_coordinat_y][blank_coordinat_x-1]=0;
	}

}
int move_right(int ptr[][9],int size){
	int blank_coordinat_x=find_blank_coordinat_x(ptr);
	int blank_coordinat_y=find_blank_coordinat_y(ptr);
	if(blank_coordinat_x==size-1){
		cout << "Something wrong !! right" ; 
		return 99 ; 
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y][blank_coordinat_x+1];
		ptr[blank_coordinat_y][blank_coordinat_x+1]=0;
	}	
}
int move_up(int ptr[][9],int size){
	int blank_coordinat_x=find_blank_coordinat_x(ptr);
	int blank_coordinat_y=find_blank_coordinat_y(ptr);
	if(blank_coordinat_y==0){
		cout << "Something Wrong !! up " ;
		return 99 ; 
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y-1][blank_coordinat_x];
		ptr[blank_coordinat_y-1][blank_coordinat_x]=0;
	}
}
int move_down(int ptr[][9],int size){
	int blank_coordinat_x=find_blank_coordinat_x(ptr);
	int blank_coordinat_y=find_blank_coordinat_y(ptr);
	if(blank_coordinat_y==size-1){
		cout << "Something wrong !!down ";
		return 99;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y+1][blank_coordinat_x];
		ptr[blank_coordinat_y+1][blank_coordinat_x]=0;
	}
}
void initializion(int ptr[][9],int size){
	int i=0;
	int k=0;
	for(i=0;i<size;i++){
		for(k=0;k<size;k++){
			ptr[i][k]=(i*size)+k+1;		
		}
		for(k=k;k<9;k++){
			ptr[i][k]=99;
		}
	}
	ptr[size-1][size-1]=0;
	for(i=i;i<9;i++){
		for(k=0;k<9;k++){
			ptr[i][k]=99;
		}
	}
}
int find_the_same_line(int ptr[9][9],int ptr_2[9][9],int goal_ptr[9][9],int size){
	int i=0;
	int j=0;
	int m=0;
	int k=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(ptr[i][j]<size*(i+1) && ptr[i][j]>size*i){
				m++; // m countu artar
			}
		}
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(ptr_2[i][j]<size*(i+1) && ptr_2[i][j]>size*i){
				k++; // m countu artar
			}
		}
	}
	if(m>k){
		return 1;
	}
	else {
		return 2 ;
	}

}
