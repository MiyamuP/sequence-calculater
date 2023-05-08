//
//  main.c
//  k19104_0722_matrix
//
//  Created by k19104kk on 2019/07/11.
//  Copyright © 2019 AIT. All rights reserved.
//
//////////////////////////////行列の計算/////////////////////////////
#include <stdio.h>
#include <math.h>
#define GYORETUMAX (5)//行列の行数、列数の上限
#define SEIBUNMAX (99)//成分の最大数
#define SEIBUNMIN (-99)//成分の最小値
int Detaminant (int gyoc, int retuc, int d, int sum, int gyoretu[][GYORETUMAX], int gyoa[][GYORETUMAX], int retua[][GYORETUMAX]){
    retua[d][d] = 1;
    
    for (int i = d; i < gyoc; i++){
        gyoa[d][i] = 1;
        if (gyoc - d == 3){
            int g = 0;
            int r = 0;
            int plus = 1;
            
            while (g < gyoc && r < retuc){
                if (gyoa[d][g] == 0 && retua[d][r] == 0){
                    plus *= gyoretu[g][r];
                    g++;
                    r++;
                    continue;
                } else if (gyoa[d][g] == 1 && gyoa[d][g+1] == 0){
                    g++;
                } else if (retua[d][r] == 1 && retua[d][r+1] == 0){
                    r++;
                } else {
                    g++;
                    r++;
                }
            }
            g = gyoc;
            r = retuc;
            int minus = -1;
            while (g > 0 && r > 0) {
                if (gyoa[d][g] == 0 && retua[d][r] == 0){
                    minus *= gyoretu[g][r];
                    g--;
                    r--;
                    continue;
                } else if (gyoa[d][g] == 1 && gyoa[d][g-1] == 0){
                    g--;
                } else {
                    g--;
                    r--;
                }
            }
            sum += powf(-1, (d+1)+(i+1)) * gyoretu[d][i] * (plus+minus);
            
        }
        
    }
    return (sum);
    
}
int main(int argc, const char *argv[]){
    int gyocnt1, retucnt1, gyocnt2, retucnt2, ganscnt, ranscnt , gcnt, rcnt, num, numf, ascii, ketamax, seibun, firstf, grcnt, hikimode, deep, detaminantans;  // 変数の定義
    int gyoretu1[GYORETUMAX][GYORETUMAX], gyoretu2[GYORETUMAX][GYORETUMAX], gyoretuans[GYORETUMAX][GYORETUMAX], gyoavoid[GYORETUMAX][GYORETUMAX], retuavoid[GYORETUMAX][GYORETUMAX];  //配列変数の定義
    
    for (int i = 0; i < GYORETUMAX; i++) {
        for (int j = 0; j < GYORETUMAX; j++) {
            gyoavoid[i][j] = 0;
            retuavoid[i][j] = 0;
        }
    }
    gcnt = rcnt = num = numf = firstf = hikimode = deep = detaminantans = 0;  //変数の初期値の設定
    ketamax = 1;  //変数の初期値の設定
    char mode[2], ch ;  //文字の定義
    
//////モード選択//////
    do {
        printf("何を計算しますか？\n"
               "行列の和 → +を入力\n"
               "行列の差 → -を入力\n"
               "行列の積 → *を入力\n"
               "行列式   → dを入力\n"
               "終了     → eを入力\n\n");  //説明文を出力
        scanf("%s", &mode[0]);  //文字の入力
        
        if(mode[0] == 'e'){  //eが押されたら
            return 0;  //プログラムの終了
        }
        
    } while ((mode[0] != '+') && (mode[0] != '-') && (mode[0] != '*') && (mode[0] != 'd'));  //＋かーか＊かdが入力されるまで回す
    
    putchar('\n');  //改行
    
//////メイン部分//////
    if(mode[0] == '+' || mode[0] == '-' || mode[0] == '*' || mode[0] == 'd'){  //＋かーか＊かdが入力された時
        if (mode[0] == '+' || mode[0] == '-'){  //＋かーが入力された時
            grcnt = 2;  //入力する行列の数を設定
            do {
                printf("行列の行と列の数を入力(５行５列まで)");  //説明文を表示
                scanf("%d %d", &gyocnt1, &retucnt1);  //行と列の数を入力
            } while (gyocnt1 > GYORETUMAX || retucnt1 > GYORETUMAX || gyocnt1 <= 0 || retucnt1 <= 0);  //行と列の数が有効範囲外ならもう一度入力させる
            ganscnt = gyocnt1;  //答えの行の数の数を代入
            ranscnt = retucnt1;  //答えの列の数の値を代入
            
            gyocnt2 = gyocnt1;  //二つめの行の数を代入
            retucnt2 = retucnt1;  //二つめの列の数を代入
            
        } else if (mode[0] == '*'){  //*が入力された時
            grcnt = 2;  //入力する行列の数を設定
            do {
                for (int i = 0; i < grcnt; i++){  //二回行と列の数を入力させる
                    printf("%dつ目の行列の行と列の数を入力(５行５列まで)", i+1);  //説明文の表示
                    if (i == 0){  //一回めの入力
                        scanf("%d %d", &gyocnt1, &retucnt1);  //一つめの行と列の数を入力
                    } else {  //二回めの入力
                        scanf("%d %d", &gyocnt2, &retucnt2);  //二つめの行と列の数を入力
                    }
                }
                
            } while (gyocnt1 > GYORETUMAX || retucnt1 > GYORETUMAX || gyocnt1 <= 0 || retucnt1 <= 0 || gyocnt2 > GYORETUMAX || retucnt2 > GYORETUMAX || gyocnt2 <= 0 || retucnt2 <= 0 || retucnt1 != gyocnt2);  //二つの行と列の数が有効範囲外ならもう一度入力させる
            ganscnt = gyocnt1;  //答えの行の数を代入
            ranscnt = retucnt2;  //答えの列の値を代入
        } else {  //dが入力された時
            grcnt = 1;  //入力する行列の数を設定
            do {
                printf("行列の行と列の数を入力(５行５列まで)");  //説明文の表示
                scanf("%d %d", &gyocnt1, &retucnt1);  //行と列の数を入力
            } while (gyocnt1 > GYORETUMAX || retucnt1 > GYORETUMAX || gyocnt1 <= 0 || retucnt1 <= 0 || gyocnt1 != retucnt1);  //行と列の数が有効範囲外ならもう一度入力させる
        }
        putchar('\n');  //改行する
        printf("数列の成分を入力してください。\n"
               "数字を入力した後にスペースキーを打ち込むと次の列に移ります。\n"
               "その行の全ての成分を入力した後にエンターキーを打ち込むと次の列に移ります。\n"
               "一つの成分に入力できる整数の範囲は %d ~ %d です。\n\n", SEIBUNMIN, SEIBUNMAX);  //説明文表示
        
        for (int i = 0; i<grcnt; i++){  //行列の個数分回す
            while (((gcnt < gyocnt1) && ((mode[0] == '+') || (mode[0] == '-') || (mode[0] == 'd'))) || ((((gcnt < gyocnt1) && (i == 0)) || ((gcnt < gyocnt2) && (i == 1))) && (mode[0] == '*'))) {  //今入力している行の番号が行の最大値を下回っている間回す
                
                printf("行列%dの%d行目 |", i+1, gcnt+1);  //今入力している場所の出力
                
                while (((ch = getchar()) != '\n') || (firstf == 0)) {  //エンターキーが入力されるまで回す
                    
                    firstf = 1;  //エンター入力巻き込み防止用の変数の初期化
                    
                    
                    switch (ch) {
                            
                        case '-':
                            if (numf == 0){  //数字が入力されておらずーが入力された時
                                hikimode = 1;  //この成分に入力する値を負の整数に変換する
                            }
                            break;
                            
                        case ' ':
                            
                            if (numf == 1){  //数字が入力されていてなおかつスペースが入力された時
                                numf = 0;  //数字が入力されたという旗を下げる
                                hikimode = 0;  //負の値にする旗を下げる
                                switch (i){
                                    case 0:  //一回めの入力の時
                                        gyoretu1[gcnt][rcnt] = num;  //数値を一つめの行列の成分に代入
                                        break;
                                    case 1:  //二回めの入力の時
                                        gyoretu2[gcnt][rcnt] = num;  //数値を二つめの行列の成分に代入
                                        break;
                                }
                                rcnt++;  //次の列の入力に移る
                                num = 0;  //値の初期化
                            }
                            break;
                            
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':  //数字を入力した時
                            if (hikimode == 0){  //成分の最初にーが入力された時
                                ascii = ch - '0';  //文字を正の整数に変換
                            } else {
                                ascii = '0' - ch;  //文字を負の整数に変換
                            }
                            num = num * 10 + ascii;  //文字を負の整数に変換
                            numf = 1;  //数字が入力されたという旗を立てる
                            break;
                            
                    }
                
                    
                }
                firstf = 0;  //エンターキー巻き込み防止変数の初期化
                if ((((rcnt == retucnt1-1) && (i == 0)) || ((rcnt == retucnt2-1) && (i == 1))) && (numf == 1)){  //最後の列の入力の時
                    numf = 0;  //数字が入力されたという旗を下げる
                    hikimode = 0;  //負の値にする旗を下げる
                    switch (i){
                        case 0:  //一回めの入力の時
                            gyoretu1[gcnt][rcnt] = num;  //数値を一つめの成分に代入
                            break;
                        case 1:  //二回めの入力の時
                            gyoretu2[gcnt][rcnt] = num;  //数値を二つめの成分に代入
                            break;
                    }
                    rcnt++;  //最後の列の数値が入力された印
                    num = 0;  //値の初期化
                }
                
                
                if ((gyoretu1[gcnt][i] > SEIBUNMAX) && (i == 0) && (gyoretu1[gcnt][i] < SEIBUNMIN)) {  //一つめの成分が有効範囲外なら
                    rcnt = 0;  //列の数をリセット
                } else if ((gyoretu2[gcnt][i] > SEIBUNMAX) && (i == 1) && (gyoretu2[gcnt][i] > SEIBUNMIN)){  //二つめの成分が有効範囲外なら
                    rcnt = 0;  //列の数をリセット
                }
                
                
                if (((rcnt != retucnt1) && (i == 0)) || ((rcnt != retucnt2) && (i == 1))){  //列の入力の数が正しくないなら
                    rcnt = 0;  //列の数をリセット
                    num = 0;  //値の初期化
                    hikimode = 0;  //負の値にする旗を下げる
                    
                    continue;  //その列の入力をやり直す
                }
                
                rcnt = 0;  //列の数をリセット
                gcnt++;  //次の行の入力に移る
            }
            gcnt = 0;  //行の数をリセット
            num = 0;  //値の初期化
            putchar('\n');  //改行する
        }
       
//////計算部分//////
        if (mode[0] == '+' || mode[0] == '-'){  //最初に＋かーを入力した時
            for (int i = 0; i < ganscnt; i++) {  //行の回数分回す
                for (int j = 0; j < ranscnt; j++) {  //列の回数分回す
                    if (mode[0] == '+') {  //最初に＋を入力した時
                        gyoretuans[i][j] = gyoretu1[i][j] + gyoretu2[i][j];  //一つめと二つめの行列の成分を足す
                    } else if (mode[0] == '-') {  //最初にーを入力した時
                        gyoretuans[i][j] = gyoretu1[i][j] - gyoretu2[i][j];  //一つめの成分の値から二つめの成分の値を引く
                    }
                }
            }
        }
        
        if (mode[0] == '*'){  //最初に＊を入力した時
            for (int i = 0; i < ganscnt; i++){  //答えの行列の行の回数分回す
                for (int j = 0; j < ranscnt; j++){  //答えの行列の列の回数分回す
                    gyoretuans[i][j] = 0;  //成分の値を0にしておく
                    for (int k = 0; k < retucnt1; k++){  //一つめの行列の列の回数分回す
                        gyoretuans[i][j] += gyoretu1[i][k] * gyoretu2[k][j];  //計算部分
                    }
                }
            }
        }
        
        
        
//////成分の桁数の最大値を出す。/////
        if (mode[0] != 'd'){  //最初にd以外を入力した時
            for (int i = 0; i < ganscnt; i++) {  //行の回数分回す
            
                for (int j = 0; j < ranscnt; j++) {  //列の回数分回す
                    int keta = 0;  //桁数を表す変数の定義
                    seibun = gyoretuans[i][j];  //桁数を表す専用の変数に成分を代入
                    if (seibun < 0){  //成分が負の値なら
                        keta++;  //桁の値を一つ上げる
                    }
                    while (seibun != 0) {  //成分が0になるまで回す
                        seibun /= 10;  //成分から十割る
                        keta++;  //桁の値を一つ上げる
                    }
                    if (ketamax < keta) {  //もし現在の桁が最大値を超えていたら
                        ketamax = keta;  //桁の最大値を現在の値に設定
                    }
                }
            }
            
            if (ketamax == 0){  //もし桁の最大値が0なら
                ketamax = 1;  //桁の最大値を一にする
            }
        
        
            for (int i = 0; i < ganscnt; i++){  //行の数分回す
                putchar('|');  //行列を囲む囲いを表示
                for (int j = 0; j < ranscnt; j++) {  //列の数分回す
                    switch (ketamax) {  //桁の最大値に合わせて成分の出力をする
                        case 1:
                            printf("%2d", gyoretuans[i][j]);
                            break;
                        case 2:
                            printf("%3d", gyoretuans[i][j]);
                            break;
                        case 3:
                            printf("%4d", gyoretuans[i][j]);
                            break;
                        case 4:
                            printf("%5d", gyoretuans[i][j]);
                            break;
                        case 5:
                            printf("%6d", gyoretuans[i][j]);
                            break;
                        case 6:
                            printf("%7d", gyoretuans[i][j]);
                            break;
                        case 7:
                            printf("%8d", gyoretuans[i][j]);
                            break;
                        case 8:
                            printf("%9d", gyoretuans[i][j]);
                            break;
                        case 9:
                            printf("%10d", gyoretuans[i][j]);
                            break;
                    }
                }
                putchar('|');  //行列を囲む囲いを表示
                putchar('\n');  //最後の改行
            }
        }
        if (mode[0] == 'd'){
            printf("答えは %d\n", Detaminant(gyocnt1, retucnt1, deep, detaminantans, gyoretu1, gyoavoid, retuavoid));
            
        }
    }
    return 0;
}
