#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

// How about making this a queue?
class Song{
	private:
		char title[20], artist[10], album[10];
		int isfav, duration, views;
	public:
		Song() {
			strcpy(title, "UNTITLED");
			strcpy(album, "UNTITLED");
			strcpy(artist, "NIL");
			duration = 0;
			isfav = 0;
		}

		void addData();
		void dispData(); //Done bare minimum
		void favit(); // Done
		void editData(); //Done for now
};

// Enter song data for the first time
void Song::addData(){
	cout<<"\nEnter title: ";
	//fgets(title, 20, stdin);
	cin>>title;
	cout<<"Enter artist: ";
	//fgets(artist, 20, stdin);
	cin>>artist;
	cout<<"Enter album: ";
	//fgets(album, 20, stdin);
	cin>>album;
	cout<<"Enter duration (sec.): ";
	cin>>duration;
}
// Display formatted song data
void Song::dispData() {
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
// This function is probably useless --> How on earth was it incomplete for so long?!
// Illlogical to change duration of a song
void Song::editData(){
	int *ch = new int;
	cout << "Edit options: \n1. Title\n2. Album Name\n3. Artist name\n";
	cin >> *ch;
	cin.ignore();
	if(*ch == 1) {
		cout<<"\nEnter new title: ";
		fgets(title, 20, stdin);
	} else if(*ch == 2) {
		cout<<"\nEnter new album name: ";
		fgets(album, 20, stdin);
	} else if(*ch == 3) {
		cout<<"\nEnter new artist name: ";
		fgets(artist, 20, stdin);
	} else {
		cout<<"\nInvalid option. Try again\n";
		editData();
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
		void editSong();
		int songcount;
};

void Library::dispSongs() {
	cout << "\n";
	for(int i=0; i<songcount; i++){
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
		cout << "Add more? [y/n] ";
		cin >> ch;
	} while(ch == 'y');
}

void Library::editSong() {
	int *ch = new int;
	cout << "Which song to edit?";
	dispSongs();
	cout << "Select number: ";
	cin >> *ch;
	songlist[(*ch - 1)].editData();
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
			cout<<username; // dont add spaces here, add them where you need them
		}
		void setup(); // for the first time setup
		void dispAll();

		// Library function definitions
		void addToLibrary();
		void editLibrary();
		void viewLibrary();
		void delFromLibrary();

		// Playlist function definitions
		void dispPlayName();
		void editPlaylistName();
		void delPlaylist();
		static int usercount; // this is the static variable we deserve

		// File handling
		void storeUsercount();
		void readUserCount();
		void storeUserdata();
		void readUserdata(int index);
		void storeAll(User *userobj);
		void readAll(User *userobj);

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

void User::dispAll() {
	cout<<"\nName: "<<username;
	cout<<"\nSongs: ";
	if ((songs.songcount) == 0) cout<<"\nNo songs";
	else{
		songs.dispSongs();
	}
	dispPlayName();
}

void User::addToLibrary() {
	songs.addSong();
	cout<<"\nYou currently have "<<songs.songcount<<" songs\n";
}

void User::editLibrary() {
	songs.editSong();
}

void User::viewLibrary(){
	songs.dispSongs();
}

void User::delFromLibrary() {
	songs.delSong();
}

void User::dispPlayName() {
	cout<<"\nPlaylists: \n";
	if (User::playlistcount == 0) cout<<"No playlists\n";
	else{
		for(int i=0; i<playlistcount; i++){
			plists[i].dispPlayName();
		}
	}
}

void User::editPlaylistName() {
	int *ch = new int;
	cout << "Which playlist?";
	dispPlayName();
	cin >> *ch;
	plists[*ch].setPlayName();
}

void User::delPlaylist() {
	int *ch = new int;
	cout << "Which playlist?";
	dispPlayName();
	cin >> *ch;
	for (int i = *ch; i < playlistcount; i++) {
		if(i < sizeof(Playlist)/2) plists[i] = plists[i + 1]; // if statement prevents segmentation faults
	}
	playlistcount--;
}

void User::storeUsercount() {
	remove("usercount.txt");
	ofstream countfile;
	countfile.open("usercount.txt");
	countfile << User::usercount;
}

void User::readUserCount() {
	ifstream countfile;
	countfile.open("usercount.txt");
	countfile >> User::usercount;
}

void User::storeUserdata() {
	ofstream file;
	file.open("userdata.dat", ios::out | ios::binary | ios::app);
	file.write((char*)this, sizeof(User));
	file.close();
}

void User::readUserdata(int index) {
	ifstream file;
	file.open("userdata.dat", ios::in | ios::binary);
	file.seekg(index * (sizeof(User)), ios::beg);
	file.read((char*)this, sizeof(User));
	file.close();
}

// This stores data for ALL USERS
void User::storeAll(User *userobj) {
	remove("userdata.dat");
	for (int i = 0; i < User::usercount; i++) {
		userobj[i].storeUserdata();
	}
	storeUsercount();
}

// Loads all data into User objects
void User::readAll(User *userobj) {
	readUserCount();
	for (int i = 0; i < User::usercount; i++) {
		userobj[i].readUserdata(i);
	}
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
		system("clear");
		cout << "1. New User\n2. Existing User\n3. Quit Program\n";
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
			users[0].storeAll(users);
		}
		else if(ch == '3'){
			exit(0);
		}

		users[0].readAll(users); // loads all users
		cout << "Currently Active Users: " << User::usercount;
		for(int i = 0; i < User::usercount; i++) {
			// this will make sure only existing users show up
			cout << "\n" << i + 1 << ". ";
			users[i].getUsername();
			cout<<"\n";
		}

		int choose_user = -1;
		cout<<"\nSelect user\n";
		cin >> choose_user;
		choose_user--; // convert to array index

		// enter user actions
		char back_to_userselect = 'n';
		do{
			system("clear");
			users[choose_user].dispAll();

			// these are 'user actions'
			cout<<"\n-------MAIN MENU-------\n";
			cout<<"1. Library actions\n";
			cout<<"2. Playlist actions\n";
			cout<<"3. User Details\n";
			cout<<"4. Back to user select\n";
			cout<<"\n What would you like to do?\n";

			int user_action;
			cin>>user_action;

			switch(user_action){
				case 1:{
					char quit_lib_actions = 'n';
					// enter lib actions
					do{
						system("clear");
						users[choose_user].viewLibrary();
						cout<<"\n-------Library actions-------\n";
						cout<<"1. Add songs\n";
						cout<<"2. Edit songs\n";
						cout<<"3. Delete songs\n";

								int lib_action;
								cin>>lib_action;

								switch(lib_action){
									case 1:
										users[choose_user].addToLibrary();
										break;
									case 2:
										users[choose_user].editLibrary();
										break;
									case 3:
										users[choose_user].delFromLibrary();
										break;
									default:
										cout<<"Invalid option\n";
								}

								cout<<"Would you like to quit library actions? (y/n)\n";
								cin>>quit_lib_actions;
							} while (quit_lib_actions == 'n');
							break;
						}
				case 2:{
						char quit_play_actions = 'n';

					// enter play actions
					do{
						system("clear");
						cout<<"-------\nPlaylist actions-------\n";
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
									users[choose_user].editPlaylistName();
									break;
								case 3:
									users[choose_user].delPlaylist();
									break;
								default:
									cout<<"Invalid option\n";
							}

							cout<<"Would you like to quit playlist actions? (y/n)\n";
							cin>>quit_play_actions;
						} while (quit_play_actions == 'n');
						break;
						}
				case 3:{
							system("clear");
							users[choose_user].dispAll();
							break;
						}
				case 4:{
							back_to_userselect = 'y';
							break;
						}
			}
		}while(back_to_userselect == 'n');

	} while (quit_program == 'n'); //back to your PC
	return 0;
}
