import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class Samotnik extends javax.swing.JFrame implements MouseListener, MouseMotionListener {
   public Integer[][] brytyjskaPlansza = new Integer[][] { { 0, 0, 1, 1, 1, 0, 0 }, { 0, 0, 1, 1, 1, 0, 0 },
         { 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, -1, 1, 1, 1 }, { 1, 1, 1, 1, 1, 1, 1 }, { 0, 0, 1, 1, 1, 0, 0 },
         { 0, 0, 1, 1, 1, 0, 0 } };
   public Integer[][] europejskaPlansza = new Integer[][] { { 0, 0, 1, 1, 1, 0, 0 }, { 0, 1, 1, 1, 1, 1, 0 },
         { 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, -1, 1, 1, 1 }, { 1, 1, 1, 1, 1, 1, 1 }, { 0, 1, 1, 1, 1, 1, 0 },
         { 0, 0, 1, 1, 1, 0, 0 } };
   javax.swing.JPanel squares[][] = new javax.swing.JPanel[7][7];

   // Variables declaration - do not modify
   private JMenu graMenu;
   private JMenu ruchyMenu;
   private JMenu ustawieniaMenu;
   private JMenu pomocMenu;
   private JMenuBar jMenuBar1;
   private JMenuItem jMenuItem1;
   private JMenuItem jMenuItem2;
   private JMenuItem jMenuItem3;
   private JMenuItem jMenuItem4;
   private JRadioButtonMenuItem brytyjskaButton;
   private JRadioButtonMenuItem europejskaButton;
   private JMenu kolorTla;
   private JRadioButtonMenuItem kolorNiebieski;
   private JRadioButtonMenuItem kolorCzarny;
   private JPopupMenu.Separator jSeparator1;
   public JPanel mapaPanel;
   public JPanel[] selectedMoves;
   private JPanel selectedPanel;
   private Color backgroundColor;
   int pieces;
   int gameType;

   int xAdjustment;
   int yAdjustment;

   int pionekPickX;
   int pionekPickY;

   int pionekDropX;
   int pionekDropY;

   JLabel pionek;

   // End of variables declaration
   public Samotnik(int gameType, Color background) {
      this.gameType = gameType;
      backgroundColor = background;
      pionekPickX = -1;
      pionekPickY = -1;
      initComponents();

      if (gameType == 0) {
         brytyjskaButton.setSelected(false);
         europejskaButton.setSelected(true);
      }
      if (gameType == 1) {
         brytyjskaButton.setSelected(true);
         europejskaButton.setSelected(false);
      }

      // Set up the map
      mapaPanel.setLayout(new java.awt.GridLayout(7, 7));
      java.awt.Dimension boardSize = new java.awt.Dimension(1200, 1200);
      mapaPanel.setPreferredSize(boardSize);
      mapaPanel.setBounds(0, 0, boardSize.width, boardSize.height);
      mapaPanel.setBorder(new javax.swing.border.CompoundBorder(new javax.swing.border.EmptyBorder(7, 7, 7, 7),
            new javax.swing.border.LineBorder(java.awt.Color.BLACK)));
      javax.swing.ImageIcon imageIcon = new javax.swing.ImageIcon(
            "/home/itachi/NetBeansProjects/Samotnik/src/main/java/sfera.png"); // load the image to a imageIcon
      java.awt.Image image = imageIcon.getImage(); // transform it
      java.awt.Image newimg = image.getScaledInstance(120, 120, java.awt.Image.SCALE_SMOOTH); // scale it the smooth
                                                                                              // waycle
      imageIcon = new javax.swing.ImageIcon(newimg);

      for (int i = 0; i < 7; i++)
         for (int j = 0; j < 7; j++) {
            squares[i][j] = new javax.swing.JPanel();
            mapaPanel.add(squares[i][j]);
            squares[i][j].setBorder(new javax.swing.border.LineBorder(java.awt.Color.WHITE));
            squares[i][j].setBackground(backgroundColor);
            if (gameType == 0) {
               if (europejskaPlansza[i][j] == 1)
                  squares[i][j].add(new javax.swing.JLabel(imageIcon));
               if (europejskaPlansza[i][j] == 0)
                  squares[i][j].setBackground(Color.WHITE);
            }
            if (gameType == 1) {
               if (brytyjskaPlansza[i][j] == 1)
                  squares[i][j].add(new javax.swing.JLabel(imageIcon));
               if (brytyjskaPlansza[i][j] == 0)
                  squares[i][j].setBackground(Color.WHITE);
            }
         }
      mapaPanel.addMouseListener(this);
      mapaPanel.addMouseMotionListener(this);
   }

   public void mousePressed(MouseEvent e) {
      if (SwingUtilities.isLeftMouseButton(e)) {
         if (selectedMoves != null)
            for (int i = 0; i < 4; i++)
               if (selectedMoves[i] != null)
                  selectedMoves[i].setBorder(new javax.swing.border.LineBorder(Color.white));

         Component t = mapaPanel.findComponentAt(e.getX(), e.getY());
         if (t instanceof JLabel) {
            if (selectedPanel != null)
               selectedPanel.setBorder(new javax.swing.border.LineBorder(Color.WHITE));

            pionekPickX = t.getParent().getLocation().x;
            pionekPickY = t.getParent().getLocation().y;
            pionek = (JLabel) t;
            selectedPanel = (JPanel) t.getParent();
            selectedPanel.setBorder(new javax.swing.border.LineBorder(Color.RED));
         } else {
            Component comp = mapaPanel.findComponentAt(e.getX(), e.getY());
            if (comp.getBackground() == Color.white)
               return;
            pionekDropX = comp.getLocation().x;
            pionekDropY = comp.getLocation().y;

            if (Math.abs(pionekDropX - pionekPickX) + Math.abs(pionekPickY - pionekDropY) > 270
                  || (Math.abs(pionekDropX - pionekPickX) * Math.abs(pionekPickY - pionekDropY) != 0))
               return;

            if (pionekDropX - pionekPickX < -200) {
               Component c = mapaPanel.findComponentAt(pionekPickX - 100, pionekPickY + 10);
               if (c instanceof JLabel) {
                  c.setVisible(false);
                  // c.setVisible(false);
               } else
                  return;
            } else if (pionekDropX - pionekPickX > 200) {
               Component c = mapaPanel.findComponentAt(pionekPickX + 140, pionekPickY + 10);
               if (c instanceof JLabel) {
                  c.setVisible(false);
               } else
                  return;
            } else if (pionekDropY - pionekPickY < -200) {
               Component c = mapaPanel.findComponentAt(pionekPickX + 10, pionekPickY - 100);
               if (c instanceof JLabel) {
                  c.setVisible(false);
               } else
                  return;
            } else if (pionekDropY - pionekPickY > 200) {
               Component c = mapaPanel.findComponentAt(pionekPickX + 10, pionekPickY + 140);
               if (c instanceof JLabel) {
                  c.setVisible(false);
               } else
                  return;
            } else {
               return;
            }

            pionek.setVisible(false);

            Component c = mapaPanel.findComponentAt(e.getX(), e.getY());

            Container parent = (Container) c;
            parent.add(pionek);
            selectedPanel.setBorder(new javax.swing.border.LineBorder(Color.white));
            pionek.setVisible(true);

            // Do something
            if (checkEnd()) {
               JOptionPane.showMessageDialog(Samotnik.this, "Koniec gry", "Game Over", JOptionPane.INFORMATION_MESSAGE);
            }
            if (selectedMoves != null)
               for (int i = 0; i < 4; i++)
                  if (selectedMoves[i] != null)
                     selectedMoves[i].setBorder(new javax.swing.border.LineBorder(Color.white));
         }
      } else if (SwingUtilities.isRightMouseButton(e)) {
         if (selectedMoves != null)
            for (int i = 0; i < 4; i++)
               if (selectedMoves[i] != null)
                  selectedMoves[i].setBorder(new javax.swing.border.LineBorder(Color.white));
         Component t = mapaPanel.findComponentAt(e.getX(), e.getY());
         int x = t.getParent().getLocation().x;
         int y = t.getParent().getLocation().y;
         int temp = showMoves(x, y);
      }
   }

   int showMoves(int posX, int posY) {
      Component t = mapaPanel.findComponentAt(posX + 10, posY + 10);
      int result = 0;
      selectedMoves = new JPanel[4];
      if (t instanceof JLabel) {
         int[] dirsX = { -266, 266, 0, 0 };
         int[] dirsY = { 0, 0, 266, -266 };
         for (int i = 0; i < 4; i++) {
            int newX = posX + dirsX[i];
            int newY = posY + dirsY[i];
            if (newX < 0 || newY < 0 || newX >= 950 || newY >= 950)
               continue;

            Component comp = mapaPanel.findComponentAt(newX, newY);
            if (comp.getBackground() == Color.white || comp.getSize().getWidth() > 133)
               continue;
            Component test = mapaPanel.findComponentAt(newX + 10, newY + 10);
            if (test instanceof JLabel)
               continue;
            if (newX - posX < -200) {
               Component c = mapaPanel.findComponentAt(posX - 100, posY + 10);
               if (c instanceof JLabel) {
                  JPanel temp = (JPanel) comp;
                  temp.setBorder(new javax.swing.border.LineBorder(Color.green));
                  selectedMoves[i] = temp;
                  result++;
               } else
                  continue;
            } else if (newX - posX > 200) {
               Component c = mapaPanel.findComponentAt(posX + 140, posY + 10);
               if (c instanceof JLabel) {
                  JPanel temp = (JPanel) comp;
                  temp.setBorder(new javax.swing.border.LineBorder(Color.green));
                  selectedMoves[i] = temp;
                  result++;
               } else
                  continue;
            } else if (newY - posY < -200) {
               Component c = mapaPanel.findComponentAt(posX + 10, posY - 100);
               if (c instanceof JLabel) {
                  JPanel temp = (JPanel) comp;
                  temp.setBorder(new javax.swing.border.LineBorder(Color.green));
                  selectedMoves[i] = temp;
                  result++;
               } else
                  continue;
            } else if (newY - posY > 200) {
               Component c = mapaPanel.findComponentAt(posX + 10, posY + 140);
               if (c instanceof JLabel) {
                  JPanel temp = (JPanel) comp;
                  temp.setBorder(new javax.swing.border.LineBorder(Color.green));
                  selectedMoves[i] = temp;
                  result++;
               } else
                  continue;
            }
         }
      }
      return result;
   }

   boolean checkEnd() {
      for (int i = 0; i < 7; i++) {
         for (int j = 0; j < 7; j++) {
            int t = showMoves(9 + j * 133, 9 + i * 133);
            if (t > 0)
               return false;
            if (selectedMoves != null)
               for (int x = 0; x < 4; x++)
                  if (selectedMoves[x] != null)
                     selectedMoves[x].setBorder(new javax.swing.border.LineBorder(Color.white));
         }
      }
      return true;
   }

   public void mouseDragged(MouseEvent me) {
   }

   public void mouseReleased(MouseEvent e) {

   }

   public void mouseClicked(MouseEvent e) {

   }

   public void mouseMoved(MouseEvent e) {
   }

   public void mouseEntered(MouseEvent e) {

   }

   public void mouseExited(MouseEvent e) {

   }

   private void initComponents() {

      mapaPanel = new javax.swing.JPanel();
      java.awt.Dimension boardSize = new java.awt.Dimension(1200, 1200);
      mapaPanel.setPreferredSize(boardSize);
      mapaPanel.setBounds(0, 0, boardSize.width, boardSize.height);
      jMenuBar1 = new javax.swing.JMenuBar();
      graMenu = new javax.swing.JMenu();
      jMenuItem2 = new javax.swing.JMenuItem();
      jSeparator1 = new javax.swing.JPopupMenu.Separator();
      jMenuItem3 = new javax.swing.JMenuItem();
      ustawieniaMenu = new javax.swing.JMenu();
      brytyjskaButton = new javax.swing.JRadioButtonMenuItem();
      europejskaButton = new javax.swing.JRadioButtonMenuItem();
      pomocMenu = new javax.swing.JMenu();
      jMenuItem1 = new javax.swing.JMenuItem();
      jMenuItem4 = new javax.swing.JMenuItem();
      ruchyMenu = new javax.swing.JMenu();
      kolorTla = new JMenu();
      kolorNiebieski = new JRadioButtonMenuItem();
      kolorCzarny = new JRadioButtonMenuItem();

      setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
      setTitle("Samotnik");

      mapaPanel.setMinimumSize(new java.awt.Dimension(900, 900));
      mapaPanel.setLayout(new java.awt.GridLayout());

      graMenu.setText("Gra");

      jMenuItem2.setText("Nowa");
      jMenuItem2.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
            if (kolorCzarny.isSelected())
               backgroundColor = Color.BLACK;
            else if (kolorNiebieski.isSelected())
               backgroundColor = Color.BLUE;
            Samotnik nowyFrame = new Samotnik(gameType, backgroundColor);
            nowyFrame.setVisible(true);
            dispose();
         }
      });
      graMenu.add(jMenuItem2);
      graMenu.add(jSeparator1);

      KeyStroke keyStrokeToOpen = KeyStroke.getKeyStroke(KeyEvent.VK_N, KeyEvent.CTRL_DOWN_MASK);
      jMenuItem2.setAccelerator(keyStrokeToOpen);

      KeyStroke keyStrokeToClose = KeyStroke.getKeyStroke(KeyEvent.VK_E, KeyEvent.CTRL_DOWN_MASK);
      jMenuItem3.setAccelerator(keyStrokeToClose);

      jMenuItem3.setText("Koniec");
      jMenuItem3.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
            dispose();
         }
      });
      graMenu.add(jMenuItem3);

      jMenuBar1.add(graMenu);

      ustawieniaMenu.setText("Ustawienia");

      // private JMenu kolorTla;
      kolorNiebieski.setText("niebieski");
      kolorNiebieski.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
            backgroundColor = Color.BLUE;
            kolorCzarny.setSelected(false);
         }

      });
      kolorCzarny.setText("czarny");
      kolorCzarny.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
            backgroundColor = Color.BLACK;
            kolorNiebieski.setSelected(false);
         }

      });

      brytyjskaButton.setSelected(true);
      brytyjskaButton.setText("Brytyjska");
      brytyjskaButton.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
            gameType = 1;
            europejskaButton.setSelected(false);
         }
      });
      ustawieniaMenu.add(brytyjskaButton);
      kolorTla.setText("Kolor tla");
      kolorTla.add(kolorNiebieski);
      kolorTla.add(kolorCzarny);
      ustawieniaMenu.add(kolorTla);

      europejskaButton.setText("Europejska");
      europejskaButton.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
            gameType = 0;
            brytyjskaButton.setSelected(false);
         }

      });
      ustawieniaMenu.add(europejskaButton);

      jMenuBar1.add(ustawieniaMenu);

      ruchyMenu.setText("Ruchy");
      jMenuBar1.add(ruchyMenu);

      setJMenuBar(jMenuBar1);

      pomocMenu.setText("Pomoc");

      jMenuItem1.setText("O grze");
      jMenuItem1.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent ev) {
            JOptionPane.showMessageDialog(Samotnik.this,
                  "Odwiedź tę stronę: https://en.wikipedia.org/wiki/Peg_solitaire", "Zasady",
                  JOptionPane.INFORMATION_MESSAGE);
         }
      });
      pomocMenu.add(jMenuItem1);

      jMenuItem4.setText("O aplikacji");
      jMenuItem4.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent ev) {
            JOptionPane.showMessageDialog(Samotnik.this, "Autorem tej aplikacji jest Filip Komorowski", "info",
                  JOptionPane.INFORMATION_MESSAGE);
         }
      });
      pomocMenu.add(jMenuItem4);

      jMenuBar1.add(Box.createHorizontalGlue());
      jMenuBar1.add(pomocMenu);

      javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
      getContentPane().setLayout(layout);
      layout.setHorizontalGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup().addComponent(mapaPanel, javax.swing.GroupLayout.PREFERRED_SIZE,
                  950, javax.swing.GroupLayout.PREFERRED_SIZE).addGap(0, 0, Short.MAX_VALUE)));
      layout.setVerticalGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup().addComponent(mapaPanel, javax.swing.GroupLayout.PREFERRED_SIZE,
                  950, javax.swing.GroupLayout.PREFERRED_SIZE).addGap(0, 0, Short.MAX_VALUE)));

      mapaPanel.getAccessibleContext().setAccessibleName("");

      pack();
   }

   public static void main(String args[]) {
      JFrame gra = new Samotnik(0, Color.BLACK);
      gra.setVisible(true);
   }
}
