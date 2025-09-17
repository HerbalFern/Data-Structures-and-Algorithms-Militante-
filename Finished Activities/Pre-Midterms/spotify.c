#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NAME 50
#define MAX_ARTIST 30
#define MAX_ALBUM 30

// Struct to hold views, likes, and dislikes of a song
typedef struct{
    int totalViews;  
    int likes;
    int dislikes;
} View;

// Struct to represent a Song
typedef struct {
    char title[MAX_NAME];      
    char artist[MAX_ARTIST];   
    char album[MAX_ALBUM];     
    int duration;              
    View views;                
} Song;

// Node of the linked list (each node is one song in the queue)
typedef struct songNode {
    Song track;                
    struct songNode *next;     
} *SongNode;

// Queue struct that holds the front and rear pointers
typedef struct {
    SongNode front;            
    SongNode rear;             
} SpotifyQueue;


// Function declarations
void initQueue(SpotifyQueue *q);
bool isEmpty(SpotifyQueue *q);
void addPlaySong(SpotifyQueue *q, char *title, char *artist, char *album, int duration, int views, int likes, int dislikes);
void skipSong(SpotifyQueue *q);
Song getSong(SpotifyQueue *q);
void displaySongs(SpotifyQueue *q);


int main(){
    SpotifyQueue q;
    initQueue(&q); 
    
    addPlaySong(&q, "Manchild", "Sabrina Caprenter", "HeartBreak", 140, 100000000, 1000000, 25000);
    addPlaySong(&q, "Touch", "Katseye", "Beautiful Chaos", 150, 250000, 5400, 1200);
    addPlaySong(&q, "Cupid", "FIFTY FIFTY", "Love is Cute", 180, 3500000, 250000, 150);
    addPlaySong(&q, "Daleng Daleng", "Abra Cadabra", "Magic to", 200, 1000, 10, 20);
    addPlaySong(&q, "Gento", "SB19", "Lupa", 180, 5000, 2500, 1500);
    addPlaySong(&q, "Nani Ga Suki", "IceScream", "Konikawa", 180, 600, 50, 40);


 
    displaySongs(&q);
    skipSong(&q);
    skipSong(&q);
    skipSong(&q);

    displaySongs(&q);
    return 0;  
}

// Initializes the queue 
void initQueue(SpotifyQueue *q){ 
    q->front = NULL;
    q->rear = NULL;
}

// Checks if the queue is empty, returns true if no songs, false otherwise
bool isEmpty(SpotifyQueue *q){
    if (q->front == NULL){
        return true;
    } return false;
}

// Adds a new song to the queue (enqueue operation)
void addPlaySong(SpotifyQueue *q, char *title, char *artist, char *album, int duration, int views, int likes, int dislikes){
    SongNode temp = malloc(sizeof(*temp));
    if (temp == NULL){
        printf("\nmem alloc failed\n");
        return;
    }

    
    temp->next = NULL;
    strcpy(temp->track.title, title);
    strcpy(temp->track.artist, artist);
    strcpy(temp->track.album, album);
    temp->track.duration = duration;
    temp->track.views.totalViews = views;
    temp->track.views.likes = likes;
    temp->track.views.dislikes = dislikes;


    if (isEmpty(q)){
        q->front = temp; 
        q->rear = temp;   
    } else {
        q->rear->next = temp;
        q->rear = temp; // lmao you dumbfuck u forgot this
    }
}

// Removes the first song in the queue 
void skipSong(SpotifyQueue *q){
    SongNode temp;
    temp = q->front;
    q->front = q->front->next;
    free(temp);
}

// Returns the first song in the queue 
Song getSong(SpotifyQueue *q){
    return q->front->track;
}

// dont toucherere
void displaySongs(SpotifyQueue *q){ 
    SongNode trav;
    int i = 0;
    printf("My Playlist\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s   %-15s    %-24s   %-24s   %-15s  %-16s   %-16s %-16s\n", "Song No.", "Title", "Artist", "Album", "Duration", "Total Views", "Likes", "Dislikes");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // traverse the linked list from front to rear
    for(trav = q->front; trav != NULL; trav = trav->next){
        i++;
        printf("%-10d   %-15s    %-24s   %-24s   %-15d  %-16d  %-16d  %-16d\n", 
               i, trav->track.title, trav->track.artist, 
               trav->track.album, trav->track.duration,
               trav->track.views.totalViews, trav->track.views.likes,
               trav->track.views.dislikes);
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}