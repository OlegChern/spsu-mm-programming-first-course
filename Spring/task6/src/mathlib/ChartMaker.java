package mathlib;

import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import java.util.Vector;

public class ChartMaker {
    public static LineChart BuiltChart(FuncMath math, double X, double Y, double scroll) {
        Vector<FuncSeries> vectorOfSeries = math.giveSeries(X, Y, scroll);
        Borders borders = math.giveResolution();
        NumberAxis xAxis = new NumberAxis(borders.getXmin(), borders.getXmax(), math.getStep());
        xAxis.setLabel("X");
        NumberAxis yAxis = new NumberAxis(borders.getYmin(), borders.getYmax(), math.getStep());
        yAxis.setLabel("Y");
        LineChart linechart = new LineChart(xAxis, yAxis);
        linechart.setCreateSymbols(false);
        Vector<Point> points;
        XYChart.Series series;
        for (FuncSeries funcSeries : vectorOfSeries) {
            series = new XYChart.Series();
            series.setName(funcSeries.getSeriesName());
            points = funcSeries.getPoints();
            for (Point point : points) {
                series.getData().add(new XYChart.Data(point.getX(), point.getY()));
            }
            linechart.getData().add(series);
        }
        return linechart;
    }
}

