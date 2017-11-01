Description:
    Applies selected filter to selected .bmp image.
Arguments:
    -s <source_file_name>
        - path to image to be modified. File needs to exist
    -o <destination_file_name>
        - path to desired destination of new image.
    -f <filter_name>
        - name of filter to be applied. If not provided, image will be copied without any filter.
        - possible filters:
            - gauss
                - Gauss' filter 3x3
            - sobelx
                - Soblel's filter on X-axis
            - sobely
                -Sobel's filter on Y-axis
            - greyen
                - change all colours to shades of grey
Example:
    myInstagram.exe -s C:\sourceImage.bmp -f sobelx -o C:\destinationImage.bmp
