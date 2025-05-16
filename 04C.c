#include <stdio.h>
#include <string.h>

#define M 1046527
#define L 14

char H[M][L]; /* Hash Table */

// 文字に対応する値
int getChar(char ch){
    if ( ch == 'A') return 1;
    else if ( ch == 'C') return 2;
    else if ( ch == 'G') return 3;
    else if ( ch == 'T') return 4;
    else return 0;
}

// 文字列からキーを作る
long long getKey(char str[]){
    long long sum = 0, p = 1, i;
    for ( i = 0; i < strlen(str); i++ ){
    sum += p*(getChar(str[i]));
    p *= 5;
    }
    return sum;
}

int h1(int key){ return key % M; }
int h2(int key){ return 1 + (key % (M - 1)); }

// 文字列を与えるとハッシュ値が作成され，その値にデータがあるかを返す
int find(char str[]){
    long long key, i, h;
    key = getKey(str);
    for ( i = 0; i < M; i++ ){
        h = (h1(key) + i*h2(key)) % M;
        if ( strcmp(H[h], str) == 0 ) return 1; // 見つかった場合
        else if ( strlen(H[h]) == 0 ) return 0; // 見つからなかった場合
    }
    return 0; // 見つからなかった場合
}

// データを挿入する
int insert(char str[]){
    if (find(str)) return 0; // すでに存在する場合は何もしない

    long long key = getKey(str);
    int h;
    for (int i = 0; i < M; i++){
        h = (h1(key) + i*h2(key)) % M;
        if ( strcmp(H[h], str) == 0 ) return 1;
        else if ( strlen(H[h]) == 0 ){
            strcpy(H[h], str); // 空いている場所に挿入
            return 0;
        }
    }
    return 0;
}

int main(){
    int i, n, h;
    char str[L], com[9];
    for ( i = 0; i < M; i++ ) H[i][0] = '\0';

    scanf("%d", &n);

    for ( i = 0; i < n; i++ ){
	scanf("%s %s", com, str);
        if ( com[0] == 'i' ){
            insert(str);
        } else {
            if (find(str)){
            printf("yes\n");
            } else {
            printf("no\n");
            }
        }
    }

    return 0;
}