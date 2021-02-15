public class Mikolaj {
   private int x;
   private int y;

   public Mikolaj(int x, int y) {
      this.x = x;
      this.y = y;
   }

   void moveUp() {
      if (y - 1 < 0) {
         y = OknoGry.height - 1;
      } else {
         y--;
      }
   }

   void moveDown() {
      if (y + 1 >= OknoGry.height) {
         y = 0;
      } else {
         y++;
      }
   }

   void moveRight() {
      if (x + 1 >= OknoGry.width) {
         x = 0;
      } else {
         x++;
      }
   }

   void moveLeft() {
      if (x - 1 < 0) {
         x = OknoGry.width - 1;
      } else {
         x--;
      }
   }

   public int getX() {
      return x;
   }

   public int getY() {
      return y;
   }
}
