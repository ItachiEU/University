import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class InputHandler extends KeyAdapter {
   private Canvas canvas;

   public InputHandler(Canvas canvas) {
      this.canvas = canvas;
   }

   @Override
   public void keyPressed(KeyEvent e) {
      int keyCode = e.getKeyCode();
      switch (keyCode) {
         case 39:
            canvas.mikolaj.moveRight();
            break;
         case 37:
            canvas.mikolaj.moveLeft();
            break;
         case 32:
            canvas.placeGift();
            break;
         case 38:
            canvas.mikolaj.moveUp();
            break;
         case 40:
            canvas.mikolaj.moveDown();
            break;
      }
   }
}
