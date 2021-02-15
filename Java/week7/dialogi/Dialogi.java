package dialogi;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

class Okno extends JFrame {
   private JPanel panel = new JPanel(new GridLayout(4, 3));
   private JLabel instr_Lab = new JLabel("Zapoznaj siÄ z instrukcjÄ:");
   private JButton instr_But = new JButton("instrukcja");
   private JTextField instr_T = new JTextField();
   private JLabel imie_Lab = new JLabel("ImiÄ i nazwisko:");
   private JButton imie_But = new JButton("podaj imiÄ i nazwisko");
   private JTextField imie_T = new JTextField();
   private JLabel czy_Lab = new JLabel("GĹos w sprawie ustawy:");
   private JButton czy_But = new JButton("gĹosowanie");
   private JTextField czy_T = new JTextField();
   private JLabel wyb_Lab = new JLabel("Wybierz kraj:");
   private JButton wyb_But = new JButton("pochodzenie");
   private JTextField wyb_T = new JTextField();

   private ActionListener zdInstr = new ActionListener() {
      public void actionPerformed(ActionEvent ev) {
         JOptionPane.showMessageDialog(Okno.this, "Nie wyĹÄczaj tej aplikacji" + "!", "instrukcja",
               JOptionPane.INFORMATION_MESSAGE);
         instr_T.setText("zapoznaĹ(a) siÄ z instrukcjÄ");
      }
   };
   private ActionListener zdImie = new ActionListener() {
      public void actionPerformed(ActionEvent ev) {
         String im = null;
         do
            im = JOptionPane.showInputDialog(Okno.this, "Podaj swoje imiÄ i nazwisko:", "imiÄ i nazwisko",
                  JOptionPane.PLAIN_MESSAGE);
         while (im == null);
         imie_T.setText(im);
      }
   };
   private ActionListener zdCzy = new ActionListener() {
      public void actionPerformed(ActionEvent ev) {
         int odp = JOptionPane.showConfirmDialog(Okno.this, "Czy jesteĹ za przyjÄciem ustawy?",
               "gĹosowanie nad ustawÄ", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE);
         switch (odp) {
            case 0:
               czy_T.setText("za");
               break;
            case 1:
               czy_T.setText("przeciw");
               break;
            default:
               czy_T.setText("wstrzymaĹ(a) siÄ od gĹosu");
         }
      }
   };
   private ActionListener zdWyb = new ActionListener() {
      public void actionPerformed(ActionEvent ev) {
         String[] mozliwosci = { "Polska", "Niemcy", "Czechy", "SĹowacja", "Ukraina", "BiaĹoruĹ", "Rosja", "Litwa" };
         String wybor = (String) JOptionPane.showInputDialog(Okno.this, "Wybierz kraj pochodzenia:", "wybĂłr kraju",
               JOptionPane.WARNING_MESSAGE, null, mozliwosci, mozliwosci[0]);
         wyb_T.setText(wybor);
      }
   };

   {
      instr_T.setEditable(false);
      panel.add(instr_Lab);
      panel.add(instr_But);
      panel.add(instr_T);
      instr_But.addActionListener(zdInstr);
      imie_T.setEditable(false);
      panel.add(imie_Lab);
      panel.add(imie_But);
      panel.add(imie_T);
      imie_But.addActionListener(zdImie);
      czy_T.setEditable(false);
      panel.add(czy_Lab);
      panel.add(czy_But);
      panel.add(czy_T);
      czy_But.addActionListener(zdCzy);
      wyb_T.setEditable(false);
      panel.add(wyb_Lab);
      panel.add(wyb_But);
      panel.add(wyb_T);
      wyb_But.addActionListener(zdWyb);
   }

   public Okno() {
      super("dialog z uĹźytkownikiem");
      setSize(640, 160);
      setLocation(80, 80);
      setResizable(false);
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      add(panel);
      setVisible(true);
   }
}

public class Dialogi {
   public static void main(String[] args) {
      new Okno();
   }
}