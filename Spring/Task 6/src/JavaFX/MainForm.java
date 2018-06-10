package JavaFX;

import GraphMath.*;
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

import java.security.spec.EllipticCurve;

public class MainForm extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {

        primaryStage.setTitle("Curve painter");
        primaryStage.setMinWidth(400);
        primaryStage.setMinHeight(400);

        BorderPane borderPane = new BorderPane();

        Scene scene = new Scene(borderPane);
        DrawCanvas drawCanvas = new DrawCanvas(400, 400);

        HBox uiPanel = new HBox(5);
        uiPanel.setAlignment(Pos.CENTER);
        uiPanel.setBorder(new Border(new BorderStroke(
                Color.BLACK, Color.BLACK, Color.BLACK, Color.BLACK,
                BorderStrokeStyle.NONE, BorderStrokeStyle.NONE, BorderStrokeStyle.SOLID, BorderStrokeStyle.NONE,
                CornerRadii.EMPTY,
                new BorderWidths(1),
                Insets.EMPTY
        )));

        drawCanvas.widthProperty().bind(borderPane.widthProperty());
        drawCanvas.heightProperty().bind(borderPane.heightProperty().subtract(uiPanel.getPrefHeight()));

        ComboBox<Curve> curveChoice = new ComboBox<>(FXCollections.observableArrayList(
                new Parabola(3),
                new Ellipse(3, 7),
                new Hyperbola(5, 2),
                new Circle(4)
        ));

        curveChoice.getSelectionModel().selectedItemProperty().addListener(e -> {
            drawCanvas.setCurve(curveChoice.getSelectionModel().getSelectedItem());
            drawCanvas.repaint();
        });
        curveChoice.getSelectionModel().select(0);

        uiPanel.getChildren().add(curveChoice);

        Region blank = new Region();
        blank.setPrefWidth(20);
        uiPanel.getChildren().add(blank);

        Button zoomIn = new Button("Zoom in");
        zoomIn.setOnAction(click -> drawCanvas.zoomIn());
        zoomIn.setCursor(Cursor.HAND);
        uiPanel.getChildren().add(zoomIn);

        Button zoomOut = new Button("Zoom out");
        zoomOut.setOnAction(click -> drawCanvas.zoomOut());
        zoomOut.setCursor(Cursor.HAND);
        uiPanel.getChildren().add(zoomOut);

        Button zoomDefault = new Button("Default");
        zoomDefault.setOnAction(click -> drawCanvas.zoomDefault());
        zoomDefault.setCursor(Cursor.HAND);
        uiPanel.getChildren().add(zoomDefault);

        borderPane.setTop(uiPanel);
        borderPane.setCenter(drawCanvas);

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
