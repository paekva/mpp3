package generators;

import types.EType;

public abstract class Generator {
    abstract double getRandomValue(double a, double b);
    abstract public EType getMessageType();

    double[] generatorParams;

    public int getFibbonachiNumber(){
        return (int)getRandomValue(generatorParams[0], generatorParams[1]);
    }

    public int getPowBase(){
        return (int)getRandomValue(generatorParams[0], generatorParams[1]);
    }

    public int getPowValue(){
        return (int)getRandomValue(generatorParams[0], generatorParams[1]);
    }

    public int getArraySize(){
        return (int)getRandomValue(generatorParams[0], generatorParams[1]);
    }

    public double[] getArray(int arrayLength){
        double[] array = new double[arrayLength];

        for(int i=0; i<arrayLength; i++){
            array[i] = getRandomValue(generatorParams[0], generatorParams[1]);
        }
        return array;
    }

    public int getMessagesCount(){
        return (int)getRandomValue(generatorParams[0], generatorParams[1]);
    }

    public double[] getMessagesIntervals(int messagesCount){
        double[] result = new double[messagesCount];
        for (int i=0;i<messagesCount;i++){
            result[i] = getRandomValue(10, 50);
        }
        return result;
    }
}
