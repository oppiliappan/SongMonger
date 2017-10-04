#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Song{
private:
	char title[20], artist[10], album[10];
	int isfav, duration, views;
public:
	Song(){
		strcpy(title, "");
		strcpy(album, "");
		strcpy(artist, "");
		duration = 0;
		isfav = 0;
	}
	void dispData();
	void favit();
};

void Song::dispData(){
	cout<<title<<"\t"<<artist<<"\t"<<album<<"\t"<<duration;
}

void Song::favit(){
	if(isfav == 0) isfav = 1;
	else isfav = 0;
}

class Playlist{
private:
	char playname[20];
	Song songlist[10];
public:
	void dispPlayName();
	void dispSongs();
	void addSongs();
	static int songcount;
};

int Playlist::songcount = 0;

void Playlist::dispSongs(){
	for(int i=0; i<Playlist::songcount; i++){
		songlist[i].dispData();
	}
}
void Playlist::addSongs(){

}

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
