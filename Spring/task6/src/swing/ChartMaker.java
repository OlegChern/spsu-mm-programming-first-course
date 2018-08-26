package swing;

import mathlib.*;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.DefaultXYDataset;

import java.util.Vector;

public class ChartMaker {

    public static JFreeChart buildChart(FuncMath math, String funcName, double X, double Y, double scroll) {
        Vector<FuncSeries> vectorOfSeries = math.giveSeries(X, Y, scroll);
        Borders borders = math.giveResolution();
        DefaultXYDataset ds = new DefaultXYDataset();
        Vector<Point> points;
        double[][] data;

        for (FuncSeries funcSeries : vectorOfSeries) {
            points = funcSeries.getPoints();
            data = new double[2][points.size()];
            int i = 0;
            for (Point point : points) {
                data[0][i] = point.getX();
                data[1][i] = point.getY();
                i++;
            }
            ds.addSeries(funcSeries.getSeriesName(), data);
        }

        JFreeChart chart = ChartFactory.createXYLineChart(funcName, "x", "y", ds, PlotOrientation.VERTICAL, true, false, false);
        chart.getXYPlot().getDomainAxis().setRange(borders.getXmin(), borders.getXmax());
        chart.getXYPlot().getRangeAxis().setRange(borders.getYmin(), borders.getYmax());
        return chart;
    }

    public static JFreeChart buildDefaultChart() {
        JFreeChart chart = ChartFactory.createXYLineChart("", "x", "y", new DefaultXYDataset(), PlotOrientation.VERTICAL, true, false, false);
        chart.getXYPlot().getDomainAxis().setRange(FuncMath.getDefaultResolution().getXmin(), FuncMath.getDefaultResolution().getXmax());
        chart.getXYPlot().getRangeAxis().setRange(FuncMath.getDefaultResolution().getYmin(), FuncMath.getDefaultResolution().getYmax());
        return chart;
    }
}