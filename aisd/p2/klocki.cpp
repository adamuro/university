#include <iostream>

using namespace std;


int main() {
  int dp[2][1000001] = { 0 };
  int n;
  int min_dif = 1000000;
  int max_dif = 1;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int h;
    int imod = i % 2;
    max_dif += h;
    scanf("%d", &h);
    for (int j = 0; j < max_dif; j++) {
      if (dp[!imod][j] != 0 || j == 0) {
        int add_dif = j + h;
        int sub_dif = abs(j - h);
        dp[imod][add_dif] = max(dp[imod][add_dif], max(dp[!imod][add_dif], dp[!imod][j] + h));
        dp[imod][sub_dif] = max(dp[imod][sub_dif], max(dp[!imod][sub_dif], dp[!imod][j] + h));
        dp[imod][j] = max(dp[imod][j], dp[!imod][j]);
        if (i > 1)
          min_dif = min(min_dif, min(add_dif, sub_dif));
      }
    }
    dp[imod][h] = max(h, dp[imod][h]);
    // printf("%d\n", h);
    // for (int j = 0; j < 1000; j++) {
    //   if (dp[i % 2][j] != 0) {
    //     printf("%d: %d ", j, dp[i % 2][j]);
    //   }
    // }
    // printf("\n");
  }

  if (dp[n % 2][0] > 0) {
    printf("TAK\n");
    printf("%d\n", dp[n % 2][0] / 2);
  }
  else {
    printf("NIE\n");
    printf("%d\n", min_dif);
  }
  return 0;
}