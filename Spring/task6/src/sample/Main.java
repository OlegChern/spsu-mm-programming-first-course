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

import static mathlib.FuncEllipse.FuncEllipseName;
import static mathlib.FuncParabollicRight.FuncParabollicRightName;

public class Main extends Application {


    private String chosenFunc;
    private LineChart linechart;
    private boolean flag;
    private boolean graphCreated;

    public void setChoosenFunc(String choosenFunc) {
        this.chosenFunc = choosenFunc;
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
        graphCreated = false;
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
                button.setDisable(false);
                linechart = ChartMaker.BuiltChart(new MathForFuncParabollicRight(), FuncMath.getDefaultPointX(), FuncMath.getDefaultPointY(), FuncMath.getDefaultScroll());
                setChoosenFunc(FuncParabollicRightName);
            }
            if (newValue == FuncEllipseName) {
                button.setDisable(false);
                linechart = ChartMaker.BuiltChart(new MathForFuncEllipse(), FuncMath.getDefaultPointX(), FuncMath.getDefaultPointY(), FuncMath.getDefaultScroll());
                setChoosenFunc(FuncEllipseName);
            }
        });

        GridPane gridPane = new GridPane();
        gridPane.setMinSize(400, 200) ;
        gridPane.setPadding(new Insets(10, 10, 10, 10) );
        gridPane.setVgap(5);
        gridPane.setHgap(5);
        gridPane.setAlignment(Pos.CENTER) ;
        gridPane .add(comboBox, 0, 1, 2, 1);
        gridPane .add(button, 2, 1);
        gridPane .add(buttonExit, 2, 4);
        gridPane .add(buttonScale, 0, 4, 2, 1);
        gridPane .add(textX, 1, 3);
        gridPane .add(textY, 2, 3);
        gridPane .add(textSc, 3, 3);
        gridPane .add(scalingX, 1, 2);
        gridPane .add(scalingY, 2, 2);
        gridPane .add(scalingSc, 3, 2);


        EventHandler<MouseEvent> eventHandler = new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent e) {
                if (graphCreated) {
                    if (flag) {
                        gridPane.getChildren().remove(10);
                    } else {
                        flag = true;
                        gridPane.getChildren().remove(linechart);
                    }
                }
                gridPane .add(linechart, 0, 0, 4, 1);
                buttonExit.setVisible(true);
                buttonScale.setVisible(true);
                scalingX.setVisible(true);
                scalingY.setVisible(true);
                scalingSc.setVisible(true);
                textX.setVisible(true);
                textY.setVisible(true);
                textSc.setVisible(true);
                button.setDisable(true);
                graphCreated = true;
            }
        };

        EventHandler<MouseEvent> eventHandlerExit = new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                System.exit(0);
            }
        };

        EventHandler<MouseEvent> eventHandlerScale = new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                if (!textX.getText().equals("") && !textY.getText().equals("") && !textSc.getText().equals("")) {
                    if (flag) {
                        gridPane.getChildren().remove(10);
                    } else {
                        flag = true;
                        gridPane.getChildren().remove(linechart);
                    }
                    if (chosenFunc.equals(FuncParabollicRightName)) {
                        MathForFuncParabollicRight math = new MathForFuncParabollicRight();
                        linechart = ChartMaker.BuiltChart(math, Double.parseDouble(textX.getText()), Double.parseDouble(textY.getText()), Double.parseDouble(textSc.getText()));
                    } else if (chosenFunc.equals(FuncEllipseName)) {
                        MathForFuncEllipse math = new MathForFuncEllipse();
                        linechart = ChartMaker.BuiltChart(math, Double.parseDouble(textX.getText()), Double.parseDouble(textY.getText()), Double.parseDouble(textSc.getText()));
                    }
                    gridPane.add(linechart, 0, 0, 4, 1);
                }
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
