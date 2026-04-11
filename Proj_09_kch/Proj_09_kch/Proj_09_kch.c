#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef char* element;

typedef struct DSongNode {
	struct DSongNode* llink;
	struct DSongNode* rlink;
	element sName;
}DSongNode;

typedef struct DPlaylistNode {
	DSongNode* slink;
	struct DPlaylistNode* llink;
	struct DPlaylistNode* rlink;
	element pName;
	int s_num;
} DPlaylistNode;

typedef struct {
	DPlaylistNode* head;
	int p_num;
} PlaylistNode;

void init_S(DPlaylistNode* D) {
	D->slink = NULL;
	D->s_num = 0;
}

void insert_nSongList(DPlaylistNode* D, element s_name, DSongNode** S) {
	DSongNode* new_S = (DSongNode*)malloc(sizeof(DSongNode));
	new_S->sName = (char*)malloc(strlen(s_name) + 1);
	strcpy(new_S->sName, s_name);
	if (D->s_num == 0) {
		D->slink = new_S;
		new_S->llink = new_S;
		new_S->rlink = new_S;
	}
	else {
		new_S->rlink = D->slink->rlink;
		D->slink->rlink->llink = new_S;
		new_S->llink = D->slink;
		D->slink->rlink = new_S;
		D->slink = new_S;
	}
	*S = new_S;
	D->s_num++;
}

void delete_cSong(DPlaylistNode* D, DSongNode** S) {
	if (D->s_num == 0)
		return -1;

	DSongNode* removed = *S;
	DSongNode* next_node = removed->rlink;

	if (D->s_num == 1) {
		D->slink = NULL;
		*S = NULL;
	}
	else {
		removed->llink->rlink = removed->rlink;
		removed->rlink->llink = removed->llink;

		if (D->slink == removed) {
			D->slink = removed->llink;
		}
		*S = next_node;
	}
	free(removed->sName);
	free(removed);
	D->s_num--;
}

void change_cSong(DSongNode** S, int mode) {
	if (*S == NULL)
		return -1;
	if (mode == 1)
		*S = (*S)->rlink;
	else if (mode == 2)
		*S = (*S)->llink;
	else
		return -1;
}

void print_aSong(DPlaylistNode* D, DSongNode* S) {
	printf("Song list :");
	if (D->s_num == 0)
		printf(" (null)\n");
	else {
		DSongNode* temp = D->slink->rlink;
		for (int i = 0; i < D->s_num; ++i) {
			if (temp == S)
				printf(" <-[*%s*]->", temp->sName);
			else
				printf(" <-[%s]->", temp->sName);
			temp = temp->rlink;
		}
	}
}

void init_P(PlaylistNode* L) {
	L->head = NULL;
	L->p_num = 0;
}

void insert_nPlaylist(PlaylistNode* L, element p_name, DPlaylistNode** D) {
	DPlaylistNode* new_P = (DPlaylistNode*)malloc(sizeof(DPlaylistNode));
	new_P->pName = (char*)malloc(strlen(p_name) + 1);
	strcpy(new_P->pName, p_name);
	new_P->slink = NULL;
	new_P->s_num = 0;
	if (L->p_num == 0) {
		L->head = new_P;
		new_P->llink = new_P;
		new_P->rlink = new_P;
	}
	else {
		new_P->rlink = L->head->rlink;
		L->head->rlink->llink = new_P;
		new_P->llink = L->head;
		L->head->rlink = new_P;
		L->head = new_P;
	}
	*D = new_P;
	L->p_num++;
}

void delete_cPlaylist(PlaylistNode* L, DPlaylistNode** D) {
	if (L->p_num == 0)
		return -1;

	DPlaylistNode* removed = *D;
	DPlaylistNode* next_node = removed->rlink;

	while (removed->s_num > 0)
		delete_cSong(removed, &(removed->slink));

	if (L->p_num == 1) {
		L->head = NULL;
		*D = NULL;
	}
	else {
		removed->llink->rlink = removed->rlink;
		removed->rlink->llink = removed->llink;

		if (L->head == removed) {
			L->head = removed->llink;
		}
		*D = next_node;
	}
	free(removed->pName);
	free(removed);
	L->p_num--;
}

void change_cPlaylist(DPlaylistNode** D, int mode) {
	if (*D == NULL)
		return -1;
	if (mode == 1)
		*D = (*D)->rlink;
	else if (mode == 2)
		*D = (*D)->llink;
	else
		return -1;
}

void print_aPlaylist(PlaylistNode L, DPlaylistNode* D){
	printf("Playlist :");
	if (L.p_num == 0)
		printf(" (null)\n");
	else {
		DPlaylistNode* temp = L.head->rlink;
		for (int i = 0; i < L.p_num; ++i) {
			if (temp == D)
				printf(" <-[*%s*]->", temp->pName);
			else
				printf(" <-[%s]->", temp->pName);
			temp = temp->rlink;
		}
	}
}

void print_playlist_menu(void)
{
	printf("\n\n---- Playlist Menu ----\n");
	printf(" a : print all playlist\n");
	printf(" c : print current playlist\n");
	printf(" n : new playlist\n");
	printf(" d : delete playlist\n");
	printf(" > : next playlist\n");
	printf(" < : previous playlist\n");
	printf(" s : song menu\n");
	printf(" q : quit\n");
	return;
}
void print_song_menu(void)
{
	printf("\n\n---- Song Menu ----\n");
	printf(" a : print all songs\n");
	printf(" c : print current song\n");
	printf(" n : add new song in playlist\n");
	printf(" d : delete current song\n");
	printf(" > : next song\n");
	printf(" < : previous song\n");
	printf(" b : quit\n");
	return;
}

int main(void)
{
	PlaylistNode head;
	char buf[100];
	init_P(&head);

	DPlaylistNode* currentPlaylist = NULL;
	DSongNode* currentSong = NULL;
	char menu, sub_menu;
	do {
		//printf("메뉴 선택");
		print_playlist_menu();
		printf("Select Menu : ");
		scanf(" %c", &menu);
		printf("--------------------------\n");
		printf("Selected playlist menu : %c \n", menu);
		switch (menu) {
		case 'a':
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'c':
			if (currentPlaylist == NULL)
				printf("No playlist exists\n");
			else
				printf("Current playlist : %s\n", currentPlaylist->pName);
			break;
		case 'n':
			printf("Playlist name : ");
			scanf("%s", buf);
			insert_nPlaylist(&head, buf, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'd':
			delete_cPlaylist(&head, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '<':
			change_cPlaylist(&currentPlaylist, 2);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '>':
			change_cPlaylist(&currentPlaylist, 1);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 's':
			if(currentPlaylist == NULL)
				printf("No playlist exists\n");
			else {
				currentSong = currentPlaylist->slink;
				do {
					printf("\nCur PL : %s \n", currentPlaylist->pName);
					print_song_menu();
					printf("Select Menu : ");
					scanf(" %c", &sub_menu);
					printf("Selected song menu : %c \n", sub_menu);
					switch (sub_menu) {
					case 'a':
						print_aSong(currentPlaylist, currentSong);
						break;
					case 'c':
						if (currentPlaylist == NULL)
							printf("No song exists\n");
						else
							printf("current song : %s\n", currentSong->sName);
						break;
					case 'n':
						printf("Song name : ");
						scanf("%s", buf);
						insert_nSongList(currentPlaylist, buf,
							&currentSong);
						print_aSong(currentPlaylist, currentSong);
						break;
					case 'd':
						delete_cSong(currentPlaylist, &currentSong);
						print_aSong(currentPlaylist, currentSong);
						break;
					case '<':
						change_cSong(&currentSong, 2);
						print_aSong(currentPlaylist, currentSong);
						break;
					case '>':
						change_cSong(&currentSong, 1);
						print_aSong(currentPlaylist, currentSong);
						break;
					}
				} while (sub_menu != 'b');
			}
			break;
		}
	} while (menu != 'q');
	return 0;
}