//g++ -std=c++11 `fltk-config --cxxflags` visible.cpp  `fltk-config --ldflags` -o trial
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Text_Display.H>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

static const int tilesize = 75;
int h1,h2,gdepth;
int weight[8][8];
class Board;
class Board : public Fl_Widget {
	
	public:
	int player,score1,score2,mode;
	int grid[8][8];
	char*scoreLabel;
	Fl_Box * scoreBox;
	Board(int mode);
	void draw();    
	void game();
	int handle (int e);
	void setScoreBox(Fl_Box** sb);
	//int scorecoins(int grid[][8],int player,int k);
	//int negamax(int grid[][8],int player,int alpha,int beta,int depth,int k);
	//pair<int, int> bestmove(int g[][8], int player, int depth,int k);
};
//To display scorebox
void Board::setScoreBox(Fl_Box** sb)
{
	scoreBox = *sb ;
	score1=0;score2=0;
	scoreLabel = (char*) malloc(sizeof(char)*100);
}
//checking if the move is available
int present(pair<int,int> point,vector<pair<int,int> > res){
	bool val=false;
	for(int i=0;i<res.size();i++){
		if(point.first==res[i].first && point.second==res[i].second)return true;
	}
	return val;
}
//player 1 is white 255
//player -1 is black 0 
//Creating a vector of valid moves
vector<pair<int,int> > validmoves(int grid[][8],int player){
		vector<pair<int,int> > res;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(grid[i][j]!=16581375)continue;
				if(player==1){
					int k=i+1;int n=0;int l=0;
					//checking vertically below 
					while(grid[k][j]==0 && k<8){
						n++;
						k++;
					}
					if(!(k>=8 or n==0)){
						if(grid[k][j]==255)res.push_back(make_pair(i,j));
					}
					//checking vertically above
					k=i-1;n=0;
					while(k>=0 && grid[k][j]==0 ){
						n++;
						k--;
					}
					if(!(k<0 or n==0)){
						if(grid[k][j]==255)res.push_back(make_pair(i,j));
					}
					//checking horizantally right
					k=j+1;n=0;
					while(k<8 && grid[i][k]==0 ){
						n++;
						k++;
					}
					if(!(k>=8 or n==0)){
						if(grid[i][k]==255)res.push_back(make_pair(i,j));
					}
					//checking horizantally left
					k=j-1;n=0;
					while(k>=0 && grid[i][k]==0 ){
						n++;
						k--;
					}
					if(!(k<0 or n==0)){
						if(grid[i][k]==255)res.push_back(make_pair(i,j));
					}
					k=i-1;l=j-1;n=0;
					//topleft
					while(k>=0 && l>=0 && grid[k][l]==0 ){
						n++;
						k--;
						l--;
					}
					if(!(k<0 or l<0 or n==0)){
						if(grid[k][l]==255)res.push_back(make_pair(i,j));
					}
					//bottom right
					k=i+1;l=j+1;n=0;
					while(k<8 && l<8 && grid[k][l]==0 ){
						n++;
						k++;
						l++;
					}
					if(!(k>=8 or l>=8 or n==0)){
						if(grid[k][l]==255)res.push_back(make_pair(i,j));
					}
					//top right
					k=i-1;l=j+1;n=0;
					while(k>=0 && l<8 && grid[k][l]==0 ){
						n++;
						k--;
						l++;
					}
					if(!(k<0 or l>=8 or n==0)){
						if(grid[k][l]==255)res.push_back(make_pair(i,j));
					}
					// bottom left
					k=i+1;l=j-1;n=0;
					while(k<8 && l>=0 && grid[k][l]==0 ){
						n++;
						k++;
						l--;
					}
					if(!(k>=8 or l<0 or n==0)){
						if(grid[k][l]==255)res.push_back(make_pair(i,j));
					}
				}
				if(player==-1){
					int k=i+1;int n=0;int l=0;
					//checking vertically below 
					while(grid[k][j]==255 && k<8){
						n++;
						k++;
					}
					if(!(k>=8 or n==0)){
						if(grid[k][j]==0)res.push_back(make_pair(i,j));
					}
					//checking vertically above
					k=i-1;n=0;
					while(k>=0 && grid[k][j]==255 ){
						n++;
						k--;
					}
					if(!(k<0 or n==0)){
						if(grid[k][j]==0)res.push_back(make_pair(i,j));
					}
					//checking horizantally right
					k=j+1;n=0;
					while(k<8 && grid[i][k]==255 ){
						n++;
						k++;
					}
					if(!(k>=8 or n==0)){
						if(grid[i][k]==0)res.push_back(make_pair(i,j));
					}
					//checking horizantally left
					k=j-1;n=0;
					while(k>=0 && grid[i][k]==255 ){
						n++;
						k--;
					}
					if(!(k<0 or n==0)){
						if(grid[i][k]==0)res.push_back(make_pair(i,j));
					}
					k=i-1;l=j-1;n=0;
					//topleft
					while(k>=0 && l>=0 && grid[k][l]==255 ){
						n++;
						k--;
						l--;
					}
					if(!(k<0 or l<0 or n==0)){
						if(grid[k][l]==0)res.push_back(make_pair(i,j));
					}
					//bottom right
					k=i+1;l=j+1;n=0;
					while(k<8 && l<8 && grid[k][l]==255 ){
						n++;
						k++;
						l++;
					}
					if(!(k>=8 or l>=8 or n==0)){
						if(grid[k][l]==0)res.push_back(make_pair(i,j));
					}
					//top right
					k=i-1;l=j+1;n=0;
					while(k>=0 && l<8 && grid[k][l]==255 ){
						n++;
						k--;
						l++;
					}
					if(!(k<0 or l>=8 or n==0)){
						if(grid[k][l]==0)res.push_back(make_pair(i,j));
					}
					// bottom left
					k=i+1;l=j-1;n=0;
					while(k<8 && l>=0 && grid[k][l]==255 ){
						n++;
						k++;
						l--;
					}
					if(!(k>=8 or l<0 or n==0)){
						if(grid[k][l]==0)res.push_back(make_pair(i,j));
					}
				}	
			}
		}
	
	return res;
	}
void makemove(int grid[][8],int i,int j){
	int opcolor;
	int color = grid[i][j];
	if(grid[i][j]==255){opcolor =0;}
	else opcolor =255;
		int n=0,k=i+1,l=0;
		while(grid[k][j]==opcolor && k<8){
			n++;
			k++;
		}
		if(!(k>=8 or n==0)){
			if(grid[k][j]==color){
				for(int m=i;m<=k;m++){
					grid[m][j]=color;
				}
			}
		}
		//checking vertically above
		k=i-1;n=0;
		while(k>=0 && grid[k][j]==opcolor ){
			n++;
			k--;
		}
		if(!(k<0 or n==0)){
			if(grid[k][j]==color){
				for(int m=k;m<=i;m++){
					grid[m][j]=color;
				}
			}
		}
		//checking horizantally right
		k=j+1;n=0;
		while(k<8 && grid[i][k]==opcolor ){
			n++;
			k++;
		}
		if(!(k>=8 or n==0)){
			if(grid[i][k]==color){
				for(int m=j;m<=k;m++){
					grid[i][m]=color;
				}
			}
		}
		//checking horizantally left
		k=j-1;n=0;
		while(k>=0 && grid[i][k]==opcolor ){
			n++;
			k--;
		}
		if(!(k<0 or n==0)){
			if(grid[i][k]==color){
				for(int m=k;m<=j;m++){
					grid[i][m]=color;
				}
			}
		}
		k=i-1;l=j-1;n=0;
		int count =0;
		//fliping in topleft
		while(k>=0 && l>=0 && grid[k][l]==opcolor ){
			n++;
			k--;
			l--;
			count++;
		}
		if(!(k<0 or l<0 or n==0)){
			if(grid[k][l]==color){
				for (int m = 0; m <=count; ++m)
				{
					grid[k+m][l+m]=color;
				}
			}
		}
		//flipping in bottom right
		k=i+1;l=j+1;n=0;
		count =0;
		while(k<8 && l<8 && grid[k][l]==opcolor ){
			n++;
			k++;
			l++;
			count++;
		}
		if(!(k>=8 or l>=8 or n==0)){
			if(grid[k][l]==color){
				for (int m = 0; m <=count; ++m)
				{
					grid[i+m][j+m]=color;
				}
			}
		}
		//flipping in bottom left
		k=i-1;l=j+1;n=0;
		count =0;
		while(k>=0 && l<8 && grid[k][l]==opcolor ){
			n++;
			k--;
			l++;
			count++;
		}
		if(!(k<0 or l>=8 or n==0)){
			if(grid[k][l]==color){
				for (int m = 0; m <=count; ++m)
				{
					grid[k+m][l-m]=color;
				}
			}
		}
		// flipping in top right
		k=i+1;l=j-1;n=0;
		count =0;
		while(k<8 && l>=0 && grid[k][l]==opcolor ){
			n++;
			k++;
			l--;
			count++;
		}
		if(!(k>=8 or l<0 or n==0)){
			if(grid[k][l]==color){
				for (int m = 0; m <=count; ++m)
				{
					grid[k-m][l+m]=color;
				}
			}
		}
}
//from the perspective of maximizing player
double score(int grid[][8],int play,int k){
	int sum1=0,sum2=0;
//	if(player==-1)k=h1;if(player==1)k=h2;
	for(int i=0;i<8;i++){
		for (int j = 0; j < 8; ++j)
		{	
			if(k==1 || k==3 || k==4){if(grid[i][j]==255)sum1++;
			         if(grid[i][j]==0)sum2++;}
			if(k==2){if(grid[i][j]==255)sum1+=(weight[i][j]);
			         if(grid[i][j]==0)sum2+=(weight[i][j]);}
			
			if(k==5){if(grid[i][j]==255)25*sum1++;
			         if(grid[i][j]==0)25*sum2++;if(grid[i][j]==255)sum1+=25*weight[i][j];
			         if(grid[i][j]==0)sum2+=25*weight[i][j];
			         if(grid[0][0]==255)30*sum1++;if(grid[0][0]==0)30*sum2++;
			         if(grid[0][7]==255)30*sum1++;if(grid[0][7]==0)30*sum2++;
			         if(grid[7][0]==255)30*sum1++;if(grid[7][0]==0)30*sum2++;
			         if(grid[7][7]==255)30*sum1++;if(grid[7][7]==0)30*sum2++;
			         sum1=5*validmoves(grid,1).size();sum2=5*validmoves(grid,-1).size();}
		}
	}
	if(k==3){if(grid[0][0]==255)sum1+=10;if(grid[0][0]==0)sum2+=10;
			         if(grid[0][7]==255)sum1+=10;if(grid[0][7]==0)sum2+=10;
			         if(grid[7][0]==255)sum1+=10;if(grid[7][0]==0)sum2+=10;
			         if(grid[7][7]==255)sum1+=10;if(grid[7][7]==0)sum2+=10;}
			if(k==4){sum1+=2*validmoves(grid,-1).size();sum2+=2*validmoves(grid,1).size();}
	//if(sum1+sum2 ==0)return 0;
	double res=(sum1-sum2)*play;
	return res;
}


void copy(int grid[][8],int copygrid[][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			copygrid[i][j]=grid[i][j];
		}
	}
}
//negamax algorithm to find best score
double negamax(int grid[][8],int player,double alpha,double beta,int depth,int h){
	double bestscore =-100000;
	if(depth==0)return score(grid,player,h);	
	vector<pair<int,int> >moves=validmoves(grid,player);
	if(moves.size()==0){
		if(validmoves(grid,-1*player).size()==0){
			return score(grid,player,h);
		}
		double val = -negamax(grid,-1*player,-beta,-alpha,depth-1,h);
		if(val>alpha){
			alpha =val;
		}
		if(val>bestscore){
				bestscore=val;
			}
		if(alpha >= beta)return bestscore;
		
	}
	else{
		for(int i=0;i<moves.size();i++){
			int copygrid[8][8];
			copy(grid,copygrid);
			if(player==1){
				copygrid[moves[i].first][moves[i].second]=255;
			}
			else copygrid[moves[i].first][moves[i].second]=0;
			makemove(copygrid,moves[i].first,moves[i].second);
			double val = -negamax(copygrid,-1*player,-beta,-alpha,depth-1,h);
			if(val>alpha){
				alpha=val;
			}
			if(val>bestscore){
				bestscore=val;
			}
			if(alpha >= beta){
				break;
			}
			
		}
	}
	return bestscore;
}
// bestmove is created here
pair<int,int> bestmove(int grid[][8],int player,int depth,int h){
	double alpha = -100000;
	int beta = 100000;int bestscore =-100000;
	vector<pair<int,int> >moves=validmoves(grid,player);
	pair<int,int> move = moves[0];
	for(int i=0;i<moves.size();i++){
			int copygrid[8][8];
			copy(grid,copygrid);
			if(player==1){
				copygrid[moves[i].first][moves[i].second]=255;
			}
			else copygrid[moves[i].first][moves[i].second]=0;
			makemove(copygrid,moves[i].first,moves[i].second);
			double val = -negamax(copygrid,-1*player,-beta,-alpha,depth-1,h);
			
			if(val>alpha){
				alpha=val;
				//move = moves[i];
			}
			if(val>bestscore){
				bestscore=val;
				move = moves[i];
			}
			if(alpha >= beta){
				break;
			}
		}
		return move;
}
//whole game is explained here
void Board::game(){
    while(!((validmoves(grid,-1).size()==0 && validmoves(grid,1).size()==0) || score1+score2==64)){
        if(player==-1){
            if(validmoves(grid,-1).size()!=0){    
            pair<int,int> bestmove1 = bestmove(grid,-1,gdepth,h1);
					grid[bestmove1.first][bestmove1.second]=0;
					makemove(grid,bestmove1.first,bestmove1.second);
					cout<<"player 1"<<" "<<bestmove1.first<<" "<<bestmove1.second<<endl;
					}
			player=1;continue;
			}
		 if(player==1){
            if(validmoves(grid,1).size()!=0){    
            pair<int,int> bestmove1 = bestmove(grid,1,gdepth,h2);
					grid[bestmove1.first][bestmove1.second]=255;
					makemove(grid,bestmove1.first,bestmove1.second);
					//cout<<"player 2"<<" "<<bestmove1.first<<" "<<bestmove1.second<<endl;
					}
			player=-1;continue;
			}
					}
	   int s1=0;int s2=0;
	   for(int i=0;i<8;i++){
	   	for(int j=0;j<8;j++){
	   		if(grid[i][j]==255)s1++;
	   		if(grid[i][j]==0)s2++;}}
	   if(s1>s2){cout<<2<<" "<<s1<<" "<<s2<<endl;}
	   if(s1<s2){cout<<1<<" "<<s2<<" "<<s1<<endl;}
	   if(s1==s2){cout<<0<<" "<<s1<<" "<<s2<<endl;}}
int Board::handle(int e) {

	if (e==2 && Fl::event_button() == FL_LEFT_MOUSE) 
	 { 
		int x1=Fl::event_x();
		int y1=Fl::event_y();
		x1=(x1)/(tilesize+1);
		y1=(y1)/(tilesize+1);
	/*	if(player==-1){
			if(x1>=0 && y1 <8 && y1>=0 && y1<8){
			//	cout<<"player";
				cout<<"player"<<" "<<x1+1<<" "<<y1+1<<endl;
				vector<pair<int,int> >res=validmoves(grid,-1);
				if(present(make_pair(x1,y1),res)){
					grid[x1][y1]=0;
					makemove(grid,x1,y1);
					player=1;
					//cout<<"player: "<<player<<endl;
					vector<pair<int,int> >res=validmoves(grid,1);
					for(int i=0;i<res.size();i++){
						//cout<<res[i].first<<" "<<res[i].second<<endl;
					}
				//	cout<<" computer ";
					if(validmoves(grid,1).size()!=0){
					pair<int,int> bestmove1 = bestmove(grid,1,gdepth);
					grid[bestmove1.first][bestmove1.second]=255;
					makemove(grid,bestmove1.first,bestmove1.second);
					cout<<" comp"<<" "<<bestmove1.first<<" "<<bestmove1.second<<endl;
					player=-1;}
					player=-1;
				}
				while(validmoves(grid,-1).size()==0){
					if(validmoves(grid,1).size()==0)break;
					pair<int,int> bestmove1 = bestmove(grid,1,gdepth);
					grid[bestmove1.first][bestmove1.second]=255;
					makemove(grid,bestmove1.first,bestmove1.second);
					cout<<" comp"<<" "<<bestmove1.first<<" "<<bestmove1.second<<endl;
					player=-1;}}
			
		}*/
		
		if(x1>=8 && x1<=12){
			if(y1==3){//cout<<" restart ";
			/*	player=-1;
				   for(int i=0;i<8;i++){
					for(int j=0;j<8;j++){
						grid[i][j]=16581375;
					}
				}
		  		 grid[3][3]=255;grid[3][4]=0;grid[4][4]=255;grid[4][3]=0;*/
		  		 game();}
		  	if(y1==4){score1=0;score2=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(grid[i][j]==0)score1++;
			if(grid[i][j]==255)score2++;}}
			cout<<score1<<" "<<score2<<endl;exit(0);}}}
	score1=0;score2=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(grid[i][j]==0)score1++;
			if(grid[i][j]==255)score2++;}}
	//cout<<"label"<<endl;
	stringstream strs1,strs2;
	strs1 << score1;
	string temp_str = strs1.str();
	if(h1==1)strcpy(scoreLabel,"coins: ");
	if(h1==2)strcpy(scoreLabel,"stability: ");
	if(h1==3)strcpy(scoreLabel,"corners: ");
	if(h1==4)strcpy(scoreLabel,"mobility: ");
	strcat(scoreLabel,(char*) temp_str.c_str() );
	strs2 << score2;temp_str = strs2.str();
	if(h2==1)strcat(scoreLabel,"\ncoins: ");
	if(h2==2)strcat(scoreLabel,"\nstability: ");
	if(h2==3)strcat(scoreLabel,"\ncorners: ");
	if(h2==4)strcat(scoreLabel,"\nmobility: ");
	strcat(scoreLabel,(char*) temp_str.c_str() );
//	strcat(scoreLabel,"\nturn : player's \n");
	if((validmoves(grid,-1).size()==0 && validmoves(grid,1).size()==0) || score1+score2==64){
		if(score1>score2){strcat(scoreLabel,"\nstatus : player 1\n");cout<<"player 1"<<endl;}
		if(score1<score2){strcat(scoreLabel,"\nstatus : player 2 \n");cout<<"player 2"<<endl;}
		if(score1==score2){strcat(scoreLabel,"\nstatus : Draw \n");cout<<"Draw"<<endl;}}
	else strcat(scoreLabel,"\nstatus : ongoing \n");
	scoreBox->label(scoreLabel); 
	redraw();
	
	}
	
Board::Board(int mode) : Fl_Widget (0,0,880,8*(tilesize+1),"Othello") {
                   player=-1;
				   for(int i=0;i<8;i++){
					for(int j=0;j<8;j++){
						grid[i][j]=16581375;
					}
				}
		   grid[3][3]=255;grid[3][4]=0;grid[4][4]=255;grid[4][3]=0;
		   
	if(mode==0){game();exit(1);}}

void Board::draw () {
           for(int i=0;i<=7;i++){
                  for(int j=0;j<=7;j++){
						fl_draw_box(FL_FLAT_BOX,i*(tilesize+1),j*(tilesize+1),tilesize,tilesize,16711680);
						fl_color(grid[i][j]);
						fl_pie(i*(tilesize+1.5),j*(tilesize+1.5),tilesize*0.9,tilesize*0.9,0,360);
					}
            }       
}



int main(int argc, char *argv[]) {
weight[0][0]=9;weight[0][1]=2;weight[0][2]=7;weight[0][3]=7;weight[0][4]=7;weight[0][5]=7;weight[0][6]=2;weight[0][7]=9;
weight[1][0]=2;weight[1][1]=1;weight[1][2]=4;weight[1][3]=4;weight[1][4]=4;weight[1][5]=4;weight[1][6]=1;weight[1][7]=2;
weight[2][0]=7;weight[2][1]=4;weight[2][2]=6;weight[2][3]=5;weight[2][4]=5;weight[2][5]=6;weight[2][6]=4;weight[2][7]=7;
weight[3][0]=7;weight[3][1]=4;weight[3][2]=5;weight[3][3]=6;weight[3][4]=6;weight[3][5]=5;weight[3][6]=4;weight[3][7]=7;
weight[4][0]=7;weight[4][1]=4;weight[4][2]=5;weight[4][3]=6;weight[4][4]=6;weight[4][5]=5;weight[4][6]=4;weight[4][7]=7;
weight[5][0]=7;weight[5][1]=4;weight[5][2]=6;weight[5][3]=5;weight[5][4]=5;weight[5][5]=6;weight[5][6]=1;weight[5][7]=7;
weight[6][0]=2;weight[6][1]=1;weight[6][2]=4;weight[6][3]=4;weight[6][4]=4;weight[6][5]=4;weight[6][6]=1;weight[6][7]=2;
weight[7][0]=9;weight[7][1]=2;weight[7][2]=7;weight[7][3]=7;weight[7][4]=7;weight[7][5]=7;weight[7][6]=2;weight[7][7]=9;

    Fl_Window *window = new Fl_Window (880,608,"Othello"); // outer window
	window->color(56);   
	h1=atoi(argv[1]),h2=atoi(argv[2]);
	gdepth=atoi(argv[3]);
	int mode=atoi(argv[4]);
	Board *b = new Board(mode);
        Fl_Box *scorebox = new Fl_Box(608,0,272,3*(tilesize+1),"Your Score: 2\n Computer :2 \n turn: player's \n");
	scorebox->box(FL_UP_BOX);
        scorebox->labelfont(FL_BOLD+FL_ITALIC);
        scorebox->labelsize(20);
        scorebox->labeltype(FL_ENGRAVED_LABEL);
	b->setScoreBox(&scorebox);     
	Fl_Box *scorebox1 = new Fl_Box(608,3*(tilesize+1),272,(tilesize+1),"Start");
	scorebox1->box(FL_UP_BOX);
        scorebox1->labelfont(FL_BOLD+FL_ITALIC);
        scorebox1->labelsize(20);
        scorebox1->labeltype(FL_ENGRAVED_LABEL);
        Fl_Box *scorebox2 = new Fl_Box(608,4*(tilesize+1),272,(tilesize+1),"Quit");
	scorebox2->box(FL_UP_BOX);
        scorebox2->labelfont(FL_BOLD+FL_ITALIC);
        scorebox2->labelsize(20);
        scorebox2->labeltype(FL_ENGRAVED_LABEL);
        
	window->end();  
   	window->show();
    	return(Fl::run());  // the process waits from here on for events
}


