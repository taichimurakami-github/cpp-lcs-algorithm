#include <stdio.h>
#include <iostream>

/**
 * @brief Structure of LcsCell
 * (row, col)
 *        col_1 col_2 col_3 .... col_n
 * row_1  (0,0) (0,1) (0,2) .... (0,n-1)
 * row_2  (1,0) ...
 * row_3  (2,0) ...
 * ...
 * row_n  (m-1,0) ...
 */
struct LcsCell
{
  int score;
  int row;
  int col;
  LcsCell *prevCell;
};

int getMaximumScore(int score1, int score2, int score3)
{
  int max = score1;
  if (max < score2)
  {
    max = score2;
  }
  if (max < score3)
  {
    max = score3;
  }
  // std::cout << "(s1,s2,s3,m) = (" << score1 << "," << score2 << "," << score3 << "," << max << ")\n";
  return max;
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
    }
    std::cout << "\n";
  }

  std::cout << "\n"
            << std::endl;
}

int main()
{

  std::string str_r = "abcdefgh";
  std::string str_c = "accccefh";

  int row = str_r.length();
  int col = str_c.length();

  int dpColLength = col + 1;
  int dpRowLength = row + 1;

  LcsCell dp[dpRowLength][dpColLength];

  // 初期化
  for (int r = 0; r < dpRowLength; r++)
  {
    for (int c = 0; c < dpColLength; c++)
    {
      dp[r][c].row = r;
      dp[r][c].col = c;
      dp[r][c].score = 0;
      // std::cout << "(y,x,score) = (" << dp[r][c].col << "," << dp[r][c].row << "," << dp[r][c].score << ")\n\n";
    }
  }

  /**
   * LCSアルゴリズム実装
   *
   * Table[i][j] =
   *     Table[i-1][j-1] + 1 if S1[i] == S2[j]
   *
   *   else
   *     Max(Table[i][j-1], Table[i-1][j])
   */
  char prevLcsChar;
  for (int r = 1; r < dpRowLength; r++)
  {

    for (int c = 1; c < dpColLength; c++)
    {
      char colChar = str_c[c - 1]; //横列の文字
      char rowChar = str_r[r - 1]; //縦列の文字

      // LcsCell cell = dp[r][c]; <- NG: cellはdp[r][c]とはメモリ上別物になるので，これをやるなら LcsCell* cell = &(dp[r][c]);であろう（実際，cellに代入してもdpには反映されない）
      // cell.col = c;
      // cell.row = r;

      LcsCell *cell = &(dp[r][c]);

      cell->col = c; // dp[r][c].col = c; でも可
      cell->row = r; // dp[r][c].row = r; でも可

      if (colChar == rowChar)
      {
        if (prevLcsChar != colChar)
        {
          std::cout << colChar;
          prevLcsChar = colChar;
        }

        cell->score = dp[r - 1][c - 1].score + 1;
        cell->prevCell = &dp[r - 1][c - 1];
      }
      else
      {
        LcsCell *aboveCell = &dp[r - 1][c];
        LcsCell *aboveLeftCell = &dp[r - 1][c - 1];
        LcsCell *leftCell = &dp[r][c - 1];

        /**
         * cellに対して左上，上，左で隣接しているcellのscoreを比較
         * prevCellを埋める & cell.scoreを決定する
         */
        if (aboveLeftCell->score >= aboveCell->score && aboveLeftCell->score >= leftCell->score)
        {
          //左上のセルのscoreが一番大きい
          cell->score = aboveLeftCell->score;
          cell->prevCell = aboveLeftCell;
        }
        else if (aboveCell->score >= leftCell->score)
        {
          //上のセルのscoreが一番大きい
          cell->score = aboveCell->score;
          cell->prevCell = aboveCell;
        }
        else
        {
          //左のセルのscoreが一番大きい
          cell->score = leftCell->score;
          cell->prevCell = leftCell;
        };
      }
    }
  }

  /**
   * dpテーブル出力
   */

  //１行目出力
  std::cout << "\n\n    ";
  for (int c = 0; c < dpColLength - 1; c++) // str_c.length() = dpColLength - 1
  {
    std::cout << str_c[c] << " "; // str_c[c]
  }
  std::cout << "\n ";

  //２行目以降出力
  for (int r = 0; r < dpRowLength; r++)
  {
    std::cout << str_r[r - 1] << " "; //１列目出力(str_r[r])

    for (int c = 0; c < dpColLength; c++)
    {
      std::cout << dp[r][c].score << " ";
    }
    std::cout << "\n"; //デバッグ用出力
  }

  /**
   * LCS文字列出力
   */
  int r = dpRowLength - 1;
  int c = dpColLength - 1;
  int cnt = 100;

  std::cout << "\n";

  // while (1)
  // {

  //   std::cout << str_r[r];

  //   r = dp[r][c].prevCell->row;
  //   c = dp[r][c].prevCell->col;
  //   cnt--;
  //   if (r == 0 || c == 0)
  //   {
  //     break;
  //   }
  // }

  // for (int r = dpRowLength - 1; r >= 0; r--)
  // {
  //   for (int c = dpColLength - 1; c >= 0; c--)
  //   {
  //     std::cout << dp[r][c].
  //   }
  // }

  // for (int r = 0; r < dpRowLength; r++)
  // {
  //   for (int c = 0; c < dpColLength; c++)
  //   {
  //     std::cout << "(y,x,score) = (" << dp[r][c].col << "," << dp[r][c].row << "," << dp[r][c].score << ")\n\n";
  //   }
  // }
}