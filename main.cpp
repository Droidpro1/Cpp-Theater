/* 
 * Author: Ritvik Divanji
 */

#include <iostream> //for I/O control
#include <string> //for string usage
#include <fstream> //for file I/O
#include <cmath> //for absolute value

using namespace std;

int getRows(char a[26][10]){
    ifstream inData;
    inData.open("A1.txt");

    /*Gets the number of rows by counting the number
     of newline characters (adding one to account for 
     the last line of the file)*/
    string line;
    int numRows=0;
    while(!inData.eof()) {
        getline(inData, line);
        if (!line.empty())
            numRows++;
    }
    inData.close();
    return numRows;
}

int getCols(char a[26][10]){
    ifstream inData;
    inData.open("A1.txt");

    /*This gets the length of the first line in the 
    file, which is equal to the amount of columns for
    the array*/

    string firstLine;
    getline(inData,firstLine);
    int numCols=firstLine.length();
    inData.close();
    return numCols;
}

void displayReport(char a[26][10]){
    char ch;
    int adult=0; //num of adult tickets
    int child=0; //num of child tickets
    int senior=0; //num of senior tickets
    int seats=0;
    int ticketsSold=0;
    double totalSales=0;

    /*Iterates through the array, adds to
     respective counter*/

    for(int y=0;y<getRows(a);y++){
        for(int x=0;x<getCols(a);x++){
            if(a[x][y]=='A')
                adult++;
            else if(a[x][y]=='C')
                child++;
            else if(a[x][y]=='S')
                senior++;
            seats++;
        }
    }
    //calculates the amount of seats by adding all counters together
    ticketsSold=adult+child+senior;
    //does the math for the sales
    totalSales=(adult*10)+(child*5)+(senior*7.5);
    //the output
    cout<<"\nThere are "<<seats<<" total seats"<<endl;
    cout<<"There are "<<ticketsSold<<" total tickets sold."<<endl;
    cout<<"There are "<<adult<<" adult tickets sold."<<endl;
    cout<<"There are "<<child<<" child tickets sold."<<endl;
    cout<<"There are "<<senior<<" senior tickets sold."<<endl;
    cout<<"Total sales were $"<<totalSales<<"!"<<endl;
}
bool checkAvailability(char a[26][10], int r, char s, int q){
    bool available=true;
    string columnHeader="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    columnHeader.resize(getCols(a)); //resizes the column header to match the length of the array

    /*find where the character of the column is in the alphabet, 
    that will be the column of the array to start the loop that iterates
    to find if there is a reserved seat, where the character is anything
    but a '.' If the character is a letter, then return false*/

    int col=columnHeader.find(s); //finds the row character in the alphabet and returns the position
    if(r<=0 || r>getRows(a)){ //to account for silly users
        return false;
    }
    if(col==-1){ //if the user wanted a seat on a column that does not exist
        return false;
    }
    for(int c=0;c<q;c++){
        if(a[col+c][r-1]!='.' || a[col+c][r-1]=='\0'){
            return false;
        }
    }
    return true;
}

void displayAuditorium(char a[26][10]){
    ifstream inData;
    inData.open("A1.txt");

    string line;

    string columnHeader="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    columnHeader.resize(getCols(a)); //resizes the column header to match the length of the array
    cout<<"   "<<columnHeader<<endl; //prints the column header
    for(int y=0;y<getRows(a);y++){
        getline(inData,line); //iterates line by line throughout the file
        //this if else is just for formatting
        if(y+1==10)
            cout<<y+1<<" "; //adds the header for the rows, y starts at 0 thats why add 1
        else
            cout<<y+1<<"  ";
        for(int x=0;x<getCols(a);x++){ //line.at(x) gets the character at the x position in the array 
            if(line.at(x)!='.') //all letters are outputted as #
                cout<<'#';
            else
                cout<<line.at(x);
            a[x][y]=line.at(x);
        }
        cout<<endl; //when the row ends, start a new one
    }
    cout<<endl;
    inData.close();
}

void writeBack(char a[26][10], int r, int c){
    ofstream outData;
    outData.open("A1.txt");
    //clears the file and starts putting stuff from the array into the file
    for(int y=0;y<r;y++){
        for(int x=0;x<c;x++)
            outData<<a[x][y];
        if(y!=r-1)//to prevent a trailing newline character from being added to the file
            outData<<"\n";
    }
    outData.close();
}

void reserveSeats(char a[26][10], int r, char s, int aq, int cq, int sq){
    string columnHeader="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    columnHeader.resize(getCols(a)); //resizes the column header to match the length of the array
    int col=columnHeader.find(s);

    //iterates through the row, setting the desired 'box' as the proper character
    for(int c=0;c<aq;c++)
        a[col+c][r-1]='A';
    for(int c=0;c<cq;c++)
        a[col+c+aq][r-1]='C';
    for(int c=0;c<sq;c++)
        a[col+c+aq+cq][r-1]='S';
    cout<<"\nYour seats have been reserved at!"<<endl;
    writeBack(a, getRows(a), getCols(a));
}

char bestAvailable(char a[26][10], int r, int q){
    string columnHeader="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    columnHeader.resize(getCols(a));
    char startingSeat;
    double middleSelection=0.0;
    double middleRow=((double)getCols(a))/2.0;
    double dist=30.0; //30 is an arbitrary number that every distance calculated will be shorter than
    int i=0;
    bool atLeastOneFound=false;

    /*iterates through the row, calculates the middle of the desired rows, 
     checks if it is available, then checks if the distance to the middle of
     the auditorium is the least that it has found*/

    while(i<getCols(a)-q+1){
        //find the middle of the quantity desired, then offset that by i
        middleSelection=q/2.0+i;
        //if the seat is available and the new distance is lower than the previous
        //set the new distance as the distance and set the current seat as the startingSeat 
        if(checkAvailability(a, r, columnHeader.at(i), q) && (double)abs(middleRow - middleSelection) < dist){
            dist=(double)abs(middleRow-middleSelection);
            startingSeat=columnHeader.at(i);
            atLeastOneFound=true;
        }
        i++;
    }
    //if there isn't a best available seating arrangement found, return some arbitrary character
    if(!atLeastOneFound)
        startingSeat='&';
    return startingSeat;
}

int main(){
    char auditorium[26][10];
    string columnHeader="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    columnHeader.resize(getCols(auditorium));

    do{
        int choice=0;
        do{
            cout<<"1. Reserve Seats\n2. Exit"<<endl;
            cin>>choice;
        }while(!(choice==1 || choice==2));
        if(choice==2) {
            displayReport(auditorium);
            writeBack(auditorium, getRows(auditorium), getCols(auditorium));
            exit(0);
        }
        displayAuditorium(auditorium);
        int r=0;
        char col;
        int adult=0;
        int child=0;
        int senior=0;
        do{
            cout<<"\nWhich row would you like to reserve a seat in?"<<endl;
            cin>>r;
        }while(r>getRows(auditorium)|| r<=0);
        do{
            cout<<"\nWhich column would you like to reserve a seat in?"<<endl;
            cin>>col;
            col=toupper(col); //makes the character uppercase
        }while(columnHeader.find(col)==-1);
        do{
            do{
                cout<<"\nHow many adult seats would you like to reserve?"<<endl;
                cin>>adult;
            }while(adult<0);
            do{
                cout<<"\nHow many child seats would you like to reserve?"<<endl;
                cin>>child;
            }while(child<0);
            do{
                cout<<"\nHow many senior seats would you like to reserve?"<<endl;
                cin>>senior;
            }while(senior<0);
        }while(adult+child+senior>getCols(auditorium));
        if(checkAvailability(auditorium, r, col, adult+child+senior)){
            reserveSeats(auditorium, r, col, adult, child, senior);
            //break;
        }
        else{
            cout<<"\nThose seats aren't available\nWould you like to reserve the best available seats on row "<<r<<"?"<<endl;
            cout<<"\n1. Yes\n2. No"<<endl;
            cin>>choice;
            if(choice!=2){
                char seat=bestAvailable(auditorium, r, adult+child+senior);
                if(seat=='&'){
                    cout<<"No best seats were found.\nSorry :("<<endl;
                }
                else
                    reserveSeats(auditorium, r, seat, adult, child, senior);
            }
        }
    }while(true);
    return 0;
}