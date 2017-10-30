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
	} else if(x == 2) {
		cout<<"\nEnter new album name: ";
	} else if(x == 3) {
		cout<<"\nEnter new artist name: ";
	} else if(x == 4) {
		cout<<"\nEnter new duration: ";
	} else {
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
	char ch = 'n';
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
	User() {
		strcpy(username, "Jawn_dough");
		isactivated = 'n';
	}
	void getUsername(){
		cout<<username;
	}
	void setup(); // for the first time setup
	void dispDetails();
	void addToLibrary();
	void viewLibrary();
	void delFromLibrary();
	static int usercount; // this is the static variable we deserve
	int playlistcount;
	char isactivated; // Self explanatory - high quality comment
}users[5];

int User::usercount = 0;

void User::setup() {
	cout << "Enter your username (No spaces or special characters): ";
	cin >> username;
	usercount++;
	isactivated = 'y';
	cout << "Now let's get songmongering!";
}

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

void deleteSong(){
	songs.delSong();
}


/* -------------------------- MAIN ----------------------------- */
int main(){
	cout<<"\t\t\tWelcome to SongMonger!\n";

	/*
	TODO
	You forgot this ----> 1. New User 2. Existing user
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
		char ch;
		cout << "1. New User\n2. Existing User\n";
		cin >> ch;
		if (ch == '1') {
			int i = 0;
			// looks for the last unused account
			while (users[i].isactivated == 'y') {
				if (i == 4) {
					cout << "User limit exceeded!";
					break;
				}
				i++;
			}
			users[i].setup();
		}

		cout<<"Select user\n";
		for(int i=0; i<users[0].usercount; i++){
			// this will make sure only existing users show up
			cout << '\n' << i + 1 << " ";
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

						// enter lib actions
						char quit_lib_actions = 'n';
						do{
							cout<<"\nLibrary actions\n";
							cout<<"1. Add songs\n";
							cout<<"2. Edit songs\n";
							cout<<"3. Delete songs\n";
							cout<<"4. Back\n";

							int lib_action;
							cin>>lib_action;

							switch(lib_action){
								case 1:
									users[choose_user].addToLibrary();
									break;
								case 2:
									// aaaaaa we dont have an edit function
									break;
								case 3:
									users.[choose_user].delFromLibrary();
									break;
								case 4:
									quit_lib_actions = 'y';
									break;
								default:
									cout<<"Invalid option\n";
									break;
							}
							cout<<"Go back? (y/n)\n";
							cin>>quit_lib_actions;
						} while (quit_lib_actions == 'n');
						break;
					}
					case 2:{

						// enter play actions
						char quit_play_actions = 'n';
						do{
							cout<<"\nPlaylist actions\n";
							cout<<"1. Create playlist\n";
							cout<<"2. Edit existing playlist\n";
							cout<<"3. Delete playlist\n";
							int play_action;
							cin>>play_action;

							switch(play_action){
								case 1:
									users[choose_user].addToLibrary();
									break;
								case 2:
									// aaaaaa we dont have an edit function
									break;
								case 3:
									break;
									// we dont have a delete function either aaaaaa
								case 4:
									quit_play_actions = 'y';
									break;
								default:
									cout<<"Invalid option\n";
							}
							cout<<"Would you like to quit? (y/n)\n";
							cin>>quit_play_actions;
						} while (quit_play_actions == 'n');
						break;
					}
				}
			} while (exit_actions == 'n');
		} while (logout == 'n');
	} while (quit_program == 'n');
	return 0;
}
