package sample;


import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.input.MouseEvent;
import mathlib.*;
import mathlib.ChartMaker;

import static mathlib.FuncEllipse.FuncEllipseName;
import static mathlib.FuncParabollicRight.FuncParabollicRightName;

public class Main extends Application {


    private String choosenFunc;
    private LineChart linechart;
    private boolean flag;

    public void setChoosenFunc(String choosenFunc) {
        this.choosenFunc = choosenFunc;
    }

    public void setDefaultLineChart() {
        Borders borders = FuncMath.getDefaultResolution();
        NumberAxis xAxis = new NumberAxis(borders.getXmin(), borders.getXmax(), FuncMath.getDefaultStep()) ;
        xAxis.setLabel("X") ;
        NumberAxis yAxis = new NumberAxis(borders.getYmin(), borders.getYmax(), FuncMath.getDefaultStep()) ;
        yAxis.setLabel("Y") ;
        linechart = new LineChart(xAxis, yAxis);
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        flag = false;
        setDefaultLineChart();





        Button button = new Button("Draw");
        Button buttonExit = new Button("Exit");
        Button buttonScale = new Button("Scale");
        Label scalingX = new Label("Enter here X");
        Label scalingY = new Label("Enter here Y");
        Label scalingSc = new Label("Enter here scale coefficient");
        TextField textX = new TextField();
        TextField textY = new TextField();
        TextField textSc = new TextField();
        buttonExit.setVisible(false);
        buttonScale.setVisible(false);
        scalingX.setVisible(false);
        scalingY.setVisible(false);
        scalingSc.setVisible(false);
        textX.setVisible(false);
        textY.setVisible(false);
        textSc.setVisible(false);

        ComboBox comboBox = new ComboBox();
        comboBox.getItems() .add(FuncParabollicRightName);
        comboBox.getItems().add(FuncEllipseName);
        comboBox.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue)->{
            if (newValue == FuncParabollicRightName) {
                linechart = ChartMaker.BuiltChart(new mathForFuncParabollicRight(), FuncMath.getDefaultPointX(), FuncMath.getDefaultPointY(), FuncMath.getDefaultScroll());
                setChoosenFunc(FuncParabollicRightName);
            }
            if (newValue == FuncEllipseName) {
                linechart = ChartMaker.BuiltChart(new mathForFuncEllipse(), FuncMath.getDefaultPointX(), FuncMath.getDefaultPointY(), FuncMath.getDefaultScroll());
                setChoosenFunc(FuncEllipseName);
            }
        });

        GridPane gridPane = new GridPane();
        gridPane.setMinSize(400, 200) ;
        gridPane.setPadding(new Insets(10, 10, 10, 10) );
        gridPane.setVgap(5);
        gridPane.setHgap(5);
        gridPane.setAlignment(Pos.CENTER) ;
        gridPane .add(comboBox, 0, 1);
        gridPane .add(button, 1, 1);
        gridPane .add(buttonExit, 1, 4);
        gridPane .add(buttonScale, 2, 3);
        gridPane .add(textX, 2, 2);
        gridPane .add(textY, 3, 2);
        gridPane .add(textSc, 4, 2);
        gridPane .add(scalingX, 2, 1);
        gridPane .add(scalingY, 3, 1);
        gridPane .add(scalingSc, 4, 1);


        EventHandler<MouseEvent> eventHandler = new EventHandler<>() {
            @Override
            public void handle(MouseEvent e) {
                gridPane .add(linechart, 0, 0);
                buttonExit.setVisible(true);
                buttonScale.setVisible(true);
                scalingX.setVisible(true);
                scalingY.setVisible(true);
                scalingSc.setVisible(true);
                textX.setVisible(true);
                textY.setVisible(true);
                textSc.setVisible(true);
            }
        };

        EventHandler<MouseEvent> eventHandlerExit = new EventHandler<>() {
            @Override
            public void handle(MouseEvent event) {
                System.exit(0);
            }
        };

        EventHandler<MouseEvent> eventHandlerScale = new EventHandler<>() {
            @Override
            public void handle(MouseEvent event) {
                if (flag) {
                    gridPane.getChildren().remove(10);
                }
                else {
                    flag = true;
                    gridPane.getChildren().remove(linechart);
                }
                if (choosenFunc.equals(FuncParabollicRightName)) {
                    mathForFuncParabollicRight math = new mathForFuncParabollicRight();
                    linechart = ChartMaker.BuiltChart(math, Double.parseDouble(textX.getText()), Double.parseDouble(textY.getText()), Double.parseDouble(textSc.getText()));
                } else if (choosenFunc.equals(FuncEllipseName)) {
                    mathForFuncEllipse math = new mathForFuncEllipse();
                    linechart = ChartMaker.BuiltChart(math, Double.parseDouble(textX.getText()), Double.parseDouble(textY.getText()), Double.parseDouble(textSc.getText()));
                }
                gridPane.add(linechart, 0, 0);
            }
        };

        button .addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandler);
        buttonExit.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandlerExit);
        buttonScale.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandlerScale);

        Scene scene = new Scene(gridPane ,1200, 600);
        primaryStage.setTitle("Graphics");
        primaryStage.setScene(scene);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
