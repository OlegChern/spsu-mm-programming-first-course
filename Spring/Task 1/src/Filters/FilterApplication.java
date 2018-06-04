package Filters;

import java.io.IOException;

public class FilterApplication {

    public static void run(String[] args) throws IOException, InvalidArgsException, InvalidFileFormatException {

        if (args.length < 3) throw new InvalidArgsException("Not enough arguments");

        checkArgs(args);

        String inputPath = args[0];
        String outputPath = args[1];
        String filterType = args[2];
        String additionalArgs = args.length > 3 ? args[3] : "";

        ImageReader processor = new ImageReader(inputPath);
        BmpImage image = processor.readFile();

        FilterApplier filter = new FilterApplier(image, getFilterType(filterType), additionalArgs);
        filter.ApplyFilter();

        ImageWriter writer = new ImageWriter(image, outputPath);
        writer.writeFile();

    }

    private static void checkArgs(String[] args) throws InvalidArgsException {

        if (args.length < 3) throw new InvalidArgsException("Not enough arguments");

        if (!(args[2].equals("median") || args[2].equals("grey") || args[2].equals("gauss") || args[2].equals("sobel")))
            throw new InvalidArgsException("Unsupported filter type");

        if (args[2].equals("gauss")) {
            if (args.length < 4) throw new InvalidArgsException("Additional filter argument is missing");
            else if (!(args[3].equals("3") || args[3].equals("5")))
                throw new InvalidArgsException("Invalid gauss filter dimension");
        }

        if (args[2].equals("sobel")) {
            if (args.length < 4) throw new InvalidArgsException("Additional filter argument is missing");
            else if (!(args[3].equals("x") || args[3].equals("y") || args[3].equals("xy")))
                throw new InvalidArgsException("Invalid sobel filter argument");
        }
    }

    private static FilterType getFilterType(String filterName) {
        switch (filterName) {
            case "median":
                return FilterType.Median;
            case "grey":
                return FilterType.Grey;
            case "gauss":
                return FilterType.Gauss;
            case "sobel":
                return FilterType.Sobel;
            default:
                return null;
        }
    }
}
