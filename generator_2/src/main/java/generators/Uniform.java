package generators;

import types.EType;

public class Uniform extends Generator {
    public Uniform(double[] params){
        generatorParams = params;
    }

    double getRandomValue(double a, double b) {
        return Math.random()*(b-a) + a;
    }

    public EType getMessageType() {
        double typeNumber = getRandomValue(1, 4);
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
