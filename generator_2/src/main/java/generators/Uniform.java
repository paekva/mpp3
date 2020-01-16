package generators;

import types.EType;

public class Uniform extends Generator {
    public Uniform(double[] params){
        generatorParams = params;
    }

    double getRandomValue(double a, double b) {
        return Math.random()*(b-a) + a;
    }
    double getRandomValue() {
        return Math.random()*(generatorParams[1]-generatorParams[0]) + generatorParams[0];
    }

    public EType getMessageType() {
        double typeNumber = getRandomValue(0, 3);
        int type = (int) typeNumber;

        switch(type){
            case 0:
                return EType.FIBONACCI;
            case 1:
                return EType.POW;
            default:
                return EType.BUBBLE_SORT_UINT64;
        }
    }
}
