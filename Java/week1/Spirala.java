class Spirala {
   public static void main(String[] args) {
      int n = Integer.valueOf(args[0]);
      if (n < 2 || n > 200) {
         throw new IllegalArgumentException("parametr spoza zakresu 2...200");
      }
      int[][] arr = new int[n][n];
      int start_x = (n - 1) / 2, start_y = n / 2, to_fill = n * n, i = 1;
      arr[start_y][start_x] = i++;
      start_x++;
      String direction = "right";
      while (i <= to_fill) {
         arr[start_y][start_x] = i;

         switch (direction) {
            case "right":
               if (arr[start_y - 1][start_x] == 0) {
                  direction = "up";
                  start_y--;
               } else {
                  start_x++;
               }
               break;
            case "up":
               if (arr[start_y][start_x - 1] == 0) {
                  direction = "left";
                  start_x--;
               } else {
                  start_y--;
               }
               break;
            case "left":
               if (arr[start_y + 1][start_x] == 0) {
                  direction = "down";
                  start_y++;
               } else {
                  start_x--;
               }
               break;
            case "down":
               if (arr[start_y][start_x + 1] == 0) {
                  direction = "right";
                  start_x++;
               } else {
                  start_y++;
               }
               break;
         }
         i++;
      }
      for (int k = 0; k < n; k++) {
         for (int j = 0; j < n; j++) {
            if (!checkPrime(arr[k][j]) || arr[k][j] == 1)
               arr[k][j] = 0;
         }
      }
      for (int k = 0; k < n; k++) {
         for (int j = 0; j < n; j++) {
            if (arr[k][j] == 0)
               System.out.print(' ');
            else
               System.out.print('*');
         }
         System.out.print('\n');
      }
   }

   public static boolean checkPrime(int a) {
      for (int i = 2; i * i <= a; i++)
         if (a % i == 0)
            return false;
      return true;
   }
}