package swing;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

import mathlib.*;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;

public class Main {

    private static ChartPanel cp;
    private static String FuncName;

    public static void main(String[] args) {

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                JFrame frame = new JFrame("Charts");

                frame.setSize(695, 500);
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
                JButton drawButton = new JButton("Draw");
                JButton exitButton = new JButton("Exit");
                JButton scaleButton = new JButton("Scale");


                JFreeChart chart = ChartMaker.buildDefaultChart();
                cp = new ChartPanel(chart);


                JPanel panel = new JPanel();
                JTextField textFieldX = new JTextField();
                textFieldX.setColumns(10);
                textFieldX.setToolTipText("Enter X");
                JTextField textFieldScale = new JTextField();
                textFieldScale.setColumns(10);
                textFieldScale.setToolTipText("enter Scale coef");
                JTextField textFieldY = new JTextField();
                textFieldY.setColumns(10);
                textFieldY.setToolTipText("Enter Y");
                String[] items = {"", FuncParabollicRight.FuncParabollicRightName, FuncEllipse.FuncEllipseName};
                JComboBox comboBox = new JComboBox(items);

                panel.add(comboBox);
                panel.add(textFieldX);
                panel.add(textFieldY);
                panel.add(textFieldScale);
                panel.add(scaleButton);
                panel.add(drawButton);
                panel.add(exitButton);

                scaleButton.setVisible(false);
                textFieldScale.setVisible(false);
                textFieldX.setVisible(false);
                textFieldY.setVisible(false);

                ActionListener actionListenerComboBox = new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        JComboBox box = (JComboBox) e.getSource();
                        String item = (String) box.getSelectedItem();
                        JFreeChart chart;
                        switch (item) {
                            case FuncParabollicRight.FuncParabollicRightName:
                                chart = ChartMaker.buildChart(new MathForFuncParabollicRight(), FuncParabollicRight.FuncParabollicRightName, FuncMath.getDefaultPointX(), FuncMath.getDefaultPointY(), FuncMath.getDefaultScroll());
                                panel.remove(panel.getComponents().length - 1);
                                cp = new ChartPanel(chart);
                                panel.add(cp);
                                cp.setVisible(false);
                                FuncName = FuncParabollicRight.FuncParabollicRightName;
                                scaleButton.setEnabled(true);
                                break;
                            case FuncEllipse.FuncEllipseName:
                                chart = ChartMaker.buildChart(new MathForFuncEllipse(), FuncEllipse.FuncEllipseName, FuncMath.getDefaultPointX(), FuncMath.getDefaultPointY(), FuncMath.getDefaultScroll());
                                panel.remove(panel.getComponents().length - 1);
                                cp = new ChartPanel(chart);
                                panel.add(cp);
                                cp.setVisible(false);
                                FuncName = FuncEllipse.FuncEllipseName;
                                scaleButton.setEnabled(true);
                                break;
                            case "":
                                chart = ChartMaker.buildDefaultChart();
                                panel.remove(panel.getComponents().length - 1);
                                cp = new ChartPanel(chart);
                                panel.add(cp);
                                cp.setVisible(false);
                                FuncName = "";
                                scaleButton.setEnabled(false);
                        }
                    }
                };

                ActionListener actionListenerExit = new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        System.exit(0);
                    }
                };

                ActionListener actionListenerDraw = new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        cp.setVisible(true);
                        scaleButton.setVisible(true);
                        textFieldScale.setVisible(true);
                        textFieldX.setVisible(true);
                        textFieldY.setVisible(true);
                    }

                };

                ActionListener actionListenerScale = new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        JFreeChart chart;
                        switch (FuncName) {
                            case FuncParabollicRight.FuncParabollicRightName:
                                chart = ChartMaker.buildChart(new MathForFuncParabollicRight(), FuncParabollicRight.FuncParabollicRightName, Double.parseDouble(textFieldX.getText()), Double.parseDouble(textFieldY.getText()), Double.parseDouble(textFieldScale.getText()));
                                panel.remove(panel.getComponents().length - 1);
                                cp = new ChartPanel(chart);
                                panel.add(cp);
                                cp.setVisible(false);
                                cp.setVisible(true);
                                break;
                            case FuncEllipse.FuncEllipseName:
                                chart = ChartMaker.buildChart(new MathForFuncEllipse(), FuncEllipse.FuncEllipseName, Double.parseDouble(textFieldX.getText()), Double.parseDouble(textFieldY.getText()), Double.parseDouble(textFieldScale.getText()));
                                panel.remove(panel.getComponents().length - 1);
                                cp = new ChartPanel(chart);
                                panel.add(cp);
                                cp.setVisible(false);
                                cp.setVisible(true);
                                break;
                        }
                    }
                };

                exitButton.addActionListener(actionListenerExit);
                drawButton.addActionListener(actionListenerDraw);
                scaleButton.addActionListener(actionListenerScale);
                comboBox.addActionListener(actionListenerComboBox);

                panel.add(cp);
                cp.setVisible(false);
                frame.getContentPane().add(panel);
                frame.setResizable(false);
            }
        });

    }
}