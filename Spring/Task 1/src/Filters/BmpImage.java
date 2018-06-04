package Filters;

public class BmpImage {

    private BitMapFileHeader header;
    private BitMapInfo mapInfo;
    private BitMap map;
    private BitMap newMap;

    BmpImage(BitMapFileHeader header, BitMapInfo mapInfo, BitMap map, BitMap copy) {
        this.header = header;
        this.mapInfo = mapInfo;
        this.map = map;
        this.newMap = copy;
    }

    public BitMapFileHeader getHeader() {
        return header;
    }

    public BitMapInfo getMapInfo() {
        return mapInfo;
    }

    public BitMap getNewMap() {
        return newMap;
    }

    public BitMap getMap() {
        return map;
    }

    public Integer getSize() {
        return header.getSize();
    }

    public Integer getHeight() {
        return mapInfo.getBiHeight();
    }

    public Integer getWidth() {
        return mapInfo.getBiWidth();
    }


}
