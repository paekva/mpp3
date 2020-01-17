package generators;

import types.EType;
import types.ModeType;

public abstract class Generator {
    abstract double getRandomValue();
    abstract public EType getMessageType();

    double[] generatorParams;

    private int getNaturalNumber(){
        int random = (int)getRandomValue();
        return random < 0
                ? random * (-1)
                : random == 0
                    ? 1
                    : random;
    }

    public static Generator initGenerator(ModeType mode, double[] params) {
        if (mode == ModeType.EXPONENTIAL) {
            return new Exponential(params[0]);
        } else if (mode == ModeType.NORMAL) {
            return new Normal(params);
        } else {
            return new Uniform(params);
        }
    }

    public int getFibbonacciNumber(){ return getNaturalNumber(); }

    public int getPowBase(){ return (int)getRandomValue(); }

    public int getPowValue(){ return getNaturalNumber(); }

    public int getArraySize(){ return getNaturalNumber(); }

    public double[] getArray(int arrayLength){
        double[] array = new double[arrayLength];

        for(int i=0; i<arrayLength; i++){
            array[i] = getRandomValue();
        }
        return array;
    }

    public int getMessagesCount(){ return getNaturalNumber(); }

    public long getMessagesInterval(){
        return getNaturalNumber()*100;
    }
}
