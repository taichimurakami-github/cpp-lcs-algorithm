#include <bits/stdc++.h>
using namespace std;

struct LcsCell
{
  int score;
  int row;
  int col;
  LcsCell *prev_cell;
};

// セルのメンバに値を代入する
void FillInCell(LcsCell *cell, int score, int i, int j, LcsCell *prev_cell)
{
  cell->score = score;
  cell->row = i;
  cell->col = j;
  cell->prev_cell = prev_cell;
}

// あるセルの左、上、左上にあるセルのスコアのうち最大値を返す
// 3つの値が同値の場合、返り値の優先度は左上>上>左とする
// また、最大値を持つセルのインデックスも求める
int CalcMaxAndPrevCell(int above_score, int left_score, int above_left_score,
                       int current_row, int current_col, int *prev_cell_row, int *prev_cell_col)
{
  int tmp_max;
  // 左上と上のセルを比較
  if (above_left_score >= above_score)
  {
    *prev_cell_row = current_row - 1;
    *prev_cell_col = current_col - 1;
    tmp_max = above_left_score;
  }
  else
  {
    *prev_cell_row = current_row - 1;
    *prev_cell_col = current_col;
    tmp_max = above_score;
  }

  // 左上と上のセルを比較したものと左のセルを比較
  if (tmp_max < left_score)
  {
    *prev_cell_row = current_row;
    *prev_cell_col = current_col - 1;
    tmp_max = left_score;
  }
  return tmp_max;
}

// LCSを求める関数
string FindLcs(LcsCell *cell, string x)
{
  LcsCell tmp = *cell;
  string lcs = "";

  printf("---trace route---\n");
  while (tmp.score)
  {
    if (tmp.score != tmp.prev_cell->score)
    {
      lcs.insert(lcs.begin(), x[(tmp.row) - 1]);
      printf("i: %d, j: %d\n", tmp.row, tmp.col);
    }
    tmp = *(tmp.prev_cell);
  }
  putchar('\n');

  return lcs;
}

int main(void)
{
  string x = "ABBCCD";
  string y = "ABCDEF";
  int m = x.length();
  int n = y.length();

  cout << "String1 : " << x << endl;
  cout << "string2 : " << y << endl;
  putchar('\n');

  int i, j;

  //文字列が短い場合は LcsCell dp[m+1][n+1]; でも可能
  LcsCell **dp;
  dp = (LcsCell **)malloc(sizeof(LcsCell *) * (m + 1));
  for (i = 0; i <= m; i++)
  {
    dp[i] = (LcsCell *)malloc(sizeof(LcsCell) * (n + 1));
  }

  // dpテーブルの初期化
  for (i = 0; i <= m; i++)
  {
    FillInCell(&dp[i][0], 0, i, 0, NULL);
  }
  for (j = 0; j <= n; j++)
  {
    FillInCell(&dp[0][j], 0, 0, j, NULL);
  }

  // dpループ
  int tmp_prev_row, tmp_prev_col;
  tmp_prev_row = tmp_prev_col = 0;
  int max_score;
  for (i = 1; i <= m; i++)
  {
    for (j = 1; j <= n; j++)
    {
      if (x[i - 1] == y[j - 1])
      {
        max_score = CalcMaxAndPrevCell(dp[i - 1][j].score, dp[i][j - 1].score, dp[i - 1][j - 1].score + 1, i, j, &tmp_prev_row, &tmp_prev_col);
      }
      else
      {
        max_score = CalcMaxAndPrevCell(dp[i - 1][j].score, dp[i][j - 1].score, dp[i - 1][j - 1].score, i, j, &tmp_prev_row, &tmp_prev_col);
      }
      FillInCell(&dp[i][j], max_score, i, j, &dp[tmp_prev_row][tmp_prev_col]);
    }
  }

  // dpテーブルの表示
  printf("---dp table---\n");
  for (i = 0; i <= m; i++)
  {
    for (j = 0; j <= n; j++)
    {
      printf("%d ", dp[i][j].score);
    }
    putchar('\n');
  }
  putchar('\n');

  // LCSの表示
  string str = FindLcs(&dp[m][n], x);
  cout << "LCS : " << str << endl;
  return 0;
}