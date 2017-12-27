#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>

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
			isfav    = 0;
		}

		int checkfav() {
			return isfav;
		}
		
		char* gettitle() {
			return title;
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
	cout<<setw(15)<<title;
	cout<<setw(15)<<artist;
	cout<<setw(15)<<album;
	cout<<setw(15)<<duration;
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
		void dispfavSongs(); // complete

		// depends on an incomplete function
		void addSong(); //Songs --> Song because one song at a time
		void delSong(); // New and done
		void editSong();
		void favinLibrary(int song_ind);
		int songcount;
		void adminAddSong();
		Song getSong(int);
};

void Library::dispSongs() {
	cout<<"\n";
	cout<<"No.";
	cout<<setw(15)<<"Title";
	cout<<setw(15)<<"Artist";
	cout<<setw(15)<<"Album";
	cout<<setw(15)<<"Duration";
	cout << "\n";
	for(int i=0; i<songcount; i++){
		cout << i + 1 << ". ";
		songlist[i].dispData();
	}
}

void Library::dispfavSongs() {
	cout << "\n";
	cout<<"No.";
	cout<<setw(15)<<"Title";
	cout<<setw(15)<<"Artist";
	cout<<setw(15)<<"Album";
	cout<<setw(15)<<"Duration";
	cout << "\n";
	for(int i=0, j=0; i<songcount; i++, j++){
		cout << j + 1 << ". ";
		if (songlist[i].checkfav() == 1) {
			songlist[i].dispData();
		}
	}
}
// Depends on addData()
// For ADMIN
void Library::adminAddSong() {
	char ch = 'n';
	do {
		songlist[songcount].addData();
		songcount++;
		cout << "Add more? [y/n] ";
		cin >> ch;
	} while(ch == 'y');
	ofstream sfile;
	sfile.open("songs.dat", ios::binary | ios::app);
	for (int i = 0; i < songcount; i++) {
		sfile.write((char*)&songlist[i], sizeof(Song));
	}
}

// For Users
void Library::addSong() {
	ifstream sfile;
	sfile.open("songs.dat", ios::binary);
	Song temp;
	int ch;
	cout << "Obtaining songs\n";
	while (sfile.read((char*)&temp, sizeof(Song))) {
		temp.dispData();
	}
	cout << "Select a song:\n";
	cin >> ch;
	sfile.clear();
	sfile.seekg((ch - 1) * sizeof(Song), ios::beg);
	cout << sfile.tellg();
	sfile.read((char*)&temp, sizeof(Song));
	for (int i = 0; i < songcount; i++) {
		if (strcmp(songlist[i].gettitle(), temp.gettitle()) == 0) {
			cout << "You already have this song!";
			return;
		}
	}
	songlist[songcount] = temp;
	songcount++;
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
	ch--; // Conver to array index
	for (int i=ch; i<songcount; i++) {
		if(i < sizeof(songlist)/2) songlist[i] = songlist[i + 1]; // if statement prevents segmentation faults
	}
	songcount--;
}

void Library::favinLibrary(int song_ind) {
	song_ind--;
	songlist[song_ind].favit();
}

Song Library::getSong(int x){
	return songlist[x];
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
		void addSong(Song);
		void delSong();
};

void Playlist::setPlayName() {
	cout << "Enter playlist name: ";
	cin>>playname;
}

void Playlist::dispPlayName() {
	cout<<playname<<" ("<<songcount<<" songs)";
}

// Is this function overloading attempt correct?
// It (ideally) overloads the definition from the Library class
void Playlist::addSong(Song newsong) {
	songlist[songcount] = newsong;
}

// Is this function overloading attempt also correct?
void Playlist::delSong() {
	int ch;
	cout << "Which one?\n";
	dispSongs();
	cout << "Enter choice: ";
	cin >> ch;
	ch--;
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
			playlistcount = 0;
		}
		void getUsername(){
			cout<<username; // dont add spaces here, add them where you need them
		}
		void setup(); // for the first time setup
		void dispAll();
		void dispFav();

		// Library function definitions
		void addToLibrary();
		void addToGlobalLibrary();
		void editLibrary();
		void viewLibrary();
		void delFromLibrary();
		Song getSong(int x);
		void favSong(int song_index);

		// Playlist function definitions
		void createPlaylist();
		void dispPlayName();
		void editPlaylist();
		void delPlaylist();
		static int usercount; // this is the static variable we deserve

		// File handling
		void storeUsercount();
		void readUserCount();
		void storeUserdata();
		void readUserdata(int);
		void storeAll(User *userobj);
		void readAll(User *userobj);

		int playlistcount;
		char isactivated; // Self explanatory - high quality comment
}users[5], admin;

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
	cout<<"\n---------------------------SONGS--------------------------------";
	if ((songs.songcount) == 0) cout<<"\nNo songs";
	else{
		songs.dispSongs();
	}
	dispPlayName();
}

void User::dispFav() {
	cout<<"\nName: "<<username;
	cout<<"\nSongs: ";
	if ((songs.songcount) == 0) cout<<"\nNo songs";
	else {
		songs.dispfavSongs();
	}
	dispPlayName();
}
void User::addToLibrary() {
	songs.addSong();
	cout<<"\nYou currently have "<<songs.songcount<<" songs\n";
}

void User::addToGlobalLibrary(){
	songs.adminAddSong();
	cout<<"\nThere are currently "<<songs.songcount<<" songs in global Library\n";
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

void User::favSong(int song_index) {
	songs.favinLibrary(song_index);
}

Song User::getSong(int x){
	return songs.getSong(x);
}

void User::createPlaylist(){
	plists[playlistcount].setPlayName();
	system("clear");

	char continue_adding = 'y';
	do{
		system("clear");
		cout<<"----------------";
		plists[playlistcount].dispPlayName();
		cout<<"----------------";
		cout<<"\n";

		songs.dispSongs();

		int ch;
		cout<<"\nEnter song to be added to ";
		plists[playlistcount].dispPlayName();
		cout<<"\n";
		cin>>ch;
		plists[playlistcount].addSong(getSong(ch-1));
		plists[playlistcount].songcount++;

		cout<<"Add more songs? [y/n]\n";
		cin>>continue_adding;
	}while(continue_adding == 'y');

	system("clear");
	plists[playlistcount].dispPlayName();
	cout<<"\n";
	plists[playlistcount].dispSongs();
	playlistcount++;
}

void User::dispPlayName() {
	cout<<"\n------------------------PLAYLISTS-------------------------------\n";
	if (User::playlistcount == 0) cout<<"No playlists\n";
	else{
		for(int i=0; i<playlistcount; i++){
			cout<<i + 1<<" ";
			plists[i].dispPlayName();
			cout<<"\n";
		}
	}
}

void User::editPlaylist() {
	system("clear");
	cout<<"Editing playlists\n";
	dispPlayName();

	int ch;
	cout<<"Which playlist to edit?\n";
	cin>>ch;
	ch--; // Convert to array index

	system("clear");

	char continue_editing = 'y';
	do{
		system("clear");
		plists[ch].dispSongs();
		cout<<"\n";
		cout<<"1. Add song\n";
		cout<<"2. Remove song\n";
		cout<<"3. Change song name\n";
		cout<<"4. Back\n";

		int edit_choice;
		cin>>edit_choice;

		switch(edit_choice){
			case 1:{
				system("clear");
				songs.dispSongs();

				cout<<"Which song?\n";
				char continue_adding='y';

				do{
					system("clear");
					cout<<"----------------";
					plists[playlistcount].dispPlayName();
					cout<<"----------------";
					cout<<"\n";

					songs.dispSongs();

					int ch;
					cout<<"\nEnter song to be added to ";
					plists[playlistcount].dispPlayName();
					cout<<"\n";
					cin>>ch;
					plists[playlistcount].addSong(getSong(ch-1));
					plists[playlistcount].songcount++;

					cout<<"Add more songs?\n";
					cin>>continue_adding;
				}while(continue_adding == 'y');

				cout<<"Continue editing? (y/n)\n";
				cin>>continue_editing;
			break;
			}

			case 2:
				system("clear");
				plists[ch].delSong();
				cout<<"Continue editing? (y/n)\n";
				cin>>continue_editing;
				break;
			case 3:
				system("clear");
				plists[ch].setPlayName();
				cout<<"Continue editing? (y/n)\n";
				cin>>continue_editing;
				break;
			case 4:
				continue_editing = 'n';
				break;
		}

	}while(continue_editing == 'y');

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
	system("clear");
	cout<<"        Welcome to Songmonger!\n";
	cout<<"   A music managment application in C++\n\n";
	cout<<"        Hit Enter to continue";
	cin.ignore();

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
a: // Planned goto
		char ch;
		system("clear");
		cout << "1. New User\n2. Existing User\n3. Admin User\n4. Quit Program\n";
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
			users[i].storeAll(users);
		}
		else if(ch == '3'){
			system("clear");
b:
			cout<<"\nWelcome to Admin\n";
			cout<<"1. Add to global library\n";
			cout<<"2. Edit songs from global library\n";
			cout<<"3. Remove songs from global library\n";
			cout<<"4. Back\n";
			cout<<"\n Choose a option...";

			int admin_choice = -1;
			cin>>admin_choice;

			char quit_admin = 'n';

			switch(admin_choice){
				case 1:
					cout<<"Adding songs to global library\n";
					admin.addToGlobalLibrary();
					break;
				case 2:
					cout<<"Editing songs from global library\n";
					admin.editLibrary();
					break;
				case 3:
					cout<<"Removing songs from global library\n";
					admin.delFromLibrary();
					break;
				case 4:
					quit_admin = 'y';
					break;
			}

			if(quit_admin == 'n'){
				cout<<"Quit Admin? [y/n]\n";
				cin>>quit_admin;
			}
			if(quit_admin == 'n'){
				goto b;
			}
			else if(quit_admin == 'y'){
				goto a;
			}

		}
		else if(ch == '4'){
			exit(0);
		}

		if (User::usercount == 0) {
			cout << "No users!";
			cin.ignore();
			cin.ignore();
			goto a;
		}
		users[0].readAll(users); // loads all users
		system("clear");
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
		int fav_only_toggle = 0;
		do{
			system("clear");
			if (fav_only_toggle == 0) {
				users[choose_user].dispAll();
			} else {
				cout << "(Showing only favourites)";
				users[choose_user].dispFav();
			}

			// these are 'user actions'
			cout<<"\n------------------------MAIN MENU-------------------------------\n";
			cout<<"1. Library actions\n";
			cout<<"2. Playlist actions\n";
			cout<<"3. Add to favourites OR Remove from favourites\n";
			cout<<"4. Toggle Show Only Favourites\n";
			cout<<"5. Back to user select\n";
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
						cout<<"2. Delete songs\n";
						cout<<"3. Back\n";

						int lib_action;
						cin>>lib_action;

						switch(lib_action){
							case 1:
								users[choose_user].addToLibrary();
								break;
							case 2:
								users[choose_user].delFromLibrary();
								break;
							case 3:
								quit_lib_actions = 'y';
								break;
							default:
								cout<<"Invalid option\n";
						}

						if(quit_lib_actions == 'n'){
							cout<<"Would you like to quit library actions? (y/n)\n";
							cin>>quit_lib_actions;
						}

					} while (quit_lib_actions == 'n');
					users[0].storeAll(users);
					break;
				}

				case 2:{
					char quit_play_actions = 'n';

					// enter play actions
					do{
						system("clear");
						cout<<"-------Playlist actions-------\n";
						cout<<"1. Create playlist\n";
						cout<<"2. Edit existing playlist\n";
						cout<<"3. Delete playlist\n";
						cout<<"4. Back\n";

						int play_action;
						cin>>play_action;

						switch(play_action){
							case 1:
								users[choose_user].createPlaylist();
								break;
							case 2:
								users[choose_user].editPlaylist();
								break;
							case 3:
								users[choose_user].delPlaylist();
								break;
							case 4:
								quit_play_actions = 'y';
								break;
							default:
								cout<<"Invalid option\n";
						}

						if(quit_play_actions == 'n'){
							cout<<"Would you like to quit playlist actions? (y/n)\n";
							cin>>quit_play_actions;
						}
					} while (quit_play_actions == 'n');
					break;
				}
				case 3:{
					int *fav_action = new int;
					cout << "Which song? ";
					cin >> *fav_action;
					users[choose_user].favSong(*fav_action);
					break;
					users[0].storeAll(users);
				}

				case 4: {
					if (fav_only_toggle == 0) {
						fav_only_toggle = 1;
					}
					else {
						fav_only_toggle = 0;
					}
					break;
				}
				case 5: {
					back_to_userselect = 'y';
					break;
				}
			}
		}while(back_to_userselect == 'n');

	} while (quit_program == 'n'); //back to your PC
	return 0;
}
