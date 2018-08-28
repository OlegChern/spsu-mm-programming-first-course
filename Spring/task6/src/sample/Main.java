package sample;

import java.util.Vector;
import mathlib.*;
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

import static mathlib.FuncEllipse.FuncEllipseName;
import static mathlib.FuncParabollicRight.FuncParabollicRightName;

public class Main extends Application {


    private String chosenFunc;
    private LineChart linechart;

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
        buttonExit.setDisable(true);
        buttonScale.setDisable(true);
        scalingX.setDisable(true);
        scalingY.setDisable(true);
        scalingSc.setDisable(true);
        textX.setDisable(true);
        textY.setDisable(true);
        textSc.setDisable(true);

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
        gridPane.setMinSize(450, 200) ;
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
        linechart.setMinSize(450, 450);
        linechart.setMaxSize(450, 450);
        gridPane .add(linechart, 0, 0, 4, 1);


        EventHandler<MouseEvent> eventHandler = new EventHandler<>() {
            @Override
            public void handle(MouseEvent e) {
                gridPane.getChildren().remove(10);
                linechart.setMinSize(450, 450);
                linechart.setMaxSize(450, 450);
                gridPane .add(linechart, 0, 0, 4, 1);
                buttonExit.setDisable(false);
                buttonScale.setDisable(false);
                scalingX.setDisable(false);
                scalingY.setDisable(false);
                scalingSc.setDisable(false);
                textX.setDisable(false);
                textY.setDisable(false);
                textSc.setDisable(false);
                button.setDisable(true);
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
                if (!textX.getText().equals("") && !textY.getText().equals("") && !textSc.getText().equals("")) {
                    gridPane.getChildren().remove(10);
                    if (chosenFunc.equals(FuncParabollicRightName)) {
                        MathForFuncParabollicRight math = new MathForFuncParabollicRight();
                        linechart = ChartMaker.BuiltChart(math, Double.parseDouble(textX.getText()), Double.parseDouble(textY.getText()), Double.parseDouble(textSc.getText()));
                    } else if (chosenFunc.equals(FuncEllipseName)) {
                        MathForFuncEllipse math = new MathForFuncEllipse();
                        linechart = ChartMaker.BuiltChart(math, Double.parseDouble(textX.getText()), Double.parseDouble(textY.getText()), Double.parseDouble(textSc.getText()));
                    }
                    linechart.setMinSize(450, 450);
                    linechart.setMaxSize(450, 450);
                    gridPane.add(linechart, 0, 0, 4, 1);
                }
            }
        };

        button .addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandler);
        buttonExit.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandlerExit);
        buttonScale.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandlerScale);

        Scene scene = new Scene(gridPane ,475, 575);
        primaryStage.setTitle("Graphics");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();
    }


    public static void main(String[] args) {
        MathForFuncEllipse math = new MathForFuncEllipse();
        Vector<FuncSeries> tmp = math.giveSeries(1, 0, 5);
        Vector <Point> points = tmp.elementAt(1).getPoints();
        launch(args);
    }
}
