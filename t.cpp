#include <stdio.h>
#include <iostream>

struct LcsCell
{
  int score;
  int row;
  int col;
  // LcsCell *prev_cell;
};

int main()
{
  LcsCell **dp;

  std::string str_A = "abcde";
  std::string str_B = "abcdef";

  int y = str_A.length(); // y = 5
  int x = str_B.length(); // x = 6
  std::cout << "str length: (str_A, str_B) = (" << y << "," << x << ")\n";

  //二次元配列の要素確保
  int dpColMemSize = sizeof(LcsCell *) * (y + 1); // column line (y + 1)
  dp = (LcsCell **)malloc(dpColMemSize);

  int dpRowMemSize = sizeof(LcsCell) * (x + 1); // row line(x + 1)
  for (int _y = 0; _y < y + 1; _y++)
  {
    dp[_y] = (LcsCell *)malloc(dpRowMemSize);
  }

  //すべてのセルを初期化(3ステップ)
  // 1. dp[y][x].y = y (column index)
  // 2. dp[y][x].x = x (row index)
  // 3. dp[y][x].score = 0
  for (int _y = 0; _y < y + 1; _y++)
  {
    for (int _x = 0; _x < x + 1; _x++)
    {

      dp[_y][_x].col = _y;
      dp[_y][_x].row = _x;
      dp[_y][_x].score = 0;
    }
  }

  // 初期化結果確認（6列目の要素をprintする）
  for (int _y = 0; _y < y + 1; _y++)
  {
    for (int _x = 0; _x < x + 1; _x++)
    {
      /**
       * なぜか6列目の値がおかしい
       *
       * 0 0 ... 0
       * 0 0 ... 0
       * 0 0 ... 0
       * ~~
       * 0 0 ... 0
       *
       * となってほしいが、
       *
       * 0 0 ... 0
       * 0 0 ... 1
       * 0 0 ... 2
       * 0 0 ... 3
       * 0 0 ... 4
       * 0 0 ... 5
       *
       * となってしまう
       */

      std::cout << "(y,x,score) = (" << dp[_y][_x].col << "," << dp[_y][_x].row << "," << dp[_y][_x].score << ")\n\n";
    }
  }
}