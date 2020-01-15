package generators;

import types.EType;

import java.util.Random;

public class Normal extends Generator {
    public Normal(double[] params){
        generatorParams = params;
    }

    double getRandomValue(double m, double y) {
        Random generator = new Random();
        double nxt = generator.nextGaussian(); // standard normal dist
        return nxt * y + m; // convert standard to original with params m and y
    }

    public EType getMessageType() {
        double typeNumber = getRandomValue(generatorParams[0], generatorParams[1]);

        // convert given value to the interval
        System.out.println("normal " + typeNumber);

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
