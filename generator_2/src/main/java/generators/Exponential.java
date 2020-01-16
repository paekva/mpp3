package generators;

import types.EType;

public class Exponential extends Generator {
    public Exponential(double[] params){
        generatorParams = params;
    }

    double getRandomValue() {
        return Math.log(1 - Math.random()) / generatorParams[0];
    }

    public EType getMessageType() {
        double typeNumber = getRandomValue();
        int type = (int) typeNumber / 3;

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
