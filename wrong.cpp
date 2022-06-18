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
  int _y, _x;
  for (_y = 0; _y <= y; _y++)
  {
    fillInCell(&dp[_y][0], 0, _y, 0, NULL);
  }

  // len = _x + 1 => _x <= xlen
  for (_x = 0; _x <= x; _x++)
  {
    fillInCell(&dp[0][_x], 0, 0, _x, NULL);
  }

  printDpTable(dp, y, x);
}

void printDpTable(LcsCell **dp, int y, int x)
{
  std::cout << "\n\n---dp table---\n";
  int i, j;
  for (i = 0; i <= y; i++)
  {
    for (j = 0; j <= x; j++)
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
  // cell->prev_cell = prev_cell;
  std::cout << "\n\n(y,x,score) = (" << cell->col << " , " << cell->row << " , " << cell->score << ")\n";
}

void fillInLcsTable(LcsCell **dp, std::string str_A, std::string str_B, int y, int x)
{
  // lcsアルゴリズム：str_A[i] == str_B[i] のとき、 dp[y-1][x-1] + 1する
  // std::cout << "\n\n";
  // std::cout << str_A << " , " << str_B << std::endl;
  // std::cout << str_A[0] << " , " << str_A[1] << std::endl;
  // std::cout << str_B[0] << " , " << str_B[1] << " , " << std::endl;
  int _y, _x;

  // 1列目・1行目以外について、LcsTableの値を埋める
  for (_y = 1; _y < y; _y++)
  {
    for (_x = 1; _x < x; _x++)
    {
      printDpTable(dp, y, x);
      int score_above_left = dp[_y - 1][_x - 1].score;
      int score_above = dp[_y - 1][_x].score;
      int score_left = dp[_y][_x - 1].score;

      std::cout << "\n\ntarget cells : (y,x) = (" << _y << "," << _x << "), val = " << dp[_y][_x].score << "\n";
      std::cout << "score_above_left : " << _y - 1 << "," << _x - 1 << " = " << score_above_left << "\n";
      std::cout << "score_above : " << _y - 1 << "," << _x << " = " << score_above << "\n";
      std::cout << "score_left : " << _y << "," << _x - 1 << " = " << score_left << "\n";

      if (str_A[_y - 1] == str_B[_x - 1])
      {
        std::cout << "----------matched---------------\n";
        // LCSテーブルの値を、左上のセルのスコア+1とする
        fillInCell(&dp[_y][_x], score_above_left + 1, _y, _x, &dp[_y - 1][_x - 1]);
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
  LcsCell **dp;
  int _y, _x;

  //入力文字列（デバッグのため固定文字列にする　 ）
  std::string str_A = "abcde";
  std::string str_B = "abcdef";
  // std::string str_A = "abcde";
  // std::string str_B = "abcdef";

  int y = str_A.length();
  int x = str_B.length();
  std::cout << "str length: (str_A, str_B) = (" << y << "," << x << ")\n";

  //二次元配列の要素確保
  int dpColMemSize = sizeof(LcsCell *) * (y + 1); // column line (y + 1)
  dp = (LcsCell **)malloc(dpColMemSize);

  int dpRowMemSize = sizeof(LcsCell *) * (x + 1); // row line(x + 1)
  for (_y = 0; _y < y + 1; _y++)
  {
    dp[_y] = (LcsCell *)malloc(dpRowMemSize);
  }

  //すべてのセルを初期化(3ステップ)
  // 1. dp[y][x].y = y (column index)
  // 2. dp[y][x].x = x (row index)
  // 3. dp[y][x].score = 0
  for (_y = 0; _y < y + 1; _y++)
  {
    for (_x = 0; _x < x + 1; _x++)
    {

      dp[_y][_x].col = _y;
      dp[_y][_x].row = _x;
      dp[_y][_x].score = 0;
      // std::cout << "(_y,_x) = (" << _y << "," << _x << ")\n";
      std::cout << "(y,x,score) = (" << dp[_y][_x].col << "," << dp[_y][_x].row << "," << dp[_y][_x].score << ")\n\n";
    }
  }

  for (_y = 0; _y < y + 1; _y++)
  {
    for (_x = 0; _x < x + 1; _x++)
    {

      std::cout << "(y,x,score) = (" << dp[_y][_x].col << "," << dp[_y][_x].row << "," << dp[_y][_x].score << ")\n";
    }
  }
  return 0;

  for (_y = 0; _y < y + 1; _y++)
  {
    for (_x = 0; _x < x + 1; _x++)
    {

      if (_x == x || 1)
      {
        std::cout << "(y,x,score) = (" << dp[_y][_x].col << "," << dp[_y][_x].row << "," << dp[_y][_x].score << ")\n\n";
      }
    }
  }

  // resetLcsTable(dp, y, x);

  //初期化の結果確認
  printDpTable(dp, y, x);
  // std::cout << "(y,x,score) = (" << dp[0][6].col << "," << dp[0][6].row << "," << dp[1][6].score << ")\n\n"; //???????

  // fillInLcsTable(dp, str_A, str_B, y, x);
  // printDpTable(dp, y, x);
}