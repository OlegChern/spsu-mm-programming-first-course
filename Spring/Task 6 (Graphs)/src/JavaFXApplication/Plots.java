package JavaFXApplication;

import Shapes.*;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Cursor;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class Plots extends Application {
    
    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Plots");
        
        primaryStage.setMinWidth(400);
        primaryStage.setMinHeight(400);
        
        BorderPane borderPane = new BorderPane();
        
        Scene scene = new Scene(borderPane);
        
        MyCanvas myCanvas = new MyCanvas(400, 400);
        myCanvas.setCursor(Cursor.MOVE);
        
        HBox uiPanel = new HBox(5);
        uiPanel.setBackground(new Background(new BackgroundFill(Color.gray(0.9), CornerRadii.EMPTY, Insets.EMPTY)));
        uiPanel.setPrefHeight(40);
        uiPanel.setPadding(new Insets(5));
        uiPanel.setAlignment(Pos.CENTER);
        uiPanel.setBorder(new Border(new BorderStroke(
                Color.BLACK, Color.BLACK, Color.BLACK, Color.BLACK,
                BorderStrokeStyle.NONE, BorderStrokeStyle.NONE, BorderStrokeStyle.SOLID, BorderStrokeStyle.NONE,
                CornerRadii.EMPTY,
                new BorderWidths(1),
                Insets.EMPTY
        )));
        
        myCanvas.widthProperty().bind(borderPane.widthProperty());
        myCanvas.heightProperty().bind(borderPane.heightProperty().subtract(uiPanel.getPrefHeight()));
        
        ComboBox<Plottable> graphChoice = new ComboBox<>(FXCollections.observableArrayList(
                new Ellipse(3, 2),
                new Hyperbola(3, 2),
                new Parabola(1),
                new EllipticCurve(-2, 1)
        ));

        graphChoice.getSelectionModel().selectedItemProperty().addListener(e -> {
            myCanvas.setPlot(graphChoice.getSelectionModel().getSelectedItem());
            myCanvas.repaintAll();
        });
        graphChoice.getSelectionModel().select(0);

        uiPanel.getChildren().add(graphChoice);
        
        Region blank = new Region();
        blank.setPrefWidth(20);
        uiPanel.getChildren().add(blank);
        
        Button zoomIn = new Button("+");
        zoomIn.setOnAction(e -> myCanvas.zoomIn());
        zoomIn.setCursor(Cursor.HAND);
        uiPanel.getChildren().add(zoomIn);

        Button zoomOut = new Button("-");
        zoomOut.setOnAction(e -> myCanvas.zoomOut());
        zoomOut.setCursor(Cursor.HAND);
        uiPanel.getChildren().add(zoomOut);

        borderPane.setTop(uiPanel);
        borderPane.setCenter(myCanvas);
        
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
