#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

// How about making this a queue?
class Song{
private:
	char title[20], artist[10], album[10];
	int isfav, duration, views;
public:
	Song(){
		strcpy(title, "UNTITLED");
		strcpy(album, "UNTITLED");
		strcpy(artist, "NIL");
		duration = 0;
		isfav = 0;
	}
	void dispData(); //Done bare minimum
	void favit(); // Done
	void editData(int); // INCOMPLETE
};

void Song::dispData(){
	cout<<title<<"\t"<<artist<<"\t"<<album<<"\t"<<duration;
}

void Song::favit(){
	if(isfav == 0) isfav = 1;
	else isfav = 0;
}

// Not sure what exactly you were trying here
// I'll leave it for you to do
void Song::editData(int x){
	if(x == 1) {
		cout<<"\nEnter new title: ";
	}
}

class Playlist{
private:
	char playname[20];
	Song songlist[10];
public:
	Playlist() {
		strcpy(playname, "UNTITLED");
	}
	void dispPlayName(); // complete
	void dispSongs(); // complete

	// depends on an incomplete function
	void addSong(); //Songs --> Song because one song at a time

	static int songcount;
};

int Playlist::songcount = 0;

void Playlist::dispPlayName() {
	puts(playname);
	cout << "\t\t" << songcount << "Song(s)";
}

void Playlist::dispSongs() {
	for(int i=0; i<Playlist::songcount; i++){
		songlist[i].dispData();
	}
}

// Is a recursive function
// Depends on an incomplete function
void Playlist::addSong() {
	char ch;
	songlist[songcount].editData(); // NOTE: Assuming this also adds data
	songcount++;
	cout << "Add more? [Y/n] ";
	cin >> ch;
	if (ch == 'y') {
		addSong();
	}
}

// Generally incomplete
class User{
private:
	char username[10];
	Playlist play[10];
public:
	void dispDetails();
	void addPlaylist();
	void viewPlaylist(char);

	static int playcount;
}user1, user2, user3;

int User::playcount = 0;

void User::dispDetails(){
	cout<<"\nName: "<<username;
	cout<<"\nPlaylists: ";
	for(int i=0; i<playcount; i++){
		play[i].dispPlayName();
	}
}


int main(){
	return 0;
}
