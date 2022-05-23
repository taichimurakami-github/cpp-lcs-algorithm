#include "./main.h"

void input(std::string *str_A, std::string *str_B)
{
  std::cout << "input FIRST string" << std::endl;

  std::cin >> *str_A;

  std::cout << "input SECOND string" << std::endl;

  std::cin >> *str_B;

  // std::cout << "length of (str_A, str_B) = (" << str_A.length() << "," << str_B.length() << ")" << std::endl;
}

void resetLcsTable(LcsCell **dp, int y, int x)
{

  for (int _y = 0; _y <= y; _y++)
  {
    fillInCell(&dp[_y][0], 0, _y, 0, NULL);
  }

  // len = _x + 1 => _x <= xlen
  for (int _x = 0; _x <= x; _x++)
  {
    fillInCell(&dp[0][_x], 0, 0, _x, NULL);
  }
}

void printDpTable(LcsCell **dp, int y, int x)
{
  std::cout << "\n\n---dp table---\n";

  for (int i = 0; i <= y; i++)
  {
    for (int j = 0; j <= x; j++)
    {
      std::cout << dp[i][j].score << " ";
      // std::cout << "cell(y,x) = (" << i << "," << j << "):";
      // std::cout << "(col, row, score) = (" << dp[i][i].col << "," << dp[i][i].col << "," << dp[i][j].score << ")\n";
    }
    std::cout << "\n";
  }

  std::cout << "\n"
            << std::endl;
}

//指定された通りにLcsTableのセルを埋める
void fillInCell(LcsCell *cell, int score, int y, int x, LcsCell *prev_cell)
{
  cell->score = score;
  cell->row = x;
  cell->col = y;
  cell->prev_cell = prev_cell;
  std::cout << "\n\n(y,x,score) = (" << cell->col << " , " << cell->row << " , " << cell->score << ")\n";
}

void fillInLcsTable(LcsCell **dp, std::string str_A, std::string str_B, int y, int x)
{
  // lcsアルゴリズム：str_A[i] == str_B[i] のとき、 dp[y-1][x-1] + 1する
  // std::cout << "\n\n";
  // std::cout << str_A << " , " << str_B << std::endl;
  // std::cout << str_A[0] << " , " << str_A[1] << std::endl;
  // std::cout << str_B[0] << " , " << str_B[1] << " , " << std::endl;

  // 1列目・1行目以外について、LcsTableの値を埋める
  for (int _y = 1; _y < y; _y++)
  {
    for (int _x = 1; _x < x; _x++)
    {
      printDpTable(dp, y, x);
      int score_above_left = dp[_y - 1][_x - 1].score;
      int score_above = dp[_y - 1][_x].score;
      int score_left = dp[_y][_x - 1].score;

      std::cout << "\n\nscore_above_left : " << _y - 1 << "," << _x - 1 << " = " << score_above_left << "\n";
      std::cout << "score_above : " << _y - 1 << "," << _x << " = " << score_above << "\n";
      std::cout << "score_left : " << _y << "," << _x - 1 << " = " << score_left << "\n";

      if (str_A[_y] == str_B[_x])
      {
        // LCSテーブルの値を、左上のセルのスコア+1とする
        fillInCell(&dp[_y][_x], score_above_left, _y, _x, &dp[_y - 1][_x - 1]);
      }
      else
      {
        //等しい文字でなかった場合
        //左上、上、左のセルの中で最も大きな値を入れる
        if (score_above_left >= score_above)
        {
          //左上が最大
          fillInCell(&dp[_y][_x], score_above_left, _y, _x, &dp[_y - 1][_x - 1]);
        }
        else if (score_above >= score_left)
        {
          //上が最大
          fillInCell(&dp[_y][_x], score_above, _y, _x, &dp[_y - 1][_x]);
        }
        else
        {
          //左が最大
          fillInCell(&dp[_y][_x], score_left, _y, _x, &dp[_y][_x - 1]);
        }
      }
    }
  }
}

int main()
{
  std::string str_A = "abcde";
  std::string str_B = "abcdef";
  std::cout << "length of (str_A, str_B) = (" << str_A.length() << "," << str_B.length() << ")" << std::endl;

  // input(&str_A, &str_B);

  int y = str_A.length();
  int x = str_B.length();
  LcsCell **dp;

  //二次元配列の要素確保
  int dpColMemSize = sizeof(LcsCell *) * (y + 1);
  dp = (LcsCell **)malloc(dpColMemSize);

  int dpRowMemSize = sizeof(LcsCell *) * (x + 1);
  for (int _y = 0; _y < y + 1; _y++)
  {
    dp[_y] = (LcsCell *)malloc(dpRowMemSize);
  }

  std::cout << "str length: (str_A, str_B) = (" << y << "," << x << ")\n";

  resetLcsTable(dp, y, x);

  printDpTable(dp, y, x);

  fillInLcsTable(dp, str_A, str_B, y, x);

  printDpTable(dp, y, x);
}