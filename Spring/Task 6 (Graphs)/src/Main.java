import Shapes.*;

import javax.swing.*;
import java.awt.*;

import Canvas.*;

public class Main {
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(Main::makeGUI);
    }
    
    private static void makeGUI() {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException e) {
            try {
                UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
            } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException e1) {
                e1.printStackTrace();
                System.exit(1);
            }
        }
    
        JFrame frame = new JFrame("Graphs");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(new Dimension(400, 400));
        frame.setMinimumSize(new Dimension(400, 400));
        
        MyCanvas myCanvas = new MyCanvas();
        myCanvas.setCursor(new Cursor(Cursor.MOVE_CURSOR));
        
        JPanel uiPanel = new JPanel();
        uiPanel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, Color.BLACK));
        
        JComboBox<Plottable> graphChoice = new JComboBox<>(new Plottable[]{
                new Ellipse(3, 2),
                new Hyperbola(3, 2),
                new Parabola(1),
                new EllipticCurve(-2, 1)
        });
        graphChoice.addActionListener(e -> {
            myCanvas.setPlot((Plottable) graphChoice.getSelectedItem());
            myCanvas.repaint();
        });
        graphChoice.setSelectedIndex(0);
        uiPanel.add(graphChoice);
        
        uiPanel.add(Box.createRigidArea(new Dimension(50, 0)));
        
        JButton zoomIn = new JButton("+");
        zoomIn.addActionListener(e -> myCanvas.zoomIn());
        zoomIn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        uiPanel.add(zoomIn);
        
        JButton zoomOut = new JButton("-");
        zoomOut.addActionListener(e -> myCanvas.zoomOut());
        zoomOut.setCursor(new Cursor(Cursor.HAND_CURSOR));
        uiPanel.add(zoomOut);
        
        frame.add(uiPanel, BorderLayout.PAGE_START);
        frame.add(myCanvas, BorderLayout.CENTER);
        
        frame.setVisible(true);
    }
}
