import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class zad7 extends JFrame {
   public static void main(String[] args) {
      String plik = args[0];
      String obiekt = args[1];
      // System.out.println(obiekt);
      if (obiekt.equals("Prostokat")) {
         // System.out.println("halo");
         try {
            FileInputStream file = new FileInputStream(plik);
            ObjectInputStream in = new ObjectInputStream(file);
            @SuppressWarnings("unchecked")
            Prostokat prostokat = (Prostokat) in.readObject();
            in.close();
            file.close();
            System.out.println("Wczytano: \n");
            System.out.println(prostokat.toString());
            Prostokat doEdycji = new Prostokat(Double.toString(prostokat.a), Double.toString(prostokat.b),
                  prostokat.nazwa, prostokat.kolor);
         } catch (IOException exception) {
            System.out.println("Brak pliku o podanej nazwie, tworzę nowy: ");
            new Prostokat();
         } catch (ClassNotFoundException exception) {
            System.out.println("Something went wrong.");
         }
      } else if (obiekt.equals("Romb")) {
         // System.out.println("halo");
         try {
            FileInputStream file = new FileInputStream(plik);
            ObjectInputStream in = new ObjectInputStream(file);
            @SuppressWarnings("unchecked")
            Romb romb = (Romb) in.readObject();
            in.close();
            file.close();
            System.out.println("Wczytano: \n");
            System.out.println(romb.toString());
            Romb doEdycji = new Romb(Double.toString(romb.a), Double.toString(romb.b), romb.nazwa, romb.kolor);
         } catch (IOException exception) {
            System.out.println("Brak pliku o podanej nazwie, tworzę nowy: ");
            new Romb();
         } catch (ClassNotFoundException exception) {
            System.out.println("Something went wrong.");
         }
      } else {
         System.out.println("Nie ma aktualnie mozliwosc obsługi takiej figury.\n");
      }
   }
}

class Prostokat extends Figury {

   double a;
   double b;

   class ProstokatSwing extends JFrame implements ActionListener {
      Prostokat parent;

      JTextField name;
      JTextField color;
      JTextField a;
      JTextField b;

      public void actionPerformed(ActionEvent e) {
         double bok1 = Double.valueOf(a.getText());
         double bok2 = Double.valueOf(b.getText());

         parent.a = bok1;
         parent.b = bok2;
         parent.pole = bok1 * bok2;
         parent.nazwa = name.getText();
         parent.kolor = color.getText();
         System.out.println(parent.toString());
         try {
            FileOutputStream file = new FileOutputStream("prostokat.ser");
            ObjectOutputStream out = new ObjectOutputStream(file);
            out.writeObject(parent);
            out.close();
            file.close();
            System.out.println("Prostokat zostal zapisany do pliku prostokat.ser .");
         } catch (IOException exception) {
            System.out.println("Something went wrong.");
         }
      }

      public ProstokatSwing(Prostokat parent, String bok1, String bok2, String figura, String kolor) {
         this.parent = parent;
         this.a = new JTextField(bok1, 60);
         this.b = new JTextField(bok2, 60);
         this.name = new JTextField(figura, 60);
         this.color = new JTextField(kolor, 60);
         JFrame frame = new JFrame("Prostokat");
         frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         Container kontener = frame.getContentPane();
         GridLayout l = new GridLayout(5, 2);
         kontener.setLayout(l);

         JLabel l_a = new JLabel("Bok a");
         kontener.add(l_a);
         kontener.add(a);
         JLabel l_b = new JLabel("Bok b");
         kontener.add(l_b);
         kontener.add(b);
         JLabel l_name = new JLabel("Figura");
         kontener.add(l_name);
         kontener.add(name);
         JLabel l_color = new JLabel("Kolor");
         kontener.add(l_color);
         kontener.add(color);
         JButton b = new JButton("Zapisz objekt");
         b.addActionListener(this);
         kontener.add(b);
         frame.setSize(600, 400);
         frame.setVisible(true);
      }
   }

   public Prostokat() {
      new ProstokatSwing(this, "bok a", "bok b", "figura", "kolor");
   }

   public Prostokat(String bok1, String bok2, String figura, String kolor) {
      new ProstokatSwing(this, bok1, bok2, figura, kolor);
   }
}

class Romb extends Figury {

   double a;
   double b;

   class RombSwing extends JFrame implements ActionListener {
      Romb parent;

      JTextField name;
      JTextField color;
      JTextField a;
      JTextField b;

      public void actionPerformed(ActionEvent e) {
         double przekatna1 = Double.valueOf(a.getText());
         double przekatna2 = Double.valueOf(b.getText());

         parent.a = przekatna1;
         parent.b = przekatna2;
         parent.pole = przekatna1 * przekatna2 / 2;
         parent.nazwa = name.getText();
         parent.kolor = color.getText();
         System.out.println(parent.toString());
         try {
            FileOutputStream file = new FileOutputStream("romb.ser");
            ObjectOutputStream out = new ObjectOutputStream(file);
            out.writeObject(parent);
            out.close();
            file.close();
            System.out.println("Romb zostal zapisany do pliku romb.ser .");
         } catch (IOException exception) {
            System.out.println("Something went wrong.");
         }
      }

      public RombSwing(Romb parent, String przekatna1, String przekatna2, String figura, String kolor) {
         this.parent = parent;
         this.a = new JTextField(przekatna1, 60);
         this.b = new JTextField(przekatna2, 60);
         this.name = new JTextField(figura, 60);
         this.color = new JTextField(kolor, 60);
         JFrame frame = new JFrame("Romb");
         frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         Container kontener = frame.getContentPane();
         GridLayout l = new GridLayout(5, 2);
         kontener.setLayout(l);

         JLabel l_a = new JLabel("Przekatna a");
         kontener.add(l_a);
         kontener.add(a);
         JLabel l_b = new JLabel("Przekatna b");
         kontener.add(l_b);
         kontener.add(b);
         JLabel l_name = new JLabel("Figura");
         kontener.add(l_name);
         kontener.add(name);
         JLabel l_color = new JLabel("Kolor");
         kontener.add(l_color);
         kontener.add(color);
         JButton b = new JButton("Zapisz objekt");
         b.addActionListener(this);
         kontener.add(b);
         frame.setSize(600, 400);
         frame.setVisible(true);
      }
   }

   public Romb() {
      new RombSwing(this, "przekatna a", "przekatna b", "figura", "kolor");
   }

   public Romb(String przekatna1, String przekatna2, String figura, String kolor) {
      new RombSwing(this, przekatna1, przekatna2, figura, kolor);
   }
}

class Figury implements Serializable {
   Double pole;
   String kolor;
   String nazwa;

   public String toString() {
      return "Figura: " + this.nazwa + ", pole: " + Double.toString(this.pole) + ", kolor: " + this.kolor;
   }
}
