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

	void addData();
	void dispData(); //Done bare minimum
	void favit(); // Done
	void editData(int); // INCOMPLETE
};

// Enter song data for the first time
void Song::addData(){
	cout<<"\nEnter title:";
	cout<<"\nEnter artist: ";
	cout<<"\nEnter album: ";
	cout<<"\nEnter duration: ";
}
// Display formatted song data
void Song::dispData(){
	cout<<title<<"\t"<<artist<<"\t"<<album<<"\t"<<duration;
}

// Favorite your songs
void Song::favit(){
	if(isfav == 0) isfav = 1;
	else isfav = 0;
}

// You can choose what part of a song you want to edit with numbers
// 1 for title
// 2 for Album
// 3 for Artist
// 4 for Duration
// This function is probably useless
void Song::editData(int x){
	if(x == 1) {
		cout<<"\nEnter new title: ";
	}
	else if(x == 2) {
		cout<<"\nEnter new album name: ";
	}
	else if(x == 3) {
		cout<<"\nEnter new artist name: ";
	}
	else if(x == 4) {
		cout<<"\nEnter new duration: ";
	}
	else {
		cout<<"\nInvalid option. Try again";
		cout<<"\nEnter the option";
		cin>>x;
		editData(x);
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
// Depends on addData()
void Playlist::addSong() {
	char ch;
	songlist[songcount].addData();
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
	Playlist play[10];// Can users have songs which dont belong to any playlist?
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
