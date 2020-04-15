import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public abstract class Figury implements Comparable<Figury> {
   public static void main(String[] args) {
      List<Figury> figury = new ArrayList<Figury>();
      figury.add(new Kwadrat(6.0));
      figury.add(new Prostokat(3.0, 5.0));
      figury.add(new Kolo(5.0));
      figury.add(new Trojkat(3.0, 4.0, 5.0));
      Collections.sort(figury);
      // for (Figury figura : figury) {
      // System.out.println(figura);
      // }
      try {
         FileOutputStream fos = new FileOutputStream("figury.txt");
         ObjectOutputStream oos = new ObjectOutputStream(fos);
         oos.writeObject(figury);
         oos.flush();
         oos.close();
      } catch (IOException ioe) {
         ioe.printStackTrace();
      }
      odzyskanie();
   }

   public abstract double pole();

   @Override
   public int compareTo(Figury o) {
      return (int) Math.signum(pole() - o.pole());
   }

   public static void odzyskanie() {
      FileInputStream fis = null;
      ObjectInputStream ois = null;
      List<Figury> figury = null;
      try {
         fis = new FileInputStream("figury.txt");
         ois = new ObjectInputStream(fis);
         figury = (List<Figury>) ois.readObject();
      } catch (FileNotFoundException err) {
         err.printStackTrace();
      } catch (IOException err) {
         err.printStackTrace();
      } catch (ClassNotFoundException err) {
         err.printStackTrace();
      }

      for (Figury figura : figury) {
         System.out.println(figura);
      }
   }
}