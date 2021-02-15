import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class MyCalendar extends javax.swing.JFrame {
   int currYear;
   int currMonth;
   int currDay;
   String[] months = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October",
         "November", "December" };
   String[] days = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

   public MyCalendar() {
      currYear = 2020;
      currMonth = 1;
      currDay = 1;
      initComponents();
   }

   void populateMonthPane(JPanel currMonthPanel, String name) {

      Calendar calendar = new GregorianCalendar(currYear, currMonth, currDay);

      int daysInMonth = calendar.getActualMaximum(Calendar.DAY_OF_MONTH);
      int firstDay = calendar.getFirstDayOfWeek();

      currMonthPanel.setBorder(BorderFactory.createLineBorder(new Color(0, 0, 0)));
      currMonthPanel.setLayout(new BorderLayout());
      JLabel monthName = new JLabel(name);
      currMonthPanel.add(monthName, BorderLayout.PAGE_START);
      JPanel daysPanel = new JPanel();
      daysPanel.setLayout(new GridLayout(6, 7));
      for (int i = 0; i < 7; i++) {
         JLabel day = new JLabel(days[i]);
         daysPanel.add(day);
      }
      for (int i = 0; i < 35; i++) {
         JLabel day;
         if (i < firstDay)
            day = new JLabel("");
         else
            day = new JLabel(Integer.toString(i - firstDay));
         daysPanel.add(day);
      }
      currMonthPanel.add(daysPanel, BorderLayout.CENTER);
   }

   private void initComponents() {
      java.awt.GridBagConstraints gridBagConstraints;

      calendarPane = new javax.swing.JTabbedPane();
      yearPanel = new javax.swing.JPanel();
      januaryPanel = new javax.swing.JPanel();
      februaryPanel = new javax.swing.JPanel();
      marchPanel = new javax.swing.JPanel();
      aprilPanel = new javax.swing.JPanel();
      mayPanel = new javax.swing.JPanel();
      junePanel = new javax.swing.JPanel();
      julyPanel = new javax.swing.JPanel();
      augustPanel = new javax.swing.JPanel();
      septemberPanel = new javax.swing.JPanel();
      octoberPanel = new javax.swing.JPanel();
      novemberPanel = new javax.swing.JPanel();
      decemberPanel = new javax.swing.JPanel();
      monthPanel = new javax.swing.JPanel();
      prevMonthPane = new javax.swing.JScrollPane();
      prevMonthList = new javax.swing.JList<>();
      currMonthPane = new javax.swing.JScrollPane();
      currMonthList = new javax.swing.JList<>();
      nextMonthPane = new javax.swing.JScrollPane();
      nextMonthList = new javax.swing.JList<>();
      prevMonthButton = new javax.swing.JButton();
      nextMonthButton = new javax.swing.JButton();

      setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

      yearPanel.setLayout(new java.awt.GridLayout(3, 4));

      javax.swing.GroupLayout januaryPanelLayout = new javax.swing.GroupLayout(januaryPanel);
      januaryPanel.setLayout(januaryPanelLayout);
      januaryPanelLayout.setHorizontalGroup(januaryPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      januaryPanelLayout.setVerticalGroup(januaryPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(januaryPanel);

      javax.swing.GroupLayout februaryPanelLayout = new javax.swing.GroupLayout(februaryPanel);
      februaryPanel.setLayout(februaryPanelLayout);
      februaryPanelLayout.setHorizontalGroup(februaryPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      februaryPanelLayout.setVerticalGroup(februaryPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(februaryPanel);

      javax.swing.GroupLayout marchPanelLayout = new javax.swing.GroupLayout(marchPanel);
      marchPanel.setLayout(marchPanelLayout);
      marchPanelLayout.setHorizontalGroup(marchPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      marchPanelLayout.setVerticalGroup(marchPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(marchPanel);

      javax.swing.GroupLayout aprilPanelLayout = new javax.swing.GroupLayout(aprilPanel);
      aprilPanel.setLayout(aprilPanelLayout);
      aprilPanelLayout.setHorizontalGroup(aprilPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      aprilPanelLayout.setVerticalGroup(aprilPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(aprilPanel);

      javax.swing.GroupLayout mayPanelLayout = new javax.swing.GroupLayout(mayPanel);
      mayPanel.setLayout(mayPanelLayout);
      mayPanelLayout.setHorizontalGroup(mayPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 178, Short.MAX_VALUE));
      mayPanelLayout.setVerticalGroup(mayPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(mayPanel);

      javax.swing.GroupLayout junePanelLayout = new javax.swing.GroupLayout(junePanel);
      junePanel.setLayout(junePanelLayout);
      junePanelLayout.setHorizontalGroup(junePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 178, Short.MAX_VALUE));
      junePanelLayout.setVerticalGroup(junePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(junePanel);

      javax.swing.GroupLayout julyPanelLayout = new javax.swing.GroupLayout(julyPanel);
      julyPanel.setLayout(julyPanelLayout);
      julyPanelLayout.setHorizontalGroup(julyPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 178, Short.MAX_VALUE));
      julyPanelLayout.setVerticalGroup(julyPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(julyPanel);

      javax.swing.GroupLayout augustPanelLayout = new javax.swing.GroupLayout(augustPanel);
      augustPanel.setLayout(augustPanelLayout);
      augustPanelLayout.setHorizontalGroup(augustPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      augustPanelLayout.setVerticalGroup(augustPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(augustPanel);

      javax.swing.GroupLayout septemberPanelLayout = new javax.swing.GroupLayout(septemberPanel);
      septemberPanel.setLayout(septemberPanelLayout);
      septemberPanelLayout.setHorizontalGroup(septemberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      septemberPanelLayout.setVerticalGroup(septemberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(septemberPanel);

      javax.swing.GroupLayout octoberPanelLayout = new javax.swing.GroupLayout(octoberPanel);
      octoberPanel.setLayout(octoberPanelLayout);
      octoberPanelLayout.setHorizontalGroup(octoberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      octoberPanelLayout.setVerticalGroup(octoberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(octoberPanel);

      javax.swing.GroupLayout novemberPanelLayout = new javax.swing.GroupLayout(novemberPanel);
      novemberPanel.setLayout(novemberPanelLayout);
      novemberPanelLayout.setHorizontalGroup(novemberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      novemberPanelLayout.setVerticalGroup(novemberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(novemberPanel);

      javax.swing.GroupLayout decemberPanelLayout = new javax.swing.GroupLayout(decemberPanel);
      decemberPanel.setLayout(decemberPanelLayout);
      decemberPanelLayout.setHorizontalGroup(decemberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 178, Short.MAX_VALUE));
      decemberPanelLayout.setVerticalGroup(decemberPanelLayout
            .createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGap(0, 163, Short.MAX_VALUE));

      yearPanel.add(decemberPanel);

      calendarPane.addTab("Year", yearPanel);

      monthPanel.setLayout(new java.awt.GridBagLayout());

      prevMonthPane.setPreferredSize(new java.awt.Dimension(200, 400));

      prevMonthList.setModel(new javax.swing.AbstractListModel<String>() {
         String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };

         public int getSize() {
            return strings.length;
         }

         public String getElementAt(int i) {
            return strings[i];
         }
      });
      prevMonthList.setPreferredSize(new java.awt.Dimension(250, 600));
      prevMonthPane.setViewportView(prevMonthList);

      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
      monthPanel.add(prevMonthPane, gridBagConstraints);

      currMonthPane.setPreferredSize(new java.awt.Dimension(200, 400));
      currMonthPane.setRequestFocusEnabled(false);

      currMonthList.setModel(new javax.swing.AbstractListModel<String>() {
         String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };

         public int getSize() {
            return strings.length;
         }

         public String getElementAt(int i) {
            return strings[i];
         }
      });
      currMonthList.setPreferredSize(new java.awt.Dimension(250, 600));
      currMonthPane.setViewportView(currMonthList);

      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
      monthPanel.add(currMonthPane, gridBagConstraints);

      nextMonthPane.setPreferredSize(new java.awt.Dimension(200, 400));

      nextMonthList.setModel(new javax.swing.AbstractListModel<String>() {
         String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };

         public int getSize() {
            return strings.length;
         }

         public String getElementAt(int i) {
            return strings[i];
         }
      });
      nextMonthList.setPreferredSize(new java.awt.Dimension(200, 600));
      nextMonthPane.setViewportView(nextMonthList);

      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
      monthPanel.add(nextMonthPane, gridBagConstraints);

      prevMonthButton.setText("Previous Month");
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 1;
      monthPanel.add(prevMonthButton, gridBagConstraints);

      nextMonthButton.setText("Next Month");
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 2;
      gridBagConstraints.gridy = 1;
      monthPanel.add(nextMonthButton, gridBagConstraints);

      calendarPane.addTab("Month", monthPanel);

      javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
      getContentPane().setLayout(layout);
      layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addComponent(calendarPane));
      layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addComponent(calendarPane));

      for (int i = 0; i < 12; i++) {
         JPanel currPanel = (JPanel) yearPanel.getComponent(i);
         populateMonthPane(currPanel, months[i]);
      }
      // populateMonthPane(januaryPanel, "January");
      pack();
   }

   public static void main(String args[]) {
      java.awt.EventQueue.invokeLater(new Runnable() {
         public void run() {
            new MyCalendar().setVisible(true);
         }
      });
   }

   private javax.swing.JPanel aprilPanel;
   private javax.swing.JPanel augustPanel;
   private javax.swing.JTabbedPane calendarPane;
   private javax.swing.JList<String> currMonthList;
   private javax.swing.JScrollPane currMonthPane;
   private javax.swing.JPanel decemberPanel;
   private javax.swing.JPanel februaryPanel;
   private javax.swing.JPanel januaryPanel;
   private javax.swing.JPanel julyPanel;
   private javax.swing.JPanel junePanel;
   private javax.swing.JPanel marchPanel;
   private javax.swing.JPanel mayPanel;
   private javax.swing.JPanel monthPanel;
   private javax.swing.JButton nextMonthButton;
   private javax.swing.JList<String> nextMonthList;
   private javax.swing.JScrollPane nextMonthPane;
   private javax.swing.JPanel novemberPanel;
   private javax.swing.JPanel octoberPanel;
   private javax.swing.JButton prevMonthButton;
   private javax.swing.JList<String> prevMonthList;
   private javax.swing.JScrollPane prevMonthPane;
   private javax.swing.JPanel septemberPanel;
   private javax.swing.JPanel yearPanel;
   // End of variables declaration
}
