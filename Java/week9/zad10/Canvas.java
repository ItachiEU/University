import javax.swing.JPanel;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.io.*;

public class Canvas extends JPanel {
   enum Img {
      GIFT(0), SANTA(1), KID_ACTIVE(2), KID_IDLE(3), KID_INACTIVE(4);

      private int value;

      public int getValue() {
         return this.value;
      }

      private Img(int value) {
         this.value = value;
      }
   }

   private static final int size = 64;
   private static final int santaSafeZone = 3;
   private static final int dzieciakiCount = 2;

   private int width;
   private int height;

   public Mikolaj mikolaj;

   public List<Dzieciak> dzieciaki;
   public List<Prezent> prezenty;
   private List<BufferedImage> images;

   public Canvas(int width, int height, Mikolaj mikolaj) {
      images = new ArrayList<>();
      this.dzieciaki = new ArrayList<>();
      this.prezenty = new ArrayList<>();
      try {
         images.add(ImageIO.read(Canvas.class.getResource("grafika/prezent.png")));
         images.add(ImageIO.read(Canvas.class.getResource("grafika/santa.png")));
         images.add(ImageIO.read(Canvas.class.getResource("grafika/kidActive.png")));
         images.add(ImageIO.read(Canvas.class.getResource("grafika/kidIdle.png")));
         images.add(ImageIO.read(Canvas.class.getResource("grafika/kidInactive.png")));
      } catch (IOException e) {

      }
      this.width = width;
      this.height = height;
      this.mikolaj = mikolaj;

      for (int i = 0; i < dzieciakiCount; i++) {
         int dzieciakX = (int) (Math.random() * (width - santaSafeZone)) + santaSafeZone;
         int dzieciakY = (int) (Math.random() * (height - santaSafeZone)) + santaSafeZone;
         dzieciaki.add(new Dzieciak(dzieciakX, dzieciakY, this));
      }

      for (Dzieciak dzieciak : dzieciaki)
         dzieciak.timer.start();

      setMinimumSize(new Dimension(width * size, height * size));
      setMaximumSize(new Dimension(width * size, height * size));
      setPreferredSize(new Dimension(width * size, height * size));
   }

   public void placeGift() {
      for (Dzieciak dzieciak : dzieciaki) {
         if (dzieciak.isSleeping()) {
            if (mikolaj.getY() + 1 == dzieciak.getY() && mikolaj.getX() == dzieciak.getX()
                  || mikolaj.getY() - 1 == dzieciak.getY() && mikolaj.getX() == dzieciak.getX()
                  || mikolaj.getY() == dzieciak.getY() && mikolaj.getX() + 1 == dzieciak.getX()
                  || mikolaj.getY() == dzieciak.getY() && mikolaj.getX() - 1 == dzieciak.getX()) {
               prezenty.add(new Prezent(mikolaj.getX(), mikolaj.getY()));
            }
         }
      }
   }

   @Override
   public void paintComponent(Graphics g) {
      super.paintComponent(g);

      g.setColor(Color.PINK.darker());
      g.fillRect(0, 0, width * size, height * size);

      g.setColor(Color.RED.darker());
      for (int x = 0; x < width; x++)
         for (int y = 0; y < height; y++)
            if (y % 2 != x % 2)
               g.fillRect(x * size, y * size, size, size);

      for (Prezent prezent : prezenty) {
         g.drawImage(images.get(Img.GIFT.getValue()), prezent.getX() * size, prezent.getY() * size, size, size, this);
      }

      for (Dzieciak dzieciak : dzieciaki) {
         if (dzieciak.disabled) {
            g.drawImage(images.get(Img.KID_INACTIVE.getValue()), dzieciak.getX() * size, dzieciak.getY() * size, size,
                  size, this);
         } else if (!dzieciak.isSleeping()) {
            g.drawImage(images.get(Img.KID_ACTIVE.getValue()), dzieciak.getX() * size, dzieciak.getY() * size, size,
                  size, this);
         } else {
            g.drawImage(images.get(Img.KID_IDLE.getValue()), dzieciak.getX() * size, dzieciak.getY() * size, size, size,
                  this);
         }

      }

      g.drawImage(images.get(Img.SANTA.getValue()), mikolaj.getX() * size, mikolaj.getY() * size, size, size, this);
   }
}
