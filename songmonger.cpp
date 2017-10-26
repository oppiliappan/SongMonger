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
	fgets(title, 20, stdin);
	cout<<"\nEnter artist: ";
	fgets(artist, 20, stdin);
	cout<<"\nEnter album: ";
	fgets(album, 20, stdin);
	cout<<"\nEnter duration (sec.): ";
	cin>>duration;
}
// Display formatted song data
void Song::dispData(){
	cout<<title<<"\t"<<artist<<"\t"<<album<<"\t"<<duration;
	if(isfav == 1)cout<<"\t*\n";
	else cout<<"\n";
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

class Library{
protected:
	Song songlist[20];
public:
	void dispSongs(); // complete

	// depends on an incomplete function
	void addSong(); //Songs --> Song because one song at a time
	void delSong(); // New and done
	static int songcount;
};

int Library::songcount = 0;

void Library::dispSongs() {
	for(int i=0; i<Library::songcount; i++){
		cout << i + 1 << ". ";
		songlist[i].dispData();
	}
}

// Depends on addData()
void Library::addSong() {
	char ch;
	do {
		songlist[songcount].addData();
		songcount++;
		cout << "Add more? [Y/n] ";
		cin >> ch;
	} while(ch == 'y');
}

void Library::delSong() {
	int ch;
	cout << "Which one?\n";
	dispSongs();
	cout << "Enter choice: ";
	cin >> ch;
	for (int i=ch; i<songcount; i++) {
		if(i < sizeof(songlist)/2) songlist[i] = songlist[i + 1]; // if statement prevents segmentation faults
	}
	songcount--;
}

// Inheriting Class
class Playlist: public Library {
private:
	char playname[20];
public:
	Playlist() {
		strcpy(playname, "UNTITLED");
	}
	void setPlayName();
	void dispPlayName(); // complete
	void addSong();
	void delSong();
};

void Playlist::setPlayName() {
	cout << "Enter playlist name: ";
	fgets(playname, 20, stdin);
}

void Playlist::dispPlayName() {
	puts(playname);
	cout << "\t\t" << songcount << "song(s)";
}

// Is this function overloading attempt correct?
// It (ideally) overloads the definition from the Library class
void Playlist::addSong() {
	int ch;
	do {
		cout << "Add what? ";
		dispSongs();
		cin >> ch;
		Library::songlist[songcount+1] = Playlist::songlist[ch]; // n + 1 is vacant, add song there
		Playlist::songcount++;
		cout << "Add more? [1. Yes! 2. No] ";
		cin >> ch;
	} while(ch == 1);
}

// Is this function overloading attempt also correct?
void Playlist::delSong() {
	int ch;
	cout << "Which one?\n";
	dispSongs();
	cout << "Enter choice: ";
	cin >> ch;
	for (int i=ch; i<songcount; i++) {
		if(i < sizeof(songlist)/2) songlist[i] = songlist[i + 1]; // if statement prevents segmentation faults
	}
	songcount--;
}

class User {
private:
	char username[10];
	Library songs;
	Playlist plists[10];

public:
	void getUsername(){
		cout<<username;
	}
	void dispDetails();
	void addToLibrary();
	void viewLibrary();

	static int playlistcount;
}users[5];

int User::playlistcount= 0;

void User::dispDetails() {
	cout<<"\nName: "<<username;
	cout<<"\nSongs: \n";
	if ((Library::songcount) == 0) cout<<"No songs\n";
	else{
		songs.dispSongs();
	}
	cout<<"\nPlaylists: \n";
	if (User::playlistcount == 0) cout<<"No playlists\n";
	else{
		for(int i=0; i<playlistcount; i++){
			plists[i].dispPlayName();
		}
	}
}

void User::addToLibrary() {
	songs.addSong();
	cout<<"\nYou currently have "<<Library::songcount<<" songs\n";
}

void User::viewLibrary(){
	songs.dispSongs();
}

int main(){
	cout<<"\t\t\tWelcome to SongMonger!\n";

	/*
	TODO
	1. User abc
	2. User xyz
	Choose option
		Welcome User abc
			Name: abc
			Songs:
				1.
				2.
				3.
			Playlists:
				1.
				2.
				3.
			1. Library actions
			2. Playlist actions
			3. Logout
			Enter option
				Library actions
					1. Add song
					2. Edit song
					3. Delete song
					4. Back

					Playlist actions
					1. Create new playlist
					2. Edit existing playlist
					3. Delete playlist
					4. Back
	*/


	// enter user select
	char quit_program = 'n';
	do{
		cout<<"Select user\n";
		for(int i=0; i<5; i++){
			cout<<i<<" ";
			users[i].getUsername();
		}

		int choose_user = -1;
		cin>>choose_user;
		choose_user--; // convert to array index

		// enter user actions
		char logout = 'n';
		do{
			users[choose_user].dispDetails();
			cout<<"1. Library actions\n";
			cout<<"2. Playlist actions\n";
			cout<<"3. Back to user select\n";
			cout<<"\n What would you like to do?\n";

			int user_action;
			cin>>user_action;

			// enter specific actions
			char exit_actions='n';
			do{
				switch(user_action){
					case 1:{
						cout<<"\nLibrary actions\n";
						cout<<"1. Add songs\n";
						cout<<"2. Edit songs\n";
						cout<<"3. Delete songs\n";
						cout<<"4. Back\n";
					}
				}
			}while(exit_actions == 'n');
		}while(logout == 'n');
	}while(quit_program == 'n');

	return 0;
}
