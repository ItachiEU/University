import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Dzieciak implements ActionListener {

   public Timer timer;
   public Boolean disabled;

   private int x;
   private int y;

   private int steps;
   private int maxSteps;
   private int timeAsleep;
   private int maxSleep;

   private static final int speed = 1;
   private static final int range = 5;

   public Canvas canvas;

   public Dzieciak(int x, int y, Canvas canvas) {
      disabled = false;
      this.x = x;
      this.y = y;
      this.canvas = canvas;

      steps = 0;
      maxSteps = (int) (Math.random() * 4) + 1;
      timeAsleep = 0;
      maxSleep = (int) (Math.random() * 4) + 1;

      timer = new Timer(1000 / speed, this);
   }

   public int getX() {
      return x;
   }

   public int getY() {
      return y;
   }

   public boolean isSleeping() {
      return steps >= maxSteps;
   }

   private boolean isSantaVisible() {
      return canvas.mikolaj.getX() <= x + range && canvas.mikolaj.getX() >= x - range
            && canvas.mikolaj.getY() <= y + range && canvas.mikolaj.getY() >= y - range;
   }

   private void moveUp() {
      if (y - 1 < 0) {
         y = OknoGry.height - 1;
      } else {
         y--;
      }
   }

   private void moveDown() {
      if (y + 1 >= OknoGry.height) {
         y = 0;
      } else {
         y++;
      }
   }

   private void moveRight() {
      if (x + 1 >= OknoGry.width) {
         x = 0;
      } else {
         x++;
      }
   }

   private void moveLeft() {
      if (x - 1 < 0) {
         x = OknoGry.width - 1;
      } else {
         x--;
      }
   }

   @Override
   public void actionPerformed(ActionEvent e) {
      synchronized (canvas) {
         if (isSleeping()) {
            timeAsleep++;

            if (timeAsleep >= maxSleep) {
               steps = 0;
               timeAsleep = 0;
               maxSteps = (int) (Math.random() * 4) + 3;
               maxSleep = (int) (Math.random() * 3) + 2;

               for (int i = 0; i < canvas.prezenty.size(); i++) {
                  Prezent prezent = canvas.prezenty.get(i);
                  if (prezent.getY() + 1 == y && prezent.getX() == x || prezent.getY() - 1 == y && prezent.getX() == x
                        || prezent.getY() == y && prezent.getX() + 1 == x
                        || prezent.getY() == y && prezent.getX() - 1 == x) {

                     x = prezent.getX();
                     y = prezent.getY();

                     canvas.prezenty.remove(i);
                     disabled = true;
                     timer.stop();
                  }
               }
            }

            return;
         }

         steps++;
         if (isSantaVisible()) {
            if (Math.abs(canvas.mikolaj.getX() - x) > Math.abs(canvas.mikolaj.getY() - y)) {
               if (canvas.mikolaj.getX() > x) {
                  moveRight();
               } else {
                  moveLeft();
               }
            } else {
               if (canvas.mikolaj.getY() > y) {
                  moveDown();
               } else {
                  moveUp();
               }
            }
         } else {
            int direction = (int) (Math.random() * 4);
            switch (direction) {
               case 0: // UP
                  if (y > 0)
                     moveUp();
                  break;
               case 1: // DOWN
                  if (y < OknoGry.height)
                     moveDown();
                  break;
               case 2: // LEFT
                  if (x > 0)
                     moveLeft();
                  break;
               case 3: // RIGHT
                  if (x < OknoGry.width)
                     moveRight();
                  break;
            }
         }
      }
   }
}
