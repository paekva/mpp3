package generators;

import ifmo.mpp.lab3.EType;

public abstract class Generator {
    abstract double getRandomValue(double a, double b);

    double[] generatorParams;

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
        return (int)getRandomValue(1, 10);
    }

    public double[] getMessagesIntervals(int messagesCount){
        double[] result = new double[messagesCount];
        for (int i=0;i<messagesCount;i++){
            result[i] = getRandomValue(0, 20);
        }
        return result;
    }
}
