package generators;

import types.EType;

public class Exponential extends Generator {
    public Exponential(double[] params){
        generatorParams = params;
    }

    double getRandomValue(double m, double y) {
        return Math.log(1 - Math.random()) / generatorParams[0];
    }

    public EType getMessageType() {
        double typeNumber = getRandomValue(generatorParams[0], generatorParams[1]);

        // convert given value to the interval

        int type = (int) typeNumber;

        switch(type){
            case 1:
                return EType.FIBONACCI;
            case 2:
                return EType.POW;
            case 3:
                return EType.BUBBLE_SORT_UINT64;
            default:
                return EType.STOP;
        }
    }
}
