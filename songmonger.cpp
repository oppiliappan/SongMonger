#include<iostream>
#include<fstream>

using namespace std;

class Song{
private:
	char title[20], artist[10], album[10];
	int isfav, duration, views;
public:
	void dispData();
};

class Playlist{
private:
	char playname[20];
	Song songlist[10];
public:
	void dispSongs();
};

class User{
private:
	char username[10], language[10];
	Playlist play;
public:
	void dispDetails();
	void addPlaylist();
	void viewPlaylist(char);
}user1, user2, user3;

void User::dispDetails(){
	cout<<"\nName: "<<username;
	cout<<"\nLanguage: "<<language;
	cout<<"\nPlaylists: ";
	play.dispSongs();
}


int main(){
	return 0;
}
