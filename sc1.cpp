//supercon 2022 yosen
using namespace std; 
#include<bits/stdc++.h>
#include "sc1.h"
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx")
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
const int INF = 1e9-1;
int get_u(int n){
    //上に進んだときのタイルの番号を取得、以下同様
    return (n+SC_L)%SC_N;
}
int get_d(int n){
    return (n-SC_L+SC_N)%SC_N;
}
int get_r(int n){
    if(n%SC_L == SC_L-1){
        return n-SC_L+1;
    }else{
        return n+1;
    }
}
int get_l(int n){
    if(n%SC_L == 0){
        return n+SC_L-1;
    }else{
        return n-1;
    }
}
int main(){
    //入力
    SC_input();

    //宣言と初期化
    //DP配列
    int dp[SC_Nt+1][SC_N];
    fill(dp[0],dp[SC_Nt+1],INF);
    //中央マス
    const int center = (SC_N-1)/2;

    //DP配列を埋める
    dp[0][center] = 0;
    for(int i=1;i<SC_Nt+1;i++){
        const int color = SC_Cr[i]; //時刻tに報告された色
        int tile_cost;
            rep(j,SC_N){
                //マス(タイル)の番号 = j
                const int tile = j;
                //そのマスである場合のコスト
                tile_cost = SC_distance(color-SC_C[tile]);
                //周囲のマスのコスト
                const int min_cost = min(min(dp[i-1][get_u(tile)],dp[i-1][get_d(tile)]),min(dp[i-1][get_r(tile)],dp[i-1][get_l(tile)]));
                dp[i][tile] = min_cost+tile_cost;
            }
    }

    //Ntステップ後にコストが最小の終着点を見つける
    int min_cost_end = INF;
    int end_point = -1;
    rep(i,SC_N){
        if(dp[SC_Nt][i]<min_cost_end){
            min_cost_end = dp[SC_Nt][i];
            end_point = i;
        }
    }

    //復元
    int point = end_point;
    int cost = min_cost_end;
    SC_ans[SC_Nt] = end_point;
    for(int i=SC_Nt-1;i>=0;i--){
        if(dp[i][get_u(point)]<=cost){
            cost = dp[i][get_u(point)];
            point = get_u(point);
        }else if(dp[i][get_d(point)]<=cost){
            cost = dp[i][get_d(point)];
            point = get_d(point);
        }else if(dp[i][get_l(point)]<=cost){
            cost = dp[i][get_l(point)];
            point = get_l(point);
        }else{
            cost = dp[i][get_r(point)];
            point = get_r(point);
        }
        SC_ans[i] = point;
    }

    SC_output();
    //終了
    return 0;
}