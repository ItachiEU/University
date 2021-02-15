import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class OknoGry implements ActionListener {

   public static final int width = 18;
   public static final int height = 12;
   private static final int refreshRate = 16;

   private JFrame frame;
   private Mikolaj mikolaj;
   private Canvas canvas;

   private OknoGry() {
      mikolaj = new Mikolaj(0, 0);

      frame = new JFrame("Mikołaj i dzieciaki");
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      frame.setLayout(new BorderLayout());

      canvas = new Canvas(width, height, mikolaj);
      frame.add(canvas, BorderLayout.CENTER);
      frame.pack();

      frame.setResizable(false);
      frame.setVisible(true);

      InputHandler handler = new InputHandler(canvas);
      canvas.setFocusable(true);
      canvas.addKeyListener(handler);

      new Timer(refreshRate, this).start();
   }

   @Override
   public void actionPerformed(ActionEvent e) {
      int disabledCount = 0;
      synchronized (canvas) {
         canvas.repaint();
         boolean end = true;
         for (Dzieciak dzieciak : canvas.dzieciaki) {
            if (!dzieciak.disabled) {
               end = false;
            } else
               disabledCount++;

            if (!dzieciak.isSleeping() && !dzieciak.disabled) {
               if (mikolaj.getY() + 1 == dzieciak.getY() && mikolaj.getX() == dzieciak.getX()
                     || mikolaj.getY() - 1 == dzieciak.getY() && mikolaj.getX() == dzieciak.getX()
                     || mikolaj.getY() == dzieciak.getY() && mikolaj.getX() + 1 == dzieciak.getX()
                     || mikolaj.getY() == dzieciak.getY() && mikolaj.getX() - 1 == dzieciak.getX()) {

                  end = true;
                  break;
               }
            }
         }
         if (end) {
            if (disabledCount == canvas.dzieciaki.size()) {
               JOptionPane.showMessageDialog(null, "YOU WIN!", "", 1);
            } else
               JOptionPane.showMessageDialog(null, "GAME OVER", "", 1);

            System.exit(0);
         }

      }
   }

   public static void main(String[] args) {
      new OknoGry();
   }

}