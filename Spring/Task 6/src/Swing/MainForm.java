package Swing;

import GraphMath.*;

import javax.swing.*;
import java.awt.*;

public class MainForm extends JFrame {

    private MainForm() {

        JFrame frame = new JFrame("Curve painter");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(new Dimension(800, 800));
        frame.setMinimumSize(new Dimension(400, 400));

        DrawPanel drawPanel = new DrawPanel();

        JPanel uiPanel = new JPanel();
        uiPanel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, Color.BLACK));

        JComboBox<Curve> curveChoice = new JComboBox<>(new Curve[]{
                new Parabola(3),
                new Ellipse(5, 7),
                new Hyperbola(5, 2),
                new Circle(7)
        });
        curveChoice.addActionListener(choice -> {
            drawPanel.setCurve((Curve) curveChoice.getSelectedItem());
            drawPanel.repaint();
        });
        curveChoice.setSelectedIndex(0);
        uiPanel.add(curveChoice);

        uiPanel.add(Box.createRigidArea(new Dimension(50, 0)));

        drawPanel.setSize(800, 800);
        drawPanel.repaint();

        JButton zoomIn = new JButton("Zoom in");
        zoomIn.addActionListener(click -> drawPanel.zoomIn());
        uiPanel.add(zoomIn);

        JButton zoomOut = new JButton("Zoom out");
        zoomOut.addActionListener(click -> drawPanel.zoomOut());
        uiPanel.add(zoomOut);

        JButton zoomDefault = new JButton("Default");
        zoomDefault.addActionListener(click -> drawPanel.zoomDefault());
        uiPanel.add(zoomDefault);

        frame.add(uiPanel, BorderLayout.PAGE_END);
        frame.add(drawPanel, BorderLayout.CENTER);

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new MainForm();
    }


}
