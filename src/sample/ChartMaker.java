package sample;

import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;

public class ChartMaker {
    public static void BuiltChart(LineChart linechart, mathForFuncParabollicRight math) {
        double[] borders = math.giveResolution();
        XYChart.Series series = new XYChart.Series();
        XYChart.Series series1 = new XYChart.Series();
        series.setName("FunctionPositive");
        series1.setName("FunctionNegative");
        double[] point = new double[2];
        point[1] = 1;
        point[0] = 1;
        linechart.setCreateSymbols(false);
        while (point[0] >= 0.1) {
            point = math.givePoint();
            series.getData().add(new XYChart.Data(point[0], point[1]));
            //System.out.println(point[0] + " " + point[1] + " ");
        }

        series.getData().add(new XYChart.Data(0, 0));
        while (point[0] < borders[3]) {
            point = math.givePoint();
            series1.getData().add(new XYChart.Data(point[0], point[1]));
            // System.out.println(point[0] + " " + point[1] + " ");
        }
        linechart.getData().add(series);
        linechart.getData().add(series1);
    }
}