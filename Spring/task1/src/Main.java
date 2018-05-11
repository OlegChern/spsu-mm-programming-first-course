import Image.*;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.InvalidParameterException;
import java.util.function.BiFunction;

public class Main {

    private static final BiFunction<Pixel, Pixel, Pixel> ROOT_MEAN_SQUARE = (p1, p2) -> {
        if (p1.getNumberOfChannels() != p2.getNumberOfChannels()) {
            throw new InvalidParameterException("Pixel dimensions mismatch");
        }

        byte[] channels = new byte[p1.getNumberOfChannels()];
        for (int i = 0; i < p1.getNumberOfChannels(); i++) {
            channels[i] = Pixel.clump(Math.sqrt((p1.getChannel(i) & 0xff) * (p1.getChannel(i) & 0xff) + (p2.getChannel(i) & 0xff) * (p2.getChannel(i) & 0xff)));
        }

        return new Pixel(channels);
    };

    public static void main(String[] args) throws Exception {

        if (args.length == 0) {
            System.out.println("You haven't input any file");
            System.out.println("You should have entered in taskbar:java Main <input file> [-out <output file>] [filter(which you want to apply to the picture)]");
        } else {
            String inputFileName = args[0];
            String outputFileName = args[1].equals("-out") ? args[2] : "output.bmp";
            Image image = new Image(new File(inputFileName));
            for (int argPos = args[1].equals("-out") ? 3 : 1; argPos < args.length; argPos++) {
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
                        image.applyFilter(Filter.GAUSSIAN_3X3);
                        break;
                    case "gaussian5x5":
                        image.applyFilter(Filter.GAUSSIAN_5X5);
                        break;
                    case "sobelX":
                        image.applyFilter(Filter.SOBEL_X);
                        break;
                    case "sobelY":
                        image.applyFilter(Filter.SOBEL_Y);
                        break;
                    case "sobel":
                        image.applyFiltersComposition(Filter.SOBEL_X, Filter.SOBEL_Y, ROOT_MEAN_SQUARE);
                        break;
                    case "scharrX":
                        image.applyFilter(Filter.SCHARR_X);
                        break;
                    case "scharrY":
                        image.applyFilter(Filter.SCHARR_Y);
                        break;
                    case "scharr":
                        image.applyFiltersComposition(Filter.SCHARR_X, Filter.SCHARR_Y, ROOT_MEAN_SQUARE);
                        break;
                    default:
                        System.out.println("Unrecognized option: " + args[argPos]);
                }
            }

            image.writeDownTo(
                    Files.exists(Paths.get(outputFileName)) ? new File(outputFileName) : Files.createFile(Paths.get(outputFileName)).toFile());

        }
    }
}