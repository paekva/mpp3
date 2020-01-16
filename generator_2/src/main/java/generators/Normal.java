package generators;

import types.EType;

import java.util.Random;

public class Normal extends Generator {
    public Normal(double[] params){
        generatorParams = params;
    }

    double getRandomValue() {
        Random generator = new Random();
        double nxt = generator.nextGaussian(); // standard normal dist
        return nxt * generatorParams[1] + generatorParams[0]; // convert standard to original with params m and y
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
