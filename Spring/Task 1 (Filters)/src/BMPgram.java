import BMPImage.*;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.InvalidParameterException;
import java.util.function.BiFunction;

public class BMPgram {

    private static final Operator GAUSSIAN_3X3_OPERATOR = new Operator(new double[][]{
            {1.0 / 16, 2.0 / 16, 1.0 / 16},
            {2.0 / 16, 4.0 / 16, 2.0 / 16},
            {1.0 / 16, 2.0 / 16, 1.0 / 16}
    });

    private static final Operator GAUSSIAN_5X5_OPERATOR = new Operator(new double[][]{
            {1.0 / 273, 4.0 / 273, 7.0 / 273, 4.0 / 273, 1.0 / 271},
            {4.0 / 273, 16.0 / 273, 26.0 / 273, 16.0 / 273, 4.0 / 273},
            {7.0 / 273, 26.0 / 273, 41.0 / 273, 26.0 / 273, 7.0 / 273},
            {4.0 / 273, 16.0 / 273, 26.0 / 273, 16.0 / 273, 4.0 / 273},
            {1.0 / 273, 4.0 / 273, 7.0 / 273, 4.0 / 273, 1.0 / 271}
    });

    private static final Operator SOBEL_X_OPERATOR = new Operator(new double[][]{
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    });

    private static final Operator SOBEL_Y_OPERATOR = new Operator(new double[][]{
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
    });

    private static final Operator SCHARR_X_OPERATOR = new Operator(new double[][]{
            {3, 0, -3},
            {10, 0, -10},
            {3, 0, -3}
    });

    private static final Operator SCHARR_Y_OPERATOR = new Operator(new double[][]{
            {3, 10, 3},
            {0, 0, 0},
            {-3, -10, -3}
    });

    private static final BiFunction<Pixel, Pixel, Pixel> ROOT_MEAN_SQUARE = (p1, p2) -> {
        if (p1.getNumberOfChannels() != p2.getNumberOfChannels()) {
            throw new InvalidParameterException("Pixel dimensions mismatch");
        }

        byte[] channels = new byte[p1.getNumberOfChannels()];
        for (int i = 0; i < p1.getNumberOfChannels(); i++) {
            channels[i] = Pixel.clump(Math.sqrt(
                    (p1.getChannel(i) & 0xff) * (p1.getChannel(i) & 0xff) +
                            (p2.getChannel(i) & 0xff) * (p2.getChannel(i) & 0xff)
            ));
        }

        return new Pixel(channels);
    };

    public static void main(String[] args) throws IOException, WrongFileFormatException {
        if (args.length == 0) {
            System.out.println("Not specified input file. See README file.");
        } else {
            String inputFileName = args[0];
            String outputFileName = args[1].equals("-o") ? args[2] : "output.bmp";

            BMPImage image = new BMPImage(new File(inputFileName));

            for (int argPos = args[1].equals("-o") ? 3 : 1; argPos < args.length; argPos++) {
                switch (args[argPos]) {
                    case "monochrome":
                        image.makeMonochrome();
                        break;
                    case "median":
                        try {
                            int regionHeight = Integer.parseInt(args[argPos + 1]);
                            int regionWidth = Integer.parseInt(args[argPos + 2]);

                            try {
                                image.medianFilter(regionHeight, regionWidth);
                            } catch (InvalidParameterException ipe) {
                                System.out.println("Incorrect parameter: " + ipe.getMessage());
                            }
                        } catch (NumberFormatException nfe) {
                            System.out.println("Incorrect parameters: cannot be parsed to number.");
                        } catch (ArrayIndexOutOfBoundsException aioobe) {
                            System.out.println("Parameter is missed");
                        }

                        argPos += 2;
                        break;
                    case "gaussian3x3":
                        image.applyFilter(GAUSSIAN_3X3_OPERATOR);
                        break;
                    case "gaussian5x5":
                        image.applyFilter(GAUSSIAN_5X5_OPERATOR);
                        break;
                    case "sobelX":
                        image.applyFilter(SOBEL_X_OPERATOR);
                        break;
                    case "sobelY":
                        image.applyFilter(SOBEL_Y_OPERATOR);
                        break;
                    case "sobel":
                        image.applyFiltersComposition(SOBEL_X_OPERATOR, SOBEL_Y_OPERATOR, ROOT_MEAN_SQUARE);
                        break;
                    case "scharrX":
                        image.applyFilter(SCHARR_X_OPERATOR);
                        break;
                    case "scharrY":
                        image.applyFilter(SCHARR_Y_OPERATOR);
                        break;
                    case "scharr":
                        image.applyFiltersComposition(SCHARR_X_OPERATOR, SCHARR_Y_OPERATOR, ROOT_MEAN_SQUARE);
                        break;
                    default:
                        System.out.println("Unrecognized option: " + args[argPos]);
                }
            }

            image.writeDownTo(
                    Files.exists(Paths.get(outputFileName)) ?
                            new File(outputFileName) :
                            Files.createFile(Paths.get(outputFileName)).toFile()
            );

        }
    }

}
